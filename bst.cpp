#include <iostream>
#include <vector>

/*
 *  Binary Search Tree의 구현
 *  기준 노드에 대해 작은 값은 왼쪽, 큰 값은 오른쪽에 배치한다.
 */

using namespace std;

struct Node
{
    Node(const int& val)
        : _val(val)
    {
        left = right = nullptr;
        level = 0;
    }

    int _val, level;
    Node* left;
    Node* right;
};

class BST
{
public:
    BST(Node* in)
    {
        _root = in;
        current = _root;
        _root->level = 1;
    }

    // push, pop등 트리 구조에 변화를 주는 함수의 호출마다
    // private 멤버 데이터를 갱신 할 수 있도록 한다.
    void status(const Node* in)
    {
        if (t_level < in->level) t_level = in->level;
    }

    void visit(const Node* in)
    {
        if (in != nullptr)
            cout << in->_val << endl;
    }

    void preorder(const Node* in)
    {
        if (in != nullptr)
        {
            visit(in);
            status(in);
            preorder(in->left);
            preorder(in->right);
        }

    }

    // 기존 노드가 더 크면 true를 반환한다.
    bool compare(int val) { return this->current->_val > val;}

    void push(int val)
    {
        // 루트 노드가 없을 경우
        if (_root == nullptr)
        {
            _root = new Node(val);
            current = _root;
            _root->level = 1;
            return;
        }

        //있을 경우
        while (true)
        {
            if (compare(val) == true && current->left != nullptr) // true-> 기존노드가 더 큰 값
            {
                current = current->left;
            }
            if (compare(val) == true && current->left == nullptr)
            {
                current->left = new Node(val);
                current->left->level = current->level + 1;
                current = _root;
                break;
            }
            if (compare(val) == false && current->right != nullptr)
            {
                current = current->right;
            }
            if (compare(val) == false && current->right == nullptr)
            {
                current->right = new Node(val);
                current->right->level = current->level + 1;
                current = _root;
                break;
            }
        }
    }

    void push_list(vector<int> arr)
    {
        for (int i : arr)
        {
            push(i);
        }
    }

private:
    int t_level;
    Node* _root{nullptr};
    Node* current{nullptr};
};

int main()
{
    /*
     *              5
     *           1      6
     *            3       7
     *                      8
     *                         9
     *
     */


    auto tmp = new Node(5);
    BST tree(tmp);

    vector<int> array = {1,3,2,4,6,7,8,9};
    tree.push_list(array);

    tree.preorder(tmp);
    return 0;
}