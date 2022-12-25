#include <SPI.h>     //Library for using SPI Communication
#include <mcp2515.h> //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)

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
}

void loop()
{

  canMsg.can_id = 0x036; // CAN id as 0x036
  canMsg.can_dlc = 8;    // CAN data length as 8
  canMsg.data[0] = random(0, 7);
  canMsg.data[1] = random(8, 15);
  canMsg.data[2] = random(16, 23);
  canMsg.data[3] = random(24, 31);
  canMsg.data[5] = random(32, 39);
  canMsg.data[5] = random(40, 47);
  canMsg.data[6] = random(48, 55);
  canMsg.data[7] = random(56, 63);
  mcp2515.sendMessage(&canMsg); // Sends the CAN message
  Serial.print("Sending message with ID: ");
  Serial.println(canMsg.can_id);
  delay(1000);
}