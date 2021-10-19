#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

/*
//   Create a default BigInt with base 10.
*/
BigInt::BigInt(){

    /******** You complete ****************/
    base = 10;
    isPositive = true;
    
}

/*
//  Create a BigInt with a specified base.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    base = setbase;
    isPositive = true;
}

/*
//  Create a BigInt from int (base 10) with a specified base.
//  Here you would convert an int (base 10) into a specified base.
//  e.g., (10,2) <-- 10 base 10 to base 2 --> result:  BigInt with value 1010 base 2
//  e.g., (100,16) <--- 100 base 10 to base 16 --> result: BigInt with value 64 base 16
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/\
    //Checks if negative
    if (input < 0) {
        input = input * -1;
        isPositive = false;
    }
    else {
        isPositive = true;
    }
    base = setbase;
    
    //Fills vector with int in base form
    while (input != 0) {
        int remainder = input % base;
        vec.push_back(remainder);
        input /= base;
    }
}

/*
//  Create a BigInt from string with a specified base.
//  You can assume that the string number input is in the same
//      base as the setbase input.
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    //Checking if negative
    string s_copy = s;
    if (s_copy[0] == '-') {
        s_copy.erase(0, 1);
        isPositive = false;
    }
    else {
        isPositive = true;
    }
    base = setbase;
    
    //Iterating through characters and filling vec with int form
    for (int i = s_copy.size() -1; i >= 0; i -= 1) {
        if ((s_copy[i] - '0') < 10) {
            vec.push_back(s_copy[i] - '0');
        }
        else if (s_copy[i] == 'A') {vec.push_back(10);}
        else if (s_copy[i] == 'B') {vec.push_back(11);}
        else if (s_copy[i] == 'C') {vec.push_back(12);}
        else if (s_copy[i] == 'D') {vec.push_back(13);}
        else if (s_copy[i] == 'E') {vec.push_back(14);}
        else if (s_copy[i] == 'F') {vec.push_back(15);}
        else if (s_copy[i] == 'G') {vec.push_back(16);}
    }
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply use the assignment operator.
*/
BigInt::BigInt(const BigInt &b){

    /************* You complete *************/
    *this = b;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}



/*
// Convert to string and return the string
//  Display it in its corresponding base
*/
string BigInt::to_string(){

    /************* You complete *************/
    string number = "";
    //Checking if vector is empty
    if (vec.size() == 0) {
        return "0";
    }
    
    //Checking if negative
    if (isPositive == false) {
        number.push_back('-');
    }
    
    //Iterating through vector and adding to string number
    for (int i = vec.size() - 1; i >= 0; i -= 1) {
        if (vec[i] < 10) {
            number.push_back(vec[i] + '0');
        }
        else if (vec[i] == 10) {number.push_back('A');}
        else if (vec[i] == 11) {number.push_back('B');}
        else if (vec[i] == 12) {number.push_back('C');}
        else if (vec[i] == 13) {number.push_back('D');}
        else if (vec[i] == 14) {number.push_back('E');}
        else if (vec[i] == 15) {number.push_back('F');}
        else if (vec[i] == 16) {number.push_back('G');}
    }

  return number;
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt > INT_MAX, return INT_MAX.
//    If BigInt < INT_MIN, return INT_MIN.
*/
int BigInt::to_int() const{

    /************* You complete *************/
    long long int total = 0;
    
    //Converting BigInt to base 10 and assigning to total
    for (int i = 0; i < (int)vec.size(); i += 1) {
       total += (vec[i] * pow(base, i));
    }
    
    if (isPositive == false) {
       total *= -1;
    }
    
    if (total > INT_MAX) {
       total = INT_MAX;
    }
    
    if (total < INT_MIN) {
       total = INT_MIN;
    }
    
    return (int)total;
}

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    if (isPositive == false && b.isPositive == true) {
        return -1;
    }
    else if (isPositive == true && b.isPositive == false) {
        return 1;
    }
    else if (isPositive == true && b.isPositive == true) {
        if (vec.size() > b.vec.size()) {
            return 1;
        }
        else if (vec.size() < b.vec.size()) {
            return -1;
        }
        else {
            for (int i = (int)(vec.size() -1); i >= 0; i -=1) {
                if (vec[i] > b.vec[i]) {
                    return 1;
                }
                else if (vec[i] < b.vec[i]) {
                    return -1;
                }
            }
            return 0;
        }
    }
    else {
        if (vec.size() > b.vec.size()) {
            return -1;
        }
        else if (vec.size() < b.vec.size()) {
            return 1;
        }
        else {
            for (int i = vec.size() - 1; i >= 0; i -= 1) {
                if (vec[i] > b.vec[i]) {
                    return -1;
                }
                else if (vec[i] < b.vec[i]) {
                    return 1;
                }
            }
            return 0;
        }
    }
    return 0;
}



/*
//  Assignment operator. (i.e., BigInt a = b;)
*/
const BigInt & BigInt::operator = (const BigInt &b){

    /************* You complete *************/
    isPositive = b.isPositive;
    vec = b.vec;
    base = b.base;

    return *this;//for now
}

/*
//  Addition assignment operator.
//    - Compute a = a + b.
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    
    //When same sign
    if (isPositive == b.isPositive) {      
        //Creating temp variables to store values
        int vec_temp; int b_temp; int size;
        //If a vec size greater than or equal to b vec size
        if (vec.size() >= b.vec.size()) {
            size = (int)(vec.size());
            for (int i = 0; i < size; i += 1) {
                vec_temp = vec[i];
                //Elements outside of b vector size are set to 0
                if (i < (int)b.vec.size()) {b_temp = b.vec[i];}
                else {b_temp = 0;}
                //Adding values
                vec[i] = vec_temp + b_temp;
                //Implementing carry over
                if (vec[i] >= base) {
                    vec[i] -= base;
                    if (i != size - 1) {       
                        vec[i + 1] += 1;
                    }
                    else if (i == size - 1) {
                        vec.push_back(1);
                    }
                }
            }
        }
        
        //If a vec size smaller than b vec size
        else {
            //Storing original a in temp
            //Assigning b to a
            BigInt biginttemp = *this;
            *this = b;
            size = (int)(b.vec.size());
            for (int i = 0; i < (int)b.vec.size(); i += 1) {
                vec_temp = vec[i];
                //Elements outside of b vector size are set to 0
                if (i < (int)biginttemp.vec.size()) {b_temp = biginttemp.vec[i];}
                else {b_temp = 0;}
                //Adding values
                vec[i] = vec_temp + b_temp;
                //Implementing carry over
                if (vec[i] >= base) {
                    vec[i] -= base;
                    if (i != size - 1) {       
                        vec[i + 1] += 1;
                    }
                    else if (i == size - 1) {
                        vec.push_back(1);
                    }
                }
            }
        }
    }


    //Not same sign
    else {
        if (isPositive == true) {
            BigInt biginttemp = b;
            biginttemp.isPositive = true;
            if (this->compare(biginttemp) >= 0) {
                *this -= biginttemp;
                isPositive = true;
            }
            else {
                *this -=biginttemp;
                isPositive = false;
            }
        }
        
        else if (isPositive == false) {
            isPositive = true;
            if (this->compare(b) >= 0) {
                *this -= b;
                isPositive = false;
                if (vec[0] == 0 && vec.size() == 1) {
                    isPositive = true;
                }
            }
            else {
                *this -= b;
                isPositive = true;
            }
        }
    }    


  return *this;
}


/*
//  Subtraction assignment operator.
//    - Compute a = a - b
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    
    //If same sign
    if (isPositive == b.isPositive) {      
        //Creating temp variables to store vec values
        int vec_temp; int b_temp; int size;
        
        //If |a|>=|b| and both positive
        if (this->compare(b) >= 0 && isPositive == true) {
            size = (int)(vec.size());
            for (int i = 0; i < size; i += 1) {
                vec_temp = vec[i];
                //Elements outside of b vector size are set to 0
                if (i < (int)b.vec.size()) {b_temp = b.vec[i];}
                else {b_temp = 0;}
                //Subtracting values
                vec[i] = vec_temp - b_temp;
                //Implementing borrowing
                if (vec[i] < 0) {
                    vec[i] += base;
                    vec[i + 1] -= 1;
                }
            }
            while (vec[vec.size()-1] == 0 && vec.size() > 1) {
                vec.pop_back();   
            }
        }
        
        //If |a|>=|b| and both negative
        else if (this->compare(b) <= 0 && isPositive == false) {
            size = (int)(vec.size());
            for (int i = 0; i < size; i += 1) {
                vec_temp = vec[i];
                //Elements outside of b vector size are set to 0
                if (i < (int)b.vec.size()) {b_temp = b.vec[i];}
                else {b_temp = 0;}
                //Subtracting values
                vec[i] = vec_temp - b_temp;
                //Implementing borrowing
                if (vec[i] < 0) {
                    vec[i] += base;
                    vec[i + 1] -= 1;
                }
            }
            while (vec[vec.size()-1] == 0 && vec.size() > 1) {
                vec.pop_back();   
            }              
        }
        
        //If |a|<|b| and both positive
        else if (this->compare(b) < 0 && isPositive == true) {
            //Storing original a in temp
            //Assigning b to a
            BigInt biginttemp = *this;
            *this = b;
            //Determining final sign
            isPositive = false;
            
            for (int i = 0; i < (int)vec.size(); i += 1) {
                vec_temp = vec[i];
                //Elements outside of b vector size are set to 0
                if (i < (int)biginttemp.vec.size()) {b_temp = biginttemp.vec[i];}
                else {b_temp = 0;}
                //Adding values
                vec[i] = vec_temp - b_temp;
                //Implementing borrowing
                if (vec[i] < 0) {
                    vec[i] += base;
                    vec[i + 1] -= 1;
                }
            }
            while (vec[vec.size()-1] == 0 && vec.size() > 1) {
                vec.pop_back();
            }
        }
        
        //If |a|<|b| and both negative
        else if (this->compare(b) > 0 && isPositive == false) {
            //Storing original a in temp
            //Assigning b to a
            BigInt biginttemp = *this;
            *this = b;
            //Determining final sign
            isPositive = true;
            
            for (int i = 0; i < (int)vec.size(); i += 1) {
                vec_temp = vec[i];
                //Elements outside of b vector size are set to 0
                if (i < (int)biginttemp.vec.size()) {b_temp = biginttemp.vec[i];}
                else {b_temp = 0;}
                //Adding values
                vec[i] = vec_temp - b_temp;
                //Implementing borrowing
                if (vec[i] < 0) {
                    vec[i] += base;
                    vec[i + 1] -= 1;
                }
            }
            while (vec[vec.size()-1] == 0 && vec.size() > 1) {
                vec.pop_back();
            }            
        }
        
    }
    
    //Not same sign
    else {
        if (isPositive == true) {
            BigInt biginttemp = b;
            biginttemp.isPositive = true;
            *this += biginttemp;
            isPositive = true;
        }
        else if (isPositive == false) {
            isPositive = true;
            *this += b;
            isPositive = false;
        }
    }

    if (vec[0] == 0 && vec.size() == 1) {
        isPositive = true;
    }

    return *this;
}

/*
//  Multiplication assignment operator.
//    - Compute a = a * b;
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    
    BigInt totalbigint("0", base);
    int carry = 0;
    //Iterating through each digit in b vector
    for (int i = 0; i < (int)b.vec.size(); i += 1) {
        //Creating buffer of zeroes and making BigInt to later push product onto
        string zero_buffer(i, '0');
        BigInt temp(zero_buffer, base);
        //Iterating through each digit in a vector
        for (int j = 0; j < (int)vec.size(); j += 1) {
            int product = b.vec[i] * vec[j] + carry;
            carry = 0;
            //Computing carry and number to add to temp
            while (product >= base) {
                product -= base;
                carry += 1;
            }
            temp.vec.push_back(product);
        }
        //Checking if there is final carry
        if (carry > 0) {
            temp.vec.push_back(carry);
        }
        //Adding temp to total
        totalbigint += temp;
        carry = 0;
    }
    
    //Assigning number to original a
    this->vec = totalbigint.vec;
    
    //Ridding excess zeroes
    while (vec[vec.size()-1] == 0 && vec.size() > 1) {
                vec.pop_back();
    }
    
    //Checking sign
    if (isPositive != b.isPositive){
        isPositive = false;
    }
    else {
        isPositive = true;
    }
    
    if (vec[0] == 0 && vec.size() == 1) {
        isPositive = true;
    }
    
    return *this;
}

/*
//  Division assignment operator.
//    - Call 'divisionMain' to compute a = a / b;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/
    
    BigInt quotient(base);
    BigInt remainder(base);
    this->divisionMain(b, quotient, remainder);
    
    *this = quotient;
  
    return *this;
}

/*
//  Modulus assignment operator.
//    - Call 'divisionMain' to compute a = a % b.
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/

    BigInt quotient(base);
    BigInt remainder(base);
    this->divisionMain(b, quotient, remainder);
    
    *this = remainder;
  
    return *this;
    
}

/*
//  Main function for the Division and Modulus operator.
//     - Compute (q)uotient and (r)emainder: a = (b * q) + r.
//     - Note: NO fraction. This should behave like integer division
//             where 2/10 = 0, not 0.2
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/
    //Making b_copy, changing signs positive, creating BigInt 0
    BigInt b_copy = b;
    b_copy.isPositive = true;
    BigInt zero("0", base);
    
    //Making initial smallest sequence that divisor can fit into
    int position = vec.size() - 1;
    BigInt seq(base);
    seq.vec.push_back(vec[position]);
    
    while (seq < b_copy && position > 0) {
        position -= 1;
        seq.vec.insert(seq.vec.begin(), vec[position]);
    }
    
    //Finding each number that makes up quotient
    while (position > -1) {
        int times = 0;
       
        //Finding how many times divisor goes into sequence
        while (seq >= b_copy) {
            seq -= b_copy;
            times += 1;
        }
        
        //If first digit of sequence is 0, we get rid of the 0
        if (seq == zero) {
            seq.vec.pop_back();
        }
        
        //Inserting quotient digits
        quotient.vec.insert(quotient.vec.begin(), times);
        
        if (position > 0) {
                seq.vec.insert(seq.vec.begin(), vec[position - 1]);
        }
        position -= 1;       
    }

    //Remainder is leftover sequence
    if (seq == zero) {
        remainder.vec.push_back(0);
        remainder.isPositive = true;
    }
    else {
        remainder = seq;
        remainder.isPositive = isPositive;
    }   
    //Determining sign
    if (quotient == zero) {
        quotient.isPositive = true;
    }
    else if (isPositive != b.isPositive) {
        quotient.isPositive = false;
    }

}

/*
//  Exponentiation assignment function.
//     - Compute a BigInt whose value is a = pow(a,b).
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/

    //Checking if b is 0 or 1
    BigInt zero("0", base);
    BigInt one("1", base);
    if (b == zero) {
        *this = one;
        return *this;
    }
    else if (b == one) {
        return *this;
    }
    
    //Making copy of b, BigInt 2, BigInt 1, BigInt result, and BigInt oddoneout
    BigInt b_copy = b;
    BigInt two("2", base);
    BigInt result = (*this);
    BigInt oddoneout = one;
    

    //Squaring algorithm
    while (b_copy != one) {
        //Odd
        if (b_copy.vec[0] % 2 == 1)  {
            b_copy -= one;
            oddoneout *= result;
        }
        //Dividing exponent by two and squaring internal
        result *= result;
        b_copy /= two;
    }
    

    
    *this = result * oddoneout;
    
    return *this;
}

/*
//  Modulus Exponentiation assignment function.
//     - Compute a = (a ^ b) % m.
//     - Do NOT compute a^b directly and then % m. 
//         This is too computationally expensive.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/

    //Checking if b is 0 or 1, or if base is 0
    BigInt zero("0", base);
    BigInt one("1", base);
    if (b == zero) {
        *this = one;
        return *this;
    }
    else if (b == one) {
        return (*this %= b);
    }
    else if (*this == zero) {
        *this = zero;
        return *this;     
    }
    
    
    //Making copy of b, BigInt 2, BigInt 1, BigInt result, and BigInt oddoneout
    BigInt b_copy = b;
    BigInt two("2", base);
    BigInt result = (*this);
    BigInt oddoneout = one;
    

    //Squaring algorithm
    while (b_copy != one) {
        //Odd
        if (b_copy.vec[0] % 2 == 1)  {
            b_copy -= one;
            oddoneout = oddoneout * (result % m);
        }
        //Dividing exponent by two and squaring internal
        result = (result * result) % m;
        b_copy /= two;
    }
   
    
    *this = (result * oddoneout) % m;

    return b;

}


//----------------------------------------------------
//* Operator overloading, non-member functions
//----------------------------------------------------


//Call the += function above to compute a BigInt whose value is a + b
BigInt operator + (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt a_copy = a;
  a_copy += b;
  
  return a_copy;
}
//Call the -= function above to compute a BigInt whose value is a - b
BigInt operator - (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt a_copy = a;
  a_copy -= b;  
    
  return a_copy;
}
//Call the *= function above to compute a BigInt whose value is a * b
BigInt operator * (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt a_copy = a;
    a_copy *= b; 
  
    return a_copy;
}

//Call the /= function above to compute a BigInt whose value is a / b
BigInt operator / (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
    BigInt a_copy = a;
    a_copy /= b;
 
    return a_copy;
}

//Call the %= function above to compute a BigInt whose value is a % b
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
    BigInt a_copy = a;
    a_copy %= b;
 
    return a_copy;
}
//Call the exponentiation function above to compute a BigInt whose value is pow(a,b)
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
    BigInt a_copy = a;
    a_copy.exponentiation(b);
    
    return a_copy;
}

//Call the modulusExp function above to compute a BigInt whose value is (a ^ b) mod c
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/
     
    BigInt a_copy = a;
    a_copy.modulusExp(b, m);
  
  
   return a_copy;
}

//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

  if (a.compare(b) == 0) {
      return true;
  }
  else {
      return false;
  }

}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

  if (a == b) {
      return false;
  }
  else {
      return true;
  }
  
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

    if (a.compare(b) == -1 || a.compare(b) == 0) {
        return true;
    }
    else {
        return false;
    }

}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

    if (a.compare(b) == 1 || a.compare(b) == 0) {
        return true;
    }
    else {
        return false;
    }

}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

    if (a.compare(b) == 1) {
        return true;
    }
    else {
        return false;
    }
  
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

    if (a.compare(b) == -1) {
        return true;
    }
    else {
        return false;
    }
  
}