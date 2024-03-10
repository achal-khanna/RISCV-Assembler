#include <bits/stdc++.h>
#include <bitset>

using namespace std;

bool initial_parse(string input_filename, map<string, int> &Label_map);
void final_parse(string input_filename, string output_filename, map<string, int> Label_map, map<string, string> &Data_segment);

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

    map<string, string> Data_segment; 
    final_parse(input_filename, output_filename, Label_map, Data_segment);

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

string binTohex(string binary){
    string hex = "";
    for (int i = 0; i < binary.length(); i += 4){
        string group = binary.substr(i, 4);
        int value = std::stoi(group, nullptr, 2); 
        char hex_char = value + (value < 10 ? '0' : 'A' - 10); 
        hex += hex_char;
    }
    return hex;
}

string decTobin(string decimal){
    int value = stoi(decimal);
    bitset<32> bits(value);
    string str = bits.to_string();
    return str;
}

string hexTobin(string hexadecimal){
    string bin = "";
    for (char c: hexadecimal){
        int value = isdigit(c) ? c - '0' : c - 'A' + 10;
        string bin_group = decTobin(to_string(value));
        bin_group = bin_group.substr(28 ,4);
        bin += bin_group;
    }
    return bin;
}

string binTodec(string binary) {
  bool isNegative = binary[0] == '1'; 
  int value = 0;

  for (int i = 1; i < binary.length(); ++i) { 
    char bit_char = binary[i];
    int digit = bit_char - '0';
    value += digit * (1 << (binary.length() - 1 - i)); 
  }

  if (isNegative) {
    value = -value - 1; 
  }
  return to_string(value);
}

// Main Functions

string toMC(vector<string> words, map<string, string> registers, map<string, int> Label_map, int PC){
    string first_word = words[0];    
    string result = "";

    if (first_word == "add"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0000000" + registers[words[3]] + registers[words[2]] + "000" + registers[words[1]] + "0110011";
    }

    else if(first_word == "and"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0000000" + registers[words[3]] + registers[words[2]] + "111" + registers[words[1]] + "0110011";
    }

    else if(first_word == "or"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0000000" + registers[words[3]] + registers[words[2]] + "110" + registers[words[1]] + "0110011";
    }

    else if(first_word == "sll"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0000000" + registers[words[3]] + registers[words[2]] + "001" + registers[words[1]] + "0110011";
    }

    else if(first_word == "slt"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0000000" + registers[words[3]] + registers[words[2]] + "010" + registers[words[1]] + "0110011";
    }

    else if(first_word == "sra"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0100000" + registers[words[3]] + registers[words[2]] + "101" + registers[words[1]] + "0110011";
    }

    else if(first_word == "srl"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0000000" + registers[words[3]] + registers[words[2]] + "101" + registers[words[1]] + "0110011";
    }

    else if(first_word == "sub"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0100000" + registers[words[3]] + registers[words[2]] + "000" + registers[words[1]] + "0110011";
    }

    else if(first_word == "xor"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0000000" + registers[words[3]] + registers[words[2]] + "100" + registers[words[1]] + "0110011";
    }

    else if(first_word == "mul"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0000001" + registers[words[3]] + registers[words[2]] + "000" + registers[words[1]] + "0110011";
    }

    else if(first_word == "div"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0000001" + registers[words[3]] + registers[words[2]] + "100" + registers[words[1]] + "0110011";
    }

    else if(first_word == "rem"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }
        result += "0000001" + registers[words[3]] + registers[words[2]] + "110" + registers[words[1]] + "0110011";
    }

    else if(first_word == "addi"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[3].substr(0, 2) == "0x"){
            imm = words[3].substr(2, words[3].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[3];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm + registers[words[2]] + "000" + registers[words[1]] + "0010011";
    }

    else if(first_word == "andi"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[3].substr(0, 2) == "0x"){
            imm = words[3].substr(2, words[3].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[3];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm + registers[words[2]] + "111" + registers[words[1]] + "0010011";
    }

    else if(first_word == "ori"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[3].substr(0, 2) == "0x"){
            imm = words[3].substr(2, words[3].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[3];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm + registers[words[2]] + "110" + registers[words[1]] + "0010011";
    }

    else if(first_word == "lb"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[2].substr(0, 2) == "0x"){
            imm = words[2].substr(2, words[2].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[2];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm + registers[words[3]] + "000" + registers[words[1]] + "0000011";
    }

    else if(first_word == "ld"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[2].substr(0, 2) == "0x"){
            imm = words[2].substr(2, words[2].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[2];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm + registers[words[3]] + "011" + registers[words[1]] + "0000011";
    }

    else if(first_word == "lh"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[2].substr(0, 2) == "0x"){
            imm = words[2].substr(2, words[2].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[2];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm + registers[words[3]] + "001" + registers[words[1]] + "0000011";
    }

    else if(first_word == "lw"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[2].substr(0, 2) == "0x"){
            imm = words[2].substr(2, words[2].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[2];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm + registers[words[3]] + "010" + registers[words[1]] + "0000011";
    }

    else if(first_word == "jalr"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[3].substr(0, 2) == "0x"){
            imm = words[3].substr(2, words[3].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[3];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm + registers[words[2]] + "000" + registers[words[1]] + "1100111";
    }

    else if(first_word == "sb"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[2].substr(0, 2) == "0x"){
            imm = words[2].substr(2, words[2].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[2];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm.substr(0, 7) + registers[words[1]] + registers[words[3]] + "000" + imm.substr(7, 5) + "0100011";
    }

    else if(first_word == "sw"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[2].substr(0, 2) == "0x"){
            imm = words[2].substr(2, words[2].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[2];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm.substr(0, 7) + registers[words[1]] + registers[words[3]] + "010" + imm.substr(7, 5) + "0100011";
    }

    else if(first_word == "sd"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[2].substr(0, 2) == "0x"){
            imm = words[2].substr(2, words[2].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[2];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm.substr(0, 7) + registers[words[1]] + registers[words[3]] + "011" + imm.substr(7, 5) + "0100011";
    }

    else if(first_word == "sh"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[3]) == registers.end())){
            return "1";
        }

        string imm;
        if (words[2].substr(0, 2) == "0x"){
            imm = words[2].substr(2, words[2].length()-2);
            imm = binTodec(hexTobin(imm));
        }else{
            imm = words[2];
        }

        int value = stoi(imm);
        if ((value > 2047) || (value <-2048)){
            cout << "Value exceeds allowed limit for imm. Change to lie between -2048 and 2047." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(20 , 12);

        result += imm.substr(0, 7) + registers[words[1]] + registers[words[3]] + "001" + imm.substr(7, 5) + "0100011";
    }

    else if(first_word == "beq"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end())){
            return "1";
        }

        string imm;
        int label = Label_map[words[3]];
        int offset = (label - PC);

        imm = decTobin(to_string(offset));
        imm = imm.substr(19 , 12);

        result += imm[0] + imm.substr(2, 6) + registers[words[2]] + registers[words[1]] + "000" + imm.substr(8, 4) + imm[1] + "1100011";
    }

    else if(first_word == "bne"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end())){
            return "1";
        }

        string imm;
        int label = Label_map[words[3]];
        int offset = (label - PC);

        imm = decTobin(to_string(offset));
        imm = imm.substr(19 , 12);

        result += imm[0] + imm.substr(2, 6) + registers[words[2]] + registers[words[1]] + "001" + imm.substr(8, 4) + imm[1] + "1100011";
    }

    else if(first_word == "blt"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end())){
            return "1";
        }

        string imm;
        int label = Label_map[words[3]];
        int offset = (label - PC);

        imm = decTobin(to_string(offset));
        imm = imm.substr(19 , 12);

        result += imm[0] + imm.substr(2, 6) + registers[words[2]] + registers[words[1]] + "100" + imm.substr(8, 4) + imm[1] + "1100011";
    }

    else if(first_word == "bge"){
        if ((registers.find(words[1]) == registers.end()) || (registers.find(words[2]) == registers.end())){
            return "1";
        }

        string imm;
        int label = Label_map[words[3]];
        int offset = (label - PC);

        imm = decTobin(to_string(offset));
        imm = imm.substr(19 , 12);

        result += imm[0] + imm.substr(2, 6) + registers[words[2]] + registers[words[1]] + "101" + imm.substr(8, 4) + imm[1] + "1100011";
    }

    else if(first_word == "auipc"){
        if (registers.find(words[1]) == registers.end()){
            return "1";
        }

        string imm;
        if (words[2].substr(0, 2) == "0x"){
            imm = words[2].substr(2, words[2].length()-2);
            imm = binTodec("0" + hexTobin(imm));
        }else{
            imm = words[2];
        }

        int value = stoi(imm);
        if ((value > 1048575) || (value < 0)){
            cout << "Value exceeds allowed limit for imm. Change to lie between 0 and 1048575." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(12 , 20);

        result += imm + registers[words[1]] + "0010111";
    }

    else if(first_word == "lui"){
        if (registers.find(words[1]) == registers.end()){
            return "1";
        }

        string imm;
        if (words[2].substr(0, 2) == "0x"){
            imm = words[2].substr(2, words[2].length()-2);
            imm = binTodec("0" + hexTobin(imm));
        }else{
            imm = words[2];
        }

        int value = stoi(imm);
        if ((value > 1048575) || (value < 0)){
            cout << "Value exceeds allowed limit for imm. Change to lie between 0 and 1048575." << endl;
            return "";
        }

        imm = decTobin(imm);
        imm = imm.substr(12 , 20);

        result += imm + registers[words[1]] + "0110111";
    }

    else{
        if (registers.find(words[1]) == registers.end()){
            return "1";
        }

        string imm;
        int label = Label_map[words[2]];
        int offset = (label - PC);

        imm = decTobin(to_string(offset));
        imm = imm.substr(11 , 20);

        result += imm[0] + imm.substr(10, 10) + imm[9] + imm.substr(1, 8) + registers[words[1]] + "1101111";
    }

    return result;
}

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

void final_parse(string input_filename, string output_filename, map<string, int> Label_map, map<string , string> &Data_segment){
    ifstream input_file(input_filename);
    ofstream output_file(output_filename);

    int PC = 0;
    bool ignore_line = 0;

    // For Data_segment
    long long Data = 0x10000000;
    long long adder = 0;

    map<string, string> registers = {{"zero", "00000"}, {"ra", "00001"}, {"sp", "00010"}, {"gp", "00011"}, {"tp", "00100"}, {"t0", "00101"}, {"t1", "00110"}, {"t2", "00111"}, {"s0", "01000"}, {"s1", "01001"}, {"a0", "01010"}, {"a1", "01011"}, {"a2", "01100"}, {"a3", "01101"}, {"a4", "01110"}, {"a5", "01111"}, {"a6", "10000"}, {"a7", "10001"}, {"s2", "10010"}, {"s3", "10011"}, {"s4", "10100"}, {"s5", "10101"}, {"s6", "10110"}, {"s7", "10111"}, {"s8", "11000"}, {"s9", "11001"}, {"s10", "11010"}, {"s11", "11011"}, {"t3", "11100"}, {"t4", "11101"}, {"t5", "11110"}, {"t6", "11111"}};

    for (int i = 0; i<=31; i++){
        string str = "x" + to_string(i);
        registers[str] = (decTobin(to_string(i))).substr(27, 5);
    }

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
            adder = 0;
            continue;
        }

        if (ignore_line){
            if (words[1] == ".byte"){
                adder = 1;
            }
            else if (words[1] == ".half"){
                adder = 2;
            }
            else if (words[1] == ".word"){
                adder = 4;
            }
            else if (words[1] == ".dword"){
                adder = 8;
            }
            else{
                words[2] = words[2].substr(1, words[2].length()-2);
                adder = 1;
            } 

            for (int i = 2; i < words.size(); i++){
                if (words[1] == ".asciiz"){
                    string str = words[2];
                    for (char c : str){
                        int value = static_cast<int>(c);
                        string intermediate = binTohex(decTobin(to_string(value)));
                        Data_segment["0x" + binTohex(decTobin(to_string(Data)))] = "0x" + intermediate.substr(6, 2);
                        Data += adder;
                    }
                    Data_segment["0x" + binTohex(decTobin(to_string(Data)))] = "0x00";
                    Data += adder; 
                    continue;
                }
                Data_segment["0x" + binTohex(decTobin(to_string(Data)))] = "0x" + binTohex(decTobin((words[i]))).substr(8-2*adder, 2*adder);
                Data += adder;
            }
            continue;
        }

        if (first_word.back() == ':'){
            continue;
        }

        string result = "0x" + binTohex(toMC(words, registers, Label_map, PC));

        if (result == "0x1"){
            cout << "Register not found in " << first_word << " operation at PC location - " << "0x" + binTohex(decTobin(to_string(PC))) << endl;
        }

        if ((result == "0x") || (result == "0x1")){
            output_file.close();
            // Rewriting all its contents to 0.
            ofstream output_file(output_filename);
            output_file.close();
            return;
        }

        string program_counter = "0x" + binTohex(decTobin(to_string(PC)));
        output_file << program_counter <<  " " << result << endl;

        PC += 4;
    }

    input_file.close();
    output_file.close();
    return;
}
 

