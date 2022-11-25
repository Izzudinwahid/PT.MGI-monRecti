void sendModbus(){
  uint16_t crc = calcCRC(perintah[flag], sizeof(perintah[flag]));
  Serial2.write(perintah[flag], sizeof(perintah[flag]));
  Serial2.write(lowByte(crc));
  Serial2.write(highByte(crc));
  while (Serial2.available()>0)
  {
   byte b = Serial2.read();
    *ptr ++= b;
     dtSerial+=(String)b;
    //Serial.print(b);
    delay(2);
  }
  int count = dtSerial.indexOf("444");
  //Serial.println(dtSerial);
  dtSerial="";
    memcmp(bufferDataModbus, perintah[flag], 2);
    ptr = bufferDataModbus;
    
    if (ptr[0] ==1) {
       teg1      = ((ptr[3] << 8) + ptr[4]) * 0.01;
      //arus1     = ((ptr[2 + 3] << 8) + ptr[3 + 3]) * 0.01;
     //  Serial.print("teg1= ");
     //  Serial.println(teg1);
     //  Serial.print("arus1=");
     //  Serial.println(arus1);
    //   memset(bufferDataModbus, 0x00, sizeof(bufferDataModbus));
    }
    else if (ptr[0] == 2 ) {
      teg2      = ((ptr[3] << 8) + ptr[4]) * 0.01;
       temp1 = ((ptr[24] << 8)+ptr[25])*0.1;
       hum1 =((ptr[26] << 8)+ptr[27])*0.1;
      
      //arus2          = ((ptr[2 + 3] << 8) + ptr[3 + 3]) * 0.01;
      //Serial.print("teg2= ");
      //Serial.println(teg2);
      //Serial.print("arus2=");
      //Serial.println(arus2);
      //memset(bufferDataModbus, 0x00, sizeof(bufferDataModbus));
    }
      if (ptr[0] == 4) {
      //Serial.println("suhu");
       temp1 = ((ptr[3] << 8)+ptr[4])*0.1;
       hum1 =((ptr[5] << 8)+ptr[6])*0.1;
       //temp2 = ((ptr[3] << 8)+ptr[4])*0.1;
      }
      if (ptr[0] == 5) {
      //Serial.println("suhu");
       temp2 = ((ptr[3] << 8)+ptr[4])*0.1;
       hum2 =((ptr[5] << 8)+ptr[6])*0.1;
       //temp2 = ((ptr[3] << 8)+ptr[4])*0.1;
      }
    if (ptr[0] == 2 &&(dtSerial.length())>2) {
       temp1 = ((ptr[24] << 8)+ptr[25])*0.1;
       hum1 =((ptr[26] << 8)+ptr[27])*0.1;
      // temp2 = ((ptr[24] << 8)+ptr[25])*0.1;
      //Serial.println(hum1);
     // hum1 = ( ((ptr[26] << 8) + ptr[27]) * 0.1 );
      //memset(bufferDataModbus, 0x00, sizeof(bufferDataModbus));
      //Serial.print("suhu= ");
      //Serial.println(temp1);
      //Serial.print("hum=");
      //Serial.println(hum1);
     // memset(bufferDataModbus, 0x00, sizeof(bufferDataModbus));
    }
    

    //Serial.print("------------");
    //Serial.println((ptr[1 + 3] ));
    //float tegangan      = ((ptr[3] << 8) + ptr[4]) * 0.01;
    //float arus          = ((ptr[2 + 3] << 8) + ptr[3 + 3]) * 0.01;

    //memset(bufferDataModbus, 0x00, sizeof(bufferDataModbus));

    //Serial.println("==========");
    // Serial.print("tegangan      = ");
    // Serial.println(tegangan);
    // Serial.print("arus          = ");
    // Serial.println(arus);
  //}
 
  
}
uint16_t calcCRC(byte *data, byte panjang)
{
  int i;
  uint16_t crc = 0xFFFF;
  for (byte p = 0; p < panjang; p++)
  {
    crc ^= data[p];
    for (i = 0; i < 8; ++i)
    {
      if (crc & 1)
        crc = (crc >> 1) ^ 0xA001;
      else
        crc = (crc >> 1);
    }
  }
  return crc;
}
