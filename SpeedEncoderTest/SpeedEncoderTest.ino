#define DIRECTION_FORWARD 0  // For use with motor controls
#define DIRECTION_REVERSE 1

/*-----( Declare objects )-----*/
/*-----( Declare Variables )-----*/
int leftMotorDirection  = 0;  // Forward zero power
int leftMotorPower      = 0;

int rightMotorDirection = 0;
int rightMotorPower     = 0;

const byte LEFT_MOTOR_DIRECTION_PIN   =  4 ; // Motor Control Pins Direction and PWM Speed
const byte LEFT_MOTOR_POWER_PIN       =  5 ;
const byte RIGHT_MOTOR_POWER_PIN      =  6 ;
const byte RIGHT_MOTOR_DIRECTION_PIN  =  7 ;


const byte LEFT_OPTOINTERRUPTER_PIN  =    2;  // The optoInterrupters for encoder discs
const byte RIGHT_OPTOINTERRUPTER_PIN =    3;

volatile unsigned int counter_left;
volatile unsigned int counter_right;


<<<<<<< HEAD
=======
/*--------------------(flags for different motor speeds)---------------*/
bool slowSpeed = false, mediumSpeed = false, fastSpeed = false;

>>>>>>> 8c27693e2bd108bc5bbce4fac48a75b53dae26b8
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


void setup() {
  Serial.begin(9600);

  pinMode(LEFT_OPTOINTERRUPTER_PIN, INPUT);
  pinMode(RIGHT_OPTOINTERRUPTER_PIN, INPUT);

  pinMode(LEFT_MOTOR_DIRECTION_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_POWER_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_POWER_PIN , OUTPUT);
  pinMode(RIGHT_MOTOR_DIRECTION_PIN, OUTPUT);

  digitalWrite(LEFT_OPTOINTERRUPTER_PIN, HIGH);
  digitalWrite(RIGHT_OPTOINTERRUPTER_PIN, HIGH);

  attachInterrupt(digitalPinToInterrupt(LEFT_OPTOINTERRUPTER_PIN), countpulse_left, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_OPTOINTERRUPTER_PIN), countpulse_right, RISING);
}


void loop() {

  if (Serial.available())
  {
    val = Serial.read();
    switch (val)
    {

      case 'M':
        manMode = true;
        lineMode = false;
        autoMode = false;
        followMode = false;
        lightMode = false;
        break;

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

<<<<<<< HEAD
=======
      case 'X':
        slowSpeed = true, mediumSpeed = false, fastSpeed = false;
        break;

      case 'Y':
        slowSpeed = false, mediumSpeed = true, fastSpeed = false;
        break;

      case 'Z':
        slowSpeed = false, mediumSpeed = false, fastSpeed = true;
        break;

>>>>>>> 8c27693e2bd108bc5bbce4fac48a75b53dae26b8
      default:
        StopMode = true;
        frontMode = false;
        backMode = false;
        leftMode = false;
        rightMode = false;
        lightMode = false;
        break;
    } // END Switch
  }// END If Serial Available

  if (manMode)
  {
    if (StopMode) {
<<<<<<< HEAD
      stopLeftMotor();
      stopRightMotor();
    }

    if (frontMode) {
      runLeftMotor(DIRECTION_FORWARD, 100);
      runRightMotor(DIRECTION_FORWARD, 100);
    }

    if (backMode) {
      runLeftMotor(DIRECTION_REVERSE, 100);
      runRightMotor(DIRECTION_REVERSE, 100);
    }

    if (leftMode) {
      runLeftMotor(DIRECTION_REVERSE, 100);
      runRightMotor(DIRECTION_FORWARD, 100);
    }

    if (rightMode) {
      runLeftMotor(DIRECTION_FORWARD, 100);
      runRightMotor(DIRECTION_REVERSE, 100);
=======
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
>>>>>>> 8c27693e2bd108bc5bbce4fac48a75b53dae26b8
    }
  }// END If ManMode


  Serial.print("LEFT_COUNT is "  + String(counter_left) + '\n');
  Serial.println("RIGHT_COUNT is "  + String(counter_right) + '\n');


}

/*-----( Declare User-written Functions )-----*/

void runLeftMotor(int LMdirection, int LMpower)
{
  leftMotorDirection  = LMdirection ;
  leftMotorPower      = LMpower ;

  if (leftMotorDirection == DIRECTION_FORWARD)
  {
    digitalWrite(LEFT_MOTOR_DIRECTION_PIN, HIGH);
    analogWrite(LEFT_MOTOR_POWER_PIN, (255 - leftMotorPower));
  }
  else
  {
    digitalWrite(LEFT_MOTOR_DIRECTION_PIN, LOW);
    analogWrite(LEFT_MOTOR_POWER_PIN,  leftMotorPower );
  }
}
//END RunLeftMotor

void stopLeftMotor()
{
  digitalWrite(LEFT_MOTOR_DIRECTION_PIN, LOW);
  analogWrite(LEFT_MOTOR_POWER_PIN, 0);
}
//END stopLeftMotor


void runRightMotor(int RMdirection, int RMpower)
{
  rightMotorDirection  = RMdirection ;
  rightMotorPower      = RMpower ;

  if (rightMotorDirection == DIRECTION_FORWARD)
  {
    digitalWrite(RIGHT_MOTOR_DIRECTION_PIN, HIGH);
    analogWrite(RIGHT_MOTOR_POWER_PIN, (255 - rightMotorPower));
  }
  else
  {
    digitalWrite(RIGHT_MOTOR_DIRECTION_PIN, LOW);
    analogWrite(RIGHT_MOTOR_POWER_PIN,  rightMotorPower );
  }
}
//END RunrightMotor

void stopRightMotor()
{
  digitalWrite(RIGHT_MOTOR_DIRECTION_PIN, LOW);
  analogWrite(RIGHT_MOTOR_POWER_PIN, 0);
}
//END stoprightMotor

void countpulse_left() {
  counter_left++;
}

void countpulse_right() {
  counter_right++;
}
