#include<iostream>
#include"array.h"
using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::istream;

Array::Array(int arraySize ){
    size = (arraySize > 0 )? arraySize : 10;
    ptr = new int[10];
    for (int i = 0; i < size; i++){
	ptr[i] = 0;
    }
}
Array::Array(const Array &arrayToCopy):size(arrayToCopy.size){
    ptr = new int[size];
    for ( int i = 0 ; i < size ; i++){
	ptr[i] = arrayToCopy.ptr[i];
    }
}
Array::~Array(){
    delete[] ptr;
}
int Array::getSize() const{
    return size;
}
const Array &Array::operator=(const Array &right){
    if (&right != this) {
	if (size != right.size){
	    delete[] ptr;
	    size = right.size;
	    ptr = new int [size];
	}
	for (int i = 0; i < size; i++){
	    ptr[i] = right.ptr[i];
	}
    }
    return *this;   
}


bool Array::operator==(const Array &right)const{
    if (size != right.size){
	return false;
    }
    for (int i = 0; i < size ; i++){
	if (ptr[i] != right.ptr[i]) return false;
    }
    return true;
}

bool Array::operator!=(const Array &right) const{
    return ! ( *this == right);
}

int &Array::operator[](int sub){
     if (sub < 0|| sub >= size){
	cout << "NOOOOOOOO" << endl;
	exit(1);
    }
    
    return ptr[sub];
}

const int &Array::operator[](int sub) const{
    if (sub < 0|| sub >= size){
	cout << "NOOOOOOOO" << endl;
	exit(1);
    }
    return ptr[sub];
}
istream &operator>>(istream &input,  Array & a){
    for (int i =0; i < a.size; i++){
	input >> a.ptr[i];				
    }
    return input;
}

ostream &operator<<(ostream &output,const Array &a){
    for (int i=0; i < a.size; i++){
	output << a[i] << "\t";
	if (i % 4 == 0) output << endl;
    }
    if ((a.size-1) % 4 == 0) output << endl;
    return output;
}


