// ------------------------------------------
// ESP32 Entry Counter Mini Project
// IR Sensor -> count++
// Ultrasonic Sensor -> count--
// 7-Segment Display Output
// ------------------------------------------

// ------------------------------
// PIN Configurations
// ------------------------------
#define IR_SENSOR_PIN 14

// Ultrasonic pins
#define TRIG_PIN 4
#define ECHO_PIN 16
#define SOUND_SPEED 0.034

// 7-segment display pins (common cathode)
int segPins[] = {23, 22, 21, 19, 18, 5, 17};  

// Digit patterns (0–9)
byte numbers[10][7] = {
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,1,0,1,1}  //9
};

// ------------------------------
// Global state variables
// ------------------------------
int countValue = 0;

bool irPrevious = 0;

// Ultrasonic state logic
bool objectPresent = false;
bool lockTriggered = false;
int hit = 0;
int release = 0;


// ------------------------------
// Setup
// ------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(IR_SENSOR_PIN, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // 7-segment init
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
    digitalWrite(segPins[i], LOW);
  }
}

// ------------------------------
// Ultrasonic reading
// ------------------------------
float getDist() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long dur = pulseIn(ECHO_PIN, HIGH, 30000);
  if (dur == 0) return 999;

  return dur * SOUND_SPEED / 2;
}

// ------------------------------
// 7-Segment display
// ------------------------------
void showNumber(int num) {
  num = num % 10;

  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], numbers[num][i]);
  }
}


// ------------------------------
// MAIN LOOP
// ------------------------------
void loop() {

  // ===============================================
  // 1) IR SENSOR → count++  (Entry)
  // ===============================================
  bool irState = digitalRead(IR_SENSOR_PIN);
  //Serial.println(irState);
  if (irState == 1 && irPrevious == 0) {
    countValue++;
    Serial.print("IR detected → Count: ");
    Serial.println(countValue);
    showNumber(countValue);
  }
  irPrevious = irState;



  // ===============================================
  // 2) ULTRASONIC SENSOR → count-- (Exit)
  // ===============================================
  float d = getDist();

  bool detected = (d > 2 && d < 8);   // obstacle zone
  bool released = (d > 9);            // clear zone

  if (detected) {
    hit++;
    release = 0;
  } else if (released) {
    release++;
    hit = 0;
  }

  // Confirm object arrival
  if (hit >= 3 && !objectPresent && !lockTriggered) {
    objectPresent = true;
    lockTriggered = true;

    countValue--;
    if (countValue < 0) countValue = 0;

    Serial.print("Ultrasonic detected EXIT → Count: ");
    Serial.println(countValue);

    showNumber(countValue);
    hit = 0;
  }

  // Confirm object removed
  if (objectPresent && release >= 5) {
    objectPresent = false;
    lockTriggered = false;
    release = 0;
  }


  // ===============================================
  // Smooth loop
  // ===============================================
  delay(40);
}
