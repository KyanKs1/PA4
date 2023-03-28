#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "InventoryRecord.h"
#include "RedBlackNode.h"
#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <fstream>
void importFile(RedBlackTree& r) {
	ifstream file;
	file.open("inventory.csv");
	InventoryRecord inv;
	string q1;
	char str[300];
	string temp;

	while (!file.eof())
	{
		getline(file, q1);
		strcpy(str, q1.c_str());
		temp = strtok(str, ",");
		inv.setId(atoi(temp.c_str()));
		temp = strtok(NULL, ",");
		inv.setType(temp);
		temp = strtok(NULL, ",");
		inv.setNumOf(atoi(temp.c_str()));
		r.insert(inv);
	}
}

int main() {
	InventoryRecord neginf(-5000, "NEGINF", -4999);
	RedBlackTree Tree{neginf};
	importFile(Tree);	
	
	Tree.printTree();
	bool end = false;
	int userI =  -1;
	while (end == false)
	{
		cout << "~~~Inventory Menu~~~" << endl;
		cout << "(1) Add Item\n(2)Update item \n(3)Display inventory\n(4)Printtree (level order)\n(5)exit" << endl;
		cin >> userI;
		
		if (userI == 5) {
			end = true;
		}

	}
}



