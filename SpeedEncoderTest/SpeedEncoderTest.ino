const byte LEFT_OPTOINTERRUPTER_PIN  =    2;  // The optoInterrupters for encoder discs
const byte RIGHT_OPTOINTERRUPTER_PIN =    3;

volatile unsigned int counter_left;
volatile unsigned int counter_right;


void setup() {
  Serial.begin(9600);

  pinMode(LEFT_OPTOINTERRUPTER_PIN, INPUT);
  pinMode(RIGHT_OPTOINTERRUPTER_PIN, INPUT);

  digitalWrite(LEFT_OPTOINTERRUPTER_PIN, HIGH);
  digitalWrite(RIGHT_OPTOINTERRUPTER_PIN, HIGH);

  attachInterrupt(digitalPinToInterrupt(LEFT_OPTOINTERRUPTER_PIN), countpulse_left, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_OPTOINTERRUPTER_PIN), countpulse_right, RISING);
}


void loop() {
  Serial.print("LEFT_COUNT is "  + String(counter_left) + '\n');
  Serial.println("RIGHT_COUNT is "  + String(counter_right) + '\n');
}

void countpulse_left() {
  counter_left++;
}

void countpulse_right() {
  counter_right++;
}
