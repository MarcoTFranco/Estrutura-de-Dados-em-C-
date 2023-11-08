/* Classe fila estatica
 *
 * by Marco Túlio, 2023
 *
 */
#include <iostream>

using namespace std;

const int FILAVAZIA = -1;
const int CAPACIDADE_FILA = 6;

class Fila
{
private:
    int *mFila;
    int mPrimeiro, mUltimo;
    int mTamanho;

public:
    // Constrói fila vazia.
    Fila();

    // Destrutor que desaloca memória.
    ~Fila();

    // Retira e retorna o elemento que estiver na primeira posição.
    int desenfileirar();

    // Insere um elemento na fila.
    void enfileirar(const int &d);

    // Apagar todos os dados da fila.
    void limparTudo();

    // Imprime os valores do elemento que está na frente da fila, sem Desenfileirar.
    inline void informacoes();

    // Informa se a fila está Vazia.
    inline bool vazia();

    // Informa se a fila está Cheia.
    inline bool cheia();
};

// Constrói fila vazia.
Fila::Fila()
{
    mFila = new int[CAPACIDADE_FILA];
    mPrimeiro = FILAVAZIA;
    mUltimo = FILAVAZIA;
    mTamanho = 0;
}

// Destrutor que desaloca memória.
Fila::~Fila()
{
    delete[] mFila;
}

// Retira e retorna o elemento que estiver na primeira posição.
int Fila::desenfileirar()
{
    if (this->vazia())
        throw runtime_error("Erro: fila vazia!");

    if (mTamanho > 0)
    {
        int aux = mFila[mPrimeiro];
        mTamanho--;
        mPrimeiro++;
        mPrimeiro = mPrimeiro % CAPACIDADE_FILA;
        return aux;
    }
    else
    {
        mPrimeiro = FILAVAZIA;
        mUltimo = FILAVAZIA;
        return mFila[mPrimeiro];
    }
}

// Insere um elemento na fila.
void Fila::enfileirar(const int &d)
{
    if (this->cheia())
        throw runtime_error("Erro: fila cheia!");

    if (mTamanho <= CAPACIDADE_FILA)
    {
        mUltimo++;
        mUltimo = mUltimo % CAPACIDADE_FILA;
        mFila[mUltimo] = d;
        if (mTamanho == 0)
        {
            mPrimeiro++;
        }
        mTamanho++;
    }
}

void Fila::limparTudo()
{
    while (!this->vazia())
    {
        desenfileirar();
    }
    mPrimeiro = FILAVAZIA;
    mUltimo = FILAVAZIA;
}

void Fila::informacoes()
{
    if (this->vazia())
        throw runtime_error("Erro: fila vazia!");

    if (mTamanho > 0)
    {
        cout << "Tamanho: " << mFila[mPrimeiro];
    }
}

bool Fila::vazia()
{
    return (mTamanho == 0);
}

bool Fila::cheia()
{
    return (mTamanho == CAPACIDADE_FILA);
}

int main()
{
    Fila fila;
    int num;

    for (int i = 0; i < CAPACIDADE_FILA; i++)
    {
        cin >> num;
        fila.enfileirar(num);
    }

    cout << fila.desenfileirar() << " ";
    cout << fila.desenfileirar() << " ";

    fila.informacoes();

    fila.limparTudo();

    return 0;
}