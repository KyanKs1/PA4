#pragma once
#include <iostream>
#include <string>
using namespace std;
//All class parts were created by me
class InventoryRecord

{
public:
	
	InventoryRecord();
	InventoryRecord(int id, string type, int numOf);
	~InventoryRecord();
	int getId();
	string getType();
	int getNum();
	void setId(int id);
	void setType(string type);
	void setNumOf(int numOf);
	InventoryRecord(InventoryRecord&& other) noexcept;
	InventoryRecord& operator=(const InventoryRecord& other)
	{
		if (this == &other) {
			return *this;
		}
		id = other.id;
		type = other.type;
		numOf = other.numOf;
		return *this;
	}
	InventoryRecord(const InventoryRecord& other) {
		id = other.id;
		type = other.type;
		numOf = other.numOf;
	}
		

		
private:
	//Data members
	int id;
	string type;
	int numOf;
};

