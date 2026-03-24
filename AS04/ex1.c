#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

/* Based on Lec06 style: allocate a new node */
struct node* nalloc(int data)
{
    struct node* p = (struct node*)malloc(sizeof(struct node));
    if (p != NULL)
    {
        p->data = data;
        p->next = NULL;
    }
    return p;
}

/* Display all elements */
void display(struct node* head)
{
    struct node* p;

    for (p = head; p != NULL; p = p->next)
        printf("%d ", p->data);

    printf("\n");
}

/* Add element to the back of the list */
struct node* addback(struct node* head, int data)
{
    struct node* p;
    struct node* newnode = nalloc(data);

    if (newnode == NULL)
        return head;

    if (head == NULL)
        return newnode;

    for (p = head; p->next != NULL; p = p->next)
        ;
    p->next = newnode;

    return head;
}

/* Find first node having the given data */
struct node* find(struct node* head, int data)
{
    struct node* p;

    for (p = head; p != NULL; p = p->next)
    {
        if (p->data == data)
            return p;
    }

    return NULL;
}

/* Delete the node pointed to by pelement */
struct node* delnode(struct node* head, struct node* pelement)
{
    struct node* p;

    if (head == NULL || pelement == NULL)
        return head;

    /* case 1: delete head */
    if (head == pelement)
    {
        head = head->next;
        free(pelement);
        return head;
    }

    /* case 2: find previous node */
    for (p = head; p != NULL && p->next != pelement; p = p->next)
        ;

    if (p != NULL)
    {
        p->next = pelement->next;
        free(pelement);
    }

    return head;
}

/* Delete entire list */
void freelist(struct node* head)
{
    struct node* p;

    while (head != NULL)
    {
        p = head;
        head = head->next;
        free(p);
    }
}

/* Test code */
int main(void)
{
    struct node* head = NULL;
    struct node* pelement;

    head = addback(head, 12);
    head = addback(head, 99);
    head = addback(head, 37);
    head = addback(head, 15);

    printf("Initial list: ");
    display(head);

    pelement = find(head, 99);
    if (pelement != NULL)
        printf("Found: %d\n", pelement->data);
    else
        printf("99 not found\n");

    pelement = find(head, 12);
    head = delnode(head, pelement);
    printf("After deleting 12: ");
    display(head);

    pelement = find(head, 37);
    head = delnode(head, pelement);
    printf("After deleting 37: ");
    display(head);

    pelement = find(head, 100);
    if (pelement == NULL)
        printf("100 not found\n");

    freelist(head);
    head = NULL;

    printf("After freelist: ");
    display(head);

    return 0;
}
