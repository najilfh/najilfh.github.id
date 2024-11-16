// Jumlah LED yang digunakan
const int jumlahLED = 13;

void setup() {
  // Inisialisasi setiap pin dari 2 sampai jumlahLED sebagai output
  for (int pin = 2; pin < 2 + jumlahLED; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  // Efek lambat
  runningLightSlow();
  delay(1000);
  
  // Efek sedang
  knightRiderMedium();
  delay(1000);
  
  // Efek cepat
  blinkAllFast();
  delay(1000);
  
  // Efek lambat lainnya
  waveEffectSlow();
  delay(1000);
  
  // Efek sedang lainnya
  randomTwinkleMedium();
  delay(1000);
  
  // Efek cepat lainnya
  runningBackForthFast();
  delay(1000);
}

// ==== EFEK LAMBAT ====
// Efek 1: Menyalakan LED satu per satu secara lambat
void runningLightSlow() {
  int delayTime = 500; // Kecepatan lambat
  for (int pin = 2; pin < 2 + jumlahLED; pin++) {
    digitalWrite(pin, HIGH); // Nyalakan LED
    delay(delayTime);        // Tunggu sebentar
    digitalWrite(pin, LOW);  // Matikan LED
  }
}

// Efek 2: Gelombang (wave) LED secara lambat
void waveEffectSlow() {
  int delayTime = 500; // Kecepatan lambat
  for (int i = 0; i < jumlahLED; i++) {
    for (int pin = 2; pin < 2 + jumlahLED; pin++) {
      int brightness = abs(pin - (i + 2)) * 25;  // Buat efek gelombang
      analogWrite(pin, brightness);
    }
    delay(delayTime);
  }
}

// ==== EFEK SEDANG ====
// Efek 3: Knight Rider dengan kecepatan sedang
void knightRiderMedium() {
  int delayTime = 150; // Kecepatan sedang
  for (int pin = 2; pin < 2 + jumlahLED; pin++) {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
  }
  for (int pin = 2 + jumlahLED - 1; pin >= 2; pin--) {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
  }
}

// Efek 4: Twinkle LED secara acak dengan kecepatan sedang
void randomTwinkleMedium() {
  int delayTime = 200; // Kecepatan sedang
  for (int i = 0; i < 30; i++) {  // Ulangi twinkle acak beberapa kali
    int pin = random(2, 2 + jumlahLED); // Pilih pin acak
    digitalWrite(pin, HIGH);            // Nyalakan LED acak
    delay(delayTime);
    digitalWrite(pin, LOW);             // Matikan LED
  }
}

// ==== EFEK CEPAT ====
// Efek 5: Blink semua LED secara cepat
void blinkAllFast() {
  int delayTime = 50; // Kecepatan cepat
  for (int i = 0; i < 10; i++) { // Blink 10 kali
    for (int pin = 2; pin < 2 + jumlahLED; pin++) {
      digitalWrite(pin, HIGH);  // Nyalakan semua LED
    }
    delay(delayTime);
    for (int pin = 2; pin < 2 + jumlahLED; pin++) {
      digitalWrite(pin, LOW);  // Matikan semua LED
    }
    delay(delayTime);
  }
}

// Efek 6: LED bergerak maju mundur dengan kecepatan cepat
void runningBackForthFast() {
  int delayTime = 50; // Kecepatan cepat
  for (int pin = 2; pin < 2 + jumlahLED; pin++) {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
  }
  for (int pin = 2 + jumlahLED - 1; pin >= 2; pin--) {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
  }
}
