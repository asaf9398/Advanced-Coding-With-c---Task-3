#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct listNode {
    int* dataPtr;
    struct listNode* next;
}ListNode;

typedef struct list
{
    ListNode* head;
    ListNode* tail;
}List;

List getList();
void printList(List* lst);
void  freeList(List* lst);
List merge(List lst1, List lst2);
void makeEmptyList(List* lst);
bool isEmptyList(List lst);
void insertDataToEndList(List* lst, int num);
void checkAllocInt(int* num);
void checkAllocNode(ListNode* node);
ListNode* makeNodeToList(int ch, ListNode* next);
List cpyList(List lst);

void main()
{
    List lst1, lst2, mergedList;
    lst1 = getList();
    lst2 = getList();
    mergedList = merge(lst1, lst2);
    printf("Merged list:\n");
    printList(&mergedList);
    freeList(&lst1);
    freeList(&lst2);
    freeList(&mergedList);
}

//The following function free all the data(int *) + all the nodes 
void  freeList(List* lst)
{
    ListNode* curr = lst->head;
    while (curr != NULL)
    {
        free(curr->dataPtr);
        lst->head = lst->head->next;
        free(curr);
        curr = lst->head;
    }

}

//The following function gets 2 sorted lists and merging between them 
List merge(List lst1, List lst2)
{
    List mergedList;
    makeEmptyList(&mergedList);
    ListNode* curr1;
    ListNode* curr2;
    int newData;
    //if one of the lists is empty them copy only the second one
    //if the first is empty
    if (isEmptyList(lst1))
    {
        mergedList = cpyList(lst2);
    }
    else
    {
        //if the second is empty
        if (isEmptyList(lst2))
        {
            mergedList = cpyList(lst1);
        }
        //no one is empty - lets merge
        else
        {
            //run on both of them until one of them is over
            curr1 = lst1.head;
            curr2 = lst2.head;
            while (curr1 != NULL && curr2 != NULL)
            {
                if (*(curr1->dataPtr) > *(curr2->dataPtr))
                {
                    newData = *(curr1->dataPtr);
                    curr1 = curr1->next;
                }
                else
                {
                    newData = *(curr2->dataPtr);
                    curr2 = curr2->next;
                }
                insertDataToEndList(&mergedList, newData);//inserting the bigger number into the new list
            }
            //we don't know if they both over so we need to pass on the leftovers
            //coping the leftovers on lst1
            while (curr1 != NULL)
            {
                newData = *(curr1->dataPtr);
                curr1 = curr1->next;
                insertDataToEndList(&mergedList, newData);
            }

            //coping the leftovers on lst2
            while (curr2 != NULL)
            {
                newData = *(curr2->dataPtr);
                curr2 = curr2->next;
                insertDataToEndList(&mergedList, newData);
            }
        }
    }

    return mergedList;//returning the struct(local variable) because on the main we have placement to other local variable

}

//The following function gets a list and creates a copy of it(with new memory allocation)
List cpyList(List lst1)
{
    List listCpy;
    makeEmptyList(&listCpy);
    ListNode* curr;
    curr = lst1.head;
    while (curr != NULL)
    {
        insertDataToEndList(&listCpy, *(curr->dataPtr));
        curr = curr->next;
    }
    return listCpy;
}

List getList()
{
    List res;
    int size, num, i;
    makeEmptyList(&res);
    printf("Please enter the number of items to be entered:\n");
    scanf("%d", &size);
    printf("Please enter the numbers:\n");
    for (i = 0; i < size; i++)
    {
        scanf("%d", &num);
        insertDataToEndList(&res, num);
    }
    return res;
}

//The following function initializing the list that given to by empty
void makeEmptyList(List* lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}

//The following function gets a list + int and adds the a node with ch as data to the end of the list
void insertDataToEndList(List* lst, int num)
{
    List temp = *lst;
    if (isEmptyList(temp))
    {
        temp.head = temp.tail = makeNodeToList(num, NULL);
    }
    else
    {
        temp.tail->next = makeNodeToList(num, NULL);
        temp.tail = temp.tail->next;
    }
    lst->head = temp.head;
    lst->tail = temp.tail;
}

//The following function checks if the list is empty or not
bool isEmptyList(List lst)
{
    return(lst.head == NULL);
}

//The following fucntion gets data + next node adress and returns the new node adress  
ListNode* makeNodeToList(int num, ListNode* next)
{
    ListNode* nodep = (ListNode*)malloc(sizeof(ListNode));//Creating new node in memory
    checkAllocNode(nodep);
    nodep->next = next;
    nodep->dataPtr = (int*)malloc(sizeof(int));//saving memory in the heap for data
    checkAllocInt(nodep->dataPtr);
    *(nodep->dataPtr) = num;//inserting data to the saved place in the heap
    return nodep;
}
//Checking allocatoin for node
void checkAllocNode(ListNode* node)
{

    if (node == NULL)
    {
        printf("Memory allocation failed!! Exiting");
        exit(1);
    }
}

//Checking allocatoin for int
void checkAllocInt(int* num)
{
    if (num == NULL)
    {
        printf("Memory allocation failed!! Exiting");
        exit(1);
    }
}

//The following function prints the merged numbers list
void printList(List* lst)
{
    ListNode* curr = lst->head;
    while (curr != NULL)
    {
        printf("%d ", *(curr->dataPtr));
        curr = curr->next;
    }
}