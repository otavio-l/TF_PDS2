## CARTÕES CRC

#### Classe: PlayerEntity

Responsabilidades:

- Posição relativa
- Posição absoluta
- Sprite
- Hitbox
- Movimentação
- Animação

Colaborações:

- MapArea
- PlayState

---

#### Classe:  mapArea

Responsabilidades:

- Parse json
- Extrai entidades
- Define posição inicial do player nos mapas

Colaborações:

- Entity
- PlayState


---

#### Classe: Game

Responsabilidades

- Fila de estados do jogo
- Muda o estado atual do jogo
- Janela de renderização
- Loop principal
- Define FPS

Colaborações:

- GameState
- PendingAction


---

#### Classe: PlayState

Responsabilidades

- Gerencia input contínuo
- Gerencia input discreto
- Inicializa as texturas
- Rendeniza entidades
- Player
- 

Colaborações:

- ResourceManager
- PlayerEntity
- Game

---

#### Classe: ResourceManager

Responsabilidades

- Carrega texturas
- Carrega áudios
- Carrega fontes
- Armazena mídia
- Retorna mídia por nome

Colaborações:

- MenuState
- PlayState
- PausedState

---

#### Classe: EnemyEntity

Responsabilidades

- Posição relativa
- Posição absoluta
- Sprite
- Hitbox
- Calcula se está no mapa atual
- Calcula movimento para seguir o player

Colaborações:

- PlayState
- Entity
- MapArea