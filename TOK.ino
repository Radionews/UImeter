/*
 *
 * File: TOK.ino
 * Date: 10-06-2020
 * URL: https://github.com/Radionews/UImeter
 * License: MIT License
 *
 * В этом скрипте измеряется постоянный ток протекающий через нагрузку, по 2 схеме.
 *
*/

#define Ri (float)1.0 //сопротивление шунта

#define VCC (float)4.7 //напряжение питания

float calc(int data_from_adc);
float calc_2(int data_from_adc);
float current(int data_from_adc);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  float out = ((float)sensorValue * (VCC / 1024.0))/Ri;
  Serial.println(out);
  delay(500);
}