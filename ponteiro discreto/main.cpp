#include <iostream>
#include <cmath>

using namespace std;

int main(){

    // MATRIZ
    int n_linhas, n_colunas;
    n_linhas = 8;
    n_colunas = 8;
    int matriz[n_linhas][n_colunas];
    for (int i_linha = 0; i_linha<n_linhas; i_linha++){
        for (int i_coluna = 0; i_coluna<n_colunas; i_coluna++){
            matriz[i_linha][i_coluna] = 0;
        }
    }

    // PONTEIRO
    //(oposto/adjacente)*x - floor
    int oposto, adjacente;
    oposto = 1;
    adjacente = 1;

    // LÓGICA
    double cord_entrada_coluna;
    double cord_saida_coluna;
    
    int i_entrada_coluna;
    int i_saida_coluna;

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

    for (int i = 0; i<n_linhas; i++){
        for (int c = 0; c<n_colunas; c++){
            cout << matriz[i][c] << " ";
        }
        cout << endl;
    }


    return 0;
}