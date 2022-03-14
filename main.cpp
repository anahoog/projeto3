#include <iostream>
#include <string>
#include "splay.h"
#include <fstream>

using namespace splay;
using namespace std;

//Função de Teste do programa
void teste_splay(){

    cout<<"-------------------------------------------------------"<<endl;
    cout<<" "<<endl;
    cout<<"Teste 1: Criação do Nodo:"<<endl;
    int aux = 50;
    auto out_nodo = cria_nodo(aux);

    cout<<"Novo nodo: "<<out_nodo->dado<<endl;
    cout<<"Nodo à esquerda:"<<out_nodo->esq<<endl;
    cout<<"Nodo à direita:"<<out_nodo->dir<<endl;
    cout<<"Nodo pai:"<<out_nodo->pai<<endl;
    cout<<" "<<endl;

    cout<<"-------------------------------------------------------"<<endl;
    cout<<" "<<endl;

    cout<<"Teste 2: Criação da Árvore Splay:"<<endl;
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
    cout<<"Teste 3: Adicionar nodo na Árvore:"<<endl;

    splay_adiciona(arv,10);
    splay_adiciona(arv,20);
    splay_adiciona(arv,30);
    splay_adiciona(arv,40);
    splay_adiciona(arv,50);

    cout<<"10"<<endl;
    cout<<"20"<<endl;
    cout<<"30"<<endl;
    cout<<"40"<<endl;
    cout<<"50"<<endl;
    cout<<" "<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    cout<<" "<<endl;

    cout<<"Teste 4: Altura da Árvore:"<<endl;
    cout<<"* Altura: "<<altura_arv(arv)<<"* "<<endl;

    cout<<" "<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    cout<<" "<<endl;

    cout<<"Teste 5: Acessa Dado:"<<endl;
    cout<<"* Raiz atual: "<<arv.raiz->dado<<endl;

    auto nodo = arv.raiz;
    cout<<"* Nodo esquerdo: "<<nodo->esq->dado<<endl;
    cout<<"* Nodo direito: "<<nodo->dir->dado<<endl;
    cout<<"* Nodo pai: "<<nodo->pai<<endl;
    cout<<" "<<endl;

    splay_acessa_dado(arv,30);
    cout<<"* Nova Raiz - Zig: "<<arv.raiz->dado<<endl;
    cout<<"* Nodo esquerdo: "<<arv.raiz->esq->dado<<endl;
    cout<<"* Nodo direito: "<<arv.raiz->dir->dado<<endl;
    cout<<"* Nodo pai: "<<arv.raiz->pai<<endl;
    cout<<" "<<endl;

    splay_acessa_dado(arv,40);
    cout<<"* Nova Raiz - Zag: "<<arv.raiz->dado<<endl;
    cout<<"* Nodo esquerdo: "<<arv.raiz->esq->dado<<endl;
    cout<<"* Nodo direito: "<<arv.raiz->dir->dado<<endl;
    cout<<"* Nodo pai: "<<arv.raiz->pai<<endl;
    cout<<" "<<endl;

    splay_acessa_dado(arv,20);
    cout<<"* Nova Raiz - ZigZig: "<<arv.raiz->dado<<endl;
    cout<<"* Nodo esquerdo: "<<arv.raiz->esq->dado<<endl;
    cout<<"* Nodo direito: "<<arv.raiz->dir->dado<<endl;
    cout<<"* Nodo pai: "<<arv.raiz->pai<<endl;
    cout<<" "<<endl;

    splay_acessa_dado(arv,40);
    cout<<"* Nova Raiz - ZagZag: "<<arv.raiz->dado<<endl;
    cout<<"* Nodo esquerdo: "<<arv.raiz->esq->dado<<endl;
    cout<<"* Nodo direito: "<<arv.raiz->dir->dado<<endl;
    cout<<"* Nodo pai: "<<arv.raiz->pai<<endl;

}

//Estrutura de Dados para classificação de dados em Matricula e Nome do aluno;
struct dados {
    int matricula;
    string nome;
    bool operator<(const dados &algo){
        if(matricula<algo.matricula){
            return true;
        }
    }
};

//Função Separa, onde recebe uma string e separa os dados de acordo com o delimitador da frase;
//Retorna uma variável do tipo dados, contendo a matricula e nome do aluno;
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

//Determinação do operador em relação ao dado "matricula";
bool operator < (const dados & algo, const dados & atual){
    if(algo.matricula < atual.matricula){
        return true;
    }return false;
};

//Determinação do operador em relação ao dado "matricula";
bool operator == (const dados & esta, const dados & aquela){
    return esta.matricula == aquela.matricula;
};

//Exercicio do projeto;
int consulta_splay(){
    /*Primeiro critério:
    * Escreva um programa que leia os dados desse arquivo e os armazene em uma árvore de pesquisa binária.
    */

    //Inicialmente o programa carrega o arquivo utilizado para consulta
    ifstream arquivo ("../matriculas.txt");

    //Caso não seja possível abrir o arquivo, retorna mensagem de erro e encerra o programa.
    if (!arquivo.is_open()) {
        cout<<"arquivo invalido"<< endl;
        return 0;
    }

    //Criação de uma arvore splay do tipo dados, uma estrutura com as informações de matricula e nome de aluno;
    Splay<dados> arv = cria_splay <dados> ();

   //Variável utilizada para armazenar a linha do arqivo;
    string linha;

    //Variável do tipo "dados"(matricula e nome) que receberá o retorno da função "separa_str";
    dados aluno;

    //Enquanto for possível obter uma linha do arquivo, chama-se a função "separa_str" que retornará a matricula e o nome do aluno.
    //O resultado da função separa_str é salvo na variável "aluno" e em seguia, é chamada a função "splay_adiciona", no qual é necessário
    // informar qual arvore será utilizada e qual dado será armazenado;
    while (getline(arquivo, linha)) {
        aluno = separa_str(linha);
        splay_adiciona(arv,aluno);
    }

    /*Segundo crtério do exercicio: programa deve entrar em um loop.
     * Em cada ciclo do loop o programa apresenta este prompt:
     * Digite matricula>
     */

    //Laço de repetição;
    while(true){

        //Variável para obter a entrada de dados do teclado;
        string aux;

        //Requisito do exercicio:
        cout << "Digite matricula>";

        //obter a entrada de dados do teclado e armazenar na variável;
        getline(cin, aux);

        /*Requisito do exercicio:
        *Se for teclado "ENTER", o programa termina.
        */
        if (aux.empty())break;

        //Variável com estrutura matricula e nome para ser utilizada na função "splay_acessa_dado";
        dados buscar;

        //A entrada de dados será convertida de string para inteiro;
        buscar.matricula = stoi(aux);

        //Chama-se a função de acesso à arvore, informando o nome da arvore e o dado necessário.
        //Se a matricula for encotrada, o programa retorna o dado com matricula e nome;
        //Se a matricula não existir, o campo buscar.nome fica em branco e transferido para a variável obtido;
        //Se fosse reaproveitar a variável "buscar", o programa retorna valor incorreto. Ex: digitei a matricula 1 e o programa retornou 0
        dados obtido = splay_acessa_dado(arv,buscar);

        //Se o valor contido na variável "obtio.nome" não estiver em branco, o programa apresenta na tela
        // "Estudante: Um Nome de Um Estudante"
        if(obtido.nome!=""){
            cout<<"Estudante: "<<obtido.nome<<endl;
        }
        /*Requisito do exercicio:
        *Se uma matrícula desconhecida for digitada, seu programa deve apresentar esta mensagem:
        *Matricula MATRICULA_DIGITADA desconhecida
        */
        else{
            cout<<"Matricula "<<buscar.matricula<<" desconhecida"<<endl;
        }
    }
}

int main() {

    //Para Testar o programa, remover as barras da função teste_splay();
   // teste_splay();
   consulta_splay();
}