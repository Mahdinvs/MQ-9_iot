#define THINGER_SERIAL_DEBUG

#include <ThingerESP32.h>
#include <HardwareSerial.h>

#define USERNAME "username" // Your username on Thinger.io
#define DEVICE_ID "pass" // Your password on Thinger.io
#define DEVICE_CREDENTIAL "Credential" // Your device credential on Thinger.io

#define SSID "SSID" // Your WiFi ssid
#define SSID_PASSWORD "WiFi-pass" // Your WiFi password 

#define gas_pin 35
#define alarm 23

int gas_value;

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

HardwareSerial sim800(2);

void setup() {

  thing.add_wifi(SSID, SSID_PASSWORD);

  Serial.begin(115200);
  sim800.begin(115200);


  Serial.println("Initializing...");
  delay(1000);
  sim800.println("AT"); 
  updateSerial();
  sim800.println("AT+CSQ"); // Signal quality check
  updateSerial();
  sim800.println("AT+CCID"); // Sim card data
  updateSerial();
  sim800.println("AT+CREG?"); // Network connection check
  updateSerial();
  // sim800.println("AT+CSCS=\"HEX\""); // Hex coding mode
  // updateSerial();
  // sim800.println("AT+CSMP=49,167,0,8"); // Set sms mode for UNICODE characters
  // updateSerial();

  pinMode(gas_pin, INPUT);
  pinMode(alarm, OUTPUT);

  thing["Gas Level"] >> outputValue(gas_value);
  
}

void loop() {

    for(int i=0; i <= 30; i++){

gas_value += analogRead(gas_pin);
delay(500);

    }
    gas_value = gas_value/30;
    Serial.println(String(gas_value));
    

  if(gas_value >= 1024){
    digitalWrite(alarm, HIGH);

    sim800.println("AT+CMGF=1");
    updateSerial();
    sim800.println("AT+CMGS=\"+ZZxxxxxxxxxx\""); // Enter country code instead of ZZ and the number instead of xs
    updateSerial();
    sim800.print("Gas alarm: Level too high");
    updateSerial();
    sim800.write(26);

    

  } else {
    digitalWrite(alarm, LOW);
  }
 thing.handle();
}
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    sim800.write(Serial.read());  
  }
  while (sim800.available()) {
    Serial.write(sim800.read());  
  }
}
