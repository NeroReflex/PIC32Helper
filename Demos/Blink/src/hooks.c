#include "../../../FreeRTOS/src/FreeRTOS.h"
#include "../../../FreeRTOS/src/task.h"

#if ( configCHECK_FOR_STACK_OVERFLOW >= 1 )
/*---------------------------------------------------------------------------*\
Usage:
   called by task system when a stack overflow is noticed
Description:
   Stack overflow handler -- Shut down all interrupts, send serious complaint
    to command port. SLOW Blink on main LED.
Arguments:
   pxTask - pointer to task handle
   pcTaskName - pointer to task name
Results:
   <none>
Notes:
   This routine will never return.
   This routine is referenced in the task.c file of FreeRTOS as an extern.
\*---------------------------------------------------------------------------*/
//extern void vApplicationStackOverflowHook(TaskHandle_t xTask, portCHAR *pcTaskName);
void vApplicationStackOverflowHook(TaskHandle_t xTask, portCHAR *pcTaskName)
{
    
}

#endif /* configCHECK_FOR_STACK_OVERFLOW >= 1 */
/*-----------------------------------------------------------*/

#if ( configUSE_MALLOC_FAILED_HOOK == 1 )
/*---------------------------------------------------------------------------*\
Usage:
   called by task system when a malloc failure is noticed
Description:
   Malloc failure handler -- Shut down all interrupts, send serious complaint
    to command port. FAST Blink on main LED.
Arguments:
   pxTask - pointer to task handle
   pcTaskName - pointer to task name
Results:
   <none>
Notes:
   This routine will never return.
   This routine is referenced in the task.c file of FreeRTOS as an extern.
\*---------------------------------------------------------------------------*/
void vApplicationMallocFailedHook(void)
{
    
}

#endif /* configUSE_MALLOC_FAILED_HOOK == 1 */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
#if ( configUSE_IDLE_HOOK == 1 )
/*
 * Call the user defined appIdleHook() function from within the idle task.
 * This allows the application designer to add background functionality
 * without the overhead of a separate task.
 *
 * NOTE: vApplicationIdleHook() MUST NOT, UNDER ANY CIRCUMSTANCES, CALL A FUNCTION THAT MIGHT BLOCK.
 */
void vApplicationIdleHook(void)
{
	
}

#endif /* configUSE_IDLE_HOOK == 1 */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
void vAssertCalled( const char * pcFile, unsigned long ulLine )
{
volatile unsigned long ul = 0;

	( void ) pcFile;
	( void ) ulLine;

	__asm volatile( "di" );
	{
		/* Set ul to a non-zero value using the debugger to step out of this
		function. */
		while( ul == 0 )
		{
			portNOP();
		}
	}
	__asm volatile( "ei" );
}
/*-----------------------------------------------------------*/