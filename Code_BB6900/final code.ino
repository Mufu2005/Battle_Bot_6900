#include <Servo.h> //library for servo
#include <AFMotor.h> //library for shield
Servo myservo; // servo name
  
//initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ); //motor 1
AF_DCMotor motor2(2, MOTOR12_1KHZ); //motor 2
AF_Stepper stepper1(20, 2);
int in1 = 9;

int val; 
int Speed = 255; // speed of motor
int pos = 0; // initial potsition of servo

void setup() // code to run once
{
  stepper1.setSpeed(200);
  myservo.attach(10); // servo pin attach
  myservo.write(115); // servo write
  Serial.begin(9600);  // Set the baud rate to your Bluetooth module.
  pinMode(in1, OUTPUT);
  digitalWrite(in1, HIGH);
}

void loop(){           // main code       
  if(Serial.available() > 0){
    val = Serial.read();
      
    Stop(); // initialize with motors stoped
      
          if (val == 'a'){   // set value
          forward();  // set variable
          Serial.println("Forward"); // to check your code (output on serial monitor)
          }
  
          if (val == 'b'){
          backward();
          Serial.println("backward");          
          }
  
          if (val == 'c'){
          left();
          Serial.println("left");
          }
  
          if (val == 'd'){
          right();
          Serial.println("right");
          }
         
          if (val == 'i'){
          Stop();
          Serial.println("Stationary, waiting for signal");
          }

          if (val == 'f'){
          Servoup();
          Serial.println("cutter up");
          }

          if (val == 'e'){
            Servodown();
            Serial.println("cutter down");
          }
              
          if (val == 'g'){
            baydooropen();
            Serial.println("Bay door open");
          }
          if (val == 'h'){
            baydoorclose();
            Serial.println("Bay door close");
          }
          if (val == 'k'){
            cutterstart();
            Serial.println("Cutter Start");
          }
          if (val == 'j'){
            cutterstop();
            Serial.println("Cutter stopped");
          }                
  }
}


void forward(){
  motor1.setSpeed(Speed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwis
  motor2.setSpeed(Speed);
  motor2.run(FORWARD);
}

void backward(){
  motor2.setSpeed(Speed);
  motor2.run(BACKWARD);
  motor1.setSpeed(Speed); 
  motor1.run(BACKWARD);
}


void left(){
  motor1.setSpeed(Speed);
  motor1.run(FORWARD);
  motor2.setSpeed(Speed);
  motor2.run(BACKWARD);
}

void right(){
  motor1.setSpeed(Speed);
  motor1.run(BACKWARD);
  motor2.setSpeed(Speed);
  motor2.run(FORWARD); // Rotate motor anti clockwis
}

void Stop(){
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor2.setSpeed(0);
  motor2.run(RELEASE);
}

void Servoup(){
  myservo.write(-1); // define servo angle
}
 
void Servodown(){
  myservo.write(180);
}

void baydooropen(){
  stepper1.step(250, FORWARD, MICROSTEP);
  delay(3000);
}

void baydoorclose(){
  stepper1.step(250 , BACKWARD ,MICROSTEP);
}

void cutterstart(){
  digitalWrite(in1, HIGH);
}

void cutterstop(){
  digitalWrite(in1, LOW);
}
  
