/* YourDuino / KUFFY EBONG  Robot Control
  - WHAT IT DOES Controls a Keyes robot in multiple modes
  - SEE the comments after "//" on each line below

  - V1.01 16 August 2019
  - V1.01 18 September 2019: corrected autoDrive() function, added servo for ultrasonic, added lightFollower() function, added  edge detection
   Questions: kuffykeys@gmail.com , terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SimpleKalmanFilter.h>
#include <Servo.h>


/*-----( Declare Constants and Pin Numbers )-----*/
//ultrasonic sensor parameters  PINS USED: 0,1,2,3,4,5,6,7,8,9,10,12,13,A0,A1,A2,A3,A4 remainder---->11,A5 for the 2 other photo sensors.... Not enough pins on UNO. That means we have to use just 1 photo sensor in front
const byte trigPin = 9;
const byte echoPin = 8;

const byte ldrPin = A4;

byte servoPin = 11;

byte thresholdDist = 35;

int lightThreshold = 600;

/*************positions of servo *****************/
byte lookLeft = 175, lookRight = 30, lookAhead = 95;

/***********flags for the millis state  ********************/
bool state1 = false, state2 = false, state3 = false, state4 = false, state5 = false, state6 = false;


bool reset1 = true, reset2 = true, reset3 = true, reset4 = true, reset5 = true, reset6 = true;

float dist1 = NULL;


/*************maybe create flags for the state of the robots movement declare these variables when the autoDrive state is entered*******************/

unsigned long prevMillis1 = 0l, prevMillis2 = 0l, prevMillis3 = 0l, prevMillis4 = 0l, prevMillis5 = 0l, prevMillis6 = 0l, currentMillis = 0l;


int pauseInterval = 1000;


const byte leftLine = A1;   // PhotoSensors in Line Follower
const byte  middleLine = A2;
const byte rightLine = A3;

const byte MA_dir = 4;  // Motor Control Pins Direction and PWM Speed
const byte MB_dir = 7;
const byte MA_spd = 5;
const byte MB_spd = 6;

const byte buzzerPin = 13; //meant for obstacle alert


/*-----( Declare objects )-----*/
SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);
Servo servo;          //create servo object to control a servo, max = 8 servos

/*-----( Declare Variables )-----*/

float dist = 0.00;
float obstacleThreshold = 35; //Threshold distance where the robot sees object in front of it as an obstacle
float estimated_value = 0;

unsigned long buzzerInterval = 0;

/*------( flags to hold the different robot modes )-----*/

bool manMode = false;
bool lineMode = false;
bool autoMode = false;
bool followMode = false;
bool StopMode = false;
bool frontMode = false;
bool backMode = false;
bool leftMode = false;
bool rightMode = false;
bool lightMode = false;

/*-----( variable to hold data from Serial )-----*/

char val = ' ';
char val1 = ' ';



void setup()   /**************************** SETUP: RUNS ONCE *******************/
{
  pinMode(leftLine, INPUT);
  pinMode(middleLine, INPUT);
  pinMode(rightLine, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(MA_dir, OUTPUT);
  pinMode(MB_dir, OUTPUT);
  pinMode(MA_spd, OUTPUT);
  pinMode(MB_spd, OUTPUT);


  servo.attach(servoPin);
  servo.write(95); //default central position

  Serial.begin(9600);

}//--(end setup )---

void loop()   /******************** LOOP: RUNS CONSTANTLY *******************/
{
  //  buzzer();
  //  delay(10);
  //  buzzer();
  //  delay(500);
  //  Serial.println(detectLight());
  if (Serial.available())
  {
    val = Serial.read();
    switch (val) {

      case 'M':
        manMode = true;
        lineMode = false;
        autoMode = false;
        followMode = false;
        lightMode = false;
        break;

      case 'f':
        manMode = false;
        lineMode = false;
        autoMode = false;
        followMode = true;
        lightMode = false;
        break;

      case 'T':
        manMode = false;
        lineMode = true;
        autoMode = false;
        followMode = false;
        lightMode = false;
        break;

      case 't':
        manMode = false;
        lineMode = false;
        autoMode = false;
        followMode = false;
        lightMode = true;
        break;

      case 'A':
        manMode = false;
        lineMode = false;
        autoMode = true;
        followMode = false;
        lightMode = false;

        dist1 = obstacle();
        state1 = true;
        state2 = false; state3 = false; state4 = false; state5 = false; state6 = false;
        reset1 = true; reset2 = true; reset3 = true; reset4 = true; reset5 = true; reset6 = true;

      case 'S':
        StopMode = true;
        frontMode = false;
        backMode = false;
        leftMode = false;
        rightMode = false;
        lightMode = false;
        break;

      case 'F':
        StopMode = false;
        frontMode = true;
        backMode = false;
        leftMode = false;
        rightMode = false;
        lightMode = false;
        break;

      case 'B':
        StopMode = false;
        frontMode = false;
        backMode = true;
        leftMode = false;
        rightMode = false;
        lightMode = false;
        break;

      case 'L':
        StopMode = false;
        frontMode = false;
        backMode = false;
        leftMode = true;
        rightMode = false;
        lightMode = false;
        break;

      case 'R':
        StopMode = false;
        frontMode = false;
        backMode = false;
        leftMode = false;
        rightMode = true;
        lightMode = false;
        break;

      default:
        StopMode = true;
        frontMode = false;
        backMode = false;
        leftMode = false;
        rightMode = false;
        lightMode = false;
        break;
    }
  }// END If Serial Vaialable

  if (manMode)
  {
    digitalWrite(buzzerPin, HIGH);
    if (StopMode) {
      Stop();
    }

    if (frontMode) {
      front();
    }

    if (backMode) {
      back();
    }

    if (leftMode) {
      left();
    }

    if (rightMode) {
      right();
    }
  }// END If ManMode

  if (lineMode)
  {
    trackLine();
  }

  if (autoMode) {
    autoDrive();
  }

  if (followMode) {
    follower();
  }

  if (lightMode) {
    detectLight();
  }

}//--(end main loop )---



/*-----( Declare User-written Functions )-----*/
void front()
{
  digitalWrite(MA_dir, HIGH);
  digitalWrite(MB_dir, HIGH);
  analogWrite(MA_spd, 80);
  analogWrite(MB_spd, 80);
}

void back()
{
  digitalWrite(MA_dir, LOW);
  digitalWrite(MB_dir, LOW);
  analogWrite(MA_spd, 80);
  analogWrite(MB_spd, 80);
}

void Stop()
{
  digitalWrite(MA_dir, HIGH);
  digitalWrite(MB_dir, HIGH);
  analogWrite(MA_spd, 0);
  analogWrite(MB_spd, 0);
}

void left()
{
  digitalWrite(MA_dir, LOW);
  digitalWrite(MB_dir, HIGH);
  analogWrite(MA_spd, 80);
  analogWrite(MB_spd, 80);
}

void right()
{
  digitalWrite(MA_dir, HIGH);
  digitalWrite(MB_dir, LOW);
  analogWrite(MA_spd, 80);
  analogWrite(MB_spd, 80);
}

void trackLine()
{
  if (digitalRead(middleLine))
  {
    if (digitalRead(rightLine) && !(digitalRead(leftLine)))
    {
      front();
    }
    else if (!(digitalRead(rightLine)) && digitalRead(leftLine))
    {
      front();
    }
    else
    {
      front();
    }
  }
  else
  {
    if (digitalRead(rightLine) && !(digitalRead(leftLine)))
    {
      left();
    }
    else if (!(digitalRead(rightLine)) && digitalRead(leftLine))
    {
      right();
    }
    else
    {
      Stop();
    }
  }
}// END TrackLine

float obstacle()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(12);
  digitalWrite(trigPin, LOW);
  dist = pulseIn(echoPin, HIGH);
  delayMicroseconds(10000);
  dist = dist / 58;

  //come up with a filtering, smoothening algorithm here for ultrasonic
  estimated_value = simpleKalmanFilter.updateEstimate(dist);

  //  Serial.println(estimated_value);
  return estimated_value;

}//END obstacle

void autoDrive()
{
  if (state1 == true)
  {
    servo.write(lookAhead);
    front();
    dist1 = obstacle();
    state2 =  false; state3 = false; state4 = false; state5 = false; state6 =  false;

    //for debugging
    Serial.println("looking ahead + moving forward + read dist1_______state1");
  }


  if (dist1 < thresholdDist && !state3 && !state4)
  {
    state1 = false; state2 =  true; state3 = false; state4 = false; state5 = false; state6 =  false;

    if (state2 == true && !state3 && !state4)
    {
      Stop();
      servo.write(lookLeft);
      unsigned long currentMillis2 = millis();
      reset2 = false;
      reset1 = true; reset3 = true; reset4 = true; reset5 = true; reset6 = true;
      float dist2 = 0.0;;



      //for debugging
      Serial.println ("Stop + lookLeft___________state2");

      if (currentMillis2 - prevMillis2 >= pauseInterval)
      {
        dist2 = obstacle();
        state2 = false;
        reset2 = true;

        //for debugging
        Serial.println("read left distance + leave state 2-----------------------------------------------------(dist2)" + String(dist2));

        if (dist2 > thresholdDist && !state1)
        {
          state1 = false; state2 =  false; state3 = true; state4 = false; state5 = false; state6 =  false;
        }

        if (dist2 < thresholdDist && !state5)
        {
          state1 = false; state2 =  false; state3 = false; state4 = true; state5 = false; state6 =  false;
        }
      }
    }
  }


  if (state3 == true)
  {
    servo.write(lookAhead);
    left();
    unsigned long currentMillis3 = millis();
    reset3 = false;
    reset1 = true; reset2 = true; reset4 = true; reset5 = true; reset6 = true;

    //for debugging
    Serial.println("lookAhead + move left __________state3");

    if (currentMillis3 - prevMillis3 >= pauseInterval)
    {
      state1 = true;
      state2 =  false; state3 = false; state4 = false; state5 = false; state6 =  false;
      reset1 = false; reset2 = true; reset3 = true; reset4 = true; reset5 = true; reset6 = true;

      //for debugging
      Serial.println("leave state3 and proceed to state 1");
    }
  }

  if (state4 == true)
  {
    Stop();
    servo.write(lookRight);
    unsigned long currentMillis4 = millis();
    reset4 = false;

    float dist3 = 0.0;

    //for debugging
    Serial.println("Stop + lookRight __________state4");

    if (currentMillis4 - prevMillis4 >= pauseInterval)
    {
      dist3  = obstacle();
      state4 = false;
      reset4 = true;

      //for debugging
      Serial.println("read right distance and left state 4-----------------------------------------------------(dist3)" + String(dist3));

      if (dist3 > thresholdDist && !state1)
      {
        state1 = false; state2 =  false; state3 = false; state4 = false; state5 = true; state6 =  false;
      }

      if (dist3  < thresholdDist && !state1)
      {
        state1 = false; state2 =  false; state3 = false; state4 = false; state5 = false; state6 =  true;
      }
    }
  }


  if (state5 == true)
  {
    servo.write(lookAhead);
    right();
    unsigned long currentMillis5 = millis();
    reset5 = false;

    //for debugging
    Serial.println("lookAhead + move right____________________state5");

    if (currentMillis - prevMillis5 >= pauseInterval)
    {
      state5 = false;
      reset5 = true;
      state1 = true;

      //for debugging
      Serial.println("left state 5 to state 1");
    }
  }


  if (state6 == true)
  {
    back();
    servo.write(lookAhead);
    unsigned long currentMillis6 = millis();
    reset6 = false;

    //for debugging
    Serial.println("moveBackward + lookAhead  ___________________state6");

    if (currentMillis6 - prevMillis6 >= pauseInterval)
    {
      state6 = false;
      reset6 = true;
      state2 = true;

      //for debugging
      Serial.println("left  state 6 to state 2 to scan again and see where to go");
    }
  }



  if (reset1)
    prevMillis1 = millis();

  if (reset2)
    prevMillis2 = millis();

  if (reset3)
    prevMillis3 = millis();

  if (reset4)
    prevMillis4 = millis();

  if (reset5)
    prevMillis5 = millis();

  if (reset6)
    prevMillis6 = millis();




  else
  {
    state1 = true; state2 =  false; state3 = false; state4 = false; state5 = false; state6 =  false;
    dist1 = obstacle();
    Serial.println("the else statement has happened");
  }


  //for debugging
  Serial.println("nothing happening here-----------------------------------------------------(dist1)" + String(dist1));
}//END Autodrive


void buzzer()
{
  //  unsigned long buzzerCurrentMillis = millis();
  //
  //  if (buzzerCurrentMillis - buzzerPrevMillis >= buzzerInterval)
  //  {
  //    digitalWrite(buzzerPin, LOW);
  //    buzzerPrevMillis = millis();
  //  }
  //
  //  else
  //  {
  //    digitalWrite(buzzerPin, HIGH);
  //  }

}//END Buzzer

void detectLight()
{
  int lightIntensity = analogRead(ldrPin);
  if (lightIntensity > lightThreshold)
  {
    front();

    //for debugging
    Serial.println("detected light ahead_____________________________________________________moving forward");
  }

  else {
    Stop();

    //for debugging
    Serial.println("Stopped because light is not up to threshold");
  }
}


void follower()
{
  dist = obstacle();

  //come up with a filtering, smoothening algorithm here for ultrasonic
  estimated_value = simpleKalmanFilter.updateEstimate(dist);

  if (estimated_value < 100 && estimated_value > 30) {
    //This condition is to move forward the robot when the object is in the range of 100 to 30 centimeters.
    front();
  }

  if (estimated_value < 30 && estimated_value > 20) {
    //This condition is to make the robot stable when the object is in the range of 20 to 30 centimeters.
    Stop();
  }

  if (estimated_value < 20 && estimated_value > 2) {
    //This condition is to move backward the robot when the object is in the range of 2 to 20 centimeters.
    back();
  }

  if (estimated_value > 100) {
    //This condition is to stop the robot when the object is in the out of range i.e greater than 100 centimeters.
    Stop();
  }
}// END Follower

//*********( THE END )***********