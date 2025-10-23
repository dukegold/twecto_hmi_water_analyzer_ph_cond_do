/**
 * @file menu_callbacks.h
 *
 * The header file includes all the functions invoked by
 * Components from the Settings page. 
 *
 * @author  Aftab Usmani (email:<usmani12345@gmail.com>)
 * @date    2023/10/1
 * @copyright 
 * Copyright (C) 2019-2023 Twecto Solutions PVT. Ltd. \n
 */
#ifndef MENU_CALLBACKS_H
#define MENU_CALLBACKS_H
#include "Sys_Variables.h"
void b_menu_minfo_release(void *ptr){
  sprintf(strbuf,"page %d",MINFO_PAGE);
  sendCommand(strbuf);
  recvRetCommandFinished();
  t_minfo_mid.setText(DEVICE_ID);
  t_minfo_ip.setText(WiFi.localIP().toString().c_str());
}

void b_menu_cal_release(void *ptr){
  sprintf(strbuf,"page %d",CAL_PAGE);
  sendCommand(strbuf);
  recvRetCommandFinished();
  sprintf(strbuf,"%.2f",cond_cal1);
  t_cal_cond_1.setText(strbuf);
  sprintf(strbuf,"%.2f",cond_cal2);
  t_cal_cond_2.setText(strbuf);
  sprintf(strbuf,"%.2f",cond_cal3);
  t_cal_cond_3.setText(strbuf);
  sprintf(strbuf,"%.2f",ph_cal1);
  t_cal_ph_1.setText(strbuf);
  sprintf(strbuf,"%.2f",ph_cal2);
  t_cal_ph_2.setText(strbuf);
  sprintf(strbuf,"%.2f",ph_cal3);
  t_cal_ph_3.setText(strbuf);
  sprintf(strbuf,"%.2f",temperature_cal1);
  t_cal_tp_1.setText(strbuf);
  sprintf(strbuf,"%.2f",temperature_cal2);
  t_cal_tp_2.setText(strbuf);
  sprintf(strbuf,"%.2f",temperature_cal3);
  t_cal_tp_3.setText(strbuf);
  sprintf(strbuf,"%.2f",disox_cal1);
  t_cal_do_1.setText(strbuf);
  sprintf(strbuf,"%.2f",disox_cal2);
  t_cal_do_2.setText(strbuf);
  sprintf(strbuf,"%.2f",disox_cal3);
  t_cal_do_3.setText(strbuf);
}


void b_menu_lcycle_release(void *ptr){
  sprintf(strbuf,"page %d",LCYCLE_PAGE);
  sendCommand(strbuf);
  recvRetCommandFinished();
  r_lcycle_c0.setValue(log_choice==0);
  r_lcycle_c1.setValue(log_choice==1);
  r_lcycle_c2.setValue(log_choice==2);
  r_lcycle_c3.setValue(log_choice==3);
  r_lcycle_c4.setValue(log_choice==4);
  r_lcycle_c5.setValue(log_choice==5);
  r_lcycle_c6.setValue(log_choice==6);
}
void b_menu_wsetup_release(void *ptr){
  sprintf(strbuf,"page %d",WSETUP_PAGE);
  sendCommand(strbuf);
  recvRetCommandFinished();
  t_wsetup_ssid.setText(wifi_ssid);
  t_wsetup_pass.setText(wifi_password);
}
#endif
