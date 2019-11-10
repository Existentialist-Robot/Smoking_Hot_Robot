

#include <Servo.h>
#include <Adafruit_VL53L0X.h>
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Servo serv1;
Servo serv2;
Servo servVert;
Servo servHortz;
int joyPinx = 8;
int joyPiny = 9;
int valuex = 0;
int valuey = 0;
int x = 0;
int y = 0;
int thing;
int codes{3};
int pastTime = 1500;
int choice = 0;
int pos = 0; //Speed of servo 1
int pos2 = 180; //speed of servo 2
void setup() {
  pinMode(10, INPUT);
  serv2.attach(8);
  serv1.attach(9);
  servVert.attach(7);
  servHortz.attach(6);
  digitalWrite(11, HIGH);
  pinMode(11, INPUT);
  Serial.begin(9600);
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
void joyStick() {
  // put your main code here, to run repeatedly:
  valuex = analogRead(joyPinx);
  delay(10);
  valuey = analogRead(joyPiny);

  digitalWrite(11, HIGH);
  int val = digitalRead(11);

  Serial.println(val);

  if (valuey < 500) {
    if (valuex >= 400 && valuex <= 600) {
      x = 0;
      y = 1;
    }
    else if (valuex < 400) {
      x = -1;
      y = 0;
    }
    else if (valuex > 600) {
      x = 1;
      y = 0;
    }
  }
  else if (valuey > 520) {
    if (valuex >= 400 && valuex <= 600) {
      x = 0;
      y = -1;
    }
    else if (valuex < 400) {
      x = -1;
      y = 0;
    }
    else if (valuex > 600) {
      x = 1;
      y = 0;
    }
  }
  else if (valuey = 510) {
    if (valuex >= 400 && valuex <= 600) {
      x = 0;
      y = 0;
    }
    else if (valuex < 400) {
      x = -1;
      y = 0;
    }
    else if (valuex > 600) {
      x = 1;
      y = 0;
    }
  }
  else {
    x = 0;
    y = 0;
  }


  int answer[] = {x, y, val};


  Serial.print(x);
  Serial.print(" ");
  Serial.println(y);
  if (val == 0){
    choice = 1;
    pos =95;
    pos2 =95;
  }
  if (x == 0 && y ==0){
    pos =95;
    pos2 =95;
  }
  if (y == 1) {
    pos = 180;
    pos2 = 0;
  }
  else if (y == -1){
  pos = 0;
  pos2 = 180;
}
else if (x == 1) {
    pos = 0;
    pos2 = 0;
  } else if (x == -1) {
    pos = 180;
    pos2 = 180;
  }

}
void dontHitWall() {
  thing = digitalRead(10);
  if (thing == LOW) {
    pos = 180;
    pos2 = 0;
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
  joyStick();
  if (choice == 0) {

    servVert.write(130);
    servHortz.write(34);
    serv1.write(pos);
    serv2.write(pos2);
    dontHitWall();


  } else if (choice == 1) {
    serv1.write(95);
    serv2.write(95);
    pos = 95;
    pos2 =95;
    scan();
    serv1.write(95);
    serv2.write(95);
    delay(500);
    choice = 0;
  }





}
