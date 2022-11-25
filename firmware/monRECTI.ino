#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);
float Voltage2 = 0.0;
float Voltage3 = 0.0;
float avgCT[2] = {0.0, 0.0};
float tampungData2[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float tampungData3[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int count = 0;
int16_t  adc0, adc1, adc2, adc3; // we read from the ADC, we have a sixteen bit integer as a result


void setup(void)
{
  Serial.begin(9600);
  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  ads.begin();

}

void loop(void)
{
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  //Voltage2 = (190.25 * ((adc2 * 0.125) / 1000)) - 475.65;
  //Voltage3 = (190.25 * ((adc3 * 0.125) / 1000)) - 475.65;
  //Voltage2=adc2;
  //Voltage3=adc3;

  //  Voltage2 = (207.51 * ((adc2 * 0.125) / 1000)) - 518.96;
  //  Voltage3 = (207.51 * ((adc3 * 0.125) / 1000)) - 518.96;

  Voltage2 = (196.56 * ((adc2 * 0.125) / 1000)) - 491.44;
  Voltage3 = (196.56 * ((adc3 * 0.125) / 1000)) - 491.44;
  //Serial.print(adc2);
  //Serial.print("||");
  //Serial.println(adc3);


  //  Serial.print("AIN2: ");
  //  Serial.print((adc2 * 0.125) / 1000, 4);
  //  Serial.print("\tArus: ");
  //  Serial.println(Voltage2, 4);
  //  Serial.print("AIN3: ");
  //  Serial.print((adc3 * 0.125) / 1000, 4);
  //  Serial.print("\tArus: ");
  //  Serial.println(Voltage3, 4);

  if (count > 9) {
    for (int i = 0; i < count; i++) {
      if (i == 9) {
        tampungData2[i] = Voltage2;
        tampungData3[i] = Voltage3;
      }
      else {
        tampungData2[i] = tampungData2[i + 1];
        tampungData3[i] = tampungData3[i + 1];
      }
    }

    for (int j = 0; j < count; j++) {
      avgCT[0] += tampungData2[j];
      avgCT[1] += tampungData3[j];
      //      Serial.println(tampungData[j]);

    }
    avgCT[0] = avgCT[0] / 10;
    avgCT[1] = avgCT[1] / 10;

    Serial.print("Data CT2    :");
    Serial.println(avgCT[0]);
    Serial.print("Data CT3    :");
    Serial.println(avgCT[1]);
    count--;
  }
  else {
    tampungData2[count] = Voltage2;
    tampungData3[count] = Voltage3;
  }

  avgCT[0] = 0.0;
  avgCT[1] = 0.0;
  count++;
  delay(1000);
}
