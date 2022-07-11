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
void freeList(List* lst);
List merge(List lst1, List lst2);
void makeEmptyList(List* lst);
bool isEmptyList(List lst);
void insertDataToEndList(List* lst, int num);
ListNode* makeNodeToList(int num, ListNode* next);
void checkAllocNode(ListNode* node);
void checkAllocInt(int* num);
void insertDataToStartList(List* lst, int data);
List mergeNodeRec(ListNode* curr1, ListNode* curr2);


void main()
{
    List lst1, lst2, mergedList;
    lst1 = getList();
    lst2 = getList();
    mergedList = merge(lst1, lst2);
    printf("Merged list:\n");
    printList(&mergedList);
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

//The following function gets 2 sorted lists and merging them 
List merge(List lst1, List lst2)
{
    return mergeNodeRec(lst1.head, lst2.head);    
}

//The following function is the recursion of "merge" function that works with the nodes intead of the lists
List mergeNodeRec(ListNode* curr1, ListNode* curr2)
{
    List lst;
    int data1, data2;
    if (curr1==NULL&&curr2==NULL)
    {
        makeEmptyList(&lst);
        return lst;
    }
    if (curr1 != NULL && curr2 != NULL)
    {
        data1 = *(curr1->dataPtr);
        data2 = *(curr2->dataPtr);
        if (data1 < data2)
        {
            lst = mergeNodeRec(curr1,curr2->next);
            insertDataToStartList(&lst, data2);
        }
        else
        {
            lst = mergeNodeRec(curr1->next, curr2);
            insertDataToStartList(&lst, data1);
        }
    }
    else
    {
        if (curr1 != NULL)
        {
            //curr2=NULL
            data1 = *(curr1->dataPtr);
            lst = mergeNodeRec(curr1->next, curr2);
            insertDataToStartList(&lst, data1);
        }
        if (curr2 != NULL)
        {
            //curr1=NULL
            data2 = *(curr2->dataPtr);
            lst = mergeNodeRec(curr1, curr2->next);
            insertDataToStartList(&lst, data2);
        }
    }
    return lst;

}

//The following function gets data and pushes it the the list and to be the new head
void insertDataToStartList(List * lst, int data)
{
    ListNode* tmp = makeNodeToList(data,lst->head);
    if (isEmptyList(*lst))
    {
        lst->tail = tmp;
    }
    lst->head = tmp;
    
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


//The following function checks if the list is empty or not
bool isEmptyList(List lst)
{
    return(lst.head == NULL);
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