#include <SPI.h>     //Library for using SPI Communication
#include <mcp2515.h> //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 6 // DHT sensor connected to pin 6
#define DHTTYPE DHT11  
#define JOYX A0
#define JOYY A1

DHT dht(DHTPIN, DHTTYPE);

struct can_frame canMsg;

MCP2515 mcp2515(10);

void setup()
{
  while (!Serial)
    ;
  Serial.begin(9600);
  SPI.begin(); // Begins SPI communication
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); // Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();
  dht.begin();
}

void loop()
{

  //sensor readings
  float temperature = dht.readTemperature() *10;
  float humidity = dht.readHumidity()*2.5;
  float joystickX = analogRead(JOYX)/1024.0*100.0;
  float joystickY = analogRead(JOYY)/1024.0*100.0;
  Serial.print("temp: ");
  Serial.println(temperature);
  Serial.print("humidity: ");
  Serial.println(humidity);
  Serial.print("Joystick x: ");
  Serial.print(joystickX);
  Serial.print(" binary: ");
  Serial.println(joystickY,BIN);
  Serial.print("Joystick y: ");
  Serial.print(joystickY);
  Serial.print(" binary: ");
  Serial.println(joystickY,BIN);
  canMsg.can_id = 0x036; // CAN id as 0x036
  canMsg.can_dlc = 8;    // CAN data length as 8
  canMsg.data[0] = temperature;
  canMsg.data[1] = humidity;
  canMsg.data[2] = joystickX;
  canMsg.data[3] = joystickY;
  canMsg.data[5] = random(32, 39);
  canMsg.data[5] = random(40, 47);
  canMsg.data[6] = random(48, 55);
  canMsg.data[7] = random(56, 63);
  mcp2515.sendMessage(&canMsg); // Sends the CAN message
  //Serial.print("Sending sound: ");
  //Serial.println(canMsg.data[2]);
  delay(100);
}