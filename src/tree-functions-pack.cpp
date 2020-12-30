//
// Created by YKROPCHIK on 16.12.2020.
//
#include "tree-functions-pack.h"

TreeNode* createTree() {
    return nullNode;
}

void addNode(TreeNode*& tree, int numb) {
    TreeNode* y = nullNode;
    TreeNode* x = tree;

    while (x != nullNode) {
        y = x;
        if (numb < x->numb) {
            x = x->leftChild;
        } else {
            x = x->rightChild;
        }
    }

    auto* newNode = new TreeNode {
        numb,
        RED,
        y,
        nullNode,
        nullNode
    };

    if (y == nullNode) {
        tree = newNode;
    } else if (numb < y->numb) {
        y->leftChild = newNode;
    } else {
        y->rightChild = newNode;
    }

    addFix(tree, newNode);
}

bool removeNode(TreeNode*& tree, int numb) {
    TreeNode* node = searchNode(tree, numb);

    if (node == nullNode) {
        return false;
    }

    TreeNode* y = node;
    TreeNode* x = nullNode;
    Color yOriginalColor = y->color;

    if (node->leftChild == nullNode) {
        x = node->rightChild;
        nodeTransplant(tree, node, node->rightChild);
    } else {
        if (node->rightChild == nullNode) {
            x = node->leftChild;
            nodeTransplant(tree, node, node->leftChild);
        } else {
            y = getMinFromSubtree(node->rightChild);
            yOriginalColor = y->color;
            x = y->rightChild;
            if (y->parent == node) {
                x->parent = y;
            } else {
                nodeTransplant(tree, y, y->rightChild);
                y->rightChild = node->rightChild;
                y->rightChild->parent = y;
            }

            nodeTransplant(tree, node, y);
            y->leftChild = node->leftChild;
            y->leftChild->parent = y;
            y->color = node->color;
        }
    }

    if (yOriginalColor == BLACK) {
        removeFix(tree, x);
    }
}

void printTree(TreeNode* tree, int level){
    if (tree == nullNode) {
        if (level == 0) {
            std::cout << "Null";
        }
        return;
    }

    if(tree)
    {
        printTree(tree->rightChild, level + 1);

        for(int i = 0; i < level; i++) {
            std::cout << "     ";
        }

        if (tree->color == RED) {
            std::cout << "\x1B[48;2;241;68;69m\x1B[1;38;2;255;255;255m " << tree->numb << " \033[0m" << std::endl;
        } else {
            std::cout << "\x1B[48;2;0;0;0m\x1B[1;38;2;255;255;255m " << tree->numb << " \033[0m" << std::endl;
        }

        printTree(tree->leftChild,level + 1);
    }
}

void removeTree(TreeNode*& tree) {
    TreeNode* runner = tree;
    TreeNode* delNode;

    while (tree->leftChild != nullNode || tree->rightChild != nullNode){
        while (runner->leftChild != nullNode) {
            runner = runner->leftChild;
        }

        if (runner->rightChild == nullNode) {
            delNode = runner;
            runner = runner->parent;

            if (delNode == runner->leftChild) {
                runner->leftChild = nullNode;
            } else {
                runner->rightChild = nullNode;
            }

            delete delNode;
            /*printTree(tree, 0);
            std::cout << " ----- " << std::endl;*/
        } else {
            runner = runner->rightChild;
        }
    }

    delete tree;
    tree = nullNode;
}

TreeNode* searchNode(TreeNode* tree, int numb) {
    TreeNode* runner = tree;
    while (runner != nullNode && runner->numb != numb) {
        runner = (numb < runner->numb ? runner->leftChild : runner->rightChild);
    }

    return runner;
}

/** --------- Balancing functions --------- **/

void addFix(TreeNode*& tree, TreeNode* node) {
    while (node->parent->color == RED) {
        if (node->parent == node->parent->parent->leftChild) {
            TreeNode* y = node->parent->parent->rightChild;
            if (y->color == RED) {
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->rightChild) {
                    node = node->parent;
                    leftRotateSubTree(tree, node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotateSubTree(tree, node->parent->parent);
            }
        } else {
            TreeNode* y = node->parent->parent->leftChild;
            if (y->color == RED) {
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->leftChild) {
                    node = node->parent;
                    rightRotateSubTree(tree, node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotateSubTree(tree, node->parent->parent);
            }
        }
    }

    tree->color = BLACK;
}

void removeFix(TreeNode*& tree, TreeNode* node) {
    while (node != tree && node->color == BLACK) {
        if (node == node->parent->leftChild) {
            TreeNode* w = node->parent->rightChild;

            if (w->color == RED) {
                w->color = BLACK;
                node->parent->color = RED;
                leftRotateSubTree(tree, node->parent);
                w = node->parent->rightChild;
            }

            if (w->leftChild->color == BLACK && w->rightChild->color == BLACK) {
                w->color = RED;
                node = node->parent;
            } else {
                if (w->rightChild->color == BLACK) {
                    w->leftChild->color = BLACK;
                    w->color = RED;
                    rightRotateSubTree(tree, w);
                    w = node->parent->rightChild;
                }

                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->rightChild->color = BLACK;
                leftRotateSubTree(tree, node->parent);
                node = tree;
            }
        } else {
            TreeNode* w = node->parent->leftChild;

            if (w->color == RED) {
                w->color = BLACK;
                node->parent->color = RED;
                rightRotateSubTree(tree, node->parent);
                w = node->parent->leftChild;
            }

            if (w->rightChild->color == BLACK && w->leftChild->color == BLACK) {
                w->color = RED;
                node = node->parent;
            } else {
                if (w->leftChild->color == BLACK) {
                    w->rightChild->color = BLACK;
                    w->color = RED;
                    leftRotateSubTree(tree, w);
                    w = node->parent->leftChild;
                }

                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->leftChild->color = BLACK;
                rightRotateSubTree(tree, node->parent);
                node = tree;
            }
        }
    }

    node->color = BLACK;
}

void leftRotateSubTree(TreeNode*& tree, TreeNode* subTree) {
    TreeNode* y = subTree->rightChild;
    subTree->rightChild = y->leftChild;

    if (y->leftChild != nullNode) {
        y->leftChild->parent = subTree;
    }

    y->parent = subTree->parent;

    if (subTree->parent == nullNode) {
        tree = y;
    } else {
        if (subTree == subTree->parent->leftChild) {
            subTree->parent->leftChild = y;
        } else {
            subTree->parent->rightChild = y;
        }
    }

    y->leftChild = subTree;
    subTree->parent = y;
}

void rightRotateSubTree(TreeNode*& tree, TreeNode* subTree) {
    TreeNode* y = subTree->leftChild;
    subTree->leftChild = y->rightChild;

    if (y->rightChild != nullNode) {
        y->rightChild->parent = subTree;
    }

    y->parent = subTree->parent;

    if (subTree->parent == nullNode) {
        tree = y;
    } else {
        if (subTree == subTree->parent->rightChild) {
            subTree->parent->rightChild = y;
        } else {
            subTree->parent->leftChild = y;
        }
    }

    y->rightChild = subTree;
    subTree->parent = y;
}

void nodeTransplant(TreeNode*& tree, TreeNode* first, TreeNode* second) {
    if (first->parent == nullNode) {
        tree = second;
    } else {
        if (first == first->parent->leftChild) {
            first->parent->leftChild = second;
        } else {
            first->parent->rightChild = second;
        }
    }

    second->parent = first->parent;
}

TreeNode* getMinFromSubtree(TreeNode* subTree) {
    while (subTree->leftChild != nullNode) {
        subTree = subTree->leftChild;
    }

    return subTree;
}
