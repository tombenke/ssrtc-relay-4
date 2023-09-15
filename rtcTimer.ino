#include <DS3231.h>
#include "uUnixDate.h"

// myRTC interrupt pin
#define CLINT 2

// RTC
DS3231 myRTC;

///** Setup the time and an alarm to fire every second */
void setupTimer() {

    // Setup alarm one to fire every second
    myRTC.turnOffAlarm(1);
    myRTC.setA1Time(0, 0, 0, 0, 0b01111111, false, false, false);
    myRTC.turnOnAlarm(1);
    myRTC.checkIfAlarm(1);

}

/** Get the actual time in ISO 8601 format string representation */
void getTimeOfDay(int *hour, int *minute) {
    RTClib rtc;
    DateTime now = rtc.now();
    uUnixDate unixNow = uUnixDate(now.unixtime());
	////Serial.println(unixNow.timestamp());
    *hour = unixNow.hour();
    *minute = unixNow.minute();
}

/** Get the actual time in ISO 8601 format string representation */
String getTimeStr() {
    RTClib rtc;
    DateTime now = rtc.now();
    uUnixDate unixNow = uUnixDate(now.unixtime());
	//Serial.println(unixNow.timestamp());
    char buf[128];
    sprintf(buf, "%.4d-%.2d-%.2dT%.2d:%.2d:%.2d.000Z",
            unixNow.year(), unixNow.month(), unixNow.day(), unixNow.hour(), unixNow.minute(), unixNow.second());

    return String(buf);
}

/** Check if the RTC Alarm is fired, and call the callback function if yes */
void checkTimerAlarm(void (*timerAlarmCb)(void)) {
    // static variable to keep track of LED on/off state
    static byte state = false;

    // if alarm went off, do alarm stuff
    // first call to checkIFAlarm does not clear alarm flag
    if (myRTC.checkIfAlarm(1, false)) {
        state = ~state;
        ////digitalWrite(LED_BUILTIN, state);
        // Call the alarm callback function
        timerAlarmCb();

        // Clear alarm state
        myRTC.checkIfAlarm(1, true);
    }
}

/* Set the date and time to the RTC */
void setDateTime(String timeValue) {
    int year, month, day, hour, min, sec;
    sscanf(timeValue.c_str(), "%d-%d-%dT%d:%d:%d", &year, &month, &day, &hour, &min, &sec);
    char buf[128];
    sprintf(buf, "setDateTime: %.4d-%.2d-%.2dT%.2d:%.2d:%.2d.000Z", year, month, day, hour, min, sec);
    Serial.println(buf);
    uUnixDate newDate = uUnixDate(year, month, day, hour, min, sec);
	Serial.println(newDate.timestamp());
    myRTC.setEpoch(newDate.timestamp(), false);
}
