#include <iostream>
#include <string>
#include <iostream>
#include "splay.h"
#include "interface.h"
#include <fstream>
#include <prglib.h>
#include <unordered_map>

using namespace splay;
using namespace std;

void teste_splay(){
    cout<<"-------------------------------------------------------"<<endl;
    cout<<" "<<endl;
    cout<<"Teste 1: Criação da Árvore Splay:"<<endl;
    Splay<int> arv = cria_splay<int>();
    cout<<" "<<endl;
    if(splay_vazia(arv)){
        cout<<"* Árvore Criada com Sucesso *"<<endl;
    }else{
        cout<<"* Falha na Criação da Árvore *"<<endl;
    }
    cout<<" "<<endl;

    cout<<"-------------------------------------------------------"<<endl;

    cout<<" "<<endl;
    cout<<"Teste 2: Adicionar nodo na Árvore:"<<endl;
    cout<<"1"<<endl;
    splay_adiciona(arv,1);
    cout<<"2"<<endl;
    splay_adiciona(arv,2);
    cout<<"3"<<endl;
    splay_adiciona(arv,3);
    cout<<"4"<<endl;
    splay_adiciona(arv,4);
    cout<<"5"<<endl;
    splay_adiciona(arv,5);
    cout<<" "<<endl;

    cout<<"-------------------------------------------------------"<<endl;

    cout<<" "<<endl;
    cout<<"Teste 3: Altura da Árvore:"<<endl;


    cout<<" "<<endl;
    cout<<"* Altura: "<<altura_arv(arv)<<"* "<<endl;
    cout<<" "<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    cout<<" "<<endl;
    cout<<"Teste 4: Move para Raiz:"<<endl;


    cout<<" "<<endl;
    cout<<"* raiz: "<<arv.raiz->dado<<"* "<<endl;
    cout<<" "<<endl;
    cout<<"-------------------------------------------------------"<<endl;

}

struct dados {
    int matricula;
    string nome;
    bool operator<(const dados &algo){
        if(matricula<algo.matricula){
            return true;
        }
    }
};

bool operator < (const dados & algo, const dados & atual){
    if(algo.matricula < atual.matricula){
        return true;
    }return false;
};

dados separa_str(const string & linha){

    string aux;
    dados varSepara;
    char sep = ',';
    int pos = linha.find_first_not_of(sep);

    while (pos != string::npos) {
        int pos_sep = linha.find(sep, pos);
        if (pos_sep != string::npos) {
            if (pos == 0) {
                aux = linha.substr(pos, pos_sep - pos);
                varSepara.matricula = stoi(aux);
                aux = linha.substr(pos_sep+1);
                varSepara.nome = aux;
            }
        }pos = linha.find_first_not_of(sep, pos_sep);
    }
    return varSepara;
}

bool operator == (const dados & esta, const dados & aquela){
    return esta.matricula == aquela.matricula;
};


int main() {

    //teste_splay();
    ifstream arquivo ("../matriculas.txt");
    string linha;
    dados aluno;

    Splay<dados> arv = cria_splay <dados> ();

    if (!arquivo.is_open()) {
        cout<<"arquivo invalido"<< endl;
        return 0;
    }

    while (getline(arquivo, linha)) {
        aluno = separa_str(linha);
        splay_adiciona(arv,aluno);
    }
    string aux;

    while(true){
        cout << "Digite matricula: ";
        getline(cin, aux);
        if (aux.empty()){
            break;
        }
        dados buscar;
        buscar.matricula = stoi(aux);
        auto obtido = splay_acessa_dado(arv,buscar);
        if(obtido.nome!=""){
            cout<<"Estudante: "<<obtido.nome<<endl;
        }else{
            cout<<"Matricula "<<buscar.matricula<<" desconhecida"<<endl;
        }
    }


    return 0;
}

