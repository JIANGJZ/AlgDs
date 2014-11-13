#include <iostream>
#include <unordered_map>

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


class Solution
{
public:
    bool detectCycle(List* l) {
        ListNode* slow = l->m_header;
        ListNode* fast = l->m_header;
        while (fast->m_next != l->m_tailer && fast != l->m_tailer) {
            slow = slow->m_next;
            fast = fast->m_next->m_next;
            
            if (fast == slow) {
                return true;
            }
        }
        return false;
    }
};

class Solution2
{
public:
    bool detectCycle(List* l) {
        unordered_map<ListNode*, bool> is_visited;

        ListNode* cur = l->m_header->m_next;
        while (cur != l->m_tailer) {
            if (is_visited[cur] == true) {
                return true;
            }
            else {
                is_visited[cur] = true;
            }
            cur = cur->m_next;
        }
        return false;
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
    
    l->m_last->m_next = l->m_header->m_next;
    
    Solution s;
    cout << s.detectCycle(l);
    
    List* l2 = new List();
    l2->insertBack(1);
    l2->insertBack(2);
    l2->insertBack(3);
    l2->insertBack(4);
    l2->insertBack(5);
    
    cout << s.detectCycle(l2);
    
    
    Solution2 s2;
    
    cout << s2.detectCycle(l);
    
    cout << s2.detectCycle(l2);
    
    
    return true;
}
*/