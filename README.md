# Sistema de Gerenciamento de Biblioteca Universitária

Aplicação de console desenvolvida em linguagem **C** para o gerenciamento do acervo bibliográfico, do cadastro de usuários e do controle de empréstimos de uma biblioteca universitária. O projeto adota uma arquitetura modular e utiliza arquivos de texto (`.txt`) no diretório `dados/` para garantir a persistência das informações entre diferentes execuções.

## Propósito do Projeto
- Registrar e consultar obras do acervo por meio de código identificador exclusivo, título, autor, ano de publicação e quantidade disponível.
- Cadastrar e consultar usuários identificados por número de matrícula exclusivo.
- Realizar, listar e encerrar empréstimos, atualizando automaticamente a disponibilidade dos exemplares.
- Assegurar o armazenamento persistente dos registros em arquivos de texto (`livros.txt`, `usuarios.txt` e `emprestimos.txt`).
- Estruturar o código-fonte de maneira coesa e de fácil manutenção.

## Funcionalidades Principais

### Gerenciamento de Livros
Permite o cadastro de novas obras no acervo respeitando o limite estabelecido e impedindo a duplicidade de códigos. Disponibiliza a listagem completa dos registros e a pesquisa por título ou autor a partir de correspondência parcial, sem distinção entre letras maiúsculas e minúsculas.

### Gerenciamento de Usuários
Possibilita o registro de novos usuários informando matrícula única, nome e curso, além da listagem geral e da consulta individual por meio da matrícula.

### Controle de Empréstimos
Gerencia o registro, a consulta e a devolução de empréstimos vinculando o código da obra à matrícula do usuário, com atualização automática do saldo de exemplares disponíveis.

## Validações e Tratamento de Erros
Para preservar a integridade dos dados e a estabilidade da execução, o sistema realiza as seguintes verificações:
- Rejeição de campos vazios ou compostos apenas por espaços em branco;
- Bloqueio de códigos de livros ou matrículas de usuários já cadastrados;
- Validação contra valores negativos para ano de publicação e quantidade, bem como tratamento de entradas não numéricas no menu com limpeza do buffer;
- Impedimento de operações inconsistentes, tais como referências a livros ou usuários inexistentes, indisponibilidade de exemplares, empréstimos ativos duplicados ou atingimento dos limites máximos de capacidade.

## Estrutura de Diretórios
- `include/`: arquivos de cabeçalho (`.h`) contendo as definições de estruturas (`struct`), constantes de limite e protótipos de funções compartilhadas entre os módulos.
- `src/`: arquivos de implementação (`.c`) responsáveis pelas regras de negócio, pela persistência em disco e pelo ponto de entrada (`main.c`) com o menu interativo.
- `dados/`: arquivos de texto (`.txt`) delimitados por ponto e vírgula (`;`), utilizados para leitura e gravação dos registros.

## Compilação e Execução

### Pré-requisitos
- Compilador **GCC** devidamente configurado no ambiente.
- Terminal posicionado no **diretório raiz** do projeto.

### Compilação
```bash
gcc -Wall -Wextra -Iinclude src/*.c -o biblioteca
