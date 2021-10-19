#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	    cout << "Usage: ./decipher <file>"<<endl;
	    cout << "Examples:" << endl;
	    cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	    cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	/************* You complete *************/
    
    //Opening message file and storing as secret
    ifstream secret(argv[1]);
    if (secret.fail()) {
        cout << "Error opening file..." << endl;
        return -1;
    }
    
    //Extracting base, exponent, and modulus
    int base; string d_string; string n_string;
    secret >> base >> d_string >> n_string;
    if (secret.fail()) {
        cout << "Error extracting data members..." << endl;
        return -1;
    }
    
    string code;
    while (secret >> code) {

        //Finding int base 10 value of code
        int message_holder;
        try {
            BigInt d(d_string, base);
            BigInt n(n_string, base);            
            BigInt line_code(code, base);
            line_code = modPow(line_code, d, n);
            message_holder = line_code.to_int();
        }
        catch(const exception& e) {
            cout << e.what() << endl;
            return -1;
        }
        
        cout << (char)(message_holder);
        
    }
    
    cout << endl;
 
	return 0;
}
