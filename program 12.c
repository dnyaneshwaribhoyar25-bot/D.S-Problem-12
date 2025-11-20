#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertBegin(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

void insertPosition(struct Node** head, int data, int pos) {
    if (pos == 1) {
        insertBegin(head, data);
        return;
    }
    struct Node* temp = *head;
    for (int i = 1; temp != NULL && i < pos - 1; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Position out of range!\n");
        return;
    }

    struct Node* newNode = createNode(data);
    newNode->next = temp->next;
    temp->next = newNode;
}
void deleteValue(struct Node** head, int value) {
    struct Node *temp = *head, *prev = NULL;
    if (temp && temp->data == value) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        printf("Value not found!\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
}

void deletePosition(struct Node** head, int pos) {
    struct Node *temp = *head, *prev = NULL;
    if (pos == 1 && temp) {
        *head = temp->next;
        free(temp);
        return;
    }
    for (int i = 1; temp != NULL && i < pos; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        printf("Position out of range!\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
}

void display(struct Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

struct Node* reverseList(struct Node* head) {
    struct Node *prev = NULL, *curr = head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void findMiddle(struct Node* head) {
    struct Node *slow = head, *fast = head;
    if (!head) {
        printf("List is empty!\n");
        return;
    }
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    printf("Middle element: %d\n", slow->data);
}

void sortList(struct Node* head) {
    if (!head) return;
    int swapped;
    struct Node *ptr, *lptr = NULL;

    do {
        swapped = 0;
        ptr = head;
        while (ptr->next != lptr) {
            if (ptr->data > ptr->next->data) {
                int temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
}
int detectLoop(struct Node* head) {
    struct Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return 1;
    }
    return 0;
}

struct Node* mergeSorted(struct Node* a, struct Node* b) {
    if (!a) return b;
    if (!b) return a;

    struct Node* result = NULL;
    if (a->data <= b->data) {
        result = a;
        result->next = mergeSorted(a->next, b);
    } else {
        result = b;
        result->next = mergeSorted(a, b->next);
    }
    return result;
}
int sumList(struct Node* head) {
    int sum = 0;
    while (head) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}
void printOddEven(struct Node* head) {
    printf("Odd elements: ");
    struct Node* temp = head;
    while (temp) {
        if (temp->data % 2 != 0) printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\nEven elements: ");
    temp = head;
    while (temp) {
        if (temp->data % 2 == 0) printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int choice, value, pos;

    while (1) {
        printf("\n---- LINKED LIST MENU ----\n");
        printf("1. Insert at begin\n2. Insert at end\n3. Insert at position\n");
        printf("4. Delete by value\n5. Delete by position\n6. Display\n7. Reverse\n");
        printf("8. Find middle\n9. Sort\n10. Sum of data\n11. Print odd-even\n");
        printf("12. Detect loop\n13. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            insertBegin(&head, value);
            break;
        case 2:
            printf("Enter value: ");
            scanf("%d", &value);
            insertEnd(&head, value);
            break;
        case 3:
            printf("Enter value and position: ");
            scanf("%d %d", &value, &pos);
            insertPosition(&head, value, pos);
            break;
        case 4:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            deleteValue(&head, value);
            break;
        case 5:
            printf("Enter position: ");
            scanf("%d", &pos);
            deletePosition(&head, pos);
            break;
        case 6:
            display(head);
            break;
        case 7:
            head = reverseList(head);
            printf("List reversed.\n");
            break;
        case 8:
            findMiddle(head);
            break;
        case 9:
            sortList(head);
            printf("List sorted.\n");
            break;
        case 10:
            printf("Sum of elements: %d\n", sumList(head));
            break;
        case 11:
            printOddEven(head);
            break;
        case 12:
            if (detectLoop(head))
                printf("Loop detected!\n");
            else
                printf("No loop.\n");
            break;
        case 13:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}

