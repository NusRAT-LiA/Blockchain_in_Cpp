#include <iostream>
#include "Point.h"

using namespace std;


int main()
{
    Point A(-35456,50);
    Point B(7,80);
    
    
   Point res=Point ::messageEncoding(7030,59999999,45,600);
    cout<<res.getX()<<" "<<res.getY();
}