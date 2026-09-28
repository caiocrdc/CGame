# CGame

RPG de terminal escrito em C, com suporte a Windows e sistemas POSIX.

A interface limpa o terminal depois de cada escolha e apresenta os textos com
quebra automatica em 80 colunas, sem dividir palavras.

## Requisitos

O projeto utiliza GCC, AR e GNU Make.

### Linux

Em distribuições baseadas em Ubuntu ou Debian, instale as ferramentas com:

```sh
sudo apt update
sudo apt install build-essential
```

### Windows

Instale o MinGW-w64 com GCC, AR e `mingw32-make`. O diretório `bin` do MinGW
deve estar configurado na variável de ambiente `PATH`.

Confirme a instalação no PowerShell ou Prompt de Comando:

```powershell
gcc --version
ar --version
mingw32-make --version
```

## Compilação e execução

### Linux

Compile o projeto:

```sh
make
```

Execute pelo Makefile ou diretamente:

```sh
make run
./build/rpg
```

Remova os arquivos gerados:

```sh
make clean
```

### Windows

No PowerShell ou Prompt de Comando, compile com:

```powershell
mingw32-make
```

Execute pelo Makefile ou diretamente:

```powershell
mingw32-make run
.\build\rpg.exe
```

Remova os arquivos gerados:

```powershell
mingw32-make clean
```

Se a instalação disponibilizar o comando como `make` em vez de
`mingw32-make`, use `make`, `make run` e `make clean` normalmente.

## Arquivos gerados

- `build/librpg.a`: biblioteca estática do jogo;
- `build/rpg`: executável no Linux;
- `build/rpg.exe`: executável no Windows.

## Estrutura

- `include/rpg.h`: API publica da biblioteca;
- `src/main.c`: ponto de entrada do executavel;
- `src/rpg.c`: inicializacao e coordenacao do jogo;
- `src/platform.c`: entrada, saida e compatibilidade de plataforma;
- `src/game.c`: jogador, inventario e combate;
- `src/story.c`: rotas e narrativa;
- `src/rpg_internal.h`: tipos e contratos internos.
