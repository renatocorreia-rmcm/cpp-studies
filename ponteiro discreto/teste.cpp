#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>


using namespace std;

int main(){
    double cord_entrada_coluna;
    double cord_saida_coluna;
    
    int i_entrada_coluna;
    int i_saida_coluna;

    // LÓGICA
    for (int ad = 1; ad<64; ad++){
        // MATRIZ
        int n_linhas, n_colunas;
        n_linhas = 64;
        n_colunas = 64;
        int matriz[n_linhas][n_colunas];
        for (int i_linha = 0; i_linha<n_linhas; i_linha++){
            for (int i_coluna = 0; i_coluna<n_colunas; i_coluna++){
                matriz[i_linha][i_coluna] = 0;
            }
        }


        // PONTEIRO
        //(oposto/adjacente)*x - floor
        int oposto, adjacente;
        oposto = 64;
        adjacente = ad;


        for (int coluna = 0; coluna<n_colunas; coluna++){  // entra em coluna 0 até n
            cord_entrada_coluna = ((double)oposto/adjacente)*coluna;  // index do pixel de entrada na coluna
            cord_saida_coluna = ((double)oposto/adjacente)*(coluna+1);  // index do pixel de saida da coluna ( = index do pixel de entrada na próxima)

            if (cord_saida_coluna==floor(cord_saida_coluna)) cord_saida_coluna-=1;
            
            i_entrada_coluna = floor(cord_entrada_coluna);
            i_saida_coluna = floor(cord_saida_coluna);

            for (int linha = i_entrada_coluna; linha<=i_saida_coluna; linha++){  // entra em linha de entrada até linha de saída da coluna
                matriz[n_linhas-linha-1][coluna]=1;
            }
        }


        // PRINT
        cout << "\033[2J\033[1;1H";  // Clear screen using ANSI escape codes
        cout << endl;
        for (int i = 0; i<n_linhas; i++){
            for (int c = 0; c<n_colunas; c++){
                cout << (matriz[i][c]==0?' ':'#') << " ";
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    // LÓGICA
    for (int op = 64; op>0; op--){
        // MATRIZ
        int n_linhas, n_colunas;
        n_linhas = 64;
        n_colunas = 64;
        int matriz[n_linhas][n_colunas];
        for (int i_linha = 0; i_linha<n_linhas; i_linha++){
            for (int i_coluna = 0; i_coluna<n_colunas; i_coluna++){
                matriz[i_linha][i_coluna] = 0;
            }
        }


        // PONTEIRO
        //(oposto/adjacente)*x - floor
        int oposto, adjacente;
        oposto = op;
        adjacente = 64;


        for (int coluna = 0; coluna<n_colunas; coluna++){  // entra em coluna 0 até n
            cord_entrada_coluna = ((double)oposto/adjacente)*coluna;  // index do pixel de entrada na coluna
            cord_saida_coluna = ((double)oposto/adjacente)*(coluna+1);  // index do pixel de saida da coluna ( = index do pixel de entrada na próxima)

            if (cord_saida_coluna==floor(cord_saida_coluna)) cord_saida_coluna-=1;
            
            i_entrada_coluna = floor(cord_entrada_coluna);
            i_saida_coluna = floor(cord_saida_coluna);

            for (int linha = i_entrada_coluna; linha<=i_saida_coluna; linha++){  // entra em linha de entrada até linha de saída da coluna
                matriz[n_linhas-linha-1][coluna]=1;
            }
        }


        // PRINT
        cout << "\033[2J\033[1;1H";  // Clear screen using ANSI escape codes
        cout << endl;
        for (int i = 0; i<n_linhas; i++){
            for (int c = 0; c<n_colunas; c++){
                cout << (matriz[i][c]==0?' ':'*') << " ";
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}