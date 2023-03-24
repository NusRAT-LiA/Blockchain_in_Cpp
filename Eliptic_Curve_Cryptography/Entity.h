#include<bits/stdc++.h>
#include"Point.h"
#include"ElipticCurve.h"
using namespace std;

class Entity{
     
     private :
        
        char EntityName;              // Entity name
        long long int PrivateKey;     // Entity's private key   
        Point SecretKey;              // Shared secret key
        string Message;               // Message to be encoded and encrypted
        long long int *MsgAscii;      // Array to store the ASCII values of message characters 
        long long int MsgSize;        // size of the Message  
        ElipticCurve ElipticCurv;    // Eliptical cirve used to generate keys
        Point *Encoded ;              // Array to store encoded message points

    public :
        
        Point PublicKey;              // Entity's public key

        // Constructor to initialize Entity object with entity name and message
        Entity(char EN, string Msg)
        {
            EntityName = EN;
            PrivateKey = 0;
            Message = Msg;
        }

        // Function to convert message characters to ASCII values and store them in MsgAscii array
        void StringToAscii()
        {
            MsgSize = Message.length();
            MsgAscii = new long long int[MsgSize];

            for (int i = 0; i < Message.length(); i++)
            {
                MsgAscii[i] = Message[i];
            }
        }

        // Function to find y-coordinate of a point on elliptical curve given the x-coordinate
        int FindY(int RHS)
        {
            for (int i = 1; i < ElipticCurv.GetRangeC(); i++)
            {
                if ((i * i) % ElipticCurv.GetRangeC() == RHS)
                {
                    return i;
                }
            }
            return 0;
        }

        // Function to generate entity's private and public keys
        void KeyGeneration(ElipticCurve E, Point G)
        {
            ElipticCurv = E;
            PrivateKey = rand() % ElipticCurv.GetRangeC() + 2;
            PublicKey=Point :: pointMultiplication(G,PrivateKey, ElipticCurv.GetRangeC(), ElipticCurv.GetA());
        }

        // Function to encode message into points on elliptical curve
        void Encoding(ElipticCurve E, long long int k)
        {
            Encoded = new Point[MsgSize];
            ElipticCurv = E;
            for (int i = 0; i < MsgSize; i++)
            {
              Point P = Point::messageEncoding(Message[i],ElipticCurv.GetRangeC(),ElipticCurv.GetA(),ElipticCurv.GetB());
              Encoded[i]=P;
            }
        }

        // Function to perform key exchange and generate shared secret key
        void KeyExchang(Point PubKey)
        {
            SecretKey=Point :: pointMultiplication(PubKey,PrivateKey, ElipticCurv.GetRangeC(), ElipticCurv.GetA());
        }

        // Function to print entity's private and public keys, as well as the shared secret key
        void PrintKeys(string Name)
        {
            cout << "\n\t\t ****" << Name << ": Keys*****";
            cout << "\nPrivateKey= " << PrivateKey << endl << "PubkeyA= R( " << PublicKey.getX() << "," << PublicKey.getY() << ")\n";

        }

       
};
