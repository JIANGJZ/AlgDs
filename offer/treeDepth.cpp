struct BinaryTreeNode
{
    int m_value;
    BinaryTreeNode* m_leftChild;
    BinaryTreeNode* m_rightChild;
};

int treeDepth(BinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return 0;
    }
    int left_depth = treeDepth(pRoot->m_leftChild);
    int right_depth = treeDepth(pRoot->m_rightChild);
    
    return left_depth > right_depth ? left_depth + 1 : right_depth + 1;
}

bool isBalanced(BinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return true;
    }
    
    int left = treeDepth(pRoot->m_leftChild);
    int right = treeDepth(pRoot->m_rightChild);
    
    int diff = left - right;
    if (diff > 1 || diff < -1) {
        return false;
    }
    
    return isBalanced(pRoot->m_leftChild) && isBalanced(pRoot->m_rightChild);
}

bool isBalanced2(BinaryTreeNode* pRoot, int* pDepth) {
    if (pRoot == nullptr) {
        *pDepth = 0;
        return true;
    }
    
    int left, right;
    if (isBalanced2(pRoot->m_leftChild, &left) && isBalanced2(pRoot->m_rightChild, &right)) {
        int diff = left - right;
        if (diff <= 1 && diff >= -1) {
            *pDepth = 1 + (left > right ? left : right);
            return true;
        }
    }
    
    return false;
}