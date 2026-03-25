#include "academia.h"
#include <stdarg.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

void configurar_terminal() {
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

static void ui_print_simples(const char *mensagem) {
    printf("%s\n", mensagem);
}

void ui_msg_info(const char *mensagem) {
    ui_print_simples(mensagem);
}

void ui_msg_sucesso(const char *mensagem) {
    ui_print_simples(mensagem);
}

void ui_msg_aviso(const char *mensagem) {
    ui_print_simples(mensagem);
}

void ui_msg_erro(const char *mensagem) {
    ui_print_simples(mensagem);
}

void ui_msg_errof(const char *formato, ...) {
    va_list args;
    va_start(args, formato);
    vprintf(formato, args);
    va_end(args);
    printf("\n");
}

void imprimir_boas_vindas() {
    printf("+---------------------------------------+\n");
    printf("|                                       |\n");
    printf("|               BEM-VINDO               |\n");
    printf("|          SISTEMA DE ACADEMIA          |\n");
    printf("|                                       |\n");
    printf("+---------------------------------------+\n\n");
}

void limpar_terminal() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

