void bacaSensor() {
  bacaCT();
  teg3 = pzem.voltage();
  arus3 = pzem.current();
  //bacaCT();
  dataSensor = "";
  dataSensor += "BMS*";
  dataSensor += "0001*";
  dataSensor += "1";
  dataSensor += "*";
  dataSensor += String(teg1);
  dataSensor += "*";
  dataSensor += String(teg2);
  dataSensor += "*";
  dataSensor += String(teg3);
  dataSensor += "*";
  dataSensor += "0";
  dataSensor += "*";
  dataSensor += "0";
  dataSensor += "*";
  dataSensor += String(arus1);
  dataSensor += "*";
  dataSensor += String(arus2);
  dataSensor += "*";
  dataSensor += String(arus3);
  dataSensor += "*";
  dataSensor += "0";
  dataSensor += "*";
  dataSensor += "0";
  dataSensor += "*";
  dataSensor += String(temp1);
  dataSensor += "*";
  dataSensor += String(temp2);
  dataSensor += "*";
  dataSensor += String(hum1);
  dataSensor += "*";
  dataSensor += String(hum2);
  dataSensor += "*";
  di[0] = (!mcp.digitalRead(3));
  di[1] = (!mcp.digitalRead(4));
  di[2] = (!mcp.digitalRead(5));
  di[3] = (!mcp.digitalRead(6));
  di[4] = (!mcp.digitalRead(7));
  di[5] = (!mcp.digitalRead(9));
  di[6] = (!mcp.digitalRead(8));
  di[7] = (!mcp.digitalRead(0));
  di[8] = (!mcp.digitalRead(1));
  di[9] = (!mcp.digitalRead(2));
  dataSensor += di[0];
  dataSensor += "*";
  dataSensor += di[1];
  dataSensor += "*";
  dataSensor += di[2];
  dataSensor += "*";
  dataSensor += di[3];
  dataSensor += "*";
  dataSensor += di[4];
  dataSensor += "*";
  dataSensor += di[5];
  dataSensor += "*";
  dataSensor += di[6];
  dataSensor += "*";
  dataSensor += di[7];
  dataSensor += "*";
  dataSensor += di[8];
  dataSensor += "*";
  dataSensor += di[9];
  dataSensor += "*";
  //  dataSensor += "#";
  //  Serial.println(di);
  Serial.println(dataSensor);
  //@BMS*1*0001*teg1*teg2*teg3*teg4*teg5*arus1*arus2*arus3*arus4*arus5*temp1*temp2*hum1*hum2*in1*in2*in3*in4*in5*in6*in7*in8*in9*in10#
}


void bacaCT()
{
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  //  Voltage2 = (190.25 * ((adc2 * 0.125) / 1000)) - 475.65;
  //  Voltage3 = (190.25 * ((adc3 * 0.125) / 1000)) - 475.65;

  //  Voltage2 = (207.51 * ((adc2 * 0.125) / 1000)) - 518.96;
  //  Voltage3 = (207.51 * ((adc3 * 0.125) / 1000)) - 518.96;

  Voltage2 = (196.56 * ((adc2 * 0.125) / 1000)) - 491.44;
  Voltage3 = (196.56 * ((adc3 * 0.125) / 1000)) - 491.44;



  //  Serial.print("AIN2: ");
  //  Serial.print((adc2 * 0.125) / 1000, 4);
  //  Serial.print("\tArus: ");
  //  Serial.println(Voltage2, 4);
  //
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
    arus1=avgCT[0];
    arus2=avgCT[1];
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
}
