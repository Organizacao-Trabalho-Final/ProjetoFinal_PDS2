# Trabalho_final_PDS2

## Integrantes do Grupo:
- Daniel Rodrigues de Oliveira
- Max Arthur Giancoli Jabour
- Nicolas Ferreira Costa Gomes
- Santiago Hagenmuller Justo

## Descrição do Problema:
Bibliotecas são lugares fundamentais para a sociedade e a cultura e, por isso, podem utilizar softwares para facilitar seu funcionamento. Nesse contexto, muitas informações precisam ser registradas para garantir a organização e a segurança do acervo da biblioteca.

## Descrição da Solução:
Um sistema de gerenciamento de biblioteca desenvolvido em C++11. O programa permite organizar o acervo, cadastrar usuários, controlar empréstimos e renovações e acompanhar a manutenção de obras danificadas.

## Objetivos Principais:
O objetivo é criar um sistema de gerenciamento de biblioteca que auxilie na organização de suas várias funções. Esse é um sistema útil não apenas para o bibliotecário, mas também para os usuários e administradores do local, pois facilita o gerenciamento de empréstimos, guarda informações dos usuários e das obras, além de verificar o estado das obras e encaminhá-las para manutenção, caso necessário.

## Por Que Escolhemos esse Tema:
O tema foi escolhido porque ele permite a criação de diversas classes que utilizam herança, composição e polimorfismo e que auxiliam na missão de garantir o bom funcionamento das bibliotecas. Como sistema de gerenciamento, a coesão entre as classes é delicada e requer refinamento contínuo durante o desenvolvimento.
Ademais, as bibliotecas são locais de incentivo à leitura e à cultura e têm funções fundamentais para a educação da população. Assim, um projeto que visa a melhoria desses lugares é importante para o grupo. A modernização das bibliotecas, instituições antigas e tradicionais na sociedade, contribui para que esses locais continuem abertos e funcionem com eficiência.

## Compilação
O projeto utiliza C++11 e pode ser compilado com:
```bash
make
```

## Execução
Após a compilação, execute:
```bash
./biblioteca
```

## Testes
Para compilar e executar todos os testes:
```bash
make test
```

## Documentação
Para gerar a documentação com Doxygen:
```bash
make docs
```

## Limpeza
Para remover os arquivos gerados durante a compilação:
```bash
make clean
```

## Funcionalidades

### Obras
- Cadastro de livros e artigos.
- Listagem e pesquisa por título, autor ou ID.
- Atualização dos dados específicos de cada tipo de obra.
- Remoção de obras que não estejam associadas a empréstimos ou manutenções.
- Consulta da disponibilidade, estado de dano e situação de manutenção.

### Usuários
- Cadastro de estudantes, professores, bibliotecários e técnicos de manutenção.
- Consulta por nome, CPF ou ID e listagem dos usuários cadastrados.
- Validação de CPF, matrícula e demais campos obrigatórios.
- Remoção por CPF, impedida quando há empréstimos ou manutenções associados.

### Empréstimos
- Empréstimo realizado por bibliotecário para estudantes e professores.
- Estudantes podem emprestar somente livros; professores podem emprestar livros e artigos.
- Prazo de 30 dias e limite de 3 empréstimos ativos para estudantes.
- Prazo de 45 dias e limite de 5 empréstimos ativos para professores.
- Consulta do histórico, situação e atraso dos empréstimos.
- Registro de devoluções e solicitação/aprovação de renovações.

### Manutenções
- Encaminhamento de obras danificadas para um técnico.
- Consulta das manutenções e da quantidade de pendências por técnico.
- Registro do início e da conclusão do reparo.
- A obra permanece indisponível durante a manutenção e volta a ficar disponível após a conclusão.

### Persistência
Os dados são carregados ao iniciar e salvos ao encerrar o programa nos arquivos `usuario.txt` e `obras.txt`, criados na pasta de execução. Na primeira execução, quando os dois arquivos ainda não existem, o sistema inicia com cadastros vazios.