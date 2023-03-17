#include<bits/stdc++.h>
using namespace std;

class Point
{
    private :
           long long int x;
           long long int y;


        
      
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
                                       


};


