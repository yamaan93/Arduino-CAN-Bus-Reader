#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;

MCP2515 mcp2515(10); // spi pin is 10

void setup()
{
  Serial.begin(9600); // begin Serial communication at 9600 buadrate
  SPI.begin();        // begin SPI Communication
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); // CAN Speed at 500KBPS and 8MHz crystal
  mcp2515.setNormalMode();

  delay(3000);

  Serial.print("Setup Complete \n");
}

void loop()
{
  Serial.println(mcp2515.readMessage(&canMsg));
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
  {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" ");
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");

    for (int i = 0; i < canMsg.can_dlc; i++)
    { // print the data
      Serial.print(canMsg.data[i], HEX);
      Serial.print(" ");
    }

    Serial.println();
  }
}