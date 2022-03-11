//
// Created by anahoog on 10/03/2022.
//
#include <iostream>
#include "main.h"
#include <ctype.h>
#include "interface.h"


void displayMenu(){
    cout << "====================================================="<< endl;
    cout << "             Projeto 3 - PROG2                       " << endl;
    cout << "=====================================================" << endl;
    cout << " Escolha uma das Opções abaixo: " << endl;
    cout << "1. Testes de Funcionamento" << endl;
    cout << "2. Exercicio Matriculas" << endl;
    cout << "3. Sair" << endl;
    cout<<endl;
}

void menu_do_usuario () {
    string opc;
    displayMenu();
    getline(cin, opc);
    opc=tratarErroOpc(opc);
    while (opc != "3") {

        if(opc=="1"){
            splay_test();
            cout<<endl;

        }else{
            cout<<"Opção inválida! Tente Novamente"<<endl;
            cout<<endl;
        }
        menu_do_usuario();
    }
    void splay_test(){

    }

    //trata o erro caso o usuario nao digite o numero que eh para digitar
    string tratarErroOpc(const string &opc){
        string aux;
        int x = opc.find_first_not_of( ' ');
        aux = opc[x];
        return aux;
    }


}