#include "linkedList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ALL true

/* Keep the core list implementation independent of OpenCV headers. */
void play(FrameNode* list);

static void freeFrameNode(FrameNode* node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->frame != NULL)
    {
        free(node->frame->name);
        free(node->frame->path);
        free(node->frame);
    }
    free(node);
}

void myFgets(char str[], int n)
{
    if (str == NULL || n <= 0)
    {
        return;
    }

    if (fgets(str, n, stdin) == NULL)
    {
        str[0] = '\0';
        return;
    }
    str[strcspn(str, "\n")] = 0;
}

Frame* checkName(FrameNode** head, char* frameName)
{
    FrameNode* current;

    if (head == NULL || frameName == NULL)
    {
        return NULL;
    }

    current = *head;
    while (current != NULL)
    {
        if (current->frame != NULL && current->frame->name != NULL &&
            strcmp(current->frame->name, frameName) == 0)
        {
            return current->frame;
        }
        current = current->next;
    }
    return NULL;
}

bool exectedCheckPath(char* framePath)
{
    FILE* pic;

    if (framePath == NULL || framePath[0] == '\0')
    {
        return false;
    }

    pic = fopen(framePath, "rb");
    if (pic == NULL)
    {
        return false;
    }
    fclose(pic);
    return true;
}

void createFrame(char* frameName, char* framePath, int frameTime, FrameNode** head)
{
    FrameNode* newNode = NULL;
    FrameNode* current = NULL;
    Frame* frame = NULL;

    if (head == NULL || frameName == NULL || framePath == NULL)
    {
        return;
    }

    if (!exectedCheckPath(framePath))
    {
        printf("Can't find file! Frame will not be added\n");
        return;
    }

    while (checkName(head, frameName) != NULL)
    {
        printf("The name is already taken, please enter another name\n");
        myFgets(frameName, SIZE);
        if (frameName[0] == '\0')
        {
            return;
        }
    }

    frame = (Frame*)calloc(1, sizeof(Frame));
    newNode = (FrameNode*)calloc(1, sizeof(FrameNode));
    if (frame == NULL || newNode == NULL)
    {
        free(frame);
        free(newNode);
        fprintf(stderr, "Failed to allocate frame\n");
        return;
    }

    frame->name = (char*)malloc(strlen(frameName) + 1);
    frame->path = (char*)malloc(strlen(framePath) + 1);
    if (frame->name == NULL || frame->path == NULL)
    {
        newNode->frame = frame;
        freeFrameNode(newNode);
        fprintf(stderr, "Failed to allocate frame strings\n");
        return;
    }

    strcpy(frame->name, frameName);
    strcpy(frame->path, framePath);
    frame->duration = frameTime;
    newNode->frame = frame;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}

void removeFrame(FrameNode** head, char* frameName)
{
    FrameNode* current;
    FrameNode* previous = NULL;

    if (head == NULL || *head == NULL || frameName == NULL)
    {
        printf("The frame was not found");
        return;
    }

    current = *head;
    while (current != NULL)
    {
        if (current->frame != NULL && current->frame->name != NULL &&
            strcmp(current->frame->name, frameName) == 0)
        {
            if (previous == NULL)
            {
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            freeFrameNode(current);
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("The frame was not found");
}

int getLen(FrameNode** head)
{
    FrameNode* current;
    int count = 0;

    if (head == NULL)
    {
        return 0;
    }

    current = *head;
    while (current != NULL)
    {
        ++count;
        current = current->next;
    }
    return count;
}

void changeDuration(FrameNode** head, unsigned int time, char* nameFrame)
{
    Frame* needed = checkName(head, nameFrame);
    if (needed == NULL)
    {
        printf(ERRORE_FILE_NOT_FOUND);
        return;
    }
    needed->duration = (int)time;
}

void moveFrame(FrameNode** head, char* frameName, int newPosition)
{
    FrameNode* current;
    FrameNode* previous = NULL;
    FrameNode* frameNode = NULL;
    FrameNode* frameNodePrev = NULL;
    int index;
    int length;

    if (head == NULL || *head == NULL || frameName == NULL)
    {
        return;
    }

    length = getLen(head);
    if (newPosition < 1 || newPosition > length)
    {
        return;
    }

    current = *head;
    while (current != NULL)
    {
        if (current->frame != NULL && current->frame->name != NULL &&
            strcmp(current->frame->name, frameName) == 0)
        {
            frameNode = current;
            frameNodePrev = previous;
            break;
        }
        previous = current;
        current = current->next;
    }

    if (frameNode == NULL)
    {
        return;
    }

    if (frameNodePrev == NULL)
    {
        *head = frameNode->next;
    }
    else
    {
        frameNodePrev->next = frameNode->next;
    }

    current = *head;
    previous = NULL;
    for (index = 1; index < newPosition && current != NULL; ++index)
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
}

void print(FrameNode** head)
{
    FrameNode* current;

    if (head == NULL)
    {
        return;
    }

    current = *head;
    printf("\tName\tduration(ms)\tPath\n");
    while (current != NULL)
    {
        printf("\t%s\t%d\t%s\n", current->frame->name, current->frame->duration, current->frame->path);
        current = current->next;
    }
}

void changeDicForAll(FrameNode** head, unsigned int duration)
{
    FrameNode* current;

    if (head == NULL)
    {
        return;
    }

    current = *head;
    while (current != NULL)
    {
        current->frame->duration = (int)duration;
        current = current->next;
    }
}

void playTheGif(FrameNode** head)
{
    FrameNode* current;

    if (head == NULL)
    {
        return;
    }

    current = *head;
    while (current != NULL)
    {
        play(current);
        current = current->next;
    }
}

void addFrame(FrameNode** head)
{
    int frameTime = 0;
    char frameName[SIZE] = { 0 };
    char framePath[SIZE] = { 0 };

    printf("*** Creating new frame ***\n");
    printf("Please insert frame path:\n");
    myFgets(framePath, SIZE);
    printf("Please insert frame duration(in miliseconds):\n");
    if (scanf("%d", &frameTime) != 1)
    {
        return;
    }
    getchar();
    printf("Please choose a name for that frame:\n");
    myFgets(frameName, SIZE);
    createFrame(frameName, framePath, frameTime, head);
}

bool checkExitend(FrameNode** head, char* frameName)
{
    if (checkName(head, frameName) == NULL)
    {
        printf(ERRORE_FILE_NOT_FOUND);
        return false;
    }
    return true;
}

void deleteFrame(FrameNode** head)
{
    char frameName[SIZE] = { 0 };
    printf("Enter the name of the frame you wish to erase\n");
    myFgets(frameName, SIZE);
    removeFrame(head, frameName);
}

void changePossionOfFrame(FrameNode** head)
{
    char nameFrame[SIZE] = { 0 };
    int position = 0;
    int len = getLen(head);

    printf("Enter the name of the frame:\n");
    myFgets(nameFrame, SIZE);
    if (!checkExitend(head, nameFrame))
    {
        return;
    }

    printf("Enter the new position:\n");
    if (scanf("%d", &position) != 1)
    {
        return;
    }
    getchar();

    while (position < 1 || position > len)
    {
        printf("The movie contains only %d frames!\n", len);
        printf("Enter the new index in the movie you wish to place the frame\n");
        if (scanf("%d", &position) != 1)
        {
            return;
        }
        getchar();
    }
    moveFrame(head, nameFrame, position);
}

unsigned int getDuration(FrameNode** head, bool all)
{
    unsigned int duration = 0;
    printf("enter new duration:\n");
    if (scanf("%u", &duration) != 1)
    {
        return 0;
    }
    getchar();

    if (all)
    {
        changeDicForAll(head, duration);
        return 0;
    }
    return duration;
}

void changeTime(FrameNode** head)
{
    unsigned int time;
    char nameFrame[SIZE] = { 0 };

    printf("enter the name of the frame:\n");
    myFgets(nameFrame, SIZE);
    if (checkExitend(head, nameFrame))
    {
        time = getDuration(head, !ALL);
        changeDuration(head, time, nameFrame);
    }
}
