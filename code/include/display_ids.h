/**
 * @file display_ids.h
 *
 * The header file includes all the object IDs from the hmi file.
 * 
 * @author  Aftab Usmani (email:<usmani12345@gmail.com>)
 * @date    01/10/2023
 * @copyright 
 * Copyright (C) 2019-2023 Twecto Solutions PVT. Ltd. \n
 */
#ifndef DISPLAY_IDS_H
#define DISPLAY_IDS_H
//Page IDs
#define TITLE_PAGE         0
#define HOME_PAGE          1
#define MENU_PAGE          2
#define MINFO_PAGE         3
#define WSETUP_PAGE	   4
#define LCYCLE_PAGE        5
#define PASS_PAGE	   6
#define WPASS_PAGE	   7
#define CONF_PAGE	   8
#define CAL_PAGE           9
#define TIME_PAGE	   10

/*************************************
 **************Button IDs*************
 *************************************/
//Main page
#define B_MAIN_MENU            14 //Button to enter the Settings Menu
//Menu page
#define B_MENU_HOME            6  // Home button
#define B_MENU_MINFO           1  // Machine Information button
#define B_MENU_CAL             7  // Calibration button
#define B_MENU_LCYCLE          4  // Log Cycle button
#define B_MENU_WSETUP          2  // Wifi Setup button
#define B_MENU_CONF            3  // Configuration Menu button
//Machine Info page
#define B_MINFO_HOME           7  //Home button
#define B_MINFO_BACK           6  //Back button
//Cal Page
#define B_CAL_HOME             3  //Home button
#define B_CAL_BACK             2  //Back button
#define B_CAL_SET              23 //Set button
//Password page
#define B_PASS_ENTER           5  //Enter Button
//Log Cycle page
#define B_LCYCLE_HOME          2  //Home button
#define B_LCYCLE_BACK          3  //Back button
#define B_LCYCLE_SET           4  //Set selected log cycle button
//Wifi Setup page
#define B_WSETUP_HOME          2  //Home button
#define B_WSETUP_BACK          3  //Back button
#define B_WSETUP_SET           8  //Set entered Wifi credentials button
//Configuration page
#define B_CONF_HOME            2  //Home button
#define B_CONF_BACK            3  //Back button
#define B_CONF_SET             6  //Set selected configuration button
//Time set page
#define B_TIME_SET             5 //Time set button
#define B_TIME_BACK            2 //Time set button

/*************************************
 ************Text Box IDs*************
 *************************************/
//Main Info page
#define T_MAIN_PH_VAL           15  //pH value display
#define T_MAIN_COND_VAL          10  //ORP value display
#define T_MAIN_TP_VAL           11  //Temperature value display
#define T_MAIN_DO_VAL           19  //Dissolve Oxygen value display
#define T_MAIN_TIME_VAL         18  //Time Date value display
//Machine Info page 
#define T_MINFO_MID             8  //Machine ID
#define T_MINFO_IP              9  //IP Address
//Cal page 
#define T_CAL_COND_1              5  //Current Value
#define T_CAL_COND_2              8  //Current Value
#define T_CAL_COND_3              9  //Current Value
#define T_CAL_PH_1              13  //Measured Value
#define T_CAL_PH_2              14  //Measured Value
#define T_CAL_PH_3              15  //Measured Value
#define T_CAL_TP_1              16  //Measured Value
#define T_CAL_TP_2              17  //Measured Value
#define T_CAL_TP_3              18  //Measured Value
#define T_CAL_DO_1              10  //Measured Value
#define T_CAL_DO_2              11  //Measured Value
#define T_CAL_DO_3              12  //Measured Value
//Password page
#define T_PASS_PASS              4 //Password entry
//Wifi setup page
#define T_WSETUP_SSID           4  //Wifi SSID
#define T_WSETUP_PASS           5  //Wifi Password
//Configuration page
#define T_CONF_COND_UC           5  //Upper Cutoff
#define T_CONF_COND_LC           10  //Lower Cutoff
#define T_CONF_COND_TH           11  //Threshold
#define T_CONF_COND_CAL          12  //Calibration Factor
#define T_CONF_PH_UC            17  //Upper Cutoff
#define T_CONF_PH_LC            18  //Lower Cutoff
#define T_CONF_PH_TH            19  //Threshold
#define T_CONF_PH_CAL           20  //Calibration Factor
#define T_CONF_TP_UC            21  //Upper Cutoff
#define T_CONF_TP_LC            22  //Lower Cutoff
#define T_CONF_TP_TH            23  //Threshold
#define T_CONF_TP_CAL           24  //Calibration Factor
#define T_CONF_DO_UC            13  //Upper Cutoff
#define T_CONF_DO_LC            14  //Lower Cutoff
#define T_CONF_DO_TH            15  //Threshold
#define T_CONF_DO_CAL           16  //Calibration Factor
//Time set page
#define T_TIME_DAY              6 // Day field
#define T_TIME_MON              8 // Month field
#define T_TIME_YEAR             9 // Year field
#define T_TIME_HOUR            12 // Hour field
#define T_TIME_MIN             13 // Minute field
/*************************************
 **********Radio Button IDs***********
 *************************************/
//Log Cycle page
#define R_LCYCLE_C0            5 //Choice 0 
#define R_LCYCLE_C1            7 //Choice 1 
#define R_LCYCLE_C2            9 //Choice 2 
#define R_LCYCLE_C3           11 //Choice 3 
#define R_LCYCLE_C4           13 //Choice 4 
#define R_LCYCLE_C5           15 //Choice 5 
#define R_LCYCLE_C6           17 //Choice 6 
/*************************************
 ************Combo Box IDs************
 *************************************/
//Log Cycle page
//#define L_LCYCLE_VAL            3  //Log Cycle value
/*************************************
 **************Picture IDs************
 *************************************/
//Main Page
#define PIC_MAIN_WIFI           16 //Wifi available picture
/*************************************
 **************Gauge IDs**************
 *************************************/

#endif
