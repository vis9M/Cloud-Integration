#ifndef TASKS_DATA_H
#define TASKS_DATA_H

#include "FreeRTOS.h"
#include "semphr.h"
//LEAVING THE COMMENTS FROM CHATGPT TO HELP
// Already existing: SystemObjects, tasks_return, etc.

// Cloud data for ThingSpeak
struct CloudData {
    int co2_setpoint;          // from TalkBack
    SemaphoreHandle_t mutex;   // protects access
};

extern CloudData g_cloud;

#endif
