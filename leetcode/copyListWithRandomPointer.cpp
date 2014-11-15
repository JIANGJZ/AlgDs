#include <iostream>

#include <iostream>

class ListNode
{
public:
    ListNode(int value) : m_value(value) {
        
    }
    int m_value;
    ListNode* m_next;
    ListNode* m_rand;
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
    
    void setRandom() {
        ListNode* node = m_header->m_next;
        while (node != m_tailer) {
            node->m_rand = node->m_next->m_next;
            node = node->m_next;
        }
    }
    ListNode* m_last;
    ListNode* m_header;
    ListNode* m_tailer;
};

class Solution
{
public:
    void copyRand(List* l1, List* l2) {
        ListNode* head_node = l1->m_header->m_next;
        while (head_node != l1->m_tailer) {
            ListNode* rand_node = new ListNode(head_node->m_value);
            rand_node->m_next = head_node->m_next;
            head_node->m_next = rand_node;
            head_node = rand_node->m_next;
        }
        
        
        head_node = l1->m_header->m_next;
        while (head_node != l1->m_tailer && head_node->m_next != l1->m_tailer && head_node->m_rand != NULL) {
            head_node->m_next->m_rand = head_node->m_rand->m_next;
            head_node = head_node->m_next->m_next;
        }
        
        head_node = l1->m_header->m_next;
        ListNode* rand_node = l1->m_header->m_next->m_next;
        l2->m_header->m_next = rand_node;
        while (head_node != l1->m_tailer && rand_node != l1->m_tailer) {
            head_node->m_next = rand_node->m_next;
            head_node = head_node->m_next;
            rand_node->m_next = head_node->m_next;
            rand_node = rand_node->m_next;
        }
        
    }
};

/*
int main()
{
    List* l1 = new List();
    l1->insertBack(1);
    l1->insertBack(2);
    l1->insertBack(3);
    l1->insertBack(4);
    l1->insertBack(5);
    l1->insertBack(6);
    l1->insertBack(7);
    
    l1->setRandom();
    
    Solution s;
    List* l2 = new List();
    s.copyRand(l1, l2);
}
*/