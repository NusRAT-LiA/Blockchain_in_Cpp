#include <iostream>
#include "Point.h"
#include "ElipticCurve.h"
#include "Entity.h"

using namespace std;


// Function to generate the base point 'G' on the elliptic curve
Point GeneratePointG(Entity E, ElipticCurve EC)
{
    // Generate random x-coordinate within the range of the elliptic curve
    srand(time(0));
    long long int x = rand() % EC.GetRangeC() + 1;

    // Find y-coordinate corresponding to the x-coordinate
    long long int y = E.FindY(EC.CalcYsqrt(x));
	
    // Continue incrementing x until a non-zero y-coordinate is found
    while (y == 0 && x < EC.GetRangeC())
    {
        y = E.FindY(EC.CalcYsqrt(++x));
    }
	
    // Create and return the point G with the coordinates (x, y)
    Point G(x, y);
    return G;
}



// Function to create an elliptic curve
ElipticCurve CreateCurve()
{
    // Set the coefficients and range constant for the elliptic curve
    long long int a = 1009, b = 20056;
    long long int RangeConst = 559799;

    // Create an elliptic curve object with the specified coefficients and range constant
    ElipticCurve EC = ElipticCurve(a, b, RangeConst);
    return EC;
}



// Function to generate the public-private key pair for an entity
Entity generateKey(Entity newEntity, ElipticCurve EC)
{
    // Generate the base point 'G' on the elliptic curve
    Point G = GeneratePointG(newEntity, EC);

    // Generate a random private key for the entity
    srand(time(NULL));
    newEntity.PrivateKeyGeneration();

    // Generate the public key for the entity using the base point 'G' 
    newEntity.PublicKeyGeneration(G);

    return newEntity;
}
