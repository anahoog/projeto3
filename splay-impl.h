#ifndef SPLAY_SPLAY_IMPL_H
#define SPLAY_SPLAY_IMPL_H
#include "splay.h"

namespace splay {

    //Função Cria o nodo: Recebe o tipo de variável e o dado que deseja adicionar em um nodo;
    template <typename T> Nodo <T> * cria_nodo(const T & algo) {
        Nodo <T> * novo;
        novo = new Nodo <T>;
        novo->dado = algo;
        novo->esq = nullptr;
        novo->dir = nullptr;
        novo->pai = nullptr;

        return novo;
    }

    //Função cria_splay: Cria uma arvore de acordo com o tipo de variável fornecido;
    template <typename T> Splay <T> cria_splay() {
        Splay<T> arv;
        arv.raiz = nullptr;

        return arv;
    }

    //Retorna true se a raiz da avore criada não possui dado, sendo considerada uma arvore vazia;
    template <typename T> bool splay_vazia (Splay <T> & arv) {
        return arv.raiz == nullptr;
    }

    //Função altura (uso privativo): Determina a altura da avore de acordo com qual lado dos nodos é o maior;
    template <typename T> int altura (Nodo <T> * nodo){

        //Se os dois lados do nodo estiverem apontando para nullpointer, a altura da arvore é 0;
        if (nodo->esq == nullptr && nodo->dir == nullptr) return 0;

        int altura_esq = 0, altura_dir = 0;

        //Contador de nodos do lado esquerdo da arvore;
        if (nodo->esq != nullptr) {
            altura_esq = 1 + altura(nodo->esq);
        }

        //Contador de nodos do lado direito da arvore;
        if (nodo->dir != nullptr){
            altura_dir = 1 + altura(nodo->dir);
        }

        //Determina qual dos dois lados é o maior e retorna seu valor. O maior valor é a altura da avore.
        if (altura_esq > altura_dir){
            return altura_esq;
        }
        return altura_dir;
    }

    //Uso Futuro - Função Incompleta
    template <typename T> int fator_balanceamento (Nodo <T> * nodo){


    }

    //Função splay_adiciona: Recebe como parâmetro o nome da arvore e o dado que deseja adicionar na arvore;
    template <typename T> void splay_adiciona (Splay <T> & arv, const T & algo){

        //Se a avore estiver vazia, cria-se um nodo e adiciona na raiz da arvore;
        if (splay_vazia(arv)) {
            arv.raiz = cria_nodo(algo);
        }
        //Caso a arvore não esteja vazia, usa-se a raiz como referência para localizar a posição inicial;
        else {
            Nodo<T> * atual = arv.raiz;

            while (true) {
                //Se o dado que deseja adicionar na arvore já existe, sobrescreve o dado do nodo atual e encerra a inserção
                if (algo == atual->dado) {
                    atual->dado = algo;
                    return;
                }
                //Se o dado a ser adicionado é menor que o dado atual;
                if (algo < atual->dado) {

                    //Se o dado á esquerda do nodo atual não estiver vazio, obtém o próximo nodo à esquerda dele.
                    if (atual->esq != nullptr) {
                        atual = atual->esq;
                    }
                    //Caso o nodo à esquerda do nodo atual esteja vazio, cria-se um nodo com o dado fornecido e adiciona à esquerda
                    //do nodo atual e insere o nodo pai com o valor do nodo atual;
                    else {
                        atual->esq = cria_nodo(algo);
                        atual->esq->pai = atual;

                        //atualiza o nodo raiz com o nodo atual;
                        move_para_raiz(arv,atual);

                        return;
                    }
                }
                //Caso o dado não seja igual ou menor que o dado do nodo atual, ele é maior que o dado do nodo atual.
                //Logo, procura-se o nodo que possua o nodo à direita vazia para então adicionar o dado em um novo nodo e
                // este ser o nodo à direita do nodo atual.
                else {
                    if (atual->dir != nullptr) {
                        atual = atual->dir;
                    }else {
                        atual->dir = cria_nodo(algo);
                        atual->dir->pai = atual;

                        //atualiza o nodo raiz com o nodo atual;
                        move_para_raiz(arv,atual);
                        return;
                    }
                }
            }
        }
    }

    //Função splay_acessa_dado: Recebe como parâmetro o nome da arvore e o dado que deseja localizar na arvore e o torna a raiz da árvore;
    template <typename T> T splay_acessa_dado (Splay <T> & arv, const T & algo) {

        Nodo <T> * dado_atual = arv.raiz;

        while (dado_atual != nullptr) {

            if (dado_atual->dado == algo) {
                move_para_raiz(arv,dado_atual);
                return dado_atual->dado;
            }
            if (algo < dado_atual->dado) {
                dado_atual = dado_atual->esq;
            }
            else {
                dado_atual = dado_atual->dir;
            }
        }
    }

    //Função move_para_raiz: Recebe como parâmetro a avore que terá a raiz atualizada e qual nodo será utilizado;
    template <typename T> void move_para_raiz (Splay <T> & arv, Nodo <T> * nodo) {

        // Enquanto nodo informado não estiver na raiz, repita o processo;
        while (nodo->pai != nullptr) {

            //Se o nodo que é o pai do nodo atual for a raiz:
            //Faça uma transformação simples do tipo Zig ou Zag
            if(nodo->pai->pai == nullptr) {

                //Se nodo atual está à esquerda, chame a função zig;
                if (na_esquerda(nodo)) {
                    zig(nodo);
                }

                //Se o nodo estiver à direita, chame a função zag;
                else {
                    zag(nodo);
                }
            }

            // Se ele não for o nodo raiz
            else{
                    //Chame a função testa_zigzig indicando que o nodo e o pai do nodo estão à esquerda
                    if (testa_zigzig(nodo)) {
                        //faça a transformação zig no nodo pai;
                        zig(nodo->pai);

                        //Chame a função zig no nodo atual;
                        zig(nodo);
                    }

                    //Se não for zigzig, chame a função testa_zigzag, indicando que o nodo está à esquerda e o pai do nodo à direita;
                    else if (testa_zigzag(nodo)) {

                        //Faça zig no nodo;
                        zig(nodo);

                        //Faça zag no nodo;
                        zag(nodo);
                    }

                    //Se não for zigzag, chame a função testa_zagzig, indicando que o nodo está à direita e o pai do nodo à esquerda;
                    else if (testa_zagzig(nodo)) {

                        //Faça zag no nodo;
                        zag(nodo);

                        //Faça zig no nodo;
                        zig(nodo);
                    }

                    //Chame a função testa_zagzag indicando que o nodo e o pai do nodo estão à direita
                    else if (testa_zagzag(nodo)) {

                        //faça a transformação zag no nodo pai;
                        zag(nodo->pai);

                        //Chame a função zag no nodo atual;
                        zag(nodo);
                    }

            }
        }
        // Ao sair do laço, atualiza a raiz da árvore com "nodo"
        arv.raiz = nodo;
    }

    //Função zig: muda a posição do nodo informado que está à esquerda do nodo pai;
    template <typename T> Nodo <T> * zig (Nodo <T> * nodoB){

        //O nodoA recebe o nodo que é o pai do nodoB;
        Nodo<T> * nodoA = nodoB->pai;

        //O sub2 recebe nullptr inicialmente e criamos uma variável para obter o nodo pai;
        Nodo<T> * sub2=nullptr, * up;

        //up recebe o nodo pai do nodoA, que era o nodo pai do nodo pai;
        up = nodoA->pai;

        //sub2 recebe o nodo à direita do nodoB;
        sub2 = nodoB->dir;

        //o nodo pai do nodoB recebe o nodo pai do nodoA;
        nodoB->pai = up;

        //se o nodo up não for nullptr
        if(up!= nullptr){

            //verifique se o nodoA está a esquerda do nodo pai;
            if (na_esquerda(nodoA)) {
                //Se estiver, o nodo a esquerda do nodo superior será o nodoB;
                up->esq = nodoB;
            }
            //Senão, ele estará à direita do nodo up;
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

    //Função zag: muda a posição do nodo informado que está à direita do nodo pai;
    template <typename T> Nodo<T>* zag(Nodo<T> * nodoA) {
        Nodo<T> *nodoB, *sub2=nullptr, *up;
        // nodoB é a raiz desta subárvore
        nodoB = nodoA->pai;
        // up é o nodo pai da raiz desta subárvore
        up = nodoB->pai;

        // atualiza o nodo pai do nodoA (nova raiz):
        // o nodo pai da nova raiz deve ser o mesmo
        // nodo pai da raiz anterior
        nodoA->pai = up;
        if (up != nullptr) {
            if (na_esquerda(nodoB)) up->esq = nodoA;
            else up->dir = nodoA;
        }
        // sub2 é a subárvore à esquerda do nodoA
        sub2 = nodoA->esq;

        // faz a transformação: nodoA se torna nova raiz,
        // e nodoB é conectado à sua esquerda
        nodoA->esq = nodoB;
        nodoB->pai = nodoA;

        // sub2 é conectada à direita de nodoB
        nodoB->dir = sub2;
        if (sub2 != nullptr) sub2->pai = nodoB;

        // retorna a nova raiz ... não tem serventia, mas
        // como originalmente se pensou que zag deveria retorná-la,
        // mantive por coerência
        return nodoA;
    }

    //Retorna true se o nodo informado está à esquerda do nodo pai;
    template <typename T> bool na_esquerda(Nodo<T> * nodo) {
        Nodo<T> *pai = nodo->pai;

        return pai->esq == nodo;
    }

    //Retorna true se o nodo informado está à direita do nodo pai;
    template <typename T> bool na_direita (Nodo <T> * nodo){
        Nodo<T> *pai = nodo->pai;

        return pai->dir == nodo;
    }

    //Retorna true se o nodo informado está à esquerda do nodo pai e a esquerda do nodo do nodo pai;;
    template <typename T> bool testa_zigzig (Nodo <T> *nodo){
        return (na_esquerda(nodo) && na_esquerda(nodo->pai));
    }

    //Retorna true se o nodo informado está à esquerda do nodo pai e a direita do nodo do nodo pai;;
    template <typename T> bool testa_zigzag (Nodo <T> *nodo){
        return (na_esquerda(nodo) && na_direita(nodo->pai));
    }

    //Retorna true se o nodo informado está à direita do nodo pai e a esquerda do nodo do nodo pai;;
    template <typename T> bool testa_zagzig (Nodo <T> *nodo){
        return (na_direita(nodo) && na_esquerda(nodo->pai));
    }

    //Retorna true se o nodo informado está à direita do nodo pai e a direita do nodo do nodo pai;;
    template <typename T> bool testa_zagzag (Nodo <T> *nodo){
        return(na_direita(nodo) && na_direita(nodo->pai));
    }

    //Função altura_arv: Chama a função privada "altura" e retorna a altura da arvore;
    template <typename T> int altura_arv (Splay <T> & arv){
        Nodo <T> * dado_atual = arv.raiz;
        int a = altura(dado_atual);
        return  a;
    }
}
#endif //SPLAY_SPLAY_IMPL_H
