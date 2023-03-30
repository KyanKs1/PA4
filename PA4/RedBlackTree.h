#pragma once
#include "RedBlackNode.h"
#include <queue>
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
    //uses getters instead of comparsion operator
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
                theParent->setLeft(temp2);// LR
            }
            return theParent->getLeft();
        }
        else
        {
            if (item.getId() < theParent->getRight()->getId()) {
                RedBlackNode* temp = theParent->getRight();
                rotateWithLeftChild(temp);
                theParent->setRight(temp);// RL
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
        if (k2 == nullptr) {
            // Handle null pointer case
            return;
        }
        RedBlackNode* k1 = k2->getLeft();
        if (k1 == nullptr) {
            // Handle null pointer case
            return;
        }
        k2->setLeft(k1->getRight());
        k1->setRight(k2);
        k2 = k1;
    }
    void rotateWithRightChild(RedBlackNode*& k1)
    {
        if (k1 == nullptr) {
            // Handle null pointer case
            return;
        }
        RedBlackNode* k2 = k1->getRight();
        if (k2 == nullptr) {
            // Handle null pointer case
            return;
        }
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
            if ((item.getId() < grand->getId()) != (item.getId() < parent->getId()))
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
            int color = t->getColor();
            string c;
            if (color == RedBlackNode::BLACK) {
                c = "Black";
            }
            else {
                c = "Red";
            }
            printTree(t->getLeft());
            cout << t->getId() << "," << t->getType() << " " << t->getNum() << " " << c << endl;
            printTree(t->getRight());
        }
    }

    //Below is print level order which uses recursion to find max level then prints from there
    // it uses 2 helper function in its incorperation. also uses STL queue in implmentation
    void printLevelOrder() const {
        if (header->getRight() == nullNode) {
            return;
        }

        queue<RedBlackNode*> q;
        q.push(header->getRight());

        while (!q.empty()) {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {
                RedBlackNode* node = q.front();
                q.pop();
                int color = node->getColor();
                string c;
                if (color == RedBlackNode::BLACK) {
                     c = "Black";
                }
                else {
                     c = "Red";
                }
                cout << node->getData().getId() <<" " << node->getData().getType() << " " << node->getData().getNum() << " at level " << getLevel(node) << " (" << c << ")" << endl;

                if (node->getLeft() != nullNode) {
                    q.push(node->getLeft());
                }
                if (node->getRight() != nullNode) {
                    q.push(node->getRight());
                }
            }
        }
    }
    //returns level of node
    int getLevel(RedBlackNode* node) const {
        int level = 0;
        RedBlackNode* curr = header->getRight();

        while (curr != nullNode) {
            if (node->getData().getId() == curr->getData().getId()) {
                return level;
            }
            else if (node->getData().getId() < curr->getData().getId()) {
                curr = curr->getLeft();
            }
            else {
                curr = curr->getRight();
            }
            level++;
        }

        return -1;  // node not found in tree
    }

    //returns height of node
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

    //Updatenode searches all nodes of tree till it finds one with matching Id to prompt changes
    //Elss it wont do anything
    void updateNode(int id, RedBlackNode* root)
    {
        RedBlackNode* current = root;
        while (current != current->getLeft())
        {
            if (id == current->getId())
            {
                int user;
                string p;
                cout << " Found Record to change..." << endl;
                cout << "New Id? ";
                cin >> user;
                cout << "new type? ";
                cin >> p;
                InventoryRecord pnew;
                pnew.setId(user);
                pnew.setType(p);
                cout << "New amount? ";
                cin >> user;
                pnew.setNumOf(user);
                current->setData(pnew);
                cout << "Succsessfull Change" << endl;
                break;
            }
            else if (id < current->getId())
            {
                current = current->getLeft();
            }
            else
            {
                current = current->getRight();
            }
        }
    }
    //stadard getter for header
    RedBlackNode* getHeader() {
        return header;
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

