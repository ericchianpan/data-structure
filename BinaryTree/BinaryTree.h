#ifndef BinaryTree_H 
#define BinaryTree_H

template<class T>
class BinaryTree;

template<class T>
class TreeNode{
public:
    TreeNode() {}
    ~TreeNode(){}
    void setData(T data) { _data = data; }
    void setLeft(TreeNode* node) { _left = node; }
    void setRight(TreeNode* node) { _right = node; }
    T Data() { return this->_data; }
    TreeNode* left() { return this->_left; }
    TreeNode* right() { return this->_right; }
    template<class U> 
    friend class BinaryTree;
private:
    TreeNode* _left = NULL;
    TreeNode* _right = NULL;
    T _data;
};

template<class T>
class BinaryTree{
public:
    BinaryTree() {}
    ~BinaryTree() { free(_root); }
    TreeNode<T>* root() { return _root; }
    void inorder(TreeNode<T>* node);
    void preorder(TreeNode<T>* node);
    void postorder(TreeNode<T>* node);
private:
    TreeNode<T>* _root = new TreeNode<T>; 
    void free(TreeNode<T>* node)
    {
        if(node == NULL) return;
        free(node->_left);
        free(node->_right);
        delete node;
    }
};

template<class T>
void BinaryTree<T>::inorder(TreeNode<T>* node)
{
    if(node == NULL) return;
    inorder(node->_left);
    std::cout << node->_data << " ";
    inorder(node->_right);
}
template<class T>
void BinaryTree<T>::preorder(TreeNode<T>* node)
{
    if(node == NULL) return;
    std::cout << node->_data << " ";
    inorder(node->_left);
    inorder(node->_right);
}
template<class T>
void BinaryTree<T>::postorder(TreeNode<T>* node)
{
    if(node == NULL) return;
    postorder(node->_left);
    postorder(node->_right);
    std::cout << node->_data << " ";
}

#endif
