#ifndef FREERTOS_H
#define FREERTOS_H
#include <stdint.h> /* READ COMMENT ABOVE. */
#include "portmacro.h"
#include "list.h"
/* Application specific configuration options. */
#include "FreeRTOSConfig.h"

/* Basic FreeRTOS definitions. */
#include "projdefs.h"

/* Definitions specific to the port being used. */
#include "portable.h"

typedef struct tskTaskControlBlock
{
	volatile StackType_t	*pxTopOfStack;	/*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

	
	ListItem_t			xStateListItem;	/*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
	StackType_t			*pxStack;			/*< Points to the start of the stack. */
	char				pcTaskName[ configMAX_TASK_NAME_LEN ];/*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

} tskTCB;
/* 上面保留旧的 tskTCB 名称，然后将其类型化为下面新的 TCB_t 名称，以便使用旧的内核感知调试器。 */
typedef tskTCB TCB_t;

struct xSTATIC_LIST_ITEM
{
	TickType_t xDummy1;
	void *pvDummy2[ 4 ];
};
typedef struct xSTATIC_LIST_ITEM StaticListItem_t;

typedef struct xSTATIC_TCB
{
	void				*pxDummy1;
	#if ( portUSING_MPU_WRAPPERS == 1 )
		xMPU_SETTINGS	xDummy2;
	#endif
	StaticListItem_t	xDummy3[ 2 ];
	UBaseType_t			uxDummy5;
	void				*pxDummy6;
	uint8_t				ucDummy7[ configMAX_TASK_NAME_LEN ];
	#if ( portSTACK_GROWTH > 0 )
		void			*pxDummy8;
	#endif
	#if ( portCRITICAL_NESTING_IN_TCB == 1 )
		UBaseType_t		uxDummy9;
	#endif
	#if ( configUSE_TRACE_FACILITY == 1 )
		UBaseType_t		uxDummy10[ 2 ];
	#endif
	#if ( configUSE_MUTEXES == 1 )
		UBaseType_t		uxDummy12[ 2 ];
	#endif
	#if ( configUSE_APPLICATION_TASK_TAG == 1 )
		void			*pxDummy14;
	#endif
	#if( configNUM_THREAD_LOCAL_STORAGE_POINTERS > 0 )
		void			*pvDummy15[ configNUM_THREAD_LOCAL_STORAGE_POINTERS ];
	#endif
	#if ( configGENERATE_RUN_TIME_STATS == 1 )
		uint32_t		ulDummy16;
	#endif
	#if ( configUSE_NEWLIB_REENTRANT == 1 )
		struct	_reent	xDummy17;
	#endif
	#if ( configUSE_TASK_NOTIFICATIONS == 1 )
		uint32_t 		ulDummy18;
		uint8_t 		ucDummy19;
	#endif
	#if( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
		uint8_t			uxDummy20;
	#endif

} StaticTask_t;

#endif
