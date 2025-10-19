/*
 * @file display_objects.h
 *
 * The header file includes all the object IDs from the hmi file.
 * 
 * @author  Aftab Usmani (email:<usmani12345@gmail.com>)
 * @date    2022/14/3
 * @copyright 
 * Copyright (C) 2019-2022 Twecto Solutions PVT. Ltd.
 */

#ifndef DISPLAY_OBJECTS_H
#define DISPLAY_OBJECTS_H
#include "display_ids.h"

/*************************************
 **************Page objects***********
 *************************************/
NexPage p_title      = NexPage(TITLE_PAGE       ,0,"Title");
NexPage p_main       = NexPage(HOME_PAGE        ,0,"Home");
NexPage p_menu       = NexPage(MENU_PAGE        ,0,"Menu");	    
NexPage p_minfo      = NexPage(MINFO_PAGE       ,0,"Machine_Info");  
NexPage p_wsetup     = NexPage(WSETUP_PAGE      ,0,"Wifi_Setting"); 
NexPage p_lcycle     = NexPage(LCYCLE_PAGE      ,0,"Log_Cycle"); 
NexPage p_pass       = NexPage(PASS_PAGE        ,0,"Password"); 
NexPage p_wpass      = NexPage(WPASS_PAGE       ,0,"WPass"); 
NexPage p_conf       = NexPage(CONF_PAGE        ,0,"Configuration"); 
NexPage p_cal        = NexPage(CAL_PAGE         ,0,"Calibration"); 
NexPage p_time       = NexPage(TIME_PAGE        ,0,"SDtime");
   

/*************************************
 *************Button objects**********
 *************************************/
//Main page
NexButton b_main_menu   = NexButton(HOME_PAGE, B_MAIN_MENU     ,"b0");
//Menu page
NexButton b_menu_home   = NexButton(MENU_PAGE, B_MENU_HOME     ,"b4");
NexButton b_menu_minfo  = NexButton(MENU_PAGE, B_MENU_MINFO    ,"b0");
NexButton b_menu_cal    = NexButton(MENU_PAGE, B_MENU_CAL      ,"b6");
NexButton b_menu_lcycle = NexButton(MENU_PAGE, B_MENU_LCYCLE   ,"b3");
NexButton b_menu_wsetup = NexButton(MENU_PAGE, B_MENU_WSETUP   ,"b1");
NexButton b_menu_conf   = NexButton(MENU_PAGE, B_MENU_CONF     ,"b2");
//Machine Info page
NexButton b_minfo_home  = NexButton(MINFO_PAGE, B_MINFO_HOME   ,"b4");
NexButton b_minfo_back  = NexButton(MINFO_PAGE, B_MINFO_BACK   ,"b5");
//Cal Page
NexButton b_cal_home    = NexButton(CAL_PAGE , B_CAL_HOME      ,"b4");
NexButton b_cal_back    = NexButton(CAL_PAGE , B_CAL_BACK      ,"b5");
NexButton b_cal_set     = NexButton(CAL_PAGE , B_CAL_SET       ,"b1");
//Password Page
NexButton b_pass_enter  = NexButton(PASS_PAGE , B_PASS_ENTER   ,"b0");
//Log Cycle page
NexButton b_lcycle_home = NexButton(LCYCLE_PAGE, B_LCYCLE_HOME ,"b4");
NexButton b_lcycle_back = NexButton(LCYCLE_PAGE, B_LCYCLE_BACK ,"b5");
NexButton b_lcycle_set  = NexButton(LCYCLE_PAGE, B_LCYCLE_SET  ,"b0");
//Wifi Setup page
NexButton b_wsetup_home = NexButton(WSETUP_PAGE, B_WSETUP_HOME ,"b4");
NexButton b_wsetup_back = NexButton(WSETUP_PAGE, B_WSETUP_BACK ,"b5");
NexButton b_wsetup_set  = NexButton(WSETUP_PAGE, B_WSETUP_SET  ,"b0");
//Configuration page
NexButton b_conf_home   = NexButton(CONF_PAGE, B_CONF_HOME     ,"b4");
NexButton b_conf_back   = NexButton(CONF_PAGE, B_CONF_BACK     ,"b5");
NexButton b_conf_set    = NexButton(CONF_PAGE, B_CONF_SET      ,"b0");
//Time set 
NexButton b_time_set    = NexButton(TIME_PAGE,  B_TIME_SET     ,"b0");
NexButton b_time_back   = NexButton(TIME_PAGE,  B_TIME_BACK    ,"b5");


/*************************************
 ************Textbox objects**********
 *************************************/
//Main Info page
NexText t_main_ph_val   = NexText(HOME_PAGE, T_MAIN_PH_VAL     ,"t9");
NexText t_main_cond_val   = NexText(HOME_PAGE, T_MAIN_COND_VAL     ,"t6");
NexText t_main_tp_val   = NexText(HOME_PAGE, T_MAIN_TP_VAL     ,"t7");
NexText t_main_do_val   = NexText(HOME_PAGE, T_MAIN_DO_VAL     ,"t8");
NexText t_main_time_val = NexText(HOME_PAGE, T_MAIN_TIME_VAL   ,"t14");
//Machine info page
NexText t_minfo_mid     = NexText(MINFO_PAGE, T_MINFO_MID      ,"t5");
NexText t_minfo_ip      = NexText(MINFO_PAGE, T_MINFO_IP       ,"t6");
//Cal page
NexText t_cal_cond_1      = NexText(CAL_PAGE, T_CAL_COND_1         ,"t1");
NexText t_cal_cond_2      = NexText(CAL_PAGE, T_CAL_COND_2         ,"t7");
NexText t_cal_cond_3      = NexText(CAL_PAGE, T_CAL_COND_3         ,"t8");
NexText t_cal_ph_1      = NexText(CAL_PAGE, T_CAL_PH_1         ,"t13");
NexText t_cal_ph_2      = NexText(CAL_PAGE, T_CAL_PH_2         ,"t14");
NexText t_cal_ph_3      = NexText(CAL_PAGE, T_CAL_PH_3         ,"t15");
NexText t_cal_tp_1      = NexText(CAL_PAGE, T_CAL_TP_1         ,"t17");
NexText t_cal_tp_2      = NexText(CAL_PAGE, T_CAL_TP_2         ,"t18");
NexText t_cal_tp_3      = NexText(CAL_PAGE, T_CAL_TP_3         ,"t19");
NexText t_cal_do_1      = NexText(CAL_PAGE, T_CAL_DO_1         ,"t2");
NexText t_cal_do_2      = NexText(CAL_PAGE, T_CAL_DO_2         ,"t10");
NexText t_cal_do_3      = NexText(CAL_PAGE, T_CAL_DO_3         ,"t11");
//Password page
NexText t_pass_pass     = NexText(PASS_PAGE, T_PASS_PASS        ,"t1");
//Wifi setup page
NexText t_wsetup_ssid   = NexText(WSETUP_PAGE, T_WSETUP_SSID   ,"t1");  
NexText t_wsetup_pass   = NexText(WSETUP_PAGE, T_WSETUP_PASS   ,"t2");  
//Configuration page
NexText t_conf_cond_uc    = NexText(CONF_PAGE, T_CONF_COND_UC      ,"t1");
NexText t_conf_cond_lc    = NexText(CONF_PAGE, T_CONF_COND_LC      ,"t7");
NexText t_conf_cond_th    = NexText(CONF_PAGE, T_CONF_COND_TH      ,"t8");
NexText t_conf_cond_cal   = NexText(CONF_PAGE, T_CONF_COND_CAL     ,"t9");
NexText t_conf_ph_uc    = NexText(CONF_PAGE, T_CONF_PH_UC      ,"t13");
NexText t_conf_ph_lc    = NexText(CONF_PAGE, T_CONF_PH_LC      ,"t14");
NexText t_conf_ph_th    = NexText(CONF_PAGE, T_CONF_PH_TH      ,"t15");
NexText t_conf_ph_cal   = NexText(CONF_PAGE, T_CONF_PH_CAL     ,"t16");
NexText t_conf_tp_uc    = NexText(CONF_PAGE, T_CONF_TP_UC      ,"t17");
NexText t_conf_tp_lc    = NexText(CONF_PAGE, T_CONF_TP_LC      ,"t18");
NexText t_conf_tp_th    = NexText(CONF_PAGE, T_CONF_TP_TH      ,"t19");
NexText t_conf_tp_cal   = NexText(CONF_PAGE, T_CONF_TP_CAL     ,"t20");
NexText t_conf_do_uc    = NexText(CONF_PAGE, T_CONF_DO_UC      ,"t2");
NexText t_conf_do_lc    = NexText(CONF_PAGE, T_CONF_DO_LC      ,"t10");
NexText t_conf_do_th    = NexText(CONF_PAGE, T_CONF_DO_TH      ,"t11");
NexText t_conf_do_cal   = NexText(CONF_PAGE, T_CONF_DO_CAL     ,"t12");
//Time set page
NexNumber t_time_day    = NexNumber(TIME_PAGE, T_TIME_DAY      ,"n0");
NexNumber t_time_month  = NexNumber(TIME_PAGE, T_TIME_MON      ,"n1");
NexNumber t_time_year   = NexNumber(TIME_PAGE, T_TIME_YEAR     ,"n2");
NexNumber t_time_hour   = NexNumber(TIME_PAGE, T_TIME_HOUR     ,"n3");
NexNumber t_time_min    = NexNumber(TIME_PAGE, T_TIME_MIN      ,"n4");

/*************************************
 ********Radio Button objects*********
 *************************************/
NexRadio r_lcycle_c0 = NexRadio(LCYCLE_PAGE, R_LCYCLE_C0 ,"r0");  
NexRadio r_lcycle_c1 = NexRadio(LCYCLE_PAGE, R_LCYCLE_C1 ,"r1");  
NexRadio r_lcycle_c2 = NexRadio(LCYCLE_PAGE, R_LCYCLE_C2 ,"r2");  
NexRadio r_lcycle_c3 = NexRadio(LCYCLE_PAGE, R_LCYCLE_C3 ,"r3");  
NexRadio r_lcycle_c4 = NexRadio(LCYCLE_PAGE, R_LCYCLE_C4 ,"r4");  
NexRadio r_lcycle_c5 = NexRadio(LCYCLE_PAGE, R_LCYCLE_C5 ,"r5");  
NexRadio r_lcycle_c6 = NexRadio(LCYCLE_PAGE, R_LCYCLE_C6 ,"r6");  

/*************************************
 ************Guage objects************
 *************************************/
//Main page
//NexGauge ga_main_cl_val     = NexGauge(MAIN_PAGE,GA_MAIN_CL_VAL,"z0");
/*************************************
 *************Image objects***********
 *************************************/
//Main page
NexPicture p_main_wifi      = NexPicture(HOME_PAGE,PIC_MAIN_WIFI,"p0");				       
/*************************************
 ***********Combobox objects**********
 *************************************/
//Log Cycle page
//const char l_lcycle_val_cid[] = "cb0";
// Not available in Arduino library. Needs to be parsed Manually

#endif
