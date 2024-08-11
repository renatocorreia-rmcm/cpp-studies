#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    // INPUTS

    int lojas;  // N
    cin >> lojas;

    int tabaco;  // K
    cin >> tabaco;

    vector<int> distancias;  // Ai
    distancias.push_back(0);
    int buffer;
    for (int i = 0; i<lojas; i++){
        cin>>buffer;
        distancias.push_back(buffer);
    }

    vector<int> quantidades;  // Bi
    quantidades.push_back(0);
    for (int i = 0; i<lojas; i++){
        cin>>buffer;
        quantidades.push_back(buffer);
    }


    // ESCOPO GLOBAL


    int pos = 0;  // INDICE

    int limite = 0;
    int orcamento;  //quanto saci gasta para chegar no limite

    int indice_melhor = pos+1;  // INDICE do saldo_melhor
    int saldo_melhor = quantidades[indice_melhor];  // melhor posição que não a atual

    int deslocamentos = 0;


    // OPERAÇÕES
    while (true){
        //conferir ate que posição o saci chega se não parar em nada = LIMITE

        orcamento = 0;
        for (int i = pos+1; (pos<lojas && orcamento+distancias[i]-distancias[pos+1]<=tabaco); i++)  // itera enquanto houver lojas e o proximo orcamento não extrapolar
        {
            orcamento = (distancias[i]-distancias[pos]);
            limite = i;
        }

        if (limite >= lojas)  // END
        {
            cout<<deslocamentos<<endl;
            break;
        }
        else if (limite == pos != 0)  // -1
        {
            cout<<-1<<endl;
            break;
        }
        

        //nesse limite, procurar casa com mais tabaco, levando em conta gasto até o limite = SALDO_MELHOR  // pode ser mesclado com passo anterior se somar distancia de cada loja com sua quantidade de tabaco para encontrar a mais vantajosa

        indice_melhor = pos+1;  // INDICE do saldo_melhor 
        saldo_melhor = quantidades[indice_melhor]-(distancias[limite]-distancias[indice_melhor]);  // melhor saldo que não o atual

        for (int i = pos+2; i <= limite; i++)
        {
            int quantidade = quantidades[i];
            int distancia_ate_limite = distancias[limite]-distancias[i];
            int saldo = quantidade - distancia_ate_limite;

            if (saldo > saldo_melhor)
            {
                saldo_melhor = saldo;
                indice_melhor = i;
            }
        }
        

        //andar até chegar nela
        tabaco = saldo_melhor;
        pos = indice_melhor;
        deslocamentos +=1;


        //repetir processo
    }

    return 0;
}