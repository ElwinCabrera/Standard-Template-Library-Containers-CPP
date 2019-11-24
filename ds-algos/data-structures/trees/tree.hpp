#ifndef TREE_HPP
#define TREE_HPP
#include "../global.hpp"

class TreeNode{
public:
    int value;

    TreeNode *left;
    TreeNode *right;
    TreeNode() {}
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class Tree {

private:
    TreeNode *root;
public:
    Tree();
    ~Tree();
    Tree(vector<int> preorder, vector<int> inorder);
    
    TreeNode *buildTree(vector<int> preorder, vector<int> inorder);

    void remove(int val);

    TreeNode* getRoot(){return root;}

    vector<int> getPreOrder();
    vector<int> getInOrder();
    vector<int> getPostOrder();

    void printPostOrder();
    void printInOrder();
    void printPreOrder();
};

class BinaryTree {

private:
    TreeNode *root ;
    TreeNode *rootPtr;

    TreeNode* buildTreeHelper(vector<int> preorder, vector<int> inorder, int leftBound, int rightBound, int nextRootIdx);
    int findIdx(vector<int> inorder, int num);

    void getPreOrderHelper(TreeNode *tn, vector<int> &v);
    void getInOrderHelper(TreeNode *tn, vector<int> &v);
    void getPostOrderHelper(TreeNode *tn, vector<int> &v);
public:
    
    BinaryTree();
    ~BinaryTree();
    void deleteTree(TreeNode *tn);
    BinaryTree(vector<int> preorder, vector<int> inorder);

    TreeNode *buildTree(vector<int> preorder, vector<int> inorder);

    TreeNode* insert(TreeNode *tn, int num);

    void remove(TreeNode *tn, int val);
    void remove(TreeNode *deleteNode);
    void removeBiggerThan(int val);
    void removeSmallerThan(int val);

    TreeNode* getRoot() {return root;}
    TreeNode* getMin(TreeNode *tn);

    vector<int> getPreOrder();
    vector<int> getInOrder();
    vector<int> getPostOrder();

    void printPostOrder(TreeNode *tn);
    void printInOrder(TreeNode *tn);
    void printPreOrder(TreeNode *tn);

};


void printTree(TreeNode* root);  
void populateArray(TreeNode *root, vector<vector<string>> &result, int level, int start, int end);
int getHeight(TreeNode *root);


#endif  //BT_HPP