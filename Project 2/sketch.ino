#define BLYNK_TEMPLATE_ID "TMPL6rGHgUeTo"
#define BLYNK_TEMPLATE_NAME "IoT Light Monitor"
#define BLYNK_AUTH_TOKEN "vTvM5xmzU8Vs3BKzqnXVHZyD6DIXEmlJ"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// pin configuration
#define LDR_PIN 34   
#define RELAY_PIN 12 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST"; 
char pass[] = "";

int threshold = 1500; 
BlynkTimer timer;


void sendData() {
  int lightLevel = analogRead(LDR_PIN);
  
 
  Blynk.virtualWrite(V1, lightLevel); 

  Serial.print("LDR Value: ");
  Serial.println(lightLevel);

  
  if (lightLevel < threshold) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V2, 1); 
    Serial.println("Status: DARK -> Relay ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V2, 0); 
    Serial.println("Status: BRIGHT -> Relay OFF");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  
  
  Blynk.begin(auth, ssid, pass);
  
  
  timer.setInterval(1000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}