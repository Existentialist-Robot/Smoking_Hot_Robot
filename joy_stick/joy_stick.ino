int ledPin = 13;
int joyPinx = 0;
int joyPiny = 1;
int valuex = 0;
/*pin x*/
int valuey = 0;
int x = 0;
int y = 0;

/*pin y*/
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}
//int treatValue(int data){
//  
//}
void loop() {
  // put your main code here, to run repeatedly:
 valuex = analogRead(joyPinx);
 delay(100);
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
// for (int i = 0; i < 2; i++){
//  Serial.println(answer[i]);
// }
// Serial.println(valuex);
// Serial.println(valuey);
 
 
 /*Serial.print(valuex);
 Serial.println(valuey);*/
 
}
