#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_SIZE 50

typedef struct {
    char name[NAME_SIZE];
    char phone[20];
} Contact;

// Swap contacts
void swap(Contact *a, Contact *b) {
    Contact temp = *a;
    *a = *b;
    *b = temp;
}

// Sort contacts alphabetically
void sortContacts(Contact contacts[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(contacts[j].name, contacts[j + 1].name) > 0) {
                swap(&contacts[j], &contacts[j + 1]);
            }
        }
    }
}

// Binary search by name
int binarySearch(Contact contacts[], int n, char key[]) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(contacts[mid].name, key);
        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {
    Contact contacts[MAX_CONTACTS];
    int n = 0;
    int choice;

    while (1) {
        printf("\n--- Contact Book Menu ---\n");
        printf("1. Add Contact\n");
        printf("2. Show Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;
        getchar(); // consume newline left by scanf

        if (choice == 1) {
            if (n >= MAX_CONTACTS) {
                printf("Contact book full!\n");
                continue;
            }

            printf("Enter name: ");
            fgets(contacts[n].name, NAME_SIZE, stdin);
            contacts[n].name[strcspn(contacts[n].name, "\n")] = 0; // remove newline

            printf("Enter phone: ");
            fgets(contacts[n].phone, 20, stdin);
            contacts[n].phone[strcspn(contacts[n].phone, "\n")] = 0;

            n++;
            sortContacts(contacts, n);

        } else if (choice == 2) {
            if (n == 0) {
                printf("No contacts.\n");
                continue;
            }
            printf("\nContacts:\n");
            for (int i = 0; i < n; i++)
                printf("%s - %s\n", contacts[i].name, contacts[i].phone);

        } else if (choice == 3) {
            if (n == 0) {
                printf("No contacts to search.\n");
                continue;
            }
            char name[NAME_SIZE];
            printf("Enter name to search: ");
            fgets(name, NAME_SIZE, stdin);
            name[strcspn(name, "\n")] = 0;

            int idx = binarySearch(contacts, n, name);
            if (idx != -1)
                printf("Found: %s - %s\n", contacts[idx].name, contacts[idx].phone);
            else
                printf("Contact not found.\n");

        } else if (choice == 4) {
            printf("Exiting...\n");
            break;

        } else {
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
