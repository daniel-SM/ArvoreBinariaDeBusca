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
    ~ABB() {}

    void visitar(Node* x) {}

    void emOrdem(Node* x) 
    {
        if (x != nullptr)
        {
            emOrdem(x->esq);
            visitar(x);
            emOrdem(x->dir);
        }
    }

    Node* buscar(Node* x, T k)
    {
        if (x == nullptr or k == x->chave) return x;

        if (k < x->chave) return buscar(x->esq); 
        else return buscar(x->dir);
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
};


int main () 
{
    return 0;
}