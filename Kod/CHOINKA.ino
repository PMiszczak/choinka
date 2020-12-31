#include <Arduino.h> // Biblioteka wymagana do poprawnego działania innych bibliotek
#include <ESP8266WiFi.h> // Biblioteka wymagana do podłączenia NodeMCU do Wi-Fi

#include <Adafruit_NeoPixel.h> // Biblioteka potrzebna dla WS2812B (ledy)

#include "fauxmoESP.h" // Biblioteka pozwalająca na podszycie się za Philips Hue
#include "dane.h" // SSID oraz hasło naszego Wi-Fi

// Zmienne

int LED_STATE = 0;

// Stałe

#define SERIAL_CZESTOTLIWOSC 115200

#define ID_CHOINKA "Christmas lights"

// Zainicjowanie bibliotek

fauxmoESP CHOINKA;
Adafruit_NeoPixel SWIATELKA(LED_ILOSC, LED_DANE, NEO_GRB + NEO_KHZ400);

void setup() {

  // Włączenie WS2812B, ustawienie jasności na 100%, wyczyszczenie możliwych artefaktów

  SWIATELKA.begin();
  SWIATELKA.setBrightness(255);
  SWIATELKA.clear();

  LED_CZYSC();

  // Rozpoczęcie komunikacji po porcie szeregowym

  Serial.begin(SERIAL_CZESTOTLIWOSC);

  // Ustawienie pinu dla WS2812B jako wyjście

  pinMode(LED_DANE, OUTPUT);

  MONITOR_CZYSC();
  WIFI_LACZENIE();

  // Inicjalizacja komunikacji biblioteki "fauxmoESP.h" z Alexą

  CHOINKA.createServer(true);
  CHOINKA.setPort(80);

  CHOINKA.enable(true);

  CHOINKA.addDevice(ID_CHOINKA);

  // Przy zmianie stanu obiektu CHOINKA (włączenie, wyłączenie, zmiana jasności przy pomocy Alexy)

  CHOINKA.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {

    // Wyświetlanie statusu obiektu CHOINKA w monitorze portu szeregowego

    Serial.printf("CHOINKA #%d (%s) status: %s wartosc: %d\n", device_id, device_name, state ? "WLACZONE" : "WYLACZONE", value);

    if (strcmp(device_name, ID_CHOINKA) == 0) {

      // Jeśli obiekt CHOINKA jest włączony i jego zakres to 100% - 90%

      if ((state ? HIGH : LOW == "HIGH") && (value >= 230)) {
        LED_STATE = 1;
      }
      else if ((!state) && (value >= 230)) {
        LED_STATE = 0;
        value = 0;
      }

      // Jeśli obiekt CHOINKA jest włączony i jego zakres to 90% - 80%

      else if ((state ? HIGH : LOW == "HIGH") && (value >= 205) && (value <= 229)) {
        LED_STATE = 2;
      }
      else if ((!state) && (value >= 205) && (value <= 229)) {
        LED_STATE = 0;
        value = 0;
      }

      // Jeśli obiekt CHOINKA jest włączony i jego zakres to 80% - 70%

      else if ((state ? HIGH : LOW == "HIGH") && (value >= 180) && (value <= 204)) {
        LED_STATE = 3;
      }
      else if ((!state) && (value >= 180) && (value <= 204)) {
        LED_STATE = 0;
        value = 0;
      }

      // Jeśli obiekt CHOINKA jest włączony i jego zakres to 70% - 60%

      else if ((state ? HIGH : LOW == "HIGH") && (value >= 155) && (value <= 179)) {
        LED_STATE = 4;
      }
      else if ((!state) && (value >= 155) && (value <= 179)) {
        LED_STATE = 0;
        value = 0;
      }

      // Jeśli obiekt CHOINKA jest włączony i jego zakres to 60% - 50%

      else if ((state ? HIGH : LOW == "HIGH") && (value >= 130) && (value <= 154)) {
        LED_STATE = 5;
      }
      else if ((!state) && (value >= 130) && (value <= 154)) {
        LED_STATE = 0;
        value = 0;
      }

      // Jeśli obiekt CHOINKA jest włączony i jego zakres to 50% - 40%

      else if ((state ? HIGH : LOW == "HIGH") && (value >= 104) && (value <= 129)) {
        LED_STATE = 6;
      }
      else if ((!state) && (value >= 104) && (value <= 129)) {
        LED_STATE = 0;
        value = 0;
      }

      // Jeśli obiekt CHOINKA jest włączony i jego zakres to 40% - 30%

      else if ((state ? HIGH : LOW == "HIGH") && (value >= 79) && (value <= 103)) {
        LED_STATE = 7;
      }
      else if ((!state) && (value >= 79) && (value <= 103)) {
        LED_STATE = 0;
        value = 0;
      }

      // Jeśli obiekt CHOINKA jest włączony i jego zakres to 30% - 20%

      else if ((state ? HIGH : LOW == "HIGH") && (value >= 53) && (value <= 78)) {
        LED_STATE = 8;
      }
      else if ((!state) && (value >= 53) && (value <= 78)) {
        LED_STATE = 0;
        value = 0;
      }

      // Jeśli obiekt CHOINKA jest włączony i jego zakres to 20% - 10%

      else if ((state ? HIGH : LOW == "HIGH") && (value >= 28) && (value <= 52)) {
        LED_STATE = 9;
      }
      else if ((!state) && (value >= 28) && (value <= 52)) {
        LED_STATE = 0;
        value = 0;
      }

      // Jeśli obiekt CHOINKA jest włączony i jego zakres to 10% - 0%

      else if ((state ? HIGH : LOW == "HIGH") && (value <= 27)) {
        LED_STATE = 10;
      }
      else if ((!state) && (value <= 27)) {
        LED_STATE = 0;
        value = 0;
      }

      else {
        ;;
      }
    }

  });
}

void loop() {

  // Obsługa obiektu CHOINKA

  CHOINKA.handle();

  // Poszczególne animacje ze względu na zakres obiektu CHOINKA

  switch (LED_STATE) {

    case 1:
      {
        KOLOR(100, 255, 0, 0);
        delay(10);
      }
      break;

    case 2:
      {
        KOLOR(100, 0, 255, 0);
        delay(10);
      }
      break;

    case 3:
      {
        KOLOR(100, 0, 0, 255);
        delay(10);
      }
      break;

    case 4:
      {
        MRUGANIE(1000, 255, 255, 0);
        delay(10);
      }
      break;

    case 5:
      {
        POSYPKA(10, 50, 0, 255, 255);
        delay(10);
      }
      break;

    case 6:
      {
        TECZA(30);
        delay(10);
      }
      break;

    case 7:
      {
        KOLOR_DWA(100, 45, 200, 230, 230, 45, 170);
        delay(10);
      }
      break;

    case 8:
      {
        KOLOR_TRZY(100, 230, 45, 45, 145, 230, 45, 230, 160, 45);
      }
      break;

    case 9:
      {
        MULTI_KOLOR(100);
      }
      break;

    case 10:
      {
        LED_CZYSC();
      }
      break;

    default:
      {
        LED_CZYSC();
      }
      break;
  }
}

// Funkcja służąca do łączenia się z Wi-Fi podanym w pliku "dane.h"

void WIFI_LACZENIE() {
  WiFi.mode(WIFI_STA);

  Serial.printf("[Wi-Fi] LACZE SIE Z %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println();

  Serial.printf("[Wi-Fi] POLACZONO!, SSID: %s, Adres IP: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

}

// Funkcja służąca do wyłączania i pierwotnego ustawiania WS2812B

void LED_CZYSC() {
  uint8_t i;
  for (i = 0; i < LED_ILOSC; i++) {
    SWIATELKA.setPixelColor(i, SWIATELKA.Color(0, 0, 0));
    SWIATELKA.show();
    delay(50);
  }
  SWIATELKA.clear();
  SWIATELKA.setBrightness(255);
}

// Funkcja służąca do pozbycia się niepotrzebnego tekstu w monitorze portu szeregowego

void MONITOR_CZYSC() {
  uint8_t i;
  for (i = 0; i < 100; i++) {
    Serial.print("\n");
  }
}

// Funkcja służąca do ustawiania WS2812B na poszczególny kolor

void KOLOR(uint8_t CZAS, uint8_t R, uint8_t G, uint8_t B) {
  uint16_t i;

  for (i = 0; i < LED_ILOSC; i++) {
    SWIATELKA.setPixelColor(i, SWIATELKA.Color(R, G, B));
    SWIATELKA.show();
    delay(CZAS);
  }

  delay(5 * CZAS);

  for (i = LED_ILOSC; i > 0; --i) {
    SWIATELKA.setPixelColor(i, SWIATELKA.Color(0, 0, 0));
    SWIATELKA.show();
    delay(CZAS);
  }
}

// Funkcja służąca do tworzenia efektu mrugania poszczególnym kolorem na WS2812B

void MRUGANIE(uint8_t CZAS, uint8_t R, uint8_t G, uint8_t B) {
  uint16_t i;

  for (i = 0; i < LED_ILOSC; i++) {
    SWIATELKA.setPixelColor(i, SWIATELKA.Color(R, G, B));
    SWIATELKA.show();
  }

  delay(CZAS);

  for (i = LED_ILOSC; i > 0; --i) {
    SWIATELKA.setPixelColor(i, SWIATELKA.Color(0, 0, 0));
    SWIATELKA.show();
  }
}

// Funkcja służąca do tworzenia efektu posypki poszczególnym kolorem na WS2812B

void POSYPKA(uint8_t CZAS, uint8_t ILOSC, uint8_t R, uint8_t G, uint8_t B) {
  uint16_t i;

  for (i = 0; i < ILOSC; i++) {
    uint16_t LOS = random(0, LED_ILOSC);
    SWIATELKA.setPixelColor(LOS, SWIATELKA.Color(R, G, B));
  }

  for (i = 1; i < 255; i++) {
    SWIATELKA.setBrightness(i);
    SWIATELKA.show();
    delay(CZAS / 5);
  }

  delay(CZAS);

  for (i = 255; i > 0; --i) {
    SWIATELKA.setBrightness(i);
    SWIATELKA.show();
    delay(CZAS / 5);
  }

  for (i = LED_ILOSC; i > 0; --i) {
    SWIATELKA.setPixelColor(i, SWIATELKA.Color(0, 0, 0));
    SWIATELKA.show();
  }
}

// Funkcja służąca do tworzenia efektu tęczy na WS2812B

void TECZA(uint8_t CZAS) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < LED_ILOSC; i++) {
      SWIATELKA.setPixelColor(i, KOLO((i * 1 + j) & 255));
    }
    SWIATELKA.show();
    delay(CZAS);
  }
}

// Funkcja służąca do poprawnego działania funkcji "TECZA"

uint32_t KOLO(byte KOLO_POZYCJA) {
  if (KOLO_POZYCJA < 85) {
    return SWIATELKA.Color(KOLO_POZYCJA * 3, 255 - KOLO_POZYCJA * 3, 0);
  }
  else if (KOLO_POZYCJA < 170) {
    KOLO_POZYCJA -= 85;
    return SWIATELKA.Color(255 - KOLO_POZYCJA * 3, 0, KOLO_POZYCJA * 3);
  }
  else {
    KOLO_POZYCJA -= 170;
    return SWIATELKA.Color(0, KOLO_POZYCJA * 3, 255 - KOLO_POZYCJA * 3);
  }
}

// Funkcja służąca do ustawiania WS2812B na poszczególne dwa kolory

void KOLOR_DWA(uint8_t CZAS, uint8_t R, uint8_t G, uint8_t B, uint8_t RR, uint8_t GG, uint8_t BB) {
  uint16_t i;

  for (i = 0; i < LED_ILOSC; i++) {
    if (i % 2 == 0) {
      SWIATELKA.setPixelColor(i, SWIATELKA.Color(R, G, B));
    }
    else {
      SWIATELKA.setPixelColor(i, SWIATELKA.Color(RR, GG, BB));
    }
    SWIATELKA.show();
    delay(CZAS);
  }

  delay(5 * CZAS);

  for (i = LED_ILOSC; i > 0; --i) {
    SWIATELKA.setPixelColor(i, SWIATELKA.Color(0, 0, 0));
    SWIATELKA.show();
    delay(CZAS);
  }
}

// Funkcja służąca do ustawiania WS2812B na poszczególne trzy kolory

void KOLOR_TRZY(uint8_t CZAS, uint8_t R, uint8_t G, uint8_t B, uint8_t RR, uint8_t GG, uint8_t BB, uint8_t RRR, uint8_t GGG, uint8_t BBB) {
  uint16_t i;
  uint16_t j = 0;


  for (i = 0; i < LED_ILOSC; i++) {

    if (j == 0) {
      SWIATELKA.setPixelColor(i, SWIATELKA.Color(R, G, B));
      j++;
    } else if (j == 1) {
      SWIATELKA.setPixelColor(i, SWIATELKA.Color(RR, GG, BB));
      j++;
    } else {
      SWIATELKA.setPixelColor(i, SWIATELKA.Color(RRR, GGG, BBB));
      j = 0;
    }

    SWIATELKA.show();
    delay(CZAS);
  }

  delay(5 * CZAS);

  for (i = LED_ILOSC; i > 0; --i) {
    SWIATELKA.setPixelColor(i, SWIATELKA.Color(0, 0, 0));
    SWIATELKA.show();
    delay(CZAS);
  }
}

// Funkcja służąca do ustawiania WS2812B na poszczególne losowe kolory

void MULTI_KOLOR(uint8_t CZAS) {
  uint16_t i;

  for (i = 0; i < LED_ILOSC; i++) {
    uint16_t LOS = random(0, 255);
    uint16_t LOS2 = random(0, 255);
    uint16_t LOS3 = random(0, 255);

    SWIATELKA.setPixelColor(i, SWIATELKA.Color(LOS, LOS2, LOS3));
    SWIATELKA.show();
    delay(CZAS);
  }

  delay(5 * CZAS);

  for (i = LED_ILOSC; i > 0; --i) {
    SWIATELKA.setPixelColor(i, SWIATELKA.Color(0, 0, 0));
    SWIATELKA.show();
    delay(CZAS);
  }
}
