//
// Jiezhi Winston Zuo-yu
// polynomial.cpp
//
#include "polynomial.h"
using namespace std;

//Constructor for Node struct
Node::Node (int data, Node* next) : data(data), next(next) {}

//output operator for Polynomial
ostream& operator<<(ostream& os,const Polynomial& polynomial) {
        Node* currNode = polynomial.headptr;
        int degree = polynomial.degree;
        string sign = " + ";
        int data = currNode->data;
        if (degree == 0) {
            os << data;
            return os;
        }
        else if (data != 0) {
            if (data == -1) {
                os << "-x";
            }
            else if (data == 1) {
                os << "x";
            }
            else {
                os << data << "x";
            }
            if (degree > 1) {
                os << "^" << degree;
            }
        }
        degree -= 1;
        currNode = currNode->next;
        while (currNode != nullptr) {
            data = currNode -> data;
            if (data < 0) {
                sign = " - ";
                data *= -1;
            }
            else if (data > 0) {
                sign = " + ";
            }
            else{
                sign = "";
            }
            os << sign;
            if (degree == 0) {
                os << data;
                return os;
            }
            else if (data != 0) {
                if (data != 1) {
                    os << data;
                }
                if (degree == 1) {
                    os << "x";
                }
                else {
                    os << "x^" << degree;
                }
            }
            degree -= 1;
            currNode = currNode->next;
        }
        return os;
    }
    //Constructor for Polynomial given coefficients
    Polynomial::Polynomial (const vector<int>& coefficients) :
    headptr(createLL(coefficients)){}
    //Default constructor for Polynomial
    Polynomial::Polynomial (): headptr(new Node(0)), degree(0){}
    //Helper function for Polynomial
    Node* Polynomial::createLL(const vector<int>& coefficients) {
        int currDegree = coefficients.size() - 1;
        size_t nonZero = 0;
        while (coefficients[nonZero] == 0) {
            nonZero += 1;
            currDegree -= 1;
        }
        Node* head = new Node(coefficients[nonZero]);
        Node* currNode = head;
        for (size_t i = nonZero + 1; i < coefficients.size(); ++ i) {
            Node* node = new Node (coefficients[i]);
            currNode = addNode(currNode, node);
        }
        degree = currDegree;
        return head;
    }
    //Helper function; links two nodes
    Node* Polynomial::addNode(Node* node, Node* nodetoadd){
        node->next = nodetoadd;
        return nodetoadd;
    }
    //Destructor for Polynomial
    Polynomial::~Polynomial() {
        Node* currNode = headptr;
        while (currNode != nullptr) {
            Node* next = currNode->next;
            delete currNode;
            currNode = next;
        }
    }
    //Copy constructor for Polynomial
    Polynomial::Polynomial(const Polynomial& rhs) {
        Node* currNode = rhs.headptr;
        headptr = new Node(currNode->data, nullptr);
        degree = rhs.degree;
        currNode = currNode->next;
        Node* nodeTrack = headptr;
        while (currNode != nullptr) {
            Node* newNode = new Node(currNode->data, nullptr);
            nodeTrack->next = newNode;
            nodeTrack = nodeTrack->next;
            currNode = currNode->next;
        }
    }
    //Assignment operator for Polynomial
    Polynomial& Polynomial::operator=(const Polynomial& rhs){
        if (this == &rhs) {
            return *this;
        }
        Node* currNode = headptr;
        while (currNode != nullptr) {
            Node* next = currNode->next;
            delete currNode;
            currNode = next;
        }
        currNode = rhs.headptr;
        headptr = new Node(currNode->data, nullptr);
        degree = rhs.degree;
        currNode = currNode->next;
        Node* nodeTrack = headptr;
        while (currNode != nullptr) {
            Node* newNode = new Node(currNode->data, nullptr);
            nodeTrack->next = newNode;
            nodeTrack = nodeTrack->next;
            currNode = currNode->next;
        }
        return *this;
    }
    //+= operator for Polynomial
    Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
        int lhsDegree = degree;
        int rhsDegree = rhs.degree;
        Node* lhsNode = headptr;
        Node* rhsNode = rhs.headptr;
        while (lhsDegree > rhsDegree) {
            lhsNode = lhsNode->next;
            lhsDegree -= 1;
        }
        if (rhsDegree > lhsDegree) {
            Node *currNode = rhs.headptr;
            headptr = new Node(currNode->data, nullptr);
            Node* nodeTrack = headptr;
            currNode = currNode->next;
            rhsDegree -= 1;
            while (rhsDegree > lhsDegree) {
                Node *newNode = new Node(currNode->data, nullptr);
                nodeTrack->next = newNode;
                nodeTrack = nodeTrack->next;
                currNode = currNode->next;
                rhsDegree -= 1;
            }
            nodeTrack->next = lhsNode;
            degree = rhs.degree;
            rhsNode = currNode;
        }
        while (lhsNode != nullptr) {
            if (lhsDegree == rhsDegree) {
                lhsNode->data += rhsNode->data;
                lhsNode = lhsNode->next;
                rhsNode = rhsNode->next;
                lhsDegree -= 1;
                rhsDegree -= 1;
            }
        }
        Node* currNode = headptr;
        while (currNode->data == 0 && currNode != nullptr) {
            Node* next = currNode->next;
            delete currNode;
            currNode = next;
            degree -= 1;
        }
        headptr = currNode;
        return *this;
    }
    //+ operator for Polynomial
    Polynomial Polynomial::operator+(const Polynomial& rhs) {
        Polynomial res = *this;
        return res += rhs;
    }
    //== operator for Polynomial
    bool Polynomial::operator==(const Polynomial& rhs) const {
        if (degree == rhs.degree) {
            Node* lhsNode = headptr;
            Node* rhsNode = rhs.headptr;
            while (lhsNode != nullptr) {
                if (lhsNode->data != rhsNode->data) {
                    return false;
                }
                lhsNode = lhsNode->next;
                rhsNode = rhsNode->next;
            }
            return true;
        }
        return false;
    }
    //!= operator for Polynomial
    bool Polynomial::operator!=(const Polynomial& rhs) const {
        return !(*this == rhs);
    }
    //evaluates Polynomial using given number
    int Polynomial::evaluate(const int number) const {
        int res = 0;
        Node* currNode = headptr;
        int currDegree = degree;
        while (currNode != nullptr) {
            if (currNode->data == 0) {
                currNode = currNode->next;
                currDegree -= 1;
            }
            else {
                if (currDegree == 0) {
                    return res += currNode->data;
                }
                else if (currDegree == 1) {
                    res += currNode->data * number;
                }
                else {
                    int start = 1;
                    int pos = 1;
                    while (pos <= currDegree) {
                        start *= number;
                        pos += 1;
                    }
                    res += currNode->data * start;
                }
                currNode = currNode->next;
                currDegree -= 1;
            }
        }
        return res;
    }


