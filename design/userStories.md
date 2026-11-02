## User Stories

# 01 - “Como usuário da biblioteca, quero pesquisar obras no catálogo e identificar obras de meu interesse.”
### Critérios de validação:
- Pesquisar por autor.
- Pesquisar por título.
- Pesquisar por ID.
- Exibir as informações das obras encontradas.
- Informar quando a pesquisa não apresentar resultados.

# 02 - “Como bibliotecário, quero cadastrar e atualizar obras para manter o acervo da biblioteca organizado.”
### Critérios de validação:
- Cadastrar novas obras (livros e artigos).
- Impedir o cadastro de obras duplicadas.
- Remover obras cadastradas.
- Atualizar informações de obras.
- Impedir a remoção de obras que ainda estejam referenciadas por empréstimos ou manutenções.

# 03 - “Como estudante ou professor, quero realizar o empréstimo de uma obra para utilizá-la fora da biblioteca.”
### Critérios de validação:
- Verificar disponibilidade da obra.
- Verificar se a obra pode ser emprestada para o usuário.
- Registrar data de retirada.
- Calcular e registrar data de devolução de acordo com o usuário.
- Não permitir que estudantes emprestem artigos, apenas livros.
- Tornar a obra indisponível após a aprovação do empréstimo.

# 04 - “Como usuário da biblioteca, quero consultar meus empréstimos para acompanhar as obras que estão sob minha responsabilidade.”
### Critérios de validação:
- Consultar empréstimos ativos e a obra associada ao empréstimo.
- Exibir datas de devolução e de retirada.
- Informar a quantidade de dias de atraso de devolução.
- Identificar o estado de cada empréstimo.

# 05 - “Como bibliotecário, quero registrar a devolução de uma obra para atualizar sua situação no sistema.”
### Critérios de validação:
- Registrar devoluções.
- Marcar empréstimo como inativo e obra como disponível (se for o caso).
- Verificar condições de atraso.
- Verificar se a obra está danificada.

# 06 - “Como administrador da biblioteca, quero que estudantes e professores tenham regras próprias de empréstimo para representar as diferentes categorias de usuários.”
### Critérios de validação:
- Períodos de empréstimo distintos por subclasse de Pessoa.
- Limites máximos de empréstimos ativos distintos por subclasse de Pessoa.
- Verificar se a obra pode ser emprestada para o usuário.
- Garantir que apenas professores podem pegar artigos emprestados.
- Calcular e registrar data de devolução de acordo com o usuário.

# 07 - “Como bibliotecário, quero encaminhar obras danificadas para manutenção para impedir que sejam emprestadas enquanto estiverem indisponíveis.”
### Critérios de validação:
- Verificar e registrar o estado da obra.
- Associar a manutenção à obra e ao técnico responsável.
- Registrar a descrição do dano e a data de início.
- Manter a obra indisponível durante o processo de manutenção.

# 08 - “Como técnico de manutenção, quero consultar e concluir manutenções atribuídas a mim para registrar o estado das obras reparadas.”
### Critérios de validação:
- Consultar número de manutenções pendentes.
- Consultar as manutenções associadas ao técnico.
- Identificar a obra associada a cada manutenção.
- Registrar a descrição do reparo realizado.
- Iniciar e concluir manutenções;
- Marcar a obra reparada como não danificada e disponível após a conclusão.

# 09 - “Como estudante ou professor, quero solicitar a renovação de um empréstimo para ter mais tempo de utilização da obra.”
### Critérios de validação:
- Permitir a solicitação de renovação de empréstimos ativos.
- Permitir que o bibliotecário avalie a solicitação.
- Impedir a renovação de empréstimos inativos.
- Impedir a renovação de empréstimos em atraso.
- Atualizar a data prevista de devolução quando a renovação for aprovada, respeitando o prazo correspondente ao usuário.

# 10 - “Como bibliotecário, quero cadastrar, consultar e remover usuários para manter o registro de pessoas autorizadas a utilizar a biblioteca.”
### Critérios de validação:
- Permitir o cadastro de estudantes, professores, bibliotecários e técnicos de manutenção.
- Validar os dados informados durante o cadastro.
- Impedir o cadastro de usuários com CPF ou ID já registrados.
- Permitir a consulta de usuários por nome, CPF ou ID.
- Identificar a categoria de cada usuário.
- Impedir a remoção de usuários que ainda estejam associados a empréstimos ou manutenções.

# 11 - “Como responsável pela biblioteca, quero que os dados do sistema sejam armazenados para preservar as informações cadastradas entre diferentes execuções do programa.”
### Critérios de validação:
- Carregar os dados previamente armazenados ao iniciar o sistema.
- Salvar os dados atualizados ao encerrar o sistema.
- Preservar os registros de usuários, obras, empréstimos e manutenções.
- Informar quando ocorrerem problemas durante o carregamento ou salvamento dos dados.