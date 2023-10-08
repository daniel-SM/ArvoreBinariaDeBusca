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

    void emOrdem();

    Node* buscar();
    Node* min();
    Node* max();
    Node* sucessor();
    Node* predecessor();
    
    void incluir();
    void remover();
};


int main () 
{
    return 0;
}