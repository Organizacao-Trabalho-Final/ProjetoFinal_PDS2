## User Stories

# 1 - “Como usuário da biblioteca, quero pesquisar obras no catálogo e identificar obras de meu interesse.”
- Pesquisar por autor
- Pesquisar por título
- Exibir as informações das obras encontradas
- Informar quando a pesquisa não tem resultados

# 2 - “Como bibliotecário, quero cadastrar e atualizar obras para manter o acervo da biblioteca organizado.”
- Cadastrar novas obras
- Impedir duplicatas
- Deletar obras cadastradas
- Atualizar informações de obras

# 3 - “Como estudante ou professor, quero realizar o empréstimo de uma obra para utilizá-la fora da biblioteca.”
- Verificar disponibilidade da obra
- Verificar se a obra pode ser emprestada para o usuário
- Registrar data de retirada
- Calcular e registrar data de devolução de acordo com o usuário

# 4 - “Como usuário, quero consultar meus empréstimos para acompanhar as obras que estão sob minha responsabilidade.”
- Consultar empréstimos ativos e a obra associada ao empréstimo
- Exibir datas de devolução e de retirada
- Informar atraso de devolução
- Pedir renovação da obra

# 5 - “Como bibliotecário, quero registrar a devolução de uma obra para atualizar sua situação no sistema.”
- Registrar devoluções
- Marcar empréstimo como inativo e obra como disponível (se for o caso)
- Verificar condições de atraso
- Verificar se a obra está danificada

# 6 - “Como administrador da biblioteca, quero que estudantes e professores tenham regras próprias de empréstimo para representar as diferentes categorias de usuários.”
- Definir período de empréstimo por subclasse de Pessoa
- Definir limite de empréstimos ativos por subclasse de Pessoa
- Verificar se a obra pode ser emprestada para o usuário
- Calcular e registrar data de devolução de acordo com o usuário

# 7 - “Como bibliotecário, quero encaminhar obras danificadas para manutenção para impedir que sejam emprestadas enquanto estiverem indisponíveis.”
- Verificar e registrar estado da obra
- Associar a manutenção à obra
- Marcar obra como indisponível
- Associar a manutenção a um técnico de manutenção

# 8 - “Como técnico de manutenção, quero consultar e concluir manutenções atribuídas a mim para registrar o estado das obras reparadas.”
- Consultar número de manutenções pendentes
- Identificar a obra associada a cada manutenção
- Marcar manunteção como concluída
- Modificar disponibilidade da obra
