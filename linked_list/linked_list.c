#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node
{
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node -> data = new_data;
    
    new_node->next = (*head_ref);

    (*head_ref) = new_node;
}

int GetNth(struct Node* head, int index)
{
    struct Node* current = head;
    int count = 0;
    while (current != NULL)
    {
        if(count == index)
            return(current->data);
        count++;
        current = current->next;
    }
        /* if we get to this line,  
    the caller was asking  
    for a non-existent element  
    so we assert fail */
    assert(0);
}

void printList(struct Node *ptr) 
{ 
    while (ptr != NULL) 
    { 
        printf("%d \n", ptr->data); 
        ptr = ptr->next; 
    } 
    printf("NULL\n"); 
} 

void deleteList(struct Node** head_ref) 
{ 
   /* deref head_ref to get the real head */
   struct Node* current = *head_ref; 
   struct Node* next; 
  
   while (current != NULL)  
   { 
       next = current->next; 
       free(current); 
       current = next; 
   } 
    
   /* deref head_ref to affect the real head back 
      in the caller. */
   *head_ref = NULL; 
} 

void deleteNode(struct Node **head_ref, int position)
{
    // If the linked list is empty throw an error and exit
    if (*head_ref == NULL)
    {
        fprintf(stderr, "Head is empty, Abort\n");
        exit(EXIT_FAILURE);
    }

    //make a temporary node to store the current data
    struct Node * temp = *head_ref;

    if (position == 0)
    {
        *head_ref = temp->next;  //change the current head to next node
        free(temp);  // release the old head 
        return;
    }

    //Since the linked list does not have a previous, we traverse it until we 
    //at the Node before the one we want to delete
    for (int i=0; temp->next != NULL && i<position-1; i++)
        temp = temp->next;

    //if the position is beyond the range of the list print the list, 
    //then delete the list, and exit
    if (temp == NULL || temp->next == NULL)
    {
        fprintf(stderr, "Position is larger than range of list\n");
        printList(*head_ref); 
        deleteList(head_ref); 
        exit(EXIT_FAILURE);
    }
    
    // Node temp->next is the node to be deleted, store pointer
    // of the node after the one we are deleting
    struct Node *next = temp->next->next;

    //free node memory from linked list
    free(temp->next);
    
    //link the current node to the node after the one you deleted
    temp->next = next;
}

static void reverse(struct Node** head_ref)
{
    struct Node * previous = NULL;
    struct Node * current = *head_ref;
    struct Node * next = NULL;

    while (current != NULL)
    {
        //initialize nodes to store and change list
        next = current -> next;
        current -> next = previous;
        previous = current;
        current = next;
    } 

    *head_ref = previous; 
}

// Function to insert a given node in a sorted linked list 
void sortedInsert(struct Node**, struct Node*); 
  
// function to sort a singly linked list using insertion sort 
void insertionSort(struct Node **head_ref) 
{ 
    // Initialize sorted linked list 
    struct Node *sorted = NULL; 
  
    // Traverse the given linked list and insert every 
    // node to sorted 
    struct Node *current = *head_ref; 
    while (current != NULL) 
    { 
        // Store next for next iteration 
        struct Node *next = current->next; 
  
        // insert current in sorted linked list 
        sortedInsert(&sorted, current); 
  
        // Update current 
        current = next; 
    } 
  
    // Update head_ref to point to sorted linked list 
    *head_ref = sorted; 
} 
  
/* function to insert a new_node in a list. Note that this 
  function expects a pointer to head_ref as this can modify the 
  head of the input linked list (similar to push())*/
void sortedInsert(struct Node** head_ref, struct Node* new_node) 
{ 
    struct Node* current; 
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data) 
    { 
        new_node->next = *head_ref; 
        *head_ref = new_node; 
    } 
    else
    { 
        /* Locate the node before the point of insertion */
        current = *head_ref; 
        while (current->next!=NULL && 
               current->next->data < new_node->data) 
        { 
            current = current->next; 
        } 
        new_node->next = current->next; 
        current->next = new_node; 
    } 
} 

int main()
{
    struct Node* head = NULL;
    push(&head, 1);   
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);
    printList(head);
    insertionSort(&head); 
    printList(head);
    deleteNode(&head, 3);
    printList(head);
    reverse(&head);
    printList(head);
    deleteList(&head); 
    return 0;
}
