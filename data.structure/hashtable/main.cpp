#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 *  올려야하는 식별자의 수, 버킷에 올라간 식별자의 수, 총 버킷의 수, 입력 데이터 타입, 식별자 밀집도
 */

struct Node
{
    Node(const string& name)
        : _name{name}, _next{nullptr}
    {}

    Node() = default;

    string _name;
    Node* _next;
};

enum class Option {All, Table, Metadata};

class Hashtable
{
public:
    Hashtable(const int& bucket_size)
        : _bucket_size(bucket_size)
    {
        _bucket.resize(_bucket_size);
    }

    ~Hashtable()
    {
    }

    void insert(vector<string>& input)
    {
        for (auto& s : input)
            insert(s);
    }

    void remove2(const string& name)
    {
        int position = djb2(name);
        auto to_remove = _bucket[position];
        while (to_remove->_next != nullptr)
        {
            if (to_remove->_name == name)
            {
                auto tmp = to_remove->_next;
                delete to_remove;
                _bucket[position] = tmp;
                return;
            }

            to_remove = to_remove->_next;
        }
    }

    void remove(const string& name)
    {
        int position = djb2(name);
        auto to_remove = _bucket[position];

        // TODO 이 if가 왜 필요하지?
        if (to_remove->_name == name)
        {
            auto tmp = to_remove->_next;
            delete to_remove;
            _bucket[position] = tmp;
        }
        else
        {
            auto tmp = _bucket[position];
            while (tmp->_next->_name != name)
            {
                tmp = tmp->_next;
            }

            if (tmp->_next == nullptr)
            {
                delete tmp;
            }
            else
            {
                auto cur = tmp;
                tmp = tmp->_next->_next;
                delete cur->_next;
                cur->_next = tmp;
            }
        }
    }

    //해시 테이블의 상태값을 보여주고, 해시 테이블 전체를 보여준다.
    void view_status(Option option)
    {
        switch (option)
        {
            case Option::All:
                cout << "---------------------------------" << endl;
                cout << "VIEW MODE : ALL" << endl;
                view_all();
                break;

            case Option::Table:
                cout << "---------------------------------" << endl;
                cout << "VIEW MODE : TABLE" << endl;
                view_table();
                break;

            case Option::Metadata:
                cout << "VIEW MODE : Metadata" << endl;
                view_metadata();
                break;

            default:
                cout << "Undefined option for view_status() " << endl;
                break;
        }
    }


// private function
private:

    void viewmode_util(string& mode)
    {
        cout << "---------------------------------" << endl;
        printf("VIEW MODE : %s", mode);
    }

    void view_all()
    {
        view_metadata();
        view_table();
    }

    void view_table()
    {

        for (int i = 0; i < _bucket_size; i++)
        {
            if (_bucket[i] == nullptr) 
            {
                cout << "empty";
            }
            else
            {
                cout << _bucket[i]->_name << " ";
                auto tmp = _bucket[i];

                while (tmp->_next != nullptr)
                {
                    cout << tmp->_next->_name << " ";
                    tmp = tmp->_next;
                }
            }
            cout << endl;
        }
    }

    void view_metadata()
    {
        cout << "---------------------------------" << endl;
    }

    void insert(const string& name)
    {
        int position = djb2(name);
        auto tmp = new Node(name);

        if (_bucket[position] == nullptr) // 버킷이 비어있는 경우
        {
            _bucket[position] = tmp;
        }
        else //버킷이 이미 노드를 가진 경우
        {
            auto cur = _bucket[position];
            while (cur->_next != nullptr)
                cur = cur->_next;

            cur->_next = tmp;
        }
    }

    // 이 해시 테이블에서 사용할 해시 함수
    unsigned int djb2(const string key)
    {
        unsigned long hash = 5381;
        for (char c : key)
            hash = ((hash << 5) + hash) + c;  // hash * 33 + c

        return hash % _bucket_size;
    }

private:
    vector<Node*> _bucket;
    int _bucket_size;
};

int main()
{
    Hashtable table(5);
    vector<string> month{"jan", "feb", "mar", "apr", "may", "jun","jul", "aug", "sep", "oct", "nov", "dec"};
    table.insert(month);
    table.view_status(Option::Table);
    table.remove2("jan");

    return 0;
}