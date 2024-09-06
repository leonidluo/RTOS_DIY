
/* Standard includes. */
#include <stdlib.h>
#include <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
all the API functions to use the MPU wrappers.  That should only be done when
task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
//#include "timers.h"
//#include "StackMacros.h"
#include "projdefs.h"

TCB_t * volatile pxCurrentTCB = NULL;
extern TCB_t Task1TCB;
extern TCB_t Task2TCB;

List_t pxReadyTasksLists[configMAX_PRIORITIES];

static void prvInitialiseNewTask( 	TaskFunction_t pxTaskCode,
									const char * const pcName,
									const uint32_t ulStackDepth,
									void * const pvParameters,
									UBaseType_t uxPriority,
									TaskHandle_t * const pxCreatedTask,
									TCB_t *pxNewTCB,
									const MemoryRegion_t * const xRegions ) /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
{
    StackType_t *pxTopOfStack;
    UBaseType_t x;
    pxTopOfStack = pxNewTCB->pxStack + ( ulStackDepth - ( uint32_t ) 1 );
    pxTopOfStack = ( StackType_t * ) ( ( ( uint32_t ) pxTopOfStack ) & ( ~( ( uint32_t ) 0x0007 ) ) ); /*lint !e923 MISRA exception.  Avoiding casts between pointers and integers is not practical.  Size differences accounted for using portPOINTER_SIZE_TYPE type. */
    /* Store the task name in the TCB. */
	for( x = ( UBaseType_t ) 0; x < ( UBaseType_t ) configMAX_TASK_NAME_LEN; x++ )
	{
		pxNewTCB->pcTaskName[ x ] = pcName[ x ];

		/* Don't copy all configMAX_TASK_NAME_LEN if the string is shorter than
		configMAX_TASK_NAME_LEN characters just in case the memory after the
		string is not accessible (extremely unlikely). */
		if( pcName[ x ] == 0x00 )
		{
			break;
		}
		
	}
    /* Ensure the name string is terminated in the case that the string length
    was greater or equal to configMAX_TASK_NAME_LEN. */
    pxNewTCB->pcTaskName[ configMAX_TASK_NAME_LEN - 1 ] = '\0';
    vListInitialiseItem( &( pxNewTCB->xStateListItem ) );
    
    /* Set the pxNewTCB as a link back from the ListItem_t.  This is so we can get
	back to	the containing TCB from a generic item in a list. */
	listSET_LIST_ITEM_OWNER( &( pxNewTCB->xStateListItem ), pxNewTCB );
    
    pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack, 
                                                    pxTaskCode, 
                                                    pvParameters );
	
    
    if( ( void * ) pxCreatedTask != NULL )
	{
		/* Pass the handle out in an anonymous way.  The handle can be used to
		change the created task's priority, delete the created task, etc.*/
		*pxCreatedTask = ( TaskHandle_t ) pxNewTCB;
	}
} 



#if( configSUPPORT_STATIC_ALLOCATION == 1 )

	TaskHandle_t xTaskCreateStatic(	TaskFunction_t pxTaskCode,
									const char * const pcName,
									const uint32_t ulStackDepth,
									void * const pvParameters,
									UBaseType_t uxPriority,
									StackType_t * const puxStackBuffer,
									TCB_t * const pxTaskBuffer ) /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
	{
	TCB_t *pxNewTCB;
	TaskHandle_t xReturn;

//		configASSERT( puxStackBuffer != NULL );
//		configASSERT( pxTaskBuffer != NULL );

		if( ( pxTaskBuffer != NULL ) && ( puxStackBuffer != NULL ) )
		{
			/* The memory used for the task's TCB and stack are passed into this
			function - use them. */
			pxNewTCB = ( TCB_t * ) pxTaskBuffer; /*lint !e740 Unusual cast is ok as the structures are designed to have the same alignment, and the size is checked by an assert. */
			pxNewTCB->pxStack = ( StackType_t * ) puxStackBuffer;

			#if( tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE != 0 )
			{
				/* Tasks can be created statically or dynamically, so note this
				task was created statically in case the task is later deleted. */
				pxNewTCB->ucStaticallyAllocated = tskSTATICALLY_ALLOCATED_STACK_AND_TCB;
			}
			#endif /* configSUPPORT_DYNAMIC_ALLOCATION */

			prvInitialiseNewTask( pxTaskCode, 
                                  pcName, 
                                  ulStackDepth, 
                                  pvParameters, 
                                  uxPriority, 
                                  &xReturn, 
                                  pxNewTCB, 
                                  NULL );
//			prvAddNewTaskToReadyList( pxNewTCB );
		}
		else
		{
			xReturn = NULL;
		}

		return xReturn;
    }

#endif /* SUPPORT_STATIC_ALLOCATION */
static void prvInitialiseTaskLists( void )
{
    UBaseType_t uxPriority;

	for( uxPriority = ( UBaseType_t ) 0U; uxPriority < ( UBaseType_t ) configMAX_PRIORITIES; uxPriority++ )
	{
		vListInitialise( &( pxReadyTasksLists[ uxPriority ] ) );
	}

//	vListInitialise( &xDelayedTaskList1 );
//	vListInitialise( &xDelayedTaskList2 );
//	vListInitialise( &xPendingReadyList );

//	#if ( INCLUDE_vTaskDelete == 1 )
//	{
//		vListInitialise( &xTasksWaitingTermination );
//	}
//	#endif /* INCLUDE_vTaskDelete */

//	#if ( INCLUDE_vTaskSuspend == 1 )
//	{
//		vListInitialise( &xSuspendedTaskList );
//	}
//	#endif /* INCLUDE_vTaskSuspend */

//	/* Start with pxDelayedTaskList using list1 and the pxOverflowDelayedTaskList
//	using list2. */
//	pxDelayedTaskList = &xDelayedTaskList1;
//	pxOverflowDelayedTaskList = &xDelayedTaskList2;
}



void vTaskStartScheduler( void )
{
    pxCurrentTCB = &Task1TCB;
    if(xPortStartScheduler() != pdFALSE)
    {
        
    }
}

void vTaskSwitchContext(void)
{
     if(pxCurrentTCB == &Task1TCB)
     {
        pxCurrentTCB = &Task2TCB;
     }
     else 
     {
        pxCurrentTCB = &Task1TCB;
     }
}

