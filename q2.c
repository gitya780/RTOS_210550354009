#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

void *const timer_Id;
TimerHandle_t my_timer_handle;

void myTimerCallback(TimerHandle_t xTimer)
{
    printf("Inside OneShot Timer callback\n");
}

void task1(void *params)
{
    printf("Created task 1, Periodicity = 1000ms\n");
    while (1)
    {
        printf("task1\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task2(void *params)
{
    printf("Created task 2, Periodicity = 2000ms\n");
    while (1)
    {
        printf("task2\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task3(void *params)
{
    printf("Created task 3, Periodicity = 5000ms\n");
    my_timer_handle = xTimerCreate(/timer name/ "my_timer",
                                   /timer tick period/ (10000 / portTICK_PERIOD_MS),
                                   /autoreload/ pdFALSE,
                                   /timer id/ timer_Id,
                                   /timer callback function/ myTimerCallback);

    xTimerStart(my_timer_handle, 1); //here we start the timer
    while (1)
    {
        printf("task3\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void app_main(void)
{
    //All tasks have same priority
    xTaskCreate(task1, "task1", 2048, NULL, 2, NULL);
    xTaskCreate(task2, "task2", 2048, NULL, 2, NULL);
    xTaskCreate(task3, "task3", 2048, NULL, 2, NULL);
    while (1)
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }