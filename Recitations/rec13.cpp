//
// Jiezhi Winston Zou-yu
// rec13.cpp
//
#include <iostream>
#include <vector>
using namespace std;

class List{
    struct Node{
        Node(int data=0, Node* next = nullptr, Node* prior = nullptr)
        : data(data), next(next), prior(prior){}
        int data;
        Node* next;
        Node* prior;
    };

    friend ostream& operator<<(ostream& os,const List& list) {
        if (list.size() > 0) {
            Node* currNode = list.header->next;
            while (currNode != list.trailer) {
                os << currNode->data << " ";
                currNode = currNode->next;
            }
        }
        return os;
    }

public:
    class iterator {
        friend List;
        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return (lhs.node == rhs.node);
        }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return !(lhs == rhs);
        }
    public:
        iterator(Node* where) : node(where) {}
        iterator& operator++() {
            if (node && node->next) node = node->next;
            return *this;
        }
        iterator& operator--() {
            if (node && node->prior) node = node->prior;
            return *this;
        }
        int& operator*() {
            return node->data;
        }

        int operator*() const {
            return node->data;
        }

    private:
        Node* node;
    };

    List(): header(new Node()), trailer(new Node()), length(0) {
        trailer->prior = header;
        header->next = trailer;
    }

    void push_back(int data) {
        Node* newNode = new Node(data, trailer, trailer->prior);
        trailer->prior->next = newNode;
        trailer->prior = newNode;
        length += 1;
    }

    void pop_back() {
        if (length == 0){
            exit(1);
        }
        Node* remove = trailer->prior;
        remove->prior->next = trailer;
        trailer->prior = remove->prior;
        delete remove;
        length -= 1;
    }
    void push_front(int data) {
        Node* newNode = new Node(data, header->next, header);
        header->next->prior = newNode;
        header->next = newNode;
        length += 1;
    }
    void pop_front() {
        if (length == 0){
            exit(1);
        }
        Node* remove = header->next;
        remove->next->prior = header;
        header->next = remove->next;
        delete remove;
        length -= 1;
    }
    int& front() {
        if (length == 0){
            exit(1);
        }
        return header->next->data;
    }
    const int front() const {
        if (length == 0){
            exit(1);
        }
        return header->next->data;
    }

    int& back() {
        if (length == 0){
            exit(1);
        }
        return trailer->prior->data;
    }
    const int back() const{
        if (length == 0){
            exit(1);
        }
        return trailer->prior->data;
    }
    size_t size() const {
        return length;
    }

    void clear() {
        if (length == 0){
            exit(1);
        }
        while (length > 0) {
            pop_back();
        }
    }

    int& operator[](int data) {
        if (length == 0){
            exit(1);
        }
        int start = 0;
        Node* currNode = header->next;
        while (start < data) {
            currNode = currNode->next;
            start += 1;
        }
        return currNode->data;
    }
    const int operator[](int data) const {
        if (length == 0){
            exit(1);
        }
        int start = 0;
        Node* currNode = header->next;
        while (start < data) {
            currNode = currNode->next;
            start += 1;
        }
        return currNode->data;
    }
    iterator begin() {
        iterator it(header->next);
        return it;
    }
    iterator end() {
        iterator it(trailer);
        return it;
    }
    iterator insert(iterator where, int data) {
        Node* newNode = new Node(data, where.node, where.node->prior);
        newNode->prior->next = newNode;
        newNode->next->prior = newNode;
        iterator it(newNode);
        length += 1;
        return it;
    }
    iterator erase(iterator where) {
        Node* next = where.node->next;
        Node* prior = where.node->prior;
        prior->next = next;
        next->prior = prior;
        iterator it(next);
        length -= 1;
        return it;
    }
private:
    Node* header;
    Node* trailer;
    size_t length;
};

// Task 1
void printListInfo(const List& myList) {
    cout << "size: " << myList.size()
         << ", front: " << myList.front()
         << ", back(): " << myList.back()
         << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

int main() {
    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";
    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";
    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";
    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";
}
