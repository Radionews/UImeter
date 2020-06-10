/*
 *
 * File: TOK_RMS.ino
 * Date: 10-06-2020
 * URL: https://github.com/Radionews/UImeter
 * License: MIT License
 *
 * В этом скрипте измеряется RMS ток протекающий через нагрузку, по 3 схеме.
 *
*/

#include <TrueRMS.h>
#include <digitalWriteFast.h>

#define LPERIOD 1000    // loop period time in us. In this case 1.0ms
#define ADC_INPUT 0     // define the used ADC input channel
#define RMS_WINDOW 40   // rms window of 40 samples, means 2 periods @50Hz
//#define RMS_WINDOW 50   // rms window of 50 samples, means 3 periods @60Hz

#define Ri (float)1.0 //сопротивление шунта

#define VCC (float)4.7 //напряжение питания

#define PIN_DEBUG 4

unsigned long nextLoop;
int adcVal;
int cnt=0;
float VoltRange = VCC; // The full scale value is set to 5.00 Volts but can be changed when using an
                        // input scaling circuit in front of the ADC.

Rms readRms; // create an instance of Rms.

float calc(float data_from_adc, int dc);
float calc_2(float data_from_adc, int dc);

void setup() {
  // run once:
  Serial.begin(115200);
  pinMode(PIN_DEBUG, OUTPUT);
  

  // configure for automatic base-line restoration and continuous scan mode:
  digitalWriteFast(PIN_DEBUG, HIGH);
  readRms.begin(VoltRange, RMS_WINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  digitalWriteFast(PIN_DEBUG, LOW);
    
  readRms.start(); //start measuring
  
  nextLoop = micros() + LPERIOD; // Set the loop timer variable for the next loop interval.
  }

void loop() {
  // run repeatedly:
  adcVal = analogRead(ADC_INPUT); // read the ADC.
  readRms.update(adcVal); 

  cnt++;
  if(cnt >= 500) { // publish every 0.5s
    readRms.publish();
    Serial.println(2*readRms.rmsVal/Ri,3);
    cnt=0;
  }

  while(nextLoop > micros());  // wait until the end of the loop time interval
  nextLoop += LPERIOD;  // set next loop time to current time + LOOP_PERIOD
}