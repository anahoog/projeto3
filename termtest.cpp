//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <functional>
#include "Terminal.h"
#include "gtest/gtest.h"

using namespace std;

#define PROG "./Prog"

struct Result {
    string w;
    int n;

    Result(const string & s) {
        istringstream inp(s);

        inp >> w >> n;
        if (inp.fail()) throw s;
    }
    Result() {}
    bool operator==(const Result & o) const {
        return w == o.w;
    }
    bool operator<(const Result & o) const {
        if (n == o.n) return w < o.w;
        return n < o.n;
    }

    class R_Hash {
    public:
        long operator()(const Result & r) const {
            hash<string> func;

            long h = func(r.w) ^r.n;
            return h;
        }
    };

    operator string() const {
        string r = w + ' ' + to_string(n);
        return r;
    }

};

struct Aluno {
    string nome;
    string matricula;

    Aluno() {}
    Aluno(const string & name, const string & m): nome(name), matricula(m) {}
};

vector<Aluno> le_matriculas(int n) {
    vector<Aluno> l;
    if (n == 0) return l;

    ifstream arq("../matriculas.txt");

    string nome, m;
    while (getline(arq, m, ',')) {
        getline(arq, nome);
        l.push_back(Aluno(nome, m));
    }

    random_shuffle(l.begin(), l.end());
    l.erase(l.begin()+n, l.end());

    return l;
}

void roda(int n) {
    string cmd = PROG;
    Terminal term(cmd);
    auto v = le_matriculas(n);

    for (auto & aluno: v) {
        auto prompt = term.leAlgo();
        if (prompt != "Digite matricula>") {
            FAIL() << "Deve ser apresentado um prompt antes de ler o número de matrícula." << endl
                   << " Seu programa apresentou isto: " << prompt << endl;
        }
        term.escreva(aluno.matricula+'\n');
        auto nome = term.leLinha();
        strip(nome);
        string name = "Estudante: " + aluno.nome;
        if (nome != name) {
            FAIL() << "Matrícula " << aluno.matricula << ", deveria mostrar " << name << endl
                   << "Seu programa informou: " << nome << endl;
        }
    }
    auto prompt = term.leAlgo();
    term.escreva("\n");
    auto fim = term.leAlgo();
    if (not fim.empty()) {
        FAIL() << "Seu programa deve terminar ao ler uma linha vazia !" << endl;
    }
}

//bool operator!=(const vector<Result> & v1, const vector<Result> & v2) {
//    unordered_set<Result,Result::R_Hash> set;
//
//    for (auto & r: v2) set.insert(r);
//    for (auto & r: v1) {
//        if (! set.count(r)) return true;
//    }
//
//    return false;
//}

TEST(TermTest, Geral) {
    for (int j=0; j < 10; j++) roda(1+(rand() % 7));
}

TEST(TermTest, Nada) {
    roda(0);
}

