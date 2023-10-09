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
    
    void incluir();
    void remover();
};


int main () 
{
    return 0;
}