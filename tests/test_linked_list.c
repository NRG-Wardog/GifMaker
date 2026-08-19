#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

/* linkedList.c calls playTheGif() through this symbol; core tests do not need OpenCV. */
void play(FrameNode* list)
{
    (void)list;
}

static void free_list(FrameNode** head)
{
    FrameNode* current = *head;
    while (current != NULL)
    {
        FrameNode* next = current->next;
        free(current->frame->name);
        free(current->frame->path);
        free(current->frame);
        free(current);
        current = next;
    }
    *head = NULL;
}

int main(void)
{
    FrameNode* head = NULL;
    char name1[] = "first";
    char name2[] = "second";
    char name3[] = "third";
    char fixture[] = "gifmaker-test-frame.tmp";
    FILE* file = fopen(fixture, "wb");

    assert(file != NULL);
    fputs("frame", file);
    fclose(file);

    /* Empty-list operations must be safe. */
    removeFrame(&head, "missing");
    moveFrame(&head, "missing", 1);
    assert(getLen(&head) == 0);

    createFrame(name1, fixture, 100, &head);
    createFrame(name2, fixture, 200, &head);
    createFrame(name3, fixture, 300, &head);

    assert(getLen(&head) == 3);
    assert(strcmp(head->frame->name, "first") == 0);
    assert(checkName(&head, "second") != NULL);

    changeDuration(&head, 450, "second");
    assert(checkName(&head, "second")->duration == 450);

    changeDicForAll(&head, 250);
    assert(checkName(&head, "first")->duration == 250);
    assert(checkName(&head, "second")->duration == 250);
    assert(checkName(&head, "third")->duration == 250);

    moveFrame(&head, "third", 1);
    assert(strcmp(head->frame->name, "third") == 0);
    assert(strcmp(head->next->frame->name, "first") == 0);

    moveFrame(&head, "third", 3);
    assert(strcmp(head->frame->name, "first") == 0);
    assert(strcmp(head->next->frame->name, "second") == 0);
    assert(strcmp(head->next->next->frame->name, "third") == 0);

    /* Invalid requests must not corrupt the list. */
    moveFrame(&head, "missing", 2);
    moveFrame(&head, "first", 99);
    assert(getLen(&head) == 3);
    assert(strcmp(head->frame->name, "first") == 0);

    removeFrame(&head, "second");
    assert(getLen(&head) == 2);
    assert(checkName(&head, "second") == NULL);

    removeFrame(&head, "first");
    assert(getLen(&head) == 1);
    assert(strcmp(head->frame->name, "third") == 0);

    removeFrame(&head, "third");
    assert(head == NULL);

    free_list(&head);
    remove(fixture);
    puts("GifMaker linked-list tests passed.");
    return 0;
}
