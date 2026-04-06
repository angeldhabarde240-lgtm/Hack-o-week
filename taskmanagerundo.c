#include <stdio.h>
#include <string.h>

#define MAX 100
#define ACTION_SIZE 100

typedef struct {
    char actions[MAX][ACTION_SIZE];
    int top;
} Stack;

// Initialize stack
void init(Stack *s) {
    s->top = -1;
}

// Check empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Push action
void push(Stack *s, char action[]) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    strcpy(s->actions[++s->top], action);
}

// Pop action
int pop(Stack *s, char result[]) {
    if (isEmpty(s)) return 0;
    strcpy(result, s->actions[s->top--]);
    return 1;
}

// Peek top action
char* peek(Stack *s) {
    if (isEmpty(s)) return NULL;
    return s->actions[s->top];
}

// Display stack contents
void display(Stack *s, const char *name) {
    if (isEmpty(s)) {
        printf("%s stack is empty.\n", name);
        return;
    }
    printf("%s stack:\n", name);
    for (int i = s->top; i >= 0; i--) {
        printf("- %s\n", s->actions[i]);
    }
}

int main() {
    Stack undoStack, redoStack;
    init(&undoStack);
    init(&redoStack);

    char action[ACTION_SIZE];
    int choice;

    while (1) {
        printf("\n--- Task Manager ---\n");
        printf("1. Perform Action\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Show Undo Stack\n");
        printf("5. Show Redo Stack\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;
        getchar(); // consume newline

        switch (choice) {
            case 1: // Perform action
                printf("Enter action description: ");
                fgets(action, ACTION_SIZE, stdin);
                action[strcspn(action, "\n")] = 0; // remove newline

                push(&undoStack, action);
                redoStack.top = -1; // clear redo stack
                printf("Action '%s' performed.\n", action);
                break;

            case 2: // Undo
                if (pop(&undoStack, action)) {
                    push(&redoStack, action);
                    printf("Undid action: %s\n", action);
                } else {
                    printf("Nothing to undo.\n");
                }
                break;

            case 3: // Redo
                if (pop(&redoStack, action)) {
                    push(&undoStack, action);
                    printf("Redid action: %s\n", action);
                } else {
                    printf("Nothing to redo.\n");
                }
                break;

            case 4:
                display(&undoStack, "Undo");
                break;

            case 5:
                display(&redoStack, "Redo");
                break;

            case 6:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
