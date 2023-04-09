#include<bits/stdc++.h>
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "Transactions.h"
#include "../Sha256_Algorithm/Sha256.h"
using namespace std ;

class Transaction
{       
        private :
            bool isVerified=false;

            

        public :
            string TxHash;
            pair<long long int,long long int> PublicKeyOfSenderWallet;
            pair<long long int,long long int> PublicKeyOfRecieverWallet;
            long long int AmountSent;
            //int TransactionNonce;
            long long int Signature;
            // Transactions TxList;

            
            
            
            
            Transaction(pair<long long int,long long int> SenderKey , pair<long long int,long long int> RecieverKey , int Amount, long long int Sign )
            {
               this->PublicKeyOfSenderWallet=SenderKey;
               this->PublicKeyOfRecieverWallet=RecieverKey;
               this->AmountSent=Amount;
               this->Signature=Sign;

            //    srand(time(NULL));
            //    this->TransactionNonce=rand()%1000 + 1; 
               
               string TxString=to_string(this->PublicKeyOfSenderWallet.first)+to_string(this->PublicKeyOfRecieverWallet.first)+to_string(this->AmountSent)+to_string(this->Signature); 
               this->TxHash=Hash(TxString);

            }

            // void SetStatus(bool status)
            // {
            //     this->isVerified=status;
            // }



};

#endif
