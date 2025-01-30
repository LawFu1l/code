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
    }

    // true-> 기존노드가 더 큰 값
    bool compare(int val) const { return _val > val; }
    bool left_ok()        const { return left != nullptr;  }
    bool right_ok()       const { return right != nullptr; }

    int _val;
    Node* left;
    Node* right;
};

class BST
{
public:
    BST(int root)
    {
        _root = new Node(root);
    }

    // push, pop등 트리 구조에 변화를 주는 함수의 호출마다
    // private 멤버 데이터를 갱신 할 수 있도록 한다.
    // void status(const Node* in)
    // {
    //     if (t_level < in->level) 
    //         t_level = in->level;
    // }
    void visit(const Node* in)
    {
        if (in != nullptr)
            cout << in->_val << endl;
    }

    void preorder_traverse()
    {
        preorder(_root);
    }

    void add(int val)
    {
        // 루트 노드가 없을 경우
        if (_root == nullptr)
        {
            _root = new Node(val);
            return;
        }

        auto curr = _root;
        while (true)
        {
            if (curr->compare(val) && curr->left_ok()) 
                curr = curr->left;

            if (curr->compare(val) && !curr->left_ok())
            {
                curr->left = new Node(val);
                break;
            }

            if (!curr->compare(val) && curr->right_ok())
                curr = curr->right;

            if (!curr->compare(val) && !curr->right_ok())
            {
                curr->right = new Node(val);
                break;
            }
        }
    }

    void add_range(vector<int> arr)
    {
        for (int i : arr)
            add(i);
    }

private:
    void preorder(const Node* in)
    {
        if (in != nullptr)
        {
            visit(in);
            preorder(in->left);
            preorder(in->right);
        }
    }

private:
    Node* _root{nullptr};
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

    vector<int> values{1, 3, 2, 4, 6, 7, 8, 9};
    BST tree(5);
    tree.add_range(values);
    tree.preorder_traverse();

    return 0;
}
