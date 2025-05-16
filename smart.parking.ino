#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Objek LCD dan Servo
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoMasuk;
Servo servoKeluar;

// Pin Sensor
const int trigMasuk = 2;
const int echoMasuk = 3;
const int trigKeluar = 4;
const int echoKeluar = 5;

// Pin Servo
const int pinServoMasuk = 6;
const int pinServoKeluar = 7;

// Kapasitas dan status kendaraan
const int kapasitas = 4;
int kendaraan = 0;

// Jarak batas deteksi
const int batasJarak = 10;

void setup() {
  // Inisialisasi pin
  pinMode(trigMasuk, OUTPUT);
  pinMode(echoMasuk, INPUT);
  pinMode(trigKeluar, OUTPUT);
  pinMode(echoKeluar, INPUT);

  // Inisialisasi servo
  servoMasuk.attach(pinServoMasuk);
  servoKeluar.attach(pinServoKeluar);
  servoMasuk.write(0);   // posisi awal tertutup
  servoKeluar.write(0);  // posisi awal tertutup

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  SMART PARKING  ");
  lcd.setCursor(0, 1);
  lcd.print("     UNIBA      ");
  delay(5000);
  updateLCD();
}

void loop() {
  float jarakMasuk = bacaJarak(trigMasuk, echoMasuk);
  float jarakKeluar = bacaJarak(trigKeluar, echoKeluar);

  // Deteksi mobil keluar
  if (jarakKeluar < batasJarak && kendaraan > 0) {
    bukaPintu(servoKeluar);
    kendaraan--;
    updateLCD();
    delay(3000); // beri waktu mobil keluar
  }

  // Deteksi mobil masuk
  if (jarakMasuk < batasJarak) {
    if (kendaraan < kapasitas) {
      bukaPintu(servoMasuk);
      kendaraan++;
      updateLCD();
    } else {
      tampilSlotPenuh();   // tampilkan pesan tapi tidak buka pintu
    }
    delay(3000); // beri waktu mobil lewat
  }
}

// Fungsi membaca jarak ultrasonik
float bacaJarak(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long durasi = pulseIn(echo, HIGH, 10000); // timeout 30ms
  if (durasi == 0) return 1000.0;            // tidak ada pantulan
  return durasi * 0.034 / 2;
}

// Fungsi membuka dan menutup pintu otomatis
void bukaPintu(Servo &servo) {
  servo.write(90);  // buka
  delay(3000);
  servo.write(0);   // tutup kembali
}

// Fungsi update LCD status slot
void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Slot tersedia: ");
  lcd.setCursor(0, 1);
  lcd.setCursor(5, 1);
  lcd.print(kapasitas - kendaraan);
}

// Fungsi tampilan jika penuh
void tampilSlotPenuh() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Slot Penuh   ");
  lcd.setCursor(0, 1);
  lcd.print(" Tunggu keluar.. ");
}
