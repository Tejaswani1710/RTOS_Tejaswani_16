#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

TaskHandle_t task1_handle, task2_handle, task3_handle, task4_handle, task5_handle;
QueueHandle_t que_handle;

void task_1(void *data)
{
    while(1)
    {
        printf("Inside Task 1...\n");
        for(int i = 0; i < 6; i++) 
        {
            printf(" %d\n", i+1);
        }
        vTaskDelay(1000);
    }
    printf("Task 1 : Deleted\n");
    vTaskDelete(NULL);
}

void task_2(void *data)
{

    while(1)
    {
        printf("Inside Task 2.....\n");
        for(int i = 0; i < 6; i++) 
        {
            printf(" %d\n", i+1);
        }
        vTaskDelay(2000);
    }

    printf("Task 2: Deleted\n" );
    vTaskDelete(NULL);
}

void task_3(void *data)
{
    while(1)
    {
        printf("Inside Task 3.....\n");
        for(int i = 0; i < 6; i++)
        {
            printf(" %d\n", i+1);
        }
        vTaskDelay(5000);
    }
    printf("Task 3: Deleted\n" );
    vTaskDelete(NULL);
}

void task_4(void *data)
{
    unsigned int sendmsg = 2;
    while (1)
    {
        printf("Inside Task 4.....\n");
        if((xQueueSend(que_handle, &sendmsg, pdMS_TO_TICKS(1000))) != pdPASS)
        {
            printf("Message cannot be queued\n");
        }
        else
        {
            printf("Message queued successfully..\n");
        }

        for(int i = 0; i < 6; i++)
        {
            printf("Task 5 getting resumed in %d\n", i+1);
        }
    }
    printf("Task 4: Deleted\n" );
    vTaskDelete(NULL);
}
void task_5(void *data)
{
    unsigned int recmsg;

    while (1)
    {
        printf("Inside Task 5......\n");        
        if((xQueueReceive(que_handle, &recmsg, pdMS_TO_TICKS(1000))) != pdPASS)
        {
            printf("Message cannot be received\n");
        }
        else
        {
            printf("Message received successfully..\n");
            printf("Data: %d\n",recmsg);
        }

        printf("Queue Deleted successfully\n");
        vQueueDelete(que_handle);
    }
    printf("Task 5: Deleted\n" );
    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("***Inside Main****\n");
    que_handle = xQueueCreate(5,2);
    if(que_handle != NULL)
    {
        printf("Queue created successfully\n");
    }

    if((xTaskCreate(task_1,"First_Task", 2048, NULL, 5 , &task1_handle)) == pdPASS)
    {
        printf("    Task 1 created successfully...\n");
    }
    if((xTaskCreate(task_2,"Second_Task", 2048, NULL, 6 , &task2_handle)) == pdPASS)
    {
        printf("    Task 2 created successfully...\n");
    }
    if((xTaskCreate(task_3,"Third_Task", 2048, NULL, 7 , &task3_handle)) == pdPASS)
    {
        printf("    Task 3 created successfully...\n");
    }
    if((xTaskCreate(task_4,"Fourth_Task", 2048, NULL, 8 , &task4_handle)) == pdPASS)
    {
        printf("    Task 4 created successfully...\n");
    }
    if((xTaskCreate(task_5,"Fifth_Task", 2048, NULL, 9 , &task5_handle)) == pdPASS)
    {
        printf("    Task 5 created successfully...\n");
    }
}
