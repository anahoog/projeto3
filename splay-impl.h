#ifndef SPLAY_SPLAY_IMPL_H
#define SPLAY_SPLAY_IMPL_H
#include "splay.h"

namespace splay {
    /*-------------------nodo---------------------*/
    template <typename T> Nodo <T> * cria_nodo(const T & algo) {
        Nodo<T> *novo;
        novo = new Nodo<T>;
        novo->dado = algo;
        novo->esq = nullptr;
        novo->dir = nullptr;
        novo->pai = nullptr;
        //arv.raiz(novo);
        return novo;
    }  //ok


    /*-------------------Splay---------------------*/
    template <typename T> Splay <T> cria_splay() {
        Splay<T> arv;
        arv.raiz = nullptr;
        return arv;
    }


    template <typename T> bool splay_vazia (Splay <T> & arv) {
        return arv.raiz == nullptr;
    } //ok


    template <typename T> int altura (Nodo <T> * nodo){
        if (nodo->esq == nullptr && nodo->dir == nullptr) return 0;

        int he = 0, hd = 0;

        // Calcula do lado esquerdo
        if (nodo->esq != nullptr) he = 1 + altura(nodo->esq);

        // Calcula do lado direito
        if (nodo->dir != nullptr) hd = 1 + altura(nodo->dir);

        // retorna o que for maior
        if (he > hd) return he;
        else return hd;
    } //ok


    template <typename T> int fator_balanceamento (Nodo <T> * nodo){


    }


    template <typename T> void splay_adiciona (Splay <T> & arv, const T & algo){

        if (splay_vazia(arv)) {
            arv.raiz = cria_nodo(algo);
        }
        else {
            Nodo<T> *atual = arv.raiz;
            bool teste = true;

            while (teste) {
                //passo 1: Se o dado procurado for igual ao dado contido no nodo atual, sobrescreve o dado do nodo atual e encerra a inserção
                if (atual->dado == algo) {
                    arv.raiz->dado = algo;
                    return;
                }

                //passo 2: Se o dado for menor que o do nodo atual, o nodo atual passa a ser o nodo da esquerda (caso exista), e volta ao passo 1.
                if (algo < atual->dado) {
                    if (atual->esq != nullptr) {
                        atual = atual->esq;
                    }
                        // * Se nodo esquerdo não existir, cria um novo nodo com o nodo dado e conecta-o à esquerda do nodo atual, encerrando a inserção.
                    else {
                        atual->esq = cria_nodo(algo);
                        atual->esq->pai = atual;
                        teste = false;
                        move_para_raiz(arv,atual);
                        return;
                    }
                }

                //Se o dado for maior que o do nodo atual, o nodo atual passa a ser o nodo da direita (caso exista), e volta ao passo 1.
                if (algo > atual->dado) {
                    if (atual->dir != nullptr) {
                        atual = atual->dir;
                    }
                        //Se nodo direito não existir, cria um novo nodo com o nodo dado e conecta-o à direita do nodo atual, encerrando a inserção.
                    else {
                        atual->dir = cria_nodo(algo);
                        atual->dir->pai = atual;
                        move_para_raiz(arv,atual);

                        teste = false;
                        return;
                    }

                }

            }
        }

    }


    template <typename T> T splay_acessa_dado (Splay <T> & arv, const T & algo) {

        Nodo <T> * dado_atual = arv.raiz;

        while (dado_atual != nullptr) {

            if (dado_atual->dado == algo) {
                return dado_atual->dado;
            }
            if (algo < dado_atual->dado) {
                dado_atual = dado_atual->esq;
                zig(dado_atual);
            }
            else {
                dado_atual = dado_atual->dir;
                zag(dado_atual);
            }
        }std::cout<<"dado inexistente"<<std::endl;

    }


    template <typename T> void move_para_raiz (Splay <T> & arv, Nodo <T> * nodo) {

        // Enquanto nodo não estiver na raiz FAÇA
        while (nodo->pai != nullptr) {
            // 1. Se pai do nodo for a raiz, faça uma transformação simples: Zig ou zag
            if(nodo->pai->pai == nullptr) {
                //se nodo esquerda, faça zig
                if (na_esquerda(nodo)) {
                    zig(nodo);
                }
                //se não zag
                else {
                    zag(nodo);
                }
            }

            // 2. Senão:
            else{
                    // 2.1 Se for caso zigzig faça a transformação zig no pai do nodo, e depois no nodo
                    if (testa_zigzig(nodo)) {
                        zig(nodo->pai);
                        zig(nodo);
                    }

                    // 2.2 Se for caso zigzag faça a transformação zig e depois zag no nodo
                    else if (testa_zigzag(nodo)) {
                        zig(nodo->pai);
                        zag(nodo);
                    }

                    // 2.3 Se for caso zagzig faça a transformação zag e depois zig no nodo
                    else if (testa_zagzig(nodo)) {
                        zag(nodo->pai);
                        zig(nodo);
                    }

                    // 2.4 Se for caso zagzag faça a transformação zag no pai do nodo, e depois no nodo
                    else if (testa_zagzag(nodo)) {
                        zag(nodo->pai);
                        zag(nodo);
                    }

            }
        }

        // Ao sair do laço, atualiza a raiz da árvore com "nodo"
        arv.raiz = nodo;
    }


    /*-----------------------ZigZag-----------------------*/

    template <typename T> Nodo <T> * zig (Nodo <T> * nodoB){
        Nodo<T> *nodoA, *sub2=nullptr, *up;
        nodoA = nodoB->pai;
        up = nodoA->pai;

        nodoB->pai = up;
        if(up!= nullptr){
            if (na_esquerda(nodoA)) up->esq = nodoB;
            else up->dir = nodoB;

        }

        sub2 = nodoB->esq;

        nodoB->esq = nodoA;
        nodoA->pai = nodoB;

        nodoA->dir = sub2;
        if (sub2 != nullptr) sub2->pai = nodoA;

        return nodoB;
    }

    template <typename T> Nodo<T> * zag (Nodo <T> * nodoA) {
        Nodo<T> *nodoB, * sub2 = nullptr, * up;

        nodoB = nodoA->pai;

        up = nodoB->pai;

        nodoA->pai = up;
        if(up!= nullptr){
            if (na_esquerda(nodoB)) up->esq = nodoA;
            else up->dir = nodoA;
        }


        sub2 = nodoA->esq;

        nodoA->esq = nodoB;
        nodoB->pai = nodoA;

        nodoB->dir = sub2;
        if (sub2 != nullptr) sub2->pai = nodoB;


        return nodoA;
    }

    /*--------------------Testes------------------------------*/

    template <typename T> bool na_esquerda (Nodo <T> * nodo){
        return nodo->pai->esq==nodo;
    }

    template <typename T> bool na_direita (Nodo <T> * nodo){
        return nodo->pai->dir==nodo;
    }

    template <typename T> bool testa_zigzig (Nodo <T> *nodo){
        return (na_esquerda(nodo) && na_esquerda(nodo->pai));
    }

    template <typename T> bool testa_zigzag (Nodo <T> *nodo){
        return (na_esquerda(nodo) && na_direita(nodo->pai));
    }

    template <typename T> bool testa_zagzig (Nodo <T> *nodo){
        return (na_direita(nodo) && na_esquerda(nodo->pai));
    }

    template <typename T> bool testa_zagzag (Nodo <T> *nodo){
        return(na_direita(nodo) && na_direita(nodo->pai));
    }

    template <typename T> T altura_arv (Splay <T> & arv){
        Nodo <T> * dado_atual = arv.raiz;
        int a = altura(dado_atual);
        return  a;
    }
}
#endif //SPLAY_SPLAY_IMPL_H
