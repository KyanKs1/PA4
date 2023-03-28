#pragma once
#include "RedBlackNode.h"

class RedBlackTree
{
public:
    ~RedBlackTree() {  }
    //Constructor creates header and sets other node to null.
    explicit RedBlackTree(InventoryRecord &negInf) {
        nullNode = new RedBlackNode();
        nullNode->setLeft(nullNode);
        nullNode->setRight(nullNode);

        header = new RedBlackNode(negInf.getId(),negInf.getType(),negInf.getNum());
        header->setLeft(nullNode);
        header->setRight(nullNode);
    }
    //Textbook isempty
    bool isEmpty() const
    {
        return header->getRight() == nullNode;
    }
    //The following insert function and helper functions are from the textbook
    //i used a node class instead of structs and edited the pointer work in rotate 
    void insert(InventoryRecord& x)
    {
        current = parent = grand = header;
        nullNode->setData(x);

        while (current->getId() != x.getId())
        {
            great = grand; grand = parent; parent = current;
            if (x.getId() < current->getId()) {
                current = current->getLeft();  // Update current to the left child
            }
            else {
                current = current->getRight();  // Update current to the right child
            }
            // Check if two red children; fix if so
            if (current->getLeft()->getColor() == RedBlackNode::RED && current->getRight()->getColor() == RedBlackNode::RED)
               handleReorient(x);
        }
        // Insertion fails if already present
        if (current != nullNode)
            return ;
        current = new RedBlackNode(x.getId(),x.getType(),x.getNum(), nullNode, nullNode);

        // Attach to parent
        if (x.getId() < parent->getId()) {
            parent->setLeft(current);
        }
        else {
            parent->setRight(current);
        }
        handleReorient(x);
    }

    RedBlackNode* rotate( InventoryRecord& item, RedBlackNode* theParent)
    {
        if (item.getId() < theParent->getId())
        {
            if (item.getId() < theParent->getLeft()->getId()) {
                RedBlackNode* temp = theParent->getLeft();
                rotateWithLeftChild(temp);  // LL
               theParent->setLeft(temp);

                //Changes without temp cannot be made due to temp value in ge
            }
            else {
                RedBlackNode* temp2 = theParent->getLeft();
                rotateWithRightChild(temp2); 
                theParent->setRight(temp2);// LR
            }
            return theParent->getLeft();
        }
        else
        {
            if (item.getId() < theParent->getRight()->getId()) {
                RedBlackNode* temp = theParent->getRight();
                rotateWithLeftChild(temp);
                theParent->setLeft(temp);// RL
            }
            else {
                RedBlackNode* temp2 = theParent->getRight();
                rotateWithRightChild(temp2); 
                theParent->setRight(temp2);// RR
            }
            return theParent->getRight();

        }
    }


    void rotateWithLeftChild(RedBlackNode*& k2)
    {
        RedBlackNode* k1 = k2->getLeft();
        k2->setLeft(k1->getRight());
        k1->setRight(k2);
        k2 = k1;
    }
    void rotateWithRightChild(RedBlackNode*& k1)
    {
        RedBlackNode* k2 = k1->getRight();
        k1->setRight(k2->getLeft());
        k2->setLeft(k1);
        k1 = k2;
    }
    void handleReorient(InventoryRecord& item)
    {
        // Do the color flip
        current->setColor(RedBlackNode::RED);
        current->getLeft()->setColor(RedBlackNode::BLACK);
        current->getRight()->setColor(RedBlackNode::BLACK);

        if (parent->getColor() == RedBlackNode::RED)   // Have to rotate
        {
            grand->setColor(RedBlackNode::RED);
            if (item.getId() < grand->getId() != item.getId() < parent->getId())
                parent = rotate(item, grand);  // Start dbl rotate
            current = rotate(item, great);
            current->setColor(RedBlackNode::BLACK);
        }
        header->getRight()->setColor(RedBlackNode::BLACK); // Make root black
    }
    //Own implemtation of make empty NOTE THAT WE NEED to CALL VERSION WITH 0 Arguments
    void makeEmpty(RedBlackNode* node)
    {
        if (node != nullNode)
        {
            makeEmpty(node->getLeft());
            makeEmpty(node->getRight());
            delete node;
        }
    }
    void makeEmpty()
    {
        makeEmpty(header->getRight());
        header->setRight(nullNode);
    }
    //Textbook Print tree edited to fit class
    
    void printTree(RedBlackNode* t) const
    {
        if (t != t->getLeft())
        {
            printTree(t->getLeft());
            cout << t->getId() << "," << t->getType() << " " << t->getNum() << endl;
            printTree(t->getRight());
        }
    }

    //Below is print level order which uses recursion to find max level then prints from there
    // it uses 2 helper function in its incorperation.
    void printLevelorder() const {
        int h = getHeight(header->getRight());
        for (int i = 1; i <= h; ++i) {
            printGivenLevel(header->getRight(), i);
        }
    }

    void printGivenLevel(RedBlackNode* node, int level) const {
        if (node == nullNode || node == header || level < 1) {
            return;
        }

        if (level == 1) {
            cout << node->getData().getId() << " ";
        }
        else if (level > 1) {
            printGivenLevel(node->getLeft(), level - 1);
            printGivenLevel(node->getRight(), level - 1);
        }
    }
    int getHeight(RedBlackNode* node) const {
        if (node == nullNode || node == header) {
            return 0;
        }

        int leftHeight = getHeight(node->getLeft());
        int rightHeight = getHeight(node->getRight());

        return 1 + max(leftHeight, rightHeight);
    }
   //PrintGTree called in main with no arguments
    void printTree() const
    {
        if (header->getRight() == nullNode)
            cout << "Empty tree" << endl;
        else
            printTree(header->getRight());
    }



private:
    //text book datamembers
	
    RedBlackNode* header;   
    RedBlackNode* nullNode;
    RedBlackNode* current;
    RedBlackNode* parent;
    RedBlackNode* grand;
    RedBlackNode* great;
};

