/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    bool d;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("Bool: ");
  Serial.println(myData.d);
  Serial.println();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);


  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("LED OFF"); // Initial status

  display.display(); 

  pinMode(15, OUTPUT);  // Pin 2 ist ein Ausgang
  pinMode(4, OUTPUT);  // Pin 4 ist ein Ausgang
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {


  if (myData.d == false)
{ 
  digitalWrite(15, HIGH);    // schaltet die LED an Pin 2 an (Rote LED)
  digitalWrite(4, HIGH);     // schaltet die LED an Pin 4 aus (Grüne LED)
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("LED RED ON");
    display.println("LED RED ON");
    display.display();
  delay(505);
  
}  

if (myData.d == true)
{
  digitalWrite(15, LOW);     // schaltet die LED an Pin 2 aus (Rote LED)
  digitalWrite(4, LOW);    // schaltet die LED an Pin 4 ein (Grüne LED)
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("LED GREEN ON");
    display.println("LED GREEN ON");
    display.display();
  delay(505);               // zwischen an und aus kurze Pause von 300 ms

  
}

}
