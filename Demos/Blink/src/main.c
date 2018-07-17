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

/*
 * Set up the hardware ready to run this demo.
 */
static void prvSetupHardware( void );

/* Define the size of the stack of the blink task */
#define xBlinkTaskSize  configMINIMAL_STACK_SIZE

/* The refenrece to the blink task handler */
TaskHandle_t xBlinkTaskHandle;

/* Structure that will hold the TCB of the task being created. */
StaticTask_t xBlinkTaskBuffer;

/* Buffer that the task being created will use as its stack.  Note this is
   an array of StackType_t variables.  The size of StackType_t is dependent on
   the RTOS port. */
StackType_t xBlinkStack[ xBlinkTaskSize ];
portTASK_FUNCTION_PROTO( blinkTask, pvParameters );

int main(int argc __attribute__ ((unused)), char** argv __attribute__ ((unused))) {
    prvSetupHardware();
    
    BaseType_t xBlinkTaskCreation = xTaskCreate(blinkTask, "Blink", xBlinkTaskSize, NULL, tskIDLE_PRIORITY, &xBlinkTaskHandle);
    //xBlinkTaskHandle = xTaskCreateStatic(blinkTask, "Blink", xBlinkTaskSize, NULL, tskIDLE_PRIORITY + 1, xBlinkStack, &xBlinkTaskBuffer);
    
    // Start the RTOS scheduler
    vTaskStartScheduler();
    
    // The scheduler crashes on a malloc fail
    vApplicationMallocFailedHook();
    
    return 1;
}

portTASK_FUNCTION( blinkTask, pvParameters ) {
    // Task timing
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = portMS_TO_TICKS( 500 );
    
    // Keep track of the led status
    uint32_t leds = 0xFF;
    
    // Set the data direction to output
    TRISB = ~(0x10);
    
    for (;;) {
        // Flip all desired bits
        LATB = (leds ^= 0xFFFFFFFF) & 0x10;
        
        // Execution frequency
        vTaskDelayUntil(&xLastWakeTime, xFrequency );
    }
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