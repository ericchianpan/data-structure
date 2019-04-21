#ifndef BinarySearchTree_H 
#define BinarySearchTree_H

template<class T>
class BinarySearchTree;

template<class T>
class TreeNode{
public:
    TreeNode():_left(NULL), _right(NULL), _parent(NULL) {}
    TreeNode(T data):_left(NULL), _right(NULL), _parent(NULL), _data(data) {}
    ~TreeNode(){}
    void setData(T data) { _data = data; }
    void setLeft(TreeNode* node) { _left = node; }
    void setRight(TreeNode* node) { _right = node; }
    void setParent(TreeNode* node) { _parent = node; }
    T Data() { return this->_data; }
    TreeNode* left() { return this->_left; }
    TreeNode* right() { return this->_right; }
    TreeNode* parent() { return this->_parent; }
    template<class U> 
    friend class BinarySearchTree;
private:
    TreeNode* _left;
    TreeNode* _right;
    TreeNode* _parent;
    T _data;
};

template<class T>
class BinarySearchTree{
public:
    BinarySearchTree():_root(NULL) {}
    ~BinarySearchTree() { free(_root); }
    TreeNode<T>* root() { return _root; }
    TreeNode<T>* search(T data);
    TreeNode<T>* leftmost(TreeNode<T>* node);
    TreeNode<T>* successor(TreeNode<T>* node);
    TreeNode<T>* rightmost(TreeNode<T>* node);
    void insert(T data);
    void remove(T data);
    void inorder(TreeNode<T>* node);
    void printInorder() { inorder(_root); }
private:
    TreeNode<T>* _root; 
    void free(TreeNode<T>* node);
};

template<class T>
void BinarySearchTree<T>::free(TreeNode<T>* node)
{
    if(node == NULL) return;
    free(node->_left);
    free(node->_right);
    delete node;
}
template<class T>
void BinarySearchTree<T>::insert(T data)
{
    TreeNode<T>* newNode = new TreeNode<T>(data);
    TreeNode<T>* parent = NULL;
    TreeNode<T>* ptr = NULL;
    ptr = _root;
    while(ptr != NULL)
    {
        parent = ptr;
        if(newNode->_data < ptr->_data) { ptr = ptr->_left; }
        else { ptr = ptr->_right; }
    }
    newNode->_parent = parent;
    if(parent == NULL) { _root = newNode; }
    else if(newNode->_data < parent->_data) { parent->_left = newNode; }
    else { parent->_right = newNode; }
}
template<class T>
void BinarySearchTree<T>::remove(T data)
{
    TreeNode<T>* node = search(data);
    if(node == NULL)
    {
        std::cout << "data " << data << " is not found" << std::endl;
        return;
    }
    TreeNode<T>* x = NULL;
    TreeNode<T>* y = NULL;
    if(node->_left == NULL || node->_right == NULL) { y = node; }
    else { y = successor(node); }
    if(y->_left != NULL) { x = y->_left; }
    else { x = y->_right; }
    if(x != NULL) { x->_parent = y->_parent; }
    if(y->_parent == NULL) { this->_root = x; }
    else if(y == y->_parent->_left) { y->_parent->_left = x; }
    else { y->_parent->_right = x; }
    if(y != node) { node->_data = y->_data; }
    delete y;
    y = NULL;
}
template<class T>
TreeNode<T>* BinarySearchTree<T>::search(T data)
{
    TreeNode<T>* ptr = _root;
    while(ptr != NULL && ptr->_data != data)
    {
        if(data < ptr->_data) { ptr = ptr->_left; }
        else { ptr = ptr->_right; }
    }
    return ptr;
}
template<class T>
TreeNode<T>* BinarySearchTree<T>::leftmost(TreeNode<T>* node)
{
    while(node->_left != NULL)
    {
        node = node->_left;
    }
    return node;
}
template<class T>
TreeNode<T>* BinarySearchTree<T>::successor(TreeNode<T>* node)
{
    if(node->_right != NULL)
        return leftmost(node->_right);
    TreeNode<T>* successor = node->_parent;
    while(successor != NULL && node == successor->_right)
    {
        node = successor;
        successor = successor->_parent;
    }
    return successor;
}
template<class T>
void BinarySearchTree<T>::inorder(TreeNode<T>* node)
{
    if(node == NULL) return;
    inorder(node->_left);
    std::cout << node->_data << std::endl;
    inorder(node->_right);
}

#endif
