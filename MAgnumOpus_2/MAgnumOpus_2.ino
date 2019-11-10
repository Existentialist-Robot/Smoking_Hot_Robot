

#include <Servo.h>
#include <Adafruit_VL53L0X.h>
//#include <SoftwareSerial.h>
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Servo serv1;
Servo serv2;
Servo servVert;
Servo servHortz;
//SoftwareSerial BTserial(11, 12); // RX | TX or 10,11

char c = ' ';
//boolean NL = true;
//const long baudRate = 38400;
int thing;
int pastTime = 1500;
int choice = 0;
int pos = 0; //Speed of servo 1
int pos2 = 180; //speed of servo 2
int ledpin = 13; // led on D13 will show blink on / off

void setup() {
  pinMode(10, INPUT);
//  pinMode(ledpin,OUTPUT);
  serv2.attach(8);
  serv1.attach(9);
  servVert.attach(7);
  servHortz.attach(6);
  Serial.begin(115200);
//  BTserial.begin(baudRate);
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  // power
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));

}

int checkTime(int interval, unsigned long previousMillis) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    return true;
  }
}
void dontHitWall() {
  thing = digitalRead(10);
  if (thing == LOW) {
    pos = 95;
    pos2 = 95;
    serv1.write(pos);
    serv2.write(pos2);
  }
}

void scan() {
  //effective range 60-180 neutral = 130
  int vertPos = 60;
  //effective range 0-60 neutral = 34
  int hortzPos = 0;
  int delayFact = 10;
  for (vertPos = 60; vertPos <= 180; vertPos ++) {
    while ((checkTime(delayFact, millis)) != true) {
      servVert.write(vertPos);

    }

  }
  for (vertPos = 180; vertPos >= 60; vertPos --) {
    servVert.write(vertPos);
    delay(delayFact);
    if (vertPos % 10 == 9) {
      maping();
    }

  }
  //Horizontal momement
  servVert.write(130);
  for (hortzPos = 34; hortzPos <= 60; hortzPos ++) {
    servHortz.write(hortzPos);
    delay(delayFact);
    if (hortzPos % 10 == 9) {
      maping();
    }

  }
  for (vertPos = 60; vertPos <= 180; vertPos ++) {
    servVert.write(vertPos);
    delay(delayFact);



  }
  for (vertPos = 180; vertPos >= 60; vertPos --) {
    servVert.write(vertPos);
    delay(delayFact);
    if (vertPos % 10 == 9) {
      maping();
    }

  }
  servVert.write(130);
  for (hortzPos = 60; hortzPos >= 0; hortzPos --) {
    servHortz.write(hortzPos);
    delay(delayFact);
    if (hortzPos % 10 == 9) {
      maping();
    }

  }
  for (vertPos = 60; vertPos <= 180; vertPos ++) {
    servVert.write(vertPos);
    delay(delayFact);


  }
  for (vertPos = 180; vertPos >= 60; vertPos --) {
    servVert.write(vertPos);
    delay(delayFact);
    if (vertPos % 10 == 9) {
      maping();
    }

  }
}
void maping() {
  VL53L0X_RangingMeasurementData_t measure;

  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
}

void loop() {
//  if (BTserial.available()) {
//    c = BTserial.read();
//    Serial.write(c);
//    if (c == '1') {
//      digitalWrite(ledpin, 1);
//      BTserial.println("LED  On D13 ON ! ");
//    }
//    if (c == '0') {
//      digitalWrite(ledpin, 0);
//      BTserial.println("LED  On D13 OFF ! ");
//    }
//  }

  if (choice == 0) {
    servVert.write(130);
    servHortz.write(34);
    serv1.write(pos);
    serv2.write(pos2);
    for ( int i = 0; i <= 1000; i++) {
      dontHitWall();
      delay(1);
    }
    choice += 1;

  } else {
    serv1.write(95);
    serv2.write(95);
    scan();
    choice = 0;
  }





}
