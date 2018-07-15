#pragma config PMDL1WAY = OFF
#pragma config IOL1WAY = OFF  
#pragma config FWDTEN = OFF
#pragma config PWP = OFF
#pragma config BWP = OFF
#pragma config CP = OFF

#pragma config FNOSC = PRI
#pragma config OSCIOFNC = ON // Output the frequency on the OSCO pin

#include "../../../FreeRTOS/src/FreeRTOS.h"
#include "../../../FreeRTOS/src/task.h"

/* Define the start address and size of the three RAM regions. */

uint8_t region1[1024 * 2];
uint8_t region2[1024 * 12];

/* Create an array of HeapRegion_t definitions, with an index for each of the three RAM regions, and terminating the array with a NULL address. The HeapRegion_t structures must appear in start address order, with the structure that contains the lowest start address appearing first. */

const HeapRegion_t xHeapRegions[] =
{
    { region1, sizeof(region1) },
    { region2, sizeof(region2) },
    //{ RAM3_START_ADDRESS, RAM3_SIZE },
    
    { NULL, 0 } /* Marks the end of the array. */
};

TaskHandle_t xBlinkTaskHandle = NULL;
void blinkTask(void* pvParameters);

int main(int argc __attribute__ ((unused)), char** argv __attribute__ ((unused))) {
    // This is super-important, configurates the heap_5
    vPortDefineHeapRegions(xHeapRegions);
    
    BaseType_t xBlinkTaskCreation = xTaskCreate(blinkTask, "Blink", 20 + configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &xBlinkTaskHandle);
    
    // Start the RTOS scheduler
    vTaskStartScheduler();
    
    // Destroy the task if it was creates successfully
    if (xBlinkTaskCreation == pdPASS) vTaskDelete(xBlinkTaskHandle);
    
    // The scheduler crashes on a malloc fail
    vApplicationMallocFailedHook();
    
    return 1;
}

void blinkTask(void* pvParameters __attribute__ ((unused))) {
    // Task timing
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 1000;
    
    // Keep track of the led status
    uint32_t leds = 0xFF;
    
    // Set the data direction to output
    TRISB = ~(0x10);
    
    for (;;) {
        // A XOR of the current PORT with FF will flip all bits
        LATB = (leds ^= 0xFFFFFFFF) & 0x10;
        
        // Execution frequency
        vTaskDelayUntil(&xLastWakeTime, xFrequency );
    }
}