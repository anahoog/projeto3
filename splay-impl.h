#ifndef SPLAY_SPLAY_IMPL_H
#define SPLAY_SPLAY_IMPL_H
#include "splay.h"

namespace splay {

    template <typename T> Nodo <T> * cria_nodo(const T & algo) {
        Nodo<T> *novo;
        novo = new Nodo<T>;

        novo->dado = algo;
        novo->esq = nullptr;
        novo->dir = nullptr;
        novo->pai = nullptr;

        return novo;
    }

    template <typename T> Splay <T> cria_splay() {
        Splay<T> arv;
        arv.raiz = nullptr;

        return arv;
    }

    template <typename T> bool splay_vazia (Splay <T> & arv) {
        return arv.raiz == nullptr;
    }


    template <typename T> int altura (Nodo <T> * nodo){
        if (nodo->esq == nullptr && nodo->dir == nullptr) return 0;

        int altura_esq = 0, altura_dir = 0;

        if (nodo->esq != nullptr) {
            altura_esq = 1 + altura(nodo->esq);
        }

        if (nodo->dir != nullptr){
            altura_dir = 1 + altura(nodo->dir);
        }

        if (altura_esq > altura_dir){
            return altura_esq;
        }
        return altura_dir;
    }


    template <typename T> int fator_balanceamento (Nodo <T> * nodo){


    }


    template <typename T> void splay_adiciona (Splay <T> & arv, const T & algo){

        if (splay_vazia(arv)) {
            arv.raiz = cria_nodo(algo);
        }else {
            Nodo<T> * atual = arv.raiz;

            while (true) {
                //passo 1: Se o dado procurado for igual ao dado contido no nodo atual, sobrescreve o dado do nodo atual e encerra a inserção
                if (algo == atual->dado) {
                    atual->dado = algo;
                    return;
                }
                if (algo < atual->dado) {
                    if (atual->esq != nullptr) {
                        atual = atual->esq;
                    }else {
                        atual->esq = cria_nodo(algo);
                        atual->esq->pai = atual;
                        move_para_raiz(arv,atual);
                        return;
                    }
                }else {
                    if (atual->dir != nullptr) {
                        atual = atual->dir;
                    }
                    else {
                        atual->dir = cria_nodo(algo);
                        atual->dir->pai = atual;
                        move_para_raiz(arv,atual);
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
        }//std::cout<<"dado inexistente"<<std::endl;
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
                        zig(nodo);
                        zag(nodo);
                    }

                    // 2.3 Se for caso zagzig faça a transformação zag e depois zig no nodo
                    else if (testa_zagzig(nodo)) {
                        zag(nodo);
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
        Nodo<T> * nodoA = nodoB->pai;
        Nodo<T> * sub2=nullptr, * up;
        up = nodoA->pai;

        sub2 = nodoB->dir;

        nodoB->pai = up;
        if(up!= nullptr){
            if (na_esquerda(nodoA)) {
                up->esq = nodoB;
            }
            else {
                up->dir = nodoB;
            }
        }

        nodoA->esq = sub2;

        if (sub2 != nullptr){
            sub2->pai = nodoA;
        }
        nodoB->dir = nodoA;
        nodoA->pai = nodoB;

        return nodoB;
    }

    template <typename T> Nodo<T> * zag (Nodo <T> * nodoA) {
        Nodo<T> * nodoB = nodoA->pai;
        Nodo<T> * sub2=nullptr, * up;
        up = nodoB->pai;

        sub2 = nodoA->dir;

        nodoA->pai = up;
        if(up!= nullptr){
            if (na_esquerda(nodoB)) {
                up->esq = nodoA;
            }
            else {
                up->dir = nodoA;
            }
        }

        nodoB->dir = sub2;

        if (sub2 != nullptr){
            sub2->pai = nodoB;
        }
        nodoA->dir = nodoB;
        nodoB->pai = nodoA;

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
