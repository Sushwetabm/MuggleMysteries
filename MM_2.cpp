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
    Book(){}
    Book(string title, string author, string genre, int pageCount)
    {
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->pageCount = pageCount;
    }
};
//Database class
class Database{
public:
    unordered_map<string, Book> books;
    void addBook(Book newBook);
    Book getBook(string title);
};

void Database::addBook(Book newBook)
{
    books[newBook.title] = newBook;
}
Book Database::getBook()
{
    return books[title];
}
//Node class
class listNode{
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
class ReadingList{
public:
    listNode *root;

    ReadingList(){}
    ReadingList()
    {
        root = NULL;
    }
    void addList(vector<Book> readingList)
    {
        root = insertList(root,readingList);
    }
    void displayLists()
    {
        inOrderTraversal(root);
    }
}

};
listNode* insertList(listNode* root, vector<Book> newList)
{

}

void inOrderTraversal(listNode* root)
{

}
/*
// Reading List Node
class ReadingListNode {
    string listName;
    vector<Book> books;
};

// Folder Node
struct FolderTreeNode {
    string folderName;
    vector<string> readingLists; // Stores reading lists and sub-folders
};

// Book Database (Map)
unordered_map<string, Book> bookDatabase;

// Reading Lists (Graph)
unordered_map<string, ReadingListNode> readingListGraph;
unordered_map<string, vector<string>> adjacencyList;

// Reading List Organization (Tree)
FolderTreeNode rootFolder; // The root of the folder tree

class Tree
{

};
*/
