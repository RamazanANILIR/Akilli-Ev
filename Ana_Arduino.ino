#include <Stepper.h>
#include <SoftwareSerial.h>
SoftwareSerial digerArduino(10, 11);// RX, TX
const int hiz = 64 * 32;
Stepper perdeMotor(hiz, 5, 3, 2, 4);
Stepper garajMotor(hiz, 9, 7, 6, 8);
int zilButton = 12;
char veri;
char digerveri;
boolean bebeketkin = false;
int sicaklikdizisi[100];
int i = 0;
int toplam = 0;
int neg=15;
void setup() {
  Serial.begin(9600);
  digerArduino.begin(9600);
  perdeMotor.setSpeed(10);
  garajMotor.setSpeed(10);
  pinMode(zilButton, INPUT);
}

void loop() {
  sicaklikdizisi[i % 100] = (int)(analogRead(A0) * 0.48828125);
  for (int j = 0; j < 100; j++) toplam += sicaklikdizisi[j];
  Serial.print(toplam / 100-neg); //Sıcaklık ölçümündeki dalgalanmaları önlemek için son ölçülen 10 degeri bir diziye atıp ortalamasını aldım
  Serial.print("#"); 
  if(toplam/100-neg>30)neg++;
  toplam = 0;
  i++;
 
  if (digitalRead(zilButton) == HIGH) {
    digerArduino.print('e');
    Serial.print("zil");//Androide Zil çaldı bildirimi için sinyal gönder
    Serial.print("#");
  } else if (digitalRead(zilButton) == LOW) {
    digerArduino.print('f');
  }
  
  if (analogRead(A1) > 800 && bebeketkin) {
    Serial.print("bebek");
    Serial.print("#");
  }
  
  
  if (digerArduino.available() > 0) {
    digerveri = digerArduino.read();
    if (digerveri == 'a') {
      Serial.print("alarm");
      Serial.print("#");
    }
  }
  
  
  if (Serial.available() > 0) {
    veri = Serial.read();
    if (veri == 'a') {
      for (int i = 0; i < 4 ; i++) {
        perdeMotor.step(hiz);
      }
    } else if (veri == 'b') {
      for (int i = 0; i < 5; i++) {
        perdeMotor.step(-hiz);
      }
    } else if (veri == 'm') {
      for (int i = 0; i < 4 ; i++) {
        garajMotor.step(hiz);
      }
    } else if (veri == 'n') {
      for (int i = 0; i < 4; i++) {
        garajMotor.step(-hiz);
      }
    }
    else if (veri == 'u') {
      bebeketkin = true;
    }
    else if (veri == 'v') {
      bebeketkin = false;
    } else {
      digerArduino.print(veri);
    }
  }
  delay(100);
}
