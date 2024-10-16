#include <stdio.h>
#include <stdlib.h>

// Node structure definition
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the circular linked list
void insertAtEnd(struct Node** tail, int value) {
    struct Node* newNode = createNode(value);

    if (*tail == NULL) {
        // If the list is empty, the new node will be the only node, and its next will point to itself
        *tail = newNode;
        newNode->next = *tail;
    } else {
        // Otherwise, add the new node at the end and update the tail
        newNode->next = (*tail)->next;  // Point new node to the head
        (*tail)->next = newNode;        // Old tail's next now points to the new node
        *tail = newNode;                // Update tail to the new node
    }

    printf("Inserted %d at the end.\n", value);
}

// Function to insert a node at the beginning of the circular linked list
void insertAtBeginning(struct Node** tail, int value) {
    struct Node* newNode = createNode(value);

    if (*tail == NULL) {
        // If the list is empty, the new node will be the only node, and its next will point to itself
        *tail = newNode;
        newNode->next = *tail;
    } else {
        // Insert at the beginning
        newNode->next = (*tail)->next;  // New node's next points to the head
        (*tail)->next = newNode;        // Update the tail to point to the new first node
    }

    printf("Inserted %d at the beginning.\n", value);
}

// Function to delete a node from the circular linked list
void deleteNode(struct Node** tail, int value) {
    if (*tail == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    struct Node* current = (*tail)->next;
    struct Node* previous = *tail;

    // Check if the list contains only one node
    if (current == *tail && current->data == value) {
        free(current);
        *tail = NULL;  // List becomes empty
        printf("Deleted %d (the only node in the list).\n", value);
        return;
    }

    // Traverse to find the node to delete
    do {
        if (current->data == value) {
            if (current == *tail) {
                // If the node to be deleted is the tail, update the tail
                *tail = previous;
            }
            previous->next = current->next;  // Skip the node to be deleted
            free(current);
            printf("Deleted %d from the list.\n", value);
            return;
        }

        previous = current;
        current = current->next;
    } while (current != (*tail)->next);

    printf("Value %d not found in the list.\n", value);
}

// Function to display the circular linked list
void display(struct Node* tail) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* current = tail->next;  // Start from the head
    printf("Circular Linked List: ");

    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != tail->next);

    printf("(back to head)\n");
}

// Main function to demonstrate circular linked list operations
int main() {
    struct Node* tail = NULL;  // Initialize the tail pointer

    insertAtEnd(&tail, 10);
    insertAtEnd(&tail, 20);
    insertAtEnd(&tail, 30);
    display(tail);

    insertAtBeginning(&tail, 5);
    display(tail);

    deleteNode(&tail, 20);
    display(tail);

    deleteNode(&tail, 5);
    display(tail);

    deleteNode(&tail, 10);
    display(tail);

    deleteNode(&tail, 30);
    display(tail);

    return 0;
}

