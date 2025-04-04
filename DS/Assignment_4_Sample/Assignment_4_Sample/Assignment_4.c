#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef OJ_JUDGE
#define main student_main
#endif

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;

// Add the element x to the "end" of the list
void push_Back(int x) {
    // TO DO
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Add an element to the "head" of the list
void push_Front(int x) {
    // TO DO
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = head;
    head = newNode;
}

// Delete "the specified element" from the list.
void remove_Node(int x) {
    // TO DO
    if (head == NULL) return;

    Node* temp = head;
    Node* prev = NULL;

    while (temp != NULL) {
        if (temp->data == x) {
            if (prev == NULL) {
                head = head->next;
            }
            else {
                prev->next = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

// Check if x is in the list, Yes return True; No return False
bool contain(int x) {
    // TO DO
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == x) return true;
        temp = temp->next;
    }
    return false;
}

// Reverse the list
void invert_List() {
    // TO DO
    Node* prev = NULL;
    Node* curr = head;
    Node* next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

// Clear the entire list
void clean() {
    // TO DO
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Output the result
void print_List() {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" ");
        temp = temp->next;
    }
    printf("\n");
}

// You can modify the main() below, it won't be executed.
int main() {
    // You can test your code here.
    int n, x;
    char op[3];
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", op);
        if (op[0] == 'b') {
            scanf("%d", &x);
            push_Back(x);
        }
        else if (op[0] == 'f') {
            scanf("%d", &x);
            push_Front(x);
        }
        else if (op[0] == 'r') {
            scanf("%d", &x);
            remove_Node(x);
        }
        else if (op[0] == 'c') {
            scanf("%d", &x);
            printf("%s\n", contain(x) ? "True" : "False");
        }
        else if (op[0] == 'i') {
            invert_List();
        }
        else if (op[0] == 'C') {
            clean();
            printf("Clear the list!\n");
        }
    }

    print_List();
    return 0;
}

// -----------------------------------------------------
// DON'T TOUCH !!!!!
#ifdef OJ_JUDGE
#undef main
int main() {
    int n, x;
    char op[3];
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", op);
        if (op[0] == 'b') {
            scanf("%d", &x);
            push_Back(x);
        }
        else if (op[0] == 'f') {
            scanf("%d", &x);
            push_Front(x);
        }
        else if (op[0] == 'r') {
            scanf("%d", &x);
            remove_Node(x);
        }
        else if (op[0] == 'c') {
            scanf("%d", &x);
            printf("%s\n", contain(x) ? "True" : "False");
        }
        else if (op[0] == 'i') {
            invert_List();
        }
        else if (op[0] == 'C') {
            clean();
            printf("Clear the list!\n");
        }
    }

    print_List();
    return 0;
}
#endif
