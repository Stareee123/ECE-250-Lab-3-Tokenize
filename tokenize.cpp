#include "tokenize.h"
#include <iostream>
#include <vector>
#include <forward_list>
#include <fstream>

unsigned HashTable::hash (const std::string & str){
    unsigned ans = 0;
    for (auto it = str.begin(); it != str.end(); ++it){
        ans = ans * 29 + *it;
    };

    return ans % hash_size;
};

void HashTable::create (unsigned int size){

    //redefine hash table size and the number of elements in the dictionary
    hash_size = size;
    word_size = 0;

    //create forward_list with size elements as a dictionary
    dictionary = new std::forward_list<Node> [size];

    //output success
    std::cout << "success" << std::endl;
};

//function load that takes string input for a file name.
//it will open the file just as in lab 2, interate through every values in the file divided by space, and put it into the insert function.
//bool load_success is used to print out success if one or more word has been inserted successfully
void HashTable::load (const std::string& filename){
    load_success = false;
    std::string word;
    std::ifstream file;
    file.open(filename);

    while (!file.eof()){
        file >> word;

        insert(word, false);
    };

    if (load_success){
        std::cout << "success" << std::endl;
    }else{
        std::cout << "failure" << std::endl;
    };
};


//helper function of insert function. 
//This function will loop for every characters in the given string and check rather there is non-alphabet in it using std::isalpha from piazza
//Returns false if there is non-alphabet character in the input string
bool HashTable::checkalpha (const std::string& str){
    for (char c : str){
        if (std::isalpha(c) == false){
            return false;
        };
    };

    return true;
};

//helper function of insert function.
void HashTable::rehash (){

    //creating new dictionary with double the original size
    unsigned int new_size = hash_size * 2;
    std::forward_list<Node>* new_dictionary = new std::forward_list<Node> [new_size];
    std::forward_list<Node>* delete_dictionary = dictionary;

    hash_size = new_size;

    //looping through every elements and nodes in the original dictionary and reallocating it to new_dictionary to the position given in the hash function
    for (unsigned int i = 0; i < (hash_size/2); ++i){
        for (const Node& node : dictionary[i]){
            unsigned int a = hash (node.key);
            new_dictionary [a].push_front(node);
        };
    };

    
    //deleting old dictionary to remove memory leak
    dictionary = new_dictionary;
    delete[] delete_dictionary;
};

//insert function
void HashTable::insert (const std::string& word, bool print){

    //computing the location in dictionary using hash function
    unsigned int i = hash (word);


    //getting the boolean value that indicates rather input fully made by alphabet
    bool alpha = checkalpha (word);

    if (alpha){
        
        //check rather i th element is empty
        if (dictionary[i].empty()){

            //if i is empty, it is certain that we will add this word
            word_size = word_size + 1;

            //check rather we need rehashing or not
            double load_factor = static_cast<double> (word_size) / hash_size;
            if (load_factor > 0.8){
                rehash();
                i = hash(word);
            };

            //pushing word into the list_of_word vector
            list_of_word.push_back(word);

            //adding new node with key, value 
            Node adder (word, word_size);
            dictionary [i].push_front(adder);

            //?? might need to delete adder for memory leak
            if (print){
                std::cout << "success" << std::endl;
            };

            load_success = true;

        } else {     //if ith element is not empty

            //looping through all nodes in ith index of dictionary to check for the duplicate
            for (const Node& node : dictionary[i]){
                if (node.key == word){
                    if (print){
                        std::cout << "failure" << std::endl;
                    };
                    return;
                };
            };

            //same inserting algorithm as above
            word_size = word_size + 1;

            double load_factor = static_cast<double> (word_size) / hash_size;
            if (load_factor > 0.8){
                rehash();
                i = hash(word);
            };

            list_of_word.push_back(word);

            Node adder (word, word_size);
            dictionary [i].push_front(adder);

            
            if (print){
                std::cout << "success" << std::endl;
            };

            load_success = true;
        };
    }else{
        if (print){
            std::cout << "failure" << std::endl;
        };
    };
};


//tok function
void HashTable::tok (const std::string& word){
    unsigned int i = hash(word);

    //if the ith element in the dictionary array is empty, print out -1.
    if (dictionary[i].empty()){
        std::cout << "-1" << std::endl;
    }else{
    //if the ith element in the dictionary array is not empty, check for the node.key values in the place.
        for (const Node& node : dictionary [i]){

            //if there is a node with same key value, print out the token value and end the function.
            if (node.key == word){
                std::cout << node.value << std::endl;
                return;
            };
        };

        //if the ith element is not empty but does not contains the word
        std::cout << "-1" << std::endl;
    };
};


//ret funciton
void HashTable::ret (unsigned int token){

    //if input value is greater than the number of total words in the table, return N/A and exit the function
    if (token > word_size){
        std::cout << "N/A" << std::endl;
        return;
    };

    std::string get_word = list_of_word [token-1];

    std::cout << get_word << std::endl;
    
};


//tok_all function
void HashTable::tok_all (const std::vector<std::string>& words){

    //looping through every single words in the input
    for (const auto& str : words){
        unsigned int i = hash(str);

        //setting a bool value that will be used to determine rather input is found or not
        bool find = false;

        //same algorithm as tok function
        if (dictionary[i].empty()){
            std::cout << "-1 ";
        }else{
            for (const Node& node : dictionary[i]){
                if (node.key == str){
                    std::cout << node.value << " ";
                    find = true;
                };
            };

            if (find == false){
                std::cout << "-1 ";
            };
        };
    };

    std::cout << std::endl;
};


//ret_all function
void HashTable::ret_all (const std::vector<unsigned int>& tokens){

    //looping through every single tokens in the input
    for (const auto& str : tokens){

        //same algorithm as ret function
        if (str > word_size){
            std::cout << "N/A ";
        }else{
            std::string get_word = list_of_word [str - 1];
            std::cout << get_word << " ";
        };
    };
    std::cout << std::endl;
};


//print function
void HashTable::print(unsigned int k){

    //print nothing if input k is not legit
    if(k >= hash_size){
        return;
    };
    
    //if input k is legit, print the key of all nodes in the kth place in the dictionary
    for (const auto& node : dictionary[k]){
        std::cout << node.key << " ";
    };

    std::cout << std::endl;
};




//test function not a part of the project
// void HashTable::printall(){
//     for (unsigned int i = 0; i < hash_size; ++i){
//         for (const auto& node : dictionary[i]){
//             std::cout << node.key << node.value << " ";
//         };
//     };

//     std::cout << std::endl;

//     std::cout << word_size << " " << hash_size << std::endl;
// }