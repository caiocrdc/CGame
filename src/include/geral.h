#ifndef GERAL_H
#define GERAL_H

void limpar_buffer(void);
int selecionar_opcao(int quantidade, const char *opcoes[]);
int escolher_menu(int quantidade, ...);
void dar_item(int item);
void escolher_itens_iniciais(void);
void mostrar_inventario(void);

#endif
