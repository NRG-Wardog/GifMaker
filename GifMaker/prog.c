/*********************************
* Class: MAGSHIMIM C2			 *
* openCV template      			 *
**********************************/
#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "linkedList.h"
#include "view.h"
#include "openAndEditProg.h"
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>


void freeAll(FrameNode** head);
void menu(FrameNode** head);
void printMenu();



int main()
{
	FrameNode* framesNode = NULL; 

	menu(&framesNode); 

	freeAll(&framesNode);

	return 0;
}

/*
func print the menu
input:none
output:none
*/
void printMenu() 
{
	printf("\nWhat would you like to do ?\n");
	printf("[0] Exit\n");
	printf("[1] Add new Frame\n");
	printf("[2] Remove a Frame\n");
	printf("[3] Change frame index\n");
	printf("[4] Change frame duration\n");
	printf("[5] Change duration of all frames\n");
	printf("[6] List frames\n");
	printf("[7] Play movie!\n");
	printf("[8] Save project\n");
}
/*
func print the start menu
input:none
output:none
*/
void printStartMenu()
{
	printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	printf("[0] Create a new project\n");
	printf("[1] Load existing project\n");
}

/*
func the main menu move for the choise
input:head
output:none
*/
void menu(FrameNode** head)
{
	int choise = 0;
	FrameNode** current = NULL;
	bool flag = true;
	while(flag)
	{
		printStartMenu();
		scanf("%d", &choise);
		getchar();
		switch (choise)
		{
			case 0:
				flag = false;
				current = head;
				printf("Working on a new project.\n");
				break;
			case 1:
				flag = false;
				current = createNewProject(head);
				if (current == NULL)
				{
					current = head;
				}
				break;
			default:
				printf("Invalid choice, try again:");
				break;
		}
	}
	flag = true;
	while (flag)
	{
		printMenu();
		scanf("%d", &choise);
		getchar();
		switch (choise)
		{
			case 0:
				flag = false;
				printf("bye!");
				break;
			case 1:
				addFrame(current);
				break;
			case 2:
				deleteFrame(current);
				break;
			case 3:
				changePossionOfFrame(current);
				break;
			case 4:
				changeTime(current);
				break;
			case 5:
				getDuration(current,ALL);
				break;
			case 6:
				print(current);
				break;
			case 7:
				playTheGif(current);
				break;
			case 8:
				saveProject(current);
			default:
				break;
		}
	}
}

/*
func free evrey danmic memory
input: adrees of the gead fremeNode
output:none
*/
void freeAll(FrameNode** head) {
	FrameNode* current = *head;
	FrameNode* next = NULL;
	while (current != NULL) {
		next = current->next;
		free(current->frame->name);
		free(current->frame->path);
		free(current->frame);
		free(current);
		current = next;
	}
	*head = NULL;
}

