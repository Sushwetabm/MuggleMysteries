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

// Book Database class
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

// Node class for k-ary tree
class listNode {
public:
    vector<Book> readingList;
    vector<listNode *> children;

    listNode(vector<Book> readingList)
    {
        this->readingList = readingList;
    }
};

// ReadingList class for managing k-ary tree of reading lists
class ReadingList {
public:
    listNode *root;
    int k; // Degree of the k-ary tree

    ReadingList(int k)
    {
        root = NULL;
        this->k = k;
    }

    void addList(vector<Book> readingList);
    void displayLists();
    void removeBook(string title);
    void reorderBooks(vector<string> newOrder);
    // Additional functions for k-ary tree operations
    void createFolder();
    void moveListToFolder(listNode *list, listNode *folder);
};

// Function declarations for k-ary tree operations
listNode *insertList(listNode *root, vector<Book> newList, int k);
void inOrderTraversal(listNode *root);
listNode *removeBookHelper(listNode *root, string title);
listNode *reorderBooksHelper(listNode *root, vector<string> newOrder);

// Function definitions for k-ary tree operations
listNode *insertList(listNode *root, vector<Book> newList, int k)
{
    if (root == NULL)
    {
        return new listNode(newList);
    }

    // If the current node has less than k children, insert the new list as a child
    if (root->children.size() < k)
    {
        root->children.push_back(new listNode(newList));
    }
    else
    {
        // Find the first child with fewer than k children and insert the new list there
        for (auto &child : root->children)
        {
            if (child->children.size() < k)
            {
                child = insertList(child, newList, k);
                return root;
            }
        }

        // If all children have k children, create a new child and insert the new list
        root->children.push_back(new listNode(newList));
    }

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

    // Traverse each child
    for (auto child : root->children)
    {
        inOrderTraversal(child);
    }
}

listNode *removeBookHelper(listNode *root, string title)
{
    if (root == NULL)
        return root;

    // Find the book to be removed and remove it from the reading list
    root->readingList.erase(remove_if(root->readingList.begin(), root->readingList.end(),
                                      [title](const Book &book) { return book.title == title; }),
                             root->readingList.end());

    // Remove any child nodes that have become empty after the book removal
    root->children.erase(remove_if(root->children.begin(), root->children.end(),
                                   [](listNode *child) { return child->readingList.empty() && child->children.empty(); }),
                         root->children.end());

    // Recur for each remaining child
    for (auto &child : root->children)
    {
        child = removeBookHelper(child, title);
    }

    return root;
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

    // Recur for each remaining child
    for (auto &child : root->children)
    {
        child = reorderBooksHelper(child, newOrder);
    }

    return root;
}


// Function definitions for ReadingList class
void ReadingList::addList(vector<Book> readingList)
{
    root = insertList(root, readingList, k);
}

void ReadingList::displayLists()
{
    inOrderTraversal(root);
}

void ReadingList::removeBook(string title)
{
    root = removeBookHelper(root, title);
}

void ReadingList::reorderBooks(vector<string> newOrder)
{
    root = reorderBooksHelper(root, newOrder);
}

void ReadingList::createFolder()
{
    // Create a new list node as a folder
    listNode *folder = new listNode(vector<Book>());
    root->children.push_back(folder);
}
void ReadingList::moveListToFolder(listNode *list, listNode *folder)
{
    // Remove the list from its current position within its parent
    auto it = find(root->children.begin(), root->children.end(), list);
    if (it != root->children.end())
    {
        root->children.erase(it);

        // Add the list to the specified folder
        folder->children.push_back(list);
    }
}


int main()
{
    // Initialize your book database and reading list
    Database bookDB;
    ReadingList readingLists(3); // Create a k-ary tree with degree 3

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

    // Create a folder and move the reading list to the folder
    readingLists.createFolder();
    cout << "\nReading List after creating a folder:" << endl;
    readingLists.displayLists();

    listNode *folder = readingLists.root->children[0];
    readingLists.moveListToFolder(readingLists.root, folder);
    cout << "\nReading List after moving to folder:" << endl;
    readingLists.displayLists();

    return 0;
}
