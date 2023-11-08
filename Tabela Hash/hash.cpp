/*
 * Tabela tabelaHash usando lista explícita
 * by Joukim, 2019
 * Atualizado por Renato, 2023
 * Implementado todas as funções da tabela hash por Marco Túlio, 2023
 */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;

// Um noh guarda um par (chave / valor)
class noh
{
    friend class lista;
    friend class tabelaHash;

private:
    string chave;
    char tipo;
    int valor;
    noh *proximo;
    noh(const string &c = "", const char &t = 'a', const int &v = 0, noh *prox = NULL) : chave(c), tipo(t), valor(v), proximo(prox) {}
};

class lista
{
    friend class tabelaHash;

private:
    noh *primeiro;
    unsigned short numElementos;

public:
    lista()
    {
        primeiro = NULL;
        numElementos = 0;
    }
    ~lista()
    {
        noh *atual = primeiro;
        noh *aux;
        while (atual != NULL)
        {
            aux = atual;
            atual = atual->proximo;
            delete aux;
        }
    }
    // Retorna o tamanho da lista (numero de elementos)
    unsigned short tamanho() { return numElementos; }

    // Adiciona um novo par (chave, valor) na lista
    void insere(const string &c, const char &t, const int &v)
    {
        noh *novo = new noh(c, t, v, primeiro);
        primeiro = novo;
        numElementos++;
    }

    // Remove o noh com dada chave da lista.
    bool remove(const string &c)
    {
        noh *atual = primeiro;
        noh *anterior = NULL;
        while ((atual != NULL) and (atual->chave != c))
        {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual == NULL)
            return false;
        else
        {
            if (anterior == NULL)
                primeiro = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            delete atual;
            numElementos--;
            return true;
        }
    }

    // Busca um elemento na lista, retorna falso se não encontrado
    bool busca(const string &c, char &tipoBuscado, int &valorBuscado)
    {
        noh *atual = primeiro;
        while ((atual != NULL) and (atual->chave != c))
            atual = atual->proximo;
        if (atual == NULL)
            return false;
        else
        {
            tipoBuscado = atual->tipo;
            valorBuscado = atual->valor;
            return true;
        }
    }

    // Verifica se já tem algum dado na lista com uma dada chave
    bool verificaOcorrencia(const string &c)
    {
        noh *atual = primeiro;
        while ((atual != NULL) and (atual->chave != c))
            atual = atual->proximo;
        if (atual == NULL)
            return false;
        else
        {
            return true;
        }
    }

    // Imprime o conteúdo da lista, para fins de depuração
    void imprime()
    {
        noh *atual = primeiro;
        while (atual != NULL)
        {
            cout << "[" << atual->chave << "/"
                 << atual->valor << "]";
            atual = atual->proximo;
        }
    }
};

class tabelaHash
{
private:
    // vetor de ponteiros para lista
    lista *tabela;

    // quantidade de posições na tabela hash
    unsigned numPosicoes;

    // converte uma chave (string) num endereço da tabela
    // - versão simples
    unsigned funcaoHash(const string &s)
    {
        return funcaoHash(s, numPosicoes);
    }

    // converte uma chave (string) num endereço da tabela
    // - versão para redimensionamento
    unsigned funcaoHash(const string &s, int cap)
    {
        unsigned pos = 0;
        for (unsigned int i = 0; i < s.size(); ++i)
            pos = (UMPRIMO * pos + s[i]) % cap;
        return pos;
    }

public:
    // construtor padrão
    tabelaHash(unsigned cap = 100)
    {
        numPosicoes = cap;
        tabela = new lista[numPosicoes];
    }

    // destrutor
    ~tabelaHash()
    {
        delete[] tabela;
    }

    // Insere um nó com dada chave e valor.
    bool insere(const string &c, char &t, const int &v)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].verificaOcorrencia(c))
        {
            return false;
        }
        else
        {
            tabela[posicao].insere(c, t, v);
            cout << "chave '" << c << "' inserida na posicao " << posicao << endl;
            return true;
        }
    }

    // Retorna um valor associado a uma dada chave.
    // Se a chave não existe, retorna "NÃO ENCONTRADO!".
    bool valor(const string &c, char &tipoBuscado, int &valorRetorno)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].busca(c, tipoBuscado, valorRetorno))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Retira do hash um nó com dada chave.
    bool remove(const string &c)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].remove(c))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Imprime o conteúdo interno do hash (para fins de depuração)
    void imprime()
    {
        for (unsigned i = 0; i < numPosicoes; i++)
        {
            cout << i << ": ";
            tabela[i].imprime();
            cout << endl;
        }
    }
};

int main()
{
    int tamanho;
    cin >> tamanho;
    tabelaHash tabela(tamanho);
    char comando;
    string chave;
    char tipo = 'a';
    int valor = -1;
    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> chave >> tipo >> valor;
                if (not tabela.insere(chave, tipo, valor))
                    cout << "Erro na inserção: chave já existente!" << endl;
                break;
            case 'r': // remover
                cin >> chave;
                if (not tabela.remove(chave))
                    cout << "Erro na remoção: chave não encontrada!" << endl;
                break;
            case 'l': // recupera
                cin >> chave;
                if (not tabela.valor(chave, tipo, valor))
                    cout << "Erro na busca: chave não encontrada!" << endl;
                else
                    cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                break;
            case 'p': // mostrar estrutura
                tabela.imprime();
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
    tabela.imprime();
    cout << endl;
    return 0;
}