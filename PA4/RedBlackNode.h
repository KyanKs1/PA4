#pragma once
#include "InventoryRecord.h"
#include <iostream>
#include <string>
using namespace std;
//All methods below were taken from struct implementation then changed by me,
//to fit class requirements
class RedBlackNode {
public:
    enum Color{ RED, BLACK };
    //Defualt constructor for redblack node
    RedBlackNode(int id = 0, string type = "", int numOf = 0, RedBlackNode* lt = nullptr,
        RedBlackNode* rt = nullptr, int c = BLACK);
       
    //Move constructor for inventory record node
    RedBlackNode(InventoryRecord&& nData, RedBlackNode* lt = nullptr,
        RedBlackNode* rt = nullptr, int c = BLACK);
      
    //Destructor delcared in header
    ~RedBlackNode() {}

    //For test fuctions in main otherwise getters and setters
    int getId()  { return data.getId(); }
    string getType()  { return data.getType(); }
    int getNum()  { return data.getNum(); }
    RedBlackNode* getLeft() {
        return left;
    }
    RedBlackNode* getRight() {
        return right;
    }
    void setRight(RedBlackNode* right) {
        
            this->right = right;
        
    }

    void setLeft(RedBlackNode* left) {
      
            this->left = left;
        
    }
    void setData(InventoryRecord& d) {
        data = d;
    }
    InventoryRecord getData() {
        return data;
    }
    int getColor() {
        return color;
    }
    void setColor(int c) {
        color = c;
    }
private:
    //Data members required
    InventoryRecord data;
    RedBlackNode* left;
    RedBlackNode* right;
    int color;
};
