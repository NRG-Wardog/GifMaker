#include "openAndEditProg.h"
#include "linkedList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define RAW 3
#define SEC 1
#define SAPARTION ','

void saveProject(FrameNode** head)
{
    FILE* project = NULL;
    FrameNode* current = NULL;
    char projectPath[SIZE] = { 0 };
    printf("Where to save the project? enter a full path and file name");
    myFgets(projectPath, SIZE);
    project = fopen(projectPath, "w");
    current = *head;
    printf("    Name    duration(ms)    Path\n");
    while (current != NULL) {
        fprintf(project, "%s,%d,%s\n", current->frame->path, current->frame->duration, current->frame->name );
        current = current->next;
    }
}

FrameNode** createNewProject(FrameNode** head) {
    char projectPath[SIZE] = { 0 };
    FILE* project = NULL;
    int frameTime = 0;
    char ch;
    int count = 0;
    int i = 0;
    int len = 0;
    char word[RAW][SIZE] = { 0 };

    printf("Enter the path of the project (including project name): ");
    myFgets(projectPath, SIZE);
    project = fopen(projectPath, "r");
    if (project == NULL) {
        printf("Error! Can't open file, creating a new project.\n");
        return NULL;
    }

    while ((ch = fgetc(project)) != EOF) {
        if (ch == SAPARTION) {
            count++;
        }
        else if (ch == '\n') {
            count = 0;
            frameTime = atoi(word[SEC]);
            createFrame(word[2], word[0], frameTime, head);
            for (i = 0; i < RAW; i++) {
                word[i][0] = '\0'; 
            }
        }
        else {
            len = strlen(word[count]);
            word[count][len] = ch;
            word[count][len + 1] = '\0'; 
        }
    }

    fclose(project);
    return head;
}