## User Stories

1) Como jogador, quero movimentar meu personagem pelo mapa para explorar o cenário.

- O personagem deve se mover para cima, baixo esquerda e direta
- O movimento deve ser controlável via teclas de movimento
- O personagem não deve atravessar obstáculos
- O personagem deve ter uma animação de caminhada em cada direção

---

2) Como jogador, desejo dispor de uma interface com menus interativos para controlar o estado do jogo.

- O jogo deve conter um menu principal
- O jogo deve conter um menu de pausa
- O jogo deve exibir uma tela de “Game over” caso o jogador seja alcançado

---

3) Como desenvolvedor, quero carregar texturas e sons de maneira centralizada para evitar duplicação e melhorar a performance.

- Todas as texturas devem ser carregadas uma única vez
- Deve ser possível acessar qualquer textura pelo nome do arquivo
- Efeitos sonoros devem ser carregados e acessíveis da mesma forma
- Se o recurso não for encontrado, uma mensagem de erro deve ser exibida

---

4) Como usuário e desenvolvedor deve estar explícito como dar build no sistema

- Explicitar as versões das dependências
- Makefile contruído
- Uso de package manager