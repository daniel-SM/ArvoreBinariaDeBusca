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

    Node* min(Node* x) 
    {
        while (x->esq != nullptr) x = x->esq;
        return x;
    }

    Node* max(Node* x)
    {
        while (x->dir != nullptr) x = x->dir;
        return x;
    }

    Node* sucessor();
    Node* predecessor();
    
    void incluir();
    void remover();
};


int main () 
{
    return 0;
}