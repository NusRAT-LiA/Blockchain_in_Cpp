// C++ program to find multiplicative modulo
// inverse using Extended Euclid algorithm.
#include <bits/stdc++.h>
using namespace std;

long long int gcdExtended(long long int a, long long int b , long long int* x, long long int* y)
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

           long long int modInverse(long long int A , long long int M)
           {
              long long int x , y ;
              long long int g = gcdExtended(A,M,&x,&y);
              
              long long int result = ((x%M)+M)%M;
              return result ;
           }
      int main()
      {
         cout<<modInverse(3,11);
      }