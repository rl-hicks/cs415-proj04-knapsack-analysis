#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>



using namespace std;

vector<int> loadData(const string& filename) {
    vector<int> numbers; // stores each word
    ifstream file(filename);

    if (file.is_open()) {
        int num;

        while (file >> num) {
            // int cleanedWord = cleanWord(word);

            //if (num != "") // isn't empty
            //{
            numbers.push_back(num);
            //}
        }

        
    } else {
        cerr << "File error: " << filename << endl;
    }

    return numbers;
}





int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Incorrect number of arguments" << endl;
        return 1;
    }

    int num =-1;
    if (argc > 1) {
        try {
            num = stoi(argv[1]);
            // std::cout << "Integer: " << num << std::endl;
        } catch (const exception& e) {
            std::cerr << "Invalid input: " << e.what() << std::endl;
            return 1;
        }
    }

    vector<int> fileC, fileV, fileW;
    string file1, file2, file3;
    if (num < 10) {
        file1 = "data/p0" + to_string(num) + "_c.txt";
        file2 = "data/p0" + to_string(num) + "_v.txt";
        file3 = "data/p0" + to_string(num) + "_w.txt";
        fileC = loadData(file1);
        fileV = loadData(file2);
        fileW = loadData(file3);
    }

    /*
    for(auto num:fileC) {
        cout << num << endl;
    }
    cout << endl << endl << endl;

    for(auto num:fileV) {
        cout << num << endl;
    }

    cout << endl << endl << endl;

    for(auto num:fileW) {
        cout << num << endl;
    }    
    */



    //cout << num << "!" << endl;

    return 0;

}

