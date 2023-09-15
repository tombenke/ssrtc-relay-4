extern void setupTimer();
extern void checkTimerAlarm(void (*timerAlarmCb)(void));
extern void setDateTime();
extern String getTimeStr(String timeValue);
extern void getTimeOfDay(int *hour, int *minute);
