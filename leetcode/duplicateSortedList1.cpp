#include <list>
#include <iostream>
#include <cassert>

using namespace std;

class Solution_STL
{
public:
    void duplicate(list<int>& l) {
        list<int>::iterator it = l.begin();
        list<int>::iterator it_next = next(it);
        while(it_next != l.end()) {
            if (*it != *it_next) {
                it = it_next;
                it_next = next(it_next);
            } else {
                list<int>::iterator temp = it_next;
                it_next = next(it_next);
                l.erase(temp);
            }
        }
    }
};

class ListNode
{
public:
    ListNode(int value) : m_value(value) {
        
    }
    int m_value;
    ListNode* m_next;
};

class List
{
public:
    List() {
        init();
    }
    
    ~List() {
        destroy();
    }
    
    void destroy() {
        ListNode* cur_node = m_header;
        while (cur_node->m_next != m_tailer) {
            cur_node = m_header->m_next;
            m_header->m_next = cur_node->m_next;
            delete cur_node;
        }
        delete m_header;
        delete m_tailer;
    }
    
    void init() {
        m_header = new ListNode(-1);
        m_tailer = new ListNode(-1);
        m_header->m_next = m_tailer;
        m_tailer->m_next = nullptr;
    }
    
    void insertBack(int e) {
        ListNode* node = new ListNode(e);
        if (m_header->m_next == m_tailer) {
            m_header->m_next = node;
            node->m_next = m_tailer;
            m_last = node;
        }
        else {
            m_last->m_next = node;
            node->m_next = m_tailer;
            m_last = node;
        }
    }
    ListNode* m_last;
    ListNode* m_header;
    ListNode* m_tailer;
};

class Solution_Iter
{
public:
    void duplicate(List* l) {
        assert(l != nullptr);
        ListNode* head = l->m_header;
        ListNode* head_next = head->m_next;
        
        while (head_next != l->m_tailer) {
            if (head->m_value != head_next->m_value) {
                head = head_next;
                head_next = head_next->m_next;
            }else{
                head->m_next = head_next->m_next;
                delete head_next;
                head_next = head->m_next;
            }
        }
        
    }
    
};


class Solution_rec
{
public:
    void duplicate(List* l) {
        ListNode* head = l->m_header;
        ListNode* head_next = head->m_next;
        _duplicate(head, head_next, l);
    }
private:
    void _duplicate(ListNode* head, ListNode* head_next, List* l) {
        if (head_next == l->m_tailer) {
            return;
        }
        
        if (head->m_value != head_next->m_value) {
            _duplicate(head->m_next, head_next->m_next, l);
        }
        else {
            head->m_next = head_next->m_next;
            delete head_next;
            _duplicate(head, head_next->m_next, l);
        }
        
    }
};

/*
int main()
{
    list<int> l;
    l.push_back(1);
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(2);
    l.push_back(4);
    l.push_back(6);
    l.sort();
    
    Solution_STL s;
    s.duplicate(l);
    
    ostream_iterator<int> out(cout, " ");
    copy(l.begin(), l.end(), out);
    
    
    List* l2 = new List();
    l2->insertBack(1);
    l2->insertBack(1);
    l2->insertBack(2);
    l2->insertBack(2);
    l2->insertBack(3);
    
    Solution_Iter s2;
    s2.duplicate(l2);
    
    
    List* l3 = new List();
    l3->insertBack(1);
    l3->insertBack(2);
    l3->insertBack(2);
    l3->insertBack(2);
    l3->insertBack(3);
    l3->insertBack(3);
    
    Solution_rec s3;
    s3.duplicate(l3);
    
    return 0;
}
*/