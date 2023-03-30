#include "InventoryRecord.h"
//Constructor
InventoryRecord::InventoryRecord(int id, string type, int numOf) {
	this->id =  id;
	this->type = type;
	this->numOf = numOf;
}
//Destructor prints for testing
InventoryRecord::~InventoryRecord() {

}
//Below are a bunch of getters and setters
int InventoryRecord::getId() {
	return id;
}
int InventoryRecord::getNum() {
	return numOf;
}
string InventoryRecord::getType() {
	return type;
}
void InventoryRecord::setId(int id) {
	this->id = id;
}

void InventoryRecord::setType(string type) {
	this->type = type;
}

void InventoryRecord::setNumOf(int numOf) {
	this->numOf = numOf;
}
//Move constructor 
InventoryRecord::InventoryRecord(InventoryRecord&& other) noexcept{
	this->id = std::move(other.id);
	this->type = std::move(other.type);
	this->numOf = std::move(other.numOf);

	other.id = 0;
	other.type = "";
	other.numOf = 0;	
}
//Defualt Constructor 
InventoryRecord::InventoryRecord() {
	this->id = 0;
	this->type = "";
	this->numOf = 0;
}

