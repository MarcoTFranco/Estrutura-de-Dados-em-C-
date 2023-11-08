/* Classe Fila encadeada
 *
 * by Marco Túlio Franco Silva, 2023,
 *
 */

#include <iostream>

using namespace std;

class noh
{
    friend class Fila;

private:
    int mValor;
    noh *mProximo;

public:
    noh(int valor);
};

noh::noh(int valor)
{
    mValor = valor;
    mProximo = NULL;
}

class Fila
{
private:
    noh *mInicio;
    noh *mFim;
    unsigned mTamanho;

public:
    //Construtor padrão
    Fila();
    //Destrutor
    ~Fila();
    //Retorna o tamanho da fila
    unsigned tamanho();
    //Insere um elemento no fim da fila
    void enfileira(int valor);
    //Retira o elemento do início da fila
    int desenfileira();
    //Apaga todos os elementos da fila
    void limpaFila();
    //Verifica se a fila está vazia
    bool vazia();
    //Retorna o elemento do início da fila
    void topo();
};

Fila::Fila()
{
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}

Fila::~Fila()
{
    limpaFila();
}

void Fila::limpaFila()
{
    while (!this->vazia())
    {
        desenfileira();
    }
}

unsigned Fila::tamanho()
{
    return mTamanho;
}

bool Fila::vazia()
{
    return (mTamanho == 0);
}

void Fila::enfileira(int valor)
{
    noh *novo = new noh(valor);
    if (this->vazia())
    {
        mInicio = novo;
    }
    else
    {
        mFim->mProximo = novo;
    }
    mFim = novo;
    mTamanho++;
}

int Fila::desenfileira()
{
    if (this->vazia())
        throw runtime_error("Erro: fila vazia!");

    int valor = mInicio->mValor;
    noh *temp = mInicio;
    mInicio = mInicio->mProximo;
    delete temp;
    mTamanho--;
    if (this->vazia())
    {
        mFim = NULL;
    }
    return valor;
}

void Fila::topo()
{
    if (this->vazia())
        throw runtime_error("Erro: Fila vazia!");
    cout << (mInicio->mValor);
}

int main()
{
    Fila p1;

    int num;
    cin >> num;

    while (num >= 0)
    {
        p1.enfileira(num);
        cin >> num;
    }

    cout << "tamanho: " << p1.tamanho() << endl;

    cout << "elementos: ";

    while (not p1.vazia())
    {
        cout << p1.desenfileira() << " ";
    }

    return 0;
}