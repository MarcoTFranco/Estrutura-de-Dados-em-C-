/*

Irei adicionar no README como utilizar o codigo.

Exemplo de Entrada:
i 3
i 4
i 2
i 5
i 1
r 3
o
p
f

Exemplo de Saída:
1/2 2/1 4/0 5/1 
4/0 2/1 1/2 5/1

*/


#include <iostream>
#include <cstdlib>

using namespace std;

class noh
{
public:
    int dado;
    noh *esquerdo;
    noh *direito;
};

class Tree
{
private:
    noh *raiz;
    void destruirNohRecursivamente(noh *atual);
    noh *buscaAux(int d);
    noh *minimoAux(noh *umNoh);
    noh *maximoAux(noh *umNoh);
    noh *removerAux(noh *umNoh, int d);
    noh *removerMenor(noh *raizSub);
    void percorreEmOrdemAux(noh *umNoh, int nivelAtual);
    void percorrePreOrdemAux(noh *umNoh, int nivelAtual);

public:
    Tree();
    ~Tree();
    void insere(int d);
    void remover(int d);
    void busca(int d);
    int minimo();
    int maximo();
    void percorreEmOrdem();
    void percorrePreOrdem();
};

// construtor
Tree::Tree()
{
    raiz = NULL;
}

// destrutor
Tree::~Tree()
{
    destruirNohRecursivamente(raiz);
}

// destrutor recursivo
void Tree::destruirNohRecursivamente(noh *atual)
{
    if (atual != NULL)
    {
        destruirNohRecursivamente(atual->esquerdo);
        destruirNohRecursivamente(atual->direito);
        delete atual;
    }
}

// insere um dado na árvore
void Tree::insere(int d)
{
    noh *novo = new noh;
    novo->dado = d;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    if (raiz == NULL)
        raiz = novo;
    else
    {
        noh *atual = raiz;
        noh *anterior;
        while (atual != NULL)
        {
            anterior = atual;
            if (atual->dado < d)
                atual = atual->direito;
            else
                atual = atual->esquerdo;
        }
        if (anterior->dado < d)
            anterior->direito = novo;
        else
            anterior->esquerdo = novo;
    }
}

// método de busca auxiliar (retorna o nó), iterativo
noh *Tree::minimoAux(noh *umNoh)
{
    while (umNoh->esquerdo != NULL)
        umNoh = umNoh->esquerdo;
    return umNoh;
}

// método de busca auxiliar (retorna o nó), iterativo
int Tree::minimo()
{
    if (raiz == NULL)
    {
        throw runtime_error("ERRO");
    }
    else
    {
        noh *minimo = minimoAux(raiz);
        return minimo->dado;
    }
}

noh *Tree::maximoAux(noh *umNoh)
{
    while (umNoh->direito != NULL)
        umNoh = umNoh->direito;
    return umNoh;
}

int Tree::maximo()
{
    if (raiz == NULL)
    {
        throw runtime_error("ERRO");
    }
    else
    {
        noh *maximo = maximoAux(raiz);
        return maximo->dado;
    }
}

noh *Tree::removerMenor(noh *raizSub)
{
    if (raizSub->esquerdo == NULL)
    {
        return raizSub->direito;
    }
    else
    {
        raizSub->esquerdo = removerMenor(raizSub->esquerdo);
        return raizSub;
    }
}

noh *Tree::removerAux(noh *umNoh, int d)
{
    if (umNoh == NULL)
    {
        throw runtime_error("ERRO");
    }
    noh *novaRaizSubArvore = umNoh;

    if (d < umNoh->dado)
    {
        umNoh->esquerdo = removerAux(umNoh->esquerdo, d);
    }
    else if (d > umNoh->dado)
    {
        umNoh->direito = removerAux(umNoh->direito, d);
    }
    else
    {
        if (umNoh->esquerdo == NULL)
        {
            novaRaizSubArvore = umNoh->direito;
        }
        else if (umNoh->direito == NULL)
        {
            novaRaizSubArvore = umNoh->esquerdo;
        }
        else
        {
            novaRaizSubArvore = minimoAux(umNoh->direito);
            novaRaizSubArvore->direito = removerMenor(umNoh->direito);
            novaRaizSubArvore->esquerdo = umNoh->esquerdo;
        }
        delete umNoh;
    }
    return novaRaizSubArvore;
}

void Tree::remover(int d)
{
    raiz = removerAux(raiz, d);
}

void Tree::busca(int d)
{
    noh *nohComValor = buscaAux(d);
    if (nohComValor == NULL)
        cout << "ERRO" << endl;
    else
        cout << "ENCONTRADO" << endl;
}

noh *Tree::buscaAux(int d)
{
    noh *atual = raiz;
    while (atual != NULL)
    {
        if (atual->dado == d)
            return atual;
        else if (atual->dado > d)
            atual = atual->esquerdo;
        else
            atual = atual->direito;
    }
    return atual;
}

void Tree::percorreEmOrdem()
{
    percorreEmOrdemAux(raiz, 0);
}

void Tree::percorreEmOrdemAux(noh *umNoh, int nivelAtual)
{
    if (umNoh != NULL)
    {
        percorreEmOrdemAux(umNoh->esquerdo, nivelAtual + 1);
        cout << umNoh->dado << "/" << nivelAtual << " ";
        percorreEmOrdemAux(umNoh->direito, nivelAtual + 1);
    }
}

void Tree::percorrePreOrdem()
{
    percorrePreOrdemAux(raiz, 0);
}

void Tree::percorrePreOrdemAux(noh *umNoh, int nivelAtual)
{
    if (umNoh != NULL)
    {
        cout << umNoh->dado << "/" << nivelAtual << " ";
        percorrePreOrdemAux(umNoh->esquerdo, nivelAtual + 1);
        percorrePreOrdemAux(umNoh->direito, nivelAtual + 1);
    }
}

int main()
{
    char comando;
    int valor;
    Tree minhaArvore;

    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir no inicio
                cin >> valor;
                minhaArvore.insere(valor);
                break;
            case 'r': // remover
                cin >> valor;
                minhaArvore.remover(valor);
                break;
            case 'o': // para escrever os elementos em ordem.
                minhaArvore.percorreEmOrdem();
                cout << endl;
                break;
            case 'p': // para escrever os elementos em pré-ordem.
                minhaArvore.percorrePreOrdem();
                cout << endl;
                break;
            case 'f': // finalizar
                break;
            default:
                cerr << "comando inválido\n";
            }
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}