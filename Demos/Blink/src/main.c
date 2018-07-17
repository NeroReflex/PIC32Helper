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

#include "ConfigPerformance.h"
#include "blink.h"

/*
 * Set up the hardware ready to run this demo.
 */
static void prvSetupHardware( void );

/* Define the size of the stack of the blink task */
const size_t xBlinkTaskSize = configMINIMAL_STACK_SIZE;

/* The refenrece to the blink task handler */
TaskHandle_t xBlinkTaskHandle;

int main(int argc __attribute__ ((unused)), char** argv __attribute__ ((unused))) {
    prvSetupHardware();
    
    BaseType_t xBlinkTaskCreation = xTaskCreate(blinkTask, "Blink", xBlinkTaskSize, NULL, tskIDLE_PRIORITY, &xBlinkTaskHandle);
    
    // Start the RTOS scheduler
    vTaskStartScheduler();
    
    /* The MCU should NEVER execute code under vTaskStartScheduler().
       If the following code is executed than the scheduler died for not having
       enough RAM to satisfy each task. */
    
    // Clean up all memory before entering the malloc failed hook
    if (xBlinkTaskCreation == pdTRUE)
        vTaskDelete(xBlinkTaskHandle);
    
    // The scheduler crashes on a malloc fail
    vApplicationMallocFailedHook();
    
    return 1;
}

/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	/* Configure the hardware for maximum performance. */
	vHardwareConfigurePerformance();

	/* Setup to use the external interrupt controller. */
	vHardwareUseMultiVectoredInterrupts();

	portDISABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/