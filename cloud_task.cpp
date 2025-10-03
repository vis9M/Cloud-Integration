#include "tasks_data.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string>
#include <cstdio>

// Wi-Fi + HTTP client library goes here (depends on what you use).
// For now, we’ll leave placeholders.

#define THINGSPEAK_CHANNEL_ID  "3096934"
#define THINGSPEAK_WRITE_KEY   "YO0TAVW1DJGASJTO"
#define THINGSPEAK_READ_KEY    "4HHJZIUCFUQXF3BT"
#define TALKBACK_ID            "55399"
#define TALKBACK_API_KEY       "MAYI4DHFO3V1R22O"

extern "C" void cloud_task(void *param) {
    auto *cloud = static_cast<CloudData*>(param);

    while (true) {
        // 🔹 1. Read local sensor values (from tasks_return or sys)
        // For now just placeholders
        float co2_val = 0;   // <- replace with sys->co2_return
        float temp_val = 0;  // <- replace with sys->t_return
        float rh_val   = 0;  // <- replace with sys->rh_return

        // 🔹 2. Send to ThingSpeak (HTTP POST)
        printf("Uploading to ThingSpeak: CO2=%.1f, Temp=%.1f, RH=%.1f\n",
               co2_val, temp_val, rh_val);

        // http_post("https://api.thingspeak.com/update",
        //           "api_key=" THINGSPEAK_WRITE_KEY "&field1=...");

        // 🔹 3. Check TalkBack for new setpoint
        // Simulate fetching a command string "1200"
        std::string command_str = "1200";  // Replace with real GET
        int new_setpoint = atoi(command_str.c_str());

        if (new_setpoint > 0) {
            xSemaphoreTake(cloud->mutex, portMAX_DELAY);
            cloud->co2_setpoint = new_setpoint;
            xSemaphoreGive(cloud->mutex);

            printf("Updated CO2 setpoint from TalkBack: %d ppm\n", new_setpoint);
        }

        // Run every 30 seconds
        vTaskDelay(pdMS_TO_TICKS(30000));
    }
}
