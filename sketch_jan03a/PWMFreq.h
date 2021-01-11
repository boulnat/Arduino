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

#ifndef __PWMFREQ_H__
#define __PWMFREQ_H__

/* Allowed pins to change the PWM */
static const byte PINS_9_10 = 0;
static const byte PINS_3_11 = 1;

/* Allowed frequencies */
static const byte PWM_32k = 0; /* All pins */
static const byte PWM_4k  = 1; /* All pins */
static const byte PWM_1k  = 2; /* Pins 3 and 11 only */
static const byte PWM_500 = 3; /* All pins */
static const byte PWM_250 = 4; /* Pins 3 and 11 only */
static const byte PWM_125 = 5; /* All pins */
static const byte PWM_30  = 6; /* All pins */

/* PWM polarity */
static const byte PWM_NORMAL    = 2;
static const byte PWM_INVERTED  = 3;

/*
 * Set the Frequency of the PWM. Available frequencies are listed above
 */
void setPWMFrequency(byte pins, byte frequency);

/*
 * Set the polarity of the PWM. PWM_NORMAL or PWM_INVERTED.
 */
void setPWMPolarity(byte pin, byte pol);

/*
 * pwmWrite is quite the same as analogWrite with polarity taken into account.
 * I changed the second argument, val, to byte instead of int.
 * I removed the digitalWrite with a threshold for output that are not PWM capable.
 * It is restricted to be used on ATMega328.
 */
void pwmWrite(uint8_t pin, byte val);

#endif /* __PWMFREQ_H__ */
