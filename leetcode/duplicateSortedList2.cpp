#include <list>
#include <iostream>

using namespace std;

class SolutionSTL
{
public:
    void duplicate(list<int>& l) {
        list<int>::iterator it_pre = l.begin();
        list<int>::iterator it_cur = next(it_pre);
        list<int>::iterator old;
        while (it_cur != l.end()) {
            bool flag = false;
            while (*it_pre == *it_cur) {
                flag = true;
                old = it_cur;
                it_cur = next(it_cur);
                l.erase(old);
            }
            
            old = it_pre;
            it_pre = next(it_pre);
            it_cur = next(it_cur);
            
            if (flag == true) {
                l.erase(old);
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

class Solution_iter
{
public:
    void duplicate(List* l) {
        ListNode* l_pre = l->m_header;
        ListNode* l_cur = l_pre->m_next;
        ListNode* l_next = l_cur->m_next;
        ListNode* old = nullptr;
        while (l_next != l->m_tailer && l_cur != l->m_tailer) {
            bool flag = false;
            while (l_cur->m_value == l_next->m_value) {
                old = l_next;
                l_next = l_next->m_next;
                l_cur->m_next = l_next;
                delete old;
                flag = true;
            }
            
            old = l_cur;
            l_cur = l_cur->m_next;
            l_next = l_next->m_next;
            if (flag == true) {
                delete old;
                l_pre->m_next = l_cur;
            }
            else{
                l_pre = old;
            }
            
        }
        
    }
};

/*
int main()
{
    SolutionSTL s;
    list<int> l = {1, 2, 3, 3, 3, 4, 4, 5};
    s.duplicate(l);
    
    copy(l.begin(), l.end(), ostream_iterator<int>(cerr, " "));
    
    List* l2 = new List();
    l2->insertBack(1);
    l2->insertBack(2);
    l2->insertBack(3);
    l2->insertBack(3);
    l2->insertBack(3);
    l2->insertBack(4);
    l2->insertBack(4);
    l2->insertBack(5);
    l2->insertBack(5);
    l2->insertBack(6);
    l2->insertBack(6);
    
    Solution_iter s2;
    s2.duplicate(l2);
    
    return 0;
    
}
*/
