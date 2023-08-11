#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct registro {       // registro de funcionario
	int matricula;
	char nome[30];
	float salario;
	struct registro *next;
};

typedef struct registro Registro;

Registro *ptrFirstNode; // ponteiro para o primeiro elemento da lista dinâmica
Registro *ptrLastNode;  // ponteiro para o último elemento da lista dinâmica

//Inicializa os ponteiros da lista
void inicializar();

// Realiza a leitura dos campos do registro e insere no final da lista
// A lista NÃO pode conter registros com a mesma matrícula
void inserir();

// Localiza o registro de matricula lida e realiza a leitura e substituicao do campo salario
// Informar em console caso o registro para a matrícula lida não exista na lista
void alterar();

// Localiza o registro de matricula lida e exibe em console os campos do registro
// Informar em console caso o registro para a matrícula lida não exista na lista
void exibir();

// Listar os registros incluídos na lista, uma linha para cada registro
// Ao término, informar o valor total dos salários, o valor médio e o maios salario
void listar();

// Retorna o endereço do registro da lista para a matrícula informada
// Caso não exista o registro procurado, returna NULL
Registro *buscar(int matricula);

// Realiza a leitura em console e retorna uma matrícula
int lerMatricula();

// Menu de opções para: 
// (1)inserir registro, (2)exibir registro, (3)alterar salario, (4)listar registros e (5)sair
int menu();

//ler o arquivo sequencial (.txt) gravado (em disco) e inserir os registros na lista (em memória).
void LerArquivo();

//salvar os registros da lista (em memória) para um arquivo sequencial (em disco) no formato texto (.txt)
void SalvarArquivo();


int main()
{
    inicializar();

    for(;;) {
        switch (menu()) {
            case 1: 
                inserir();
                break;
            case 2: 
                exibir();
                break;
            case 3: 
                alterar();
                break;
            case 4: 
                listar();
                break;
            case 5:
                LerArquivo();
                break;
            case 6:
                SalvarArquivo();
                break;
            case 7:
                exit(0);
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    
    return 0;
}

void inicializar()
{
    ptrFirstNode = NULL;
    ptrLastNode = NULL;
}


int menu()
{
    int op;

    printf("\n(1)inserir registro\n(2)exibir registro\n(3)alterar salario\n(4)listar registros\n(5)Ler Arquivo\n(6)Salvar Arquivo\n(7)sair");

    scanf("%d", &op);

    return op;

}

void inserir()
{
    Registro *noatual, *nonovo, *cabeca;

    cabeca = ptrFirstNode;

    int nova_matricula;
    float novo_salario;
    char novo_nome[30];

    printf("Digite a matrícula: \n");
    scanf (" %d", &nova_matricula);

    printf("Digite o nome: \n");
    scanf (" %s", novo_nome);
    
    printf("Digite o salario: \n");
    scanf(" %f", &novo_salario);
    

    if(cabeca == NULL)
    {
        cabeca = (Registro*) malloc(sizeof(Registro));

        cabeca -> matricula = nova_matricula;
        strcpy(cabeca -> nome, novo_nome);
        cabeca -> salario = novo_salario;
        cabeca -> next = NULL;
    }

    else if (buscar(nova_matricula))
    {
        printf ("\nMatrícula já cadastrada!\n");
    }

    else 
    {
        
        noatual = cabeca;

        while (noatual -> next != NULL)
        { 
            noatual = noatual -> next;
        }

        nonovo = (Registro*) malloc(sizeof(Registro));

        nonovo -> matricula = nova_matricula;
        strcpy(nonovo -> nome, novo_nome);
        nonovo -> salario = novo_salario;
        nonovo -> next = NULL;
        noatual -> next = nonovo;
    }

    ptrFirstNode = cabeca;


}



void listar()
{
    
    Registro *node;

    node = ptrFirstNode;

    float valor_total_salario = 0;
    float i = 0;
    float maior = node -> salario;

    while (node != NULL)
    {
        printf("Matrícula: %d\t\t", node -> matricula );
        printf("Nome: %s\t", node -> nome );
        printf("Salário: %.2f\n\n", node -> salario );

        if (node -> salario > maior)
        {
            maior = node -> salario;
        }

        valor_total_salario = valor_total_salario + node -> salario;
        i++;

        node = node -> next;
    }

    printf("\tValor total do salário: %.2f\n\n", valor_total_salario );
    printf("\tMédia dos salários: %.2f\n\n", valor_total_salario / i );
    printf("\tO maior salário: %.2f\n\n", maior );

}

int lerMatricula()
{
    int matricula;


    printf("Digite a matrícula: \n\n");
    scanf("%d", &matricula);

    return matricula;
}

void exibir()

{
    Registro *noatual;

    noatual = ptrFirstNode;

    int matricula;

    matricula = lerMatricula();

    
    if(buscar(matricula))
    {
        printf("\n\nA matricula: %d\n", buscar(matricula) -> matricula);
        printf("Nome: %s\n", buscar(matricula) -> nome);
        printf("O salário: %.2f\n\n", buscar(matricula) ->salario);
        return;
    }
       
    printf ("Matrícula não cadastrada!\n\n");
        
}

Registro *buscar(int matricula)
{

    Registro *noatual;

    noatual = ptrFirstNode;
    
    while (noatual != NULL)
    {
        if (noatual -> matricula == matricula)
        {
            return noatual;
        }

        noatual = noatual -> next;
    }
    
}

void alterar()
{
    int matricula;
    float salario_att;


    matricula = lerMatricula();

    if (buscar(matricula))
    {
        printf("\nDigite o novo salario: \n");
        scanf(" %f", &salario_att);

    buscar(matricula) -> salario = salario_att;

    }

    else 
    {
        printf("\nMatricula não encontrada\n");
    }
}



void LerArquivo(){

    FILE *file;

    file = fopen("D:\\Intro Prog\\trabalho2 - Copia\\teste.txt", "r");

    if(file == NULL){
      printf("Nao foi possivel abrir o arquivo\n");
      return;
    }

    int matr;
    char name[30];
    float sal;

    while(!feof(file)){

    fscanf(file, "%d %s %f", &matr, name, &sal);

      inserir(matr, sal, name);
    }

    printf("Arquivo lido\n");
}

void SalvarArquivo(){

    FILE *file;
    Registro *aux = ptrFirstNode;

    file = fopen("D:\\Intro Prog\\trabalho2 - Copia\\teste.txt", "w");

    while(aux != NULL){

      fprintf(file,"%d %s %0.2f\n",aux->matricula, aux->nome, aux->salario);
      aux = aux->next;
    }

    fclose(file);

}
