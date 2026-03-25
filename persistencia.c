#include "academia.h"

FILE *abrir_arquivo_append(const char *caminho) {
    FILE *arquivo = fopen(caminho, "a+");
    if (arquivo == NULL) {
        ui_msg_errof("Erro ao abrir arquivo: %s", caminho);
    }
    return arquivo;
}

int abrir_arquivos_reescrita(const char *origem, const char *temporario, FILE **entrada, FILE **saida) {
    *entrada = fopen(origem, "r");
    if (*entrada == NULL) {
        ui_msg_errof("Erro ao abrir arquivo de origem: %s", origem);
        return 0;
    }

    *saida = fopen(temporario, "w");
    if (*saida == NULL) {
        fclose(*entrada);
        ui_msg_errof("Erro ao abrir arquivo temporario: %s", temporario);
        return 0;
    }

    return 1;
}

int finalizar_reescrita_arquivo(FILE *entrada, FILE *saida, const char *origem, const char *temporario) {
    fclose(entrada);
    fclose(saida);

    if (remove(origem) != 0) {
        ui_msg_errof("Erro ao remover arquivo antigo: %s", origem);
        return 0;
    }

    if (rename(temporario, origem) != 0) {
        ui_msg_errof("Erro ao renomear arquivo temporario: %s", temporario);
        return 0;
    }

    return 1;
}

