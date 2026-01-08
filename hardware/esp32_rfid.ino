#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// ---------------- WIFI ----------------
const char* ssid = "shri";
const char* password = "12345678";

// 🔴 CHANGE TO YOUR PC IP
const char* serverURL = "http://192.168.1.100:5000/api/trolley/event";

// ---------------- RFID ----------------
#define SS_PIN  5
#define RST_PIN 11
MFRC522 rfid(SS_PIN, RST_PIN);

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- BUZZER ----------------
#define BUZZER_PIN 6

// ---------------- ADMIN CARD ----------------
byte accessCard[4] = {0x73, 0x96, 0x27, 0x0E};

// ---------------- PRODUCT TAGS ----------------
byte product1[4] = {0xDA, 0x23, 0x90, 0x04};
byte product2[4] = {0xC0, 0x2D, 0xCD, 0xCF};
byte product3[4] = {0x45, 0x3F, 0xB2, 0xCF};
byte product4[4] = {0x41, 0x4D, 0x90, 0x04};

String productName[4] = {"Dairy Milk", "Lays Chips", "Notebook", "Juice Bottle"};
int productPrice[4] = {40, 20, 30, 50};
bool productAdded[4] = {false, false, false, false};

// ---------------- KEYPAD ----------------
const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13,14,15,16};
byte colPins[COLS] = {7,8,9,10};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------------- VARIABLES ----------------
bool accessGranted = false;
String correctPassword = "1234";
int totalAmount = 0;

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  lcd.init();
  lcd.backlight();
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.print("Connecting WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    lcd.print(".");
  }

  lcd.clear();
  lcd.print("Smart Trolley");
  lcd.setCursor(0,1);
  lcd.print("Scan Admin Card");
}

// ---------------- LOOP ----------------
void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;
  byte *uid = rfid.uid.uidByte;

  // -------- ADMIN CARD --------
  if (compareTag(uid, accessCard)) {
    if (!accessGranted) {
      lcd.clear();
      lcd.print("Enter Password");
      if (getPassword()) {
        accessGranted = true;
        lcd.clear();
        lcd.print("Unlocked");
        sendToServer("ADMIN", 0, "TROLLEY_UNLOCKED");
      } else {
        lcd.clear();
        lcd.print("Access Denied");
      }
      delay(1500);
      lcd.clear();
      lcd.print("Scan Products");
    } else {
      lcd.clear();
      lcd.print("Checkout Done");
      sendToServer("ADMIN", 0, "TROLLEY_LOCKED");
      delay(1500);
      resetTrolley();
    }
    rfid.PICC_HaltA();
    return;
  }

  // -------- PRODUCT CARD --------
  if (accessGranted) handleProduct(uid);

  rfid.PICC_HaltA();
}

// ---------------- FUNCTIONS ----------------

bool compareTag(byte *a, byte *b) {
  for (int i=0;i<4;i++) if (a[i]!=b[i]) return false;
  return true;
}

void handleProduct(byte *uid) {
  int index = -1;
  if (compareTag(uid, product1)) index = 0;
  else if (compareTag(uid, product2)) index = 1;
  else if (compareTag(uid, product3)) index = 2;
  else if (compareTag(uid, product4)) index = 3;

  if (index == -1) return;

  if (productAdded[index]) {
    productAdded[index] = false;
    totalAmount -= productPrice[index];
    lcd.clear();
    lcd.print("Removed:");
    lcd.setCursor(0,1);
    lcd.print(productName[index]);
    sendToServer(productName[index], productPrice[index], "REMOVED");
  } else {
    productAdded[index] = true;
    totalAmount += productPrice[index];
    lcd.clear();
    lcd.print("Added:");
    lcd.setCursor(0,1);
    lcd.print(productName[index]);
    sendToServer(productName[index], productPrice[index], "ADDED");
  }
  delay(1200);
  showTotal();
}

void showTotal() {
  lcd.clear();
  lcd.print("Total: Rs ");
  lcd.print(totalAmount);
  delay(1200);
  lcd.clear();
  lcd.print("Scan Products");
}

bool getPassword() {
  String input = "";
  while (true) {
    char key = keypad.getKey();
    if (key) {
      if (key == '#') break;
      input += key;
      lcd.setCursor(input.length()-1,1);
      lcd.print("*");
    }
  }
  return input == correctPassword;
}

void resetTrolley() {
  for (int i=0;i<4;i++) productAdded[i]=false;
  totalAmount = 0;
  accessGranted = false;
  lcd.clear();
  lcd.print("Scan Admin Card");
}

// ---------------- SEND TO MERN ----------------
void sendToServer(String name, int price, String eventType){
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  http.begin(serverURL);
  http.addHeader("Content-Type", "application/json");

  String json = "{";
  json += "\"product\":\""+name+"\",";
  json += "\"price\":"+String(price)+",";
  json += "\"event\":\""+eventType+"\",";
  json += "\"total\":"+String(totalAmount);
  json += "}";

  http.POST(json);
  http.end();
}
