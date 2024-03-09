#include <bits/stdc++.h>
using namespace std;

bool inital_parse(string input_filename, map<string, int> &Label_map);

int main(){
    const string input_filename = "input.asm";
    const string output_filename = "output.mc";

    // A map to store the address of Labels with respect to PC
    map<string, int> Label_map;

    bool error = initial_parse(input_filename, Label_map);
    if (error)
        return 1;
    
    // Checking if all labels are present
    for (auto it = Label_map.begin(); it != Label_map.end(); ++it) {
        if (it->second == -1){
            cout << "Error: Didn't mention Label - " << it->first << endl;
            return 1;
        }
    }

    for (const auto& pair : Label_map) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}

// Auxiliary Functions 

string remove_leading_spaces(string input){
    size_t pos = input.find_first_not_of(' '); 
    if (pos != string::npos) {  
        input.erase(0, pos); 
    }
    return input;
}

string remove_trailing_spaces(string input){
    size_t pos = input.find_last_not_of(' ');
    if (pos != string::npos){
        input.erase(pos + 1);
    }
    return input;
}

vector<string> preprocess(string line){
    string word = "";
    vector<string> words;

    size_t pos = line.find_first_of('#');
    if (pos != string::npos){
        line.erase(pos);
    }

    for (int i = 0; i <= line.length(); i++){
        if ((line[i] != ' ') & (line[i] != ',') & (line[i] != '(') & (line[i] != ')') & (line[i] != '\0')){
            word += line[i];
        }
        else{
            word = remove_leading_spaces(word);
            word = remove_trailing_spaces(word);
            if (!word.empty()){
                words.push_back(word);
            }
            word = "";
        }
    }

    return words;
}

// Main Functions

bool initial_parse(string input_filename, map<string, int> &Label_map){
    set<string> instructions = {"add", "and", "or", "sll", "slt", "sra", "srl", "sub", "xor", "mul", "div", "rem", "addi", "andi", "ori", "lb", "ld", "lh", "lw", "jalr", "sb", "sw", "sd", "sh", "beq", "bne", "bge", "blt", "auipc", "lui", "jal"};

    ifstream input_file(input_filename);
    int PC = 0;
    bool ignore_line = 0;

    string line;
    while (std::getline(input_file, line)) {
        line = remove_leading_spaces(line);
        line = remove_trailing_spaces(line);
        if ((line.empty()) || (line[0] == '#'))
            continue;

        vector<string> words = preprocess(line);
        if (words.empty()){
            continue;
        }
        string first_word = words[0];

        if (first_word == ".data"){
            ignore_line = 1;
            continue;
        }
        if (first_word == ".text"){
            ignore_line = 0;
            continue;
        }

        if (first_word.back() == ':'){
            if (ignore_line){
                continue;
            }
            string Label_name = first_word.substr(0, first_word.length() - 1);
            Label_map[Label_name] = PC;
            continue;
        }

        if (!ignore_line){
            PC += 4;
        }
        
        // Finding if all the instructions are ISA or not.
        auto it = instructions.find(first_word);
        if (it == instructions.end()) {
            cout << "Error: Using instruction - " << first_word << " not in ISA" << endl;
            input_file.close();
            return 1;
        } 

        // Checking for labels 
        if ((first_word == "beq") || (first_word == "bne") || (first_word == "bge") || (first_word == "blt") || (first_word == "jal")){
            auto it  = Label_map.find(words.back());
            if (it == Label_map.end()){
                Label_map.insert({words.back(), -1});
            }
        }
    }

    input_file.close();
    return 0;
}

void final_parse(string input_filename, string output_filename, map<string, int> Label_map);
