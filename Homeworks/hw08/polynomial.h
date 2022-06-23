//
// Jiezhi Winston Zuo-yu
// polynomial.h
//

#ifndef HW08_POLYNOMIAL_H
#define HW08_POLYNOMIAL_H
#include<iostream>
#include<vector>
struct Node{
    Node (int data, Node* next = nullptr);
    int data;
    Node* next;
};

class Polynomial{
public:
    friend std::ostream& operator<<(std::ostream& os,const Polynomial& polynomial);
    Polynomial (const std::vector<int>& coefficients);
    Polynomial ();
    Node* createLL(const std::vector<int>& coefficients);
    Node* addNode(Node* node, Node* nodetoadd);
    ~Polynomial();
    Polynomial(const Polynomial& rhs);
    Polynomial& operator=(const Polynomial& rhs);
    Polynomial& operator+=(const Polynomial& rhs);
    Polynomial operator+(const Polynomial& rhs);
    bool operator==(const Polynomial& rhs) const;
    bool operator!=(const Polynomial& rhs) const;
    int evaluate(const int number) const;
private:
    Node* headptr;
    int degree;
};
#endif //HW08_POLYNOMIAL_H
