#include <Servo.h> 

// Definisikan pin
const int trigPin = 9;
const int echoPin = 10;
Servo myServo;  // Buat objek servo
int servoPin = 3;  // Pin untuk servo motor

void setup() {
  // Inisialisasi pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);  // Menghubungkan servo ke pin 3
  Serial.begin(9600);  // Inisialisasi komunikasi serial
}

void loop() {
  // Mengukur jarak
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Menghitung jarak dalam cm
  
  // Tampilkan jarak di serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Menggerakkan servo berdasarkan jarak
  if (distance <= 5) {
    myServo.write(180);  // Jika objek dekat, servo bergerak ke 180 derajat
  } else {
    myServo.write(0);  // Jika objek jauh, servo bergerak ke 0 derajat
  }
  
  delay(500);  // Delay agar tidak terlalu cepat
}
