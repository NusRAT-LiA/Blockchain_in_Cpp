#include<bits/stdc++.h>
#ifndef ELIPTIC_CURVE_H
#define ELIPTIC_CURVE_H
using namespace std ;


class ElipticCurve{ 


       // For equation y^2 =x^3 + ax + b ;
        
        private :
           long long int rangeConstant ;

        public :
           long long int a;
           long long int b;
           
           long long int GetRangeC(){return this->rangeConstant;}
           long long int GetA(){return this->a;}
           long long int GetB(){return this->b;}

           void SetRangeC(long long int p){this->rangeConstant=p;}
           void SetA(long long int a){this->a=a;}
           void SetB(long long int b){this->b=b;}

           ElipticCurve()
           {
              this->a=this->b=this->rangeConstant=0;
           }

           ElipticCurve(long long int a , long long int b , long long int rangeC)
           {
              this->a=a;
              this->b=b;
              this->rangeConstant=rangeC;
           } 

           long long int CalcYsqrt(long long int x)
           {
                long long int y = pow(x,3)+(this->a*x)+this->b;

                return(y%(this->rangeConstant));
           }

};
#endif