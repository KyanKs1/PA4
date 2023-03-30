#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "InventoryRecord.h"
#include "RedBlackNode.h"
#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <fstream>
/**********************************************************************************
* Programmer: Kyan Kotschevar-Smead                                                *
* Class: CptS 223                                          *
* Programming Assignment:4                                       *
* Date:3/30/2023                                                                      *
*                                                                                *
* Description: Program models a redblack tree and its operations dealing with data
* insertion,changing,deletion and displaying
*                                                                                *
*********************************************************************************/
//function below parses inventory.csv lines into inventory records and inserts into tree
void importFile(RedBlackTree& r) {
	cout << "Importing from file..." << endl;
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
//Main acts as the main interface of the program where all functions are called. Ie summmary of programing
int main() {
	InventoryRecord neginf(-5000, "NEGINF", -4999);
	RedBlackTree Tree{ neginf };
	importFile(Tree);	
	
	Tree.printTree();
	bool end = false;
	int userI =  -1;
	while (end == false)
	{
		cout << "~~~Inventory Menu~~~" << endl;
		cout << "(1) Add Item\n(2)Update item \n(3)Display inventory\n(4)Printtree (level order)\n(5)exit" << endl;
		cin >> userI;
		if (userI == 1) {
			cout << "~~~Add item" << endl;	
			InventoryRecord add;
			int p;
			string t;
			cout << "Enter a id (int) : ";
			cin >> p;
			add.setId(p);
			cout << "Enter a type (string) : ";
			cin >> t;
			add.setType(t);
			cout << "Enter an Amount (int) : ";
			cin >> p;
			add.setNumOf(p);
			cout << "Adding new Record..." << endl;
			Tree.insert(add);
		}
		if (userI == 2) {
			int id;
			cout << "Changing Data\n What Id do you want to change(int) " << endl;
			cin >> id;
			Tree.updateNode(id, Tree.getHeader());
		}
		if(userI == 4) {
			cout << "~~~Printing Level order:" << endl;
			Tree.printLevelOrder();
		}//PrintLevelorder
		if (userI == 3) {
			cout << "~~~ Printing inventory:" << endl;
			Tree.printTree();
		}//PrintinOrder
		if (userI == 5) {
			Tree.makeEmpty();
			cout << "Exiting Program" << endl;
			end = true;
		}//Exit

	}
}


/*
(4 pts) What is the worst-case Big-O of the insert() algorithm for the red-black tree? Explain.
For insertion it is ologn to traverse the node to find the place to insert garteed becuase of the balencing properties.
Checking for color and rotates are minimal thus the worst case is OlogN
 (4 pts) What is the worst-case Big-O of the printLevelOrder() algorithm for the red-black tree?
Explain.
O(n) becuase it has to search thorugh every element of tree in order to properly print all of them. Other operations like checking color and heigh 
also requre a similar time but is done along side with recursion thus worst case is o(n)
 (2 pts) What is the worst-case Big-O of the findMax() algorithm for the red-black tree? Explain.
OLogn, becuase of the balenceing properties of the tree, the function should only have to traverse the right subtree countinually
thus it its not going through all the node meaning worst case should be ologn
*/

