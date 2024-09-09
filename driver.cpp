// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "tokenize.h"
#include <vector>
#include <sstream>


int main(){
    
    std::string command = " ";

    //variable used to run a while loop that runs till program is over
    bool program_run = true;

    //variables used for function intake
    std::string word_input;
    unsigned int size_input;
    int k_input;
    std::vector<std::string> words_input;
    //unsigned int token_input;
    std::vector<unsigned int> tokens_input;

    //creating object for HashTable header file
    HashTable HashTableobject;

    while (program_run){
        std::cin >> command;

        if (command == "create"){
            std::cin >> size_input;
            HashTableobject.create(size_input);
        }else if (command == "insert"){
            std::cin >> word_input;
            HashTableobject.insert(word_input, true);
        }else if  (command == "exit"){
            program_run = false;
        }else if (command == "print"){
            std::cin >> k_input;
            HashTableobject.print(k_input);
        }else if (command == "tok"){
            std::cin >> word_input;
            HashTableobject.tok(word_input);
        }else if (command == "ret"){
            std::cin >> size_input;
            HashTableobject.ret(size_input);
        }else if (command == "tok_all"){
            //getting all words divided by space into one vector
            std::getline(std::cin, word_input);
            std::istringstream iss (word_input);
            std::string single_word;

            while (iss >> single_word){
                words_input.push_back(single_word);
            };

            HashTableobject.tok_all(words_input);
            words_input.clear();
        }else if (command == "ret_all"){
            
            //getting all tokens divided by space into one vector
            std::getline(std::cin, word_input);
            std::istringstream iss (word_input);
            unsigned int single_token;

            while (iss >> single_token){
                tokens_input.push_back(single_token);
            };

            HashTableobject.ret_all(tokens_input);
            tokens_input.clear();
        }else if (command == "load"){
            std::cin >> word_input;
            HashTableobject.load (word_input);
        };
    };
    
    return 0;
};