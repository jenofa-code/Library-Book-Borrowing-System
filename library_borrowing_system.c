#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BookRecord {
    int studentID;
    int bookID;
    char bookTitle[100];
    char dateOfIssue[20];
    struct BookRecord *next;
} BookRecord;

BookRecord *head = NULL;

// Function to create a new node
BookRecord* createRecord(int studentID, int bookID, char bookTitle[], char dateOfIssue[]) {
    BookRecord *newNode = (BookRecord*)malloc(sizeof(BookRecord));
    newNode->studentID = studentID;
    newNode->bookID = bookID;
    strcpy(newNode->bookTitle, bookTitle);
    strcpy(newNode->dateOfIssue, dateOfIssue);
    newNode->next = NULL;
    return newNode;
}

// Function to issue a new book (insert node)
void issueBook(int studentID, int bookID, char bookTitle[], char dateOfIssue[]) {
    BookRecord *newNode = createRecord(studentID, bookID, bookTitle, dateOfIssue);
    if (head == NULL)
        head = newNode;
    else {
        BookRecord *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    printf("\n✅ Book issued successfully!\n");
}

// Function to return a book (delete node)
void returnBook(int studentID, int bookID) {
    BookRecord *temp = head, *prev = NULL;
    while (temp != NULL && !(temp->studentID == studentID && temp->bookID == bookID)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("\n❌ Record not found!\n");
        return;
    }
    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    printf("\n📗 Book returned successfully!\n");
}

// Function to search for a borrowed book by student ID
void searchByStudent(int studentID) {
    BookRecord *temp = head;
    int found = 0;
    printf("\n🔍 Borrowed books for Student ID: %d\n", studentID);
    while (temp != NULL) {
        if (temp->studentID == studentID) {
            printf("Book ID: %d | Title: %s | Date of Issue: %s\n",
                   temp->bookID, temp->bookTitle, temp->dateOfIssue);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("No records found for this student.\n");
}

// Function to display borrowing history per student
void displayHistory(int studentID) {
    printf("\n📚 Borrowing History for Student ID: %d\n", studentID);
    searchByStudent(studentID);
}

// Function to count total borrowed books
int countTotalBooks() {
    int count = 0;
    BookRecord *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Function to clone the list for audits
BookRecord* cloneList(BookRecord *head) {
    if (head == NULL)
        return NULL;
    BookRecord *newNode = createRecord(head->studentID, head->bookID, head->bookTitle, head->dateOfIssue);
    newNode->next = cloneList(head->next);
    return newNode;
}

// Function to display all records
void displayAll() {
    BookRecord *temp = head;
    if (temp == NULL) {
        printf("\n⚠️ No borrowing records found.\n");
        return;
    }
    printf("\n📘 All Borrowed Books:\n");
    while (temp != NULL) {
        printf("Student ID: %d | Book ID: %d | Title: %s | Date: %s\n",
               temp->studentID, temp->bookID, temp->bookTitle, temp->dateOfIssue);
        temp = temp->next;
    }
}

// Function to display list in reverse
void reverseDisplay(BookRecord *node) {
    if (node == NULL)
        return;
    reverseDisplay(node->next);
    printf("Student ID: %d | Book ID: %d | Title: %s | Date: %s\n",
           node->studentID, node->bookID, node->bookTitle, node->dateOfIssue);
}

int main() {
    int choice, studentID, bookID;
    char bookTitle[100], dateOfIssue[20];
    BookRecord *auditList = NULL;

    do {
        printf("\n========= Library Book Borrowing System =========\n");
        printf("1. Issue New Book\n");
        printf("2. Return Book\n");
        printf("3. Search Borrowed Book by Student ID\n");
        printf("4. Display Borrowing History per Student\n");
        printf("5. Display All Borrowed Books\n");
        printf("6. Reverse Display\n");
        printf("7. Clone Borrowing History for Audit\n");
        printf("8. Count Total Borrowed Books\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &studentID);
                printf("Enter Book ID: ");
                scanf("%d", &bookID);
                printf("Enter Book Title: ");
                getchar(); // clear input buffer
                fgets(bookTitle, sizeof(bookTitle), stdin);
                bookTitle[strcspn(bookTitle, "\n")] = 0;
                printf("Enter Date of Issue (DD-MM-YYYY): ");
                scanf("%s", dateOfIssue);
                issueBook(studentID, bookID, bookTitle, dateOfIssue);
                break;

            case 2:
                printf("Enter Student ID: ");
                scanf("%d", &studentID);
                printf("Enter Book ID to return: ");
                scanf("%d", &bookID);
                returnBook(studentID, bookID);
                break;

            case 3:
                printf("Enter Student ID: ");
                scanf("%d", &studentID);
                searchByStudent(studentID);
                break;

            case 4:
                printf("Enter Student ID: ");
                scanf("%d", &studentID);
                displayHistory(studentID);
                break;

            case 5:
                displayAll();
                break;

            case 6:
                printf("\n🔁 Reverse Borrowing Record Display:\n");
                reverseDisplay(head);
                break;

            case 7:
                auditList = cloneList(head);
                printf("\n✅ Borrowing history cloned for audit review!\n");
                break;

            case 8:
                printf("\nTotal Books Borrowed: %d\n", countTotalBooks());
                break;

            case 9:
                printf("\n👋 Exiting system. Goodbye!\n");
                break;

            default:
                printf("\n❌ Invalid choice. Try again.\n");
        }
    } while (choice != 9);

    return 0;
}