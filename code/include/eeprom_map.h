#ifndef EEPROM_MAP_H
#define EEPROM_MAP_H
#define EEP_COND_MCAL             0    // Nh3 Manual offset Calibration
#define EEP_COND_UCUTOFF          4    // Nh3 Upper Cutoff
#define EEP_COND_LCUTOFF          8    // Nh3 Lower Cutoff
#define EEP_COND_THRESH           12   // Nh3 Threshold
#define EEP_DISOX_MCAL           16   // disox Manual offset Calibration
#define EEP_DISOX_UCUTOFF        20   // disox Upper Cutoff
#define EEP_DISOX_LCUTOFF        24   // disox Lower Cutoff
#define EEP_DISOX_THRESH         28   // disox Threshold
#define EEP_PH_MCAL              32   // ph Manual offset Calibration
#define EEP_PH_UCUTOFF           36   // ph Upper Cutoff
#define EEP_PH_LCUTOFF           40   // ph Lower Cutoff
#define EEP_PH_THRESH            44   // ph Threshold
#define EEP_TEMPERATURE_MCAL     48   // temperature Manual offset Calibration
#define EEP_TEMPERATURE_UCUTOFF  52   // temperature Upper Cutoff
#define EEP_TEMPERATURE_LCUTOFF  56   // temperature Lower Cutoff
#define EEP_TEMPERATURE_THRESH   60   // temperature Threshold
#define EEP_COND_CAL1             64   // Nh3 Calibration point 1
#define EEP_COND_CAL2             68   // Nh3 Calibration point 2
#define EEP_COND_CAL3             72   // Nh3 Calibration point 3
#define EEP_DISOX_CAL1           76   // disox Calibration point 1
#define EEP_DISOX_CAL2           80   // disox Calibration point 2
#define EEP_DISOX_CAL3           84   // disox Calibration point 3
#define EEP_PH_CAL1              88   // ph Calibration point 1
#define EEP_PH_CAL2              92   // ph Calibration point 2
#define EEP_PH_CAL3              96   // ph Calibration point 3
#define EEP_TEMPERATURE_CAL1     100  // temperature Calibration point 1
#define EEP_TEMPERATURE_CAL2     104  // temperature Calibration point 2
#define EEP_TEMPERATURE_CAL3     108  // temperature Calibration point 3
#define EEP_PRE_HR               112  // Previous logging hour.
#define EEP_DATA_SENT            113  // Data sent in the current hour.
#define EEP_LOG_CHOICE           114  // Logging interval selection.
#define EEP_LAST_DAY             118  // Last day when logging was done.
#define EEP_LOG_SLOTS            119  // Current slots where logging has/has not occurred.
#define EEP_WIFI_SSID            123  // Wi-Fi SSID.
#define EEP_WIFI_PASS            163  // Wi-Fi Password.
#define EEP_MAGIC_NUM            203  // Magic number to load EEPROM defaults.
#endif
