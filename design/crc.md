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
- Cria entidades
- Mantém vetor de entidades
- Carrega background
- Define posição inicial do player nos mapas

Colaborações:

- Entity
- PlayState


---

#### Classe: Game

Responsabilidades

- Stack de estados do jogo
- Muda o estado atual do jogo
- Janela de rendenização
- Loop principal
- Define FPS

Colaborações:

- MenuState
- PlayState
- PausedState

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

- Texturas
- Audios
- Fontes
- Load da mídia
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