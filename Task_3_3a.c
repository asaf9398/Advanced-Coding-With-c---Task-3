#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define NONE 0
#define INIT_SIZE 1
#define END_OF_STRING '\0'
#define START_OF_ARR 0
#define SAME 0
#define MULTIPLY_ARRAY_BY_TWO 2
#define ZERO_CHAR '0'
#define NUM_OF_INTEGERS_IN_POINT 2
#define INITIALIZE_X_DATA 0
#define INITIALIZE_Y_DATA 0
#define FIRST_X_POINT_CELL 0
#define INITIALIZE_COUNTER 0
#define NEXT_CELL 1
#define ENTER_CHAR '\n'



typedef struct YlistNode {
    int yData;
    struct YlistNode* yNext;
} YListNode;

typedef struct Ylist {
    YListNode* yHead;
    YListNode* yTail;
} YList;

typedef struct XlistNode {
    struct XlistNode* xPrev;
    struct XlistNode* xNext;
    int xData;
    YList yPointsList;
} XListNode;

typedef struct list {
    XListNode* xHead;
    XListNode* xTail;
} List;

List getCoordList();
char* getStringFromUser();
void checkAllocStr(char* str);
void freeList(List* coordList);
int* getPoints(char* userInput, int* numOfPoints);
void checkAllocInt(int* arr);
YList createYList();
void initializeXListNode(XListNode* xNode);
XListNode* createXListNode();
bool xIsInside(List list, int x);
void addDataToList(List* list, int x, int y);
void addYcoordinate(List list, int  x, int  y);
YListNode* createYListNode();
void addXcoordinate(List* list, int x, int y);
List createEmptyList();
void checkAllocXListNode(XListNode* xNode);
void checkAllocYListNode(YListNode* yNode);
bool isEmptyXlist(List list);
bool isEmptyYlist(YList list);
int checkYOccurence(XListNode* xCurr, int y);
int getPairOccurrences(List coordList, int x, int y);
void freeYList(YList list);


void main()
{

    List coordList;

    int x, y;
    unsigned int res;

    // The user will enter the number of points followed by the points.
    // The pointes will be entered in a sorted fashion.
    // i.e. first by the x value and then by y.
    // for example (5 points): 5 1 2 1 5 2 7 3 3 3 8
    // are: (1,2),(1,5),(2,7),(3,3),(3,8)
    coordList = getCoordList();

    // get the (x,y) to look for
    scanf("%d%d", &x, &y);

    res = getPairOccurrences(coordList, x, y);

    printf("The point (%d,%d) appears %u times\n", x, y, res);

    freeList(&coordList);
}

//The following function free the Ylist
void freeYList(YList list)
{
    YListNode* curr = list.yHead;
    while (curr != NULL)
    {
        list.yHead = list.yHead->yNext;
        free(curr);
        curr = list.yHead;
    }
}

//The following function free the Xlist
void freeList(List* coordList)
{
    XListNode* xCurr = coordList->xTail;
    while (xCurr != NULL)
    {
        freeYList(xCurr->yPointsList);//free yList
        coordList->xTail = coordList->xTail->xPrev;//getting backwards to the xHead
        free(xCurr);//letting the current node to get free only after his yNodes are already free
        xCurr = coordList->xTail;//moving the xCurr for the next iteration
    }
}

//The following function gets a XListNode* and returns how many times y is in his yList
int checkYOccurence(XListNode* xCurr, int y)
{
    int counter = INITIALIZE_COUNTER;
    YListNode* curr = xCurr->yPointsList.yHead;
    while (curr != NULL)
    {
        if (curr->yData == y)
        {
            counter++;
        }
        curr = curr->yNext;
    }
    return counter;
}

//The following function returns how many time the coordinate (x,y) is in coordList
int getPairOccurrences(List coordList, int x, int y)
{
    int counter = INITIALIZE_COUNTER;
    XListNode* curr = coordList.xHead;
    while (curr->xData != x)
    {
        curr = curr->xNext;//trying to find the specific XListNode* for X
    }
    if (curr != NULL)//checking if x is inside list
    {
        if (curr->xData == x)
        {
            counter = checkYOccurence(curr, y);
        }
    }
    return counter;
}


//The following function gets the number of points that the user is about to enter + their values
//The function returns the List of the dots
List getCoordList()
{
    int numOfPoints;
    //getting numOfPoints from the user
    char* userInput = getStringFromUser();

    //getting the points from the user
    int* pointsTmpArr = getPoints(userInput, &numOfPoints);
    free(userInput);//free temp memory

    //putting the points into the xList
    int ind;
    List list = createEmptyList();
    for (ind = FIRST_X_POINT_CELL; ind < numOfPoints* NUM_OF_INTEGERS_IN_POINT; ind += NUM_OF_INTEGERS_IN_POINT)
    {
        addDataToList(&list, pointsTmpArr[ind], pointsTmpArr[ind + NEXT_CELL]);
    }

    free(pointsTmpArr);//free temp points array

    return list;
}

//The following function creates new empty list and returns it
List createEmptyList()
{
    List list;
    list.xHead = list.xTail = NULL;
    return list;
}

//The following function gets a list + x,y coordinates and adds the point to the list
void addDataToList(List* list, int x, int y)
{
    if (xIsInside(*list, x))//checking if the x value inside that list
    {
        addYcoordinate(*list, x, y);//if x is inside -> add the y to that x
    }
    else
    {
        addXcoordinate(list, x, y);//if the x isn't inside add it to the list
        addYcoordinate(*list, x, y);//add the y to the list
    }
}

//The following function gets a list + coordinates and adds the X,Y into the list(when the X value is not in the list)
void addXcoordinate(List * list, int x, int y)
{
    XListNode* newXlistNode = createXListNode();
    newXlistNode->xData = x;
    if (list->xHead == NULL)
    {
        list->xHead = list->xTail = newXlistNode;
    }
    else
    {
        list->xTail->xNext = newXlistNode;
        newXlistNode->xPrev = list->xTail;
        list->xTail = newXlistNode;
    }
}

//The following function gets a list + x + y and adds the y coordinate to an exist x coordinate
void addYcoordinate(List list, int  x, int  y)
{
    XListNode* curr = list.xHead;
    //finding the x inside the Xlist
    while (curr->xData != x)
    {
        curr = curr->xNext;
    }

    //Adding the y value to the yList
    //checks if the yPointsList is empty
    YListNode* yNode = createYListNode();
    yNode->yData = y;

    if (isEmptyYlist(curr->yPointsList))
    {
        curr->yPointsList.yHead = curr->yPointsList.yTail = yNode;
    }
    else
    {
        curr->yPointsList.yTail->yNext = yNode;
        curr->yPointsList.yTail = yNode;
    }

}

//Initializing YListNode
void initializeYListNode(YListNode* yNode)
{
    yNode->yData = INITIALIZE_Y_DATA;
    yNode->yNext = NULL;
}

//The following function creates empty YList
YList createYList()
{
    YList yList;
    yList.yHead = NULL;
    yList.yTail = NULL;
    return yList;
}

//Initializing XListNode
void initializeXListNode(XListNode* xNode)
{
    xNode->xData = INITIALIZE_X_DATA;
    xNode->xNext = NULL;
    xNode->xPrev = NULL;
    xNode->yPointsList = createYList();

}

//Create YListNode
YListNode* createYListNode()
{
    YListNode* yNode = (YListNode*)malloc(sizeof(YListNode));
    checkAllocYListNode(yNode);
    initializeYListNode(yNode);
    return yNode;
}

//Create XListNode
XListNode* createXListNode()
{
    XListNode* xNode = (XListNode*)malloc(sizeof(XListNode));
    checkAllocXListNode(xNode);
    initializeXListNode(xNode);
    return xNode;
}

//The following function gets the user's input and returns array of points
int* getPoints(char* userInput, int* numOfPoints)
{
    char* seps = " ";
    char* token = strtok(userInput, seps);
    int size = (*token) - ZERO_CHAR;//getting the number of points from the input
    *numOfPoints = size;
    int* pointsTmpArr = (int*)malloc(sizeof(int) * size * NUM_OF_INTEGERS_IN_POINT);
    checkAllocInt(pointsTmpArr);
    int ind = START_OF_ARR;
    token = strtok(NULL, seps);
    while (token != NULL)
    {
        pointsTmpArr[ind] = (*token) - ZERO_CHAR;//getting the point from the input
        ind++;
        token = strtok(NULL, seps);
    }
    return pointsTmpArr;
}

//The following function gets the string from the user
char* getStringFromUser()
{
    int logSize = NONE, physSize = INIT_SIZE;
    char* tmpStr = (char*)malloc(sizeof(char));//making an array for getting the input from the user
    checkAllocStr(tmpStr);
    tmpStr[START_OF_ARR] = END_OF_STRING;
    char ch;
    scanf("%c", &ch);
    while (ch - ENTER_CHAR != SAME)
    {
        if (logSize == physSize)//if the sizes are the same -> multiply the physical size by 2
        {
            physSize *= MULTIPLY_ARRAY_BY_TWO;
            tmpStr = (char*)realloc(tmpStr, physSize * sizeof(char));
            checkAllocStr(tmpStr);//checking if the allocation succeed

        }
        *(tmpStr + logSize) = ch;
        logSize++;
        scanf("%c", &ch);
    }
    tmpStr = (char*)realloc(tmpStr, (logSize + 1) * sizeof(char));//decreasing the array to the smallest length that needed
    tmpStr[logSize] = END_OF_STRING;
    return tmpStr;

}

//The following function check allocation for string
void checkAllocStr(char* str)
{
    if (str == NULL)
    {
        printf("Memory Allocation Failed!!, Exiting now ! ");
        exit(1);
    }
}

//The following function check allocation for int array
void checkAllocInt(int* arr)
{
    if (arr == NULL)
    {
        printf("Memory Allocation Failed!!, Exiting now ! ");
        exit(1);
    }
}

//The following function check allocation for YNode
void checkAllocYListNode(YListNode* yNode)
{
    if (yNode == NULL)
    {
        printf("Memory Allocation Failed!!, Exiting now ! ");
        exit(1);
    }
}

//The following function check allocation for XNode
void checkAllocXListNode(XListNode* xNode)
{
    if (xNode == NULL)
    {
        printf("Memory Allocation Failed!!, Exiting now ! ");
        exit(1);
    }
}

//The following function checks if the Xlist is empty
bool isEmptyXlist(List list)
{
    if (list.xHead == NULL)
        return true;
    return false;
}

//The following function checks if the Ylist is empty
bool isEmptyYlist(YList list)
{
    if (list.yHead == NULL)
        return true;
    return false;
}

//The following function checks if the specific x is inside list
bool xIsInside(List list, int x)
{
    XListNode* curr = list.xHead;
    while (curr != NULL)
    {
        if (curr->xData == x)
        {
            return true;
        }
        curr = curr->xNext;
    }
    return false;
}