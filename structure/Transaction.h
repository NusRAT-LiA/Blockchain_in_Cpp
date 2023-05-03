#include<bits/stdc++.h> // include all standard C++ headers
#ifndef TRANSACTION_H
#define TRANSACTION_H


#include "../Sha256_Algorithm/Sha256.h" // include header file for SHA256 hash function

using namespace std;

class Transaction
{
    private:
        bool isVerified = false; // flag indicating if transaction has been verified

    public:
        string TxHash; // hash of the transaction
        pair<long long int,long long int> PublicKeyOfSenderWallet; // public key of the sender's wallet
        pair<long long int,long long int> PublicKeyOfRecieverWallet; // public key of the receiver's wallet
        long long int AmountSent; // amount of currency being sent
        long long int Signature; // digital signature of the transaction
        int TxFee;

        bool operator==(const Transaction& other) const {
         return TxHash == other.TxHash;
         }
   

        // constructor for Transaction class
        Transaction(pair<long long int,long long int> SenderKey, pair<long long int,long long int> RecieverKey, int Amount, long long int Sign, int offeredFee)
        {
            this->PublicKeyOfSenderWallet = SenderKey;
            this->PublicKeyOfRecieverWallet = RecieverKey;
            this->AmountSent = Amount;
            this->Signature = Sign;

            // generate hash of transaction string
            string TxString = to_string(this->PublicKeyOfSenderWallet.first) + to_string(this->PublicKeyOfRecieverWallet.first) + to_string(this->AmountSent) + to_string(this->Signature); 
            this->TxHash = Hash(TxString);
            this->TxFee=offeredFee;
        }

        // setter function for isVerified flag
        // void SetStatus(bool status)
        // {
        //     this->isVerified = status;
        // }
};

#endif
