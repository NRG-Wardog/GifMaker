#include "linkedList.h"
#include "view.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SIZE 250
#define ERRORE_FILE_NOT_FOUND "this frame does not exist.\n"
#define ALL true

/*
Function will perform the fgets command and also remove the newline
that might be at the end of the string - a known issue with fgets.
input: the buffer to read into, the number of chars to read
*/
void myFgets(char str[], int n)
{
    fgets(str, n, stdin);
    str[strcspn(str, "\n")] = 0;
}

/*
func check if there is a frame name the same as frame name
input: address of the head FrameNode, name of frame
output: pointer to Frame if found, NULL otherwise
*/
Frame* checkName(FrameNode** head,char* frameName)
{
    FrameNode* current = *head;
    while (current != NULL)
    {
        if (strcmp(current->frame->name, frameName) == 0)
        {
            return current->frame;
        }
        current = current->next;
    }
    return NULL;
}

/*
func check if the path exists
input: path of the frame
output: true or false
*/
bool exectedCheckPath(char* framePath)
{
    FILE* pic = fopen(framePath, "r");

    if (pic == NULL)
    {
        return false;
    }
    fclose(pic);
    return true;
}

/*
func create a frame
input: frame name, frame path, frame time, address of the head FrameNode
output: true if frame created successfully, false otherwise
*/
void createFrame(char* frameName, char* framePath, int frameTime, FrameNode** head)
{
    FrameNode* newNode = NULL;
    FrameNode* current = NULL;
    Frame* temp = NULL;

    if (!exectedCheckPath(framePath))
    {
        printf("Can't find file! Frame will not be added\n");
    }
    else
    {
        while (checkName(head, frameName) != NULL)
        {
            printf("The name is already taken, please enter another name\n");
            myFgets(frameName, SIZE);
        }

        temp = (Frame*)malloc(sizeof(Frame));
        temp->name = (char*)malloc(strlen(frameName) + 1);
        temp->path = (char*)malloc(strlen(framePath) + 1);

        strcpy(temp->name, frameName);
        strcpy(temp->path, framePath);
        temp->duration = frameTime;

        newNode = (FrameNode*)malloc(sizeof(FrameNode));
        newNode->frame = temp;
        newNode->next = NULL;

        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        {
            current = *head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }
}


/*
func remove a frame from node
input: address of the head FrameNode, frame name
output: true if frame removed successfully, false otherwise
*/
void removeFrame(FrameNode** head, char* frameName)
{
    FrameNode* current = *head;
    FrameNode* previous = NULL;
    bool change = false;
    do{
        if (strcmp(current->frame->name, frameName) == 0)
        {
            if (previous == NULL)
            {
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current->frame->name);
            free(current->frame->path);
            free(current->frame);
            free(current);
            change = true;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }while ((current != NULL && !change));
    !change ? printf("The frame was not found") : (void)0;//Shawn this is so cool understood from stackoverflow
}

/*
func count how many frames in the list
input: address of the head FrameNode
output: the length of the list
*/
int getLen(FrameNode** head)
{
    FrameNode* current = *head;
    int count = 0;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

/*
Function to change the duration of a frame
input: address of the head FrameNode, new duration, frame name
output: true if duration changed successfully, false otherwise
*/
void changeDuration(FrameNode** head, unsigned int time, char* nameFrame)
{
    Frame* needed = checkName(head, nameFrame);
    if (needed == NULL)
    {
        printf(ERRORE_FILE_NOT_FOUND);
    }
    else
    {
        needed->duration = time;
    }
}

/*
Function moves a frame to a new position in the list
input: pointer to the head FrameNode, frame name, new position
output: true if successful, false otherwise
*/
void moveFrame(FrameNode** head, char* frameName, int newPosition)
{
    FrameNode* current = *head;
    FrameNode* previous = NULL;
    FrameNode* frameNode = NULL;
    FrameNode* frameNodePrev = NULL;
    int i = 0;

    //find frame
    while (current != NULL)
    {
        if (strcmp(current->frame->name, frameName) == 0)
        {
            frameNode = current;
            frameNodePrev = previous;
            break;
        }
        previous = current;
        current = current->next;
    }

    // Remove frame 
    if (frameNodePrev == NULL)
    {
        *head = frameNode->next;
    }
    else
    {
        frameNodePrev->next = frameNode->next;
    }

    // Insert the frame to the new position
    current = *head;
    previous = NULL;
    for (i = 1; i < newPosition; i++)
    {
        previous = current;
        current = current->next;
    }

    if (previous == NULL)
    {
        frameNode->next = *head;
        *head = frameNode;
    }
    else
    {
        frameNode->next = current;
        previous->next = frameNode;
    }

    return true;
}

/*
func print the list
input:pointer head of the list
output:none
*/
void print(FrameNode** head)
{
    FrameNode* current = *head;
    printf("\tName\tduration(ms)\tPath\n");
    while(current!=NULL)
    {
        printf("\t%s\t%d\t%s\n",current->frame->name, current->frame->duration, current->frame->path);
        current = current->next;
    }
}

/*
func change time of frame for all the frames
input:pointer head of list , int time to change
output:none
*/
void changeDicForAll(FrameNode** head, unsigned int duration)
{
    FrameNode* current = *head;
    while (current != NULL)
    {
        current->frame->duration = duration;
        current = current->next;
    }
}

/*
func play all the frames
input:pointer for the head of the list
output:none
*/
void playTheGif(FrameNode** head)
{
    FrameNode* current = *head;
    while (current != NULL)
    {
        play(current);
        current = current->next;
    }
}




/*
func add a frame
input:adress of the gead fremeNode
output:none
*/
void addFrame(FrameNode** head)
{
    int frameTime = 0;
    char frameName[SIZE] = { 0 };
    char framePath[SIZE] = { 0 };
    printf("*** Creating new frame ***\n");
    printf("Please insert frame path:\n");
    myFgets(framePath, SIZE);
    printf("Please insert frame duration(in miliseconds):\n");
    scanf("%d", &frameTime);
    getchar();
    printf("Please choose a name for that frame:\n");
    myFgets(frameName, SIZE);
    createFrame(frameName, framePath, frameTime, head);
}

/*
func use the func check name for auto printing the not found message
input:pointer for head of list,name of frame
output:bool(false or true)
*/
bool checkExitend(FrameNode** head, char* frameName)
{
    if (checkName(head, frameName) == NULL)
    {
        printf(ERRORE_FILE_NOT_FOUND);
        return false;
    }
    return true;

}
/*
func erase a frame
input:adrees of the gead fremeNode
output:none
*/
void deleteFrame(FrameNode** head)
{
    char frameName[SIZE] = { 0 };
    printf("Enter the name of the frame you wish to erase\n");
    myFgets(frameName, SIZE);
    removeFrame(head, frameName);
}



/*
Function to change the position of a frame in the linked list
input: address of the head FrameNode
output: none
*/
void changePossionOfFrame(FrameNode** head)
{
    char nameFrame[SIZE] = { 0 };
    int position = 0;
    int len = getLen(head);
    printf("Enter the name of the frame:\n");
    myFgets(nameFrame, SIZE);
    if (checkExitend(head, nameFrame))
    {
        printf("Enter the new position:\n");
        scanf("%d", &position);
        getchar();

        while(position < 1 || position > len) {
            printf("The movie contains only %d frames!\n", len);
            printf("Enter the new index in the movie you wish to place the frame\n");
            scanf("%d", &position);
            getchar();
        }
        moveFrame(head, nameFrame, position);
    }
}


/*
func get a duration input and if for all 
intput:head of the list, all?
output:none
*/
unsigned int getDuration(FrameNode** head,bool all)
{
    unsigned int duration = 0;
    printf("enter new duration:\n");
    scanf("%d", &duration);
    getchar();
    if (all)
    {
        changeDicForAll(head, duration);
    }
    else
    {
        return duration;
    }
}


/*
func change the  duration
input:head of framenode
output:none
*/
void changeTime(FrameNode** head)
{
    unsigned int time = 0;
    char nameFrame[SIZE] = { 0 };
    printf("enter the name of the frame:\n");
    myFgets(nameFrame, SIZE);
    if (checkExitend(head, nameFrame))
    {
        time = getDuration(head, !ALL);
        changeDuration(head, time, nameFrame);
    }
}
