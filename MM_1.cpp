#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Book structure
struct Book {
    string title;
    string author;
    string genre;
    int pageCount;
};

// Reading List Node
struct ReadingListNode {
    string listName;
    vector<Book> books;
};

// Folder Node
struct FolderNode {
    string folderName;
    vector<string> readingLists; // Stores reading lists and sub-folders
};

// Book Database (Map)
unordered_map<string, Book> bookDatabase;

// Reading Lists (Graph)
unordered_map<string, ReadingListNode> readingListGraph;
unordered_map<string, vector<string>> adjacencyList;

// Reading List Organization (Tree)
FolderNode rootFolder; // The root of the folder tree

// Function to add a book to the database
void addBook(const string& title, const string& author, const string& genre, int pageCount) {
    Book newBook = {title, author, genre, pageCount};
    bookDatabase[title] = newBook;
}

// Function to add a reading list
void addReadingList(const string& listName) {
    ReadingListNode newList;
    newList.listName = listName;
    readingListGraph[listName] = newList;
}

// Function to add a book to a reading list
void addBookToReadingList(const string& listName, const string& bookTitle) {
    if (readingListGraph.find(listName) != readingListGraph.end() && bookDatabase.find(bookTitle) != bookDatabase.end()) {
        readingListGraph[listName].books.push_back(bookDatabase[bookTitle]);
        adjacencyList[listName].push_back(bookTitle);
    }
}

// Function to display books in a reading list
void displayBooksInReadingList(const string& listName) {
    if (readingListGraph.find(listName) != readingListGraph.end()) {
        cout << "Books in Reading List '" << listName << "':" << endl;
        for (const auto& book : readingListGraph[listName].books) {
            cout << "Title: " << book.title << ", Author: " << book.author << ", Genre: " << book.genre << ", Page Count: " << book.pageCount << endl;
        }
    } else {
        cout << "Reading List '" << listName << "' not found." << endl;
    }
}

// Function to display all reading lists
void displayAllReadingLists() {
    cout << "All Reading Lists:" << endl;
    for (const auto& pair : readingListGraph) {
        cout << pair.first << endl;
    }
}

// Function to create a folder
void createFolder(const string& folderName) {
    FolderNode newFolder;
    newFolder.folderName = folderName;
    rootFolder.readingLists.push_back(folderName);
}

// Function to display all folders and reading lists in the tree
void displayFolderTree(FolderNode& folderNode, int level = 0) {
    for (const auto& item : folderNode.readingLists) {
        if (item.find("Folder:") == 0) {
            // Display folder
            cout << string(level, '\t') << item.substr(7) << " (Folder)" << endl;
            displayFolderTree(rootFolder, level + 1);
        } else {
            // Display reading list
            cout << string(level, '\t') << item << endl;
        }
    }
}

// Function to delete a reading list
void deleteReadingList(const string& listName) {
    if (readingListGraph.find(listName) != readingListGraph.end()) {
        readingListGraph.erase(listName);

        // Remove references in the adjacency list
        for (auto& pair : adjacencyList) {
            pair.second.erase(remove_if(pair.second.begin(), pair.second.end(),
                                        [&](const string& s) { return s == listName; }),
                              pair.second.end());
        }

        cout << "Reading List '" << listName << "' deleted." << endl;
    } else {
        cout << "Reading List '" << listName << "' not found." << endl;
    }
}

// Function to move a reading list to a folder
void moveReadingListToFolder(const string& listName, const string& folderName) {
    // Check if the folder exists
    auto folderIt = find(rootFolder.readingLists.begin(), rootFolder.readingLists.end(), "Folder:" + folderName);
    if (folderIt != rootFolder.readingLists.end()) {
        // Check if the reading list exists
        auto listIt = find(rootFolder.readingLists.begin(), rootFolder.readingLists.end(), listName);
        if (listIt != rootFolder.readingLists.end()) {
            // Move the reading list to the folder
            rootFolder.readingLists.erase(listIt);
            rootFolder.readingLists.push_back(folderName);
            cout << "Reading List '" << listName << "' moved to folder '" << folderName << "'." << endl;
        } else {
            cout << "Reading List '" << listName << "' not found." << endl;
        }
    } else {
        cout << "Folder '" << folderName << "' not found." << endl;
    }
}

// Add more functions based on your requirements

int main() {
    // Sample usage of functions
    addBook("Book1", "Author1", "Fiction", 300);
    addBook("Book2", "Author2", "Mystery", 250);

    addReadingList("To Read");
    addBookToReadingList("To Read", "Book1");

    displayBooksInReadingList("To Read");
    displayAllReadingLists();

    createFolder("Fantasy");
    createFolder("Mystery");

    displayFolderTree(rootFolder);

    moveReadingListToFolder("To Read", "Fantasy");

    return 0;
}
