#include <iostream>
#include "Point.h"

using namespace std;


int main()
{
    Point A(35456,50);
    Point B(7,80);
    
    
   Point res=Point::pointAddition(A,B,50,3);
    cout<<res.getX()<<" "<<res.getY();
}