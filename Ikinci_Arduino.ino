int ketle = 2;
int bahce = 3;
int zil = 4 ;
int lamba = 5 ;
int fan = 6;
int utu = 7;
int camasirMakinasi = 8 ;
int trigPin = 9;
int echoPin = 10;
int sacKurutmaMakinasi = 11 ;

long sure;
long uzaklik;
char veri;
boolean guvenliketkin = false;


void setup() {
  Serial.begin(9600);
  pinMode(ketle, OUTPUT);
  pinMode(bahce, OUTPUT);
  pinMode(zil, OUTPUT);
  pinMode(lamba, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(utu, OUTPUT);
  pinMode(camasirMakinasi, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sacKurutmaMakinasi, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW); /* sensör pasif hale getirildi */
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); /* Sensore ses dalgasının üretmesi için emir verildi */
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  /* Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi */
  sure = pulseIn(echoPin, HIGH); /* ses dalgasının geri dönmesi için geçen sure ölçülüyor */
  uzaklik = sure / 29.1 / 2; /* ölçülen sure uzaklığa çevriliyor */
  if (uzaklik < 4 && guvenliketkin) {
    Serial.print("a");
  }
  
  
  
  if (Serial.available() > 0) {
    veri = Serial.read();
    if (veri == 'k') {
      digitalWrite(ketle, HIGH);
    } else if (veri == 'l') {
      digitalWrite(ketle, LOW);
    } else if (veri == 'c') {
      digitalWrite(bahce, HIGH);
    } else if (veri == 'd') {
      digitalWrite(bahce, LOW);
    } else  if (veri == 'e') {
      digitalWrite(zil, HIGH);
    } else if (veri == 'f') {
      digitalWrite(zil, LOW);
    } else if (veri == 'g') {
      digitalWrite(lamba, HIGH);
    } else if (veri == 'h') {
      digitalWrite(lamba, LOW);
    } else if (veri == 'o') {
      digitalWrite(fan, HIGH);
    } else if (veri == 'p') {
      digitalWrite(fan, LOW);
    } else  if (veri == 'q') {
      digitalWrite(utu, HIGH);
    } else if (veri == 'r') {
      digitalWrite(utu, LOW);
    } else if (veri == 's') {
      digitalWrite(camasirMakinasi, HIGH);
    } else if (veri == 't') {
      digitalWrite(camasirMakinasi, LOW);
    } else if (veri == 'y') {
      guvenliketkin = true;
    } else if (veri == 'z') {
      guvenliketkin = false;
    } else if (veri == 'w') {
      digitalWrite(sacKurutmaMakinasi, HIGH);
    } else if (veri == 'i') {
      digitalWrite(sacKurutmaMakinasi, LOW);
    }
  }
  delay(100);
}
