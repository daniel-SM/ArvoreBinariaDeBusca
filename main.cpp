#include <iostream>

template <typename T>
class ABB
{
private:
    struct Node
    {
        T chave;
        Node *pai, *esq, *dir;
    };
    Node *raiz;

public:
    ABB() : raiz{nullptr} {}

    void desalocar (Node* x) 
    {
        if (x != nullptr)
        {
            desalocar(x->esq);
            desalocar(x->dir);
            delete x;
        }
    } 

    ~ABB() { desalocar(raiz);}

    void visitar(Node* x) { std::cout << "Chave: " << x->chave << "\n"; }

    void emOrdem(Node* x) 
    {
        if (x != nullptr)
        {
            emOrdem(x->esq);
            visitar(x);
            emOrdem(x->dir);
        }
    }

    Node* buscar (Node* x, T k)
    {
        if (x == nullptr or k == x->chave) return x;

        if (k < x->chave) return buscar(x->esq, k); 
        else return buscar(x->dir, k);
    }

    Node* min(Node* x) // Assume que x é diferente de NULO 
    {
        while (x->esq != nullptr) x = x->esq;
        return x;
    }

    Node* max(Node* x) // Assume que x é diferente de NULO
    {
        while (x->dir != nullptr) x = x->dir;
        return x;
    }

    Node* sucessor(Node* x) // Assume que x é diferente de NULO
    {
        if (x->dir != nullptr) return min(x->dir);
        
        Node* y = x->pai;
        while (y != nullptr and x == y->dir)
        {
            x = y;
            y = y->pai;
        }
        return y;
    }

    Node* predecessor(Node* x)
    {
        if (x->esq != nullptr) return max(x->esq);

        Node* y = x->pai;
        while (y != nullptr and x == y->esq)
        {
            x = y;
            y = y->pai;
        }
        return y;
    }
    
    void incluir(Node* z)
    {
        Node* y = nullptr;
        Node* x = raiz;

        while (x != nullptr)
        {
            y = x;
            if (z->chave < x->chave) 
                x = x->esq;
            else 
                x = x->dir;
        }

        z->pai = y;
        if (y == nullptr) 
            raiz = z;
        else if (z->chave < y->chave) 
            y->esq = z;
        else 
            y->dir = z;
        
        z->esq = nullptr;
        z->dir = nullptr;
    }

    void transplantar (Node* u, Node* v) 
    {
        if (u->pai == nullptr) 
            raiz = v;
        else if (u == u->pai->esq ) 
            u->pai->esq = v;
        else 
            u->pai->dir = v;

        if (v != nullptr) v->pai = u->pai;
    }

    void remover(Node* z)
    {
        if (z->esq == nullptr)
        {
            transplantar(z, z->dir);
        }
        else if (z->dir == nullptr)
        {
            transplantar(z, z->esq);
        }
        else
        {
            Node* y = min(z->dir);
            if (y->pai != z)
            {
                transplantar(y, y->dir);
                y->dir = z->dir;
                z->dir->pai = y;
            }
            transplantar(z, y);
            y->esq = z->esq;
            z->esq->pai = y;
        }
    }

    // Função auxiliar que chama emOrdem() a partir da raiz
    void percurso () 
    {
        emOrdem(raiz);
    }

    // Função auxiliar que chama buscar() a partir da raiz
    Node* busca (T k) 
    {
        return buscar(raiz, k);
    }

    // Função auxiliar que aloca novo nó e chama incluir() para ele
    void insercao (T k) 
    {
        Node* z = new Node;
        z->chave = k;
        incluir(z);
    }

    // Função auxiliar que encontra nó com chave k e remove da árvore
    void remocao(T k) 
    {
        Node* z = busca(k);
        if (z != nullptr) remover(z);
    }
};


int main () 
{
    ABB<int> arvore;

    // Testando inclusão
    arvore.insercao(10);
    arvore.insercao(12);
    arvore.insercao(11);
    arvore.insercao(9);
    arvore.insercao(6);
    // OK

    // Testando busca
    std::cout << "Buscando: " << arvore.busca(6)->chave << "\n";
    std::cout << "Buscando: " << arvore.busca(9)->chave << "\n";
    std::cout << "Buscando: " << arvore.busca(10)->chave << "\n";
    std::cout << "Buscando: " << arvore.busca(11)->chave << "\n";
    std::cout << "Buscando: " << arvore.busca(12)->chave << "\n";
    // OK

    // Testando remoção 
    arvore.remocao(10);
    arvore.remocao(6);

    // Testando percurso em ordem na árvore
    arvore.percurso();

    return 0;
}