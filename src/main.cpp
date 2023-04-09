#include<bits/stdc++.h>
#include "../Sha256_Algorithm/Sha256.h"
#include "../Eliptic_Curve_Cryptography/GeneratePoint.h"
using namespace std;
bool validateNonce(string hash, int target) {
        for(int i = 0; i < target; i++) {
            if(hash[i] != '0') {
                return false;
            }
        }
        return true;}
int main()
{  
    cout<<"\n The hash -\n ";
    string cdH=Hash("Nursat jahan Lia");
    cout<<Hash("Nursat jahan Lia")<<endl;
   pair<long long int , long long int > result ;
   ElipticCurve EC=CreateCurve();
         Entity WalletOwner("alice",EC);
   result=generateKey(WalletOwner,EC);
   cout<<"PublicKey :  "<<result.first<<"\t"<<result.second<<endl;
   
   int target = 4;
   int nonce=0;
   while(true)
   {
     string nonceStr = to_string(nonce);
     auto now = chrono::system_clock::now();
     time_t time =chrono::system_clock::to_time_t(now);
     string timestr=to_string(time);
     string candidateHash=Hash(cdH+nonceStr+timestr);
     if(validateNonce(candidateHash, target)) {cout<<candidateHash<<endl;break;}
     nonce++;


   }
}