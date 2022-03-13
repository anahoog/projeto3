#ifndef SPLAY_SPLAY_H
#define SPLAY_SPLAY_H

namespace splay {

    template <typename T> struct Nodo {
        Nodo<T> * esq, * dir, * pai;
        T dado;
    };

    template <typename T> struct Splay{
        Nodo <T> * raiz;
    };

    template <typename T> Splay <T> cria_splay();

    template <typename T> bool splay_vazia (Splay <T> & arv);

    template <typename T> void splay_adiciona (Splay <T> & arv, const T & algo);

    template <typename T> T splay_acessa_dado (Splay <T> & arv, const T & algo);

    template <typename T> int altura(Nodo<T> * nodo);

    template <typename T> int fator_balanceamento(Nodo<T> * nodo);

    template <typename T> Nodo <T> * zig (Nodo<T> * nodoA);

    template <typename T> Nodo <T> * zag (Nodo<T> * nodoB);

    template <typename T> bool testa_zigzig (Nodo<T> * nodo);

    template <typename T> bool testa_zigzag (Nodo<T> * nodo);

    template <typename T> bool testa_zagzig (Nodo<T> * nodo);

    template <typename T> bool testa_zagzag (Nodo<T> * nodo);

    template <typename T> int altura_arv (Splay <T> & arv);

}
#endif //SPLAY_SPLAY_H

#include "splay-impl.h"

