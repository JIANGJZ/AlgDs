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
    
    void init() {
        m_header = new ListNode(-1);
        m_tailer = new ListNode(-1);
        m_header->m_next = m_tailer;
        m_tailer->m_next = nullptr;
    }
    
    void insert(int e) {
        ListNode* node = new ListNode(e);
        if (m_header->m_next == m_tailer) {
            m_header->m_next = node;
            node->m_next = m_tailer;
            m_last = node;
        } else {
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
    void reverseList(List* L1) {
        ListNode* swap = L1->m_header->m_next->m_next;
        ListNode* swap_prev = L1->m_header->m_next;
        ListNode* swap_next = swap->m_next;
        
        while (swap != L1->m_tailer) {
            
            swap->m_next = L1->m_header->m_next;
            L1->m_header->m_next = swap;
            swap_prev->m_next = swap_next;
            
            swap = swap_next;
            swap_next = swap->m_next;
            
        }
    }
};

/*
int main()
{
    List L;
    L.insert(1);
    L.insert(2);
    L.insert(3);
    L.insert(4);
    
    Solution s;
    s.reverseList(&L);
    
    ListNode* node = L.m_header->m_next;
    while (node != L.m_tailer) {
        cout << node->m_value << endl;
        node = node->m_next;
    }
}
*/