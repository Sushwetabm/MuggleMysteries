#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Book structure
class Book {
public:
    string title;
    string author;
    string genre;
    float rating;
    int pageCount;
    Book() {}
    Book(string title, string author, string genre, float rating, int pageCount)
    {
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->rating = rating;
        this->pageCount = pageCount;
    }
};

// Book Database class
class Database {
public:
    unordered_map<string, Book> books;
    void addBook(Book newBook);
    Book getBook(const string& title);
    void displayByGenre();
    void displayByAuthor();
    void searchBooksByGenre(const string& genre);
    void searchBooksByAuthor(const string& author);

};

void Database::addBook(Book newBook)
{
    books[newBook.title] = newBook;
}

Book Database::getBook(const string& title)
{
    if (books.find(title) != books.end()) {
        return books[title];
    } else {
        cout << "Book with title '" << title << "' not found." << endl;
        return Book();
    }
}

void Database::searchBooksByGenre(const string& genre)
{
    cout << "Books in the genre '" << genre << "':" << endl;
    for (const auto& pair : books) {
        if (pair.second.genre == genre) {
            cout << pair.second.title << " by " << pair.second.author << endl;
        }
    }
    cout << endl;
}

void Database::searchBooksByAuthor(const string& author)
{
    cout << "Books by the author '" << author << "':" << endl;
    for (const auto& pair : books) {
        if (pair.second.author == author) {
            cout << pair.second.title << " in the genre " << pair.second.genre << endl;
        }
    }
    cout << endl;
}
void Database::displayByGenre()
{

    int ch=1;
    while(ch!=0)
    {
        cout<<"Chose the genre you want to explore:"<<endl;
        cout<<"1.Mystery"<<endl;;
        cout<<"2.Romance"<<endl;
        cout<<"3.Science Fiction"<<endl;
        cout<<"4.Fantasy"<<endl;
        cout<<"5.Horror"<<endl;
        cout<<"6.Historical"<<endl;
        cout<<"7.Thriller"<<endl;
        cout<<"8.Classics"<<endl;
        cout<<"9.Poetry"<<endl;
        cout<<"10.Autobiography"<<endl;
        cout<<"0.Exit menu"<<endl;
        cout<<"Enter choice: ";
        cin>>ch;

        switch (ch)
        {
            case 0:
                break;
            case 1:
                {
                    searchBooksByGenre("Mystery");
                    break;
                }
            case 2:
                {
                    searchBooksByGenre("Romance");
                    break;
                }
            case 3:
                {
                    searchBooksByGenre("Science Fiction");
                    break;
                }
             case 4:
                {
                    searchBooksByGenre("Fantasy");
                    break;
                }
            case 5:
                {
                    searchBooksByGenre("Horror");
                    break;
                }
            case 6:
                {
                    searchBooksByGenre("Historical");
                    break;
                }
            case 7:
                {
                    searchBooksByGenre("Thriller");
                    break;
                }
            case 8:
                {
                    searchBooksByGenre("Classics");
                    break;
                }
            case 9:
                {
                    searchBooksByGenre("Poetry");
                    break;
                }
             case 10:
                {
                    searchBooksByGenre("Autobiography");
                    break;
                }
             default:
                cout<<"Please enter a valid number";
                break;

            }
    }
}
void Database::displayByAuthor()
{

    int ch=1;
    while(ch!=0)
    {
        cout<<"Chose the author whose book you want to explore:"<<endl;
        cout<<"1. Agatha Christie"<<endl;;
        cout<<"2. Ana Huang"<<endl;
        cout<<"3. Dan Brown"<<endl;
        cout<<"4. J K Rowling"<<endl;
        cout<<"5. Stephen King"<<endl;
        cout<<"6. Charles Dickens"<<endl;
        cout<<"7. Paula Hawkins"<<endl;
        cout<<"8. Jane Austen"<<endl;
        cout<<"9. Sylvia Path"<<endl;
        cout<<"10. Leo Tolstoy"<<endl;
        cout<<"0.Exit menu"<<endl;
        cout<<"Enter choice: ";
        cin>>ch;

        switch (ch)
        {
            case 0:
                break;
            case 1:
                {
                    searchBooksByAuthor("Agatha Christie");
                    break;
                }
            case 2:
                {
                    searchBooksByAuthor("Nora Roberts");
                    break;
                }
            case 3:
                {
                    searchBooksByAuthor("Dan Brown");
                    break;
                }
             case 4:
                {
                    searchBooksByAuthor("J K Rowling");
                    break;
                }
            case 5:
                {
                    searchBooksByAuthor("Stephen King");
                    break;
                }
            case 6:
                {
                    searchBooksByAuthor("Charles Dickens");
                    break;
                }
            case 7:
                {
                    searchBooksByAuthor("Paula Hawkins");
                    break;
                }
            case 8:
                {
                    searchBooksByAuthor("Jane Austen");
                    break;
                }
            case 9:
                {
                    searchBooksByAuthor("Sylvia Path");
                    break;
                }
             case 10:
                {
                    searchBooksByAuthor("Leo Tolstoy");
                    break;
                }
             default:
                cout<<"Please enter a valid number";
                break;

            }

    }
}
class ReadingListNode
 {
public:
    string ReadingListName;
    vector <string> bookNames;
    ReadingListNode *left;
    ReadingListNode *right;
    ReadingListNode(){}
    ReadingListNode(string rl_name)
     {
        ReadingListName=rl_name;
        left=right=NULL;

     }

 };
class ReadingListTree
{
private:
    ReadingListNode *root;
public:
    ReadingListTree()
    {
        root = NULL;
    }
    void insertReadingList(ReadingListNode*& root, string rl_name);
    void printLevelOrder(ReadingListNode* root);
    void addBookIntoRL(string bookName, string rl_name);
    void removeBookFromRL(string bookName, string rl_name);
    void getReadingList(ReadingListNode*& root, string rl_name);

};
// Function to add new ReadingListName in level order
void ReadingListTree :: insertReadingList(ReadingListNode*& root, string rl_name)
{
    ReadingListNode* temp = new ReadingListNode(rl_name); // Initialize with ReadingListName
    temp->ReadingListName = rl_name;
    temp->left = temp->right = NULL;
    if (!root)
        root = temp;
    else {
        queue<ReadingListNode*> q;
        q.push(root);
        while (!q.empty()) {
            ReadingListNode* temp = q.front();
            q.pop();
            if (!temp->left)
            {
                temp->left = new ReadingListNode;
                temp->left->ReadingListName = rl_name;
                temp->left->left = temp->left->right = NULL;
                break;
            }
            else
                q.push(temp->left);
            if (!temp->right)
            {
                temp->right = new ReadingListNode;
                temp->right->ReadingListName = rl_name;
                temp->right->left = temp->right->right = NULL;
                break;
            }
            else
                q.push(temp->right);
            }
        }
}

// Function to print Level Order Traversal
void ReadingListTree :: printLevelOrder(ReadingListNode* root) {
    if (root == NULL) return;
    queue<ReadingListNode*> q;
    q.push(root);
    while (!q.empty()) {
        ReadingListNode* node = q.front();
        cout << node->ReadingListName << " ";
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
        }
}
void ReadingListTree :: addBookIntoRL(string bookName, string rl_name)
{
    if (root == NULL) return;
    queue<ReadingListNode*> q;
    q.push(root);
    while (!q.empty()) {
        ReadingListNode* node = q.front();
        if (node->ReadingListName == rl_name)
        {
            node->bookNames.push_back(bookName);
            break;
        }
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
        }
}
void ReadingListTree :: removeBookFromRL(string bookName, string rl_name)
{
    if (root == NULL)
        return;
    queue<ReadingListNode*> q;
    q.push(root);
    while (!q.empty()) {
        ReadingListNode* node = q.front();
        if (node->ReadingListName == rl_name)
        {
            auto it = find(node->bookNames.begin(), node->bookNames.end(),
                   bookName);
            if (it != node->bookNames.end()) {
                node->bookNames.erase(it);
            }
            break;
        }
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
        }
}

void ReadingListTree :: getReadingList(ReadingListNode*& root, string rl_name) {
{
    if (root == NULL) return;
    queue<ReadingListNode*> q;
    q.push(root);
    while (!q.empty())
        {
        ReadingListNode* node = q.front();
        if (node->ReadingListName == rl_name)
        {
            int n = node->bookNames.size();
            for(int i = 0; i < n; i++)
            {
                cout << node->bookNames[i] << endl;
            }
            break;
        }
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
        }
}
int main()
{

    return 0;
}
