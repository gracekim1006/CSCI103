#ifndef CLOCK_H
#define CLOCK_H

class Clock {
  public:
    //Default Constructor
     Clock();
     //Constructor
     Clock(int, int, int);
     void setTime(int, int, int);
     void setAlarm(int, int, int);
     //Turns alarm on/off
     void toggleAlarm();
     //Checks to see if Alarm time is equal to Current Time
     bool checkAlarm();
     void printTime();
     void snoozeAlarm();
     void tick();
  
  private:
     int ch, cm, cs;
     int ah, am, as;
     bool alarmOn;
};

 #endif