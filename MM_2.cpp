#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Book structure
class Book {
public:
    string title;
    string author;
    string genre;
    int pageCount;
    Book() {}
    Book(string title, string author, string genre, int pageCount)
    {
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->pageCount = pageCount;
    }
};

// Database class
class Database {
public:
    unordered_map<string, Book> books;
    void addBook(Book newBook);
    Book getBook(string title);
};

void Database::addBook(Book newBook)
{
    books[newBook.title] = newBook;
}

Book Database::getBook(string title)
{
    return books[title];
}

// Node class
class listNode {
public:
    vector<Book> readingList;
    listNode *left;
    listNode *right;

    listNode(vector<Book> readingList)
    {
        this->readingList = readingList;
        left = NULL;
        right = NULL;
    }
};

// Function prototypes
listNode *insertList(listNode *root, vector<Book> newList);
void inOrderTraversal(listNode *root);
listNode *removeBookHelper(listNode *root, string title);
listNode *reorderBooksHelper(listNode *root, vector<string> newOrder);

// Reading List class
class ReadingList {
public:
    listNode *root;

    ReadingList()
    {
        root = NULL;
    }

    void addList(vector<Book> readingList)
    {
        root = insertList(root, readingList);
    }

    void displayLists()
    {
        inOrderTraversal(root);
    }

    void removeBook(string title);
    void reorderBooks(vector<string> newOrder);
};

listNode *insertList(listNode *root, vector<Book> newList)
{
    if (root == NULL)
    {
        return new listNode(newList);
    }

    // Implement logic to insert based on a specific condition (e.g., alphabetical order)
    // You may use the book titles for comparison
    // For simplicity, the new list is added to the right of the current node
    root->right = insertList(root->right, newList);

    return root;
}

void inOrderTraversal(listNode *root)
{
    if (root == NULL)
        return;

    // Display the contents of the current node
    for (const auto &book : root->readingList)
    {
        cout << "Title: " << book.title << ", Author: " << book.author << ", Genre: " << book.genre << ", Page Count: " << book.pageCount << endl;
    }

    // Traverse the left and right subtrees
    inOrderTraversal(root->left);
    inOrderTraversal(root->right);
}

void ReadingList::removeBook(string title)
{
    root = removeBookHelper(root, title);
}

listNode *removeBookHelper(listNode *root, string title)
{
    if (root == NULL)
        return root;

    // Find the book to be removed and remove it from the reading list
    root->readingList.erase(remove_if(root->readingList.begin(), root->readingList.end(),
                                      [title](const Book &book) { return book.title == title; }),
                             root->readingList.end());

    // Recur for the left and right subtrees
    root->left = removeBookHelper(root->left, title);
    root->right = removeBookHelper(root->right, title);

    return root;
}

void ReadingList::reorderBooks(vector<string> newOrder)
{
    root = reorderBooksHelper(root, newOrder);
}

listNode *reorderBooksHelper(listNode *root, vector<string> newOrder)
{
    if (root == NULL)
        return root;

    vector<Book> reorderedList;

    // Reorder the books based on the new order
    for (const auto &title : newOrder)
    {
        auto it = find_if(root->readingList.begin(), root->readingList.end(),
                          [title](const Book &book) { return book.title == title; });

        if (it != root->readingList.end())
        {
            reorderedList.push_back(*it);
        }
    }

    // Replace the existing reading list with the reordered one
    root->readingList = reorderedList;

    // Recur for the left and right subtrees
    root->left = reorderBooksHelper(root->left, newOrder);
    root->right = reorderBooksHelper(root->right, newOrder);

    return root;
}

int main()
{
    // Initialize your book database and reading list
    Database bookDB;
    ReadingList readingLists;

    // Add books to the database
    Book book1("The Hobbit", "J.R.R. Tolkien", "Fantasy", 300);
    Book book2("To Kill a Mockingbird", "Harper Lee", "Fiction", 350);
    Book book3("1984", "George Orwell", "Dystopian", 400);

    bookDB.addBook(book1);
    bookDB.addBook(book2);
    bookDB.addBook(book3);

    // Create a reading list
    vector<Book> myReadingList = {book1, book2};
    readingLists.addList(myReadingList);

    // Display reading lists
    cout << "Initial Reading Lists:" << endl;
    readingLists.displayLists();

    // Remove a book from the reading list
    readingLists.removeBook("To Kill a Mockingbird");
    cout << "\nReading List after removing a book:" << endl;
    readingLists.displayLists();

    // Reorder books in the reading list
    vector<string> newOrder = {"1984", "The Hobbit"};
    readingLists.reorderBooks(newOrder);
    cout << "\nReading List after reordering books:" << endl;
    readingLists.displayLists();

    return 0;
}
