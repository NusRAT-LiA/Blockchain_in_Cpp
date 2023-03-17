#include<bits/stdc++.h>
using namespace std ;
// Function to convert an integer to a binary string
string toBinaryString(int n) {
    if (n == 0) {
        return "0"; // Special case for 0
    }

    string binary = ""; // Initialize an empty string to hold the binary digits

    while (n > 0) {
        int bit = n % 2; // Extract the least significant bit
        binary = to_string(bit) + binary; // Prepend the bit to the binary string
        n /= 2; // Shift the integer right by 1 bit
    }

    return binary; // Return the binary string
}


int main()
{
   long long int m=10;
   cout<<toBinaryString(m);
   
}