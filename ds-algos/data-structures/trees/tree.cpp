#include "tree.hpp"

BinaryTree::BinaryTree(){
    root = NULL;
}

BinaryTree::BinaryTree(vector<int> preorder, vector<int> inorder){
    root = buildTree(preorder, inorder);
}

BinaryTree::~BinaryTree(){
    printf("destroying tree\n");
    deleteTree(root);
}
void BinaryTree::deleteTree(TreeNode *tn){
    if(!tn) return;
    
    deleteTree(tn->left);
    deleteTree(tn->right);
    delete tn;
}


/* Building tree from preorder and inorder */
TreeNode* BinaryTree::buildTree(vector<int> preorder, vector<int> inorder){
    if(preorder.empty() || inorder.empty()) return NULL;
    //inorder contains the root in the middle of the children
    //preorder has all the roots in
    return buildTreeHelper(preorder, inorder, 0, inorder.size()-1, 0); 
}

TreeNode* BinaryTree::buildTreeHelper(vector<int> preorder, vector<int> inorder, int leftBound, int rightBound, int nextRootIdx){
    if(leftBound > rightBound || nextRootIdx >= preorder.size()) return NULL;

    int rootVal = preorder.at(nextRootIdx);
    TreeNode *tn = new TreeNode(rootVal);


    int rootIdx = findIdx(inorder, rootVal);
    tn->left = buildTreeHelper(preorder, inorder, leftBound, rootIdx-1, nextRootIdx + 1);
    tn->right = buildTreeHelper(preorder, inorder, rootIdx+1, rightBound, nextRootIdx + 2);

    return tn;
}
int BinaryTree::findIdx(vector<int> inorder, int num){
    if(inorder.empty()) return -1;
    for(int i = 0; i < inorder.size(); ++i) if(inorder.at(i) == num) return i;
    return -1;
}


/* Inserting into tree */
TreeNode* BinaryTree::insert(TreeNode *tn, int val){
    
    //recursive way
    if(!tn) {

        if(!root) {
            root = new TreeNode(val);
            return root;
        }

        return new TreeNode(val);
    }
    if(val > tn->value) tn->right =  insert(tn->right,val);
    if(val < tn->value) tn->left =  insert(tn->left, val);

    
    return tn;


    //Iterative way
    /* TreeNode *rootPtr = root;
    TreeNode *newNode = new TreeNode(val);
    while(rootPtr->left && rootPtr->right){
        if(val >= rootPtr->value){
            rootPtr = rootPtr->right;
        } else {
            rootPtr = rootPtr->left;
        }
        
    }

    while(rootPtr->right){
        if(val >= rootPtr->value){
            rootPtr = rootPtr->right;
        } else {
            rootPtr = rootPtr->left;
        }       
    }

    while(rootPtr->left){
        if(val >= rootPtr->value){
            rootPtr = rootPtr->right;
        } else {
            rootPtr = rootPtr->left;
        }       
    }

    if(val >= rootPtr->value) rootPtr->right = newNode;
    else rootPtr->left = newNode;

    return newNode;*/

}


/*removing from list */
void BinaryTree::remove(TreeNode *tn, int val){
    /*
    First we need to find the actual node that we want to delete 
    after we find the node we then condider the following three cases.

    Case 1: leaf Node
        -Then just delete that node

    Case 2: node with a left subtree or right subtree
        -Then just point the current node (delete node)
         to whatever subtree that the current node 
         has 

    Case 3: node with both a left and right subtree
        -Then find the minimum node in right 
         subtree or the maximum in the left 
         subtree and set that to the current node 
         that we are trying to delete then just 
         delete the minimum value that we found 
         in one of those trees. 
    */

   if(!tn) return;
   
   if(val > tn->value){
       remove(tn->right, val);
   } else if(val < tn->value){
       remove(tn->left, val);
   } else {
       TreeNode *trash  = NULL;

       if( tn->left== NULL && tn->right == NULL){
           trash = tn;
       } else if(tn->left == NULL && tn->right != NULL){
           trash = tn;
           tn = tn->right;
       } else if(tn->left != NULL && tn->right == NULL){
           trash = tn;
           tn = tn->left;
       } else {
           TreeNode *min = getMin(tn->right);
           tn->value = min->value;
           remove(min, min->value);
       }
       if(trash) delete trash;
   }
   
}

void BinaryTree::remove(TreeNode *deleteNode){

}

TreeNode* BinaryTree::getMin(TreeNode *tn){
    if(!tn || !tn->left) return tn;
    return getMin(tn->left);
}

/* Tree traversals returning a vector*/
vector<int> BinaryTree::getPreOrder(){
    vector<int> result;
    getPreOrderHelper(root, result);
    return result;
}
void BinaryTree::getPreOrderHelper(TreeNode *tn, vector<int> &v){
    if(!tn) return;

    v.push_back(tn->value);
    printInOrder(tn->left);
    printInOrder(tn->right);
}

vector<int> BinaryTree::getInOrder(){
    vector<int> result;
    getInOrderHelper(root, result);
    return result;
}
void BinaryTree::getInOrderHelper(TreeNode *tn, vector<int> &v){
    if(!tn) return;

    printInOrder(tn->left);
    v.push_back(tn->value);
    printInOrder(tn->right);
}

vector<int> BinaryTree::getPostOrder(){
    vector<int> result;
    getPostOrderHelper(root, result);
    return result;
}
void BinaryTree::getPostOrderHelper(TreeNode *tn, vector<int> &v){
    if(!tn) return;

    printInOrder(tn->left);
    printInOrder(tn->right);
    v.push_back(tn->value);
}




/* Tree traversals printing to stdout */
void BinaryTree::printPreOrder(TreeNode *root){
    if(!root) return;

    printf("%d ", root->value);
    printInOrder(root->left);
    printInOrder(root->right);
}

void BinaryTree::printInOrder(TreeNode *root){
    if(!root) return;

    printInOrder(root->left);
    printf("%d ", root->value);
    printInOrder(root->right);
}

void BinaryTree::printPostOrder(TreeNode *root){
    if(!root) return;
    
    printInOrder(root->left);
    printInOrder(root->right);
    printf("%d ", root->value);
    
}









 void printTree(TreeNode* root) {

    vector<vector<string>> result;
    if(!root) return ;
        
    int height = getHeight(root);
    int maxColCount = 0 ;
    for(int i =1; i<=height; ++i) maxColCount += pow(2, i -1);
    if(maxColCount %2 == 0) maxColCount += 1;
        
    //printf("height = %d, max colCount = %d\n", height, maxColCount);
        
        
    for(int h = 0; h<height; ++h) {
        vector<string> v;
        for(int w = 0; w<maxColCount; ++w) v.push_back("");
        result.push_back(v);
    }
    populateArray(root,result, 0, 0, result.at(0).size()-1);


    if(result.empty()) {printf("[]\n"); return;}
    printf("[\n\n");
    for(vector<string> v: result){
        printf("[");
        for(string s: v){
            if(s == "") cout<<".";
            else cout<<s<<"";
        }
        printf("]\n");
    }
    printf("\n]\n");
        
}
    
void populateArray(TreeNode *root, vector<vector<string>> &result, int level, int start, int end){
    if(!root ) return;
        
    int mid = ((end+1)+start)/2;
    //printf("mid %d\n", mid);
    result.at(level).at(mid) = to_string(root->value);
        
    populateArray(root->left, result,level+1,start, mid-1);
    populateArray(root->right, result,level+1, mid+1, end);
        
}

int getHeight(TreeNode *root){
    if(!root) return 0;
        
    int left = getHeight(root->left) +1;
    int right = getHeight(root->right) +1;
        
    return max(left, right);
}