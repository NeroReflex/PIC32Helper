#include "blink.h"

portTASK_FUNCTION( blinkTask, pvParameters ) {
    // Task timing
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = portMS_TO_TICKS( 500 );
    
    // Keep track of the led status
    uint32_t leds = 0xFF;
    
    // Set the data direction to output
    TRISB = ~(0x20);
    
    for (;;) {
        // Flip all desired bits
        LATB = (leds ^= 0xFFFFFFFF) & 0x20;
        
        // Execution frequency
        vTaskDelayUntil(&xLastWakeTime, xFrequency );
    }
}