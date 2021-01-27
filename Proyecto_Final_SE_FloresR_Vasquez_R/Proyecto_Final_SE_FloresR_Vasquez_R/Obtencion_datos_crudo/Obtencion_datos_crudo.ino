int sensor135=0;
int mq7=1;
int aire=12;
int co2=11;
int gas=10;
//
int led5=5;
int led6=6;
int led7=7;
int i;

void setup() {
Serial.begin(9600);
pinMode(aire,OUTPUT);
pinMode(co2,OUTPUT);
pinMode(gas,OUTPUT);
//
pinMode(led5,OUTPUT);
pinMode(led6,OUTPUT);
pinMode(led7,OUTPUT);
digitalWrite(aire,LOW);
digitalWrite(co2,LOW);
digitalWrite(gas,LOW);
digitalWrite(led5,LOW);
digitalWrite(led6,LOW);
digitalWrite(led7,LOW);

}
void loop() {
  
  
  Serial.println("Sensor mq 135");
  for(i=0;i<150;i++){
  sensor135=analogRead(0);
    Serial.println(sensor135,DEC);
    delay(500);
  }
  Serial.println("Sensor mq 7  "); 
  for(i=0;i<150;i++){
    mq7=analogRead(1);
    Serial.println(mq7,DEC);
    delay(500);
  }    
}
