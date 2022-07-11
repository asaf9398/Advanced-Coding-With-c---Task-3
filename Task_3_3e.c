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
#define INITIALIZE_NUM 0
#define FIRST_ARRAY_CELL 0
#define ZERO_APPEARENCE 0
#define NOT_INSIDE 1
#define ONE_TIME 1
#define SINGLE_XY_OCCURENCE 3
#define NOT_SINGLE_XY_OCCURENCE 0
#define MORE_THAN_ONE_OCCURENCE 2


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
unsigned int getYOccurrences(List coord_list, int y);
int countYInYList(YList lst, int y);
int convertTokenToInt(char* token);
unsigned int getXOccurrences(List coord_list, int x);
int numOfYCoordinate(XListNode* curr);
int insertCoordinate(List* coord_list, int x, int y);
bool yIsInside(List lst, int x, int y);
void printList(List* coordList);
void printYCoordinates(XListNode* currX);
int removeCoordinate(List* coord_list, int x, int y);
int findXY(List* list, int x, int y, XListNode** XlistP);
void removeYNode(XListNode* currX, int y);
void removeXNode(List* coord_list, XListNode* node);

void main()

{

    List coordList;

    int x, y;

    int res;

    coordList = getCoordList();

    // get the (x,y) to remove

    scanf("%d%d", &x, &y);



    res = removeCoordinate(&coordList, x, y);

    if (res == 1)

        printf("The point (%d,%d) didn't appear\n", x, y);

    else if (res == 2)

        printf("The point (%d,%d) has another occurrence\n", x, y);

    else if (res == 3)

        printf("The point (%d,%d) was the only point with this x\n", x, y);

    else

        printf("Other\n");

    printf("Updated list: ");

    printList(&coordList);

    freeList(&coordList);

}

//The following function returns how many times is (x,y) in list + the pointer for this specific XListNode
int findXY(List * list,int x,int y,XListNode ** XlistP)
{
    int counter = INITIALIZE_COUNTER;
    //checking list not empty
    if (isEmptyXlist(*list))
    {
        return ZERO_APPEARENCE;//if list is empty -> return 0 
    }
    else
    {
        //checking x is inside
        if (!xIsInside(*list,x))
        {
            //if x is not inside -> return 0 
            return ZERO_APPEARENCE;
        }
        else
        {
            //if x is inside -> check number of y appearence
            XListNode* currX = list->xHead;
            while (currX->xData != x)
            {
                currX = currX->xNext;//find that XListNode that contain x
            }
            YListNode* currY = currX->yPointsList.yHead;
            while (currY!=NULL)
            {
                if (currY->yData == y)
                {
                    counter++;//counting number of time that (x,y) is int the list
                }
                currY = currY->yNext;
            }
            *XlistP = currX;
            return counter;
        }        
    }
}

//The following function removes y from currX's yList
void removeYNode(XListNode* currX, int y)
{
    YListNode* prev;
    YListNode* curr;
    if (currX->yPointsList.yHead->yData == y)//delete head
    {
        if (currX->yPointsList.yHead == currX->yPointsList.yTail)//checking if there is only one node
        {
            free(currX->yPointsList.yHead);//free unused memory
            currX->yPointsList.yHead = currX->yPointsList.yTail = NULL;
        }
        else//there is more than one node -> delete the head
        {
            prev = currX->yPointsList.yHead;
            currX->yPointsList.yHead = currX->yPointsList.yHead->yNext;//changing head
            free(prev);//free unused memory
        }
    }
    else//y is in the middle or in the end
    {
        prev = currX->yPointsList.yHead;
        curr = prev->yNext;
        while (curr->yData != y)//go to the node that contains y
        {
            prev = prev->yNext;
            curr = curr->yNext;
        }
        if (curr == currX->yPointsList.yTail)//if it is tail -> change it 
        {
            prev->yNext = NULL;
            currX->yPointsList.yTail = prev;
            free(curr);//free unused memory
        }
        else//if it is not tail -> it is between nodes
        {
            prev->yNext = curr->yNext;//jump over curr
            free(curr);//free unused memory
        }
    }
}

//The following function removes X from List
void removeXNode(List* coord_list, XListNode* node)
{
    if (coord_list->xHead == coord_list->xTail) // == node)
        coord_list->xHead = coord_list->xTail = NULL;
    else if (coord_list->xHead == node) // or node->prev == NULL
    {
        coord_list->xHead = coord_list->xHead->xNext;
        coord_list->xHead->xPrev = NULL;
    }
    else if (coord_list->xTail == node) // or node->next == NULL
    {
        coord_list->xTail = coord_list->xTail->xPrev;
        coord_list->xTail->xNext = NULL;
    }
    else
    {
        node->xPrev->xNext = node->xNext;
        node->xNext->xPrev = node->xPrev;
    }
    free(node);
}

//The following function gets a list and removes (x,y) from the list
//The function returns integer according to the mission's request 
int removeCoordinate(List* coord_list, int x, int y)
{
    XListNode* currX;
    int numOfTimes=findXY(coord_list, x,y,&currX);
    if (numOfTimes == ZERO_APPEARENCE)
    {
        return NOT_INSIDE;
    }
    else
    {
        if (numOfTimes == ONE_TIME)
        {
            if (currX->yPointsList.yHead == currX->yPointsList.yTail)//if there is only one node
            {
                //remove y node
                removeYNode(currX, y);
                //remove X node
                removeXNode(coord_list,currX);
                return SINGLE_XY_OCCURENCE;
            }
            else//there is more than one y
            {
                //remove y node
                removeYNode(currX, y);
                return NOT_SINGLE_XY_OCCURENCE;
            }
        }
        else
        {
            if (numOfTimes > ONE_TIME)//it means that we have more that one node in yList
            {
                //remove y node
                removeYNode(currX, y);
                return MORE_THAN_ONE_OCCURENCE;
            }
        }
        
    }

}

//The following function helo to print the list
void printYCoordinates(XListNode* currX)
{
    YListNode* currY = currX->yPointsList.yHead;
    while (currY != NULL)
    {
        printf("(%d,%d), ",currX->xData,currY->yData);
        currY = currY->yNext;
    }

}

//The following function prints the list
void printList(List* coordList)
{
    XListNode * currX = coordList->xHead;
    while (currX!=NULL)
    {
        printYCoordinates(currX);
        currX = currX->xNext;
    }
}

//The following function gets list + (x,y) coordinate and returns if the y is inside
//The function assuming that x is inside
bool yIsInside(List lst, int x, int y)
{
    XListNode* curr = lst.xHead;
    while (curr->xData != x)//getting to the x we search for
    {
        curr = curr->xNext;
    }
    YListNode* currY = curr->yPointsList.yHead;
    while (currY != NULL)//searching the y point
    {
        if (currY->yData == y)
            return true;//if we found it -> get out
        currY = currY->yNext;//else -> keep looking
    }
    return false;//if you got to the end of the list and you didn't found y -> return false
}

int insertCoordinate(List* coord_list, int x, int y)
{

    if (xIsInside(*coord_list, x))//checking if the x value inside that list
    {
        if (yIsInside(*coord_list, x, y))//if y is inside -> add the dot and retun 1
        {
            addYcoordinate(*coord_list, x, y);//if x is inside -> add the y to that x
            return 1;
        }
        else//if y is not inside -> add the dot and retun 0
        {
            addYcoordinate(*coord_list, x, y);//if x is inside -> add the y to that x
            return 0;
        }
    }
    else//if X not inside -> add point and return 0
    {
        addXcoordinate(coord_list, x, y);//if the x isn't inside add it to the list
        addYcoordinate(*coord_list, x, y);//add the y to the list
        return 0;
    }
}

//The following function gets a XListNode and returns how many y coordinates it has
int numOfYCoordinate(XListNode* xNode)
{
    int counter = INITIALIZE_COUNTER;
    YListNode* curr = xNode->yPointsList.yHead;
    while (curr!=NULL)
    {
        counter++;
        curr = curr->yNext;
    }
    return counter;
}

unsigned int getXOccurrences(List coord_list, int x)
{
    XListNode* curr = coord_list.xHead;
    while (curr != NULL)
    {
        if (curr->xData == x)//than check how many y dots it has
        {
            return numOfYCoordinate(curr);
        }
        curr = curr->xNext;
    }

}

//The following function gets YList + y coordinate and returns how many times y appears
int countYInYList(YList lst, int y)
{
    YList tmp;//just a local list for not being able to change the original list(and easier work)
    tmp = lst;
    YListNode* curr = tmp.yHead;
    int counter = INITIALIZE_COUNTER;
    while (curr != NULL)
    {
        if (curr->yData == y)//counting the y appeareces
        {
            counter++;
        }
        curr = curr->yNext;
    }
    return counter;
}

//The following function returns how many times is y in the XList
unsigned int getYOccurrences(List coord_list, int y)
{
    int counter = INITIALIZE_COUNTER;
    XListNode* currX = coord_list.xHead;
    while (currX != NULL)
    {
        counter += countYInYList(currX->yPointsList, y);
        currX = currX->xNext;
    }
    return counter;

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
    for (ind = FIRST_X_POINT_CELL; ind < numOfPoints * NUM_OF_INTEGERS_IN_POINT; ind += NUM_OF_INTEGERS_IN_POINT)
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
void addXcoordinate(List* list, int x, int y)
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

int convertTokenToInt(char* token)
{
    int num = INITIALIZE_NUM;
    int ind = FIRST_ARRAY_CELL;
    while (*(token + ind) - END_OF_STRING != SAME)
    {
        num *= 10;
        num += *(token + ind) - ZERO_CHAR;
        ind++;
    }
    return num;

}

//The following function gets the user's input and returns array of points
int* getPoints(char* userInput, int* numOfPoints)
{
    char* seps = " ";
    char* token = strtok(userInput, seps);
    //int size = (*token) - ZERO_CHAR;//getting the number of points from the input
    int size = convertTokenToInt(token);
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