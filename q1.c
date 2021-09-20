#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t one_handle;
TaskHandle_t two_handle;
TaskHandle_t three_handle;
TaskHandle_t location_handle;
TaskHandle_t mqtt_handle;
QueueHandle_t locmq;

void task_one(void *argument)
{
    while(1)
    {
        printf("IN Task 2\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS );
    }
}

void task_two(void *argument)
{
    while(1)
    {
        printf("IN Task 3\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS );
    }
}

void task_three(void *data)
{
    while(1)
    {
        printf("IN Task 3\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS );
    }
}

void location_task(void *data)
{
    int lat = 0;
    while(1)
    {
        printf("Location started\n");
        lat++;// geting GSP lat
        //send lat to mq
        xQueueSend(locmq, &lat, 0);
        printf("Location ended\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void mqtt_task(void *data)
{
    int buff;
    while(1)
    {
        printf("MQTT started\n");
        //recv lat from mq  
        xQueueReceive(locmq, &buff, 0);
        printf("MQTT: Buff (lat): %d\n", buff);
        printf("MQTT ended\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    //int i = 0;
    locmq = xQueueCreate(5, sizeof(int));
    xTaskCreate(task_one, "tsk_1", 2048, NULL, 1, &one_handle);
    xTaskCreate(task_two, "tsk_2", 2028, NULL, 2, &two_handle);
    xTaskCreate(task_three, "tsk_3", 2028, NULL, 3, &three_handle);
    xTaskCreate(location_task, "loc_tsk", 2048, NULL, 4, &location_handle);
    xTaskCreate(mqtt_task, "mqtt_tsk", 2028, NULL, 5, &mqtt_handle);
    while (1) {
        //printf("[%d] Hello world!\n", i);
        //i++;
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}