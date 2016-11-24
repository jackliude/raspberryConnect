String number[2]={};
String* castInt(double a,String number[]){
  String b = String(a);
   for(int i=0;i<b.length();i++){
    if(b.substring(i,i+1)=="."){
      if((b.substring(i+1,b.length()).toInt()==0)){
        number[0]=b.substring(0,i);
        number[1]="0";
        }else if(b.length()-i-1==1){
           number[0]=b.substring(0,i)+b.substring(i+1,b.length());
           number[1]="10";
          }
         else if(b.length()-i-1==2){
          number[0]=b.substring(0,i)+b.substring(i+1,b.length());
          number[1]="100";
          }
      }
    }
    return number;
  }
  
  void setValue(String &a,String &b,String *c){
    String *pt;
    pt=c;
    a=*pt;
    b=*(pt+1);
    }
    
 double castFloat(String a[]){
  double c;
  if(a[1].toInt()==0){
    return double(a[0].toInt());
    }
    else{
    c=double(a[0].toInt())/double(a[1].toInt());
    }
   return c;
  }
  
 void sendData(String recive[]){
  Serial.print(recive[0]);
  Serial.print(",");
  Serial.print(recive[1]);
  }
  
#include <dht11.h>
#define DHT11PIN 8
dht11 DHT11;
const int NUMBER_OF_FIELDS = 2;
int fieldIndex = 0;
int values[NUMBER_OF_FIELDS];
String  recive[2]={"",""};
const int sensorPin=0; 
const int input1 = 5;    
const int input2 = 6;  
double sun=0;
double temperature=NULL;
double humidity=NULL;
double switchValue=2000;
String sun1="";
String sun2="";
String temperature1="";
String temperature2="";
String humidity1="";
String humidity2="";
void Motor(double a,double b){
  if(a>=b){ 
  digitalWrite(input1,HIGH); 
  digitalWrite(input2,LOW); 
   }
  else{
 digitalWrite(input1,LOW);  
 digitalWrite(input2,LOW);    
    }
  }
void setup() {
 Serial.begin(9600);  
 pinMode(DHT11PIN,OUTPUT);
 pinMode(input1,OUTPUT);  
 pinMode(input2,OUTPUT);  
}
void loop() {
  sun=analogRead(sensorPin);
  int chk = DHT11.read(DHT11PIN);
  temperature=(float)DHT11.temperature;
  humidity=(float)DHT11.humidity;
  Motor(sun,switchValue);
 //Serial.print(sun);
 //Serial.print(" ");
 //Serial.println(switchValue);
  delay(1000);
   if (Serial.available()) {
    if(Serial.available()>0){
    int count = 0;
    char ch = Serial.read();
    if (ch >= '0' && ch <= '9') {
      if (fieldIndex < NUMBER_OF_FIELDS) {
        values[fieldIndex] = (values[fieldIndex] * 10) + (ch - '0');
      }
    }
    else if (ch == ',') {
      fieldIndex++;
    }
    else {
      for (int i = 0; i < min(NUMBER_OF_FIELDS, fieldIndex + 1); i++) {
        recive[count] = values[i];
        count++;
        values[i] = 0;
      }
      fieldIndex = 0;
      switchValue=castFloat(recive);
    }
   }

  if(humidity!=NULL && temperature!=NULL){
   setValue(sun1,sun2,castInt(sun,number));
   setValue(temperature1,temperature2,castInt(temperature,number));
   setValue(humidity1,humidity2,castInt(humidity,number));
 
  //Serial.println("set value success");
  //Serial.println(sun1);
  //Serial.println(sun2);
  //Serial.println(temperature1);
  //Serial.println(temperature2);
  //Serial.println(humidity1);
  //Serial.println(humidity2);
  if (recive[1]!="" && sun2!="" && temperature2!="" && humidity2!="") {
      Serial.print("H");
      Serial.print(",");
      Serial.print(sun1);
      Serial.print(",");
      Serial.print(sun2);
      Serial.print(",");
      Serial.print(temperature1);
      Serial.print(",");
      Serial.print(temperature2);
      Serial.print(",");
      Serial.print(humidity1);
      Serial.print(",");
      Serial.print(humidity2);
      Serial.print(",");
      sendData(recive);
      Serial.println();
      recive[1]="";
      sun1="";// 回收标志
      sun2="";
      temperature1="";
      temperature2="";
      humidity1="";
      humidity2="";
      }
    }
  }
 
}


 
