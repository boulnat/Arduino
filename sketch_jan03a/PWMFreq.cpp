/*=============================================================================
 * PWMFreq
 *
 * Copyright (c) 2017 Jean-Luc Béchennec. All rights reserved
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *=============================================================================
 */

#include <avr/io.h>
#include "wiring_private.h"
#include "Arduino.h"
#include "PWMFreq.h"

/* CS codes for timer 1 */
const byte codeForTimer1[] PROGMEM = {
  B00000001,
  B00000010,
  B00000000, /* no clock if config not allowed */
  B00000011,
  B00000000, /* no clock if config not allowed */
  B00000100,
  B00000101,
};

/* CS codes for timer 2 */
const byte codeForTimer2[] PROGMEM = {
  B00000001,
  B00000010,
  B00000011,
  B00000100,
  B00000101,
  B00000110,
  B00000111,
};

/*
 * Set the Frequency of the PWM. Look PWMFreq.h for available frequencies
 */
void setPWMFrequency(byte pins, byte frequency)
{
    if (frequency < 7) {
        if (pins == PINS_9_10) {
            byte csCode = pgm_read_byte_near(codeForTimer1 + frequency);
            TCCR1B &= B11111000; /* aucune horloge */
            TCCR1B |= csCode;
        }
        else if (pins == PINS_3_11) {
            byte csCode = pgm_read_byte_near(codeForTimer2 + frequency);
            TCCR2B &= B11111000; /* aucune horloge */
            TCCR2B |= csCode;
        }
    }
}

/*
 * Set the polarity of the PWM. PWM_NORMAL or PWM_INVERTED.
 */
void setPWMPolarity(byte pin, byte pol)
{
    if (pol == PWM_NORMAL || pol == PWM_INVERTED) {
        switch (pin) {
            case 3:
                /* OC2B output */
                TCCR2A = (TCCR2A & B11001111) | (pol << 4); break;
            case 5:
                /* OC0B output */
                TCCR0A = (TCCR0A & B11001111) | (pol << 4); break;
            case 6:
                /* OC0A output */
                TCCR0A = (TCCR0A & B00111111) | (pol << 6); break;
            case 9:
                /* OC1A output */
                TCCR1A = (TCCR1A & B00111111) | (pol << 6); break;
            case 10:
                /* OC1B output */
                TCCR1A = (TCCR1A & B11001111) | (pol << 4); break;
            case 11:
                /* OC2A output */
                TCCR2A = (TCCR2A & B00111111) | (pol << 6); break;
        }
    }
}


bool notExtremumPWM(byte pin, byte val, byte pol)
{
    bool notExtremumPWMFlag = true;
    
    if (val == 0) {
        if (pol == 0) {
            digitalWrite(pin, LOW);
        }
        else {
            digitalWrite(pin, HIGH);
        }
        notExtremumPWMFlag = false;
    }
    else if (val == 255) {
        if (pol == 0) {
            digitalWrite(pin, HIGH);
        }
        else {
            digitalWrite(pin, LOW);
        }
        notExtremumPWMFlag = false;
    }
    
    return notExtremumPWMFlag;
}

/*
 * pwmWrite is quite the same as analogWrite with polarity taken into account.
 * I changed the second argument, val, to byte instead of int.
 * I removed the digitalWrite with a threshold for output that are not PWM capable.
 * It is restricted to be used on ATMega328.
 */
void pwmWrite(uint8_t pin, byte val)
{
	// We need to make sure the PWM output is enabled for those pins
	// that support it, as we turn it off when digitally reading or
	// writing with them.  Also, make sure the pin is in output mode
	// for consistenty with Wiring, which doesn't require a pinMode
	// call for the analog output pins.
	pinMode(pin, OUTPUT);
	
    switch(digitalPinToTimer(pin))
    {
        #if defined(TCCR0A) && defined(COM0A1)
        case TIMER0A:
            // read COM0A0 to check the polarity
            if (notExtremumPWM(pin, val, TCCR0A & B01000000)) {
                // connect pwm to pin on timer 0, channel A
                sbi(TCCR0A, COM0A1);
                OCR0A = val; // set pwm duty
            }
            break;
        #endif

        #if defined(TCCR0A) && defined(COM0B1)
        case TIMER0B:
            if (notExtremumPWM(pin, val, TCCR0A & B00010000)) {
                // connect pwm to pin on timer 0, channel B
                sbi(TCCR0A, COM0B1);
                OCR0B = val; // set pwm duty
            }
            break;
        #endif

        #if defined(TCCR1A) && defined(COM1A1)
        case TIMER1A:
            if (notExtremumPWM(pin, val, TCCR1A & B01000000)) {
                // connect pwm to pin on timer 1, channel A
                sbi(TCCR1A, COM1A1);
                OCR1A = val; // set pwm duty
            }
            break;
        #endif

        #if defined(TCCR1A) && defined(COM1B1)
        case TIMER1B:
            if (notExtremumPWM(pin, val, TCCR1A & B00010000)) {
                // connect pwm to pin on timer 1, channel B
                sbi(TCCR1A, COM1B1);
                OCR1B = val; // set pwm duty
            }
            break;
        #endif

        #if defined(TCCR2A) && defined(COM2A1)
        case TIMER2A:
            if (notExtremumPWM(pin, val, TCCR2A & B01000000)) {
                // connect pwm to pin on timer 2, channel A
                sbi(TCCR2A, COM2A1);
                OCR2A = val; // set pwm duty
            }
            break;
        #endif

        #if defined(TCCR2A) && defined(COM2B1)
        case TIMER2B:
            if (notExtremumPWM(pin, val, TCCR2A & B00010000)) {
                // connect pwm to pin on timer 2, channel B
                sbi(TCCR2A, COM2B1);
                OCR2B = val; // set pwm duty
            }
            break;
        #endif
    }
}
