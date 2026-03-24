#include <iostream>
#include <list>
#include <vector>

class HashTableChaining {
private:
    int size;
    int no_of_keys = 0;
    float load_factor_threshold = 0.75;
    float current_load_factor = 0.0;
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
        no_of_keys++;
        current_load_factor = static_cast<float>(no_of_keys) / size;
        std::cout << "Clave insertada: " << key << ", Factor de carga: " << current_load_factor << std::endl;
        if (current_load_factor > load_factor_threshold) {
            std::cout << "Factor de carga excedido. Rehashing..." << std::endl;
            rehash();
        }
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

    
    void rehash() {
        int old_size = size;
        size *= 2; // o next_prime(size*2)
        HashTableChaining new_table(size);

        for (int i = 0; i < old_size; ++i) {
            for (int key : table[i]) {
                new_table.insert(key);
            }
        }
        table = move(new_table.table);
        std::cout << "Rehashing completo. Nueva capacidad: " << size << std::endl;
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
    hashTable.display();

    std::cout << "Buscando clave 11: " << (hashTable.search(11) ? "Encontrada" : "No encontrada") << std::endl;

    return 0;
}