# CGame

## Compilacao

Na raiz do repositorio, compile as duas variantes com:

```sh
make
```

Os executaveis ficam em `bin/`. Para compilar apenas uma variante, use `make bin/RPGLIN` ou `make bin/RPGWIN`. No Windows, use MinGW-w64 ou outro compilador que defina `_WIN32` e ofereca `windows.h`.

Para remover os executaveis gerados:

```sh
make clean
```

Os headers compartilhados ficam em `src/include/`; suas implementacoes estao em `src/`.
