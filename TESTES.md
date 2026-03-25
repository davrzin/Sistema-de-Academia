# Plano de Testes - Sistema de Academia

## Objetivo

Validar fluxos principais, validacoes de entrada, persistencia em arquivo e integridade das operacoes de atualizacao/exclusao.

## Pre-condicoes

- Build concluido com sucesso.
- Arquivos de dados ausentes ou vazios para cenario inicial limpo.

## Casos de teste

1. CT-01 - Cadastro de aluno valido
- Entrada: nome valido, idade > 0, peso > 0, altura > 0.
- Esperado: aluno cadastrado, matricula exibida, registro em memoria.

2. CT-02 - Cadastro de aluno com nome invalido
- Entrada: nome vazio/numero/caractere invalido em todas as tentativas.
- Esperado: operacao cancelada apos limite de tentativas.

3. CT-03 - Cadastro de aluno com idade/peso/altura invalidos
- Entrada: valores invalidos repetidos.
- Esperado: mensagem de erro por tentativa e cancelamento ao exceder limite.

4. CT-04 - Consulta por matricula existente
- Entrada: matricula cadastrada.
- Esperado: dados de aluno exibidos e treino (se existir).

5. CT-05 - Consulta por matricula inexistente
- Entrada: matricula sem cadastro.
- Esperado: mensagem de aluno nao encontrado.

6. CT-06 - Cadastro de treino valido
- Entrada: matricula existente sem treino + 7 descricoes de treino.
- Esperado: treino cadastrado com sucesso.

7. CT-07 - Cadastro de treino duplicado
- Entrada: matricula com treino ja cadastrado.
- Esperado: aviso de treino ja cadastrado.

8. CT-08 - Atualizacao de dados do aluno
- Entrada: atualizar nome/idade/peso/altura.
- Esperado: campo alterado e persistencia refletida no arquivo quando aplicavel.

9. CT-09 - Atualizacao de treino
- Entrada: escolher grupo muscular e novo valor.
- Esperado: campo alterado e persistencia refletida no arquivo quando aplicavel.

10. CT-10 - Exclusao de aluno
- Entrada: deletar aluno por matricula.
- Esperado: aluno removido da memoria/arquivo conforme origem do dado.

11. CT-11 - Exclusao de treino
- Entrada: deletar treino por matricula.
- Esperado: treino removido da memoria/arquivo conforme origem do dado.

12. CT-12 - Consulta por nome
- Entrada: substring de nome existente e inexistente.
- Esperado: lista de alunos correspondentes ou mensagem de ausencia.

## Evidencias recomendadas

- Captura de tela do terminal para cada caso principal.
- Trecho de arquivo de dados antes/depois para casos de atualizacao/exclusao.
- Registro de build com status de sucesso.

## Critérios de aceite

- Nenhum travamento em entradas invalidas.
- Mensagens padronizadas de erro/sucesso.
- Dados consistentes entre memoria e arquivo.
- Fluxo completo executavel do menu sem comportamento inesperado.
