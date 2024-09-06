#ifndef LIST_H
#define LIST_H
#include "portmacro.h"

struct xLIST_ITEM
{
	TickType_t xItemValue;			    /*< 列出的值。 在大多数情况下，它用于按降序对列表进行排序。*/
	struct xLIST_ITEM *  pxNext;		/*< 指向列表中下一个 ListItem_t 的指针。 */
	struct xLIST_ITEM *  pxPrevious;	/*< 指向列表中前一个 ListItem_t 的指针。*/
	void * pvOwner;						/*<指向包含列表项的对象（通常是 TCB） >*/
	void * pvContainer;				    /*< 指向该列表项所在列表的指针（如果有）。 */
};
typedef struct xLIST_ITEM ListItem_t;	/* 由于某些原因，lint 希望将其作为两个独立的定义。 */

struct xMINI_LIST_ITEM
{
	TickType_t xItemValue;
	struct xLIST_ITEM *  pxNext;
	struct xLIST_ITEM *  pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;

typedef struct xLIST
{
	UBaseType_t uxNumberOfItems;
	ListItem_t *  pxIndex;			/*< Used to walk through the list.  Points to the last item returned by a call to listGET_OWNER_OF_NEXT_ENTRY (). */
	MiniListItem_t xListEnd;							/*< List item that contains the maximum possible item value meaning it is always at the end of the list and is therefore used as a marker. */
} List_t;


#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwner )		( ( pxListItem )->pvOwner = ( void * ) ( pxOwner ) )



void vListInitialiseItem( ListItem_t * const pxItem );
void vListInitialise( List_t * const pxList );
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem );
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem );
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove );



#endif
