#include <iostream>
#include <list>
#include <vector>

class HashTableOpenAddressing {
private:
    int size;
    std::vector<int> table;
    int EMPTY = -1;

public:
    HashTableOpenAddressing(int s) : size(s) {
        table.resize(size, EMPTY);
    }

    void insert(int key) {
        int index = key % size;
        int i = 0;
        
        while (table[(index + i) % size] != EMPTY) {
            i++;
            if (i == size) {
                std::cout << "Tabla llena" << std::endl;
                return;
            }
        }
        table[(index + i) % size] = key;
    }

    bool search(int key) {
        int index = key % size;
        int i = 0;

        while (table[(index + i) % size] != EMPTY) {
            if (table[(index + i) % size] == key) return true;
            i++;
            if (i == size) return false; // Hemos recorrido toda la tabla
        }
        return false; // No se encontró el elemento
    }

    void remove(int key) {
        int index = key % size;
        int i = 0;

        while (table[(index + i) % size] != EMPTY) {
            if (table[(index + i) % size] == key) {
                table[(index + i) % size] = EMPTY; // Marcar como eliminado
                std::cout << "Clave eliminada: " << key << std::endl;
                return;
            }
            i++;
            if (i == size) {
                std::cout << "Clave no encontrada: " << key << std::endl;
                return; // Hemos recorrido toda la tabla
            }
        }
        std::cout << "Clave no encontrada: " << key << std::endl; // No se encontró el elemento
    }

    void display() {
        for (int i = 0; i < size; i++) {
            std::cout << "[" << i << "]: " << (table[i] == EMPTY ? "Empty" : std::to_string(table[i])) << std::endl;
        }
    }
};

int main() {
    // Limpiar pantalla para mejor legibilidad
    std::cout << "\033[2J\033[1;1H";
    
    HashTableOpenAddressing hashTable(5);

    hashTable.insert(1);
    hashTable.insert(6);
    hashTable.insert(11);
    hashTable.insert(7);

    hashTable.display();

    std::cout << "Buscar 6: " << (hashTable.search(6) ? "Encontrado" : "No encontrado") << std::endl;
    std::cout << "Buscar 2: " << (hashTable.search(2) ? "Encontrado" : "No encontrado") << std::endl;

    hashTable.remove(6);
    hashTable.remove(2);

    hashTable.display();

    return 0;
}