#include <iostream>
#include <string>

using namespace std;

int main(){

    string dna;
    cin >> dna;

    double l = dna.length();


    char past = dna[0];
    char current;
    int seq = 1;
    int bigger_seq = 1;

    for (int i = 1; i<l; i++){
        current = dna[i];

        if (current == past){
            seq+=1;
        }

        else {
            if (seq>bigger_seq){
                bigger_seq = seq;
            }
            seq = 1;
        }
        past = current;
    }
    if (seq>bigger_seq){
        bigger_seq = seq;
    }
    cout<<bigger_seq<<endl;


    return 0;
}