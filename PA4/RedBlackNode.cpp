#include "RedBlackNode.h"
//Constructer sets values to parameters
RedBlackNode::RedBlackNode(int id, string type, int numOf , RedBlackNode* lt,
	RedBlackNode* rt, int c) {
	data.setId(id);
	data.setType(type);
	data.setNumOf(numOf);
	left = lt;
	right = rt;
	color = c;
}
//Constructer creates new data object with nData moved from other object, calls inventoryrecord move constructor.
RedBlackNode::RedBlackNode(InventoryRecord&& nData, RedBlackNode* lt,
	RedBlackNode * rt, int c) : data(std::move(nData)) {
	this->right = rt;
	this->left = lt;
	this->color = c;
}

