#include <Arduino.h>
#include <SPI.h> 
#include <mcp2515.h> 

struct can_frame canMsg;

MCP2515 mcp2515(10); //spi pin is 10



void setup() {
  Serial.begin(9600); // begin Serial communication at 9600 buadrate
  SPI.begin(); //begin SPI Communication
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //CAN Speed at 500KBPS and 8MHz crystal
  mcp2515.setNormalMode();

  delay(3000);

  Serial.print("Setup Complete \n");
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
        
        //expecting the first 2 data points to be speed and temp
        int speed = canMsg.data[0];
        int temp = canMsg.data[1];

        char message[80];

        sprintf (message, "Temperature: %d Speed: %d",temp, speed);

        Serial.print(message);

    }



}