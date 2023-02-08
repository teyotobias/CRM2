// CRM in C++ CustomerDB.cpp
// EE 312 Project 7 submission by
// Teyo Turrubiates
// ttt2443
// Slip days used: 0
// Summer 2022
#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(UTString name) {
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) {
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) {
    return this->length;
}

CustomerDB::~CustomerDB(void) {
    delete[] this->data;
}



void CustomerDB::clear(void) {
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) {
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) {
    for(int i = 0; i < length;i++){
        if(data[i].name == name){
            return data[i];
        }
    }
    if(capacity > length){
        data[length] = name;
        length++;
        return data[length-1];
    }
    else {
        capacity*=2;
        Customer* newData = new Customer[capacity];
        for(int i = 0; i < length;i++){
            newData[i] = data[i];
        }
        delete[] data;
        newData[length] = name;
        length++;
        data = newData;
        return data[length-1];
    }
}

bool CustomerDB::isMember(UTString name) {
    for(int i = 0; i < length;i++){
        if(data[i].name == name){
            return true;
        }
    }
    return false;
}