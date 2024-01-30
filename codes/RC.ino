#include <Servo.h>

const int motorAPin1 = 11; // N1 pin
const int motorAPin2 = 10; // N2 pin
const int motorBPin1 = 9;  // N3 pin
const int motorBPin2 = 8;  // N4 pin
const int enableAPin = 6;  // ENA pin
const int enableBPin = 5;  // ENB pin
const int servoPin = 3;
Servo myservo;

int currentGear = 1;
int pwmValue = 0; 

void setup() {
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableAPin, OUTPUT);
  pinMode(enableBPin, OUTPUT);
  
  myservo.attach(servoPin);

  Serial.begin(9600);
  Serial.println("Arac Hareket Etme ve Vites Durumu Kontrolu (PWM)");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'w':
        moveForward();
        break;
      case 's':
        moveBackward();
        break;
      case 'a': 
        turnLeft();
        break;
      case 'd':
        turnRight();
        break;
      case 'c':
        stopMotors();
        break;
      case 'z':
        applyBrake();
        break;
      case 'y':
        increaseGear();
        break;
      case 'u':
        decreaseGear();
        break;
    }
  }
}

void moveForward() {
  applyPower();
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
  analogWrite(enableAPin, pwmValue);
  analogWrite(enableBPin, pwmValue);
  Serial.println("İleri Hareket Ediliyor");
  printGearInfo();
}

void moveBackward() {
  applyPower();
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(enableAPin, pwmValue);
  analogWrite(enableBPin, pwmValue);
  Serial.println("Geri Hareket Ediliyor");
  printGearInfo();
}

void turnLeft() {
  applyPower();
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
  analogWrite(enableAPin, pwmValue);
  analogWrite(enableBPin, pwmValue);
  Serial.println("Sola Dönülüyor");
  printGearInfo();
}

void turnRight() {
  applyPower();
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(enableAPin, pwmValue);
  analogWrite(enableBPin, pwmValue);
  Serial.println("Sağa Dönülüyor");
  printGearInfo();
}

void stopMotors() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
  analogWrite(enableAPin, 0);
  analogWrite(enableBPin, 0);
  Serial.println("Araç Durdu");
  printGearInfo();
}

void applyBrake() {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(enableAPin, 0);
  analogWrite(enableBPin, 0);
  Serial.println("Fren Yapılıyor");
  printGearInfo();
}

void increaseGear() {
  if (currentGear < 5) { 
    currentGear++;
    calculatePower();
    Serial.print("Vites Arttırıldı: ");
    Serial.println(currentGear);
    printGearInfo();
  }
}

void decreaseGear() {
  if (currentGear > 1) {
    currentGear--;
    calculatePower();
    Serial.print("Vites Düşürüldü: ");
    Serial.println(currentGear);
    printGearInfo();
  }
}

void calculatePower() {
  pwmValue = currentGear * 50;
}

void applyPower() {
  analogWrite(enableAPin, pwmValue);
  analogWrite(enableBPin, pwmValue);
}

void printGearInfo() {
  Serial.print("Şu anki Vites: ");
  Serial.println(currentGear);
  Serial.print("PWM Değeri: ");
  Serial.println(pwmValue);
  Serial.println("-------------");
}
