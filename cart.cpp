#include "cart.h"
using namespace std;


Cart::Cart(int num, const string& link) : Cnbr(num), Clink(link)
{
}
int Cart::getNumber()const{
    return Cnbr;
}
string Cart::getLink()const{
    return Clink;
}
void Cart::setNumber(int n){
    Cnbr=n;
}
void Cart::setLink(string n){
    Clink=n;
}
