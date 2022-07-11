#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INITIALIZED_GRADE 0
#define ZERO_CHAR '0'
#define NINE_CHAR '9'
#define MULTIPLY_BY_TEN 10

typedef struct list_node
{
    char* dataPtr;
    struct list_node* next;
}ListNode;

typedef struct list
{
    ListNode* head;
    ListNode* tail;
}List;

typedef struct  student
{
    List first;
    int grade;
} Student;





Student unScramble(List  lst);
void makeEmptyList(List * lst);
void insertDataToEndList(List* lst, char ch);
ListNode* makeNodeToList(char ch, ListNode* next);
bool isEmptyList(List lst);
void printStudent(Student * student);
void freeList(List * name);
void printCharList(List lst);
void checkAllocNode(ListNode* node);
void checkAllocChar(char * ch);

void main()
{
    List lst;
    Student student;
    char ch;
    makeEmptyList(&lst);
    printf("Please enter the scrambled student:\n");
    ch = (char)getchar();
    while (ch != '\n')
    {
        insertDataToEndList(&lst, ch);
        ch = (char)getchar();
    }
    student = unScramble(lst);
    printStudent(&student);
    freeList(&student.first);
}

//The following function get a list and returns a student 
Student unScramble(List lst)
{
    Student student;
    char data;
    //Initializing studend 
    student.grade = INITIALIZED_GRADE;

    //running on the list
    ListNode* curr = lst.head;
    ListNode* prev = lst.head;

    while (curr != NULL)
    {
        data = *(curr->dataPtr);

        //Checking what if the head is a number
        if (curr == lst.head)
        {
            if (data >= ZERO_CHAR && data <= NINE_CHAR)
            {
                student.grade = (student.grade * 10) + (data - ZERO_CHAR);
                lst.head = lst.head->next;
                free(curr->dataPtr);
                free(curr);
                curr = lst.head;
                prev = lst.head;
            }
            else
            {
                curr = curr->next;
            }
        }
        else
        {
            //if curr is not a the head
            if (data >= ZERO_CHAR && data <= NINE_CHAR)
            {
                student.grade = (student.grade * MULTIPLY_BY_TEN) + (data - ZERO_CHAR);
                prev->next = curr->next;
                free(curr->dataPtr);
                free(curr);
                curr = prev->next;
            }
            else
            {
                prev = prev->next;
                curr = curr->next;
            }
        }
        if (prev == lst.tail)
        {
            lst.tail = prev;
        }
        
    }

    student.first.head = lst.head;
    student.first.tail = lst.tail;
    return student;
}

//The following function gets an adress of list and free all the data from the memory
void freeList(List* name)
{
    ListNode* curr=name->head;
    while (curr != NULL)
    {
        free(curr->dataPtr);//free every data that saved in the heap 
        name->head = name->head->next;//promoting the head before "free"(we don't want to lose the next node)
        free(curr);//free the node itself from the memory
        curr = name->head;//updating curr to the next node
    }
}

//The follwing function prints a student
void printStudent(Student* student)
{
    printf("First name: ");
    printCharList(student->first);
    printf("\n");
    printf("Grade: %d",student->grade);
}

//The follwing function gets a list and prints it
void printCharList(List lst)
{
    ListNode* curr = lst.head;
    while (curr!=NULL)
    {
        printf("%c",*(curr->dataPtr));
        curr = curr->next;
    }

}

//The following function initializing the list that given to by empty
void makeEmptyList(List* lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}

//The following function gets a list + char and adds the a node with ch as data to the end of the list
void insertDataToEndList(List* lst, char ch)
{
    List temp = *lst;
    if (isEmptyList(temp))
    {
        temp.head = temp.tail = makeNodeToList(ch, NULL);
    }
    else
    {
        temp.tail->next = makeNodeToList(ch, NULL);
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
ListNode* makeNodeToList(char ch, ListNode * next)
{
    ListNode* nodep = (ListNode*)malloc(sizeof(ListNode));//Creating new node in memory
    checkAllocNode(nodep);
    nodep->next = next;
    nodep->dataPtr = (char*)malloc(sizeof(char));//saving memory in the heap for data
    checkAllocChar(nodep->dataPtr);
    *(nodep->dataPtr) = ch;//inserting data to the saved place in the heap
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

//Checking allocatoin for char
void checkAllocChar(char* ch)
{
    if (ch == NULL)
    {
        printf("Memory allocation failed!! Exiting");
        exit(1);
    }
}