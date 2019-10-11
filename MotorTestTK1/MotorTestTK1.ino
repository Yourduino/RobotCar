/* YourDuino Physical Computing Kit Tests
  - SEE the comments after "//" on each line below
  - CONNECTIONS:
   -
   -
  - V1.00 01/10/19
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/

/*-------------( Declare  Pin Numbers )-----------------------*/
const byte LEFT_OPTOINTERRUPTER_PIN  =    2;  // The optoInterrupters for encoder discs
const byte RIGHT_OPTOINTERRUPTER_PIN =    3;

const byte LEFT_MOTOR_DIRECTION_PIN   =  4 ; // Motor Control Pins Direction and PWM Speed
const byte LEFT_MOTOR_SPEED_PIN       =  5 ;
const byte RIGHT_MOTOR_SPEED_PIN      =  6 ;
const byte RIGHT_MOTOR_DIRECTION_PIN  =  7 ;

const byte ULTRASONIC_ECHO_PIN        = 8 ;   //ultrasonic sensor parameters
const byte ULTRASONIC_TRIGGER_PIN     = 9 ;

const byte UNUSED10_PIN               = 10 ;  // Unused
const byte SERVO_PIN                  = 11 ;
const byte UNUSED12_PIN               = 12 ;  // Unused
const byte BUZZER_PIN                 = 13 ; //meant for obstacle alert

const byte LEFT_LINE_FOLLOW           = A0 ;   // PhotoSensors in Line Follower mode
const byte MIDDLE_LINE_FOLLOW         = A1 ;
const byte RIGHT_LINE_FOLLOW          = A2 ;

const byte LIGHT_SENSOR_PIN           = A3 ;   // For Light-following mode

NOTE: Pins A4,A5 reserved for I2C communication (LCD etc.)

/*-----( Declare Constants  )-----*/
 /*-----( Declare objects )-----*/
/*-----( Declare Variables )-----*/


void setup()   /****** SETUP: RUNS ONCE ******/
{
 
    pinMode(LEFT_LINE_FOLLOW, INPUT);
    pinMode(MIDDLE_LINE_FOLLOW, INPUT);
    pinMode(RIGHT_LINE_FOLLOW, INPUT);
    pinMode(LIGHT_SENSOR_PIN, INPUT);
 
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(SERVO_PIN, OUTPUT);
    pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
    pinMode(LEFT_MOTOR_DIRECTION_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_SPEED_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_SPEED_PIN , OUTPUT);
    pinMode(RIGHT_MOTOR_DIRECTION_PIN, OUTPUT);
  
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{


}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/


//*********( THE END )***********
