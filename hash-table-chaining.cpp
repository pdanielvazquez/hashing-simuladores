#include <iostream>
#include <list>
#include <vector>

class HashTableChaining {
private:
    int size;
    std::vector<std::list<int>> table;

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTableChaining(int s) : size(s) {
        table.resize(size);
    }

    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    bool search(int key) {
        int index = hashFunction(key);
        for (auto x : table[index]) {
            if (x == key) return true;
        }
        return false;
    }

    void remove(int key) {
        if (!search(key)) {
            std::cout << "Key not found: " << key << std::endl;
            return;
        }
        int index = hashFunction(key);
        table[index].remove(key);
        std::cout << "Key removed: " << key << std::endl;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            std::cout << "[" << i << "]: ";
            for (auto x : table[i]) std::cout << x << " -> ";
            std::cout << "nullptr" << std::endl;
        }
        std::cout << "\n" <<  std::endl;
    }
};

int main() {
    // Cleaning sreen for better readability
    std::cout << "\033[2J\033[1;1H";
    
    HashTableChaining hashTable(5);

    hashTable.insert(1);
    hashTable.insert(6);
    hashTable.insert(11);
    hashTable.insert(16);
    hashTable.insert(21);

    std::cout << "Hash Table with Chaining:" << std::endl;
    hashTable.display();

    std::cout << "Search for 11: " << (hashTable.search(11) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search for 10: " << (hashTable.search(10) ? "Found" : "Not Found") << std::endl;

    hashTable.remove(11);
    std::cout << "After removing 11:" << std::endl;
    hashTable.display();

    return 0;
}