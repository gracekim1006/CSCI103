#include "clock.h"
#include <iostream> 

using namespace std;

 Clock::Clock()
 {
   ch=12; cm=0; cs=0;
   ah=12; am=0; as=0;
 }
 Clock::Clock(int h, int m, int s)
 {
   ch = h; cm = m; cs = s;
   ah=12; am=0; as=0;
   alarmOn = false;
 }
 
 void Clock::setTime(int h, int m, int s)
 {
   ch = h; cm = m; cs = s;
 }
 
 void Clock::setAlarm(int h, int m, int s)
 {
   ah = h; am = m; as = s;
 }
 void Clock::toggleAlarm()
 {
   alarmOn = !alarmOn;
 }
 bool Clock::checkAlarm()
 {
   return (ch==ah) && (cm == am) && (cs == as);
 }
 void Clock::printTime()
 {
   cout << ch << ":" << cm << ":" << cs << endl;
 }
 void Clock::snoozeAlarm()
 {
   am+=5;
   //roll over to hours
 }
 void Clock::tick()
 {
   cs++;
   //roll seconds to minutes
   //roll minutes to hours
 }
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
