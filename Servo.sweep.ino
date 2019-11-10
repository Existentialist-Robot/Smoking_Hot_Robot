#include <Servo.h>
Servo serv1;
Servo serv2;
int pos = 0; //Speed of servo 1 
int pos2 =180; //speed of servo 2
void setup() {
  serv2.attach(8);
  serv1.attach(9);


}

void loop() {

  serv1.write(pos);
  serv2.write(pos2);
}
