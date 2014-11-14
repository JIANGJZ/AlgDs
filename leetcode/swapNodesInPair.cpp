#include <iostream>

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


class Solution
{
public:
    void swapNodeInPair(List* l) {
        ListNode* node1 = l->m_header;
        ListNode* node2 = node1->m_next;
        ListNode* node3 = node2->m_next;
        ListNode* node4 = node3->m_next;
        
        while (node3 != l->m_tailer && node2 != l->m_tailer) {
            //swap
            node1->m_next = node3;
            node3->m_next = node2;
            node2->m_next = node4;
            
            //iter
            node1 = node1->m_next->m_next;
            ListNode* swap = node3;
            node3 = node2->m_next->m_next;
            node2 = swap->m_next->m_next;
            if (node4 == NULL || node4->m_next == NULL) {
                continue;
            }
            node4 = node4->m_next->m_next;
        }
    }
};

/*
int main()
{
    List* l = new List;
    l->insertBack(1);
    l->insertBack(2);
    l->insertBack(3);
    l->insertBack(4);
    l->insertBack(5);
    l->insertBack(6);
    l->insertBack(7);
    l->insertBack(8);
    Solution s;
    s.swapNodeInPair(l);
}
*/