#ifndef CART_H
#define CART_H
#include<string>

using namespace std;

class Cart
{
public:
    Cart(int num, const string& link);

private:
    int Cnbr;
    string Clink;
public:
    int getNumber()const;
    string getLink()const;
    void setNumber(int n);
    void setLink(string n);
};

#endif // CART_H
