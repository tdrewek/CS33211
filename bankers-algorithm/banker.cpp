#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctype.h>

void getData(std::vector< std::vector<int> > &all, std::vector< std::vector<int> > &max, std::vector<int> &ava, int &processes, int &resources) {
    std::ifstream in;
    in.open("input.csv");
    if(!in) {
        std::cerr << "File failed to open..." << std::endl;
        exit(1);
    }
    char input;
    int i = 0;
    std::string word;
    std::vector<int> row;
        while(!in.eof()) {
            in.get(input);
            if(!isdigit(input)) {
                if(word != "") {
                    int num = std::stoi(word);
                    if(i == 2) {
                        ava.push_back(num);
                    }
                    row.push_back(num);
                }
                word = "";
            }
            else if(isdigit(input) && input != ' ' && input != ',') {
                word.push_back(input);
            }
            if(input == '\n' || input == '\t' || input == '\r') {
                i = 0;
                row.clear();           
            }
            else if(input == ',') {
                if(i == 0) {
                    all.push_back(row);
                }
                else if(i == 1) {
                    max.push_back(row);
                }
                row.clear();          
                i++;
            }
        }
    processes = all.size();
    resources = ava.size();
}

int main() {
    int processes, resources;
    std::vector< std::vector<int> > all;
    std::vector< std::vector<int> > max;
    std::vector<int> ava;
    getData(all, max, ava, processes, resources);
    std::cout << "\nAllocated Resource Table:\n";
    for(int i = 0; i < processes; i++) {
        for(int j = 0; j < resources; j++) {
            std::cout << all[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Max Resource Table:\n";
    for(int i = 0; i < processes; i++) {
        for(int j = 0; j < resources; j++) {
            std::cout << max[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Available Resources:\n";
    for(int i = 0; i < resources; i++) {
       std::cout << ava[i] << " ";
    }

    std::cout << "\n\n";

    int finished[processes];
    int ordered[processes];

    int needed[processes][resources];

    int step = 0;

    for(int i = 0; i < processes; i++)
        finished[i] = 0;
    for(int i = 0; i < processes; i++) {
        for(int j = 0; j < resources; j++) {
            needed[i][j] = max[i][j] - all[i][j];
        }
    }
    std::cout << "Needed Resources:\n";
    for(int i = 0; i < processes; i++) {
        for(int j = 0; j < resources; j++) {
            std::cout << needed[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for(int i = 0; i < processes; i++) {
        for(int j = 0; j < processes; j++) {
            if(finished[j] == 0) {
                int safe = 0;
            
                for(int k = 0; k < resources; k++) {
                    if(needed[j][k] > ava[k]) {
                     safe = 1;
                        break;
                    }
                }
                if (safe == 0) {
                    ordered[step++] = j;
                    for(int l = 0; l < resources; l++)
                        ava[l] += all[j][l];
                    finished[j] = 1;
                }
            }
        }
    }
    int safe = 1;

    for(int i = 0; i < processes; i++) {
        if(finished[i] == 0) {
         safe = 0;
            std::cout << "Sequence is unsafe\n";
            break;
        }
    }

    if (safe == 1) {
        std::cout << "Safe sequence is: \n";
        for(int i = 0; i < processes - 1; i++)
            std::cout << " P" << ordered[i] << " to";
        std::cout << " P" << ordered[processes-1] << std::endl;
    }
    return 0;
}