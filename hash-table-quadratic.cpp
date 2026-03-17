#include <iostream>
#include <vector>
#include <cmath>

class HashTableQuadratic {
private:
    int size;
    std::vector<int> table;
    int EMPTY = -1;
    int DELETED = -2; // Estado especial para borrados

public:
    HashTableQuadratic(int s) : size(s) {
        table.resize(size, EMPTY);
    }

    void insert(int key) {
        int index = key % size;
        int i = 0;

        while (i < size) {
            int pos = (index + i * i) % size; // Salto cuadrático: i^2
            
            if (table[pos] == EMPTY || table[pos] == DELETED) {
                table[pos] = key;
                std::cout << "Insertado " << key << " en indice " << pos << " (intento " << i << ")" << std::endl;
                return;
            }
            i++;
        }
        std::cout << "Error: No se pudo insertar " << key << " (Tabla llena o ciclo infinito)" << std::endl;
    }

    void display() {
        std::cout << "\n--- Estado de la Tabla (Quadratic) ---\n";
        for (int i = 0; i < size; i++) {
            std::cout << "[" << i << "]: ";
            if (table[i] == EMPTY) std::cout << "E";
            else if (table[i] == DELETED) std::cout << "D";
            else std::cout << table[i];
            std::cout << std::endl;
        }
    }
};

int main() {
    HashTableQuadratic ht(10);

    // Provocamos colisiones en el índice 2
    ht.insert(2);   // (2 + 0^2) % 10 = 2
    ht.insert(12);  // (2 + 1^2) % 10 = 3
    ht.insert(22);  // (2 + 2^2) % 10 = 6
    ht.insert(32);  // (2 + 3^2) % 10 = 1 (Porque 2 + 9 = 11, 11 % 10 = 1)

    ht.display();
    return 0;
}