#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void generarGrafo(int n, vector<vector<int>>& grafo) {
    grafo.resize(n, vector<int>(n, 0));

    // Generar el camino base
    for (int i = 0; i < 3; ++i) {
        grafo[i][i + 1] = 1;
        grafo[i + 1][i] = 1;
    }
    grafo[0][2]=1;
    grafo[2][0]=1;

    // Agregar enlaces aleatorios
    srand(time(0));

    for (int i = 0; i < n; ++i) {
        for (int j = i + 2; j < n; ++j) {
            if (rand() % 2 == 1) {
                grafo[i][j] = 1;
                grafo[j][i] = 1;
            }
        }
    }
}

void escribirDot(const vector<vector<int>>& grafo, const string& nombreArchivo) {
    ofstream archivoDot(nombreArchivo);
    archivoDot << "graph G {\n";

    for (size_t i = 0; i < grafo.size(); ++i) {
        for (size_t j = i + 1; j < grafo[i].size(); ++j) {
            if (grafo[i][j] == 1) {
                archivoDot << "  " << char('A' + i) << " -- " << char('A' + j) << ";\n";
            }
        }
    }

    archivoDot << "}\n";
    archivoDot.close();
}

// Función para realizar la búsqueda en profundidad y generar un árbol de expansión
void DFS(const vector<vector<int>>& grafo, int nodo, vector<bool>& visitado, vector<vector<int>>& arbol) {
    visitado[nodo] = true;

    for (size_t i = 0; i < grafo.size(); ++i) {
        if (grafo[nodo][i] == 1 && !visitado[i]) {
            arbol[nodo][i] = 1;
            arbol[i][nodo] = 1;
            DFS(grafo, i, visitado, arbol);
        }
    }
}

int main() {
    int n = 26; // Número de vértices
    vector<vector<int>> grafo;
    vector<bool> visitado(n, false);
    vector<vector<int>> arbol(n, vector<int>(n, 0));

    generarGrafo(n, grafo);
    escribirDot(grafo, "grafo.dot");

    // Iniciar la búsqueda en profundidad desde el nodo 0
    DFS(grafo, 0, visitado, arbol);

    escribirDot(arbol, "arbol.dot");

    system("dot -Tjpg grafo.dot -o grafo.jpg");
    system("dot -Tjpg arbol.dot -o arbol.jpg");

    cout << "arbol de expansion generado y guardado en arbol.dot y arbol.jpg\n";

    return 0;
}
