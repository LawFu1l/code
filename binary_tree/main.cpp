#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct Node
{
    Node(const int& no)
        : _no(no)
    {
        left = right = nullptr;
    }

    int _no;
    Node* left;
    Node* right;
};

class Binary_tree
{
public:
    Binary_tree(Node* in)
    {
        _root = in;
    }

    template <typename Visitor>
    auto visit(Visitor& visitor, int options) -> void
    {
        if (options == 0) preorder(_root, visitor);
        if (options == 1) inorder(_root, visitor);
        if (options == 2) postorder(_root, visitor);
    }

private:
    template <typename Visitor>
    void preorder(const Node* in, Visitor& visitor)
    {
        if (in == nullptr) return;

        visitor(in);
        preorder(in->left,  visitor);
        preorder(in->right, visitor);
    }

    template <typename Visitor>
    void inorder(const Node* in, Visitor& visitor)
    {
        if (in == nullptr) return;

        inorder(in->left,  visitor);
        visitor(in);
        inorder(in->right, visitor);
    }

    template <typename Visitor>
    void postorder(const Node* in, Visitor& visitor)
    {
        if (in == nullptr) return;

        postorder(in->left,  visitor);
        postorder(in->right, visitor);
        visitor(in);
    }

    // 노드 삽입 함수

private:
    Node* _root;
};

int main()
{
    Node* n = new Node(0);     // _root == 0
    n->left = new Node(1);     // 1
    n->right = new Node(2);    // 2 
                               //
    Node* one = n->left;
    one->left = new Node(3);   // 3
    one->right = new Node(4);  // 4

    Node* two = n->right;
    two->left = new Node(5);    // 5
    two->right = new Node(6);   // 6

    Binary_tree bt(n);

    int sum = 0;
    auto summer = [&sum](const auto node) { sum += node->_no; };
    
    bt.visit(summer, 0);

    cout << sum << endl;

    // 1. lambda
    // 2. tree traversal
    // 3. template programming

    vector<int> v = { 10, 1, 2, 3, 4, 5 };
    list<int> l = { 10, 1, 2, 3, 4, 5 };

    sort(l.begin(), l.end(), [](const int& a, const int& b) { return a < b; });

    return 0;
}