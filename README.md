
# 📚 Library Book Borrowing System – C Program

---

## 🎯 **Objective**
To develop a **dynamic Library Book Borrowing System** using **linked lists** in C language.  
This system efficiently tracks borrowed books by students, supporting dynamic data management without fixed-size limitations.

---

## 🧾 **Data Fields**
Each borrowing record contains the following details:

| Field | Description |
|--------|--------------|
| **Student ID** | Unique identifier for the student |
| **Book ID** | Unique identifier for each book |
| **Book Title** | Title of the borrowed book |
| **Date of Issue** | Date when the book was issued *(DD-MM-YYYY)* |

---

## ⚙️ **Features Implemented**

| No. | Feature | Description |
|-----|----------|-------------|
| 1️⃣ | ➕ **Issue New Book** | Insert a new book borrowing record |
| 2️⃣ | ❌ **Return Book** | Delete a record when a book is returned |
| 3️⃣ | 🔍 **Search Borrowed Book** | Search borrowed book by student ID |
| 4️⃣ | 📖 **Display Borrowing History** | Show all books borrowed by a specific student |
| 5️⃣ | 🔁 **Reverse Display** | Display records in reverse order (latest first) |
| 6️⃣ | 📋 **Clone Borrowing List** | Clone entire borrowing history for audits |
| 7️⃣ | 🔢 **Count Borrowed Books** | Count total number of books currently borrowed |
| 💡 | 🗂️ **Bonus Feature** | Maintain separate lists per department or genre |

---

## 🧩 **Data Structure Used**
### **Singly Linked List**
A **linked list** is used to store borrowing records dynamically.

**Why Linked List?**
- Allows **dynamic insertion and deletion** of records.  
- No fixed memory allocation (unlike arrays).  
- Enables **easy traversal** and **record search**.  
- Efficient for real-time library transactions.  

**Each node stores:**
- Student ID  
- Book ID  
- Book Title  
- Date of Issue  
- Pointer to the next record  

---

## 🧠 **Core Functions Overview**

| Function | Description |
|-----------|--------------|
| `issueBook()` | Adds a new borrowing record |
| `returnBook()` | Deletes a record for returned books |
| `searchByStudent()` | Finds all books borrowed by a student |
| `displayHistory()` | Shows borrowing history for a student |
| `reverseDisplay()` | Displays records in reverse order |
| `cloneList()` | Creates a deep copy of all records (for audits) |
| `countTotalBooks()` | Counts total borrowed books |

---
