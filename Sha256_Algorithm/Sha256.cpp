#include<iostream>
#include<cstring>
#include<cassert>
using namespace std;

uint32_t RotateRight(uint32_t x, size_t numOfBitsToBeShifted)
{
    return (x >> numOfBitsToBeShifted) | (x << (32-numOfBitsToBeShifted));
}

uint32_t ShiftRight(uint32_t x , size_t numOfBitsToBeShifted)
{
     return x >> numOfBitsToBeShifted  ;
}

uint32_t Choice(uint32_t x , uint32_t y , uint32_t z) // if a bit in x has a value of "1" the resulting bit will have the value y has at that position , else if the value is "0" the result will take the value of z at that place
{
    return (x & y) ^ (~x & z);
}


uint32_t Majority(uint32_t x , uint32_t y , uint32_t z) // the result takes the bit which occurs more frequently among x,y,z . such as [x0=1,y0=1,z0=0]=>[res0=0];
{
   return (x & y) ^ (x & z) ^ (y & z);
}


uint32_t Epsilon0(uint32_t x)
{
    return RotateRight(x, 2) ^ RotateRight(x, 13) ^ RotateRight(x, 22);
}


uint32_t Epsilon1(uint32_t x) 
{
    return RotateRight(x, 6) ^ RotateRight(x, 11) ^ RotateRight(x, 25);
}


uint32_t Sigma0(uint32_t x)
{
    return RotateRight(x, 7) ^ RotateRight(x, 18) ^ ShiftRight(x, 3);
}


uint32_t Sigma1(uint32_t x) 
{
    return RotateRight(x, 17) ^ RotateRight(x, 19) ^ ShiftRight(x, 10);
}

uint32_t swapE32(uint32_t value) {
    uint32_t x = value;
    x = (x & 0xffff0000) >> 16 | (x & 0x0000ffff) << 16;
    x = (x & 0xff00ff00) >>  8 | (x & 0x00ff00ff) <<  8;
    return x;
}

uint64_t swapE64(uint64_t value) {
    uint64_t x = value;
    x = (x & 0xffffffff00000000) >> 32 | (x & 0x00000000ffffffff) << 32;
    x = (x & 0xffff0000ffff0000) >> 16 | (x & 0x0000ffff0000ffff) << 16;
    x = (x & 0xff00ff00ff00ff00) >>  8 | (x & 0x00ff00ff00ff00ff) <<  8;
    return x;
}

string hexOutput(void* buffer, size_t len)
 {
    string hexString;

    for(size_t i = 0; i < len; i++) 
    {
        char buf[3];
        sprintf(buf, "%02x", ((char*)buffer)[i] & 0xff);
        hexString += buf;
    }

    return hexString;
}

string PreProcess(string input)
{
   size_t inputLength = input.length();
   uint64_t inputBitLength = inputLength * sizeof(char) * 8 ;
   size_t  bitsToBePadded = ( 448 - inputLength - 1) % 512;
   if(bitsToBePadded < 0) bitsToBePadded+=512;

   size_t ProcessedStringSize = inputBitLength + 1 + bitsToBePadded + 64 ;

  // assert(ProcessedStringSize % 512 == 0);

   string processedString(ProcessedStringSize / 8 , 0);
   memcpy( &processedString[0] , &input[0] , inputLength );
   processedString[inputLength] = 0x80 ;
   inputBitLength = swapE64 (inputBitLength) ;
   memcpy(&processedString[inputLength+1] ,&inputBitLength , 8);

   return processedString ;


}


string Hash(string input)
{
   return PreProcess(input);
}