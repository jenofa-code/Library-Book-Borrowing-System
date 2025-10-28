#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    char studentID[20];
    char bookID[20];
    char bookTitle[50];
    char dateOfIssue[20];
    struct Book *next;
};

// Function prototypes
struct Book* issueBook(struct Book *head);
struct Book* returnBook(struct Book *head);
void searchBorrowedBook(struct Book *head);
void displayBorrowingHistory(struct Book *head);
struct Book* cloneHistory(struct Book *head);
void countTotalBooks(struct Book *head);

// Helper functions
void clearInputBuffer() {
    while (getchar() != '\n');
}

struct Book* issueBook(struct Book *head) {
    struct Book *newBook = (struct Book*)malloc(sizeof(struct Book));
    if (!newBook) {
        printf("Memory allocation failed!\n");
        return head;
    }

    printf("Enter Student ID: ");
    scanf("%s", newBook->studentID);
    printf("Enter Book ID: ");
    scanf("%s", newBook->bookID);
    clearInputBuffer();
    printf("Enter Book Title: ");
    fgets(newBook->bookTitle, sizeof(newBook->bookTitle), stdin);
    newBook->bookTitle[strcspn(newBook->bookTitle, "\n")] = '\0';
    printf("Enter Date of Issue (DD-MM-YYYY): ");
    scanf("%s", newBook->dateOfIssue);

    newBook->next = NULL;

    if (head == NULL) {
        head = newBook;
    } else {
        struct Book *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newBook;
    }

    printf("\n✅ Book issued successfully!\n");
    return head;
}

struct Book* returnBook(struct Book *head) {
    if (head == NULL) {
        printf("\nNo records found!\n");
        return head;
    }

    char studentID[20], bookID[20];
    printf("Enter Student ID: ");
    scanf("%s", studentID);
    printf("Enter Book ID to return: ");
    scanf("%s", bookID);

    struct Book *temp = head, *prev = NULL;

    while (temp != NULL && 
           (strcmp(temp->studentID, studentID) != 0 || strcmp(temp->bookID, bookID) != 0)) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\n❌ Record not found!\n");
        return head;
    }

    if (prev == NULL)
        head = head->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("\n✅ Book returned successfully!\n");
    return head;
}

void searchBorrowedBook(struct Book *head) {
    if (head == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    char studentID[20];
    printf("Enter Student ID to search: ");
    scanf("%s", studentID);

    struct Book *temp = head;
    int found = 0;

    while (temp != NULL) {
        if (strcmp(temp->studentID, studentID) == 0) {
            printf("\nBook ID: %s | Title: %s | Date of Issue: %s\n",
                   temp->bookID, temp->bookTitle, temp->dateOfIssue);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
        printf("\n❌ No books found for Student ID %s\n", studentID);
}

void displayBorrowingHistory(struct Book *head) {
    if (head == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    struct Book *temp = head;
    printf("\n📚 Borrowing History:\n");
    printf("---------------------------------------------\n");
    while (temp != NULL) {
        printf("Student ID: %s | Book ID: %s | Title: %s | Date: %s\n",
               temp->studentID, temp->bookID, temp->bookTitle, temp->dateOfIssue);
        temp = temp->next;
    }
}

struct Book* cloneHistory(struct Book *head) {
    if (head == NULL) return NULL;

    struct Book *newHead = NULL, *tail = NULL;
    struct Book *temp = head;

    while (temp != NULL) {
        struct Book *newNode = (struct Book*)malloc(sizeof(struct Book));
        strcpy(newNode->studentID, temp->studentID);
        strcpy(newNode->bookID, temp->bookID);
        strcpy(newNode->bookTitle, temp->bookTitle);
        strcpy(newNode->dateOfIssue, temp->dateOfIssue);
        newNode->next = NULL;

        if (newHead == NULL)
            newHead = newNode;
        else
            tail->next = newNode;

        tail = newNode;
        temp = temp->next;
    }

    printf("\n✅ Borrowing history cloned successfully!\n");
    return newHead;
}

void countTotalBooks(struct Book *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    printf("\nTotal books borrowed: %d\n", count);
}

int main() {
    struct Book *deptHeads[3] = {NULL, NULL, NULL};  // For 3 departments
    int deptChoice, choice;
    struct Book *cloneList = NULL;

    while (1) {
        printf("\n========== Library Book Borrowing System ==========\n");
        printf("Select Department:\n");
        printf("1. Computer Science\n2. Mechanical\n3. Electronics\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &deptChoice);

        if (deptChoice == 4) break;
        if (deptChoice < 1 || deptChoice > 3) {
            printf("\nInvalid department!\n");
            continue;
        }

        while (1) {
            printf("\n------ Department Menu ------\n");
            printf("1. Issue New Book\n2. Return Book\n3. Search Borrowed Book\n");
            printf("4. Display Borrowing History\n5. Clone Borrowing History\n");
            printf("6. Count Total Books Borrowed\n7. Back to Department Menu\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: deptHeads[deptChoice - 1] = issueBook(deptHeads[deptChoice - 1]); break;
                case 2: deptHeads[deptChoice - 1] = returnBook(deptHeads[deptChoice - 1]); break;
                case 3: searchBorrowedBook(deptHeads[deptChoice - 1]); break;
                case 4: displayBorrowingHistory(deptHeads[deptChoice - 1]); break;
                case 5: cloneList = cloneHistory(deptHeads[deptChoice - 1]); break;
                case 6: countTotalBooks(deptHeads[deptChoice - 1]); break;
                case 7: goto backToMain;
                default: printf("\nInvalid choice!\n");
            }
        }
        backToMain: continue;
    }

    printf("\n📖 Exiting Library System... Thank you!\n");
    return 0;
}