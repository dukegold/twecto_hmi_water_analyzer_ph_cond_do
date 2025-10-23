/**
 * @file pinmap.h
 *
 * The header file includes all the pin definitions used on the ESP32.
 * 
 * @author  Aftab Usmani (email:<usmani12345@gmail.com>)
 * @date    2022/14/3
 * @copyright 
 * Copyright (C) 2019-2022 Twecto Solutions PVT. Ltd. \n
 */
#ifndef PINMAP_H
#define PINMAP_H
/*************************************************
 * Buzzer Pin Defs
 * Buzzer for generating alarm.
 *************************************************/
#define PIN_BUZZ_ALARM          14

/*************************************************
 * Pin for putting Nextion in lowpower mode when
 * lid is closed.
 *************************************************/
#define PIN_LID_CLOSE           34
/*************************************************
 * UART Pin Defs
 * Serial2: Used for Nextion HMI interface. Set in NexConfig.h library file
 * Serial1: Used for CL sensor RS-485.
 * Serial: Used for serial debug.
 *************************************************/
#define PIN_HMI_TX   17
#define PIN_HMI_RX   16
//#define PIN_PC_TX    1
//#define PIN_PC_RX    3
#define PIN_CL_TX   33
#define PIN_CL_RX   32
#endif PINMAP_H