#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Defini��o dos tipos de chave
typedef int TipoChave;

// Defini��o de uma c�lula da lista encadeada
typedef struct TipoCelula *Apontador;

// Defini��o de estruturas para representar diferentes tipos de entidades
typedef struct
{
    int ID;
    int idTurma;
    char nomeProfessor[80];
    char disciplina[50];
} TipoProfessor;

typedef struct
{
    int ID;
    int idTurma;
    char nomeAluno[80];
    int idade;
} TipoAluno;

typedef struct
{
    int ID;
    char nomeDoCurso[50];
    int cargaHoraria;
    char descricaoCurso[500];
} TipoCurso;

typedef struct
{
    int ID;
    int idProfessor;
} TipoTurma;

typedef union
{
    TipoAluno aluno;
    TipoCurso curso;
    TipoTurma turma;
    TipoProfessor professor;
} TipoItem;

// Defini��o da estrutura de uma c�lula da lista encadeada
struct TipoCelula
{
    TipoItem Item;
    Apontador Prox;
};

// Defini��o de uma lista encadeada
typedef struct
{
    Apontador Primeiro, Ultimo;
    int TagTipo; // Identifica o tipo de entidade na lista
    int tamanho; // Armazena o tamanho da lista
} TipoLista;

// Declara��o de inst�ncias das listas para diferentes tipos de entidades
TipoLista AlunosInstancia, CursosInstancia, TurmasInstancia, ProfessoresInstancia;

// Fun��o para inicializar uma lista encadeada
void Inicia(TipoLista *Lista)
{
    Lista->Primeiro = (Apontador)malloc(sizeof(struct TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
    Lista->tamanho = 0;
}

// Fun��o para verificar se uma lista est� vazia
int Vazia(TipoLista *Lista)
{
    return (Lista->Primeiro == Lista->Ultimo);
}

// Fun��o para inserir um item no final da lista
void Insere(TipoItem *x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (Apontador)malloc(sizeof(struct TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = *x;
    Lista->Ultimo->Prox = NULL;
    Lista->tamanho++;
}

// Fun��o para imprimir informa��es de um aluno
void Imprime1Aluno(TipoAluno aluno)
{
    printf("Matr�cula: %d\n", aluno.ID);
    printf("Nome: %s\n", aluno.nomeAluno);
    printf("Turma matriculado: %d\n", aluno.idTurma);
    printf("\n");
}

// Fun��o para imprimir informa��es de um curso
void Imprime1Curso(TipoCurso curso)
{
    printf("Nome do Curso: %s\n", curso.nomeDoCurso);
    printf("Carga Hor�ria: %d horas\n", curso.cargaHoraria);
    printf("ID do Curso: %d\n", curso.ID);
    printf("Descri��o do Curso: %s\n", curso.descricaoCurso);
    printf("\n");
}

// Fun��o para imprimir informa��es de um professor
void Imprime1Professor(TipoProfessor professor)
{
    printf("Nome do Professor: %s\n", professor.nomeProfessor);
    printf("Disciplina Lecionada: %s\n", professor.disciplina);
    printf("\n");
}

// Fun��o para buscar um item por ID na lista
TipoItem *getById(int idToSearch, TipoLista Lista)
{
    Apontador Aux;
    Aux = Lista.Primeiro;

    while (Aux != NULL)
    {
        TipoItem *itemNow = &(Aux->Item);

        switch (Lista.TagTipo)
        {
        case 1:
            if (itemNow->aluno.ID == idToSearch)
            {
                return itemNow;
            }
            break;
        case 2:
            if (itemNow->curso.ID == idToSearch)
            {
                return itemNow;
            }
            break;
        case 3:
            if (itemNow->turma.ID == idToSearch)
            {
                return itemNow;
            }
            break;
        case 4:
            if (itemNow->professor.ID == idToSearch)
            {
                return itemNow;
            }
            break;
        default:
            break;
        }

        Aux = Aux->Prox;
    }

    return NULL;
}

// Fun��o para imprimir informa��es de uma turma
void Imprime1Turma(TipoTurma turma)
{
    printf("Identificador da Turma: %d\n", turma.ID);

    if (turma.idProfessor)
    {
        printf("Professor Respons�vel: ");
        Imprime1Professor(getById(turma.idProfessor, ProfessoresInstancia)->professor);
    }
    else
    {
        printf("Nenhum professor responsavel");
    }
}

// Fun��o para imprimir a lista de entidades com base no tipo
void ImprimeLista(TipoLista Lista)
{
    Apontador Aux;
    Aux = Lista.Primeiro->Prox;

    while (Aux != NULL)
    {
        TipoItem itemNow = Aux->Item;

        switch (Lista.TagTipo)
        {
        case 1:
            Imprime1Aluno(itemNow.aluno);
            break;
        case 2:
            Imprime1Curso(itemNow.curso);
            break;
        case 3:
            Imprime1Turma(itemNow.turma);
            break;
        case 4:
            Imprime1Professor(itemNow.professor);
            break;
        default:
            break;
        }

        Aux = Aux->Prox;
    }
}

// Fun��o para liberar a mem�ria alocada para a lista
void DestroiLista(TipoLista *Lista)
{
    Apontador Aux = Lista->Primeiro;

    while (Aux != NULL)
    {
        Apontador temp = Aux;
        Aux = Aux->Prox;
        free(temp);
    }

    Lista->Primeiro = Lista->Ultimo = NULL;
    Lista->tamanho = 0;
}
