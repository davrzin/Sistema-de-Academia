#include "academia.h"

static int ler_treino_nao_vazio(const char *mensagem, char *destino, size_t tamanho) {
    const int tentativas_maximas = 3;

    for (int tentativa = 0; tentativa < tentativas_maximas; tentativa++) {
        ler_entrada_texto(mensagem, destino, tamanho);
        if (destino[0] != '\0') {
            return 1;
        }
        ui_msg_errof("Treino invalido! Tentativas restantes: %d", tentativas_maximas - tentativa - 1);
    }

    ui_msg_erro("Numero maximo de tentativas excedido. Operacao cancelada.");
    return 0;
}

static void trim_espacos(char *texto) {
    char *inicio_trim;
    char *fim_trim;

    if (texto == NULL || texto[0] == '\0') {
        return;
    }

    inicio_trim = texto;
    while (*inicio_trim != '\0' && isspace((unsigned char)*inicio_trim)) {
        inicio_trim++;
    }

    if (inicio_trim != texto) {
        memmove(texto, inicio_trim, strlen(inicio_trim) + 1);
    }

    if (texto[0] == '\0') {
        return;
    }

    fim_trim = texto + strlen(texto) - 1;
    while (fim_trim >= texto && isspace((unsigned char)*fim_trim)) {
        *fim_trim = '\0';
        fim_trim--;
    }
}

gMuscular *acessar_treino_por_matricula(int matricula_desejada) {
    gMuscular *temp = iniciog;

    while (temp != NULL) {
        if (temp->matricula == matricula_desejada) {
            return temp;
        }
        temp = temp->proximo;
    }

    return NULL;
}

gMuscular *acessar_treino_por_matricula_arquivo(int matricula_desejada) {
    FILE *arquivo = fopen(ARQ_TREINOS, "r");
    if (arquivo == NULL) {
        return NULL;
    }

    gMuscular *treino = (gMuscular *)malloc(sizeof(gMuscular));
    if (treino == NULL) {
        fclose(arquivo);
        return NULL;
    }

    char copia_quadriceps[256], copia_posterior[256], copia_biceps[256], copia_triceps[256], copia_ombro[256], copia_costas[256], copia_peitoral[256];

    while (fscanf(arquivo, "%d/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255s", &treino->matricula, copia_quadriceps, copia_posterior, copia_biceps, copia_triceps, copia_ombro, copia_costas, copia_peitoral) == 8) {
        if (treino->matricula == matricula_desejada) {
            trim_espacos(copia_quadriceps);
            trim_espacos(copia_posterior);
            trim_espacos(copia_biceps);
            trim_espacos(copia_triceps);
            trim_espacos(copia_ombro);
            trim_espacos(copia_costas);
            trim_espacos(copia_peitoral);

            treino->quadriceps = duplicar_texto(copia_quadriceps);
            treino->posterior = duplicar_texto(copia_posterior);
            treino->biceps = duplicar_texto(copia_biceps);
            treino->triceps = duplicar_texto(copia_triceps);
            treino->ombro = duplicar_texto(copia_ombro);
            treino->costas = duplicar_texto(copia_costas);
            treino->peitoral = duplicar_texto(copia_peitoral);

            if (treino->quadriceps == NULL || treino->posterior == NULL || treino->biceps == NULL || treino->triceps == NULL || treino->ombro == NULL || treino->costas == NULL || treino->peitoral == NULL) {
                fclose(arquivo);
                liberar_treino_heap(treino);
                return NULL;
            }

            fclose(arquivo);
            return treino;
        }
    }

    fclose(arquivo);
    free(treino);
    return NULL;
}

void adicionar_treino(int matricula_desejada, char *quadriceps, char *posterior, char *biceps, char *triceps, char *ombro, char *costas, char *peitoral) {
    gMuscular *treino = (gMuscular *)malloc(sizeof(gMuscular));
    if (treino == NULL) {
        ui_msg_erro("Erro de memoria ao cadastrar treino.");
        return;
    }

    treino->matricula = matricula_desejada;

    treino->quadriceps = duplicar_texto(quadriceps);
    treino->posterior = duplicar_texto(posterior);
    treino->biceps = duplicar_texto(biceps);
    treino->triceps = duplicar_texto(triceps);
    treino->ombro = duplicar_texto(ombro);
    treino->costas = duplicar_texto(costas);
    treino->peitoral = duplicar_texto(peitoral);

    if (treino->quadriceps == NULL || treino->posterior == NULL || treino->biceps == NULL || treino->triceps == NULL || treino->ombro == NULL || treino->costas == NULL || treino->peitoral == NULL) {
        liberar_treino_heap(treino);
        ui_msg_erro("Erro de memoria ao cadastrar treino.");
        return;
    }

    treino->proximo = NULL;

    ui_msg_sucesso("Seu cadastro de treino foi concluido!");

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

void atualizar_treino_aluno(gMuscular *treino, int matricula_desejada) {
    int opcao;
    int matricula;
    char novo_treino[256];
    char novo_treino_quadriceps[256], novo_treino_posterior[256], novo_treino_biceps[256], novo_treino_triceps[256], novo_treino_ombro[256], novo_treino_costas[256], novo_treino_peitoral[256];

    char **campos_treino[] = {
        &treino->quadriceps,
        &treino->posterior,
        &treino->biceps,
        &treino->triceps,
        &treino->ombro,
        &treino->costas,
        &treino->peitoral
    };

    const char *nomes_treino[] = {
        "quadriceps",
        "posterior",
        "biceps",
        "triceps",
        "ombro",
        "costas",
        "peitoral"
    };

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

    if (opcao < 0 || opcao > 7) {
        ui_msg_erro("Opcao invalida!");
        return;
    }

    if (opcao == 0) {
        return;
    }

    {
        char mensagem[96];
        snprintf(mensagem, sizeof(mensagem), "\nAtualize o treino de %s: ", nomes_treino[opcao - 1]);
        if (!ler_treino_nao_vazio(mensagem, novo_treino, sizeof(novo_treino))) {
            return;
        }
        trim_espacos(novo_treino);
        if (novo_treino[0] == '\0') {
            ui_msg_erro("Treino invalido!");
            return;
        }
    }

    char *novo_valor = duplicar_texto(novo_treino);
    if (novo_valor == NULL) {
        ui_msg_erro("Erro de memoria ao atualizar treino.");
        return;
    }
    free(*campos_treino[opcao - 1]);
    *campos_treino[opcao - 1] = novo_valor;

    printf("Treino de %s atualizado com sucesso!\n", nomes_treino[opcao - 1]);

    if (matricula_desejada == -1) {
        return;
    }

    FILE *arquivo = NULL;
    FILE *temp_arquivo = NULL;
    if (!abrir_arquivos_reescrita(ARQ_TREINOS, "temp.txt", &arquivo, &temp_arquivo)) {
        return;
    }

    char linha[2048];

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255s\n", &matricula, novo_treino_quadriceps, novo_treino_posterior, novo_treino_biceps, novo_treino_triceps, novo_treino_ombro, novo_treino_costas, novo_treino_peitoral) == 8) {
            if (matricula == matricula_desejada) {
                fprintf(temp_arquivo, "%d/%s/%s/%s/%s/%s/%s/%s\n", treino->matricula, treino->quadriceps, treino->posterior, treino->biceps, treino->triceps, treino->ombro, treino->costas, treino->peitoral);
            } else {
                fprintf(temp_arquivo, "%s", linha);
            }
        } else {
            fprintf(temp_arquivo, "%s", linha);
        }
    }

    finalizar_reescrita_arquivo(arquivo, temp_arquivo, ARQ_TREINOS, "temp.txt");
}

void cadastrar_treino_aluno(int matricula_desejada) {
    gMuscular *treino_memoria = acessar_treino_por_matricula(matricula_desejada);
    if (treino_memoria != NULL) {
        ui_msg_aviso("Treino ja cadastrado!");
        return;
    }

    gMuscular *treino_arquivo = acessar_treino_por_matricula_arquivo(matricula_desejada);
    if (treino_arquivo != NULL) {
        liberar_treino_heap(treino_arquivo);
        ui_msg_aviso("Treino ja cadastrado!");
        return;
    }

    char quadriceps[256], posterior[256], biceps[256], triceps[256], ombro[256], costas[256], peitoral[256];
    char *campos[] = {quadriceps, posterior, biceps, triceps, ombro, costas, peitoral};
    const char *grupos[] = {"QUADRICEPS", "POSTERIOR", "BICEPS", "TRICEPS", "OMBRO", "COSTAS", "PEITORAL"};
    char mensagem[96];

    for (int i = 0; i < 7; i++) {
        snprintf(mensagem, sizeof(mensagem), "\nDigite o treino de %s do aluno: ", grupos[i]);
        if (!ler_treino_nao_vazio(mensagem, campos[i], 256)) {
            return;
        }
        trim_espacos(campos[i]);
        if (campos[i][0] == '\0') {
            ui_msg_erro("Treino invalido!");
            return;
        }
    }

    adicionar_treino(matricula_desejada, quadriceps, posterior, biceps, triceps, ombro, costas, peitoral);
}

void deletar_treino_sistema(gMuscular *treino, int matricula_desejada) {
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
                liberar_treino_heap(atual);
                return;
            }
        }
    }

    FILE *arquivo_entrada = NULL;
    FILE *arquivo_saida = NULL;
    if (abrir_arquivos_reescrita(ARQ_TREINOS, "temp.txt", &arquivo_entrada, &arquivo_saida)) {

        int removido = 0;
        int matricula;
        char novo_treino_quadriceps[256], novo_treino_posterior[256], novo_treino_biceps[256], novo_treino_triceps[256], novo_treino_ombro[256], novo_treino_costas[256], novo_treino_peitoral[256];

        while (fscanf(arquivo_entrada, "%d/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255[^/]/%255s\n", &matricula, novo_treino_quadriceps, novo_treino_posterior, novo_treino_biceps, novo_treino_triceps, novo_treino_ombro, novo_treino_costas, novo_treino_peitoral) == 8) {
            if (matricula != matricula_desejada) {
                fprintf(arquivo_saida, "%d/%s/%s/%s/%s/%s/%s/%s\n", matricula, novo_treino_quadriceps, novo_treino_posterior, novo_treino_biceps, novo_treino_triceps, novo_treino_ombro, novo_treino_costas, novo_treino_peitoral);
            } else {
                removido = 1;
            }
        }

        finalizar_reescrita_arquivo(arquivo_entrada, arquivo_saida, ARQ_TREINOS, "temp.txt");

        if (removido) {
            printf("Treino removido com sucesso!\n\n");
        }
    }
}

void mostrar_treino(int matricula_desejada) {
    gMuscular *treino = acessar_treino_por_matricula(matricula_desejada);

    if (treino != NULL) {
        imprimir_treino(treino);
        return;
    }

    treino = acessar_treino_por_matricula_arquivo(matricula_desejada);
    if (treino != NULL) {
        imprimir_treino(treino);
        liberar_treino_heap(treino);
        return;
    }

    ui_msg_erro("Treino ainda nao cadastrado!");
}

void salvar_treino_em_arquivo(gMuscular *lista_treinos_alunos) {
    FILE *arquivo = abrir_arquivo_append(ARQ_TREINOS);
    if (arquivo == NULL) {
        return;
    }

    while (lista_treinos_alunos != NULL) {
        fprintf(arquivo, "%d/%s/%s/%s/%s/%s/%s/%s\n", lista_treinos_alunos->matricula, lista_treinos_alunos->quadriceps, lista_treinos_alunos->posterior, lista_treinos_alunos->biceps, lista_treinos_alunos->triceps, lista_treinos_alunos->ombro, lista_treinos_alunos->costas, lista_treinos_alunos->peitoral);
        lista_treinos_alunos = lista_treinos_alunos->proximo;
    }

    fclose(arquivo);
}

void verificar_local_cadastro_treino(int matricula_desejada, int opcao) {
    gMuscular *treino = acessar_treino_por_matricula(matricula_desejada);

    if (treino == NULL) {
        treino = acessar_treino_por_matricula_arquivo(matricula_desejada);

        if (opcao == 1) {
            if (treino == NULL) {
                ui_msg_erro("Treino ainda nao cadastrado!");
            } else {
                atualizar_treino_aluno(treino, matricula_desejada);
                liberar_treino_heap(treino);
                return;
            }
        } else {
            if (treino != NULL) {
                deletar_treino_sistema(treino, matricula_desejada);
                liberar_treino_heap(treino);
            }
        }
        return;
    }

    if (opcao == 1) {
        atualizar_treino_aluno(treino, -1);
    } else {
        deletar_treino_sistema(treino, -1);
    }
}

