#include <iostream>
using namespace std;

const short unsigned int lVec = 32;
const unsigned long int MAX_CPF = 999999999;
const unsigned long int MAX_INT = ~0;           /* Será utilizado no lugar de numeric_limits<streamsize>::max() */

int pow(int a, int b)
{
    int c = a;

    for(; b > 1; b--)
        a = a * c;

    if (b == 0)
        a = 1;

    return a;
}

void iniVec (int a, int b[]) /* Inicializa um vetor 'b' de tamanho 'a' */
{
    for(int i = 0; i < a; i++)
        b[i] = 0;
}

int str2vec (string a, int b[]) /* Converte uma string 'a' para um vetor do tipo inteiro 'b' aplicando medidas de segurança 
                                   a fim de evitar um possível buffer overflow. Retorna, também, o tamanho do vetor */
{
    int i = 0;
    int j = 0;

    while (a[i] != '\0' && i-j < lVec)
    {
        if(a[i] > 47 && a[i] < 58)
        {
        b[i-j] = (a[i] - '0');
        i++;
        }
        else
        { 
        i++;
        j++;
        }
    }
    return i-j;
}

void prtVec (int b[], int c) /* Imprime um vetor 'b' desde sua origem até o 'c'-nésimo elemento */
{
    for(int i = 0; i < c; i++)
        cout<<b[i];
}

void copVec (int b[], int c, int aux[]) /* Faz uma cópia desde a origem de um vetor 'b' até seu 'c'-nésimo termo em um vetor auxiliar 'aux' */
{
    for(int i = 0; i < c; i++)
        aux[i] = b[i];
}

void multCres (int d[], int b[], int c) /* Multiplica sucessivamente os elementos de um vetor 'b' desde o 'c'nésimo elemento até sua origem utilizando
                                           uma progressão aritmética de razão 1 e termo inicial 2 como multiplicador. Depois, adiciona todos os
                                           elementos, realiza uma operação de módulo com divisor 11 e checa se o valor obtido é maior que 1. Caso 
                                           verdadeiro, armazena 11 - [resultado] em 'd'[0]. Caso falso, armazena 0 em 'd'[0]. Posteriormente, repete o 
                                           processo suprarreferido utilizando 'd'[0] como elemento inicial da multiplicação e por fim armazenando o 
                                           resultado em 'd'[1] */                  
{
    int b_aux[lVec];

    iniVec(lVec, b_aux);
    iniVec(2, d);
    copVec(b, c, b_aux);

    for(int i = (c-1); i >= 0; i--)
        {
            b_aux[i] = b_aux[i] * (c+1-i);
            d[0] = d[0] + b_aux[i];
        }

    if(d[0] % 11 >= 2){
        d[0] = 11 - d[0] % 11;
    }else{
        d[0] = 0;
    }

    copVec(b, c, b_aux);

    for(int i = (c-1); i >= 0; i--)
        {
            b_aux[i] = b_aux[i] * (c+2-i);
            d[1] = d[1] + b_aux[i];
        }

    if((d[1] + d[0] * 2) % 11 >= 2){
        d[1] = 11 - (d[1] + d[0] * 2) % 11;
    }else{
        d[1] = 0;
    }    
}

void digVec (int a[], int b[], int c) /* Extrai e armazena os dois últimos elementos de um vetor 'a' de tamanho 'c' em um vetor 'b' */
{
    for(int i = 2; i > 0; i--)
        b[i-1] = a[c-3+i]; 
}

int deltaVec (int d[], int b[], int c) /* Compara dois vetores 'd' e 'b' de tamanho 'c' e retorna o número de elementos idênticos */                                                
{
    int a = 0;

    for(int i = c-1; i >= 0; i--)
        if(d[i] == b[i])
        {
            a++;
        }

return a;
}

int repCPF (int b[], int d[], int c, char a) /* Recebe dois vetores, um 'b' de tamanho 'c' e outro 'd' de tamanho 2. Então, realiza uma
                                        análise combinatória simplificada para determinar as iterações que satisfazem a
                                        condição da função multCres e as imprime. Também retorna a quantidade de resultados
                                        verdadeiros encontrados. */
{
    int b_aux[9];
    int b_dig_aux[2];
    int digIdt = 0;
    int itrVerd = 0;

    copVec(b, 9, b_aux);

    for(int i = 0; i < c; i++)
    {
        if(i > 0)
        {
            b_aux[i-1] = b[i-1]; 
        } 
        for(int j = 0; j < 10; j++)
        {
            digIdt = 0;
            b_aux[i] = j;
            multCres(b_dig_aux, b_aux, 9);
            digIdt = deltaVec(b_dig_aux, d, 2);
            if(digIdt == 2 && (b_aux[8] == (a - '0') || a == 'n'))
            {
                cout<<"Seu CPF pode ser: ";
                prtVec(b_aux, 9);
                prtVec(b_dig_aux, 2);
                cout<<endl;
                itrVerd++;
            }
        }
    }

return itrVerd;
}

int repCPF_completo (int b[], int d[], int c, char a)
{
    int b_aux[9];
    int b_dig_aux[2];
    int digIdt = 0;
    int itrVerd = 0;

    iniVec(c, b_aux);

    for(int i = 0; i < MAX_CPF; i++)
    {
        digIdt = 0;
        multCres(b_dig_aux, b_aux, 9);
        digIdt = deltaVec(b_dig_aux, d, 2);
            if(digIdt == 2 && (b_aux[8] == (a - '0') || a == 'n'))
            {
                cout<<"Seu CPF pode ser: ";
                prtVec(b_aux, 9);
                prtVec(b_dig_aux, 2);
                cout<<endl;
                itrVerd++;
            }
        for(int j = 0; j < c; j++)
            b_aux[c-j-1] = (i / pow(10, j)) % 10;
    }

    return itrVerd;
}

int main ()
{
    string sCPF;                             /* String CPF */
    char eCPF;                               /* Estado CPF */
    char validar;                            /* Utilizado para validar entrada através de perguntas de sim ou não [s/n] */
    int vCPF[lVec];                          /* Vetor CPF */
    int vCPF_dig[2];                         /* Dígitos verificadores do CPF original */
    int vCPF_dig_aux[2];                     /* Dígitos verificadores do CPF auxiliar */
    int tamVec = 0;                          /* Tamanho do vetor */
    int digIdt = 0;                          /* Dígitos idênticos */
    int CPFs_pos = 0;                        /* CPFs possíveis */

    iniVec(lVec, vCPF);
    iniVec(2, vCPF_dig);
    iniVec(2, vCPF_dig_aux);

    cout << "+-------------------------------+\n"
         << "| R E P A R A D O R  D E  C P F |\n"
         << "+-------------------------------+\n\n"
         << "|\n"
         << "||\n"
         << "||| Reparador de CPF\n"
         << "||| Inexorabilis-Nero - ver 0.2\n"
         << "|||\n"
         << "||| Contribua com esse projeto open-source:\n"
         << "||| https://github.com/Inexorabilis-Nero/Reparador-de-CPF/\n"
         << "||\n"
         << "|\n\n";

    cout << "Informe o Estado de origem do CPF. De outro modo, escolha a alternativa \"N/A\" para pular esta etapa.\n\n"
         << "[1] DF, GO, MS, MT e TO                 [2] AC, AM, AP, PA, RO e RR             [3] CE, MA e PI\n"
         << "[4] AL, PB, PE e RN                     [5] BA e SE                             [6] MG\n"
         << "[7] ES e RJ                             [8] SP                                  [9] PR e SC\n"
         << "[0] RS                                  [n] N/A\n\n"
         << "[ ]\b\b";

    cin >> eCPF;

    while ((eCPF < 48 || eCPF > 57) && eCPF != 110 || cin.peek() != '\n')
    {
        cin.clear();
        cin.ignore(MAX_INT, '\n');
        cout<<"\nResposta inexata. Por favor, selecione uma das alternativas acima\n"
            <<"[ ]\b\b";
        cin >> eCPF;
    }

    cout << "\nInforme o CPF que deseja reparar:\n";
    cin >> sCPF;
    cout << endl;
    tamVec = str2vec(sCPF, vCPF);

    if(tamVec == 11)
    {
        digVec(vCPF, vCPF_dig, tamVec);
        multCres(vCPF_dig_aux, vCPF, 9);
        digIdt = deltaVec(vCPF_dig_aux, vCPF_dig, 2);

        switch(digIdt)
        {
            case 0:
                CPFs_pos = repCPF(vCPF, vCPF_dig, 9, eCPF) + CPFs_pos;
                break;
            case 1:
                if(vCPF[8] == (eCPF - '0') || eCPF == 'n')
                {
                    cout << "Seu CPF pode ser: ";
                    prtVec(vCPF, 9);
                    prtVec(vCPF_dig_aux, 2);
                    cout << endl;
                    CPFs_pos++;
                    CPFs_pos = repCPF(vCPF, vCPF_dig, 9, eCPF) + CPFs_pos;
                }
                break;
            case 2:
                cout << "Erro: O CPF inserido carece de avarias.\n";
                break;
            default:
                cout << "Erro: Resultado inesperado na var. digIdt. Por favor, contate o administrador do projeto.\n";
        }

        if(digIdt != 2 )
        {
            cout << endl << CPFs_pos << " CPF(s) encontrado(s) pela varredura simplificada. Deseja realizar uma varredura completa? [s/n]\n"
                 << "[ ]\b\b";

            cin >> validar;

            while (validar != 110 && validar != 115 || cin.peek() != '\n')
            {
                cin.clear();
                cin.ignore(MAX_INT, '\n');
                cout<<"\nResposta inexata. Por favor, responda com 's' ou 'n'.\n"
                    <<"[ ]\b\b";
                cin >> validar;
            }
            if (validar == 115)
            CPFs_pos = repCPF_completo(vCPF, vCPF_dig, 9, eCPF) + CPFs_pos;
        }
    }

    if(CPFs_pos == 0 && digIdt != 2)
    {
        cout << "Erro: CPF sem conserto." << endl;
    }

    cin.ignore();
    cin.get();

    return 0;
}