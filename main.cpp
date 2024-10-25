/* 
Autores:
Didimo Luan Neves da Silva
Jéssica Lopes Melo
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

class Ordenador {
private:
    vector<int> dados;
    int comparacoes;
    int trocas;

public:
    Ordenador(int tamanho) : dados(tamanho), comparacoes(0), trocas(0) {}

    void preencherAleatorio() {
        for (int &valor : dados) {
            valor = rand() % 1000; // Números aleatórios de 0 a 999
        }
    }

    void preencherDecrescente() {
        for (size_t i = 0; i < dados.size(); ++i) {
            dados[i] = dados.size() - i; // Ordem decrescente
        }
    }

    void exibir() {
        for (const int &valor : dados) {
            cout << valor << " ";
        }
        cout << endl;
    }

    // Algoritmo 1: Bubble Sort
    void bubbleSort() {
        comparacoes = 0;
        trocas = 0;
        for (size_t i = 0; i < dados.size() - 1; ++i) {
            for (size_t j = 0; j < dados.size() - i - 1; ++j) {
                comparacoes++;
                if (dados[j] > dados[j + 1]) {
                    swap(dados[j], dados[j + 1]);
                    trocas++;
                }
            }
        }
    }

    // Algoritmo 2: Merge Sort
    void merge(int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<int> L(n1), R(n2);
        for (int i = 0; i < n1; i++)
            L[i] = dados[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = dados[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            comparacoes++;
            if (L[i] <= R[j]) {
                dados[k++] = L[i++];
            } else {
                dados[k++] = R[j++];
            }
        }

        while (i < n1) dados[k++] = L[i++];
        while (j < n2) dados[k++] = R[j++];
    }

    void mergeSort(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(left, mid);
            mergeSort(mid + 1, right);
            merge(left, mid, right);
        }
    }

    // Algoritmo 3: Counting Sort
    void countingSort() {
        int maxVal = *max_element(dados.begin(), dados.end());
        vector<int> contagem(maxVal + 1, 0);

        for (int valor : dados) {
            contagem[valor]++;
        }

        int index = 0;
        for (int i = 0; i <= maxVal; i++) {
            while (contagem[i]-- > 0) {
                dados[index++] = i;
                trocas++;  // Cada inserção é considerada uma troca
            }
        }
    }

    void mostrarResultados(chrono::duration<double> duracao) {
        cout << "Vetor ordenado:\n";
        exibir();
        cout << "Tempo de execução: " << duracao.count() << " segundos\n";
        cout << "Número de comparações: " << comparacoes << "\n";
        cout << "Número de trocas: " << trocas << "\n";
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    char reiniciar;

    do {
        // Escolher quantidade de valores
        int tamanho;
        cout << "Escolha a quantidade de valores:\n1) 10\n2) 100\n3) 1000\n4) 10000\n";
        int opcao;
        cin >> opcao;

        switch (opcao) {
            case 1: tamanho = 10; break;
            case 2: tamanho = 100; break;
            case 3: tamanho = 1000; break;
            case 4: tamanho = 10000; break;
            default: 
                cout << "Opção inválida. Usando 10 como padrão.\n"; 
                tamanho = 10; 
                break;
        }

        Ordenador ordenador(tamanho);

        // Escolher como os valores serão dispostos
        cout << "\nEscolha como os valores serão dispostos:\n1) Ordenados Descendentes\n2) Aleatórios\n";
        cin >> opcao;
        if (opcao == 1) {
            ordenador.preencherDecrescente();
        } else {
            ordenador.preencherAleatorio();
        }

        cout << "\nVetor antes da ordenação:\n";
        ordenador.exibir();

        // Escolher algoritmo de ordenação
        cout << "\nEscolha o algoritmo de ordenação:\n";
        cout << "1) Bubble Sort\n";
        cout << "2) Merge Sort\n";
        cout << "3) Counting Sort\n";
        int algoritmo;
        cin >> algoritmo;

        auto inicio = chrono::high_resolution_clock::now(); // Início do temporizador

        switch (algoritmo) {
            case 1:
                cout << "\nExecutando Bubble Sort...\n";
                ordenador.bubbleSort();
                break;
            case 2:
                cout << "\nExecutando Merge Sort...\n";
                ordenador.mergeSort(0, tamanho - 1);
                break;
            case 3:
                cout << "\nExecutando Counting Sort...\n";
                ordenador.countingSort();
                break;
            default:
                cout << "Opção inválida.\n";
                return 1; // Termina o programa se a opção for inválida
        }

        auto fim = chrono::high_resolution_clock::now(); // Fim do temporizador
        chrono::duration<double> duracao = fim - inicio;

        ordenador.mostrarResultados(duracao); // Mostra os resultados

        // Perguntar se deseja reiniciar
        cout << "\nDeseja reiniciar o programa? (s/n): ";
        cin >> reiniciar;

    } while (reiniciar == 's' || reiniciar == 'S');

    cout << "Programa encerrado.\n";
    return 0;
}
