#include <iostream>
#include "employee1.h"
using namespace std;
int main(){
    Date birth(7,24,1949);
    Date death(3,12,1988);
    Employee manager("Lucifer", "Mephisto", birth, death);
    cout << endl;
    manager.print();
    return 0;
}
