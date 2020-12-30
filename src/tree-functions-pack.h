//
// Created by YKROPCHIK on 16.12.2020.
//
#include "iostream"

enum Color {
    BLACK,
    RED
};

struct TreeNode {
    int numb;
    Color color;
    TreeNode* parent;
    TreeNode* leftChild;
    TreeNode* rightChild;
};

static TreeNode* nullNode = new TreeNode {
    0,
    BLACK,
    nullptr,
    nullptr,
    nullptr
};

TreeNode* createTree();
void addNode(TreeNode*& tree, int numb);
bool removeNode(TreeNode*& tree, int numb);
void printTree(TreeNode* tree, int level);
void removeTree(TreeNode*& tree);
TreeNode* searchNode(TreeNode* tree, int numb);

void addFix(TreeNode*& tree, TreeNode* node);
void removeFix(TreeNode*& tree, TreeNode* node);
void leftRotateSubTree(TreeNode*& tree, TreeNode* subTree);
void rightRotateSubTree(TreeNode*& tree, TreeNode* subTree);
void nodeTransplant(TreeNode*& tree, TreeNode* first, TreeNode* second);
TreeNode* getMinFromSubtree(TreeNode* subTree);
