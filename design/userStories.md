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
- O jogo deve exibir uma tela de “Game over” caso o jogador perca

---

3) Como desenvolvedor, quero carregar texturas e de maneira centralizada para evitar duplicação e melhorar a performance.

- Todas as texturas devem ser carregadas uma única vez
- Deve ser possível acessar qualquer textura pelo nome do arquivo
- Efeitos sonoros devem ser carregados e acessíveis da mesma forma
- Se o recurso não for encontrado, uma mensagem de erro deve ser exibida

---

4) Como usuário quero uma mapa interativo e variável
- O jogo deve conter mais de um mapa
- O mapa deve conter locais que são gatilhos para novas ações
- O mapa deve ser customizável sem precisar recompilar o programa

---

5) Como usuário quero um mecanismo de perseguição ao meu personagem
- O perseguidor deve continuar me seguindo ao trocar de mapa
- O perseguidor deve conter movimentação contínua como o jogador
- O perseguidor deve conter animação de movimentação

---

6) Como usuário e desenvolvedor deve estar explícito como dar build no sistema

- Explicitar as versões das dependências
- Makefile contruído
- Uso de package manager