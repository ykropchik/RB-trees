#include "src/tree-functions-pack.h"

int main() {
    TreeNode* tree = createTree();

    /*addNode(tree, 15);
    addNode(tree,  10);
    addNode(tree, 25);
    addNode(tree, 13);
    addNode(tree, 78);
    addNode(tree, 4);
    addNode(tree, 5);
    addNode(tree, 8);
    addNode(tree, 11);
    addNode(tree, 3);
    addNode(tree, 9);
    addNode(tree, 66);
    addNode(tree, 45);
    printTree(tree, 0);
    std::cout << std::endl;
    removeNode(tree, 11);
    printTree(tree, 0);
    std::cout << std::endl;
    removeNode(tree, 66);
    printTree(tree, 0);
    std::cout << std::endl;
    removeNode(tree, 78);
    printTree(tree, 0);*/


    for (int i=1; i<25;i++)
    {  addNode(tree, i); }
    std::cout <<"------ ADD -------" <<std::endl;
    printTree(tree, 0);
    std::cout << std::endl;

    for (int i=1; i<8;i++)
    {  removeNode(tree, i*2+1); }
    std::cout <<"------ DEL -------" <<std::endl;
    printTree(tree, 0);

    std::cout <<"------ DEL TREE-------" <<std::endl;
    removeTree(tree);
    printTree(tree, 0);

    return 0;
}
