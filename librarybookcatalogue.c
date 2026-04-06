#include <stdio.h>
#include <string.h>

#define MAX 5

struct Book {
    int id;
    char title[50];
    char author[50];
};

struct Book library[MAX];
int count = 0;

// Clear input buffer
void clearBuffer() {
    while (getchar() != '\n');
}

// Add Book
void addBook() {
    if (count == MAX) {
        printf("Library is full!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &library[count].id);
    clearBuffer();

    printf("Enter Title: ");
    fgets(library[count].title, 50, stdin);
    library[count].title[strcspn(library[count].title, "\n")] = 0;

    printf("Enter Author: ");
    fgets(library[count].author, 50, stdin);
    library[count].author[strcspn(library[count].author, "\n")] = 0;

    count++;
    printf("Book added successfully!\n");
}

// Display Books
void displayBooks() {
    if (count == 0) {
        printf("No books available.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\nTitle: %s\nAuthor: %s\n",
               library[i].id,
               library[i].title,
               library[i].author);
    }
}

// Search Book
void searchBook() {
    char title[50];
    clearBuffer();

    printf("Enter title to search: ");
    fgets(title, 50, stdin);
    title[strcspn(title, "\n")] = 0;

    int found = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(library[i].title, title) == 0) {
            printf("\nBook Found!\n");
            printf("ID: %d\nAuthor: %s\n",
                   library[i].id,
                   library[i].author);
            found = 1;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

// Remove Book
void removeBook() {
    char title[50];
    clearBuffer();

    printf("Enter title to remove: ");
    fgets(title, 50, stdin);
    title[strcspn(title, "\n")] = 0;

    int found = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(library[i].title, title) == 0) {
            for (int j = i; j < count - 1; j++) {
                library[j] = library[j + 1];
            }
            count--;
            printf("Book removed successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

// Main
int main() {
    int choice;

    while (1) {
        printf("\n===== Library Menu =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Remove Book\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            return 0;
        }

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: removeBook(); break;
            case 5: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
