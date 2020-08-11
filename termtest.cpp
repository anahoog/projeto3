//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <sstream>
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

vector<Result> roda(const string & cmd) {
    Terminal term(cmd);

    auto res = term.leLinhas();
    vector<Result> v;

    for (auto & s: res) v.push_back(Result(s));
    return v;
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

void verifica(int n, int k) {
    string arq = "cat ../data/res"+to_string(n)+"_"+to_string(k)+".txt";
    string arqres = PROG;
    arqres += " ../data/arq"+to_string(n)+".txt " + to_string(k);

    try {
        auto v = roda(arq);
        auto res = roda(arqres);

        if (v != res) {
//        sort(v.begin(), v.end());
//        sort(res.begin(), res.end());
            FAIL() << "Esperado: " << v2str(v, ", ") << endl
                   << "Obtido: " << v2str(res, ", ");
        }
    } catch (string s) {
        FAIL() << "Exceção ao ler isto dos seus resultados: " << s;
    }
}

TEST(TermTest, Arquivo1) {
    verifica(1, 7);
    verifica(1, 8);
}

TEST(TermTest, Arquivo2) {
    verifica(2, 3);
    verifica(2, 5);
}

TEST(TermTest, Arquivo3) {
    verifica(3, 5);
    verifica(3, 7);
    verifica(3, 10);
}
