#define potentiometer  A0  //10k Variable Resistor
#define sensorPin A1 // choose the input pin (for GAS sensor)  

#define R_led 2 // choose the pin for the Red Led
#define Relay 6 // choose the pin for the Relay moudel

int read_ADC =0;
int set_timer =0;
int sensor =0;
int seconds =0 ,timer=0;
int flag=0;
long delay_Start;


void setup(){ // put your setup code here, to run once

Serial.begin(9600);// initialize serial communication at 9600 bits per second:
  
pinMode(sensorPin, INPUT); // declare sensor as input

pinMode(R_led,OUTPUT); // declare Red LED as output
pinMode(Relay,OUTPUT); // declare Relay as output
digitalWrite(Relay, HIGH);// Relay Turn Off

delay(1000); // Waiting for a while
}

void loop(){
read_ADC = analogRead(potentiometer); // read analogue to digital value 0 to 1023
set_timer = read_ADC /17.05; // Maximum value analogue to digital 1023 / 17.05

sensor = digitalRead(sensorPin);

if(sensor==1){ // pin state change: 0 -> 1
Serial.println("Motion detected!");
digitalWrite(R_led, HIGH); // LED Turn On 
digitalWrite(Relay, LOW); // Relay Turn On 
seconds = 0;
flag=1;
delay_Start = millis(); // set start time
}
else{ // pin state change: 1 -> 0
Serial.println("Motion stopped!");
digitalWrite(R_led, LOW); // LED Turn Off.  
}

if((flag==1) && (millis()- delay_Start) > 999){ 
seconds = seconds+1;  
delay_Start = millis(); // set start time
}

if(seconds>set_timer){
flag=0;
seconds=0; 
digitalWrite(Relay, HIGH); // Relay Turn Off   
}

delay(100);
}
