#include <stdio.h>
#include <stdlib.h>

struct Node {
    int id;
    float price;
    int qty;
    struct Node* next;
};

struct Node* head = NULL;

// Add item
void add(int id, float price, int qty) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->id = id;
    newNode->price = price;
    newNode->qty = qty;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Remove item
void removeItem(int id) {
    struct Node *temp = head, *prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Not Found\n");
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("Removed\n");
}

// Display
void display() {
    struct Node* temp = head;
    float total = 0;

    if (temp == NULL) {
        printf("Cart Empty\n");
        return;
    }

    while (temp != NULL) {
        float t = temp->price * temp->qty;
        printf("ID:%d Price:%.2f Qty:%d Total:%.2f\n",
               temp->id, temp->price, temp->qty, t);
        total += t;
        temp = temp->next;
    }

    printf("Total=%.2f\n", total);
}

int main() {
    int n, choice, id, qty;
    float price;

    // number of operations
    scanf("%d", &n);

    while (n--) {
        scanf("%d", &choice);

        if (choice == 1) {
            scanf("%d %f %d", &id, &price, &qty);
            add(id, price, qty);
        }
        else if (choice == 2) {
            scanf("%d", &id);
            removeItem(id);
        }
        else if (choice == 3) {
            display();
        }
    }

    return 0;
}
