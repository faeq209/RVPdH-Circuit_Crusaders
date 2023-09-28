#define Motor1f 7 //Forward Pin for Motor1 in2
#define Motor1b 6 //Backward Pin for Motor1 in1
#define Motor2f 8 //Forward Pin for Motor2 in3
#define Motor2b 9 //Backward Pin for Motor2 in4
#define PWMmotor1 5 //Speed Pin for Motor1 ena1
#define PWMmotor2 10 //Speed Pin for Motor2 ena2

#define IR1 14 //Leftmost IR Sensor
#define IR2 15 //Left IR Sensor
#define IR3 16 //Center UP IR Sensor
#define IR4 17 //Center Down IR Sensor
#define IR5 18 //Right IR Sensor
#define IR6 19 //Rightmost IR Sensor

int valuePWM1 = 200; // speed motor 1
int valuePWM2 = 200; // speed motor 2

// Store the car was on False path or not untill it reaches the junction back
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Motor1f, OUTPUT);
  pinMode(Motor1b, OUTPUT);
  pinMode(Motor2f, OUTPUT);
  pinMode(Motor2b, OUTPUT);
  pinMode(PWMmotor1, OUTPUT);
  pinMode(PWMmotor2, OUTPUT);

  pinMode(IR1, INPUT); //Leftmost IR Sensor
  pinMode(IR2, INPUT); //Left IR Sensor
  pinMode(IR3, INPUT); //Center Down IR Sensor
  pinMode(IR4, INPUT); //Center Up IR Sensor
  pinMode(IR5, INPUT); //Right IR Sensor
  pinMode(IR6, INPUT); //Rightmost IR Sensor
  /* The Robot will follow Left Hand Rule that states in a maze you go on taking the left path anf you will eventually solve the maze. This is not the shortest path algorithm.
     There will be 5 IR sensor placed horizonatally on the front deck of the robot

                               IR4
                IR1     IR2           IR5      IR6
                               IR3
  */
  //The IR SENSOR will return 0 for white and 1 for black.

}

void loop() {
  // put your main code here, to run repeatedly:
  int s1 = digitalRead(IR1);//Left most
  int s2 = digitalRead(IR2);//Left
  int s3 = digitalRead(IR3);//center Down
  int s4 = digitalRead(IR4);//CENTER Up
  int s5 = digitalRead(IR5);//Right
  int s6 = digitalRead(IR6);//Right most

  Serial.print("Left Most value:");
  Serial.println(s1);
  Serial.print("Left value:");
  Serial.println(s2);
  Serial.print("Center Down value:");
  Serial.println(s3);
  Serial.print("Center Up value:");
  Serial.println(s4);
  Serial.print("Right value:");
  Serial.println(s5);
  Serial.print("Right Most value:");
  Serial.println(s6);

  //Forward condition 001100(IR1,IR2,IR3,IR4,IR5,IR6)
  if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 1 && s5 == 0 && s6 == 0 ) // For a straight black line
  {
    Serial.println("Move Straight");

    carforward();

  }


  // Reverse condition 001000
  else if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 0 && s5 == 0 && s6 == 0) //For a junction with right and left turns possible
  {
    Serial.println("Move Backward");

    carbackward();
  }


  // Left T condition 111X00
  else if (s1 == 1 && s2 == 1 && s3 == 1 && s5 == 0 && s6 == 0)
  {
    Serial.println("Move Left");

    carturnleft();
  }



  // Right T condition 001X11
  else if (s1 == 0 && s2 == 0 && s3 == 1 && s5 == 1 && s6 == 1)
  {
    Serial.println("Move Right");

    carturnright();
  }



  // Cross condition 111111
  else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1)
  {
    Serial.println("Move Left");

    carturnleft();
  }

  //Slight Left
  else if (s1 == 1 || s2 == 1)
  {
    Serial.println("Move Left");

    carturnleft();
  }



  //Slight Right
  else if (s5 == 1 || s6 == 1)
  {
    Serial.println("Move Right");

    carturnright();
  }


  // Stop condition 1X00X1
  else if (s1 == 1 && s3 == 0 && s4 == 0 && s6 == 1)
  {
    Serial.println("STOP");
    Serial.println("Maze Solved");

    carStop();
  }



}
void carforward() {
  analogWrite(PWMmotor1, valuePWM1);
  analogWrite(PWMmotor2, valuePWM2);
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor1f, HIGH);
  digitalWrite(Motor2f, HIGH);
  digitalWrite(Motor2b, LOW);
  delay(100);
}

void carturnleft() {
  analogWrite(PWMmotor1, valuePWM1);
  analogWrite(PWMmotor2, valuePWM2);
  digitalWrite(Motor1b, HIGH);
  digitalWrite(Motor1f, LOW);
  digitalWrite(Motor2f, HIGH);
  digitalWrite(Motor2b, LOW);
  delay(100);
}
void carturnright() {
  analogWrite(PWMmotor1, valuePWM1);
  analogWrite(PWMmotor2, valuePWM2);
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor1f, HIGH);
  digitalWrite(Motor2f, LOW);
  digitalWrite(Motor2b, HIGH);
  delay(100);
}
void carbackward() {
  analogWrite(PWMmotor1, valuePWM1);
  analogWrite(PWMmotor2, valuePWM2);
  digitalWrite(Motor1b, HIGH);
  digitalWrite(Motor1f, LOW);
  digitalWrite(Motor2f, HIGH);
  digitalWrite(Motor2b, LOW);
  delay(200);
}
void carStop() {
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor1f, LOW);
  digitalWrite(Motor2f, LOW);
  digitalWrite(Motor2b, LOW);

}