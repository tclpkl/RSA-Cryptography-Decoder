#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

// Declaring helper functions
long int modular_exponentiation(std::string b_string, long int n, long int m);
long int decryption_key(long int p, long int q);
long int extended_euclidian_algorithm_for_d(long int e, long int l);

int main(int argc, char** argv) {

    const int e = 65537;
    // Setting e as constant and reading in p and q
    std::string par_1 = argv[1];
    const long int p = std::stoi(par_1);
    std::string par_2 = argv[2];
    const long int q = std::stoi(par_2);
    int d = decryption_key(p, q);
    // Checking if l was smaller than or equal to e
    if (d == -1) {
        std::cout << "L is smaller than e" << std::endl;
        return 0;
    }

    // Runs while user input contains "ENCRYPT" or "DECRYPT"
    std::string input;
    getline(std::cin, input);
    while (input.substr(0, 7) == "DECRYPT" || input.substr(0, 7) == "ENCRYPT") {

        // Putting contents into stringstream
        std::stringstream ss(input);
        std::string throw_away;
        ss >> throw_away;

        // If Decrypting
        if (input.substr(0, 7) == "DECRYPT") {

            // Storing relevant command line information
            std::string input_file;
            std::string output_file;
            ss >> input_file >> output_file;
            // Checking valid input
            if (ss.fail()) {
                std::cout << "Invalid input" << std::endl;
                return 0;
            }

            // Opening input file
            std::ifstream open_file;
            open_file.open(input_file);

            // Creaing output file
            std::ofstream create_file;
            create_file.open(output_file);

            // Dict to map value to character
            std::map<std::string, char> map;
            map["00"] = ' ';
            map["01"] = 'a';
            map["02"] = 'b';
            map["03"] = 'c';
            map["04"] = 'd';
            map["05"] = 'e';
            map["06"] = 'f';
            map["07"] = 'g';
            map["08"] = 'h';
            map["09"] = 'i';
            map["10"] = 'j';
            map["11"] = 'k';
            map["12"] = 'l';
            map["13"] = 'm';
            map["14"] = 'n';
            map["15"] = 'o';
            map["16"] = 'p';
            map["17"] = 'q';
            map["18"] = 'r';
            map["19"] = 's';
            map["20"] = 't';
            map["21"] = 'u';
            map["22"] = 'v';
            map["23"] = 'w';
            map["24"] = 'x';
            map["25"] = 'y';
            map["26"] = 'z';

            // Reading in all C's from input file and decrypting them and then outputting into output file
            long int c;
            while (open_file >> c) {
                // Decrypting C to M
                std::string m = std::to_string(modular_exponentiation(std::to_string(c), d, p * q));
                // Checking for leading 0
                if (m.size() % 2 == 1) {
                    m = "0" + m;
                }
                // Converting M to letters and spaces and outputing into output file
                for (int i = 0; i < int(m.size()); i += 2) {
                    char character = map[m.substr(i, 2)];
                    create_file << character;
                }
            }
            open_file.close();
            create_file.close();
        }

        // If Encrypting
        if (input.substr(0, 7) == "ENCRYPT") {

            // Storing relevant command line information
            std::string output_file;
            long long int n;
            std::string message;
            ss >> output_file >> n;
            // Finding substring of ss that includes only message
            int space_counter = 0;
            message = ss.str();
            while (space_counter < 3) {
                for (int i = 0; i < int(message.size()); i += 1) {
                    if (message[i] == ' ') {
                        space_counter += 1;
                        message = message.substr(i + 1);
                        break;
                    }
                }
            }
            // Checking valid input
            if (ss.fail()) {
                std::cout << "Invalid input" << std::endl;
                return 0;
            }

            // Creating output file
            std::ofstream file;
            file.open(output_file);

            // ENCRYPTION STEPS
            // Finding x
            if (n < 27) {
                std::cout << "n value is too small" << std::endl;
                return 0;
            }
            int x = 1 + (log10(n / 27) / 2);

            // Dict to map character to value
            std::map<char, std::string> map;
            map[' '] = "00";
            map['a'] = "01";
            map['b'] = "02";
            map['c'] = "03";
            map['d'] = "04";
            map['e'] = "05";
            map['f'] = "06";
            map['g'] = "07";
            map['h'] = "08";
            map['i'] = "09";
            map['j'] = "10";
            map['k'] = "11";
            map['l'] = "12";
            map['m'] = "13";
            map['n'] = "14";
            map['o'] = "15";
            map['p'] = "16";
            map['q'] = "17";
            map['r'] = "18";
            map['s'] = "19";
            map['t'] = "20";
            map['u'] = "21";
            map['v'] = "22";
            map['w'] = "23";
            map['x'] = "24";
            map['y'] = "25";
            map['z'] = "26";
            // While string is not finished being read
            int counter = 0;
            while (counter < int(message.size())) {
                // Looping through x letters
                std::string m = "";
                for (int i = 0; i < x; i += 1) {
                    // If counter alr reached end of message
                    if (counter == int(message.size())) {
                        // Fills remaining x amount of integers with 00's
                        for (int j = i; j < x; j += 1) {
                            m += map[' '];
                        }
                        break;
                    }
                    // Mapping character to integer and concantenating to m
                    m += map[message[counter]];
                    // Increasing character counter
                    counter += 1;
                }

                // Modular exponentiation;
                long int c = modular_exponentiation(m, e, n);
                file << c << " ";
            }
            file.close();
        }

        // Reading in next command
        getline(std::cin, input);
    }
    return 0;
};

// Implementing modular exponentiation
long int modular_exponentiation(std::string b_string, long int n, long int m) {
    // Storing b_string as long int
    long int b = std::stol(b_string);
    // Converting n to its binary form stored in a vector
    std::vector<int> n_binary;
    while (n != 0) {
        n_binary.push_back(n % 2);
        n /= 2;
    }

    // Modular exponentiation steps
    int x = 1;
    long long int power = b % m;
    for (int i = 0; i < int(n_binary.size()); i += 1) {
        if (n_binary[i] == 1) {
            x = (x * power) % m;
        }
        power = (power * power) % m;
    }

    return x;
}

// Implementing decryption function to use at program start
long int decryption_key(long int p, long int q) {

    // Finding gcd of (p-1), (q-1)
    long int x;
    long int y;
    // Storing larger of the two in x and smaller in y
    if (p > q) {
        x = p - 1;
        y = q - 1;
    } else {
        x = q - 1;
        y = p - 1;
    }
    // Implementing euclidian algorithm
    while (y != 0) {
        long int r = x % y;
        x = y;
        y = r;
    }
    int gcd = x;

    // Computing L
    long int l = (p - 1) * (q - 1) / gcd;
    // Checking if L is less than or equal to e
    if (l <= 65537) {
        return -1;
    }

    // Finding d through extended euclidian algorithm
    long int d = extended_euclidian_algorithm_for_d(65537, l);
    // Correcting d if negative
    if (d < 0) {
        d += (p - 1) * (q - 1);
    }

    return d;
}

// Implementinng Extended Euclidian algorithm to use in decryption key function
long int extended_euclidian_algorithm_for_d(long int e, long int l) {

    // Step 1
    int s = 0;
    int old_s = 1;
    // Step 2
    int t = 1;
    int old_t = 0;
    // Step 3;
    int r = e;
    int old_r = l;

    // Repeats steps 4-13 while r != 0
    while (r != 0) {
        // Step 4
        int quotient = old_r / r;
        // Step 5
        int temp = r;
        // Step 6
        r = old_r - quotient * r;
        // Step 7
        old_r = temp;
        // Step 8
        temp = s;
        // Step 9
        s = old_s - quotient * s;
        // Step 10
        old_s = temp;
        // Step 11
        temp = t;
        // Step 12
        t = old_t - quotient * t;
        // Step 13
        old_t = temp;
    }

    return old_t;
}