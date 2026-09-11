#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;
    int issuedToMemberId;

    Book(int bId = 0, string t = "", string a = "", bool issued = false, int mId = -1)
        : id(bId), title(t), author(a), isIssued(issued), issuedToMemberId(mId) {}

    void displayBook() const {
        cout << left << setw(10) << id
             << setw(30) << title
             << setw(25) << author
             << setw(15) << (isIssued ? "Issued" : "Available")
             << setw(15) << (isIssued ? to_string(issuedToMemberId) : "-") << endl;
    }
};

class Member {
public:
    int id;
    string name;

    Member(int mId = 0, string n = "") : id(mId), name(n) {}

    void displayMember() const {
        cout << left << setw(10) << id << setw(30) << name << endl;
    }
};

class LibraryManagementSystem {
private:
    vector<Book> books;
    vector<Member> members;
    const string bookFileName = "books.txt";
    const string memberFileName = "members.txt";

    void loadData() {
        ifstream bookFile(bookFileName);
        if (bookFile.is_open()) {
            Book b;
            while (bookFile >> b.id) {
                bookFile.ignore();
                getline(bookFile, b.title);
                getline(bookFile, b.author);
                bookFile >> b.isIssued >> b.issuedToMemberId;
                books.push_back(b);
            }
            bookFile.close();
        }

        ifstream memberFile(memberFileName);
        if (memberFile.is_open()) {
            Member m;
            while (memberFile >> m.id) {
                memberFile.ignore();
                getline(memberFile, m.name);
                members.push_back(m);
            }
            memberFile.close();
        }
    }

    void saveData() const {
        ofstream bookFile(bookFileName);
        for (const auto &b : books) {
            bookFile << b.id << "\n" << b.title << "\n" << b.author << "\n"
                     << b.isIssued << " " << b.issuedToMemberId << "\n";
        }
        bookFile.close();

        ofstream memberFile(memberFileName);
        for (const auto &m : members) {
            memberFile << m.id << "\n" << m.name << "\n";
        }
        memberFile.close();
    }

    Book* findBookById(int id) {
        for (auto &b : books) {
            if (b.id == id) return &b;
        }
        return nullptr;
    }

    Member* findMemberById(int id) {
        for (auto &m : members) {
            if (m.id == id) return &m;
        }
        return nullptr;
    }

public:
    LibraryManagementSystem() {
        loadData();
    }

    ~LibraryManagementSystem() {
        saveData();
    }

    void addBook() {
        int id;
        string title, author;
        cout << "\nEnter Book ID: ";
        cin >> id;
        if (findBookById(id)) {
            cout << "Book with ID " << id << " already exists!\n";
            return;
        }
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Book Author: ";
        getline(cin, author);

        books.emplace_back(id, title, author);
        saveData();
        cout << "Book added successfully!\n";
    }

    void addMember() {
        int id;
        string name;
        cout << "\nEnter Member ID: ";
        cin >> id;
        if (findMemberById(id)) {
            cout << "Member with ID " << id << " already exists!\n";
            return;
        }
        cin.ignore();
        cout << "Enter Member Name: ";
        getline(cin, name);

        members.emplace_back(id, name);
        saveData();
        cout << "Member added successfully!\n";
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "\nNo books available in the library.\n";
            return;
        }
        cout << "\n" << left << setw(10) << "Book ID" << setw(30) << "Title" << setw(25) << "Author" << setw(15) << "Status" << setw(15) << "Member ID" << endl;
        cout << string(90, '-') << endl;
        for (const auto &b : books) {
            b.displayBook();
        }
    }

    void displayAllMembers() const {
        if (members.empty()) {
            cout << "\nNo members registered.\n";
            return;
        }
        cout << "\n" << left << setw(10) << "Member ID" << setw(30) << "Name" << endl;
        cout << string(40, '-') << endl;
        for (const auto &m : members) {
            m.displayMember();
        }
    }

    void searchBook() const {
        if (books.empty()) {
            cout << "\nNo books available to search.\n";
            return;
        }
        int choice;
        cout << "\nSearch by:\n1. Title\n2. Author\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        string query;
        if (choice == 1) {
            cout << "Enter Title keyword: ";
            getline(cin, query);
        } else if (choice == 2) {
            cout << "Enter Author keyword: ";
            getline(cin, query);
        } else {
            cout << "Invalid search choice!\n";
            return;
        }

        bool found = false;
        cout << "\n" << left << setw(10) << "Book ID" << setw(30) << "Title" << setw(25) << "Author" << setw(15) << "Status" << setw(15) << "Member ID" << endl;
        cout << string(90, '-') << endl;

        for (const auto &b : books) {
            string target = (choice == 1) ? b.title : b.author;
            string targetLower = target, queryLower = query;
            transform(targetLower.begin(), targetLower.end(), targetLower.begin(), ::tolower);
            transform(queryLower.begin(), queryLower.end(), queryLower.begin(), ::tolower);

            if (targetLower.find(queryLower) != string::npos) {
                b.displayBook();
                found = true;
            }
        }

        if (!found) {
            cout << "No matching books found.\n";
        }
    }

    void issueBook() {
        int bId, mId;
        cout << "\nEnter Book ID to issue: ";
        cin >> bId;
        Book *b = findBookById(bId);

        if (!b) {
            cout << "Book not found!\n";
            return;
        }
        if (b->isIssued) {
            cout << "Book is already issued to Member ID: " << b->issuedToMemberId << endl;
            return;
        }

        cout << "Enter Member ID issuing the book: ";
        cin >> mId;
        Member *m = findMemberById(mId);

        if (!m) {
            cout << "Member not found! Register the member first.\n";
            return;
        }

        b->isIssued = true;
        b->issuedToMemberId = mId;
        saveData();
        cout << "Book '" << b->title << "' issued successfully to " << m->name << " (ID: " << mId << ")!\n";
    }

    void returnBook() {
        int bId;
        cout << "\nEnter Book ID to return: ";
        cin >> bId;
        Book *b = findBookById(bId);

        if (!b) {
            cout << "Book not found!\n";
            return;
        }
        if (!b->isIssued) {
            cout << "This book is not currently issued.\n";
            return;
        }

        b->isIssued = false;
        b->issuedToMemberId = -1;
        saveData();
        cout << "Book '" << b->title << "' returned successfully!\n";
    }
};

int main() {
    LibraryManagementSystem sys;
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "       LIBRARY MANAGEMENT SYSTEM        \n";
        cout << "========================================\n";
        cout << "1. Add New Book\n";
        cout << "2. Register New Member\n";
        cout << "3. Display All Books\n";
        cout << "4. Display All Members\n";
        cout << "5. Search Book (by Title or Author)\n";
        cout << "6. Issue Book\n";
        cout << "7. Return Book\n";
        cout << "8. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sys.addBook(); break;
            case 2: sys.addMember(); break;
            case 3: sys.displayAllBooks(); break;
            case 4: sys.displayAllMembers(); break;
            case 5: sys.searchBook(); break;
            case 6: sys.issueBook(); break;
            case 7: sys.returnBook(); break;
            case 8: cout << "\nExiting and saving session data...\n"; break;
            default: cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 8);

    return 0;
}