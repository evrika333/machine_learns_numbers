#include <fstream>
#include <string>
#include <sstream>
#include "../Algo/hashmap.H"

struct data {
    std::string key;
    std::string value;
};

class json {
    std::string filename;
    std::string Cur_Line;
    std::fstream InFile;

public:
    json(std::string name) {
        filename = name;
        std::ofstream create(name + ".txt", std::ios::app);
        create.close();
        InFile.open(name + ".txt", std::ios::in | std::ios::out);
    }

    void Read(std::string Id) {
        InFile.clear();
        InFile.seekg(0, std::ios::beg);

        while (std::getline(InFile, Cur_Line)) {
            if (Cur_Line == Id)
                break;
        }
        if (Cur_Line != Id)
            return;

        HashMap map(Id);
        while (std::getline(InFile, Cur_Line)) {
            if (Cur_Line == "{")
                continue;
            else if (Cur_Line == "}")
                break;

            bool isKey = true;
            std::string keyBuffer = "";
            std::string valueBuffer = "";

            for (char letter : Cur_Line) {
                if (letter == ' ')
                    continue;
                else if (letter == ':') {
                    isKey = false;
                }
                else if (letter == ',') {
                    break;
                }
                else if (isKey) {
                    keyBuffer += letter;
                }
                else {
                    valueBuffer += letter;
                }
            }

            if (!keyBuffer.empty()) {
                map.appendKey(keyBuffer);
                if (!valueBuffer.empty()) {
                    map.appendValue(keyBuffer, valueBuffer);
                }
            }
        }
    }

    void Write(data Data, std::string Id) {
        // ── read entire file into memory ──
        InFile.clear();
        InFile.seekg(0, std::ios::beg);
        std::string fullFile = "";
        std::string line;
        bool IdExist = false;
        bool inserted = false;

        std::string newEntry = Data.key + ":" + Data.value + ",";

        while (std::getline(InFile, line)) {
            if (line == Id) {
                IdExist = true;
            }
            // if id exists, insert new entry just before closing }
            if (IdExist && !inserted && line == "}") {
                fullFile += newEntry + "\n";
                inserted = true;
            }
            fullFile += line + "\n";
        }

        // ── id not found, append new block ──
        if (!IdExist) {
            fullFile += Id + "\n";
            fullFile += "{\n";
            fullFile += newEntry + "\n";
            fullFile += "}\n";
        }

        // ── write everything back ──
        InFile.clear();
        InFile.seekp(0, std::ios::beg);
        InFile << fullFile;
        InFile.flush();
    }

    ~json() {
        if (InFile.is_open())
            InFile.close();
    }
};

