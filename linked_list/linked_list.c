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
int main()
{
    struct Node* head = NULL;
    push(&head, 1);   
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);
    printList(head);
    deleteNode(&head, 3);
    printList(head);
    deleteList(&head); 
    return 0;
}
