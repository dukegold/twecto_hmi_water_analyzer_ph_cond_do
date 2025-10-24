/****************************************************************************
 *  Copyright 2023 Twecto Solutions PVT LTD                                 *
 *  All Rights Reserved.                                                    *
 *                                                                          *
 * All information contained herein is, and remains the property of         *
 * Twecto Solutions PVT LTD and its suppliers, if any.  The intellectual    *
 * and technical concepts contained herein are proprietary to Twecto        *
 * Solutions PVT LTD and its suppliers.Dissemination of this information or *
 * reproduction of this material is strictly forbidden unless prior written *
 * permission is obtained from Twecto Solutions PVT LTD.                    *
 *                                                                          *
 * Author:                                                                  *
 *  Aftab Usmani                                                            *
 *                                                                          *
 * Date Created:                                                            *
 *  06/24/2023                                                              *
 ***************************************************************************/

#define DEBUG_EN //Uncomment to print Serial debug
#include <Arduino.h>
#include <I2C_eeprom.h>
#include <SD.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Sys_Variables.h"
#include <ModbusMaster.h>
#include <Nextion.h>
#include "display_objects.h"
#include "saveData.h"
#include "uRTCLib.h"
#include "rtc.h"
#include <esp_task_wdt.h>

/********Function Prototypes ****************/
void sensorRead(ModbusMaster *cond_sensor, ModbusMaster *ph_sensor, ModbusMaster *do_sensor,
                float *cond_val, float *ph_val, float *temp_val, float *do_val,
                bool *is_cond_con, bool *is_ph_con, bool *is_do_con, bool *is_temp_con);
void sensor_mqtt( float cond_val,float ph_val, float temp_val, float do_val, bool cond_con, bool ph_con, bool do_con);
bool get_page_num(uint32_t *number);
void IRAM_ATTR onTimer0_0();
void(* resetFunc)() = nullptr;
/******* Code objects **********/
I2C_eeprom eeprom(0x57, I2C_DEVICESIZE_24LC32);
uRTCLib       rtc;
ModbusMaster ph_sensor;
ModbusMaster cond_sensor;
ModbusMaster do_sensor; //Temperature as well
WiFiClient espClient;
PubSubClient mqttClient(espClient);
/******* Code Variables for EEPROM**********/
float     cond_mcal;
float     cond_ucutoff;
float     cond_lcutoff;
float     cond_thresh;
float     disox_mcal;
float     disox_ucutoff;
float     disox_lcutoff;
float     disox_thresh;
float     ph_mcal;
float     ph_ucutoff;
float     ph_lcutoff;
float     ph_thresh;
float     temperature_ucutoff;
float     temperature_lcutoff;
float     temperature_thresh;
float     temperature_mcal;
float     cond_cal1;
float     cond_cal2;
float     cond_cal3;
float     disox_cal1;
float     disox_cal2;
float     disox_cal3;
float     ph_cal1;
float     ph_cal2;
float     ph_cal3;
float     temperature_cal1;
float     temperature_cal2;
float     temperature_cal3;
uint8_t   prehr;
uint8_t   dataSend;
uint32_t  log_choice;
uint8_t   lastReadDay;
uint32_t  slots;
char      wifi_ssid[40];
char      wifi_password[40];

/******* Code Variables for Logic**********/
float cond_val,ph_val,temp_val,do_val; // Sensor value
bool is_cond_con, is_ph_con, is_temp_con, is_do_con;
bool log_min, log_hr, wifi_recon;
bool loop_exit_update = false, log_choice_update = false, force_lcd_update;
bool saveStatus = true;
boolean sdFound,rtcFound, update_rtc_time = false;
unsigned long lastTime, lcdTime, menuTime, wifiTime;
String buf;
bool backlight = true, wifi_con = false;
char str_rep[75];
uint8_t last_log_min,logging_interval_minute;
byte second = 0,minute = 0,hour = 0,weekday = 0, monthday = 0,month = 0, year = 0;
uint32_t current_page;
uint32_t time_read_timer;
const char *log_intvl_str[] ={
  "2  Mins",
  "5  Mins",
  "1  Hour ",
  "2  Hours",
  "4  Hours",
  "6  Hours",
  "12 Hours",
  "24 Hours"};        
#include "nextion_callbacks.h"


void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Disconnected from WiFi access point");
  Serial.print("WiFi lost connection. Reason: ");
  Serial.println(info.wifi_sta_disconnected.reason);
  resetFunc();
}

void setup() {
  /*************************** Initialize IOs **************************/
  pinMode(PIN_ALARM_BUZZ, OUTPUT);
  pinMode(PIN_LID_CLOSE,  INPUT);
  digitalWrite(PIN_ALARM_BUZZ,  LOW); //Active High Alarm
  /*********************** Initialize peripherals **********************/
  MODBUS.begin(MODBUS_BAUD,SERIAL_8N1, RXD1, TXD1);
  Wire.begin();
  /*********************** Initialize Serial ports *********************/
  Serial.begin(115200);     //Debug
  MODBUS.begin(9600,SERIAL_8N1,PIN_CL_RX,PIN_CL_TX);     //RS485 Sensors
  Serial2.begin(9600, SERIAL_8N1, PIN_HMI_RX, PIN_HMI_TX);
  
  //Initialize the Nextion Display
  delay(2000);
  nexInit();
  sprintf(str_rep,"baud=%d",NEXTION_BAUD_RATE);
  sendCommand(str_rep);
  recvRetCommandFinished();
  Serial2.begin(NEXTION_BAUD_RATE, SERIAL_8N1, PIN_HMI_RX, PIN_HMI_TX);
  nexInit();

  /******************* Intialize EEPROM ******************/
  if(!eeprom.begin()){
    #ifdef DEBUG_EN
    Serial.println("EEPROM Not Initialized");
    #endif
  }
  
  if(eeprom.readByte(EEP_MAGIC_NUM) != EEPROM_MAGIC_NUM){
    //Defaults
    cond_mcal                  = 0                        ; //Nh3 Manual offset Calibration
    cond_ucutoff               = 100                      ; //Nh3 Upper Cutoff
    cond_lcutoff               = 0.1                      ; //Nh3 Lower Cutoff
    cond_thresh                = 0                        ; //Nh3 Threshold
    disox_mcal                = 0                        ; //disox Manual offset Calibration
    disox_ucutoff             = 20                       ; //disox Upper Cutoff
    disox_lcutoff             = 0                        ; //disox Lower Cutoff
    disox_thresh              = 0                        ; //disox Threshold
    ph_mcal                   = 0                        ; //ph Manual offset Calibration
    ph_ucutoff                = 12                       ; //ph Upper Cutoff
    ph_lcutoff                = 2                        ; //ph Lower Cutoff
    ph_thresh                 = 0                        ; //ph Threshold
    temperature_mcal          = 0                        ; //temperature Manual offset Calibration
    temperature_ucutoff       = 50                       ; //temperature Upper Cutoff
    temperature_lcutoff       = 0                        ; //temperature Lower Cutoff
    temperature_thresh        = 0                        ; //temperature Threshold
    cond_cal1                  = 0                        ; //Nh3 Calibration point 1
    cond_cal2                  = 0                        ; //Nh3 Calibration point 2
    cond_cal3                  = 0                        ; //Nh3 Calibration point 3
    disox_cal1                = 0                        ; //disox Calibration point 1
    disox_cal2                = 0                        ; //disox Calibration point 2
    disox_cal3                = 0                        ; //disox Calibration point 3
    ph_cal1                   = 0                        ; //ph Calibration point 1
    ph_cal2                   = 0                        ; //ph Calibration point 2
    ph_cal3                   = 0                        ; //ph Calibration point 3
    temperature_cal1          = 0                        ; //temperature Calibration point 1
    temperature_cal2          = 0                        ; //temperature Calibration point 2
    temperature_cal3          = 0                        ; //temperature Calibration point 3
    prehr                     = 0                        ; //Previous logging hour.
    dataSend                  = 0                        ; //Data sent in the current hour.
    log_choice                = 2                        ; //Logging interval selection.
    lastReadDay               = 0                        ; //Last day when logging was done.
    slots                     = 0xffffffff               ; //Current slots where logging has/has not occurred.
    sprintf(wifi_ssid,DEF_WIFI_SSID)                     ; //Wifi SSID
    sprintf(wifi_password,DEF_WIFI_PASS)                 ; //Wifi Password
    //EEPROM Default Updates
    eeprom.writeBlock(EEP_COND_MCAL,(uint8_t*) &cond_mcal,4);
    eeprom.writeBlock(EEP_COND_UCUTOFF,(uint8_t*) &cond_ucutoff,4);
    eeprom.writeBlock(EEP_COND_LCUTOFF,(uint8_t*) &cond_lcutoff,4);
    eeprom.writeBlock(EEP_COND_THRESH,(uint8_t*) &cond_thresh,4);
    eeprom.writeBlock(EEP_DISOX_MCAL,(uint8_t*) &disox_mcal,4);
    eeprom.writeBlock(EEP_DISOX_UCUTOFF,(uint8_t*) &disox_ucutoff,4);
    eeprom.writeBlock(EEP_DISOX_LCUTOFF,(uint8_t*) &disox_lcutoff,4);
    eeprom.writeBlock(EEP_DISOX_THRESH,(uint8_t*) &disox_thresh,4);
    eeprom.writeBlock(EEP_PH_MCAL,(uint8_t*) &ph_mcal,4);
    eeprom.writeBlock(EEP_PH_UCUTOFF,(uint8_t*) &ph_ucutoff,4);
    eeprom.writeBlock(EEP_PH_LCUTOFF,(uint8_t*) &ph_lcutoff,4);
    eeprom.writeBlock(EEP_PH_THRESH,(uint8_t*) &ph_thresh,4);
    eeprom.writeBlock(EEP_TEMPERATURE_MCAL,(uint8_t*) &temperature_mcal,4);
    eeprom.writeBlock(EEP_TEMPERATURE_UCUTOFF,(uint8_t*) &temperature_ucutoff,4);
    eeprom.writeBlock(EEP_TEMPERATURE_LCUTOFF,(uint8_t*) &temperature_lcutoff,4);
    eeprom.writeBlock(EEP_TEMPERATURE_THRESH,(uint8_t*) &temperature_thresh,4);
    eeprom.writeBlock(EEP_COND_CAL1,(uint8_t*) &cond_cal1,4);
    eeprom.writeBlock(EEP_COND_CAL2,(uint8_t*) &cond_cal2,4);
    eeprom.writeBlock(EEP_COND_CAL3,(uint8_t*) &cond_cal3,4);
    eeprom.writeBlock(EEP_DISOX_CAL1,(uint8_t*) &disox_cal1,4);
    eeprom.writeBlock(EEP_DISOX_CAL2,(uint8_t*) &disox_cal2,4);
    eeprom.writeBlock(EEP_DISOX_CAL3,(uint8_t*) &disox_cal3,4);
    eeprom.writeBlock(EEP_PH_CAL1,(uint8_t*) &ph_cal1,4);
    eeprom.writeBlock(EEP_PH_CAL2,(uint8_t*) &ph_cal2,4);
    eeprom.writeBlock(EEP_PH_CAL3,(uint8_t*) &ph_cal3,4);
    eeprom.writeBlock(EEP_TEMPERATURE_CAL1,(uint8_t*) &temperature_cal1,4);
    eeprom.writeBlock(EEP_TEMPERATURE_CAL2,(uint8_t*) &temperature_cal2,4);
    eeprom.writeBlock(EEP_TEMPERATURE_CAL3,(uint8_t*) &temperature_cal3,4);
    eeprom.writeByte(EEP_PRE_HR,prehr);
    eeprom.writeByte(EEP_DATA_SENT,dataSend);
    eeprom.writeBlock(EEP_LOG_CHOICE,(uint8_t*) &log_choice,4);
    eeprom.writeByte(EEP_LAST_DAY,lastReadDay);
    eeprom.writeBlock(EEP_LOG_SLOTS,(uint8_t*) &slots,4);
    eeprom.writeBlock(EEP_WIFI_SSID,(uint8_t*) wifi_ssid,40);
    eeprom.writeBlock(EEP_WIFI_PASS,(uint8_t*) wifi_password,40);
    eeprom.writeByte(EEP_MAGIC_NUM,EEPROM_MAGIC_NUM);
  }
  else{
    //Load from EEPROM
    eeprom.readBlock(EEP_COND_MCAL,(uint8_t*) &cond_mcal,4);
    eeprom.readBlock(EEP_COND_UCUTOFF,(uint8_t*) &cond_ucutoff,4);
    eeprom.readBlock(EEP_COND_LCUTOFF,(uint8_t*) &cond_lcutoff,4);
    eeprom.readBlock(EEP_COND_THRESH,(uint8_t*) &cond_thresh,4);
    eeprom.readBlock(EEP_DISOX_MCAL,(uint8_t*) &disox_mcal,4);
    eeprom.readBlock(EEP_DISOX_UCUTOFF,(uint8_t*) &disox_ucutoff,4);
    eeprom.readBlock(EEP_DISOX_LCUTOFF,(uint8_t*) &disox_lcutoff,4);
    eeprom.readBlock(EEP_DISOX_THRESH,(uint8_t*) &disox_thresh,4);
    eeprom.readBlock(EEP_PH_MCAL,(uint8_t*) &ph_mcal,4);
    eeprom.readBlock(EEP_PH_UCUTOFF,(uint8_t*) &ph_ucutoff,4);
    eeprom.readBlock(EEP_PH_LCUTOFF,(uint8_t*) &ph_lcutoff,4);
    eeprom.readBlock(EEP_PH_THRESH,(uint8_t*) &ph_thresh,4);
    eeprom.readBlock(EEP_TEMPERATURE_MCAL,(uint8_t*) &temperature_mcal,4);
    eeprom.readBlock(EEP_TEMPERATURE_UCUTOFF,(uint8_t*) &temperature_ucutoff,4);
    eeprom.readBlock(EEP_TEMPERATURE_LCUTOFF,(uint8_t*) &temperature_lcutoff,4);
    eeprom.readBlock(EEP_TEMPERATURE_THRESH,(uint8_t*) &temperature_thresh,4);
    eeprom.readBlock(EEP_COND_CAL1,(uint8_t*) &cond_cal1,4);
    eeprom.readBlock(EEP_COND_CAL2,(uint8_t*) &cond_cal2,4);
    eeprom.readBlock(EEP_COND_CAL3,(uint8_t*) &cond_cal3,4);
    eeprom.readBlock(EEP_DISOX_CAL1,(uint8_t*) &disox_cal1,4);
    eeprom.readBlock(EEP_DISOX_CAL2,(uint8_t*) &disox_cal2,4);
    eeprom.readBlock(EEP_DISOX_CAL3,(uint8_t*) &disox_cal3,4);
    eeprom.readBlock(EEP_PH_CAL1,(uint8_t*) &ph_cal1,4);
    eeprom.readBlock(EEP_PH_CAL2,(uint8_t*) &ph_cal2,4);
    eeprom.readBlock(EEP_PH_CAL3,(uint8_t*) &ph_cal3,4);
    eeprom.readBlock(EEP_TEMPERATURE_CAL1,(uint8_t*) &temperature_cal1,4);
    eeprom.readBlock(EEP_TEMPERATURE_CAL2,(uint8_t*) &temperature_cal2,4);
    eeprom.readBlock(EEP_TEMPERATURE_CAL3,(uint8_t*) &temperature_cal3,4);
    prehr = eeprom.readByte(EEP_PRE_HR);
    dataSend = eeprom.readByte(EEP_DATA_SENT);
    eeprom.readBlock(EEP_LOG_CHOICE,(uint8_t*) &log_choice,4);
    lastReadDay = eeprom.readByte(EEP_LAST_DAY);
    eeprom.readBlock(EEP_LOG_SLOTS,(uint8_t*) &slots,4);
    eeprom.readBlock(EEP_WIFI_SSID,(uint8_t*) wifi_ssid,40);
    eeprom.readBlock(EEP_WIFI_PASS,(uint8_t*) wifi_password,40);
  }
  /*************** End Initialize EEPROM  ********************/
  
  /****************** Nextion Globals  ***********************/

  //Nextion Function attachments to buttons
  b_menu_minfo.attachPop (b_menu_minfo_release  , &b_menu_minfo );
  b_menu_cal.attachPop   (b_menu_cal_release    , &b_menu_cal   );
  b_menu_lcycle.attachPop(b_menu_lcycle_release , &b_menu_lcycle);
  b_menu_wsetup.attachPop(b_menu_wsetup_release , &b_menu_wsetup);
  b_cal_set.attachPop    (b_cal_set_release     , &b_cal_set    );
  b_lcycle_set.attachPop (b_lcycle_set_release  , &b_lcycle_set );
  b_pass_enter.attachPop (b_pass_enter_release  , &b_pass_enter );
  b_wsetup_set.attachPop (b_wsetup_set_release  , &b_wsetup_set );
  b_conf_set.attachPop   (b_conf_set_release    , &b_conf_set   );
  b_time_set.attachPop   (b_time_set_release    , &b_time_set   );

  //############ RTC Initialization ###########
  if (! URTCLIB_WIRE.begin()) {
#ifdef DEBUG_EN
    Serial.println("Couldn't find RTC");
#endif

    rtcFound = false;
  } else {
    rtcFound = true;
  }
  rtc.set_rtc_address(0x68);
  rtc.set_model(URTCLIB_MODEL_DS3231);
  /*********************** Intialize Wifi ****************************/
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFiClass::mode(WIFI_STA);
#ifdef DEBUG_EN
  Serial.println("Connecting Wifi ...");
#endif

  WiFi.begin(wifi_ssid, wifi_password);
  for(int i = 0;i<10;i++) {
    if(WiFiClass::status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
      delay(250);
#ifdef DEBUG_EN
      Serial.print('.');
#endif
    }
  }
  wifi_con = WiFiClass::status() == WL_CONNECTED;
  /*********************** End Intialize Wifi ****************************/

  /*********************** Intialize MQTT ****************************/
    mqttClient.setServer(IOT_SERVER, 1883);
  
  if(wifi_con){
    mqttClient.connect(MQTT_CLIENT_ID,MQTT_USERNAME,MQTT_PASS);
  }
  /*********************** End Intialize MQTT ****************************/

  /*********************** Set pin Modes **********************/
  pinMode(PIN_BUZZ_ALARM,OUTPUT);
  //Turn off everything
  digitalWrite(PIN_BUZZ_ALARM,0);
  /*********************** End Set pin Modes **********************/
  
  //########## SD Card Initialization ##########
  sdFound = true;
  if (!SD.begin(SDCSPIN)) {
    #ifdef DEBUG_EN
    Serial.println("Err! SD Not Found.");
    #endif
    sdFound = false;
  }
  
  /*********************** Initialize Modbus *********************/
  cond_sensor.begin(COND_SENSOR_SLAVE_ID,MODBUS);  //Nh3 sensor
  ph_sensor.begin(PH_SENSOR_SLAVE_ID,MODBUS);    //PH sensor
  do_sensor.begin(DO_SENSOR_SLAVE_ID,MODBUS);    //Dissolved Oxygen sensor

  /*********************** Initialize Timers *********************/
  force_lcd_update = true;
  lcdTime = millis();

  last_log_min = minute;
  switch(log_choice){
    case 0:
      logging_interval_minute = 2;
      break;
    case 1:
      logging_interval_minute = 5;
      break;
    case 2:
      logging_interval_minute = 10;
      break;
    case 3:
      logging_interval_minute = 15;
      break;
    case 4:
      logging_interval_minute = 20;
      break;
    case 5:
      logging_interval_minute = 25;
      break;
    case 6:
      logging_interval_minute = 30;
      break;
    default:
      logging_interval_minute = 2;
      break;
  }
  #ifdef DEBUG_EN
  Serial.print("Log choice:");
  Serial.println(log_choice);
  Serial.print("Interval(min):");
  Serial.println(logging_interval_minute);
  Serial.print("last_log_min:");
  Serial.println(last_log_min);
  #endif
  sprintf(strbuf,"sleep=0");
  sendCommand(strbuf);
  delay(500);
  //Go to main page
  sprintf(str_rep,"page %d",HOME_PAGE);
  sendCommand(str_rep);
  recvRetCommandFinished();
  readTime(&rtc,&second,&minute,&hour,&weekday, &monthday,&month, &year); //refresh current time from RTC
  time_read_timer = millis();
  backlight = true;
  //Setup WDT
  esp_task_wdt_init(WDT_TIMEOUT, true);
  esp_task_wdt_add(nullptr);
}

void loop(){
  //*******************************
  //***** Nextion Callbacks *******
  //*******************************
  if(backlight)
    nexLoop(nex_listen_list);
  
  //*******************************
  //**** Nextion Power Control ****
  //*******************************
  if(!backlight && !digitalRead(PIN_LID_CLOSE)){
    //sprintf(strbuf,"lowpower=0");
    sprintf(strbuf,"sleep=0");
    sendCommand(strbuf);
    //delay(500);
    backlight = true;
    #ifdef DEBUG_EN
    Serial.println("HMI: Waking up...!");
    #endif
  }
  else if(backlight && digitalRead(PIN_LID_CLOSE)){
    //sprintf(strbuf,"lowpower=1");
    sprintf(strbuf,"sleep=1");
    sendCommand(strbuf);
    backlight = false;
    #ifdef DEBUG_EN
    Serial.println("HMI: Entering Sleep...!");
    #endif
  }
  //*******************************
  //**** LCD interaction code *****
  //*******************************
  if((millis() - lcdTime > LCD_UPDATE_TIME) || force_lcd_update){
    if(update_rtc_time){
      setRTCTime(&rtc, 0,minute,hour,0,monthday,month,year);
      update_rtc_time = false;
    }
    //Refresh Time
    readTime(&rtc,&second,&minute,&hour,&weekday, &monthday,&month, &year); //refresh current time from RTC
    //Sensor read
    #ifdef DEBUG_EN
    Serial.println("Sensor Read");
    #endif
    sensorRead(&cond_sensor, &ph_sensor, &do_sensor,
               &cond_val, &ph_val, &temp_val, &do_val,
               &is_cond_con, &is_ph_con, &is_do_con, &is_temp_con);
    // Manipulate
    cond_val   = cond_val   + cond_mcal;
    ph_val   = ph_val   + ph_mcal;
    temp_val = temp_val + temperature_mcal;
    do_val   = do_val   + disox_mcal;
    
    //Bind values within limits
    if(cond_val > cond_ucutoff)
      cond_val = cond_ucutoff;
    if(cond_val < cond_lcutoff)
      cond_val = cond_lcutoff;
    
    if(do_val > disox_ucutoff)
      do_val = disox_ucutoff;
    if(do_val < disox_lcutoff)
      do_val = disox_lcutoff;

    if(ph_val > ph_ucutoff)
      ph_val = ph_ucutoff;
    if(ph_val < ph_lcutoff)
      ph_val = ph_lcutoff;
    if(temp_val > temperature_ucutoff)
      temp_val = temperature_ucutoff;
    if(temp_val < temperature_lcutoff)
      temp_val = temperature_lcutoff;
    
    lcdTime = millis();
    if(backlight){
      get_page_num(&current_page);
      if(current_page == HOME_PAGE  || force_lcd_update){
	//Wifi Icon
	if(wifi_con)
	  sendCommand("vis p0,1");
	else
	  sendCommand("vis p0,0");
	//COND
	sprintf(str_rep,"%.2f",cond_val);
	if(is_cond_con)
	  t_main_cond_val.setText(str_rep);
	else
	  t_main_cond_val.setText("NC");
	//DO
	sprintf(str_rep,"%.2f",do_val);
	if(is_do_con)
	  t_main_do_val.setText(str_rep);
	else
	  t_main_do_val.setText("NC");
	//Temperature
	sprintf(str_rep,"%.2f",temp_val);
	if(is_temp_con)
	  t_main_tp_val.setText(str_rep);
	else
	  t_main_tp_val.setText("NC");
	//pH
	sprintf(str_rep,"%.2f",ph_val);
	if(is_ph_con)
	  t_main_ph_val.setText(str_rep);
	else
	  t_main_ph_val.setText("NC");
	//Time
	getDateFullc(&rtc,str_rep);
	t_main_time_val.setText(str_rep);
      }
    }
    force_lcd_update = false;
  }
  
  //*******************************
  //***** Connectivity Checks *****
  //*******************************
  if(millis() - wifiTime > WIFI_RETRY_MS) {
    wifiTime = millis();
    wifi_con = (WiFiClass::status() == WL_CONNECTED);
    if(!wifi_con){
#ifdef DEBUG_EN
      Serial.print("Reconnecting WiFi");
#endif
      WiFi.disconnect(true,true);
      WiFiClass::mode(WIFI_STA);
      //WiFi.reconnect();
      WiFi.begin(wifi_ssid, wifi_password);
      for(int i = 0;i<10;i++) {
        if(WiFiClass::status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
          delay(250);
#ifdef DEBUG_EN
          Serial.print('.');
#endif
        }
      }
      wifi_con = (WiFiClass::status() == WL_CONNECTED) ;
      if(wifi_con)
        Serial.println("Reconnecting WiFi success");
    }
    if(wifi_con && !mqttClient.connected()){
      mqttClient.connect(MQTT_CLIENT_ID,MQTT_USERNAME,MQTT_PASS);
    }
  }

  //*******************************
  //**** Log timing calculation ***
  //*******************************
  if (log_choice_update) {
    log_choice_update = false;
    switch(log_choice){
    case 0:{
      logging_interval_minute = 2;
      break;
    }
    case 1:{
      logging_interval_minute = 5;
      break;
    }
    case 2:{
      logging_interval_minute = 10;
      break;
    }
    case 3:{
      logging_interval_minute = 15;
      break;
    }
    case 4:{
      logging_interval_minute = 20;
      break;
    }
    case 5:{
      logging_interval_minute = 25;
      break;
    }
    case 6:{
      logging_interval_minute = 30;
      break;
    }
    default:{
      logging_interval_minute = 2;
      break;
    }
    } 
    #ifdef DEBUG_EN
    Serial.print("Log choice:");
    Serial.println(log_choice);
    Serial.print("Interval(min):");
    Serial.println(logging_interval_minute);
    #endif
  }
  
  //*******************************
  //*** Data Logging to SD/HTTP ***
  //*******************************
  int min_diff =  minute >= last_log_min ?
    minute - last_log_min:
    60 - last_log_min + minute;
  log_min    = (min_diff >= logging_interval_minute);
  if (log_min) {
    // Save Data to SD Card
    saveData(getFilename(month,year), cond_val, ph_val, temp_val, do_val, is_cond_con, is_ph_con, is_do_con, &rtc);
    esp_task_wdt_reset();
    if (wifi_con){
      // Create message to client
      sensor_mqtt( cond_val,ph_val, temp_val, do_val, is_cond_con, is_ph_con, is_do_con);
    }
    // Update Log status
    last_log_min = minute;
  }
  //Reset WDT Timer
  esp_task_wdt_reset();
}

void sensorRead(ModbusMaster *cond_sensor, ModbusMaster *ph_sensor, ModbusMaster *do_sensor,
		float *cond_val, float *ph_val, float *temp_val, float *do_val,
                bool *is_cond_con, bool *is_ph_con, bool *is_do_con, bool *is_temp_con) {
  float value;
  int result;
  uint16_t data[2];
  uint16_t slope;
  uint32_t data_combined;
  // Read Conductivity value from sensor
  result = cond_sensor->readHoldingRegisters(0, 2);
  if (result == ModbusMaster::ku8MBSuccess){
    for (int j = 0; j < 2; j++){
      data[j] = cond_sensor->getResponseBuffer(j);
    }
    *cond_val = ((float) (data[1]+(data[0]<<16)))/10;
    *is_cond_con = true;
  }
  else{
    *cond_val = -1;
    *is_cond_con = false;
  }
  delay(100);
  esp_task_wdt_reset();
  // Read pH value from sensor -> Address 2, 1 reg
  result = ph_sensor->readHoldingRegisters(2, 1);
  if (result == ModbusMaster::ku8MBSuccess){
    for (int j = 0; j < 1; j++){
      data[j] = ph_sensor->getResponseBuffer(j);
    }
    data_combined = data[0];
    *ph_val = ((float) data_combined)/100;
    *is_ph_con = true;
  }
  else{
    *ph_val = -1;
    *is_ph_con = false;
  }
  delay(100);
  esp_task_wdt_reset();
   // Read DO value from sensor
  union conv32
  {
    uint32_t u32; // here_write_bits
    float    f32; // here_read_float
  };
  result = do_sensor->readHoldingRegisters(0x2100, 2);
  if (result == ModbusMaster::ku8MBSuccess){
    for (int j = 0; j < 2; j++){
      data[j] = do_sensor->getResponseBuffer(j);
    }
    //Change Little Endian to Big Endian
    data_combined = (data[0]&0xff)<<8;
    data_combined |= data[0] >> 8;
    data_combined |= (data[1]&0xff)<<24;
    data_combined |= (data[1]&0xff00)<<8;
    *do_val = ((union conv32){.u32 = data_combined}).f32;
    *is_do_con = true;
  }
  else{
    *do_val = -1;
    *is_do_con = false;
  }
  delay(100);
  // Read Temp value from DO sensor
  result = do_sensor->readHoldingRegisters(0x2000, 2);
  if (result == ModbusMaster::ku8MBSuccess){
    for (int j = 0; j < 2; j++){
      data[j] = do_sensor->getResponseBuffer(j);
    }
    //Change Little Endian to Big Endian
    data_combined = (data[0]&0xff)<<8;
    data_combined |= data[0] >> 8;
    data_combined |= (data[1]&0xff)<<24;
    data_combined |= (data[1]&0xff00)<<8;
    *temp_val = ((union conv32){.u32 = data_combined}).f32;
    *is_temp_con = true;
  }
  else{
    *temp_val = -999;
    *is_temp_con = false;
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void sensor_mqtt( float cond_val,
                  float ph_val,
                  float temp_val,
                  float do_val,
                  bool cond_con,
                  bool ph_con,
                  bool do_con){
  char str_tmp[200];
  char buf1[20],buf2[20];
  sprintf(buf1,"%02d:%02d:%02d",hour,minute,second);
  sprintf(buf2,"%04d-%02d-%02d",2000+year,month,monthday);
  sprintf(str_tmp,"{\"timestamp\":\"%sT%s+05:30\",\"ec_uS_cm\":%.2f,\"ph\":%.2f,\"do_mg_per_l\":%.2f,\"temperature_degC\":%.2f}", buf2, buf1, cond_val, ph_val, do_val, temp_val);
  mqttClient.publish(IOT_PUB_TOPIC, str_tmp);
}

bool get_page_num(uint32_t *number){
  String cmd = String("get dp");
  sendCommand(cmd.c_str());
  return recvRetNumber(number);
}

