//LIBRARY DECLARATION 

#include <IRremote.h> 

#include <Servo.h> 

  

//DECLARATION OF OUTPUT ELECTRONIC COMPONENTS 

int RECV_PIN = 11; 

int led = 2; 

int buzzer = 4; 

int ledeme1 = 52; 

int ledeme2 = 53; 

int porta = 22; 

int porta2 = 9; 

int leds1 = 50; 

int leds2 = 48; 

int leds3 = 46; 

int leds4 = 44; 

int leds5 = 42; 

int a = 21; 

int b = 23; 

int c = 25; 

int d = 27; 

int g = 29; 

  

//DECLARATION OF INPUT ELECTRONIC COMPONENTS 

int ecoS = 7; 

int acionador = 8; 

int ecoS2 = 10; 

int acionador2 = 12; 

int botao = 26; 

  

//DECLARATION OF LOGICAL VARIABLES 

int x = 0; 

int pos; 

int frequency; 

int distance = 0; 

int distance2 = 0; 

float sine; 

  

//DECLARATION OF SERVO LIBRARY VARIABLES 

Servo s; 

Servo s2; 

  

//DECLARATION OF INFRARED RECEIVER LIBRARY VARIABLES 

IRrecv irrecv(RECV_PIN); 

decode_results results; 

  

//ULTRASONIC SENSOR DISTANCE READING FUNCTION 

long readUltrasonicDistance(int triggerPin, int echoPin) { 

  pinMode(triggerPin, OUTPUT);  

  digitalWrite(triggerPin, LOW); 

  delayMicroseconds(2); 

  digitalWrite(triggerPin, HIGH); 

  delayMicroseconds(10); 

  digitalWrite(triggerPin, LOW); 

  pinMode(echoPin, INPUT); 

  return pulseIn(echoPin, HIGH); 

} 

  

void setup() { 

  //SERIAL INITIALIZATION 

  Serial.begin(9600); 

  

  //INITIALIZATION OF THE INFRARED RECEIVER 

  irrecv.enableIRIn(); 

  

  //DECLARATION OF VARIABLES AS INPUT OR OUTPUT 

  pinMode(led, OUTPUT); 

  pinMode(buzzer, OUTPUT); 

  pinMode(botao, INPUT_PULLUP); 

  pinMode(ledeme1, OUTPUT); 

  pinMode(ledeme2, OUTPUT); 

  pinMode(leds1, OUTPUT); 

  pinMode(leds2, OUTPUT); 

  pinMode(leds3, OUTPUT); 

  pinMode(leds4, OUTPUT); 

  pinMode(leds5, OUTPUT); 

  pinMode(a, OUTPUT); 

  pinMode(b, OUTPUT); 

  pinMode(c, OUTPUT); 

  pinMode(d, OUTPUT); 

  pinMode(g, OUTPUT); 

  

  //ACTIVATION OF SERVO VARIABLES 

  s.attach(porta); 

  s2.attach(porta2); 

  

  //SET SERVOS TO INITIAL POSITION 

  s.write(0); 

  s2.write(0); 

} 

  

//FUNCTION TO RESET THE SKETCH 

void(* resetFunc) (void) = 0; 

  

void loop() { 

  //CONVERSION OF ULTRASONIC SENSOR READING INTO CENTIMETERS 

  distance = 0.01723 * readUltrasonicDistance(8, 7); 

  distance2 = 0.01723 * readUltrasonicDistance(12, 10); 

  

  //DISPLAYING THE DISTANCE OBTAINED BY THE ULTRASONIC SENSOR (COMMENTED TO BE USED ONLY WHEN NECESSARY) 

  //Serial.println(distance); 

  //Serial.println(distance2); 

  

  //READING THE INFRARED CONTROL SIGNAL THROUGH THE RECEIVER 

  if(irrecv.decode(&results)) { 

  

    //VARIABLE THAT STORES THE INFRARED WAVE CODE 

    unsigned int CR = results.value; 

  

    //DISPLAYING THE REGISTERED WAVE ON THE SERIAL MONITOR 

    Serial.println(CR); 

    delay(100); 

  

    //INFRARED RECEIVER LIBRARY FUNCTION 

    irrecv.resume(); 

     

    //CONDITION 2 (ROOM 2 WITH ULTRASONIC SENSOR ACTIVATED BETWEEN 5 AND 1 CM) 

    if(CR == 10839 && distance2 <= 5 && distance2 > 0) { 

  

      //CONDITION USED AS A PARAMETER IN THE REPEAT STRUCTURE 

      x = 2; 

  

      //OPENING SERVO MOTOR 1 

      for(pos = 0; pos < 90; pos++) { 

        s.write(pos); 

        delay(15); 

      } 

  

      //DISPLAYING NUMBER 3 ON THE SEVEN-SEGMENT DISPLAY (REFERRING TO THE SCHOOL NUMBER) 

      digitalWrite(a, 1); 

      digitalWrite(b, 1); 

      digitalWrite(c, 1); 

      digitalWrite(d, 1); 

      digitalWrite(g, 1); 

    } 

  

    //CONDITION 3 (ROOM 1 WITH ULTRASONIC SENSOR ACTIVATED BETWEEN 5 CM AND 1 CM) 

    if(CR == 10839 && distance <= 5 && distance > 0) { 

  

      //CONDITION USED AS A PARAMETER IN THE REPEAT STRUCTURE 

      x = 3; 

  

      //OPENING SERVO MOTOR 2 

      for(pos = 0; pos < 90; pos++) { 

        s2.write(pos); 

        delay(15); 

      } 

  

      //DISPLAYING NUMBER 3 ON THE SEVEN-SEGMENT DISPLAY (REFERRING TO THE SCHOOL NUMBER) 

      digitalWrite(a, 1); 

      digitalWrite(b, 1); 

      digitalWrite(c, 1); 

      digitalWrite(d, 1); 

      digitalWrite(g, 1); 

    } 

  

    //CONDITION 1 ACTIVATED BY BOTH INFRARED RECEIVERS WITHOUT ULTRASONIC SENSOR ACTION 

    if(CR == 55777) { 

  

      //CONDITION USED AS A PARAMETER IN THE REPEAT STRUCTURE 

      x = 1; 

  

      //OPENING BOTH SERVO MOTORS 

      for(pos = 0; pos < 90; pos++) { 

        s.write(pos); 

        delay(15); 

        s2.write(pos); 

        delay(15); 

      } 

  

      //DISPLAYING NUMBER 3 ON THE SEVEN-SEGMENT DISPLAY (REFERRING TO THE SCHOOL NUMBER) 

      digitalWrite(a, 1); 

      digitalWrite(b, 1); 

      digitalWrite(c, 1); 

      digitalWrite(d, 1); 

      digitalWrite(g, 1); 

    } 

  } 

  

  //INITIALIZATION OF CONDITION 1 (EXTERNAL ALERT) 

  while(x == 1) { 

  

    //ACTIVATION OF THE LEDS ABOVE THE DOORS INSIDE THE ROOMS 

    digitalWrite(ledeme1, HIGH); 

    delay(30); 

    digitalWrite(ledeme1, LOW); 

    delay(30); 

    digitalWrite(ledeme2, HIGH); 

    delay(30); 

    digitalWrite(ledeme2, LOW); 

    delay(30); 

  

    //CHAIN ACTIVATION OF THE LEDS LOCATED IN THE CORRIDOR, REFERENCING THE EMERGENCY DOOR (THE RED DOOR) 

    digitalWrite(leds1, HIGH); 

    delay(50); 

    digitalWrite(leds1, LOW); 

    delay(50); 

    digitalWrite(leds2, HIGH); 

    delay(50); 

    digitalWrite(leds2, LOW); 

    delay(50); 

    digitalWrite(leds3, HIGH); 

    delay(50); 

    digitalWrite(leds3, LOW); 

    delay(50); 

    digitalWrite(leds4, HIGH); 

    delay(50); 

    digitalWrite(leds4, LOW); 

    delay(50); 

    digitalWrite(leds5, HIGH); 

    delay(50); 

    digitalWrite(leds5, LOW); 

    delay(50); 

  

    //ACTIVATION OF THE BUZZER AT A FREQUENCY SIMILAR TO AN EMERGENCY ALERT 

    for(int x = 0; x < 180; x++) { 

  

      //VARIABLE CAUSING INSTABILITY IN THE BUZZER SOUND (AMBULANCE SOUND EFFECT) 

      sine = (sin(x * 3.1416 / 180)); 

      frequency = 2000 + (int(sine * 1000)); 

  

      //INSERTION OF THE UNSTABLE FREQUENCY AS A PARAMETER FOR THE BUZZER SOUND REPRODUCTION 

      tone(4, frequency); 

      delay(2); 

    } 

  

    //READING THE INFRARED CONTROL SIGNAL THROUGH THE RECEIVER 

    if(irrecv.decode(&results)) { 

  

      //VARIABLE THAT STORES THE INFRARED WAVE CODE 

      unsigned int CR = results.value; 

  

      //DISPLAYING THE REGISTERED WAVE ON THE SERIAL MONITOR 

      Serial.println(CR); 

      delay(100); 

  

      //INFRARED RECEIVER LIBRARY FUNCTION 

      irrecv.resume(); 

    } 

  

    //ACTIVATION OF THE LEDS ABOVE THE DOORS INSIDE THE ROOMS (REACTIVATED FOR OSCILLATION EFFECT) 

    digitalWrite(ledeme1, HIGH); 

    delay(30); 

    digitalWrite(ledeme1, LOW); 

    delay(30); 

    digitalWrite(ledeme2, HIGH); 

    delay(30); 

    digitalWrite(ledeme2, LOW); 

    delay(30); 

  

    //DEACTIVATION OF ALL ELECTRONIC COMPONENTS FORCED BY ACTIVATION OF THE SAFETY BUTTON (LOCATED IN THE OFFICE) 

    if(digitalRead(botao) == LOW) { 

  

      //DISPLAYING THE MESSAGE "BUTTON PRESSED" IF THE SAFETY BUTTON IS ACTIVATED 

      Serial.println("BUTTON PRESSED"); 

  

      //DEACTIVATION OF THE LEDS LOCATED IN THE CORRIDOR (USED TO REFER TO THE EMERGENCY DOOR) 

      digitalWrite(leds1, LOW); 

      digitalWrite(leds2, LOW); 

      
