#include <iostream>
#include <string>

struct ValueNode {
    std::string value;
    ValueNode* next;

    ValueNode(std::string val) : value(val), next(nullptr) {}
};

struct KeyNode {
    std::string key;
    KeyNode* next;
    ValueNode* down;

    KeyNode(std::string k) : key(k), next(nullptr), down(nullptr) {}
};

// ── hashmap ────────────────────────────────────────────

class HashMap {
    KeyNode* head;

public:
    HashMap(std::string id) {
        head = new KeyNode(id);
    }

    void appendKey(std::string key) {
        KeyNode* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new KeyNode(key);
    }

    void appendValue(std::string key, std::string value) {
        KeyNode* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                if (!current->down) {
                    current->down = new ValueNode(value);
                } else {
                    ValueNode* vCurrent = current->down;
                    while (vCurrent->next) {
                        vCurrent = vCurrent->next;
                    }
                    vCurrent->next = new ValueNode(value);
                }
                return;
            }
            current = current->next;
        }
        std::cout << "Key not found: " << key << std::endl;
    }

    ValueNode* get(std::string key) {
        KeyNode* current = head;
        while (current != nullptr) {
            if (current->key == key) return current->down;
            current = current->next;
        }
        return nullptr;
    }

    void print() {
        KeyNode* current = head;
        while (current) {
            std::cout << "[" << current->key << "]";
            if (current->next) std::cout << " -> ";
            current = current->next;
        }
        std::cout << std::endl;

        current = head;
        while (current) {
            if (current->down) {
                std::cout << "  " << current->key << ":\n";
                ValueNode* vCurrent = current->down;
                while (vCurrent) {
                    std::cout << "    | " << vCurrent->value << "\n";
                    vCurrent = vCurrent->next;
                }
            }
            current = current->next;
        }
    }

    ~HashMap() {
        KeyNode* current = head;
        while (current) {
            ValueNode* vCurrent = current->down;
            while (vCurrent) {
                ValueNode* vTemp = vCurrent;
                vCurrent = vCurrent->next;
                delete vTemp;
            }
            KeyNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};


