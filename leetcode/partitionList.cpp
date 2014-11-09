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

class Solution
{
public:
    void partitionList(List* ori_list, int x, List* result_list) {
        List *list_less = new List();
        List *list_greater = new List();
        ListNode* cur_node = ori_list->m_header->m_next;
        
        while (cur_node != ori_list->m_tailer) {
            if (cur_node->m_value < x) {
                list_less->insertBack(cur_node->m_value);
            }
            else{
                list_greater->insertBack(cur_node->m_value);
            }
            cur_node = cur_node->m_next;
        }
        
        cur_node = list_less->m_header->m_next;
        while (cur_node != list_less->m_tailer) {
            result_list->insertBack(cur_node->m_value);
            cur_node = cur_node->m_next;
        }
        
        cur_node = list_greater->m_header->m_next;
        while (cur_node != list_greater->m_tailer) {
            result_list->insertBack(cur_node->m_value);
            cur_node = cur_node->m_next;
        }
        
        delete list_greater;
        delete list_less;
    }
};

int main()
{
    List* ori_list = new List();
    ori_list->insertBack(1);
    ori_list->insertBack(4);
    ori_list->insertBack(3);
    ori_list->insertBack(2);
    ori_list->insertBack(5);
    ori_list->insertBack(2);
    
    Solution s;
    List* result_list = new List();
    s.partitionList(ori_list, 3, result_list);
    return 0;
}