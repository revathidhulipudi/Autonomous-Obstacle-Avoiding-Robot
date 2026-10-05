 ######## CODE ########
This is the code that I have used for this project.

// =====================================================
// Autonomous Obstacle Avoiding Robot
// Arduino UNO + L298N + Ultrasonic + 2 IR Sensors
// =====================================================

// ---------------- Motor Pins ----------------
const int ENA = 5;
const int IN1 = 6;
const int IN2 = 7;

const int IN3 = 8;
const int IN4 = 9;
const int ENB = 10;

// ---------------- Sensor Pins ----------------
const int IR_LEFT  = 2;
const int IR_RIGHT = 3;

const int TRIG = 11;
const int ECHO = 12;

// ---------------- Robot Parameters ----------------
const int SPEED = 180;
const int STOP_DIST = 15;    // Obstacle detection distance (cm)
const int CLEAR_DIST = 30;   // Clear path distance (cm)


// =====================================================
// IR SENSOR FUNCTIONS
// =====================================================

bool leftBlocked()
{
  return digitalRead(IR_LEFT) == LOW;
}

bool rightBlocked()
{
  return digitalRead(IR_RIGHT) == LOW;
}


// =====================================================
// ULTRASONIC DISTANCE MEASUREMENT
// =====================================================

long distanceCM()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long t = pulseIn(ECHO, HIGH, 30000UL);

  if (t == 0)
    return 999;

  return t / 58;
}


// =====================================================
// MOTOR DIRECTION CONTROL
// =====================================================

void motorL(bool forwardDirection)
{
  digitalWrite(IN1, forwardDirection);
  digitalWrite(IN2, !forwardDirection);
}

void motorR(bool forwardDirection)
{
  digitalWrite(IN3, forwardDirection);
  digitalWrite(IN4, !forwardDirection);
}


// =====================================================
// ROBOT MOVEMENT FUNCTIONS
// =====================================================

void forward()
{
  motorL(true);
  motorR(true);

  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void backward()
{
  motorL(false);
  motorR(false);

  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void spinLeft()
{
  motorL(false);
  motorR(true);

  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void spinRight()
{
  motorL(true);
  motorR(false);

  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void stopCar()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


// =====================================================
// TURN UNTIL PATH IS CLEAR
// =====================================================

void turnUntilClear(bool toLeft)
{
  unsigned long startTime = millis();

  // Safety timeout to prevent continuous rotation
  while (millis() - startTime < 5000)
  {
    if (toLeft)
      spinLeft();
    else
      spinRight();

    if (distanceCM() > CLEAR_DIST)
    {
      delay(200);
      break;
    }
  }

  stopCar();
}


// =====================================================
// SENSOR-BASED TURN DECISION
// =====================================================

void lookAndTurn()
{
  bool L = leftBlocked();
  bool R = rightBlocked();

  // Left side open, right side blocked
  if (!L && R)
  {
    turnUntilClear(true);
  }

  // Left side blocked, right side open
  else if (L && !R)
  {
    turnUntilClear(false);
  }

  // Both sides open
  else if (!L && !R)
  {
    turnUntilClear(true);
  }

  // Both sides blocked
  else
  {
    backward();
    delay(500);

    stopCar();
    delay(100);

    // Approximate U-turn
    spinRight();
    delay(800);

    stopCar();
  }
}


// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(9600);

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Ultrasonic sensor
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // IR sensors
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  // Keep motors stopped at startup
  stopCar();

  delay(2000);
}


// =====================================================
// MAIN LOOP
// =====================================================

void loop()
{
  // Check front distance
  if (distanceCM() > STOP_DIST)
  {
    forward();
  }
  else
  {
    // Obstacle detected
    stopCar();
    delay(250);

    // Decide where to turn
    lookAndTurn();
  }

  delay(50);
}
