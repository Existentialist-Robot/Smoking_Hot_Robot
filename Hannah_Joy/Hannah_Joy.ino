#include <Keypad.h>
#include <LiquidCrystal.h>

int ledPin = 13;
int joyPinx = 0;
int joyPiny = 1;
int valuex = 0;
/*pin x*/
int valuey = 0;
int x = 0;
int y = 0;
int c = 2;
int update_start = 1;

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {6, 7, 8, 9}; 
byte colPins[COLS] = {2, 3, 4, 5}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(22,24,26,28,30,32);

/*pin y*/
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}
//int treatValue(int data){
//  
//}
void loop(){
if(c==2){
  if(update_start == 1){
    lcd.setCursor(0, 0);
    lcd.print("0 for Auto");
    lcd.setCursor(0, 1);
    lcd.print("1 for Manual");
    update_start = 0;
  }
  char key = customKeypad.getKey();
  if (key == 0 || key == 1){
    Serial.println(key);
//    lcd.clear();
//    lcd.print(key);
      delay(500);
  }
  else{
    lcd.clear();
    lcd.print("Invalid Response");
    delay(1500);
    update_start = 1;
    c=2;
  }
}
else if(c==1){
 lcd.clear();
 lcd.print("Joystick Working");
 valuex = analogRead(joyPinx);
 delay(1500);
 valuey = analogRead(joyPiny);
 digitalWrite(ledPin,HIGH);

 digitalWrite(ledPin,LOW);

 if(valuey<510){
  if(valuex>=400 && valuex<=600){
    x = 0;
    y = 1;
  }
  else if(valuex<400){
    x=-1;
    y=0;
  }
  else if(valuex>600){
    x=1;
    y=0;
  }
 }
 else if(valuey>510){
  if(valuex>=400 && valuex<=600){
    x = 0;
    y = -1;
  }
  else if(valuex<400){
    x= -1;
    y= 0;
  }
  else if(valuex>600){
    x= 1;
    y= 0;
  }
 }
 else if (valuey = 510){
  if (valuex>=400 && valuex<=600){
    x=0;
    y=0;
  }
  else if (valuex<400){
    x = -1;
    y = 0;
  }
  else if(valuex>600){
    x = 1;
    y = 0;
  }
 }
 else{
  x = 0;
  y = 0;
 }
 

 int answer[] = {x,y};
 for (int i = 0; i < 2; i++){
  Serial.println(answer[i]);
 }
 Serial.println(valuex);
 Serial.println(valuey);

//lcd.setCursor(col, row)
//    lcd.setCursor(0, 0);
//    lcd.print(String("X Value: ") + String(valuex));
//    lcd.setCursor(0, 1);
//    lcd.print(String("Y Value: ") + String(valuey));
//    update_start = 0;
 
 /*Serial.print(valuex);
 Serial.println(valuey);*/
}
else if(c==0){
 lcd.clear();
 lcd.print("Automation Commence");
}
}
