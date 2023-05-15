#include<bits/stdc++.h>
#ifndef ENTITY_H
#define ENTITY_H
#include"Point.h"
#include"ElipticCurve.h"
#include"../Sha256_Algorithm/Sha256.h"
using namespace std;

class Entity{
     
     private :
        
        string EntityName;            // Entity name
        long long int PrivateKey;     // Entity's private key   
        Point SecretKey;              // Shared secret key
        ElipticCurve ElipticCurv;     // Eliptical curve used to generate keys

    public :
        
        Point PublicKey;              // Entity's public key

       
        Entity(string EN , ElipticCurve EC)
        {
            EntityName=EN;
            PrivateKey=0;
            ElipticCurv=EC;
        }

        Entity(){} 

      
        // Function to find y-coordinate of a point on elliptical curve given the x-coordinate
        int FindY(int RHS)
        {
            for (int i = 1; i < ElipticCurv.GetRangeC(); i++)
            {   
                // Check if the square of 'i' modulo the range of the curve is equal to RHS
                if ((i * i) % ElipticCurv.GetRangeC() == RHS)
                {
                    return i;
                }
            }
            return 0;
        }

        // Function to generate entity's private and public keys
        void PrivateKeyGeneration()
        {   
            // Generate a random private key for the wallet
            // The private key is a random value within the range of the elliptic curve plus 2
            PrivateKey = rand() % ElipticCurv.GetRangeC() + 2;
            cout<<"Rremember "<<this->EntityName<<"'s  Private Key to verify transactions requested from this  wallet !!  : "<<PrivateKey<<endl;
        }

        void PublicKeyGeneration( Point G)
        {   
            // Compute the public key by performing point multiplication on the base point 'G'
            // using the private key and the parameters of the elliptic curve
            this->PublicKey=Point :: pointMultiplication(G,PrivateKey, ElipticCurv.GetRangeC(), ElipticCurv.GetA());
        }

       

        bool isEnityValid(long long int PrivKey)
        {
           if(this->PrivateKey==PrivKey)return true;
           return false;
        }

        string EntityAdress()
        {
            string addressString=to_string(this->PublicKey.getX())+to_string(this->PublicKey.getY())+this->EntityName+to_string(this->PrivateKey);
            return Hash(addressString);
        
        }
        
       
};
#endif