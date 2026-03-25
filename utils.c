#include "academia.h"

void liberar_aluno_heap(Aluno *aluno) {
    if (aluno == NULL) {
        return;
    }
    free(aluno->nome);
    free(aluno);
}

void liberar_treino_heap(gMuscular *treino) {
    if (treino == NULL) {
        return;
    }
    free(treino->quadriceps);
    free(treino->posterior);
    free(treino->biceps);
    free(treino->triceps);
    free(treino->ombro);
    free(treino->costas);
    free(treino->peitoral);
    free(treino);
}

char *duplicar_texto(const char *texto) {
    if (texto == NULL) {
        return NULL;
    }
    return strdup(texto);
}

void ler_entrada_texto(const char *mensagem, char *destino, size_t tamanho) {
    printf("%s", mensagem);
    if (fgets(destino, tamanho, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }
    destino[strcspn(destino, "\r\n")] = '\0';
}

void imprimir_aluno(const Aluno *aluno) {
    printf("\nNome: %s\n", aluno->nome);
    printf("Idade: %d\n", aluno->idade);
    printf("Peso: %.2f\n", aluno->peso);
    printf("Altura: %.2f\n\n", aluno->altura);
}

void imprimir_treino(const gMuscular *treino) {
    printf("Quadriceps: %s\n", treino->quadriceps);
    printf("Posterior: %s\n", treino->posterior);
    printf("Biceps: %s\n", treino->biceps);
    printf("Triceps: %s\n", treino->triceps);
    printf("Ombro: %s\n", treino->ombro);
    printf("Costas: %s\n", treino->costas);
    printf("Peitoral: %s\n\n", treino->peitoral);
}

int verificar_string(const char *str) {
    if (str == NULL || str[0] == ' ' || str[0] == '\0') {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ') {
            return 0;
        }
    }

    return 1;
}

void capitalizar(char *nome) {
    int length = (int)strlen(nome);
    for (int i = 0; i < length; i++) {
        nome[i] = (char)tolower((unsigned char)nome[i]);
    }

    if (length > 0) {
        nome[0] = (char)toupper((unsigned char)nome[0]);
    }

    for (int i = 1; i < length; i++) {
        if (isspace((unsigned char)nome[i]) && i + 1 < length) {
            nome[i + 1] = (char)toupper((unsigned char)nome[i + 1]);
        }
    }
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int contemLetra(const char *str) {
    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            return 1;
        }
        str++;
    }
    return 0;
}

int ler_int_positivo(const char *mensagem, const char *campo, int tentativas_maximas, int *saida) {
    for (int tentativa = 0; tentativa < tentativas_maximas; tentativa++) {
        printf("%s", mensagem);
        if (scanf("%d", saida) == 1 && *saida > 0) {
            return 1;
        }

        ui_msg_errof("%s invalido! Tentativas restantes: %d", campo, tentativas_maximas - tentativa - 1);
        limpar_buffer();
    }

    ui_msg_erro("Numero maximo de tentativas excedido. Operacao cancelada.");
    return 0;
}

int ler_float_positivo(const char *mensagem, const char *campo, int tentativas_maximas, float *saida) {
    for (int tentativa = 0; tentativa < tentativas_maximas; tentativa++) {
        printf("%s", mensagem);
        if (scanf("%f", saida) == 1 && *saida > 0) {
            return 1;
        }

        ui_msg_errof("%s invalido! Tentativas restantes: %d", campo, tentativas_maximas - tentativa - 1);
        limpar_buffer();
    }

    ui_msg_erro("Numero maximo de tentativas excedido. Operacao cancelada.");
    return 0;
}

