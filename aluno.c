#include "academia.h"

static int ler_nome_valido(char *nome, size_t tamanho, int tentativas_maximas, const char *mensagem_prompt) {
    for (int tentativa = 0; tentativa < tentativas_maximas; tentativa++) {
        printf("%s", mensagem_prompt);
        fgets(nome, tamanho, stdin);
        nome[strcspn(nome, "\r\n")] = '\0';

        int nome_valido = verificar_string(nome);
        for (int i = 0; nome[i] != '\0'; i++) {
            if (isdigit((unsigned char)nome[i])) {
                nome_valido = 0;
                break;
            }
        }

        if (nome_valido) {
            return 1;
        }

        ui_msg_errof("Nome invalido! Tentativas restantes: %d", tentativas_maximas - tentativa - 1);
    }

    ui_msg_erro("Numero maximo de tentativas excedido. Operacao cancelada.");
    return 0;
}

Aluno *acessar_aluno_por_matricula(int matricula_desejada) {
    Aluno *temp = inicio;

    while (temp != NULL) {
        if (temp->matricula == matricula_desejada) {
            return temp;
        }
        temp = temp->proximo;
    }

    return NULL;
}

Aluno *acessar_aluno_por_matricula_arquivo(int matricula_desejada) {
    FILE *arquivo = fopen(ARQ_ALUNOS, "r");
    if (arquivo == NULL) {
        return NULL;
    }

    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));
    if (aluno == NULL) {
        fclose(arquivo);
        return NULL;
    }

    char copia_nome[100];

    while (fscanf(arquivo, "%d/%99[^/]/%d/%f/%f", &aluno->matricula, copia_nome, &aluno->idade, &aluno->peso, &aluno->altura) == 5) {
        if (aluno->matricula == matricula_desejada) {
            aluno->nome = duplicar_texto(copia_nome);
            if (aluno->nome == NULL) {
                fclose(arquivo);
                free(aluno);
                return NULL;
            }
            fclose(arquivo);
            return aluno;
        }
    }

    fclose(arquivo);
    free(aluno);
    return NULL;
}

void adicionar_aluno(char *nome, int idade, float peso, float altura) {
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

    FILE *arquivo = fopen(ARQ_ALUNOS, "r");
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
    if (novo_aluno == NULL) {
        ui_msg_erro("Erro de memoria ao cadastrar aluno.");
        return;
    }

    capitalizar(nome);
    novo_aluno->nome = duplicar_texto(nome);
    if (novo_aluno->nome == NULL) {
        free(novo_aluno);
        ui_msg_erro("Erro de memoria ao cadastrar aluno.");
        return;
    }

    novo_aluno->idade = idade;
    novo_aluno->peso = peso;
    novo_aluno->altura = altura;
    novo_aluno->matricula = proxima_matricula;
    novo_aluno->proximo = NULL;

    printf("Bem-vindo, seu cadastro foi concluido!\n");
    printf("Sua Matricula e: %d.\n\n", novo_aluno->matricula);

    if (inicio == NULL) {
        inicio = novo_aluno;
    } else {
        Aluno *atual = inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo_aluno;
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

    switch (opcao) {
        case 1:
            ler_entrada_texto("\nAtualize o novo nome: ", novo_nome, sizeof(novo_nome));
            capitalizar(novo_nome);
            {
                char *novo_nome_alocado = duplicar_texto(novo_nome);
                if (novo_nome_alocado == NULL) {
                    ui_msg_erro("Erro de memoria ao atualizar nome.");
                    return;
                }
                free(aluno->nome);
                aluno->nome = novo_nome_alocado;
            }
            ui_msg_sucesso("Nome atualizado com sucesso!");
            break;
        case 2:
            printf("\nAtualize a nova idade: ");
            scanf("%d", &aluno->idade);
            limpar_buffer();
            ui_msg_sucesso("Idade atualizada com sucesso!");
            break;
        case 3:
            printf("\nAtualize o novo peso: ");
            scanf("%f", &aluno->peso);
            limpar_buffer();
            ui_msg_sucesso("Peso atualizado com sucesso!");
            break;
        case 4:
            printf("\nAtualize a nova altura: ");
            scanf("%f", &aluno->altura);
            limpar_buffer();
            ui_msg_sucesso("Altura atualizada com sucesso!");
            break;
        case 0:
            return;
        default:
            ui_msg_erro("Opcao invalida!");
            return;
    }

    if (matricula_desejada == -1) {
        return;
    }

    FILE *arquivo = NULL;
    FILE *temp_arquivo = NULL;
    if (!abrir_arquivos_reescrita(ARQ_ALUNOS, "temp.txt", &arquivo, &temp_arquivo)) {
        return;
    }

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

    finalizar_reescrita_arquivo(arquivo, temp_arquivo, ARQ_ALUNOS, "temp.txt");
}

void cadastrar_aluno() {
    char nome[100];
    int idade;
    float peso, altura;
    int tentativas_maximas = 3;

    if (!ler_nome_valido(nome, sizeof(nome), tentativas_maximas, "\nDigite o nome do aluno: ")) {
        return;
    }

    if (!ler_int_positivo("\nDigite a idade do aluno: ", "Idade", tentativas_maximas, &idade)) {
        return;
    }

    if (!ler_float_positivo("\nDigite o peso do aluno (em kg): ", "Peso", tentativas_maximas, &peso)) {
        return;
    }

    if (!ler_float_positivo("\nDigite a altura do aluno (em metros): ", "Altura", tentativas_maximas, &altura)) {
        return;
    }

    printf("\n");
    adicionar_aluno(nome, idade, peso, altura);
}

void deletar_aluno_sistema(Aluno *aluno, int matricula_desejada) {
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
                ui_msg_sucesso("Aluno removido com sucesso!");
                return;
            }
        }
    }

    FILE *arquivo_entrada = NULL;
    FILE *arquivo_saida = NULL;
    if (!abrir_arquivos_reescrita(ARQ_ALUNOS, "arquivotemp.txt", &arquivo_entrada, &arquivo_saida)) {
        return;
    }

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
            } else {
                removido = 1;
            }
        }
    }

    finalizar_reescrita_arquivo(arquivo_entrada, arquivo_saida, ARQ_ALUNOS, "arquivotemp.txt");

    if (removido) {
        ui_msg_sucesso("Aluno removido com sucesso!");
    }
}

Aluno *criarAlunoNo(const char *nome, int idade, float peso, float altura, int matricula) {
    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));
    if (novoAluno == NULL) {
        printf("Erro ao alocar memória para o novo aluno.\n");
        exit(1);
    }

    novoAluno->nome = duplicar_texto(nome);
    novoAluno->idade = idade;
    novoAluno->peso = peso;
    novoAluno->altura = altura;
    novoAluno->matricula = matricula;
    novoAluno->proximo = NULL;

    return novoAluno;
}

void adicionarAlunoLista(Aluno **head, Aluno *novoAluno) {
    if (*head == NULL) {
        *head = novoAluno;
    } else {
        Aluno *temp = *head;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoAluno;
    }
}

void liberarLista(Aluno *head) {
    Aluno *temp;
    while (head != NULL) {
        temp = head;
        head = head->proximo;
        free(temp->nome);
        free(temp);
    }
}

void consultaNome(Aluno *head, char *string) {
    Aluno *temp = head;
    int algumAluno = 0;

    while (temp != NULL) {
        if (strstr(temp->nome, string) != NULL) {
            algumAluno = 1;
            printf("Nome: %s    Matricula: %d\n", temp->nome, temp->matricula);
        }
        temp = temp->proximo;
    }

    if (algumAluno == 0) {
        ui_msg_erro("Nao houve aluno com esse nome!");
    }

    printf("\n");
}

void pesquisaAluno() {
    char pesquisaNome[100];
    int tentativas_maximas = 3;
    int nome_valido = 0;

    for (int tentativa_nome = 0; tentativa_nome < tentativas_maximas; tentativa_nome++) {
        printf("\nDigite uma parte do nome do aluno que deseja consultar: ");
        fgets(pesquisaNome, sizeof(pesquisaNome), stdin);
        pesquisaNome[strcspn(pesquisaNome, "\r\n")] = '\0';
        capitalizar(pesquisaNome);

        nome_valido = 1;

        for (int i = 0; pesquisaNome[i] != '\0'; i++) {
            if (isdigit((unsigned char)pesquisaNome[i])) {
                nome_valido = 0;
                break;
            }
        }

        if (!nome_valido || verificar_string(pesquisaNome) == 0) {
            ui_msg_errof("Nome invalido! Tentativas restantes: %d", tentativas_maximas - tentativa_nome - 1);
            if (tentativa_nome == tentativas_maximas - 1) {
                ui_msg_erro("Numero maximo de tentativas excedido. Operacao cancelada.");
                return;
            }
        } else {
            printf("\n");
            break;
        }
    }

    if (contemLetra(pesquisaNome)) {
        Aluno *lista = NULL;
        Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));
        if (aluno == NULL) {
            ui_msg_erro("Erro de memoria ao consultar alunos.");
            return;
        }

        FILE *arquivo = fopen(ARQ_ALUNOS, "r");
        if (arquivo == NULL) {
            ui_msg_erro("Nao foi possivel abrir o cadastro de alunos.");
            free(aluno);
            return;
        }

        char copia_nome[100];

        while (fscanf(arquivo, "%d/%99[^/]/%d/%f/%f", &aluno->matricula, copia_nome, &aluno->idade, &aluno->peso, &aluno->altura) == 5) {
            Aluno *alunoTemp = criarAlunoNo(copia_nome, aluno->idade, aluno->peso, aluno->altura, aluno->matricula);
            adicionarAlunoLista(&lista, alunoTemp);
        }

        Aluno *temp = inicio;
        while (temp != NULL) {
            Aluno *alunoTemp = criarAlunoNo(temp->nome, temp->idade, temp->peso, temp->altura, temp->matricula);
            adicionarAlunoLista(&lista, alunoTemp);
            temp = temp->proximo;
        }

        consultaNome(lista, pesquisaNome);

        fclose(arquivo);
        liberarLista(lista);
        free(aluno);
    } else {
        ui_msg_erro("Entrada invalida para nome de aluno!");
    }
}

int mostrar_aluno(int matricula_desejada) {
    Aluno *aluno = acessar_aluno_por_matricula(matricula_desejada);

    if (aluno != NULL) {
        imprimir_aluno(aluno);
        mostrar_treino(matricula_desejada);
        return 1;
    }

    aluno = acessar_aluno_por_matricula_arquivo(matricula_desejada);
    if (aluno != NULL) {
        imprimir_aluno(aluno);
        mostrar_treino(matricula_desejada);
        liberar_aluno_heap(aluno);
        return 1;
    }

    ui_msg_erro("Aluno nao encontrado!");
    return 0;
}

void salvar_lista_em_arquivo(Aluno *lista_alunos) {
    FILE *arquivo = abrir_arquivo_append(ARQ_ALUNOS);
    if (arquivo == NULL) {
        return;
    }

    while (lista_alunos != NULL) {
        fprintf(arquivo, "%d/%s/%d/%.2f/%.2f\n", lista_alunos->matricula, lista_alunos->nome, lista_alunos->idade, lista_alunos->peso, lista_alunos->altura);
        lista_alunos = lista_alunos->proximo;
    }

    fclose(arquivo);
}

void verificar_local_cadastro(int matricula_desejada, int opcao) {
    Aluno *aluno = acessar_aluno_por_matricula(matricula_desejada);

    if (aluno == NULL) {
        aluno = acessar_aluno_por_matricula_arquivo(matricula_desejada);
        if (aluno == NULL) {
            ui_msg_erro("Aluno nao encontrado!");
            return;
        }

        if (opcao == 1) {
            atualizar_dados_aluno(aluno, matricula_desejada);
        } else {
            deletar_aluno_sistema(aluno, matricula_desejada);
        }

        liberar_aluno_heap(aluno);
        return;
    }

    if (opcao == 1) {
        atualizar_dados_aluno(aluno, -1);
    } else {
        deletar_aluno_sistema(aluno, -1);
    }
}

