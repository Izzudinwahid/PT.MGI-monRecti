#define pinModBusTX
#include <lorawan.h>
//#define INTERVAL_MESSAGE1 1000

//LIB for MCP
#include <Adafruit_MCP23X17.h>

//LIB for PZEM 01T
  
#define PZEM_RX_PIN 25
#define PZEM_TX_PIN 13

//LIB for ADS1115
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;
float Voltage2 = 0.0;
float Voltage3 = 0.0;
float avgCT[2] = {0.0, 0.0};
float tampungData2[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float tampungData3[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int count = 0;
int16_t  adc0,adc1,adc2, adc3; // we read from the ADC, we have a sixteen bit integer as a result


const char *devAddr = "0003bae3";
const char *nwkSKey = "666fd1dc5734b8e52c5b65da67f26aa1";
const char *appSKey = "7b6ba06d5309e0b03b1cb5c64d6dded1";

const unsigned long interval = 10000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent
unsigned int counter = 0;     // message counter

char myStr[100];
char outStr[255];
byte recvStatus = 0;

const sRFM_pins RFM_pins = {
  .CS = 18,
  .RST = 14,
  .DIO0 = 26,
  .DIO1 = 3,
  .DIO2 = -1,
  .DIO5 = -1,
};


//#SoftwareSerial pzem(2, 3); // RX, TX
float temp1 = 0;
float temp2 = 0;
float hum1 = 0;
float hum2 = 0;
float teg1 = 0;
float teg2 = 0;
float teg3 = 0;
float arus1 = 0;
float arus2 = 0;
float arus3 = 0;
boolean in1 = false;
boolean in2 = false;
boolean in3 = false;
boolean in4 = false;
boolean in5 = false;
boolean in6 = false;
boolean in7 = false;
boolean in8 = false;
boolean in9 = false;
boolean in10 = false;
int di[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
String dtSerial = "";
String dataSensor = "";
byte perintah[4][6] = {
  {0x01, 0x04, 0x00, 0x00, 0x00, 0x08}, //
  {0x02, 0x04, 0x00, 0x00, 0x00, 0x08},
  {0x04, 0x04, 0x00, 0x01, 0x00, 0x02}, //suhu
  {0x05, 0x04, 0x00, 0x01, 0x00, 0x02}
  //{0x01, 0x06, 0x01, 0x01, 0x00, 0x05}
};

//byte perintah[]={0x1,0x6,0x1,0x1,0x00,0x04};
byte bufferDataModbus[100];
byte *ptr;
int flag = 0;

Adafruit_MCP23X17 mcp;
PZEM004Tv30 pzem(Serial1, PZEM_RX_PIN, PZEM_TX_PIN);
void setup() {
  Serial.begin(9600, SERIAL_8N2);
  Serial1.begin(9600, SERIAL_8N2, PZEM_RX_PIN, PZEM_TX_PIN);
  Serial2.begin(9600, SERIAL_8N2);
  Serial.println();
  ptr = bufferDataModbus;
  if (!lora.init()) {
    Serial.println("RFM95 not detected");
    delay(5000);
    return;
  }
  lora.setDeviceClass(CLASS_C);

  // Set Data Rate
  lora.setDataRate(SF7BW125);

  // set channel to random
  lora.setChannel(MULTI);

  // Put ABP Key and DevAddress here
  lora.setNwkSKey(nwkSKey);
  lora.setAppSKey(appSKey);
  lora.setDevAddr(devAddr);

  //MCP
  mcp.begin_I2C(0x20);
  // if (!mcp.begin_I2C(0x20)) {
  //if (!mcp.begin_SPI(CS_PIN)) {
  //  Serial.println("MCP not detected");
  //   while (1);
  // }
  mcp.pinMode(0, INPUT_PULLUP);
  mcp.pinMode(1, INPUT_PULLUP);
  mcp.pinMode(2, INPUT_PULLUP);
  mcp.pinMode(3, INPUT_PULLUP);
  mcp.pinMode(4, INPUT_PULLUP);
  mcp.pinMode(5, INPUT_PULLUP);
  mcp.pinMode(6, INPUT_PULLUP);
  mcp.pinMode(7, INPUT_PULLUP);
  mcp.pinMode(8, INPUT_PULLUP);
  mcp.pinMode(9, INPUT_PULLUP);

  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  ads.begin();
}

void loop()
{
  
    sendModbus();
    bacaCT();
  if (millis() - previousMillis > interval) {

        bacaSensor();
    
        sprintf(myStr, dataSensor.c_str());
    //    //Serial.print("Sending: ");
        Serial.println(myStr);
        lora.sendUplink(myStr, dataSensor.length(), 0, 1);
    //    counter++;

    previousMillis = millis();
  }

  //recvStatus = lora.readData(outStr);
  //  if (recvStatus) {
  //    Serial.println(outStr);
  //  }

    lora.update();
  delay(200);
  flag++;
  if (flag > 3) {
    flag = 0;
  }
}
