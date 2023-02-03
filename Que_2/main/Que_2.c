#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>

TaskHandle_t task1_handle, task2_handle, task3_handle;
TimerHandle_t timer_handle;

void Timer_Callback(TimerHandle_t timer_handle)
{
    printf("Oneshot Timer : Fired\n");
}

void task_1(void *data)
{
    while(1)
    {
        printf("Inside Task 1....\n");  
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
        timer_handle = xTimerCreate("Oneshot", pdMS_TO_TICKS(10000), pdFALSE, NULL, Timer_Callback);
        printf("Oneshot Timer : Going to start\n");
        xTimerStart(timer_handle, 0);
        vTaskDelay(5000);
    }
    printf("Task 3 : Deleted\n");
    vTaskDelete(NULL);
}


void app_main(void)
{
    BaseType_t res_1, res_2, res_3;
    printf("****Main Task****\n");
    res_1 = xTaskCreate(task_1,"First_Task", 2048, NULL, 5 , &task1_handle);
    if(res_1 == pdPASS)
    {
        printf("    Task 1 successfully created...\n");
    }
    res_2 = xTaskCreate(task_2,"Second_Task", 2048, NULL, 6, &task2_handle);
    if(res_2 == pdPASS)
    {
        printf("    Task 2 successfully created...\n");
    }
    res_3 = xTaskCreate(task_3,"Third_Task", 2048, NULL, 7, &task3_handle);
    if(res_3 == pdPASS)
    {
        printf("    Task 3 successfully created...\n");
    }
}
