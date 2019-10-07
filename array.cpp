#include<iostream>
#include"array.h"
using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::istream;

//Primo costruttore di Array, prende la dimensione dell'array
//Se non definita la setta in automatico a 10 ( vedere array.h)
//Se arraySize < 0 si rifiuta di farlo e lo setta a 10

Array::Array(int arraySize ){				
    size = (arraySize > 0 )? arraySize : 10;		
    ptr = new int[10];					
    for (int i = 0; i < size; i++){			
	ptr[i] = 0;					
    }
}


//Copy Constructor, crea un oggetto identico a quello dato come argomento

Array::Array(const Array &arrayToCopy):size(arrayToCopy.size){
    ptr = new int[size];
    for ( int i = 0 ; i < size ; i++){
	ptr[i] = arrayToCopy.ptr[i];
    }
}
//Distruttore, libera la memoria occupata dal puntatore quando si termina un oggetto
Array::~Array(){
    delete[] ptr;
}

//Restituisce la dimensione dell'array (very comodo per i for)
int Array::getSize() const{
    return size;
}

//Overload dell'operatore =
//Prende un array ( sinistra ) e lo pone 
//uguale ad un altro ( destra )
//Utilizzo A = B;
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

//Overload dell'operatore ==
//Confronta due array chiedendosi se siano uguali
//Se hanno dimensione diversa restituisce false
//Lo stesso vale se hanno anche solo un elemento differente
bool Array::operator==(const Array &right)const{
    if (size != right.size){
	return false;
    }
    for (int i = 0; i < size ; i++){
	if (ptr[i] != right.ptr[i]) return false;
    }
    return true;
}
//Overload dell'operatore !=
//Confronta due array e restituisce true se sono diversi
//Ovvero l'opposto dell'operatore ==
//(this serve a chiamare l'oggetto a sinistra)
bool Array::operator!=(const Array &right) const{
    return ! ( *this == right);
}

//Overload dell'operatore [ ]
//Fa in modo che si possano modificare i singoli
//elementi dell'array, restituendone il puntatore(?)
//Es Array A(3);
//A[1] = 4;
int &Array::operator[](int sub){
     if (sub < 0|| sub >= size){
	cout << "NOOOOOOOO" << endl;
	exit(1);
    }
    
    return ptr[sub];
}
//Overload dell'operatore [ ]
//Restituisce il valore contenuto all'interno di
//una posizione del puntatore in modo da poterlo, ad esempio, stampare
//senza rischio di modificarlo
//Es Array A(3);
//A[2] = 3;
//cout << A[0]<<A[2]<<A[1];
//risulterà in: 030
const int &Array::operator[](int sub) const{
    if (sub < 0|| sub >= size){
	cout << "NOOOOOOOO" << endl;
	exit(1);
    }
    return ptr[sub];
}
//Overload dell'operatore >> 
//Si attiva nel caso in cui >> si trovasse un oggetto Array
//Es Array A();
//cin >> A;
//Attenderà di ricevere 10 elementi, con i quali riempirà A
istream &operator>>(istream &input,  Array & a){
    for (int i =0; i < a.size; i++){
	input >> a.ptr[i];				
    }
    return input;
}
//Overload dell'operatore << 
//Utile modo per formattare rapidamente l'output 
//nel caso in cui alla sinistra di << ci fosse un Array
//Stampa 4 elementi separati da una tablatura e poi va a capo
//Es Array A();
//cout << A << endl;
//Stamperà
//0	0  0	0
//0	0  0	0
//0
ostream &operator<<(ostream &output,const Array &a){
    for (int i=0; i < a.size; i++){
	output << a[i] << "\t";
	if (i % 4 == 0) output << endl;
    }
    if ((a.size-1) % 4 == 0) output << endl;
    return output;
}


