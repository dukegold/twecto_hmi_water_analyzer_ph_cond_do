#ifndef SAVEDATA_H
#define SAVEDATA_H
#include "rtc.h"
#include "uRTCLib.h"

void saveData(String filename, float cond_val,float ph_val, float temp_val, float do_val, bool cond_con, bool ph_con, bool do_con, uRTCLib *rtc);
String getFilename();
String decToHex(byte decValue, byte desiredStringLength);

void saveData(String filename, float cond_val,float ph_val, float temp_val, float do_val, bool cond_con, bool ph_con, bool do_con, uRTCLib *rtc){
  bool writeHeader;
  File file;
  #ifdef DEBUG_EN
    Serial.print("SD Filename:");
    Serial.println(filename);
    #endif
  if (SD.exists((char*)filename.c_str())){
    writeHeader = false;
    file = SD.open(filename.c_str(), FILE_APPEND);
  }
  else{
    writeHeader = true;
    file = SD.open(filename.c_str(), FILE_WRITE);
  }
  char buf[10];
  if (file) {
    if (writeHeader) {
      file.println(",############,##################################,######################,###################");
      file.println(",############,Report,,###################");
      file.println(",############,Chlorine Data,,###################");
      file.print(",############,Device ID: ");
      file.print(DEVICE_ID);
      file.print(", Serial No: ");
      file.print(DEV_SER);
      file.println(",###################");
      file.println(",############,,,###################");
      file.println(",############,Powered by Teknowish,,###################");
      file.println(",############,##################################,######################,###################");
      file.println(",Date,Time,conductivity (uS), Dissolved Oxygen(mg/L),pH,Temperature (C)");
    }
    #ifdef DEBUG_EN
    Serial.println("Data Saved");
    #endif
    file.print(",");
    getDate(rtc, buf);
    file.print(buf);
    file.print(",");
    getTime(rtc, buf);
    file.print(buf);
    file.print(",");
    if(cond_con)
      file.print(cond_val);
    else
      file.print("NC");
    file.print(",");
    if(do_con)
      file.print(do_val);
    else
      file.print("NC");
    file.print(",");
    if(ph_con)
      file.print(ph_val);
    else
      file.print("NC");
    file.print(",");
    if(do_con)
      file.println(temp_val);
    else
      file.println("NC");
    file.close();
  }
  else{
    #ifdef DEBUG_EN
    Serial.println("SD Data failed!!");
    #endif
  }
}

String getFilename(byte month, byte year) {
  char buf[10];
  String s = "/";
  s += DEVICE_ID;
  s += "_";
  sprintf(buf,"%d_%d",month,year);
  s += buf;
  s += ".csv";
  return s;
}

String decToHex(byte decValue, byte desiredStringLength) {

  String hexString = String(decValue, HEX);
  while (hexString.length() < desiredStringLength) hexString = "0" + hexString;
  hexString.toUpperCase();
  return hexString;
}
#endif