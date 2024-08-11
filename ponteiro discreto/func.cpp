#include <iostream>
#include <cmath>

using namespace std;

struct Matrix  // must have int** return type to resolve this
{
    int m[8][8];
};


Matrix analogic_to_digital(int matrix[8][8], int n_linhas, int n_colunas, int oposto, int adjacente){  // must pass int** matrix to achieve variable size - then n_linhas and n_colunas will be actually effective

    double cord_entrada_coluna, cord_saida_coluna;
    int i_entrada_coluna, i_saida_coluna;

    cord_entrada_coluna = 0;  // index do pixel de entrada na coluna
    cord_saida_coluna = ((double)oposto/adjacente);  // index do pixel de saida da coluna ( = index do pixel de entrada na próxima)

    for (int coluna = 0; coluna<n_colunas; coluna++){  // entra em coluna 0 até n


        if (cord_saida_coluna==floor(cord_saida_coluna)) cord_saida_coluna-=1;
        
        i_entrada_coluna = floor(cord_entrada_coluna);
        i_saida_coluna = floor(cord_saida_coluna);

        for (int linha = i_entrada_coluna; linha<=i_saida_coluna; linha++){  // entra em linha de entrada até linha de saída da coluna
            matrix[n_linhas-linha-1][coluna]=1;
        }

        cord_entrada_coluna = ((double)oposto/adjacente)*coluna;  // index do pixel de entrada na coluna
        cord_saida_coluna = ((double)oposto/adjacente)*(coluna+1);  // index do pixel de saida da coluna ( = index do pixel de entrada na próxima)

    }
    return matrix;
}

int main(){

    // CREATE MATRIX as an 2d array
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
    //(oposto/adjacente)*x -> floor
    int oposto, adjacente;
    oposto = 1;
    adjacente = 1;


    // PRINT

    for (int i = 0; i<n_linhas; i++){
        for (int c = 0; c<n_colunas; c++){
            cout << matriz[i][c] << " ";
        }
        cout << endl;
    }

    return 0;
}