#include <iostream>
#include "Point.h"

using namespace std;


int main()
{
    Point A(-35456,50);
    Point B(7,80);
    
    
   Point res=Point::pointMultiplication(A,16,10000,3);
    cout<<res.getX()<<" "<<res.getY();
}