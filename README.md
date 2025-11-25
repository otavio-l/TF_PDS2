# README - JOGO - GRUPO 4 TURMA TN

Trabalho final de PDS2/2025-2 da UFMG, **integrantes**: Cauã M., Hugo S., Murilo N. e Otavio L.

O projeto trata da elaboração de uma demo de jogo 2D com estilo 8-bit e visualização top-down.


## Objetivos
Produzir um jogo 2D com menu, pause, checkpoints, movimentação, colisão, gerenciamento 
de recursos, profundidade na renderização, cutscenes, mapas interativos e animação dos personagens
seguindo as boas práticas de programação.
> Inspirado em "Faith: The Unholy Trinity"

## Ferramentas
Esse projeto utiliza as seguintes linguagem, ferramentas e bibliotecas:
- Linguagem: C++11
- Compilação: Make
- Gerenciador de pacotes: Conan (versão: 2.20.1)
- Biblioteca: [SFML](https://github.com/SFML/SFML)(versão: 2.6.1), [JSON](https://github.com/nlohmann/json)(versão: 3.12.0)
- Documentação: Doxygen (versão: 1.14.0)
- Testes Unitários: Doctest
- Cobertura: gcovr

## Compilação
> Esteja no diretório root do projeto

> Primeira vez usando o conan execute `$ conan profile detect`

`$ conan install . --lockfile=conan.lock --output-folder=build --build=missing -c tools.system.package_manager:mode=install`

`$ make`

## Execução
`$ make run`

## Compilação de Testes
`$ make tests`

## Execução Testes
`$ make run_tests`

## Relatório de Cobertura
Para imprimir o relatório no terminal
`$ make coverage`

Para gerar o relatório em HTML 
`$ make html_coverage`

## Documentação
`$ doxygen Doxyfile`
> Arquivos gerados no diretório docs/

## Remover arquivos auxiliares
`$ make clean`
.
---

## Controles

#### Menu inicial

Teclas direcionais: troca botão selecionado

Enter: aciona o botão

#### Jogo

A: move para esquerda

S: move para baixo

D: move para a direita

W: move para cima

Esc: pausa

#### Pause

Enter: despausa