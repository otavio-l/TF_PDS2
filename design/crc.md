## CARTÕES CRC

#### Classe: Entity

Responsabilidades:

- Posição
- Sprite
- Hitbox
- Colisão
- Gatilho

Colaborações:

- Game
- MapArea
- InputSystem
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

- Game
- InputSystem
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

- InputSystem
- ResourceManager
- Entity
- Game

---

#### Classe: InputSystem

Responsabilidades

- Movimento potencial do player
- Checagem de colisão
- Checagem de gatilho
- Carrega novo mapa
- Atualiza hitbox e sprite do player

Colaborações:

- PlayState
- Entity
- MapArea

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

