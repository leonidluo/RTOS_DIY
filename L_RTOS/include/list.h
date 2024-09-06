#ifndef LIST_H
#define LIST_H
#include "portmacro.h"

struct xLIST_ITEM
{
	TickType_t xItemValue;			    /*< �г���ֵ�� �ڴ��������£������ڰ�������б��������*/
	struct xLIST_ITEM *  pxNext;		/*< ָ���б�����һ�� ListItem_t ��ָ�롣 */
	struct xLIST_ITEM *  pxPrevious;	/*< ָ���б���ǰһ�� ListItem_t ��ָ�롣*/
	void * pvOwner;						/*<ָ������б���Ķ���ͨ���� TCB�� >*/
	void * pvContainer;				    /*< ָ����б��������б��ָ�루����У��� */
};
typedef struct xLIST_ITEM ListItem_t;	/* ����ĳЩԭ��lint ϣ��������Ϊ���������Ķ��塣 */

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
