#include <iostream>

using namespace std;

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


class Solution1
{
public:
    ListNode* detectCycle(List* l) {
        
        ListNode* fast = l->m_header;
        ListNode* slow = l->m_header;
        
        while (fast != l->m_tailer) {
            
            fast = fast->m_next->m_next;
            slow = slow->m_next;
            
            if (fast == slow) {
                ListNode* slow2 = l->m_header;
                while (slow2 != slow) {
                    slow = slow->m_next;
                    slow2 = slow2->m_next;
                }
                return slow2;
            }
            
        }

        return NULL;
    }
};


/*
int main()
{
    List* l = new List();
    
    l->insertBack(1);
    l->insertBack(2);
    l->insertBack(3);
    l->insertBack(4);
    l->insertBack(5);
    l->insertBack(6);
    l->insertBack(7);
    l->insertBack(8);
    l->insertBack(9);
    l->insertBack(10);
    
    l->m_last->m_next = l->m_header->m_next->m_next->m_next->m_next->m_next->m_next;
    
    Solution1 s;
    cout << s.detectCycle(l)->m_value;
    
    
    return true;
}
 */
