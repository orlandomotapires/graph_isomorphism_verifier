#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 10;

vector<vector<char>> g(MAX);
vector<char> nomesg;

int main(){
    string nome_arq = "adj.txt";
    ifstream arquivo(nome_arq);

    if(!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    vector<string> linhas;
    string linha;
    while(getline(arquivo, linha)) {
        linhas.push_back(linha);
    }

    arquivo.close();

    for(int i = 0; i < linhas[0].size(); i++){
        g[i].push_back(linhas[0][i]);
    }

    for(int i = 1; i < linhas.size(); i++){
        for(int j = 0; j < linhas[i].size(); j++){
            if(linhas[i][j] == '1'){
                g[i-1].push_back(g[j][0]);            
            }
        }
    }

    cout << "Lista ADJ final: " << endl;
    for(int i = 0; i < 4; i++){
        cout << g[i][0] << " -> ";
        for(int j = 1; j < g[i].size(); j++){
            cout << g[i][j] << " ";
        }
        cout << endl;
    }

//     ABCD
//   A 1111
//   B 1011
//   C 1101
//   D 1111
     
    // A B C D
    return 0;
}