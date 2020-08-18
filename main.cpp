// implemente aqui seu programa
#include <prglib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <Terminal.h>

using prglib::arvore;
using namespace std;

struct DEstudante {
    int matricula;
    string nome;

    bool operator==(const DEstudante & outro) const {
        return matricula == outro.matricula;
    }

    bool operator<(const DEstudante & outro) const {
        return matricula < outro.matricula;
    }
};

// converte uma string no formato "numero_matricula,nome_estudante"
// para um valor DEstudante
// se "desc" for inválido, retorna DEstudante com matricula = 0
DEstudante cria_estudante(const string & desc) {
    DEstudante alguem = {0, ""};

    auto par = separa(desc, ",");
    if (par.size() == 2) { // "desc" tem duas substrings
        try {
            alguem.matricula = stoi(par[0]);

            if (par[1].empty()) alguem.matricula = 0;
            else alguem.nome = par[1];
        } catch (...) {
            // pode ser que número de matricula seja inválido (não numérico)
            // isso vai gerar uma exceção em stoi !
            // faz nada ... matricula ficará com zero
        }
    }

    return alguem;
}

// formato de cada linha:
// num_matricula,nome_estudante
// - num_matricula: numero inteiro
arvore<DEstudante> * le_arquivo(const string & nome_arq) {
    ifstream arq(nome_arq);

    // erro: arquivo não pode ser aberto
    if (! arq.is_open()) return nullptr;

    arvore<DEstudante> * arv = nullptr;
    string linha;

    while (getline(arq, linha)) {
        DEstudante alguem = cria_estudante(linha);
        if (alguem.matricula > 0) { // se dado lido for válido
            // se árvore ainda não existe, crie-a usando este dado como valor da raiz
            if (arv == nullptr) arv = new arvore<DEstudante>(alguem);
            else arv->adiciona(alguem); // senão acrescenta-o a árvore
        }
//        cout << alguem.matricula << ": " << alguem.nome << endl;
    }

    return arv;
}

int main(int argc, char * argv[]) {
    // carregar os dados do arquivo. Resultado é uma árvore com os dados
    arvore<DEstudante> * dados = le_arquivo(argv[1]);
    if (dados == nullptr) {
        cout << "Não conseguiu ler o arquivo " << argv[1] << endl;
        return 0;
    }

    cout << "Altura da árvore: " << dados->altura() << endl;

    // apresenta ciclicamente o prompt para o usuário,
    // para que se digite uma matrícula e se faça a consulta na árvore
    DEstudante fulano = {112233, ""};
    try {
        DEstudante aluno = dados->obtem(fulano);

        cout << "Matrícula " << aluno.matricula << ": " << aluno.nome << endl;
    } catch(...) {
        cout << "Matrícula " << fulano.matricula << ": NÃO ENCONTRADA" << endl;
    }
}