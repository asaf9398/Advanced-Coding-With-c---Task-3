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
void insertNodeToEndList(List* lst, ListNode* node);
void insertDataToEndList(List* lst, int num);
ListNode* makeNodeToList(int num, ListNode* next);
void checkAllocNode(ListNode* node);
void checkAllocInt(int* num);


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
    List mergedList;
    makeEmptyList(&mergedList);
    int data1, data2;
    ListNode* biggerNode;
    //if one of the lists is empty then just return the other one
    //if the first is empty
    if (isEmptyList(lst1))
    {
        return lst2;
    }
    else
    {
        //if the second is empty
        if (isEmptyList(lst2))
        {
            return lst1;
        }
        //no one is empty - lets merge
        else
        {
            //run on both of them until one of them is over
            while (!isEmptyList(lst1) && !isEmptyList(lst2))
            {
                data1 = *(lst1.head->dataPtr);
                data2 = *(lst2.head->dataPtr);
                if (data1 > data2)
                {
                    biggerNode = lst1.head;
                    lst1.head = lst1.head->next;
                }
                else
                {
                    biggerNode = lst2.head;
                    lst2.head = lst2.head->next;
                }
                insertNodeToEndList(&mergedList, biggerNode);//inserting the bigger node into the new list
            }


            //we don't know if they both over so we need to pass on the leftovers
            //taking the leftovers from lst1
            while (!isEmptyList(lst1))
            {
                biggerNode = lst1.head;
                lst1.head = lst1.head->next;
                insertNodeToEndList(&mergedList, biggerNode);
            }

            //taking the leftovers from lst2
            while (!isEmptyList(lst2))
            {
                biggerNode = lst2.head;
                lst2.head = lst2.head->next;
                insertNodeToEndList(&mergedList, biggerNode);
            }
        }
    }

    return mergedList;//returning the struct(local variable) because on the main we have placement to other local variable - we changed only the adresses

}

//The following function gets a list's adress and inserts the node to the end
void insertNodeToEndList(List* lst, ListNode* node)
{
    List tmp = *lst;
    node->next = NULL;
    if (isEmptyList(tmp))
    {
        tmp.head = tmp.tail = node;
    }
    else
    {
        tmp.tail->next = node;
        tmp.tail = tmp.tail->next;
    }
    *lst = tmp;
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
    int data;
    while (curr != NULL)
    {
        data = *(curr->dataPtr);
        printf("%d ", data);
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