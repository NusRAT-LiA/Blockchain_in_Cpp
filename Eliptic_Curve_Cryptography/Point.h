#include<bits/stdc++.h>
using namespace std;

class Point
{
    private :
           long long int x;
           long long int y;


        int modular_inverse(int a, int m) {
                int m0 = m;
                int y = 0, x = 1;
 
                  if (m == 1)
                       return 0;
 
                  while (a > 1) {
                      int q = a / m;
                      int t = m;
                      m = a % m, a = t;
                       t = y;
                       y = x - q * y;
                       x = t;
                    }
 
                   if (x < 0)
                        x += m0;
  
           return x;
        }       


        int gcdExtended(int a, int b, int &x, int &y) {
          if (a == 0) {
            x = 0;
            y = 1;
          return b;
        }
        int x1, y1;
        int gcd = gcdExtended(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
       return gcd;
      }

    public :

        Point(long long int a , long long int b)
        {
            this->x=a;
            this->y=b;
        }

        long long int getX()
        {
            return x;
        }

        long long int getY()
        {
            return y;
        } 

        void setX(long long int a)
        {
            this->x=a;
        }

        void setY(long long int b)
        {
            this->y=b;
        }
        Point pointDoubling(Point p1, long long int a, long long int p) {
         Point result(0, 0);

         long long int numerator = (3 * p1.getX() * p1.getX() + a) % p;
         long long int denominator = (2 * p1.getY()) % p;

         denominator = gcdExtended(denominator, p);
         
         long long int slope = (numerator * denominator) % p;
    result.setX((slope * slope - 2 * p1.getX() + p) % p);
    result.setY((slope * (p1.getX() - result.getX()) - p1.getY() + p) % p);
    return result;
}

      

                                       


};