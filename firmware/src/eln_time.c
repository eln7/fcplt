#include "definitions.h"

time_t time(time_t *tod) { 
    time_t t;
   //t = (time_t)SYS_TIME_CounterGet();
   t = (time_t)xTaskGetTickCount()/configTICK_RATE_HZ;
    if (tod != NULL) *tod = t;  
    return t;
 }