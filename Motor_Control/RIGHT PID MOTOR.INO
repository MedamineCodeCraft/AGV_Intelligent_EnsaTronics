#include <AFMotor.h>

// ====== MOTEUR DROIT M2 ======
AF_DCMotor motorRight(2);

// ====== ENCODEUR ======
volatile long ticksRight = 0;

// ====== PID ======
float Kp = 1.5;
float Ki = 0.2;
float Kd = 0.0;

float setpoint = 0;
float speedRight = 0;

float error = 0;
float integral = 0;
float derivative = 0;
float prevError = 0;

long prevTicksRight = 0;

unsigned long lastTime = 0;
const float dt = 0.1;   // 100 ms

bool pidMode = false;

// ====== INTERRUPTION ENCODEUR ======
void ISR_right() {
  ticksRight++;
}

void setup() {

  Serial.begin(9600);

  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), ISR_right, RISING);

  motorRight.setSpeed(0);
  motorRight.run(FORWARD);

  Serial.println("=== CONTROLE MOTEUR DROIT ===");
  Serial.println("Entrez:");
  Serial.println("0-255  -> Mode simple");
  Serial.println("1000-1255 -> Mode PID (ex: 1150 = PID 150)");
  Serial.println("0 pour arret");
}

void loop() {

  // ====== LECTURE SERIAL ======
  if (Serial.available()) {

    int value = Serial.parseInt();

    if (value >= 0 && value <= 255) {
      // ----- MODE SIMPLE -----
      pidMode = false;
      setpoint = value;

      motorRight.run(FORWARD);
      motorRight.setSpeed(setpoint);

      Serial.print("Mode SIMPLE | PWM = ");
      Serial.println(setpoint);
    }

    else if (value >= 1000 && value <= 1255) {
      // ----- MODE PID -----
      pidMode = true;
      setpoint = value - 1000;

      Serial.print("Mode PID | Consigne = ");
      Serial.println(setpoint);
    }
  }

  // ====== BOUCLE PID ======
  if (pidMode && millis() - lastTime >= 100) {

    long deltaTicks = ticksRight - prevTicksRight;
    speedRight = deltaTicks / dt;

    prevTicksRight = ticksRight;
    lastTime = millis();

    error = setpoint - speedRight;
    integral += error * dt;
    derivative = (error - prevError) / dt;

    float outputPWM = Kp * error + Ki * integral + Kd * derivative;

    prevError = error;

    outputPWM = constrain(outputPWM, 0, 255);

    motorRight.run(FORWARD);
    motorRight.setSpeed(outputPWM);

    Serial.print("Consigne: ");
    Serial.print(setpoint);
    Serial.print(" | Vitesse: ");
    Serial.println(speedRight);
  }
}