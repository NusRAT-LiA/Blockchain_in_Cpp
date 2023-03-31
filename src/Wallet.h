#include<bits/stdc++.h>
#ifndef WALLET_h
#define WALLET_h
#include "Transaction.h"
#include "Eliptic_Curve_Cryptography/ElipticCurve.h"
#include "Eliptic_Curve_Cryptography/Entity.h"
#include "Eliptic_Curve_Cryptography/Point.h"
#include "Eliptic_Curve_Cryptography/GeneratePoint.h"

using namespace std;

class Wallet{

    private :
       int Balance ;

    public :
       Entity WalletOwner;


};

#endif