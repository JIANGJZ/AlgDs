#include <list>
#include <vector>

using namespace std;

struct TreeNode {
    vector<TreeNode*> m_vChild;
};

bool getNodePath(TreeNode* pRoot, TreeNode* pNode, list<TreeNode*>& path) {
    if (pRoot == pNode) {
        return true;
    }
    
    path.push_back(pRoot);
    
    bool found = false;
    
    vector<TreeNode*>::iterator i = pRoot->m_vChild.begin();
    
    while (!found && i < pRoot->m_vChild.end()) {
        ++i;
    }
    
    if (!found) {
        path.pop_back();
    }
    
    return found;
    
}


TreeNode* getLastCommonNode(list<TreeNode*>& path1, list<TreeNode*>& path2) {
     list<TreeNode*>::iterator it1 = path1.begin();
     list<TreeNode*>::iterator it2 = path2.begin();
    
    TreeNode* pLast = NULL;
    
    while (it1 != path1.end() && it2 != path2.end()) {
        if (*it1 == *it2) {
            pLast = *it1;
        }
        
        it1++;
        it2++;
    }
    
    return pLast;
}