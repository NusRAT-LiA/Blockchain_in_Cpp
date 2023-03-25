#include<bits/stdc++.h>
#ifndef POINT_H
#define POINT_H
using namespace std;

class Point
{
    private :
           long long int x;
           long long int y;


        
      
    public :
        
        Point(){this->x=0;this->y=0;}

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

        // Function to convert an integer to a binary string
        static string toBinaryString(int n) {
         if (n == 0) { return "0"; }// Special case for 0 

        string binary = ""; // Initialize an empty string to hold the binary digits

        while (n > 0) {
        int bit = n % 2; // Extract the least significant bit
        binary = to_string(bit) + binary; // Prepend the bit to the binary string
        n /= 2; // Shift the integer right by 1 bit
        }

         return binary; // Return the binary string
        }


         static   long long int gcdExtended(long long int a, long long int b , long long int* x, long long int* y)
           {
                if (a == 0) 
                {
                 *x = 0, *y = 1;
                 return b;
                }   

                long long int x1, y1;
                long long int gcd=gcdExtended(b%a , a, &x1 , &y1);
                *x = y1 - (b / a) * x1;
                *y = x1;
    
                return gcd;        

           } 

        static   long long int modInverse(long long int A , long long int M)
           {
              long long int x , y ;
              long long int g = gcdExtended(A,M,&x,&y);
              
              long long int result = ((x%M)+M)%M;
              return result ;
           }


        static  long long int pow_mod(long long int x, long long int n, long long int p) {
              if (n == 0) return 1;
              if (n & 1)
              return (pow_mod(x, n-1, p) * x) % p;
              x = pow_mod(x, n/2, p);
              return (x * x) % p;
            }

         static bool is_prime(int p) {
                   if (p < 2) {
                        return false;
                    }
                   for (int i = 2; i * i <= p; i++) {
                   if (p % i == 0) {
                   return false;
                   }
                  }
                  return true;
               }
   

        static pair<long long int, long long int> TonelliShanks(long long int n, long long int p) {
         if(!is_prime(p)) {cout<<"p";return {-1,-1};}
        long long int x1 = p - 1;
        long long int expTemp = x1 / 2;
        long long int temp = pow_mod(n, expTemp, p);
     
         // Check if n is a quadratic residue mod p
          if (temp != 1) {
          return {-1, -1};
          }
    
         long long int q = x1;
         int counter = 0;
         while (q % 2 == 0) {
          q = q / 2;
          counter++;
         }
    
        if (counter == 1) {
        long long int r1 = pow_mod(n, (p + 1) / 4, p);
        long long int r2 = p - r1;
        return {r1, r2};
         }
    
        long long int z = 2;
        temp = pow_mod(z, x1 / 2, p);
        while (temp != x1) {
        z++;
        temp = pow_mod(z, x1 / 2, p);
        }
    
        long long int c = pow_mod(z, q, p);
        long long int r = pow_mod(n, (q + 1) / 2, p);
        long long int t = pow_mod(n, q, p);
        int m = counter;
    
       while (true) {
        if (t == 1) {
            long long int r2 = p - 1;
            return {r, r2};
        }
        
        int i = 0;
        long long int zz = t;
        while (zz != 1 && i < (m - 1)) {
            zz = pow_mod(t, pow(2, i), p);
            i++;
        }
        
        long long int b = pow_mod(c, pow(2, m - i - 1), p);
        r = (r * b) % p;
        t = (t * pow_mod(b, 2, p)) % p;
        c = pow_mod(b, 2, p);
        m = i;
    }

    return {-1,-1};
  }




               
 
        
       static  Point pointDoubling(Point A ,long long int rangeConst, long long int a)
        {
          long long  int x3 ,y3;

          long  long int numerator = 3*A.x*A.x +a ;
          long  long int denominator = 2*A.y;

          denominator=modInverse(denominator,rangeConst);
          long long int slope = (numerator*denominator)%rangeConst;

          x3=(slope*slope - A.x - A.x)%rangeConst;
          y3=(slope*(A.x -x3)-A.y)%rangeConst;

          Point result(x3,y3);

          return result ;


        }

      static  Point pointAddition(Point A , Point B , long long int rangeConst, long long int a)
        {
               long long int slope , yIntercept;
               long long int x3 , y3 ;

               if(A.x==B.x && A.y==B.y)
               {
                 Point result(0,0) ;
                 result = pointDoubling(A,rangeConst,a);
                 return result ;
               }

               long long int numerator = B.y - A.y;
               long long int denominator = B.x - A.x;
               if(numerator < 0)
                {
                    numerator= (-numerator);
                    denominator = ( - denominator);

                }

                denominator=modInverse(denominator,rangeConst);
                slope = (numerator*denominator)%rangeConst;
                x3=(slope*slope - A.x -B.x)%rangeConst;
                y3=(slope*(A.x -x3)-A.y)%rangeConst;

                 Point result(x3,y3);
  
                  return result ;

        }   

        static Point pointMultiplication(Point P , long long int m , long long int rangeConstant , long long int a)
        {
                Point n = P;
                Point result(0, 0);
                string binaryM =toBinaryString(m);
                int i = binaryM.length()-1;

                while (i >=0)
                 {
                    if (binaryM[i] == '1')
                   {
                     if (result.getX() == 0 && result.getY() == 0) { result = n;  }
                     else{ result =pointAddition(result , n , rangeConstant , a);}
                   }
                   n = pointDoubling(n,rangeConstant,a);
                   i--;
                  }
               return result;
       }  


static Point messageEncoding(long long int m,long long int rangeConstant, long long  int a , long long int b) {
    long long int  K = 10;
    long long int maxMessageSize = (rangeConstant - K) / K;
    if (m > maxMessageSize)
        return Point(-1, -1);
    long long int m1 = m + 1;
    if (m1 * K < rangeConstant) {
        long long int j = 0;
        while (j < K) {
            long long int x = m * K + j;
            long long int y2 = (pow_mod(x, 3, rangeConstant) + a * x + b) % rangeConstant;
            pair<long long int, long long int> roots = TonelliShanks(y2, rangeConstant);
            if (roots.first != -1 && roots.second != -1)
                return Point(x, min(roots.first, roots.second));
            j++;
        }
    }
    return Point(-1, -1);
}

                                       



};

#endif


