#ifndef ACADEMIA_H
#define ACADEMIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARQ_ALUNOS "arquivo.txt"
#define ARQ_TREINOS "treino.txt"

typedef struct Aluno {
    char *nome;
    int idade;
    float peso;
    float altura;
    int matricula;
    struct Aluno *proximo;
} Aluno;

typedef struct gMuscular {
    int matricula;
    char *quadriceps;
    char *posterior;
    char *biceps;
    char *triceps;
    char *ombro;
    char *costas;
    char *peitoral;
    struct gMuscular *proximo;
} gMuscular;

extern Aluno *inicio;
extern gMuscular *iniciog;

/* utils.c */
void liberar_aluno_heap(Aluno *aluno);
void liberar_treino_heap(gMuscular *treino);
char *duplicar_texto(const char *texto);
void ler_entrada_texto(const char *mensagem, char *destino, size_t tamanho);
void imprimir_aluno(const Aluno *aluno);
void imprimir_treino(const gMuscular *treino);
int verificar_string(const char *str);
void capitalizar(char *str);
void limpar_buffer();
int contemLetra(const char *str);
int ler_int_positivo(const char *mensagem, const char *campo, int tentativas_maximas, int *saida);
int ler_float_positivo(const char *mensagem, const char *campo, int tentativas_maximas, float *saida);

/* aluno.c */
Aluno *acessar_aluno_por_matricula(int matricula_desejada);
Aluno *acessar_aluno_por_matricula_arquivo(int matricula_desejada);
void adicionar_aluno(char *nome, int idade, float peso, float altura);
void atualizar_dados_aluno(Aluno *aluno, int matricula_desejada);
void cadastrar_aluno();
void deletar_aluno_sistema(Aluno *aluno, int matricula_desejada);
Aluno *criarAlunoNo(const char *nome, int idade, float peso, float altura, int matricula);
void adicionarAlunoLista(Aluno **head, Aluno *novoAluno);
void liberarLista(Aluno *head);
void consultaNome(Aluno *head, char *string);
void pesquisaAluno();
int mostrar_aluno(int matricula_desejada);
void salvar_lista_em_arquivo(Aluno *lista_alunos);
void verificar_local_cadastro(int matricula_desejada, int opcao);

/* treino.c */
gMuscular *acessar_treino_por_matricula(int matricula_desejada);
gMuscular *acessar_treino_por_matricula_arquivo(int matricula_desejada);
void adicionar_treino(int matricula_desejada, char *quadriceps, char *posterior, char *biceps, char *triceps, char *ombro, char *costas, char *peitoral);
void atualizar_treino_aluno(gMuscular *treino, int matricula_desejada);
void cadastrar_treino_aluno(int matricula_desejada);
void deletar_treino_sistema(gMuscular *treino, int matricula_desejada);
void mostrar_treino(int matricula_desejada);
void salvar_treino_em_arquivo(gMuscular *lista_treinos_alunos);
void verificar_local_cadastro_treino(int matricula_desejada, int opcao);

/* menu.c */
void menu();

/* ui.c */
void configurar_terminal();
void ui_msg_info(const char *mensagem);
void ui_msg_sucesso(const char *mensagem);
void ui_msg_aviso(const char *mensagem);
void ui_msg_erro(const char *mensagem);
void ui_msg_errof(const char *formato, ...);
void imprimir_boas_vindas();
void limpar_terminal();

/* persistencia.c */
FILE *abrir_arquivo_append(const char *caminho);
int abrir_arquivos_reescrita(const char *origem, const char *temporario, FILE **entrada, FILE **saida);
int finalizar_reescrita_arquivo(FILE *entrada, FILE *saida, const char *origem, const char *temporario);

#endif
