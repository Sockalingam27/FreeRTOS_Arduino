//Using only 1 core for learning purpose
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Pins
static const int led_pin = 2;

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


void setup() {
  // Configuring pins

  pinMode(led_pin,OUTPUT);

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
}

void loop() {
  // put your main code here, to run repeatedly:

}
