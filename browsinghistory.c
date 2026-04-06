#include <stdio.h>
#include <string.h>

#define MAX 100
#define URL_SIZE 100

typedef struct {
    char urls[MAX][URL_SIZE];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char url[]) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    strcpy(s->urls[++s->top], url);
}

// FIX: pop now copies into destination instead of returning pointer
int pop(Stack *s, char result[]) {
    if (isEmpty(s)) {
        return 0; // failure
    }
    strcpy(result, s->urls[s->top--]);
    return 1; // success
}

int main() {
    Stack backStack, forwardStack;
    init(&backStack);
    init(&forwardStack);

    char current[URL_SIZE] = "home";
    char temp[URL_SIZE];
    int choice;
    char url[URL_SIZE];

    while (1) {
        printf("\n-----------------------------\n");
        printf("Current Page: %s\n", current);
        printf("-----------------------------\n");
        printf("1. Visit New Page\n2. Back\n3. Forward\n4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) break;

        switch (choice) {

            case 1:
                printf("Enter URL: ");
                scanf("%99s", url);  // FIX: prevent overflow

                push(&backStack, current);
                strcpy(current, url);

                forwardStack.top = -1; // clear forward
                break;

            case 2:
                if (pop(&backStack, temp)) {
                    push(&forwardStack, current);
                    strcpy(current, temp);
                } else {
                    printf("No back history!\n");
                }
                break;

            case 3:
                if (pop(&forwardStack, temp)) {
                    push(&backStack, current);
                    strcpy(current, temp);
                } else {
                    printf("No forward history!\n");
                }
                break;

            case 4:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
