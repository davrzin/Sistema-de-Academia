# Sistema de Academia

Projeto em C para cadastro e gerenciamento de alunos e treinos.

## Estrutura do projeto

- Academia.c: ponto de entrada (`main`).
- academia.h: contratos, tipos compartilhados e constantes.
- menu.c: fluxo de menu e orquestracao da aplicacao.
- aluno.c: regras de aluno (cadastro, busca, atualizacao, exclusao, persistencia).
- treino.c: regras de treino (cadastro, busca, atualizacao, exclusao, persistencia).
- utils.c: funcoes utilitarias reutilizaveis (validacao, entrada, formatacao e memoria).
- persistencia.c: helpers para abertura e reescrita segura de arquivos.
- ui.c: banner e recursos de interface de terminal.
- build.bat: build rapido no Windows.
- Makefile: build padrao por `make`.
- Academia_UML.puml: modelagem UML em PlantUML.

## Build

Compile todos os modulos:

```bash
gcc -Wall -Wextra -g Academia.c menu.c aluno.c treino.c utils.c persistencia.c ui.c -o Academia.exe
```

Ou use os atalhos:

```bash
build.bat
```

```bash
make
```

## Execucao

```bash
./Academia.exe
```

## Git e versionamento

O projeto usa um arquivo .gitignore para manter o repositorio limpo.

Arquivos ignorados automaticamente:

- Binarios de build (por exemplo: Academia.exe).
- Arquivos temporarios (por exemplo: temp.txt e arquivotemp.txt).
- Arquivos gerados em execucao e validacao (arquivo.txt, treino.txt e RESULTADOS_TESTES.txt).

Fluxo recomendado:

1. Compile e execute normalmente.
2. Versione apenas codigo-fonte, scripts e documentacao.
3. Use git status para confirmar que apenas arquivos relevantes serao commitados.

## Organizacao e manutencao

- Regras de negocio ficam em `aluno.c` e `treino.c`.
- Utilitarios ficam em `utils.c` para evitar repeticao.
- Persistencia de arquivos fica concentrada em `persistencia.c`.
- Interface de terminal fica isolada em `ui.c`.
- Mensagens de erro/aviso/sucesso usam API padronizada de UI para manter consistencia.
- Contratos de funcao e structs ficam centralizados em `academia.h`.
- O `menu.c` apenas coordena o fluxo, sem carregar regras de dominio.

## Padrões adotados

- Nomes e mensagens em portugues para facilitar a manutencao local.
- Validacoes de entrada com numero maximo de tentativas.
- Persistencia em arquivos texto (`arquivo.txt` e `treino.txt`) com formato delimitado por `/`.
- Funcoes de liberacao dedicadas para evitar vazamento de memoria.
