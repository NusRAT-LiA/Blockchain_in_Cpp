#include <iostream>
#include "BigInteger.h"

using namespace std;


int main() {
    BigInteger a("123456789012345678901234567890");
    BigInteger b("98765432109876543210987654321000");

    BigInteger num1("-9");
    BigInteger num2("21");
    string sum = num1.add(num2);
    string substr=num1.subtract(num2);
    string mult = num1.multiply(num2);
    cout << "The sum of " << num1.toString() << " and " << num2.toString() << " is: " << sum << endl;
    cout << "The substraction of " << num1.toString() << " and " << num2.toString() << " is: " << substr << endl;
    cout<<mult;
    return 0;

    
}