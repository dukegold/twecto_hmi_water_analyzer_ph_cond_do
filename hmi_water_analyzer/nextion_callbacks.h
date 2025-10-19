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
#ifndef NEXTION_CALLBACKS_H
#define NEXTION_CALLBACKS_H
#include "Nextion.h"
#include "Sys_Variables.h"
#include "display_ids.h"

char strbuf[20];
uint32_t tmpu32;

//Menu page buttons functions
#include "menu_callbacks.h"

//Cal page set button function
void b_cal_set_release(void *ptr){
  t_cal_cond_1.getText(strbuf,10);
  cond_cal1 = atof(strbuf);
  t_cal_cond_2.getText(strbuf,10);
  cond_cal2 = atof(strbuf);
  t_cal_cond_3.getText(strbuf,10);
  cond_cal3 = atof(strbuf);
  t_cal_ph_1.getText(strbuf,10);
  ph_cal1 = atof(strbuf);
  t_cal_ph_2.getText(strbuf,10);
  ph_cal2 = atof(strbuf);
  t_cal_ph_3.getText(strbuf,10);
  ph_cal3 = atof(strbuf);
  t_cal_tp_1.getText(strbuf,10);
  temperature_cal1 = atof(strbuf);
  t_cal_tp_2.getText(strbuf,10);
  temperature_cal2 = atof(strbuf);
  t_cal_tp_3.getText(strbuf,10);
  temperature_cal3 = atof(strbuf);
  t_cal_do_1.getText(strbuf,10);
  disox_cal1 = atof(strbuf);
  t_cal_do_2.getText(strbuf,10);
  disox_cal2 = atof(strbuf);
  t_cal_do_3.getText(strbuf,10);
  disox_cal3 = atof(strbuf);
  /* FIXME: write calibration registers */
  
  /* Span Calibration end */
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
  sprintf(strbuf,"page %d",MENU_PAGE);
  sendCommand(strbuf);
  recvRetCommandFinished();
}

//log cycle page buttons functions
void b_lcycle_set_release(void *ptr){
  log_choice_update = true;
  r_lcycle_c0.getValue(&tmpu32);
  log_choice = tmpu32?0:log_choice;
  r_lcycle_c1.getValue(&tmpu32);
  log_choice = tmpu32?1:log_choice;
  r_lcycle_c2.getValue(&tmpu32);
  log_choice = tmpu32?2:log_choice;
  r_lcycle_c3.getValue(&tmpu32);
  log_choice = tmpu32?3:log_choice;
  r_lcycle_c4.getValue(&tmpu32);
  log_choice = tmpu32?4:log_choice;
  r_lcycle_c5.getValue(&tmpu32);
  log_choice = tmpu32?5:log_choice;
  r_lcycle_c6.getValue(&tmpu32);
  log_choice = tmpu32?6:log_choice;
  eeprom.writeByte(EEP_LOG_CHOICE,log_choice);
  sprintf(strbuf,"page %d",MENU_PAGE);
  sendCommand(strbuf);
  recvRetCommandFinished();
}

//Password page button functions
void b_pass_enter_release(void *ptr){
  t_pass_pass.getText(strbuf,7);
  int len = 0;
  while(strbuf[len] != '\0')
    len++;
  if(len != 4){
    sprintf(strbuf,"page %d",WPASS_PAGE);
    sendCommand(strbuf);
    recvRetCommandFinished();
  }
  else{
    bool wrong_pass = false;
    for(int k = 0;k<4;k++)
      if(strbuf[k] != auth_pass[k])
        wrong_pass = true;
    if(wrong_pass){
      sprintf(strbuf,"page %d",WPASS_PAGE);
      sendCommand(strbuf);
      recvRetCommandFinished();
    }
    else{
        sprintf(strbuf,"page %d",CONF_PAGE);
        sendCommand(strbuf);
        recvRetCommandFinished();
        sprintf(strbuf,"%.2f",cond_ucutoff);
        t_conf_cond_uc.setText(strbuf);
        sprintf(strbuf,"%.2f",  cond_lcutoff);
        t_conf_cond_lc.setText(strbuf);
        sprintf(strbuf,"%.2f",  cond_thresh);
        t_conf_cond_th.setText(strbuf);
        sprintf(strbuf,"%.2f",  cond_mcal);
        t_conf_cond_cal.setText(strbuf);
        sprintf(strbuf,"%.2f",  ph_ucutoff);
        t_conf_ph_uc.setText(strbuf);
        sprintf(strbuf,"%.2f",  ph_lcutoff);
        t_conf_ph_lc.setText(strbuf);
        sprintf(strbuf,"%.2f",  ph_thresh);
        t_conf_ph_th.setText(strbuf);
        sprintf(strbuf,"%.2f",  ph_mcal);
        t_conf_ph_cal.setText(strbuf);
        sprintf(strbuf,"%.2f",  temperature_ucutoff);
        t_conf_tp_uc.setText(strbuf);
        sprintf(strbuf,"%.2f",  temperature_lcutoff);
        t_conf_tp_lc.setText(strbuf);
        sprintf(strbuf,"%.2f",  temperature_thresh);
        t_conf_tp_th.setText(strbuf);
        sprintf(strbuf,"%.2f",  temperature_mcal);
        t_conf_tp_cal.setText(strbuf);
        sprintf(strbuf,"%.2f",  disox_ucutoff);
        t_conf_do_uc.setText(strbuf);
        sprintf(strbuf,"%.2f",  disox_lcutoff);
        t_conf_do_lc.setText(strbuf);
        sprintf(strbuf,"%.2f",  disox_thresh);
        t_conf_do_th.setText(strbuf);
        sprintf(strbuf,"%.2f",  disox_mcal);
        t_conf_do_cal.setText(strbuf);
    }
  }
}

//Wifi setup page button functions
void b_wsetup_set_release(void *ptr){
  t_wsetup_ssid.getText(wifi_ssid,40);
  t_wsetup_pass.getText(wifi_password,40);
  for(int i=0;i<40;i++){
    eeprom.writeByte(EEP_WIFI_SSID+i,wifi_ssid[i]);
    eeprom.writeByte(EEP_WIFI_PASS+i,wifi_password[i]);
  }
  sprintf(strbuf,"page %d",MENU_PAGE);
  sendCommand(strbuf);
  recvRetCommandFinished();
}

//Configuration page functions
void b_conf_set_release(void *ptr){
  t_conf_cond_uc.getText(strbuf,10);
  cond_ucutoff = atof(strbuf);
  t_conf_cond_lc.getText(strbuf,10);
  cond_lcutoff = atof(strbuf);
  t_conf_cond_th.getText(strbuf,10);
  cond_thresh = atof(strbuf);
  t_conf_cond_cal.getText(strbuf,10);
  cond_mcal = atof(strbuf);
  t_conf_ph_uc.getText(strbuf,10);
  ph_ucutoff = atof(strbuf);
  t_conf_ph_lc.getText(strbuf,10);
  ph_lcutoff = atof(strbuf);
  t_conf_ph_th.getText(strbuf,10);
  ph_thresh = atof(strbuf);
  t_conf_ph_cal.getText(strbuf,10);
  ph_mcal = atof(strbuf);
  t_conf_tp_uc.getText(strbuf,10);
  temperature_ucutoff = atof(strbuf);
  t_conf_tp_lc.getText(strbuf,10);
  temperature_lcutoff = atof(strbuf);
  t_conf_tp_th.getText(strbuf,10);
  temperature_thresh = atof(strbuf);
  t_conf_tp_cal.getText(strbuf,10);
  temperature_mcal = atof(strbuf);
  t_conf_do_uc.getText(strbuf,10);
  disox_ucutoff = atof(strbuf);
  t_conf_do_lc.getText(strbuf,10);
  disox_lcutoff = atof(strbuf);
  t_conf_do_th.getText(strbuf,10);
  disox_thresh = atof(strbuf);
  t_conf_do_cal.getText(strbuf,10);
  disox_mcal = atof(strbuf);
  
  //EEPROM Update
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
  sprintf(strbuf,"page %d",MENU_PAGE);
  sendCommand(strbuf);
  recvRetCommandFinished();
}

//Time page functions
void b_time_set_release(void *ptr){
  t_time_day.getValue(&tmpu32);
  monthday = tmpu32;
  t_time_month.getValue(&tmpu32);
  month = tmpu32;
  t_time_year.getValue(&tmpu32);
  year = tmpu32-2000;
  t_time_hour.getValue(&tmpu32);
  hour = tmpu32;
  t_time_min.getValue(&tmpu32);
  minute = tmpu32;
  update_rtc_time = true;
  force_lcd_update = true;
  sprintf(strbuf,"page %d",HOME_PAGE);
  sendCommand(strbuf);
  recvRetCommandFinished();
}
NexTouch *nex_listen_list[] = {
  &b_menu_minfo  ,
  &b_menu_cal    ,
  &b_menu_lcycle ,
  &b_menu_wsetup ,
  &b_cal_set	 ,
  &b_pass_enter  ,
  &b_lcycle_set	 ,
  &b_wsetup_set	 ,
  &b_conf_set	 ,
  &b_time_set    ,
  NULL
};
#endif
