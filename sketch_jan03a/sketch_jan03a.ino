/*#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
 
void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");
  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
 
  // save I2C bitrate
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 12; // upgrade to 400KHz!
 
}
 
void loop() {
  // Drive each PWM in a 'wave'
  for (uint16_t i=0; i<4096; i += 8) 
  {
    for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++) 
    {
      pwm.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
    }
  }
}
*/

/*
int led_pin_5 = 5;
int led_pin_6 = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin_5, OUTPUT);
  pinMode(led_pin_6, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //analogWrite(led_pin_5, 0);
  //analogWrite(LED_BUILTIN, 0);
  
  digitalWrite(led_pin_5, HIGH);
  digitalWrite(led_pin_6, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(233);
  digitalWrite(led_pin_5, LOW);
  digitalWrite(led_pin_6, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}
  /*
for(int i=0; i<60; i++){
    analogWrite(led_pin_5, i);
    analogWrite(led_pin_6, (60-i));
    delay(5);
  }
  for(int i=60; i>0; i--){
    analogWrite(led_pin_5, i);
    analogWrite(led_pin_6, (60-i));
    delay(5);
  }
}*/

/*
 * This example sets the pins 9 and 10 frequency to 32kHz and pins 3 and 11 frequency to 4kHz
 * and outputs a PWM with a 50% duty cycle.
 *//*
#include "PWMFreq.h"

void setup() {
  setPWMFrequency(PINS_9_10, PWM_32k);
  setPWMFrequency(PINS_3_11, PWM_4k);
  analogWrite(9,0);
  analogWrite(3,0);
}

void loop() {
}*/

int latchPin = 5;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 6; // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 4;  // Data pin of 74HC595 is connected to Digital pin 4

byte leds = 0;    // Variable to hold the pattern of which LEDs are currently turned on or off

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

/*
 * loop() - this function runs over and over again
 */
void loop() 
{
  
  leds = 0xFE; // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  updateShiftRegister();
  delay(125);
  leds = 0xFD;
  updateShiftRegister();
  delay(125);
  leds = 0xFF;
  updateShiftRegister();
  delay(125);
  leds = 0xFC;
  updateShiftRegister();
  delay(125);
  
  leds = 0xFF; // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  updateShiftRegister();
  delay(125);

  leds = 0xFE;
  updateShiftRegister();
  delay(125);
  leds = 0xFF; // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  updateShiftRegister();
  delay(125);

  leds = 0xFE;
  updateShiftRegister();
  delay(125);
  leds = 0xFD; // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  updateShiftRegister();
  delay(125);
  leds = 0xFF;
  updateShiftRegister();
  delay(125);
  leds = 0xFD;
  updateShiftRegister();
  delay(125);
  
  leds = 0xFE;
  updateShiftRegister();
  delay(125);
  leds = 0xFF; // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  updateShiftRegister();
  delay(125);

  leds = 0xFE;
  updateShiftRegister();
  delay(125);
  leds = 0xFF; // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  updateShiftRegister();
  delay(125);
  delay(250);

}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
