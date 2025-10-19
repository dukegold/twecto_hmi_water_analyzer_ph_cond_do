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

#ifndef SYSVARIABLES_H
#define SYSVARIABLES_H
#include "pinmap.h"

// ########################## Product Info #########################################
#define DEVICE_ID "AQUA2501"
#define DEV_SER "2400000022501"
const uint64_t dev_ser = 2400000022501UL;
#define FIRMNAME "NatureDots"
const char auth_pass[] =  "5432";
#define COMPANY_TITLE "NatureDots Private Limited\n"
// ############################# Network Related ###################################
// Server instance settings
#define IOT_SERVER     "iothub.fogwing.net"
#define IOT_PUB_TOPIC  "fwent/edge/c506f7c0e07be86d/inbound"
#define MQTT_CLIENT_ID "1151-1659-1445-3867"
#define MQTT_USERNAME  "pzotester"
#define MQTT_PASS      "Bhasam123#"
// ############################# Wifi Related ###################################
#define DEF_WIFI_SSID  "TP-Link_50B6"
#define DEF_WIFI_PASS  "42374565"
#define BLE_PASS       "Bhasam"
#define WIFI_RETRY_MS  15000UL
//########################## Watchdog Time #################################
#define WDT_TIMEOUT 600 //10 Minutes wdt
// ############################# Pin Map ###################################
#define PIN_ALARM_BUZZ 4
// ##########################Sensors #########################################
#define COND_SENSOR_SLAVE_ID 3       //Default sensor Modbus slave ID
#define PH_SENSOR_SLAVE_ID 2       //Default sensor Modbus slave ID
#define DO_SENSOR_SLAVE_ID 1       //Default sensor Modbus slave ID
// ########################## GUI #########################################
#define LCD_UPDATE_TIME         2000 // LCD screen refresh period
#define NEXTION_BAUD_RATE     921600 //Nextion Baud rate
#define INTERVAL_LOWER_LIMIT       2 // Lower limit in minutes for off interval input
#define INTERVAL_UPPER_LIMIT    1440 // Upper limit in minutes for off interval input

// ####################################### EEPROM Map #######################################
#include "eeprom_map.h"

#define EEPROM_MAGIC_NUM        0x77 //Number to check for during first boot

// #################################### Modbus #####################################
#define MODBUS_BAUD      9600UL
// ##########################Serial ports and pins #########################################
#define USB    Serial2
#define MODBUS Serial1 // RX, TX
#define RXD2 16
#define TXD2 17
#define RXD1 32
#define TXD1 33

// ##########################SD File creation #########################################
#define fileHeader "Date, Time, FCL (mg/L)\n"
#define SDCSPIN 5 //ESP32 CS
#endif

