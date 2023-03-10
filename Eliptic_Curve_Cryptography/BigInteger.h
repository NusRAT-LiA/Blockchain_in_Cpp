#include<bits/stdc++.h>

using namespace std ;

class BigInteger {
    private:
        char* digits;
        int size;
        bool isNegative;
    
    public:
       

        BigInteger(string num) {
            if (num[0] == '-') {
                isNegative = true;
                num = num.substr(1);
            } else {
                isNegative = false;
            }
            size = num.length();
            digits = new char[size];
            for (int i = 0; i < size; i++) {
                digits[i] = num[i];
            }
        }

     string toString()
      {
            string result = "";
             if (isNegative) {
                result += "-";
            }
            
            for (int i = size - 1; i >= 0; i--) {
                result += digits[i];
            }
           
            return result;
        }

        string add(BigInteger num) {
            string num1 = this->toString();
            string num2 = num.toString();
            string result;
            int carry = 0;
            int tempSum = 0;
            int i = 0;
            int n1 = num1.size();
            int n2 = num2.size();

            // Ensure that num1 is the longer string
            if (n1 < n2) {
                swap(num1, num2);
                swap(n1, n2);
            }

            // Resize result string to fit the sum of num1 and num2
            result.resize(n1);

            while (i < n1) {
                if (i < n2) {
                    tempSum = num1[i] - '0' + num2[i] - '0' + carry;
                    tempSum+=carry;
                    carry = 0;

                    if (tempSum > 9) {
                        result[i] = tempSum - 10 + '0';
                        carry = 1;
                    } else {
                        result[i] = tempSum + '0';
                    }
                } else {
                    tempSum = num1[i] - '0';
                    tempSum+=carry;
                    carry = 0;

                    if (tempSum > 9) {
                        result[i] = tempSum - 10 + '0';
                        carry = 1;
                    } else {
                        result[i] = tempSum + '0';
                    }
                }
                i++;
            }

            
             reverse(result.begin(), result.end());

            return result;
        }

         string subtract(BigInteger num) {
    string num1 = this->toString();
    string num2 = num.toString();
    string result;
    int borrow = 0;
    int tempDiff = 0;
    int i = 0;
    int n1 = num1.size();
    int n2 = num2.size();
    bool flag;

    // Ensure that num1 is the longer string
    if (n1 < n2) {
        flag=1;
        swap(num1, num2);
        swap(n1, n2);
    }

    // Resize result string to fit the difference of num1 and num2
    result.resize(n1);

    while (i < n1) {
        if (i < n2) {
            tempDiff = num1[i] - num2[i] - borrow;
            borrow = 0;

            if (tempDiff < 0) {
                result[i] = tempDiff + 10 + '0';
                borrow = 1;
            } else {
                result[i] = tempDiff + '0';
            }
        } else {
            tempDiff = num1[i] - '0';
            tempDiff -= borrow;
            borrow = 0;

            if (tempDiff < 0) {
                result[i] = tempDiff + 10 + '0';
                borrow = 1;
            } else {
                result[i] = tempDiff + '0';
            }
        }
        i++;
    }

    // Remove leading zeros from result
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    // If result is negative, add '-' sign
    if (borrow == 1) {
        result += '-';
    }

    if(flag==1)
     result += '-';

     // Reverse result string
    reverse(result.begin(), result.end());

    return result;
}

 string multiply(BigInteger num) {
    string num1 = this->toString();
    string num2 = num.toString();

    int n1 = num1.size();
    int n2 = num2.size();

    // allocate memory for result
    char* result = new char[n1 + n2];
    for (int i = 0; i < n1 + n2; i++) {
        result[i] = 0;
    }

    // multiply each digit and store in result
    int carry = 0;
    for (int i = 0; i < n1; i++) {
        carry = 0;
        int digit1 = num1[i] - '0';
        for (int j = 0; j < n2; j++) {
            int digit2 = num2[j] - '0';
            int sum = digit1 * digit2 + result[i + j] + carry;
            carry = sum / 10;
            result[i + j] = sum % 10;
        }
        if (carry > 0) {
            result[i + n2] += carry;
        }
    }

    // convert result to string
    string resultString = "";
    for (int i = n1 + n2 - 1; i >= 0; i--) {
        if (result[i] > 0 || resultString.size() > 0) {
            resultString += (char)(result[i] + '0');
        }
    }
    if (resultString.size() == 0) {
        resultString = "0";
    }
    delete[] result;
    return resultString;
}


        // Other methods (arithmetic operations, comparison operators, shift operators) go here
};

