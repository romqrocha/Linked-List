#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_INT 0x7fffffff
#define SUCCESS_INT 0x80000000

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static Node *head = NULL;
static Node *tail = NULL;

void init() {
    // Make head and tail point to valid memory locations
    head = malloc(sizeof(Node));
    tail = head;

    // Create the head node
    printf("Enter the first value of your linked list: ");
    scanf("%d", &(head->value));
    head->next = NULL;
}

/* Returns the length of this linked list. */
int lengthOfLL() {
    Node current = *head;
    int len = 1;

    while (current.next != NULL) {
        len++;
        current = *(current.next);
    }
    
    return len;
}

/** Converts an integer to a string. Remember to free the string after. */
char *itoa(int i) {
    char *a = calloc(12, sizeof(char));
    sprintf(a, "%d", i);
    return a;
}

void length() {
    int len = lengthOfLL();
    char *lenAsStr = itoa(len);
    
    char dest[28] = {0};
    strcat(dest, "\nLength: ");
    strcat(dest, lenAsStr); free(lenAsStr);
    strcat(dest, (len == 1) ? " node\n" : " nodes\n");

    printf("%s", dest);
    return;
}

/* Returns the index of the new node in the linked list. */
int insertInLL(int value, int pos) {
    Node *new = malloc(sizeof(Node));
    new->value = value;

    int cpos = 0;
    if (pos <= 0) {
        new->next = head;
        head = new;
    } else {
        cpos = 1;
        Node *current = head;
        
        while (cpos < pos && current->next != NULL) {
            current = current->next;
            cpos++;
        }
        
        new->next = current->next;
        current->next = new;

        if (new->next == NULL) {
            tail = new;
        }
    }

    return cpos;
}

void add() {
    int value;
    int index;

    printf("\nNew value to be added: ");
    scanf("%d", &value);
    printf("Index to insert new value: ");
    scanf("%d", &index);

    int aindex = insertInLL(value, index);
    if (aindex == index) {
        printf("Successfully inserted value in index %d.\n", aindex);
    } else {
        printf("Index %d is out of bounds. Instead, the value was inserted in the last possible index, %d.\n", index, aindex);
    }

}

/* Returns -1 if the key is not found, or the index of the key if it was found. */
int linearSearchInLL(int key) {
    Node *currNode = head;
    int index = 0;
    while (currNode != NULL && currNode->value != key) {
        currNode = currNode->next;
        index++;
    }

    if (currNode == NULL) {
        return -1; 
    } else {
        return index;
    }
}

void find() {
    int key;

    printf("\nWhat value do you want to find? ");
    scanf("%d", &key);

    int index = linearSearchInLL(key);
    if (index == -1) {
        printf("Value %d not found.\n", key);
    } else {
        printf("Value %d found in index %d.\n", key, index);
    }

    return;
}

/** Returns 1 if deletion was successful or 0 if index was out of bounds. */
int deleteByIndexInLL(int index) {
    if (index < 0) {
        return 0;
    }

    Node *current = head;

    if (index == 0) {
        head = current->next;
        free(current);
        return 1;
    } else if (current == tail) {
        // Trying to delete something after tail; out of bounds
        return 0;
    }
    
    for (int i = 0; i + 1 < index; i++) {
        current = current->next;
        if (current == tail) {
            //Trying to delete something after tail; out ouf bounds
            return 0;
        }
    }

    Node *del = current->next;

    if (del == tail) {
        tail = current;
    }
        
    current->next = del->next;
    free(del);
    return 1;
}

void delete() {
    int index;
    printf("\nWhat index do you want to delete? ");
    scanf("%d", &index);

    int successful = deleteByIndexInLL(index);
    if (successful) {
        printf("Node at index %d successfully deleted.\n", index);
    } else {
        printf("Index %d is out of bounds. ", index);
        printf("Maximum index is %d.\n", lengthOfLL() - 1);
    }
    return;
}

/** 
 * Returns (2^31 - 1) if the index is out of bounds. 
 * Otherwise, returns the value that was replaced. 
 */
int replaceInLL(int value, int index) {
    if (index < 0) {
        return ERROR_INT;
    }

    Node *current = head;
    int cindex = 0;

    while (cindex < index) {
        if (current->next == NULL) {
            return ERROR_INT;
        }
        current = current->next;
        cindex++;
    }

    int oldvalue = current->value;
    current->value = value;

    return oldvalue;
}

void replace() {
    int value;
    int index;

    printf("\nNew value to be added: ");
    scanf("%d", &value);
    printf("Index of old node to be replaced: ");
    scanf("%d", &index);

    int oldval = replaceInLL(value, index);

    if (oldval != ERROR_INT) {
        printf("Successfully replaced old value \"%d\" with new value \"%d\".\n", oldval, value);
    } else {
        printf("Operation failed. Index %d is out of bounds.\n", index);
    }

    return;
}

/** 
 * Swaps the index of one node with another node.
 * If an index is out of bounds, this function returns that index.
 * Otherwise, this function returns SUCCESS_INT. 
 */
int swapInLL(int index1, int index2) {
    if (index1 < 0) {
        return index1;
    } else if (index2 < 0) {
        return index2;
    } else if (index1 == index2) {
        return SUCCESS_INT;
    }

    // Ensure that index2 > index1
    if (index1 > index2) {
        int temp = index1;
        index1 = index2;
        index2 = temp;
    }

    Node *curr = head;
    Node *node1 = NULL;
    Node *node2 = NULL;
    for (int i = 0; i < index2; i++) {
        if (i == index1) {
            node1 = curr;
        }

        curr = curr->next;
        if (curr == NULL) {
            return index2;
        }
    }
    node2 = curr;
    
    int temp = node1->value;
    node1->value = node2->value;
    node2->value = temp; 

    return SUCCESS_INT;
}

void swap() {
    int index1;
    printf("\nIndex of the first value: ");
    scanf("%d", &index1);

    int index2;
    printf("Index of the second value: ");
    scanf("%d", &index2);

    int result = swapInLL(index1, index2);
    if (result != SUCCESS_INT) {
        printf("Operation failed. Index %d is out of bounds.\n", result);
    } else {
        printf("Successfully swapped node %d and node %d.\n", index1, index2);
    }

    return;
}

/** Reverse the linked list recursively. */
Node *reverseLL(Node *curr, Node *caller) {
    if (curr == NULL) {
        head = caller;
        return curr;
    }

    reverseLL(curr->next, curr);

    curr->next = caller;

    return curr;
}

void reverse() {
    tail = reverseLL(head, NULL);
    printf("\nLinked List successfully reversed.\n");
    return;
}

Node *getMiddle(Node *head, Node *tail) {
    Node *fast = head;
    Node *slow = head;

    while (fast != tail && fast->next != tail) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // slow == middle
    return slow;
}

void merge(Node *head1, Node *tail1, Node *head2, Node *tail2) {
    Node *copyHead1 = malloc(sizeof(Node));
    
    Node *current = head1;    
    Node *copyCurrent1 = copyHead1;

    while (current != tail1) {
        copyCurrent1->next = malloc(sizeof(Node));
        copyCurrent1->value = current->value;
        copyCurrent1 = copyCurrent1->next;

        current = current->next;
    }
    
    copyCurrent1->value = current->value;
    copyCurrent1->next = NULL;

    /***/

    Node *copyHead2 = malloc(sizeof(Node));
    
    current = head2;
    Node *copyCurrent2 = copyHead2;

    while (current != tail2) {
        copyCurrent2->next = malloc(sizeof(Node));
        copyCurrent2->value = current->value;
        copyCurrent2 = copyCurrent2->next;

        current = current->next;
    }

    copyCurrent2->value = current->value;
    copyCurrent2->next = NULL;

    /***/

    current = head1;
    copyCurrent1 = copyHead1;
    copyCurrent2 = copyHead2;
    while (copyCurrent1 != NULL && copyCurrent2 != NULL && current != NULL) {
        if (copyCurrent1->value <= copyCurrent2->value) {
            current->value = copyCurrent1->value;
            copyCurrent1 = copyCurrent1->next;
        } else {
            current->value = copyCurrent2->value;
            copyCurrent2 = copyCurrent2->next;
        }
        current = current->next;
    }

    /***/

    while (copyCurrent1 != NULL) {
        current->value = copyCurrent1->value;
        current = current->next;

        copyCurrent1 = copyCurrent1->next;
    }

    while (copyCurrent2 != NULL) {
        current->value = copyCurrent2->value;
        current = current->next;

        copyCurrent2 = copyCurrent2->next;
    }

    /***/

    Node *prev;

    if (copyHead1->next != NULL) {
        prev = copyHead1->next;
        current = prev->next;

        while (current != NULL) {
            free(prev);
            prev = current;

            current = current->next;
        }

        free(prev);
    }
    
    free(copyHead1);

    if (copyHead2->next != NULL) {
        prev = copyHead2->next;
        current = prev->next;

        while (current != NULL) {
            free(prev);
            prev = current;

            current = current->next;
        }

        free(prev);
    }
    
    free(copyHead2);
    
    return;
}

void mergeSortLL(Node *head, Node *tail) {
    if (head != tail) {
        Node *middle = getMiddle(head, tail);

        mergeSortLL(head, middle);
        mergeSortLL(middle->next, tail);

        merge(head, middle, middle->next, tail);
    }
}

void sort() {
    int choice;

    askchoice:
        printf("\nWhat kind of sort would you like to use?\n");
        printf("1: Merge sort\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                mergeSortLL(head, tail); 
                break;
            } default: {
                printf("Invalid choice, please try again.\n");
                goto askchoice;
            }
        }
}

void print() {
    Node current = *head;

    printf("\n%d", current.value);
    while (current.next != NULL) {
        current = *(current.next);
        printf(" --> %d", current.value);
    }
    printf("\n");

    return;
}

void prompt(char *msg) {
    fputs(msg, stdout);
    printf("0: Quit\n");
    printf("1: Add\n");
    printf("2: Find\n");
    printf("3: Delete\n");
    printf("4: Replace\n");
    printf("5: Swap\n");
    printf("6: Get Length\n");
    printf("7: Reverse\n");
    printf("8: Sort\n");
    printf("9: Print\n");
    printf("Your choice: ");
    return;
}

void pick(int choice) {
    switch (choice) {
        case 0: break;
        case 1: add(); break;
        case 2: find(); break;
        case 3: delete(); break;
        case 4: replace(); break;
        case 5: swap(); break;
        case 6: length(); break;
        case 7: reverse(); break;
        case 8: sort(); break;
        case 9: print(); break;
        default: printf("\nInvalid input \"%d\", please try again.\n", choice);
    }

    return;
}

int main(int argc, char **argv) {
    if (argc != 1) {
        printf("Error: You entered %d command line arguments, but this program takes no extra arguments.\n", argc);
        return -1;
    }

    init();

    char myprompt[65] = "\nChoose one of the options below to manipulate the linked list.\n";
    int choice;
    do {
        prompt(myprompt);
        scanf("%d", &choice);
        pick(choice);
    } while (choice != 0);

    printf("\nQuitting...\n\n");
    return 0;
}   