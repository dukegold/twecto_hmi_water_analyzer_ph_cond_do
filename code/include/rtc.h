#ifndef RTC_H
#define RTC_H

#include "uRTCLib.h"

byte decToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}

byte bcdToDec(byte val) {
  return ((val / 16 * 10) + (val % 16));
}
void readTime(uRTCLib *rtc, byte *second,byte *minute, byte *hour,byte *weekday, byte *monthday, byte *month, byte *year) {
  rtc->refresh();
  *second   = rtc->second();
  *minute   = rtc->minute();
  *hour     = rtc->hour();
  *weekday  = rtc->dayOfWeek();
  *monthday = rtc->day();
  *month    = rtc->month();
  *year     = rtc->year();
}

void setRTCTime(uRTCLib *rtc, byte second, byte minute, byte hour, byte weekday, byte monthday, byte month, byte year) {
  rtc->set(second, minute, hour, weekday, monthday, month, year);
}

void getDateTime(uRTCLib *rtc, char *buf) {
  rtc->refresh();
  uint8_t second, minute,hour,weekday,monthday,month,year;
  second   = rtc->second();
  minute   = rtc->minute();
  hour     = rtc->hour();
  weekday  = rtc->dayOfWeek();
  monthday = rtc->day();
  month    = rtc->month();
  year     = rtc->year();
  sprintf(buf,"%02d-%02d-%02d %02d:%02d",monthday,month,year,hour,minute);
}

void getMonthYear(uRTCLib *rtc, char *buf) {
  rtc->refresh();
  uint8_t second, minute,hour,weekday,monthday,month,year;
  second   = rtc->second();
  minute   = rtc->minute();
  hour     = rtc->hour();
  weekday  = rtc->dayOfWeek();
  monthday = rtc->day();
  month    = rtc->month();
  year     = rtc->year();
  sprintf(buf,"%02d_%02d ",month,year);
}

void getDate(uRTCLib *rtc, char *buf) {
  rtc->refresh();
  uint8_t second, minute,hour,weekday,monthday,month,year;
  second   = rtc->second();
  minute   = rtc->minute();
  hour     = rtc->hour();
  weekday  = rtc->dayOfWeek();
  monthday = rtc->day();
  month    = rtc->month();
  year     = rtc->year();
  sprintf(buf,"%02d-%02d-%02d ",monthday,month,year);
}

void getTime(uRTCLib *rtc, char *buf) {
  rtc->refresh();
  uint8_t second, minute,hour,weekday,monthday,month,year;
  second   = rtc->second();
  minute   = rtc->minute();
  hour     = rtc->hour();
  weekday  = rtc->dayOfWeek();
  monthday = rtc->day();
  month    = rtc->month();
  year     = rtc->year();
  sprintf(buf,"%02d:%02d ",hour,minute);
}
void getDateFullc(uRTCLib *rtc, char *buf) {
  rtc->refresh();
  uint8_t second, minute,hour,weekday,monthday,month,year;
  second   = rtc->second();
  minute   = rtc->minute();
  hour     = rtc->hour();
  weekday  = rtc->dayOfWeek();
  monthday = rtc->day();
  month    = rtc->month();
  year     = rtc->year();
  sprintf(buf, "%02d/%02d/%02d %02d:%02d",monthday,month,year,hour,minute);
}
#endif
