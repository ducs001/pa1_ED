#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>

const int MAX_SIZE = 20000; // Tamaño máximo permitido para el arreglo
const int NUM_SIZES = 40; // Número de tamaños distintos a probar

// Función para eliminar duplicados usando arreglos
int eliminarDuplicadosArreglo(int arr[], int n, int resultado[]) {
    int k = 0; // Contador para el arreglo sin duplicados
    for (int i = 0; i < n; i++) {
        bool encontrado = false;
        for (int j = 0; j < k; j++) {
            if (arr[i] == resultado[j]) {
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            resultado[k++] = arr[i]; // Agregar elemento único
        }
    }
    return k; // Retornar el tamaño del arreglo sin duplicados
}

// Función para eliminar duplicados usando listas estáticas (simuladas con vectores)
int eliminarDuplicadosListaEstatica(const std::vector<int>& arr, std::vector<int>& resultado) {
    resultado.clear(); // Limpiar el vector de resultados
    for (int num : arr) {
        if (std::find(resultado.begin(), resultado.end(), num) == resultado.end()) {
            resultado.push_back(num); // Agregar elemento único
        }
    }
    return resultado.size(); // Retornar el tamaño del vector sin duplicados
}

// Función para realizar pruebas de eficiencia
void realizarPruebasEficiencia() {
    int datos[MAX_SIZE]; // Arreglo para almacenar los datos
    int resultadosArreglo[MAX_SIZE]; // Arreglo para almacenar resultados sin duplicados
    std::vector<int> resultadosLista; // Vector para almacenar resultados sin duplicados

    // Generar 40 tamaños distintos de entrada
    int tamaños[NUM_SIZES];
    for (int i = 0; i < NUM_SIZES; i++) {
        tamaños[i] = (i + 1) * (MAX_SIZE / NUM_SIZES); // Distribuir tamaños uniformemente
    }

    // Probar diferentes tamaños de entrada
    for (int i = 0; i < NUM_SIZES; i++) {
        int n = tamaños[i];

        // Generar datos aleatorios
        for (int j = 0; j < n; j++) {
            datos[j] = rand() % 1000; // Números aleatorios entre 0 y 999
        }

        // Medir tiempo de ejecución para arreglos
        auto inicioArreglos = std::chrono::high_resolution_clock::now();
        int kArreglos = eliminarDuplicadosArreglo(datos, n, resultadosArreglo);
        auto finArreglos = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tiempoArreglos = finArreglos - inicioArreglos;

        // Medir tiempo de ejecución para listas estáticas (vectores)
        auto inicioListas = std::chrono::high_resolution_clock::now();
        int kListas = eliminarDuplicadosListaEstatica(std::vector<int>(datos, datos + n), resultadosLista);
        auto finListas = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tiempoListas = finListas - inicioListas;

        // Calcular espacio utilizado
        size_t espacioArreglos = n * sizeof(int); // Espacio para el arreglo
        size_t espacioListas = resultadosLista.size() * sizeof(int); // Espacio para el vector

        // Mostrar resultados
        std::cout << "Tamanio: " << n << "\n";
        std::cout << "Tiempo de ejecucion (arreglos): " << tiempoArreglos.count() << " segundos\n";
        std::cout << "Elementos unicos (arreglos): " << kArreglos << "\n";
        std::cout << "Espacio utilizado (arreglos): " << espacioArreglos << " bytes\n";
        std::cout << "Tiempo de ejecucion (listas estaticas): " << tiempoListas.count() << " segundos\n";
        std::cout << "Elementos unicos (listas estaticas): " << kListas << "\n";
        std::cout << "Espacio utilizado (listas estaticas): " << espacioListas << " bytes\n\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicializar generador de números aleatorios

    // Llamada a la función para realizar pruebas de eficiencia
    realizarPruebasEficiencia();
    return 0; // Finaliza el programa
}
