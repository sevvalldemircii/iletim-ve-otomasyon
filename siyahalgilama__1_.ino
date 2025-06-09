#include <Servo.h>
#define s0 5
#define s1 6
#define s2 7
#define s3 8
#define role 3
#define cikis 9
#define TRIG_PIN 12
#define ECHO_PIN 13
Servo myServo;
int kirmizi, yesil, mavi = 0;
long duration;
float distance;
float degisti = true;

void setup() {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(role,OUTPUT);
  pinMode(cikis, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  Serial.begin(9600);
  myServo.attach(11);
}

void loop() {
  Serial.println(degisti);
  kalibreedilmis();
  renkbelirle();
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

}

void kalibreet() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  kirmizi = pulseIn(cikis, LOW);
  Serial.print("Kırmızı renk: ");
  Serial.print(kirmizi);
  Serial.print("\t");
  delay(50);

  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  yesil = pulseIn(cikis, LOW);
  Serial.print("Yeşil renk: ");
  Serial.print(yesil);
  Serial.print("\t");
  delay(50);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  mavi = pulseIn(cikis, LOW);
  Serial.print("Mavi renk: ");
  Serial.print(mavi);
  Serial.println("\t");
  delay(50);
}

void kalibreedilmis() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  kirmizi = pulseIn(cikis, LOW);
  kirmizi = map(kirmizi, -23, 45, -40, 60);
  Serial.print("Kırmızı renk: ");
  Serial.print(kirmizi);
  Serial.print("\t");
  delay(50);

  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  yesil = pulseIn(cikis, LOW);  
  yesil = map(yesil, -15, 47, -30, 70);
  Serial.print("Yeşil renk: ");
  Serial.print(yesil);
  Serial.print("\t");
  delay(50);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  mavi = pulseIn(cikis, LOW);
  mavi = map(mavi, -16, 46, -25, 75);
  Serial.print("Mavi renk: ");
  Serial.print(mavi);
  Serial.println("\t");
  delay(50);
}

void renkbelirle() {
  // Siyah rengi algıla (RGB yüksekse, yansıma azsa → siyah)
  if (400 >kirmizi && kirmizi > 310 && 510> yesil&& yesil > 410 && 460 > mavi && mavi> 380) {

    Serial.println("Siyah algılandı");
    if(distance < 15)
    {
    delay(800);
    digitalWrite(role,HIGH);
    delay(500);
    digitalWrite(role,LOW);
    
    }

    


  }
  else if (60 <kirmizi && kirmizi < 100 && 220<mavi&& mavi<280 && 270<yesil&& yesil<330) {
 
    Serial.println("Kırmızı algılandı");
    if(distance<15)
    {
    degisti = true;
    myServo.write(90);
    }
    digitalWrite(role,LOW);
    }

  
  else if (250 <kirmizi&& kirmizi < 320 && 70<mavi&& mavi<120 && 160<yesil&& yesil<220) {

    Serial.println("Mavi algılandı");
    
    if(distance<15)
    {
      degisti = true;
    myServo.write(135);
    }
    digitalWrite(role,LOW);

    
  }
  
  else if  (270 <kirmizi&& kirmizi < 330 && 250<mavi&& mavi<310 && 210<yesil&& yesil<270) {

    Serial.println("Yeşil algılandı");
    if(distance<15)
    {
      degisti = true;
    myServo.write(180);
    }
    digitalWrite(role,LOW);

    
  }
  else {

    Serial.println("Renk algılanamadı");
    digitalWrite(role,LOW);
  }
    Serial.print("Mesafe: ");
    Serial.print(distance);
    Serial.println("m");
}
