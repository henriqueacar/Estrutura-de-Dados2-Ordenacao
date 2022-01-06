// **************************************************************
//  ATIVIDADE 1
// **************************************************************
// Dados do Aluno
// Nome: HENRIQUE DE ALMEIDA CARDOSO
// Matricula: 201576015
// E-mail: henrique.cardoso@estudante.ufjf.br
//***************************************************************


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <cstdlib>

using namespace std;
void preencheVet(int vetor[], int TAM);
double BubbleSort(int vetor[], int TAM, long long int *pTroca, long long int *pCompara);
double QuickSort(int vetor[], int p, int r, long long int *pTroca, long long int *pCompara);
int Particionamento(int vetor[], int p, int q, long long int *pTroca, long long int *pCompara);
void Troca(int* a, int* b);
double ShellSort(int vetor[], int TAM, long long int *pTroca, long long int *pCompara);
void longprintaVetor(long long int vetor[], int TAM);
void doubleprintaVetor(double vetor[], int TAM);
int compare(const void * a, const void * b);

/**

    TESTADO COM ATE 5 TESTES DE 50000 POSICOES CADA
    Vetores muito maiores que isso podem acabar gerando
    overflow nas metricas devido aos numeros serem
    muito grandes quando somados e ultrapassarem os limites

**/

// Criar uma rotina para gerar um vetor de tamanho N com numeros
// aleatórios

void preencheVet(int vetor[], int TAM)
{
    for(int i=0; i<TAM; i++)
    {
        vetor[i] = rand()%9999;
    }
}

/** Dois metodos de impressao, um para imprimir inteiros grandes necessarios para
    calcular a soma das metricas caso o teste seja realizado com vetores muito grandes
    e o outro utilizado para imprimir a quantidade de tempo **/

void longprintaVetor(long long int vetor[], int TAM)
{
    for(int i=0; i<TAM; i++)
    {
        cout << "["<<vetor[i]<<"]";
    }
}
void doubleprintaVetor(double vetor[], int TAM)
{
    for(int i=0; i<TAM; i++)
    {
        cout << "["<<vetor[i]<<"]";
    }
}

// Insere aqui o método de ordenacão classe quadrática

double BubbleSort(int vetor[], int TAM, long long int *pTroca, long long int *pCompara)
{
    double tempoGasto=0;
    auto start = std::chrono::steady_clock::now(); /** Inicio a contagem de tempo **/
    for(int i=0; i<TAM; i++)
    {
        for(int j=i+1; j<TAM; j++)
        {
            *pCompara+=1;                          /** Incremento de comparacao **/
            if(vetor[i]>vetor[j])
            {
                *pTroca+=1;                        /** Incremento de troca **/
                int aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }
        }
    }
    auto end = std::chrono::steady_clock::now(); /** Termino a contagem de tempo e armazeno **/
    std::chrono::duration<double> elapsed_seconds = end-start;
    tempoGasto = elapsed_seconds.count();

    return tempoGasto; /** Retorno o tempo gasto **/
}

// Insere aqui o método Shellsort

double ShellSort(int vetor[], int TAM, long long int *pTroca, long long int *pCompara)
{

    double tempoGasto=0;
    auto start = std::chrono::steady_clock::now(); /** Inicio a contagem de tempo **/
    for(int aux=TAM/2; aux>0; aux/=2)
    {
        for(int i = aux; i<TAM; i++)
        {
            int temp=vetor[i];
            int j;
            for(j=i; j>=aux && vetor[j-aux]>temp; j-=aux)
            {
                vetor[j] = vetor[j-aux];
                *pTroca+=1;                       /** Incremento de troca **/
            }
            vetor[j]=temp;
            *pTroca+=1;                           /** Incremento de troca **/
            *pCompara+=1;                         /** Incremento de comparacao **/
        }
    }

    auto end = std::chrono::steady_clock::now();  /** Termino a contagem de tempo e armazeno **/
    std::chrono::duration<double> elapsed_seconds = end-start;
    tempoGasto = elapsed_seconds.count();

    return tempoGasto; /** Retorno o tempo gasto **/
}

// Insere aqui o método de ordenacão classe NLOGN

double QuickSort(int vetor[], int p, int r, long long int *pTroca, long long int *pCompara)
{
    double tempoGasto=0;
    auto start = std::chrono::steady_clock::now(); /** Inicio a contagem de tempo **/
    if(p<r)
    {
        int q = Particionamento(vetor, p, r, pTroca, pCompara);
        QuickSort(vetor, p, q-1, pTroca, pCompara);
        QuickSort(vetor, q+1, r, pTroca, pCompara);
    }
    auto end = std::chrono::steady_clock::now();  /** Termino a contagem de tempo e armazeno **/
    std::chrono::duration<double> elapsed_seconds = end-start;
    tempoGasto = elapsed_seconds.count();

    return tempoGasto; /** Retorno o tempo gasto **/
}

int Particionamento(int vetor[], int p, int q, long long int *pTroca, long long int *pCompara)
{
    int pivo = vetor[q];
    int i=p-1;

    for(int j=p; j<=q-1; j++)
    {
        if(vetor[j]<pivo)
        {
            i++;
            Troca(&vetor[i], &vetor[j]);
            *pTroca+=1;                     /** Incremento de troca **/
        }
        *pCompara+=1;                       /** Incremento de comparacao **/
    }
    Troca(&vetor[i+1], &vetor[q]);
    *pTroca+=1;                             /** Incremento de troca **/
    return (i+1);
}

void Troca(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Dica:
// Crie rotina para comparar e trocar
//  e coloque um contador internamente para
// obter as métricas de desempenho.

// Observação:
// Caso queira, pode-se implementar usando OO.
//

/** Usado no metodo qsort **/
int compare(const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int main()
{
    srand(time(NULL));

    /** Variaveis que contem o tempo gasto total de cada metodo **/
    double tempoGastoBubble=0;
    double tempoGastoQuickSort=0;
    double tempoGastoShellSort=0;
    double tempoGastoQsort=0;

    /** Variaveis que contem o numero total de trocas de cada metodo **/
    long long int numTrocasBubbleSort=0;
    long long int numTrocasQuickSort=0;
    long long int numTrocasShellSort=0;

    /** Variaveis que contem o numero total de comparacoes de cada metodo **/
    long long int numComparaBubbleSort=0;
    long long int numComparaQuickSort=0;
    long long int numComparaShellSort=0;

    /** Ponteiros usados para passar as variaveis de troca e compara acima
       para os metodos de ordenacao para poder calcular a quantidade total **/
    long long int *pTroca;
    long long int *pCompara;

    /** vetEntrada armazena a quantidade de testes a serem feitos **/
    int numTestes=0;
    cout<<"Numero de testes a serem executados: ";
    cin>>numTestes;
    int vetEntrada[numTestes];

    /** Os vetores abaixo possuem o tamanho igual a quantidade de testes a serem realizados e
        sao utilizados para armazenar os dados individuais de cada teste:
        Quantide de trocas
        Quantidade de comparacoes
        Tempo gasto **/
    long long int trocasVetBubble[numTestes];
    long long int trocasVetQuick[numTestes];
    long long int trocasVetShell[numTestes];
    long long int comparaVetBubble[numTestes];
    long long int comparaVetQuick[numTestes];
    long long int comparaVetShell[numTestes];
    double tGastoBubble[numTestes];
    double tGastoQuick[numTestes];
    double tGastoShell[numTestes];
    double tGastoQsort[numTestes];

    /** Variaveis auxiliares para fazer o calculo das metricas de cada teste **/
    long long int auxTroca=0;
    long long int auxCompara=0;
    double auxTempo=0;

    /** Cada slot do vetEntrada armazena o tamanho do vetorTestes no laco abaixo a ser ordenado **/
    cout<<"Tamanho de cada teste" << endl;
    for(int i = 0; i<numTestes; i++)
    {
        cout<<"["<<i+1<<"]: ";
        cin>>vetEntrada[i];
    }

    /** Variavel controladorTestes usada para controlar o indice dos vetores no laco**/
    int controladorTestes=0;

    /** Descricao do laco:
        Comeco inicializando o vetorTestes com o tamanho que foi armazenado em vetEntrada
        Cada repeticao do laco eu inicializo o vetorTestes com um tamanho diferente,
        de acordo com o que estiver armazenado em vetEntrada[controladorTestes]

        Antes de qualquer metodo de ordenaca, eu preencho o vetor com valores aleatorios
        e faco as atribuicoes dos ponteiros que serao passados aos metodos de ordenacao
        e das variaveis auxiliares

        Cada metodo de ordenacao me retorna o tempo gasto para a ordenacao, e esse tempo
        e somado com o tempo armazenado previamente em loops anteriores. As variaveis passadas
        por ponteiro tambem sao incrementadas de acordo com o que se foi pedido para fazer a medicao

        Por fim, faco um calculo usando as variaveis auxiliares para subtrair:

        quantidade total - quantidade antes do metodo ser chamado

        Assim eu consigo medir quanto de tempo, comparacoes e trocas foi incrementado
        da penultima chamada das funcoes de ordenacao para a ultima e armazeno
        essa informacao nos vetores e metricas para cada teste
        **/
    while(controladorTestes<numTestes)
    {
        int vetorTestes[vetEntrada[controladorTestes]];

        /**-----------------BUBBLE----------------**/
        preencheVet(vetorTestes, vetEntrada[controladorTestes]);

        pTroca=&numTrocasBubbleSort;
        pCompara=&numComparaBubbleSort;
        auxTroca=*pTroca;
        auxCompara=*pCompara;
        auxTempo = tempoGastoBubble;

        tempoGastoBubble+=BubbleSort(vetorTestes, vetEntrada[controladorTestes], pTroca, pCompara);

        auxTroca = *pTroca - auxTroca;
        auxCompara = *pCompara - auxCompara;
        auxTempo = tempoGastoBubble - auxTempo;
        trocasVetBubble[controladorTestes]= auxTroca;
        comparaVetBubble[controladorTestes]= auxCompara;
        tGastoBubble[controladorTestes]=auxTempo;

        /**-----------------BUBBLE----------------**/

        /**----------------QUICK-----------------**/
        preencheVet(vetorTestes, vetEntrada[controladorTestes]);

        pTroca=&numTrocasQuickSort;
        pCompara=&numComparaQuickSort;
        auxTroca=*pTroca;
        auxCompara=*pCompara;
        auxTempo = tempoGastoQuickSort;

        tempoGastoQuickSort+=QuickSort(vetorTestes, 0, vetEntrada[controladorTestes]-1, pTroca, pCompara);

        auxTroca = *pTroca - auxTroca;
        auxCompara = *pCompara - auxCompara;
        auxTempo = tempoGastoQuickSort - auxTempo;
        trocasVetQuick[controladorTestes]= auxTroca;
        comparaVetQuick[controladorTestes]= auxCompara;
        tGastoQuick[controladorTestes]=auxTempo;
        /**----------------QUICK-----------------**/

        /**----------------SHELL-----------------**/
        preencheVet(vetorTestes, vetEntrada[controladorTestes]);

        pTroca=&numTrocasShellSort;
        pCompara=&numComparaShellSort;
        auxTroca=*pTroca;
        auxCompara=*pCompara;
        auxTempo = tempoGastoShellSort;

        tempoGastoShellSort+=ShellSort(vetorTestes, vetEntrada[controladorTestes], pTroca, pCompara);

        auxTroca = *pTroca - auxTroca;
        auxCompara = *pCompara - auxCompara;
        auxTempo = tempoGastoShellSort - auxTempo;
        trocasVetShell[controladorTestes]= auxTroca;
        comparaVetShell[controladorTestes]= auxCompara;
        tGastoShell[controladorTestes]=auxTempo;
        /**----------------SHELL-----------------**/

        /**-----------------QSORT----------------**/
        preencheVet(vetorTestes, vetEntrada[controladorTestes]);

        auxTempo = tempoGastoQsort;

        auto start = std::chrono::steady_clock::now();
        qsort(vetorTestes, vetEntrada[controladorTestes], sizeof(int), compare);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        tempoGastoQsort += elapsed_seconds.count();

        auxTempo = tempoGastoQsort - auxTempo;

        tGastoQsort[controladorTestes]=auxTempo;
        /**-----------------QSORT----------------**/
        controladorTestes++;
    }

    /**IMPRESSAO DE RESULTADO**/
    cout<<"\n\nRESULTADOS"
        <<"\n\nBUBBLESORT"
        <<"\nComparacoes por teste: ";
    longprintaVetor(comparaVetBubble, numTestes);
    cout<<"\nTrocas por teste: ";
    longprintaVetor(trocasVetBubble, numTestes);
    cout<<"\nTempo por teste: ";
    doubleprintaVetor(tGastoBubble, numTestes);
    cout<<"\nTotal de comparacoes: " << numComparaBubbleSort
        <<"\nTotal de trocas: " << numTrocasBubbleSort
        <<"\nTempo total: " << tempoGastoBubble << endl;

    cout<<"\n\nQUICKSORT"
        <<"\nComparacoes por teste: ";
    longprintaVetor(comparaVetQuick, numTestes);
    cout<<"\nTrocas por teste: ";
    longprintaVetor(trocasVetQuick, numTestes);
    cout<<"\nTempo por teste: ";
    doubleprintaVetor(tGastoQuick, numTestes);
    cout<<"\nTotal de comparacoes: " << numComparaQuickSort
        <<"\nTotal de trocas: " << numTrocasQuickSort
        <<"\nTempo total: " << tempoGastoQuickSort << endl;

    cout<<"\n\nSHELLSORT"
        <<"\nComparacoes por teste: ";
    longprintaVetor(comparaVetShell, numTestes);
    cout<<"\nTrocas por teste: ";
    longprintaVetor(trocasVetShell, numTestes);
    cout<<"\nTempo por teste: ";
    doubleprintaVetor(tGastoShell, numTestes);
    cout<<"\nTotal de comparacoes: " << numComparaShellSort
        <<"\nTotal de trocas: " << numTrocasShellSort
        <<"\nTempo total: " << tempoGastoShellSort << endl;

    cout<<"\n\nQSORT"
        <<"\nTempo por teste: ";
    doubleprintaVetor(tGastoQsort, numTestes);
    cout<<"\nTempo total: " << tempoGastoQsort << endl;
    /**IMPRESSAO DE RESULTADO**/
    return 0;
}
