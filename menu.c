#include "academia.h"

Aluno *inicio = NULL;
gMuscular *iniciog = NULL;

void menu() {
    int opcao;

    do {
        printf("Escolha uma opcao:\n");
        printf("1 - Cadastrar aluno.\n");
        printf("2 - Acessar aluno por matricula.\n");
        printf("3 - Consultar aluno por nome.\n");
        printf("0 - Sair.\n\n");

        if ((scanf("%d", &opcao) == 1) && (opcao == 1 || opcao == 2 || opcao == 3 || opcao == 0)) {
            limpar_buffer();
            if (opcao == 1) {
                cadastrar_aluno();
            } else if (opcao == 2) {
                int matricula_desejada;
                printf("\nDigite a matricula desejada: ");
                if (scanf("%d", &matricula_desejada) != 1 || matricula_desejada <= 0) {
                    ui_msg_erro("Matricula invalida!");
                    limpar_buffer();
                    continue;
                }
                limpar_buffer();
                int opcao1;

                do {
                    int validacao = mostrar_aluno(matricula_desejada);
                    if (validacao == 1) {
                        printf("Escolha uma opcao:\n");
                        printf("1 - Atualizar dados do aluno\n");
                        printf("2 - Deletar aluno do sistema\n");
                        printf("3 - Cadastrar treino\n");
                        printf("4 - Atualizar treino\n");
                        printf("0 - Voltar\n\n");

                        if ((scanf("%d", &opcao1) == 1) && (opcao1 == 1 || opcao1 == 2 || opcao1 == 3 || opcao1 == 4 || opcao1 == 0)) {
                            limpar_buffer();
                            if (opcao1 == 1) {
                                verificar_local_cadastro(matricula_desejada, opcao1);
                            } else if (opcao1 == 2) {
                                verificar_local_cadastro(matricula_desejada, opcao1);
                                verificar_local_cadastro_treino(matricula_desejada, opcao1);
                                break;
                            } else if (opcao1 == 3) {
                                cadastrar_treino_aluno(matricula_desejada);
                            } else if (opcao1 == 4) {
                                verificar_local_cadastro_treino(matricula_desejada, 1);
                            } else {
                                ui_msg_info("Voltando...");
                            }
                        } else {
                            ui_msg_erro("Opcao invalida!");
                            break;
                        }
                    } else {
                        break;
                    }
                } while (opcao1 != 0);
            } else if (opcao == 3) {
                pesquisaAluno();
            } else {
                ui_msg_info("Saindo...");
            }
        } else {
            limpar_buffer();
            ui_msg_erro("Opcao invalida!");
            break;
        }

    } while (opcao != 0);

    if (inicio != NULL) {
        salvar_lista_em_arquivo(inicio);
    }

    if (iniciog != NULL) {
        salvar_treino_em_arquivo(iniciog);
    }
}



