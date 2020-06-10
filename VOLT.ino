/*
 *
 * File: VOLT.ino
 * Date: 10-06-2020
 * URL: https://github.com/Radionews/UImeter
 * License: MIT License
 *
 * В этом скрипте измеряется постоянное напряжение по 1 схеме
 *
*/

//сопротивления делителя
#define R1 (float)100100.0
#define R2 (float)9890.0
#define R3 (float)993.0

//сопротивления к источнику питания
#define R4 (float)9930.0
#define R5 (float)1113.0

#define Ri (float)1.0 //сопротивление шунта

#define VCC (float)4.7 //напряжение питания

float calc(int data_from_adc);
float calc_2(int data_from_adc);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  float out = calc(sensorValue);
  Serial.println(out);
  delay(500);
}

//расчет напряжения для диапазона 50В
float calc(int data_from_adc){
  float temp = 0;
  temp = (float)data_from_adc * (VCC / 1024.0);
  temp = temp * (1/R1 + 1/(R2+R3) + 1/R4);
  temp = temp - VCC/R4;
  temp = temp * R1;
  return temp;
}

//расчет напряжения для диапазона 500В
float calc_2(int data_from_adc){
  float temp = 0;
  temp = (float)data_from_adc * (VCC / 1024.0);
  temp = temp * (1/(R1+R2) + 1/R3 + 1/R5);
  temp = temp - VCC/R5;
  temp = temp * (R1+R2);
  return temp;
}