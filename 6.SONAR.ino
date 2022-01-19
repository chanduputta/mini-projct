#include <Servo.h>. 
#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13); //rs en d4...

const int trigPin = 4;
const int echoPin = 5;
#define servo1 3
Servo myServo;

long duration;
int distance;

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600); //gsm pin 0 and 1
  myServo.attach(servo1); // Defines on which pin is the servo motor attached
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  lcd.setCursor(0,0);lcd.print("SONAR RADAR");
  lcd.setCursor(0,1);lcd.print("MODEL SYSTEM "); delay(3000);
  lcd.clear();
}
void loop() {
  // rotates the servo motor from 0 to 180 degrees
  for(int i=0;i<=180;i++)
  {  
  myServo.write(i);delay(10);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing   
  lcd.setCursor(0,1);lcd.print(distance); delay(10);
  lcd.setCursor(0,1);lcd.print("      ");
 }
   lcd.setCursor(0,0);lcd.print("MONITORING     ");delay(5); 
       
  for(int i=180;i>0;i--)//reverse
  {  
    myServo.write(i);delay(10);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    lcd.setCursor(0,1);lcd.print(distance); delay(10);
    lcd.setCursor(0,1);lcd.print("      ");
   }
  lcd.setCursor(0,0);lcd.print("MONITORING     ");delay(5);  
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance()
{   
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

 
