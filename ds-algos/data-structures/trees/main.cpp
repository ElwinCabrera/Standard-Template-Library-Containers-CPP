#include <iostream>

#include "main.hpp"


int main(){
    BinaryTree bTree;
    bTree.insert(bTree.getRoot(),10);
    
    //left subtree
    bTree.insert(bTree.getRoot(),9);
    bTree.insert(bTree.getRoot(),8);
    bTree.insert(bTree.getRoot(),7);
    bTree.insert(bTree.getRoot(),6);
    bTree.insert(bTree.getRoot(),5);

    //right subtree 
    bTree.insert(bTree.getRoot(),11);
    bTree.insert(bTree.getRoot(),12);
    bTree.insert(bTree.getRoot(),13);
    bTree.insert(bTree.getRoot(),14);
    bTree.insert(bTree.getRoot(),15);

    bTree.printInOrder(bTree.getRoot());
    printf("\n");

    bTree.printPreOrder(bTree.getRoot());
    printf("\n");

    printTree(bTree.getRoot());

    printf("minimum value is %d\n",bTree.getMin(bTree.getRoot())->value);
    
    bTree.remove(bTree.getRoot(),12);
    
    printf("\n");
    bTree.printInOrder(bTree.getRoot());
    printf("\n");

    bTree.printPreOrder(bTree.getRoot());
    printf("\n");

    printTree(bTree.getRoot());

    return 0;
}
