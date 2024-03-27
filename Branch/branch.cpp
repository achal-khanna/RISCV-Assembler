#include <bits/stdc++.h>
using namespace std;

#define max_lines 10e7

long long extractOffset(string currLine){
    size_t posPlus = currLine.find("pc +");
    size_t posMinus = currLine.find("pc -");

    if (posPlus != string::npos) {
        string offsetStr = currLine.substr(posPlus + 4);
        return atoi(offsetStr.c_str()); 
    } 
    else if (posMinus != string::npos) {
        string offsetStr = currLine.substr(posMinus + 4); 
        return -atoi(offsetStr.c_str()); 
    }

    return -1;
}

double alwaysTaken(long long currAddress, long long nextAddress, long long targetAddress){
    static long long predicted = 0, total = 0;
    if (nextAddress == targetAddress){
        predicted++;
    }
    total++;
    return (double)predicted/total;
}

double notTaken(long long currAddress, long long nextAddress, long long targetAddress){
    static long long predicted = 0, total = 0;
    if (nextAddress != targetAddress){
        predicted++;
    }
    total++;
    return (double)predicted/total;
}

double oneBit(long long currAddress, long long nextAddress, long long targetAddress){
    static long long predicted = 0, total = 0;
    static map<long long, bool> predictionTable;

    auto it = predictionTable.find(currAddress);
    if (it == predictionTable.end()){
        predictionTable.insert({currAddress, true});
    }

    bool prediction = predictionTable[currAddress];
    if ((prediction) && (nextAddress == targetAddress)){
        predicted++;
    }else if ((prediction) && (nextAddress != targetAddress)){
        predictionTable[currAddress] = false;
    }else if ((!prediction) && (nextAddress == targetAddress)){
        predictionTable[currAddress] = true;
    }else{
        predicted++;
    }

    total++;
    return (double)predicted/total;
}

double twoBit(long long currAddress, long long nextAddress, long long targetAddress){
    static long long predicted = 0, total = 0;
    static map<long long, int> predictionTable;

    auto it = predictionTable.find(currAddress);
    if (it == predictionTable.end()){
        predictionTable.insert({currAddress, 2});
    }

    int val = predictionTable[currAddress];
    bool prediction = (val >= 2) ? 1: 0;

    if ((prediction) && (nextAddress == targetAddress)){
        predicted++;
        predictionTable[currAddress]++;
        if (predictionTable[currAddress] >= 3)   predictionTable[currAddress] = 3;
    }else if ((prediction) && (nextAddress != targetAddress)){
        predictionTable[currAddress]--;
    }else if ((!prediction) && (nextAddress == targetAddress)){
        predictionTable[currAddress]++;
    }else{
        predicted++;
        predictionTable[currAddress]--;
        if (predictionTable[currAddress] <= 0)   predictionTable[currAddress] = 0;
    }

    total++;
    return (double)predicted/total;
}

string longLongToHexString(long long value) {
    ostringstream oss;
    oss << std::hex << setw(8) << setfill('0') << value; 
    return "0x" + oss.str(); 
}

int main(){
    const string inputFilename = "input.txt";
    ifstream inputFile(inputFilename);
    long long count = 1;
    map<string, string> targetBuffer;

    string currLine, nextLine, core, zero, programCounter, machineCode, instruction;
    getline(inputFile, currLine);

    double takenAccuracy = 0, nottakenAccuracy = 0, OnebitAccuracy = 0, TwobitAccuracy = 0; 

    while ((getline(inputFile, nextLine)) && (count <= max_lines)){
        istringstream currText(currLine);
        currText >> core >> zero >> programCounter >> machineCode >> instruction;

        if ((programCounter.substr(0, 2) != "0x") || (core != "core")){
            currLine = nextLine;
            count++;
            continue;
        }

        long long currAddress = 0, nextAddress = 0, targetAddress = 0;
        currAddress = stoll(programCounter.substr(2, 8), nullptr, 16);

        if (instruction[0] == 'b'){
            istringstream nextText(nextLine);
            nextText >> core >> zero >> programCounter;

            if ((programCounter.substr(0, 2) != "0x")|| (core != "core")){
                currLine = nextLine;
                count++;
                continue;
            }
                
            nextAddress = stoll(programCounter.substr(2, 8), nullptr, 16);
            targetAddress = extractOffset(currLine);
            if (targetAddress == -1){
                std::cout << "Error extracting offset at line " << currLine << endl;
                break;
            }targetAddress += currAddress; 

            // Updating Target Buffer to include the current address.
            auto it = targetBuffer.find(longLongToHexString(currAddress));
            if (it == targetBuffer.end()){
                targetBuffer.insert({longLongToHexString(currAddress), longLongToHexString(targetAddress)});
            }

            takenAccuracy = alwaysTaken(currAddress, nextAddress, targetAddress);
            nottakenAccuracy = notTaken(currAddress, nextAddress, targetAddress);
            OnebitAccuracy = oneBit(currAddress, nextAddress, targetAddress);
            TwobitAccuracy = twoBit(currAddress, nextAddress, targetAddress);
        }

        currLine = nextLine;
        count++;
    }

    std::cout << "Accuracy for Always Taken: " << 100*takenAccuracy << "\n" << "Accuracy for Always Not Taken: " << 100*nottakenAccuracy << "\n" << "Accuracy for 1 Bit: " << 100*OnebitAccuracy << "\n" << "Accuracy for 2 Bit: " << 100*TwobitAccuracy << endl;
    std::cout << "Branch Target Buffer - " << endl;
    for (const auto& pair : targetBuffer) {
        std::cout << "PC: " << pair.first << ", Target Address: " << pair.second << std::endl;
    }

    inputFile.close();
    return 0;
}
