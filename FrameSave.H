#pragma once
#include <string>
#include <fstream>

class File {
public:
    template<int W>
    void SaveFile(int HEIGHT_CANVA, int WIDTH_CANVA, char (*frame)[W], std::string answer) {
        int index = 0;
        std::ifstream testFile(std::to_string(index) + ".txt");
        while (testFile.good()) {
            testFile.close();
            index++;
            testFile.open(std::to_string(index) + ".txt");
        }
        testFile.close();

        std::ofstream outFile(std::to_string(index) + ".txt");
        for (int i = 0; i < HEIGHT_CANVA; i++) {
            std::string next_row;
            for (int j = 0; j < WIDTH_CANVA; j++) {
                next_row += frame[i][j];
            }
            outFile << next_row << "\n";
        }
        outFile << answer;
    }
};
