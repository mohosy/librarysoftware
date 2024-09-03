#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Function to remove underscores from a string
string removeUnderscores(const string &str) {
    string result = str;
    replace(result.begin(), result.end(), '_', ' ');
    return result;
}

// Abstract base class for Book
class Book {
private:
    int code;           // Unique code for the book
    string title;       // Title of the book
    int available;      // Number of available copies
    int rented;         // Number of rented copies
    Book* next;         // Pointer to the next book in the linked list

public:
    // Constructor for Book class
    Book(int c, string t, int a, int r) : code(c), title(t), available(a), rented(r), next(NULL) {}

    // Pure virtual function to display book details
    virtual void display() const = 0;

    // Getter functions
    int getCode() const { return code; }
    string getTitle() const { return title; }
    int getAvailable() const { return available; }
    int getRented() const { return rented; }

    // Setter functions
    void setAvailable(int a) { available = a; }
    void setRented(int r) { rented = r; }
    void setNext(Book* n) { next = n; }
    Book* getNext() const { return next; }

    // Pure virtual functions to get category and extra info
    virtual string getCategory() const = 0;
    virtual string getExtraInfo() const = 0;

    // Virtual destructor
    virtual ~Book() {}
};

// Derived class for ChildrenBook
class ChildrenBook : public Book {
private:
    int age;            // Recommended age for the book

public:
    // Constructor for ChildrenBook class
    ChildrenBook(int c, string t, int a, int r, int ag) : Book(c, t, a, r), age(ag) {}

    // Function to display book details
    void display() const {
        cout << setw(5) << getCode() << " " << setw(30) << removeUnderscores(getTitle()) << " " << setw(10) << age << " " << setw(10) << getAvailable() << " " << setw(10) << getRented() << endl;
    }

    // Function to get book category
    string getCategory() const { return "Children Book"; }

    // Function to get extra information about the book
    string getExtraInfo() const {
        stringstream ss;
        ss << "age : " << age;
        return ss.str();
    }
};

// Derived class for ComputerBook
class ComputerBook : public Book {
private:
    string publisher;   // Publisher of the book

public:
    // Constructor for ComputerBook class
    ComputerBook(int c, string t, int a, int r, string p) : Book(c, t, a, r), publisher(p) {}

    // Function to display book details
    void display() const {
        cout << setw(5) << getCode() << " " << setw(30) << removeUnderscores(getTitle()) << " " << setw(20) << publisher << " " << setw(10) << getAvailable() << " " << setw(10) << getRented() << endl;
    }

    // Function to get book category
    string getCategory() const { return "Computer Book"; }

    // Function to get extra information about the book
    string getExtraInfo() const {
        return "publisher : " + publisher;
    }
};

// Derived class for Novel
class Novel : public Book {
private:
    int publishDate;    // Publish date of the novel

public:
    // Constructor for Novel class
    Novel(int c, string t, int a, int r, int pd) : Book(c, t, a, r), publishDate(pd) {}

    // Function to display book details
    void display() const {
        cout << setw(5) << getCode() << " " << setw(30) << removeUnderscores(getTitle()) << " " << setw(10) << publishDate << " " << setw(10) << getAvailable() << " " << setw(10) << getRented() << endl;
    }

    // Function to get book category
    string getCategory() const { return "Novel"; }

    // Function to get extra information about the book
    string getExtraInfo() const {
        stringstream ss;
        ss << "publish_date : " << publishDate;
        return ss.str();
    }
};

// Abstract base class for Person
class Person {
private:
    int id;                     // Unique ID for the person
    string name;                // Name of the person
    int borrowed;               // Number of books borrowed
    int rentedBooks[3];         // Array to store codes of rented books
    Person* next;               // Pointer to the next person in the linked list

public:
    // Constructor for Person class
    Person(int i, string n, int b) : id(i), name(n), borrowed(b), next(NULL) {
        fill_n(rentedBooks, 3, -1); // Initialize with -1 (no book rented)
    }

    // Pure virtual function to display person details
    virtual void display() const = 0;

    // Getter functions
    string getName() const { return name; }
    int getId() const { return id; }
    int getBorrowed() const { return borrowed; }
    int* getRentedBooks() { return rentedBooks; }

    // Setter functions
    void setBorrowed(int b) { borrowed = b; }
    void setNext(Person* n) { next = n; }
    Person* getNext() const { return next; }

    // Function to add a rented book
    void addRentedBook(int bookCode) {
        for (int i = 0; i < 3; ++i) {
            if (rentedBooks[i] == -1) {
                rentedBooks[i] = bookCode;
                break;
            }
        }
    }

    // Function to remove a rented book
    void removeRentedBook(int bookCode) {
        for (int i = 0; i < 3; ++i) {
            if (rentedBooks[i] == bookCode) {
                rentedBooks[i] = -1;
                break;
            }
        }
    }

    // Function to check if a book is already rented
    bool hasRentedBook(int bookCode) {
        for (int i = 0; i < 3; ++i) {
            if (rentedBooks[i] == bookCode) {
                return true;
            }
        }
        return false;
    }

    // Virtual destructor
    virtual ~Person() {}
};

// Derived class for Student
class Student : public Person {
private:
    int borrowedBooks[2];       // Array to store codes of borrowed books for students

public:
    // Constructor for Student class
    Student(int i, string n, int b, int* books) : Person(i, n, b) {
        for (int j = 0; j < b; j++) {
            borrowedBooks[j] = books[j];
        }
    }

    // Function to display student details
    void display() const {
        cout << "Student: " << getName() << " ID: " << getId() << " Borrowed books: ";
        for (int j = 0; j < getBorrowed(); j++) {
            cout << borrowedBooks[j] << " ";
        }
        cout << endl;
    }
};

// Derived class for Teacher
class Teacher : public Person {
private:
    int borrowedBooks[3];       // Array to store codes of borrowed books for teachers

public:
    // Constructor for Teacher class
    Teacher(int i, string n, int b, int* books) : Person(i, n, b) {
        for (int j = 0; j < b; j++) {
            borrowedBooks[j] = books[j];
        }
    }

    // Function to display teacher details
    void display() const {
        cout << "Teacher: " << getName() << " ID: " << getId() << " Borrowed books: ";
        for (int j = 0; j < getBorrowed(); j++) {
            cout << borrowedBooks[j] << " ";
        }
        cout << endl;
    }
};

// Class to manage the library and persons
class LibraryManager {
private:
    Book* library[3];
    Person* persons[2];

public:
    // Constructor to initialize the arrays
    LibraryManager() {
        for (int i = 0; i < 3; ++i) {
            library[i] = nullptr;
        }
        for (int i = 0; i < 2; ++i) {
            persons[i] = nullptr;
        }
    }

    // Function to add a book to the library
    void addBook(Book* book, int index) {
        if (library[index] == nullptr) {
            library[index] = book;
        } else {
            Book* temp = library[index];
            while (temp->getNext() != nullptr) {
                temp = temp->getNext();
            }
            temp->setNext(book);
        }
    }

    // Function to add a person to the list
    void addPerson(Person* person, int index) {
        if (persons[index] == nullptr) {
            persons[index] = person;
        } else {
            Person* temp = persons[index];
            while (temp->getNext() != nullptr) {
                temp = temp->getNext();
            }
            temp->setNext(person);
        }
    }

    // Function to read books from a file and add to the library
    void readBooks(const string& filename) {
        ifstream file(filename.c_str());
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int code, available, rented;
            string title;
            ss >> code;
            ss.ignore(); // ignore space
            getline(ss, title, ' ');
            if (code >= 1001 && code <= 2000) { // Children Book
                int age;
                ss >> age >> available >> rented;
                addBook(new ChildrenBook(code, title, available, rented, age), 0);
            } else if (code >= 2001 && code <= 3000) { // Computer Book
                string publisher;
                ss >> publisher >> available >> rented;
                addBook(new ComputerBook(code, title, available, rented, publisher), 1);
            } else if (code >= 3001 && code <= 4000) { // Novel
                int publishDate;
                ss >> publishDate >> available >> rented;
                addBook(new Novel(code, title, available, rented, publishDate), 2);
            }
        }
    }

    // Function to read persons from a file and add to the list
    void readPersons(const string& filename) {
        ifstream file(filename.c_str());
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id, borrowed;
            string name;
            ss >> id >> name >> borrowed;
            int books[3];
            for (int i = 0; i < borrowed; i++) {
                ss >> books[i];
            }
            Person* person = nullptr;
            if (borrowed <= 2) { // Student
                person = new Student(id, name, borrowed, books);
                addPerson(person, 1);
            } else { // Teacher
                person = new Teacher(id, name, borrowed, books);
                addPerson(person, 0);
            }
            for (int i = 0; i < borrowed; i++) {
                person->addRentedBook(books[i]);
            }
        }
    }

    // Function to return a rented book
    void returnBook() {
        int id, code;
        cout << endl; 
        cout << "Enter your id: ";
        cin >> id;
        Person* person = searchPersonById(id);
        if (person == nullptr) {
            cout << "Person not found." << endl;
            return;
        }

        cout << "Enter the book code to return: ";
        cin >> code;

        if (!person->hasRentedBook(code)) {
            cout << "The id did not rent the book." << endl;
            return;
        }

        Book* book = searchBookByCode(code);
        if (book == nullptr) {
            cout << "Book not found." << endl;
            return;
        }

        cout << endl; 
        cout << "Do you want to return '" << book->getTitle() << "' (y/n)? ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            book->setAvailable(book->getAvailable() + 1);
            book->setRented(book->getRented() - 1);
            person->setBorrowed(person->getBorrowed() - 1);
            person->removeRentedBook(code);
            cout << "***** Return succeed. Check your info!" << endl;
        } else {
            cout << "Return cancelled." << endl;
        }
    }

    // Function to display books sorted by code
    void displayBooksSorted(Book* head) {
        if (head == nullptr) return;

        // Count the number of books
        int count = 0;
        Book* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->getNext();
        }

        // Create an array to store the books
        Book** books = new Book*[count];
        temp = head;
        for (int i = 0; i < count; i++) {
            books[i] = temp;
            temp = temp->getNext();
        }

        // Sort the array using bubble sort
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (books[j]->getCode() > books[j + 1]->getCode()) {
                    Book* temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }

        // Display the sorted books
        for (int i = 0; i < count; i++) {
            books[i]->display();
        }

        // Clean up
        delete[] books;
    }

    // Function to search for a book by code
    Book* searchBookByCode(int code) {
        for (int i = 0; i < 3; ++i) {
            Book* current = library[i];
            while (current != nullptr) {
                if (current->getCode() == code) {
                    return current;
                }
                current = current->getNext();
            }
        }
        return nullptr;
    }

    // Function to display details of a person by ID
    void displayPersonById(int id) {
        Person* person = searchPersonById(id);
        if (person != nullptr) {
            cout << "Enter your name: ";
            string name;
            cin >> name;
            if (person->getName() == name) {
                cout << endl; 
                cout << "You rented " << person->getBorrowed() << " books." << endl;
                int* rentedBooks = person->getRentedBooks();
                for (int i = 0; i < person->getBorrowed(); i++) {
                    Book* book = searchBookByCode(rentedBooks[i]);
                    if (book != nullptr) {
                        cout << "* " << book->getTitle() << "(" << book->getCode() << ") - " << book->getExtraInfo() << endl;
                    }
                }
            } else {
                cout << "Name does not match ID." << endl;
            }
        } else {
            cout << "Person not found." << endl;
        }
    }

    // Function to display all books in the library
    void displayBooks() {
        cout << endl; 
        cout << endl; 
        cout << "----------------------------------------------------------------------\n";
        cout << "                         Children Books\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "code  title                           age         available   rented\n";
        cout << "----------------------------------------------------------------------\n";
        displayBooksSorted(library[0]);


        cout << "--------------------------------------------------------------------------------\n";
        cout << "                              Computer Books\n";
        cout << "--------------------------------------------------------------------------------\n";

        cout << "code  title                           publisher           available   rented\n";
        cout << "--------------------------------------------------------------------------------\n";
        displayBooksSorted(library[1]);

        cout << "----------------------------------------------------------------------\n";
        cout << "                             Novels\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "code  title                           publish_date   available   rented\n";
        cout << "----------------------------------------------------------------------\n";
        displayBooksSorted(library[2]);
    }

    // Function to display all persons
    void displayPersons() {
        cout << "----------------------------------------------------------------------\n";
        cout << "                            Teachers\n";
        cout << "----------------------------------------------------------------------\n";
        Person* temp = persons[0];
        while (temp != nullptr) {
            temp->display();
            temp = temp->getNext();
        }

        cout << "----------------------------------------------------------------------\n";
        cout << "                            Students\n";
        cout << "----------------------------------------------------------------------\n";
        temp = persons[1];
        while (temp != nullptr) {
            temp->display();
            temp = temp->getNext();
        }
    }

    // Function to delete all books in the library
    void deleteBooks(Book* head) {
        while (head != nullptr) {
            Book* temp = head;
            head = head->getNext();
            delete temp;
        }
    }

    // Function to delete all persons in the list
    void deletePersons(Person* head) {
        while (head != nullptr) {
            Person* temp = head;
            head = head->getNext();
            delete temp;
        }
    }

    // Function to search for a book by code and title
    Book* searchBook(int code, const string& title) {
        for (int i = 0; i < 3; ++i) {
            Book* current = library[i];
            while (current != nullptr) {
                if (current->getCode() == code && current->getTitle() == title) {
                    return current;
                }
                current = current->getNext();
            }
        }
        return nullptr;
    }

    // Function to search for a book by title
    Book* searchBookByTitle(const string& title) {
        for (int i = 0; i < 3; ++i) {
            Book* current = library[i];
            while (current != nullptr) {
                if (current->getTitle() == title) {
                    return current;
                }
                current = current->getNext();
            }
        }
        return nullptr;
    }

    // Function to search for a person by ID
    Person* searchPersonById(int id) {
        for (int i = 0; i < 2; ++i) {
            Person* current = persons[i];
            while (current != nullptr) {
                if (current->getId() == id) {
                    return current;
                }
                current = current->getNext();
            }
        }
        return nullptr;
    }

    // Main function to manage library operations
    void manageLibrary() {
        readBooks("book.txt");   // Read books from file
        readPersons("person.txt"); // Read persons from file

        int response;
        bool exit = false;
        while (!exit) {
            cout << endl; 
            cout << "----------------------\n";
            cout << "         Menu            \n";
            cout << "----------------------\n";
            cout << "1. Search a book\n";
            cout << "2. Rent a book\n";
            cout << "3. Return a book\n";
            cout << "4. Show my information\n";
            cout << "5. Show all books\n";
            cout << "6. Exit\n";
            cout << "Select (1-6) : ";
            cin >> response;
            switch (response) {
                case 1: {
                    int code;
                    string title;
                    cout << endl;
                    cout << "Enter code: ";
                    cin >> code;
                    cout << "Enter title: ";
                    cin.ignore(); // to ignore any newline character left in the buffer
                    getline(cin, title);

                    Book* book = searchBook(code, title);
                    if (book != nullptr) {
                        cout << endl; 
                        cout << title << " (" << book->getCode() << ") exists." << endl;
                        cout << "category : " << book->getCategory() << endl;
                        cout << book->getExtraInfo() << endl;
                        cout << book->getAvailable() << " available, " << book->getRented() << " rented" << endl;
                    } else {
                        cout << "Code and title do not match." << endl;
                    }
                    break;
                }
                case 2: {
                    int id;
                    string title;
                    cout << endl; 
                    cout << "Enter your id: ";
                    cin >> id;
                    cout << "Enter book title: ";
                    cin.ignore();
                    getline(cin, title);

                    Person* person = searchPersonById(id);
                    if (person == nullptr) {
                        cout << "Person not found." << endl;
                        break;
                    }

                    if ((dynamic_cast<Student*>(person) && person->getBorrowed() >= 2) || 
                        (dynamic_cast<Teacher*>(person) && person->getBorrowed() >= 3)) {
                        cout << "You already rented the maximum number of books." << endl;
                        break;
                    }

                    Book* book = searchBookByTitle(title);
                    if (book == nullptr) {
                        cout << "Book not found." << endl;
                        break;
                    }

                    if (book->getAvailable() == 0) {
                        cout << "The book is not available (all rented out)." << endl;
                        break;
                    }

                    if (person->hasRentedBook(book->getCode())) {
                        cout << "You have already rented this book." << endl;
                        break;
                    }
                    cout << endl; 
                    cout << "You are " << person->getName() << ". You rented " << person->getBorrowed() << " book(s)." << endl;
                    cout << "Do you want to rent '" << book->getTitle() << "' (y/n)? ";
                    char confirm;
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        book->setAvailable(book->getAvailable() - 1);
                        book->setRented(book->getRented() + 1);
                        person->setBorrowed(person->getBorrowed() + 1);
                        person->addRentedBook(book->getCode());
                        cout << "***** Rent succeed. Check your info!" << endl;
                    } else {
                        cout << "Rent cancelled." << endl;
                    }
                    break;
                }
                case 3: {
                    returnBook();
                    break;
                }
                case 4: {
                    int id;
                    cout << endl; 
                    cout << "Enter your id: ";
                    cin >> id;
                    displayPersonById(id);
                    break;
                }
                case 5:
                    displayBooks();
                    break;
                case 6:
                    exit = true;
                    break;
                default:
                    cout << "Invalid option. Please try again.\n";
            }
        }

        // Delete all books and persons before exiting
        for (int i = 0; i < 3; i++) {
            deleteBooks(library[i]);
        }
        for (int i = 0; i < 2; i++) {
            deletePersons(persons[i]);
        }
    }
};

// Main function
int main() {
    LibraryManager libraryManager;
    libraryManager.manageLibrary();
    return 0;
}
