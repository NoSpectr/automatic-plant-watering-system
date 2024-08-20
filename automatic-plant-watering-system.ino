#define BLYNK_TEMPLATE_ID "TMPL66kiHzN1Z"                   // ID Template Blynk
#define BLYNK_TEMPLATE_NAME "NODEMCU"                       // Nama Template Blynk
#define BLYNK_AUTH_TOKEN "oiBE1CCufW5esOqp5YsPoACPejVX7GP8" // Blynk Auth Token

#include <ESP8266WiFi.h>        // Library untuk ESP8266 WiFi Module
#include <BlynkSimpleEsp8266.h> // Library untuk Blynk ESP8266
#include <DHT.h>                // Library untuk sensor DHT (Suhu)
#include <Wire.h>               // Library untuk I2C LCD
#include <LiquidCrystal_I2C.h>  // Library untuk I2C LCD (Liquid Crystal)

// Variabel untuk Blynk dan WiFi
char auth[] = "oiBE1CCufW5esOqp5YsPoACPejVX7GP8"; // BLYNK AUTH TOKEN
char ssid[] = "Android&";                         // nama WiFi
char pass[] = "00000000";                         // sandi WiFi

BlynkTimer timer;        // Inisialisasi timer untuk Blynk
bool relayState = false; // Status relay

// Definisi pin komponen
#define SENSOR_PIN A0     // Pin untuk Sensor Moisture (Kelembapan)
#define WATER_PUMP_PIN D1 // Pin untuk Aktuator Pompa Air
#define LDR_PIN D0        // Pin untuk sensor LDR (Cahaya)
#define DHT_PIN D5        // Pin untuk sensor DHT11 (Suhu)
#define DHT_TYPE DHT11    // Tipe sensor DHT (Suhu)

DHT dht(DHT_PIN, DHT_TYPE); // Inisialisasi sensor DHT

int moistThreshold = 50; // Ambang batas kelembapan tanah

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD, 16 kolom, 2 baris

void setup()
{
    pinMode(WATER_PUMP_PIN, OUTPUT);                  // Mengatur pin pompa air sebagai output
    digitalWrite(WATER_PUMP_PIN, HIGH);               // Mematikan pompa air
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); // Memulai koneksi Blynk
    dht.begin();                                      // Inisialisasi sensor DHT

    // Inisialisasi LCD
    Wire.begin(D3, D4); // Set Pin SDA ke D3 dan Pin SCL ke D4
    lcd.begin();        // Inisialisasi LCD
    lcd.backlight();    // Nyalakan backlight LCD

    // Mengatur interval timer
    timer.setInterval(100, soilMoistureSensor);   // Periksa kelembapan tanah setiap 1 detik
    timer.setInterval(2000L, readTemperature);    // Baca suhu setiap 2 detik
    timer.setInterval(2000L, readLightIntensity); // Baca intensitas cahaya setiap 2 detik
}

// Fungsi untuk membaca nilai kelembapan tanah
void soilMoistureSensor()
{
    int sensorValue = analogRead(SENSOR_PIN);        // Membaca nilai sensor kelembapan tanah dari pin A0
    sensorValue = map(sensorValue, 0, 1024, 0, 100); // Menyesuaikan nilai sensor kelembapan tanah
    sensorValue = 100 - sensorValue;                 // Menyesuaikan pembacaan sensor

    Blynk.virtualWrite(V0, sensorValue); // Kirim nilai kelembapan ke Blynk

    if (sensorValue >= moistThreshold) // Jika Kelembapan tanah tinggi
    {
        digitalWrite(WATER_PUMP_PIN, LOW);                                  // Matikan pompa air
        Blynk.virtualWrite(V4, "Status Tanah: Basah");                      // Tampilkan indikator basah
        Blynk.virtualWrite(V3, "Kelembapan: " + String(sensorValue) + "%"); // Kirim nilai kelembapan ke Blynk

        // Tampilkan di LCD
        lcd.clear();
        lcd.print("Pompa: Non Aktif");
        lcd.setCursor(0, 1);
        lcd.print("Kelembapan: " + String(sensorValue) + "%");
    }
    else
    {
        digitalWrite(WATER_PUMP_PIN, HIGH);                                 // Nyalakan pompa air
        Blynk.virtualWrite(V4, "Status Tanah: Kering");                     // Tampilkan indikator kering
        Blynk.virtualWrite(V3, "Kelembapan: " + String(sensorValue) + "%"); // Kirim nilai kelembapan ke Blynk

        // Tampilkan di LCD
        lcd.clear();
        lcd.print("Pompa: Aktif");
        lcd.setCursor(0, 1);
        lcd.print("Kelembapan: " + String(sensorValue) + "%");
    }
}

void readTemperature() // Fungsi untuk membaca suhu dari sensor DHT
{
    float temperature = dht.readTemperature(); // Membaca suhu dari sensor DHT
    if (!isnan(temperature))                   // Jika nilai suhu valid maka kirim ke Blynk
    {
        Blynk.virtualWrite(V2, temperature); // Kirim nilai suhu ke Blynk
    }
    else // Jika nilai suhu tidak valid maka tampilkan pesan error
    {
        Serial.println("Failed to read temperature from DHT sensor!"); // Tampilkan pesan error di Serial Monitor
    }
}

void readLightIntensity() // Fungsi untuk membaca intensitas cahaya dari sensor LDR
{
    int lightIntensity = analogRead(LDR_PIN); // Membaca nilai intensitas cahaya dari sensor LDR
    Blynk.virtualWrite(V5, lightIntensity);   // Kirim nilai intensitas cahaya ke Blynk
}

void loop()
{
    Blynk.run(); // Jalankan Blynk
    timer.run(); // Jalankan timer Blynk
}
