const byte MA_dir = 4;  // Motor Control Pins Direction and PWM Speed
const byte MB_dir = 7;
const byte MA_spd = 5;
const byte MB_spd = 6;

void setup()   /**************************** SETUP: RUNS ONCE *******************/
{
  pinMode(MA_dir, OUTPUT);
  pinMode(MB_dir, OUTPUT);
  pinMode(MA_spd, OUTPUT);
  pinMode(MB_spd, OUTPUT);

}//--(end setup )---

void loop()   /******************** LOOP: RUNS CONSTANTLY *******************/
{
	front();
}

void front()
{
  digitalWrite(MA_dir, HIGH);
  digitalWrite(MB_dir, HIGH);
  analogWrite(MA_spd, 80);
  analogWrite(MB_spd, 80);
}
