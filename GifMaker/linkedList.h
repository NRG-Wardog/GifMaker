#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#define SIZE 250
#define ERRORE_FILE_NOT_FOUND "this frame does not exist"
#define ALL true

// Frame struct
typedef struct Frame
{
    char* name;
    char* path;
    int duration;
} Frame;

// Link (node) struct
typedef struct FrameNode
{
    Frame* frame;
    struct FrameNode* next;
} FrameNode;

void createFrame(char* frameName, char* framePath, int frameTime, FrameNode** head);
void removeFrame(FrameNode** head, char* frameName);
int getLen(FrameNode** head);
void changeDuration(FrameNode** head, unsigned int time, char* nameFrame);
void moveFrame(FrameNode** head, char* frameName, int newPosition);
void myFgets(char str[], int n);
void print(FrameNode** head);
void changeDicForAll(FrameNode** head, unsigned int duration);
void playTheGif(FrameNode** head);
bool exectedCheckPath(char* framePath);
Frame* checkName(FrameNode** head,char* frameName);
void addFrame(FrameNode** head);
void deleteFrame(FrameNode** framesNode);
void changeTime(FrameNode** head);
void changePossionOfFrame(FrameNode** head);
unsigned int getDuration(FrameNode** head, bool all);
bool checkExitend(FrameNode** head, char* name);

#endif
