#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Aluno {
    char *nome;
    int idade;
    float peso;
    float altura;
    int matricula;
    struct Aluno *proximo;
};

struct gMuscular
{   
    int matricula;
    char *quadriceps;
    char *posterior;
    char *biceps;
    char *triceps;
    char *ombro;
    char *costas;
    char *peitoral;
    struct gMuscular *proximo;
};

typedef struct Aluno Aluno;
typedef struct gMuscular gMuscular;

Aluno *inicio = NULL;
gMuscular *iniciog = NULL;

Aluno *acessar_aluno_por_matricula(int matricula_desejada);
Aluno *acessar_aluno_por_matricula_arquivo(int matricula_desejada);
gMuscular *acessar_treino_por_matricula(int matricula_desejada);
gMuscular *acessar_treino_por_matricula_arquivo(int matricula_desejada);
void adicionar_aluno(char *nome, int idade, float peso, float altura);
void adicionar_treino(int matricula_desejada, char *quadriceps, char *posterior, char *biceps, char *triceps, char *ombro, char *costas, char *peitoral);
void atualizar_dados_aluno(Aluno *aluno, int matricula_desejada);
void atualizar_treino_aluno(gMuscular *treino, int matricula_desejada);
void cadastrar_aluno();
void cadastrar_treino_aluno(int matricula_desejada);
void deletar_aluno_sistema(Aluno *aluno, int matricula_desejada);
void deletar_treino_sistema(gMuscular *treino, int matricula_desejada);
void limpar_buffer();
void menu();
int mostrar_aluno(int matricula_desejada);
void mostrar_treino(int matricula_desejada);
void salvar_lista_em_arquivo(Aluno *lista_alunos);
void salvar_treino_em_arquivo(gMuscular *lista_treinos_alunos);
void verificar_local_cadastro(int matricula_desejada, int opcao);
void verificar_local_cadastro_treino(int matricula_desejada, int opcao);
struct Aluno* criarAlunoNo(const char *nome, int idade, float peso, float altura, int matricula);
void adicionarAlunoLista(struct Aluno **head, struct Aluno *novoAluno);
void liberarLista(struct Aluno *head);
void consultaNome(struct Aluno *head, char *string);
int contemLetra(const char *str);
void pesquisaAluno();
void capitalizar(char *str);

int verificar_string(const char *str) {
    if (str == NULL) {
        return 0;
    }

    if (str[0] == ' ') {
        return 0;
    }

    if (str[0] == '\0') {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') {
            return 0;
        }
    }

    return 1;
}

Aluno* acessar_aluno_por_matricula(int matricula_desejada){
    
    Aluno *temp = inicio;

    while (temp != NULL) {
        if (temp->matricula == matricula_desejada) {
            return temp;
        }
        temp = temp->proximo;
    }

    return NULL;
}

Aluno* acessar_aluno_por_matricula_arquivo(int matricula_desejada){
    
    FILE *arquivo = fopen("arquivo.txt", "r");

    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));

    char copia_nome[100];

    while (fscanf(arquivo, "%d/%99[^/]/%d/%f/%f", &aluno->matricula, copia_nome, &aluno->idade, &aluno->peso, &aluno->altura) == 5) {
        if (aluno->matricula == matricula_desejada) {
            aluno->nome = strdup(copia_nome);
            fclose(arquivo);
            return aluno;
        }
    }


    fclose(arquivo);
    free(aluno);
    return NULL;
}

gMuscular* acessar_treino_por_matricula(int matricula_desejada){

    gMuscular *temp = iniciog;

    while (temp != NULL) {
        if (temp->matricula == matricula_desejada) {
            return temp;
        }
        temp = temp->proximo;
    }

    return NULL;

}

gMuscular* acessar_treino_por_matricula_arquivo(int matricula_desejada){

    FILE *arquivo = fopen("treino.txt", "r");

    gMuscular *treino = (gMuscular *)malloc(sizeof(gMuscular));

    char copia_quadriceps[256], copia_posterior[256], copia_biceps[256], copia_triceps[256], copia_ombro[256], copia_costas[256], copia_peitoral[256];

    while (fscanf(arquivo, "%d/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255s", &treino->matricula, copia_quadriceps, copia_posterior, copia_biceps, copia_triceps, copia_ombro, copia_costas, copia_peitoral) == 8) {
        if (treino->matricula == matricula_desejada) {
            treino->quadriceps = strdup(copia_quadriceps);
            treino->posterior = strdup(copia_posterior);
            treino->biceps = strdup(copia_biceps);
            treino->triceps = strdup(copia_triceps);
            treino->ombro = strdup(copia_ombro);
            treino->costas = strdup(copia_costas);
            treino->peitoral = strdup(copia_peitoral);
            fclose(arquivo);
            return treino;
        }
    }
    fclose(arquivo);
    free(treino);
    return NULL;
}

void adicionar_aluno(char *nome, int idade, float peso, float altura){

    int proxima_matricula = 202401;

    Aluno *ultimo_aluno = inicio;
    while (ultimo_aluno != NULL && ultimo_aluno->proximo != NULL) {
        ultimo_aluno = ultimo_aluno->proximo;
    }

    if (ultimo_aluno != NULL) {
        proxima_matricula = ultimo_aluno->matricula + 1;
    }

    Aluno *temp = inicio;
    while (temp != NULL) {
        if (temp->matricula == proxima_matricula) {
            proxima_matricula++;
            temp = inicio;
        }
        temp = temp->proximo;
    }

    FILE *arquivo = fopen("arquivo.txt", "r");
    if (arquivo != NULL) {
        int matricula_arquivo;
        char nome_arquivo[100];
        int idade_arquivo;
        float peso_arquivo, altura_arquivo;

        while (fscanf(arquivo, "%d/%99[^/]/%d/%f/%f\n", &matricula_arquivo, nome_arquivo, &idade_arquivo, &peso_arquivo, &altura_arquivo) == 5) {
            if (matricula_arquivo == proxima_matricula) {
                proxima_matricula++;
                fseek(arquivo, 0, SEEK_SET);
            }
        }
        fclose(arquivo);
    }

    Aluno *novo_aluno = (Aluno *)malloc(sizeof(Aluno));
    capitalizar(nome);
    novo_aluno->nome = (char *)malloc(strlen(nome) + 1);
    strcpy(novo_aluno->nome, nome);
    novo_aluno->idade = idade;
    novo_aluno->peso = peso;
    novo_aluno->altura = altura;
    novo_aluno->matricula = proxima_matricula;
    printf("\033[1;32mBem-vindo, seu cadastro foi concluído!\n");
    printf("Sua Matrícula é: \033[1;34m%d.\n\n\033[0m", novo_aluno->matricula);
    novo_aluno->proximo = NULL;
    if (inicio == NULL) {
        inicio = novo_aluno;
    } else {
        Aluno *temp = inicio;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novo_aluno;
    }
}

void adicionar_treino(int matricula_desejada, char *quadriceps, char *posterior, char *biceps, char *triceps, char *ombro, char *costas, char *peitoral){

    gMuscular *treino = (gMuscular *)malloc(sizeof(gMuscular));

    treino->matricula = matricula_desejada;

    treino->quadriceps = (char *)malloc(strlen(quadriceps) + 1);
    strcpy(treino->quadriceps, quadriceps);

    treino->posterior = (char *)malloc(strlen(posterior) + 1);
    strcpy(treino->posterior, posterior);

    treino->biceps = (char *)malloc(strlen(biceps) + 1);
    strcpy(treino->biceps, biceps);

    treino->triceps = (char *)malloc(strlen(triceps) + 1);
    strcpy(treino->triceps, triceps);

    treino->ombro = (char *)malloc(strlen(ombro) + 1);
    strcpy(treino->ombro, ombro);

    treino->costas = (char *)malloc(strlen(costas) + 1);
    strcpy(treino->costas, costas);

    treino->peitoral = (char *)malloc(strlen(peitoral) + 1);
    strcpy(treino->peitoral, peitoral);

    treino->proximo = NULL;

    printf("\033[1;32m\nSeu cadastro de treino foi concluído!\n\033[0m");

    if (iniciog == NULL) {
        iniciog = treino;
    } else {
        gMuscular *temp = iniciog;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = treino;
    }

}

void atualizar_dados_aluno(Aluno *aluno, int matricula_desejada) {
    int opcao;
    char novo_nome[100];

    printf("\nDigite o que deseja atualizar:\n");
    printf("1 - Nome\n");
    printf("2 - Idade\n");
    printf("3 - Peso(kg)\n");
    printf("4 - Altura\n");
    printf("0 - Voltar\n\n");
    scanf("%d", &opcao);
    limpar_buffer();

    if (opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 0) {
        if (opcao == 1) {
            printf("\nAtualize o novo nome: ");
            fgets(novo_nome, sizeof(novo_nome), stdin);
            novo_nome[strcspn(novo_nome, "\n")] = '\0';
            free(aluno->nome);
            capitalizar(novo_nome);
            aluno->nome = strdup(novo_nome);
            printf("\033[1;32m\nNome atualizado com sucesso!\n\033[0m");
        } 
        else if (opcao == 2) {
            printf("\nAtualize a nova idade: ");
            scanf("%d", &aluno->idade);
            limpar_buffer();
            printf("\033[1;32m\nIdade atualizada com sucesso!\n\033[0m");
        } 
        else if (opcao == 3) {
            printf("\nAtualize o novo peso: ");
            scanf("%f", &aluno->peso);
            limpar_buffer();
            printf("\033[1;32m\nPeso atualizado com sucesso!\n\033[0m");
        } 
        else if (opcao == 4) {
            printf("\nAtualize a nova altura: ");
            scanf("%f", &aluno->altura);
            limpar_buffer();
            printf("\033[1;32m\nAltura atualizada com sucesso!\n\033[0m");
        } 
        else {
            return;
        }
    } 
    
    else {
        printf("\033[1;31mOpção inválida!\n\033[0m");
        return;
    }

    if (matricula_desejada == -1)
        return;

    FILE *arquivo = fopen("arquivo.txt", "r");

    FILE *temp_arquivo = fopen("temp.txt", "w");

    char linha[256];
    int matricula;
    char nome[100];
    int idade;
    float peso, altura;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d/%99[^/]/%d/%f/%f\n", &matricula, nome, &idade, &peso, &altura) == 5) {
            if (matricula == matricula_desejada) {
                fprintf(temp_arquivo, "%d/%s/%d/%.2f/%.2f\n", aluno->matricula, aluno->nome, aluno->idade, aluno->peso, aluno->altura);
            } else {
                fprintf(temp_arquivo, "%s", linha);
            }
        } else {
            fprintf(temp_arquivo, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp_arquivo);
    remove("arquivo.txt");
    rename("temp.txt", "arquivo.txt");
    return;
}

void atualizar_treino_aluno(gMuscular *treino, int matricula_desejada){

    int opcao;
    int matricula;
    char novo_treino_quadriceps[256], novo_treino_posterior[256], novo_treino_biceps[256], novo_treino_triceps[256], novo_treino_ombro[256], novo_treino_costas[256], novo_treino_peitoral[256];

    printf("\nDigite o que deseja atualizar:\n");
    printf("1 - Treino de Quadriceps\n");
    printf("2 - Treino de Posterior\n");
    printf("3 - Treino de Biceps\n");
    printf("4 - Treino de Triceps\n");
    printf("5 - Treino de Ombro\n");
    printf("6 - Treino de Costas\n");
    printf("7 - Treino de Peitoral\n");
    printf("0 - Voltar\n\n");
    scanf("%d", &opcao);
    limpar_buffer();

    if(opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5 || opcao == 6 || opcao == 7 || opcao == 0){

        if(opcao == 1){
            printf("\nAtualize o treino de quadríceps: ");
            fgets(novo_treino_quadriceps, sizeof(novo_treino_quadriceps), stdin);
            novo_treino_quadriceps[strcspn(novo_treino_quadriceps, "\n")] = '\0';
            free(treino->quadriceps);
            treino->quadriceps = strdup(novo_treino_quadriceps);
            printf("\033[1;32m\nTreino de quadríceps atualizado com sucesso!\n\033[0m");
        }
        else if(opcao == 2){
            printf("\nAtualize o treino de posterior: ");
            fgets(novo_treino_posterior, sizeof(novo_treino_posterior), stdin);
            novo_treino_posterior[strcspn(novo_treino_posterior, "\n")] = '\0';
            free(treino->posterior);
            treino->posterior = strdup(novo_treino_posterior);
            printf("\033[1;32m\nTreino de posterior atualizado com sucesso!\n\033[0m");
        }
        else if(opcao == 3){
            printf("\nAtualize o treino de biceps: ");
            fgets(novo_treino_biceps, sizeof(novo_treino_biceps), stdin);
            novo_treino_biceps[strcspn(novo_treino_biceps, "\n")] = '\0';
            free(treino->biceps);
            treino->biceps = strdup(novo_treino_biceps);
            printf("\033[1;32m\nTreino de biceps atualizado com sucesso!\n\033[0m");
        }
        else if(opcao == 4){
            printf("\nAtualize o treino de triceps: ");
            fgets(novo_treino_triceps, sizeof(novo_treino_triceps), stdin);
            novo_treino_triceps[strcspn(novo_treino_triceps, "\n")] = '\0';
            free(treino->triceps);
            treino->triceps = strdup(novo_treino_triceps);
            printf("\033[1;32m\nTreino de triceps atualizado com sucesso!\n\033[0m");
        }
        else if(opcao == 5){
            printf("\nAtualize o treino de ombro: ");
            fgets(novo_treino_ombro, sizeof(novo_treino_ombro), stdin);
            novo_treino_ombro[strcspn(novo_treino_ombro, "\n")] = '\0';
            free(treino->ombro);
            treino->ombro = strdup(novo_treino_ombro);
            printf("\033[1;32m\nTreino de ombro atualizado com sucesso!\n\033[0m");
        }
        else if(opcao == 6){
            printf("\nAtualize o treino de costas: ");
            fgets(novo_treino_costas, sizeof(novo_treino_costas), stdin);
            novo_treino_costas[strcspn(novo_treino_costas, "\n")] = '\0';
            free(treino->costas);
            treino->costas = strdup(novo_treino_costas);
            printf("\033[1;32m\nTreino de costas atualizado com sucesso!\n\033[0m");
        }
        else if(opcao == 7){
            printf("\nAtualize o treino de peitoral: ");
            fgets(novo_treino_peitoral, sizeof(novo_treino_peitoral), stdin);
            novo_treino_peitoral[strcspn(novo_treino_peitoral, "\n")] = '\0';
            free(treino->peitoral);
            treino->peitoral = strdup(novo_treino_peitoral);
            printf("\033[1;32m\nTreino de peitoral atualizado com sucesso!\n\033[0m");
        }
        else{
            return;
        }
    }

    else {
        printf("\033[1;31mOpção inválida!\n\n\033[0m");
        return;
    }
    if(matricula_desejada == -1){
        return;
    }

    FILE *arquivo = fopen("treino.txt", "r");
    FILE *temp_arquivo = fopen("temp.txt", "w");
    char linha[2048];

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255s\n",&matricula, novo_treino_quadriceps, novo_treino_posterior, novo_treino_biceps, novo_treino_triceps, novo_treino_ombro, novo_treino_costas, novo_treino_peitoral) == 8) {
            if (matricula == matricula_desejada) {
                fprintf(temp_arquivo, "%d/%s/%s/%s/%s/%s/%s/%s\n", treino->matricula, treino->quadriceps, treino->posterior, treino->biceps, treino->triceps, treino->ombro, treino->costas, treino->peitoral);
            } else {
                fprintf(temp_arquivo, "%s", linha);
            }
        } else {
            fprintf(temp_arquivo, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp_arquivo);
    remove("treino.txt");
    rename("temp.txt", "treino.txt");    
}

void cadastrar_aluno(){
    
    char nome[100];
    int idade;
    float peso, altura;
    int todas_variaveis_recebidas = 0;
    int tentativas_maximas = 3;
    int nome_valido = 1;

    for (int tentativa_nome = 0; tentativa_nome < tentativas_maximas; tentativa_nome++) {
        printf("\nDigite o nome do aluno: ");
        fflush(stdin); 
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';

        nome_valido = 1;

        for (int i = 0; nome[i] != '\0'; i++) {
            if (isdigit(nome[i])) {
                nome_valido = 0;
                break;
            }
        }

        if (!nome_valido || verificar_string(nome) == 0) {
            printf("\033[1;31m\nNome Inválido! Tentativas restantes: %d\n\033[0m", tentativas_maximas - tentativa_nome - 1);
            if (tentativa_nome == tentativas_maximas - 1) {
                printf("\033[1;31m\nNúmero máximo de tentativas excedido. Operação cancelada.\n\n\033[0m");
                return;
            }
        } else {
            todas_variaveis_recebidas++;
            break;
        }
    }

    for (int tentativa_idade = 0; tentativa_idade < tentativas_maximas; tentativa_idade++) {
        printf("\nDigite a idade do aluno: ");
        if (scanf("%d", &idade) != 1 || idade <= 0) {
            printf("\033[1;31m\nIdade Inválida! Tentativas restantes: %d\n\033[0m", tentativas_maximas - tentativa_idade - 1);
            if (tentativa_idade == tentativas_maximas - 1) {
                printf("\033[1;31m\nNúmero máximo de tentativas excedido. Retornando ao menu de opções.\n\n\033[0m");
                limpar_buffer();
                return;
            }
            limpar_buffer();
        } else {
            todas_variaveis_recebidas++;
            break;
        }
    }

    for (int tentativa_peso = 0; tentativa_peso < tentativas_maximas; tentativa_peso++) {
        printf("\nDigite o peso do aluno (em kg): ");
        if (scanf("%f", &peso) != 1 || peso <= 0) {
            printf("\033[1;31m\nPeso Inválido! Tentativas restantes: %d\n\033[0m", tentativas_maximas - tentativa_peso - 1);
            if (tentativa_peso == tentativas_maximas - 1) {
                printf("\033[1;31m\nNúmero máximo de tentativas excedido. Retornando ao menu de opções.\n\n\033[0m");
                limpar_buffer();
                return;
            }
            limpar_buffer();
        } else {
            todas_variaveis_recebidas++;
            break;
        }
    }

    for (int tentativa_altura = 0; tentativa_altura < tentativas_maximas; tentativa_altura++) {
        printf("\nDigite a altura do aluno (em metros): ");
        if (scanf("%f", &altura) != 1 || altura <= 0) {
            printf("\033[1;31m\nAltura Inválida! Tentativas restantes: %d\n\033[0m", tentativas_maximas - tentativa_altura - 1);
            if (tentativa_altura == tentativas_maximas - 1) {
                printf("\033[1;31m\nNúmero máximo de tentativas excedido. Retornando ao menu de opções.\n\n\033[0m");
                limpar_buffer();
                return;
            }
            limpar_buffer();
        } else {
            todas_variaveis_recebidas++;
            break;
        }
    }

    if (todas_variaveis_recebidas == 4) {
        printf("\n");
        adicionar_aluno(nome, idade, peso, altura);
        return;
    }
    return;
}

void cadastrar_treino_aluno(int matricula_desejada){

    gMuscular *treino_memoria = acessar_treino_por_matricula(matricula_desejada);
    if (treino_memoria != NULL) {
        printf("\033[1;31m\nTreino já cadastrado!\n\n\033[0m");
        return;
    }

    gMuscular *treino_arquivo = acessar_treino_por_matricula_arquivo(matricula_desejada);
    if (treino_arquivo != NULL) {
        printf("\033[1;31m\nTreino já cadastrado!\n\n\033[0m");
        return;
    }

    char quadriceps[256], posterior[256], biceps[256], triceps[256], ombro[256], costas[256], peitoral[256];

    printf("\nDigite o treino de QUADRÍCEPS do aluno: ");
    fflush(stdin);
    fgets(quadriceps, sizeof(quadriceps), stdin);
    quadriceps[strcspn(quadriceps, "\n")] = '\0';

    printf("\nDigite o treino de POSTERIOR do aluno: ");
    fflush(stdin);
    fgets(posterior, sizeof(posterior), stdin);
    posterior[strcspn(posterior, "\n")] = '\0';

    printf("\nDigite o treino de BÍCEPS do aluno: ");
    fflush(stdin);
    fgets(biceps, sizeof(biceps), stdin);
    biceps[strcspn(biceps, "\n")] = '\0';

    printf("\nDigite o treino de TRÍCEPS do aluno: ");
    fflush(stdin);
    fgets(triceps, sizeof(triceps), stdin);
    triceps[strcspn(triceps, "\n")] = '\0';

    printf("\nDigite o treino de OMBRO do aluno: ");
    fflush(stdin);
    fgets(ombro, sizeof(ombro), stdin);
    ombro[strcspn(ombro, "\n")] = '\0';

    printf("\nDigite o treino de COSTAS do aluno: ");
    fflush(stdin);
    fgets(costas, sizeof(costas), stdin);
    costas[strcspn(costas, "\n")] = '\0';

    printf("\nDigite o treino de PEITORAL do aluno: ");
    fflush(stdin);
    fgets(peitoral, sizeof(peitoral), stdin);
    peitoral[strcspn(peitoral, "\n")] = '\0';

    adicionar_treino(matricula_desejada,quadriceps,posterior,biceps,triceps,ombro,costas,peitoral);
}

void capitalizar(char *nome) {
    int length = strlen(nome);
    int i;
    for (i = 0; i < length; i++) {
        nome[i] = tolower(nome[i]);
    }
    nome[0] = toupper(nome[0]);
    for (i = 1; i < length; i++) {
        if (isspace(nome[i])) {
            nome[i + 1] = toupper(nome[i + 1]);
        }
    }
}

void deletar_aluno_sistema(Aluno *aluno, int matricula_desejada){

    Aluno *atual = inicio;
    Aluno *anterior = NULL;

    if (matricula_desejada == -1) {
        if (inicio != NULL) {
            while (atual != NULL && atual->matricula != aluno->matricula) {
                anterior = atual;
                atual = atual->proximo;
            }
            if (atual != NULL) {
                if (anterior == NULL) {
                    inicio = atual->proximo;
                } else {
                    anterior->proximo = atual->proximo;
                }
                free(atual->nome);
                free(atual);
                printf("\033\n[1;31mAluno removido com sucesso\n\n\033[0m");
                return;
            }
        }
    }  

    FILE *arquivo_entrada = fopen("arquivo.txt", "r");
    FILE *arquivo_saida = fopen("arquivotemp.txt", "w");

    int removido = 0;

    char linha[256];
    int matricula;
    char nome[100];
    int idade;
    float peso, altura;

    while (fgets(linha, sizeof(linha), arquivo_entrada)) {
        if (sscanf(linha, "%d/%99[^/]/%d/%f/%f\n", &matricula, nome, &idade, &peso, &altura) == 5) {
            if (matricula != matricula_desejada) {
                fprintf(arquivo_saida, "%d/%s/%d/%.2f/%.2f\n", matricula, nome, idade, peso, altura);
            }
            else{
                removido = 1;
            }
        }
    }

    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    remove("arquivo.txt");
    rename("arquivotemp.txt", "arquivo.txt");

    if (removido) {
        printf("\n\033[1;32mAluno removido com sucesso!\n\n\033[0m");
        return;
    }
}

void deletar_treino_sistema(gMuscular *treino, int matricula_desejada){

    gMuscular *atual = iniciog;
    gMuscular *anterior = NULL;

    if (matricula_desejada == -1) {
        if (iniciog != NULL) {
            while (atual != NULL && atual->matricula != treino->matricula) {
                anterior = atual;
                atual = atual->proximo;
            }
            if (atual != NULL) {
                if (anterior == NULL) {
                    iniciog = atual->proximo;
                } else {
                    anterior->proximo = atual->proximo;
                }
                free(atual->quadriceps);
                free(atual->posterior);
                free(atual->biceps);
                free(atual->triceps);
                free(atual->ombro);
                free(atual->costas);
                free(atual->peitoral);
                free(atual);
                return;
            }
        }
    }

    FILE *arquivo_entrada = fopen("treino.txt", "r");
    if(arquivo_entrada != NULL){
        FILE *arquivo_saida = fopen("temp.txt", "w");

        int removido = 0;

        int matricula;
        char novo_treino_quadriceps[256], novo_treino_posterior[256], novo_treino_biceps[256], novo_treino_triceps[256], novo_treino_ombro[256], novo_treino_costas[256], novo_treino_peitoral[256];

        while (fscanf(arquivo_entrada, "%d/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255s\n", &matricula, novo_treino_quadriceps, novo_treino_posterior, novo_treino_biceps, novo_treino_triceps, novo_treino_ombro, novo_treino_costas, novo_treino_peitoral) == 8) {
            if (matricula != matricula_desejada) {
                
                fprintf(arquivo_saida, "%d/%s/%s/%s/%s/%s/%s/%s\n", matricula, novo_treino_quadriceps, novo_treino_posterior, novo_treino_biceps, novo_treino_triceps, novo_treino_ombro, novo_treino_costas, novo_treino_peitoral);
            } 
            else{
                removido = 1;
            }
        }

        fclose(arquivo_entrada);
        fclose(arquivo_saida);
        remove("treino.txt");
        rename("temp.txt", "treino.txt");

        if (removido) {
            printf("Treino removido com sucesso!\n\n");
            return;
        }
    }
}

void limpar_buffer(){
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int contemLetra(const char *str) {
    while (*str != '\0') {  // percorre a string
        if (isalpha((unsigned char)*str)) {
            return 1;  // Retorna 1 se encontrar uma letra
        }
        str++;
    }
    return 0;  // Retorna 0 se não encontrar nenhuma letra
}

struct Aluno* criarAlunoNo(const char *nome, int idade, float peso, float altura, int matricula) {
    
    struct Aluno *novoAluno = (struct Aluno*)malloc(sizeof(struct Aluno));
    if (novoAluno == NULL) {
        printf("Erro ao alocar memória para o novo aluno.\n");
        exit(1);
    }
    novoAluno->nome = strdup(nome); // Duplicar a string nome
    novoAluno->idade = idade;
    novoAluno->peso = peso;
    novoAluno->altura = altura;
    novoAluno->matricula = matricula;
    novoAluno->proximo = NULL;

    return novoAluno;
}

void adicionarAlunoLista(struct Aluno **head, struct Aluno *novoAluno) {
    if (*head == NULL) {
        *head = novoAluno;
    } else {
        struct Aluno *temp = *head;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoAluno;
    }
}

void liberarLista(struct Aluno *head) {
    struct Aluno *temp;
    while (head != NULL) {
        temp = head;
        head = head->proximo;
        free(temp->nome);  // Liberar a memória alocada para o nome
        free(temp);        // Liberar a memória alocada para o nó
    }
}

void consultaNome(struct Aluno *head, char *string){
    struct Aluno *temp = head;
    int algumAluno = 0;
    while (temp != NULL) {
        if(strstr(temp -> nome, string)!= NULL){
            algumAluno = 1;
            printf("\033[0;34mNome:\033[0m %s    \033[0;32mMatricula:\033[0m %d\n", temp -> nome, temp -> matricula);
        }
        temp = temp->proximo;
    }
    if(algumAluno == 0){
        printf("\033[0;31mNao houve aluno com esse nome!\n\033[0m");
    }
    printf("\n");
}

void pesquisaAluno(){
    char pesquisaNome[100];
    int tentativas_maximas = 3;
    int nome_valido = 0;

    for (int tentativa_nome = 0; tentativa_nome < tentativas_maximas; tentativa_nome++) {
        printf("\nDigite uma parte do nome do aluno que deseja consultar: ");
        fflush(stdin); 
        fgets(pesquisaNome, sizeof(pesquisaNome), stdin);
        pesquisaNome[strcspn(pesquisaNome, "\n")] = '\0';
        capitalizar(pesquisaNome);

        nome_valido = 1;

        for (int i = 0; pesquisaNome[i] != '\0'; i++) {
            if (isdigit(pesquisaNome[i])) {
                nome_valido = 0;
                break;
            }
        }

        if (!nome_valido || verificar_string(pesquisaNome) == 0) {
            printf("\033[1;31m\nNome Inválido! Tentativas restantes: %d\n\033[0m", tentativas_maximas - tentativa_nome - 1);
            if (tentativa_nome == tentativas_maximas - 1) {
                printf("\033[1;31m\nNúmero máximo de tentativas excedido. Operação cancelada.\n\n\033[0m");
                return;
            }
        } else {
            printf("\n");
            break;
        }
    }

    if(contemLetra(pesquisaNome)){

        // cria lista encadeada dos alunos a partir do que ta salvo no arquivo
        FILE *arquivo = fopen("arquivo.txt", "r");

        struct Aluno *lista = NULL;
        Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));

        char copia_nome[100];

        while (fscanf(arquivo, "%d/%99[^/]/%d/%f/%f", &aluno->matricula, copia_nome, &aluno->idade, &aluno->peso, &aluno->altura) == 5) {
            aluno->nome = strdup(copia_nome);
            Aluno *alunoTemp = criarAlunoNo(aluno->nome, aluno->idade, aluno->peso, aluno->altura, aluno->matricula);
            adicionarAlunoLista(&lista, alunoTemp);
        }

        // adiciona os alunos que foram adicionados durante a execucao

        Aluno *temp = inicio;

        while (temp != NULL) {
            Aluno *alunoTemp = criarAlunoNo(temp->nome, temp->idade, temp->peso, temp->altura, temp->matricula);
            adicionarAlunoLista(&lista, alunoTemp);
            temp = temp->proximo;
         }

        // percorre os nome dos alunos na lista encadeada, caso esteja a string retorna nome e matricula
        consultaNome(lista, pesquisaNome);

        // fecha arquivo e libera a memoria da lista encadeada
        fclose(arquivo);
        liberarLista(lista);
        free(aluno); 
    }else{
        printf("\033[1;31mEntrada inválida para nome de aluno!\n\n\033[0m");
    }
}

void menu(){
    
    int opcao;
    
    do {
        printf("Escolha uma opcao:\n");
        printf("1 - Cadastrar aluno.\n");
        printf("2 - Acessar aluno por matricula.\n");
        printf("3 - Consultar aluno por nome.\n");
        printf("0 - Sair.\n\n");
        
        if ((scanf("%d", &opcao) == 1) && (opcao == 1 || opcao == 2 ||opcao == 3 || opcao == 0)){

            if(opcao == 1){
            cadastrar_aluno();
            } 
            
            else if(opcao == 2) {
                int matricula_desejada;
                printf("\nDigite a matricula desejada: ");
                scanf("%d", &matricula_desejada);
                int opcao1;
                do{
                    int validacao = mostrar_aluno(matricula_desejada);
                    if (validacao == 1) {
                        printf("Escolha uma opcao:\n");
                        printf("1 - Atualizar dados do aluno\n");
                        printf("2 - Deletar aluno do sistema\n");
                        printf("3 - Cadastrar treino\n");
                        printf("4 - Atualizar treino\n");
                        printf("0 - Voltar\n\n");

                        if((scanf("%d", &opcao1) == 1) && (opcao1 == 1 || opcao1 == 2 || opcao1 == 3 || opcao1 == 4 || opcao1 == 0)){

                            if(opcao1 == 1){
                                verificar_local_cadastro(matricula_desejada,opcao1);
                                }
                            else if(opcao1 == 2){
                                verificar_local_cadastro(matricula_desejada,opcao1);
                                verificar_local_cadastro_treino(matricula_desejada,opcao1);
                                break;
                            }
                            else if(opcao1 == 3){
                                cadastrar_treino_aluno(matricula_desejada);
                            }
                            else if(opcao1 == 4){
                                verificar_local_cadastro_treino(matricula_desejada,1);
                            }
                            else{
                                printf("\nVoltando...\n\n");
                            }
                        }
                        else{
                            printf("\n\033[1;31mOpcao invalida!\n\n\033[0m");
                            break;
                        }
                    }
                    else{
                        break;
                    }
                }while(opcao1 != 0);
            } 
            
            else if(opcao == 3) {
                pesquisaAluno();    
            }
            else{
                printf("\nSaindo...\n");
            }
        } 
        else{
            printf("\n\033[1;31mOpcao invalida!\n\n\033[0m");
            break;
        }

    } while (opcao != 0);

    if(inicio != NULL) {
        salvar_lista_em_arquivo(inicio);
    }

    if(iniciog != NULL){
        salvar_treino_em_arquivo(iniciog);
    }
    
}

int mostrar_aluno(int matricula_desejada) {
    Aluno *aluno = acessar_aluno_por_matricula(matricula_desejada);

    if (aluno != NULL) {
        printf("\n\033[1;34mNome:\033[0m %s\n", aluno->nome);
        printf("\033[1;34mIdade:\033[0m %d\n", aluno->idade);
        printf("\033[1;34mPeso:\033[0m %.2f\n", aluno->peso);
        printf("\033[1;34mAltura:\033[0m %.2f\n\n", aluno->altura);
        mostrar_treino(matricula_desejada);
        return 1;

    } else {
        aluno = acessar_aluno_por_matricula_arquivo(matricula_desejada);
        if (aluno != NULL) {
            printf("\n\033[1;34mNome:\033[0m %s\n", aluno->nome);
            printf("\033[1;34mIdade:\033[0m %d\n", aluno->idade);
            printf("\033[1;34mPeso:\033[0m %.2f\n", aluno->peso);
            printf("\033[1;34mAltura:\033[0m %.2f\n\n", aluno->altura);
            mostrar_treino(matricula_desejada);
            free(aluno);
            return 1;
        } else {
            printf("\n\033[1;31mAluno não encontrado!\n\n\033[0m");
            return 0;
        }
    }
    free(aluno);
}

void mostrar_treino(int matricula_desejada) {
    gMuscular *treino = acessar_treino_por_matricula(matricula_desejada);

    if (treino != NULL) {
        printf("\033[1;32mQuadríceps:\033[0m %s\n", treino->quadriceps);
        printf("\033[1;32mPosterior:\033[0m %s\n", treino->posterior);
        printf("\033[1;32mBíceps:\033[0m %s\n", treino->biceps);
        printf("\033[1;32mTríceps:\033[0m %s\n", treino->triceps);
        printf("\033[1;32mOmbro:\033[0m %s\n", treino->ombro);
        printf("\033[1;32mCostas:\033[0m %s\n", treino->costas);
        printf("\033[1;32mPeitoral:\033[0m %s\n\n", treino->peitoral);
        return;
    } else {
        treino = acessar_treino_por_matricula_arquivo(matricula_desejada);
        if (treino != NULL) {
            printf("\033[1;32mQuadríceps:\033[0m %s\n", treino->quadriceps);
            printf("\033[1;32mPosterior:\033[0m %s\n", treino->posterior);
            printf("\033[1;32mBíceps:\033[0m %s\n", treino->biceps);
            printf("\033[1;32mTríceps:\033[0m %s\n", treino->triceps);
            printf("\033[1;32mOmbro:\033[0m %s\n", treino->ombro);
            printf("\033[1;32mCostas:\033[0m %s\n", treino->costas);
            printf("\033[1;32mPeitoral:\033[0m %s\n\n", treino->peitoral);
            free(treino);
            return;
        } else {
            printf("\033[1;31mTreino ainda não cadastrado!\n\n\033[0m");
            return;
        }
    }
    free(treino);
}

void salvar_lista_em_arquivo(Aluno *lista_alunos){
 
    FILE *arquivo;
    arquivo = fopen("arquivo.txt", "r");
    if (arquivo == NULL) {
        arquivo = fopen("arquivo.txt", "w");
    }
    else{
        arquivo = fopen("arquivo.txt", "a+");
    }

    while (lista_alunos != NULL) {
        fprintf(arquivo, "%d/%s/%d/%.2f/%.2f\n", lista_alunos->matricula, lista_alunos->nome, lista_alunos->idade, lista_alunos->peso, lista_alunos->altura);
        lista_alunos = lista_alunos->proximo;
    }

    fclose(arquivo);
}

void salvar_treino_em_arquivo(gMuscular *lista_treinos_alunos){
    
    FILE *arquivo;
    arquivo = fopen("treino.txt", "r");
    if (arquivo == NULL) {
        arquivo = fopen("treino.txt", "w");
    }
    else{
        arquivo = fopen("treino.txt", "a+");
    }

    while (lista_treinos_alunos != NULL) {
        fprintf(arquivo, "%d/%s/%s/%s/%s/%s/%s/%s\n", lista_treinos_alunos->matricula, lista_treinos_alunos->quadriceps, lista_treinos_alunos->posterior, lista_treinos_alunos->biceps, lista_treinos_alunos->triceps, lista_treinos_alunos->ombro, lista_treinos_alunos->costas,lista_treinos_alunos->peitoral);
        lista_treinos_alunos = lista_treinos_alunos->proximo;
    }

    fclose(arquivo);
}

void verificar_local_cadastro(int matricula_desejada,int opcao){

    Aluno *aluno = acessar_aluno_por_matricula(matricula_desejada);

    if(aluno == NULL){

        aluno = acessar_aluno_por_matricula_arquivo(matricula_desejada);
        
        if(opcao ==1){
            atualizar_dados_aluno(aluno, matricula_desejada);   
        }
        else{
            deletar_aluno_sistema(aluno, matricula_desejada);
        }
    } 
    else{
        if(opcao == 1){
            atualizar_dados_aluno(aluno, -1);
        }
        else{
            deletar_aluno_sistema(aluno, -1);
        }
    }    
}

void verificar_local_cadastro_treino(int matricula_desejada, int opcao){

    gMuscular *treino = acessar_treino_por_matricula(matricula_desejada);

    if (treino == NULL) {

        treino = acessar_treino_por_matricula_arquivo(matricula_desejada);

        if(opcao == 1){
            if(treino == NULL){
                printf("\033[1;31mTreino ainda não cadastrado!\n\n\033[0m");
            }
            else{
                atualizar_treino_aluno(treino, matricula_desejada);
                return;
            }
        }
        else{
            if(treino != NULL){
                deletar_treino_sistema(treino, matricula_desejada);
            }
        }
    }
    else{
        if(opcao == 1){
            atualizar_treino_aluno(treino, -1);
        }
        else{
            deletar_treino_sistema(treino, -1);
        }
    }
}

void imprimir_boas_vindas() {
    printf("\033[1;38;5;208m*****************************************\n");
    printf("*                                       *\n");
    printf("*               BEM-VINDO               *\n");
    printf("*          SISTEMA DE ACADEMIA          *\n");
    printf("*                                       *\n");
    printf("*****************************************\033[0m\n\n");
}

void limpar_terminal() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

int main(){
    imprimir_boas_vindas();
    menu();
    limpar_terminal();
    return 0;
}