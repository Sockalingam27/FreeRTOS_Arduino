-------------------------------------------------------------------
//Using only 1 core for learning purpose
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

-------------------------------------------------------------------
This is written to make sure only one core of the ESP32 Wrover is used. Since learning FreeRTOS with 2 cores would be tuf ? i donno see


-------------------------------------------------------------------
// Task: Blink an LED
void toggleLED(void *parameter)
{
  while(1)
  {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(led_pin,LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
    }
}
-------------------------------------------------------------------
Now we define something called as task, task is the soul of FreeRTOS
a program has so many Tasks of which each will be for a particular task,  say its more like a fn diff fn diff work
And all of these tasks run separately.

Here something called vTaskDelay is used which is a particular delay used for FreeRTOS and not the normal delay() fn.
500 is the amt milliseconds we ewant to delay and the portTICK_PERIOD_MS is the tick timer present in the controller which makes sure the particular milliseconds is reached.


-------------------------------------------------------------------
 //Task to run forever
  xTaskCreatePinnedToCore(                  // xTaskCreate is used for vanilla FreeRTOS
                      toggleLED,            // Name of fn that is being called
                      "Toggle the LED bruh",// Name of the task
                      1024,                 // Stack size (for esp32 idf its in bytes for FreeRTOS its words
                      NULL,                 // parameter that is passed to fn
                      1,                    // Priority of task varies from 0 to 24, 24 being most priority
                      NULL,                 // Task Handle
                      app_cpu);             //Informing it to run on 1 core

  // In vanilla RTOS, vTaskStartSchedueler() must be called in main
  // once the tasks are done   
-------------------------------------------------------------------
Now we know what task fn we have but we have to make sure this particular task is activated say made sure it runs.

xTaskCreate() or xTaskCreatePinnedToCore() creates a fn that creates the task.
The first is a normal fn but the second is a fn used for MCUs with more than 1 cores.

This fn takes in the following arguments,

                      toggleLED,            // Name of fn that is being called
                      "Toggle the LED bruh",// Name of the task
                      1024,                 // Stack size for esp32 idf its in bytes for FreeRTOS its words
                      NULL,                 // parameter that is passed to fn
                      1,                    // Priority of task varies from 0 to 24, 24 being most priority
                      NULL,                 // Task Handle
                      app_cpu);             //Informing it to run on 1 core


-------------------------------------------------------------------
