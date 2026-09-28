/*
 * ============================================================
 *  Universidade Federal do Ceara - Campus de Russas
 *  Disciplina: Laboratorio de Programacao
 *  Projeto 1 em C - Jogo de Aventura em Texto (RPG Interativo)
 * ============================================================
 *
 *  Requisitos do projeto atendidos:
 *   - if / else if / else  -> decisoes da historia e finais
 *   - switch               -> menus, itens e acoes de combate
 *   - int e char[]         -> vida, pontuacao, itens e nome do jogador
 *   - printf / scanf       -> entrada e saida de dados
 *   - Funcoes              -> organizacao do codigo (opcional)
 *
 *  Desafios obrigatorios:
 *   1) Varios finais diferentes conforme as escolhas
 *   2) Sistema de vida: o jogo termina se o HP chegar a 0
 *   3) Sistema de itens: os itens coletados alteram o final
 *   + Sistema de pontuacao (tesouros e inimigos derrotados)
 *
 *  Compilar:  gcc rpg_texto.c -o rpg_texto
 *  Executar:  ./rpg_texto
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef DELAY_LETRA
#define DELAY_LETRA 3500 // microssegundos entre cada letra (efeito de digitacao)
#endif

// ===================== VARIAVEIS GLOBAIS =====================

// Itens do inventario (0 = nao tem, 1 = tem)
int lanterna = 0;
int colar_forca = 0;   // Colar de rubi: +3 de dano
int colar_hp = 0;      // Colar de esmeralda: +20 de HP maximo
int chave_simples = 0;
int facao = 0;
int pistola = 0;
int anel = 0;          // Anel ensanguentado (altera o final)
int cetro = 0;         // Cetro de pedra valiosa
int ataduras = 0;      // Quantidade de ataduras
int municao = 0;       // Quantidade de municao da pistola

// Status do jogador
int sangramento = 0;   // 1 = sangrando (perde 5 de HP por turno em combate)
int combate = 0;       // 1 = ja lutou (ou neutralizou) um cultista
int vitoria = 1;       // Resultado do ultimo combate: 1 = vitoria, 0 = derrota
int hp_maximo = 40;    // Vida maxima (sobe para 60 com o colar de esmeralda)
int hp_jogador = 40;   // Vida atual do explorador
int pontuacao = 0;     // Pontuacao final do jogador
char nome_jogador[50]; // Nome do personagem

// ===================== FUNCOES AUXILIARES =====================

// Muda a cor do texto no terminal usando codigos ANSI padrao
void mudar_cor(int cor) {
    switch (cor) {
        case 15: printf("\033[0m"); break;  // Branco (Reset)
        case 14: printf("\033[33m"); break; // Amarelo (Historia)
        case 12: printf("\033[31m"); break; // Vermelho (Boss / Dano)
    }
    fflush(stdout);
}

// Imprime o texto letra por letra (efeito de digitacao)
void imprimir(const char *str) {
    size_t tamanho = strlen(str);
    for (size_t i = 0; i < tamanho; i++) {
        putchar(str[i]);
        fflush(stdout);
        usleep(DELAY_LETRA);
    }
}

// Descarta o que sobrou na linha digitada
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Le um inteiro com seguranca. Retorna -1 se o jogador digitar algo que nao seja numero
int ler_int(void) {
    int valor;
    if (scanf("%d", &valor) != 1) {
        if (feof(stdin)) {
            printf("\nEntrada encerrada. Fim de jogo.\n");
            exit(0);
        }
        limpar_buffer();
        return -1;
    }
    limpar_buffer();
    return valor;
}

// Le uma opcao de menu e so aceita valores entre minimo e maximo
int ler_opcao(int minimo, int maximo) {
    int opcao;
    while (1) {
        opcao = ler_int();
        if (opcao >= minimo && opcao <= maximo) {
            return opcao;
        }
        printf("Opcao invalida! Digite um numero entre %d e %d: ", minimo, maximo);
    }
}

// ===================== ITENS E INVENTARIO =====================

// Mostra a descricao de um dos 4 itens iniciais
void texto_item(int item) {
    switch (item) {
        case 1: imprimir("1 - Facao --> 6 de dano\n"); break;
        case 2: imprimir("2 - Pistola com 6 municoes --> 10 de dano por municao\n"); break;
        case 3: imprimir("3 - Lanterna --> ilumina lugares escuros\n"); break;
        case 4: imprimir("4 - 2 Ataduras --> curam 15 de vida e param sangramento\n"); break;
    }
}

// Entrega ao jogador o item escolhido
void dar_item(int item) {
    switch (item) {
        case 1:
            facao = 1;
            break;
        case 2:
            pistola = 1;
            municao = 6;
            break;
        case 3:
            lanterna = 1;
            break;
        case 4:
            ataduras = 2;
            break;
    }
}

// O jogador escolhe 2 dos 4 itens iniciais
void escolher_itens_iniciais(void) {
    int primeiro, segundo;

    for (int i = 1; i <= 4; i++) {
        texto_item(i);
    }
    primeiro = ler_opcao(1, 4);
    dar_item(primeiro);

    imprimir("\nAgora escolha o seu segundo item:\n");
    for (int i = 1; i <= 4; i++) {
        if (i != primeiro) {
            texto_item(i);
        }
    }
    do {
        segundo = ler_opcao(1, 4);
        if (segundo == primeiro) {
            printf("Voce ja escolheu esse item! Escolha outro: ");
        }
    } while (segundo == primeiro);
    dar_item(segundo);
}

void mostrar_inventario(void) {
    char buffer[100];

    imprimir("\nInventario:\n");
    if (facao == 1) imprimir("Facao --> 6 de dano\n");
    if (pistola == 1) {
        sprintf(buffer, "Pistola --> 10 de dano por municao (Municao: %d)\n", municao);
        imprimir(buffer);
    }
    if (lanterna == 1) imprimir("Lanterna --> ilumina lugares escuros\n");
    if (ataduras > 0) {
        sprintf(buffer, "%d Ataduras --> curam 15 de vida e param sangramento\n", ataduras);
        imprimir(buffer);
    }
    if (colar_forca == 1) imprimir("Colar de Rubi --> +3 de dano\n");
    if (colar_hp == 1) imprimir("Colar de Esmeralda --> +20 de HP maximo\n");
    if (anel == 1) imprimir("Anel ensanguentado com um pequeno diamante\n");
    if (cetro == 1) imprimir("Cetro de pedra valiosa\n");
    if (chave_simples == 1) imprimir("Chave Simples\n");
}

// ===================== SISTEMA DE COMBATE =====================

// Retorna 1 se o jogador venceu e 0 se morreu
int func_combate(const char *nome_inimigo, int hp_inimigo, int dano_inimigo) {
    int hp_inicial_inimigo = hp_inimigo;
    int bonus_dano = (colar_forca == 1) ? 3 : 0; // Colar de forca aumenta o dano

    mudar_cor(15);
    imprimir("\n==================================\n");
    imprimir("        COMBATE INICIADO!         \n");
    printf("Inimigo: ");
    mudar_cor(12);
    printf("%s", nome_inimigo);
    mudar_cor(15);
    printf(" | HP: %d | Dano: %d\n", hp_inimigo, dano_inimigo);
    imprimir("==================================\n");

    // Loop de combate (enquanto os dois estiverem vivos)
    while (hp_jogador > 0 && hp_inimigo > 0) {

        // Efeito de sangramento
        if (sangramento == 1) {
            mudar_cor(12);
            imprimir("\n[STATUS] Voce esta sangrando! Perdeu 5 de HP.\n");
            mudar_cor(15);
            hp_jogador -= 5;
            if (hp_jogador <= 0) break; // Morreu de sangramento
        }

        printf("\nSeu HP: %d/%d | HP Inimigo: %d\n", hp_jogador, hp_maximo, hp_inimigo);
        printf("Sua vez, %s. Escolha uma acao:\n", nome_jogador);
        imprimir("1 - Atacar\n");
        printf("2 - Usar Atadura (Cura 15 HP e para o sangramento) [%d restantes]\n", ataduras);
        int acao = ler_int();

        // --- TURNO DO JOGADOR ---
        switch (acao) {
            case 1: { // ATACAR
                int dano_causado = 2 + bonus_dano; // Soco (dano base 2)
                int arma;

                imprimir("Com qual arma?\n");
                printf("1 - Soco (Dano: %d)\n", 2 + bonus_dano);
                if (facao == 1) printf("2 - Facao (Dano: %d)\n", 6 + bonus_dano);
                if (pistola == 1) printf("3 - Pistola (Dano: %d | Municao: %d)\n", 10 + bonus_dano, municao);
                arma = ler_int();

                switch (arma) {
                    case 2:
                        if (facao == 1) {
                            dano_causado = 6 + bonus_dano;
                        }
                        break;
                    case 3:
                        if (pistola == 1) {
                            if (municao > 0) {
                                dano_causado = 10 + bonus_dano;
                                municao--;
                            } else {
                                imprimir("A arma apenas faz um barulho de *click*. Sem municao! Voce deu um soco de desespero.\n");
                            }
                        }
                        break;
                    default: // Soco
                        break;
                }

                printf("\n> Voce atacou causando %d de dano!\n", dano_causado);
                hp_inimigo -= dano_causado;
                break;
            }

            case 2: // CURAR
                if (ataduras > 0) {
                    imprimir("\n> Voce rapidamente enfaixou seus machucados! (+15 HP)\n");
                    ataduras--;
                    hp_jogador += 15;
                    sangramento = 0; // Para de sangrar
                    if (hp_jogador > hp_maximo) hp_jogador = hp_maximo; // Nao passa do HP maximo
                } else {
                    imprimir("\n> Voce procura na bolsa, mas nao tem ataduras! Voce perdeu seu turno...\n");
                }
                break;

            default:
                imprimir("\n> Opcao invalida! Na confusao da batalha, voce tropecou e perdeu o turno.\n");
        }

        // --- TURNO DO INIMIGO ---
        if (hp_inimigo > 0) {
            printf("> O ");
            mudar_cor(12);
            printf("%s", nome_inimigo);
            mudar_cor(15);
            printf(" te ataca, causando %d de dano!\n", dano_inimigo);
            hp_jogador -= dano_inimigo;
        }
    }

    // --- RESULTADO DO COMBATE ---
    if (hp_jogador <= 0) {
        hp_jogador = 0;
        mudar_cor(14);
        imprimir("\nSua visao escurece e voce cai no chao...\n");
        mudar_cor(15);
        return 0; // Derrota
    }

    printf("\nO ");
    mudar_cor(12);
    printf("%s", nome_inimigo);
    mudar_cor(15);
    printf(" cai sem vida! Voce sobreviveu.\n");
    
    pontuacao += hp_inicial_inimigo * 2; // Inimigos mais fortes valem mais pontos
    return 1; // Vitoria
}

// Combate padrao contra um cultista. Retorna 1 se sobreviveu e 0 se morreu (final ruim)
int luta_cultista(void) {
    vitoria = func_combate("Cultista Encapuzado", 15, 6);

    if (vitoria == 0) {
        mudar_cor(12);
        imprimir("\n=====FINAL RUIM=====\n");
        imprimir("A figura encapuzada ganha de voce e o usa como sacrificio para o Deus maligno que ela cultua.\n");
        mudar_cor(15);
        return 0;
    }

    mudar_cor(14);
    imprimir("Analisando o corpo da figura para ver o que ela carregava, ela nao possuia nada de valioso, mas uma chave chama sua atencao; ela provavelmente deve abrir algo importante.\n");
    mudar_cor(15);
    chave_simples = 1;
    combate = 1;
    return 1;
}

// ===================== FINAIS =====================

// Final bom: muda de acordo com os itens que o jogador coletou
void final_bom(void) {
    pontuacao += 500; // Diamante gigante
    mudar_cor(14);
    
    if (colar_forca == 1 && colar_hp == 1) {
        imprimir("\n=====FINAL LENDARIO=====\n");
        imprimir("Apos a luta, os dois colares que voce carrega comecam a brilhar em sintonia: o rubi da forca e a esmeralda da protecao. Uma energia antiga percorre o seu corpo e as vozes do templo se calam para sempre.\n");
        imprimir("Voce sai do templo com o diamante gigante, volta para o seu barquinho e foge daquela ilha. Alem de quitar toda a sua divida, voce vende os colares por uma fortuna e se torna uma lenda entre os exploradores!\n");
    } else if (anel == 1) {
        imprimir("\n=====FINAL BOM (ANEL AMALDICOADO)=====\n");
        imprimir("Apos a luta, voce sai correndo para fora daquele templo com o diamante gigante, volta para o seu barquinho e foge daquela ilha.\n");
        imprimir("Voce consegue pagar toda a sua divida e viver uma vida de luxo... mas o anel ensanguentado nunca mais sai do seu dedo. Toda noite voce escuta sussurros em uma lingua estranha, e sabe que um dia o Deus que voce ofendeu vira cobrar o que e dele...\n");
    } else {
        imprimir("\n=====FINAL BOM=====\n");
        imprimir("Apos a luta, voce sai correndo para fora daquele templo sabendo que o que ja havia encontrado era muito mais do que o suficiente para pagar sua divida! Assim, voce volta para o seu barquinho e foge daquela ilha.\n");
        imprimir("Voce consegue pagar toda a sua divida e viver uma vida de luxo pelos proximos anos sem se preocupar em trabalhar de novo!\n");
    }
    mudar_cor(15);
}

// Final neutro: depende de quantos tesouros o jogador juntou antes de fugir
void final_neutro(void) {
    mudar_cor(14);
    if (pontuacao >= 700) {
        imprimir("\n=====FINAL AGRIDOCE=====\n");
        imprimir("Voce sai correndo para fora daquele templo macabro, volta para o seu barquinho e foge daquela ilha.\n");
        imprimir("Felizmente, os tesouros que voce coletou pelo caminho foram suficientes para quitar toda a sua divida! Mesmo assim, voce nunca deixa de pensar no diamante gigante que deixou para tras...\n");
    } else {
        imprimir("\n=====FINAL NEUTRO=====\n");
        imprimir("Voce sai correndo para fora daquele templo esperando que o que ja havia encontrado fosse milagrosamente o suficiente para pagar sua divida... Voce volta para o seu barquinho e foge daquela ilha.\n");
        imprimir("Com isso, voce consegue pagar parte de sua divida, mas ainda tera que trabalhar o resto de sua vida para se tornar livre dela... Felizmente, pagar parte do valor fez o seu cobrador nao tomar uma medida mais radical contra voce...\n");
    }
    mudar_cor(15);
}

// Tela de resumo exibida ao terminar o jogo (qualquer final)
void tela_final(void) {
    mudar_cor(15);
    imprimir("\n==================================\n");
    imprimir("           FIM DE JOGO            \n");
    imprimir("==================================\n");
    printf("Explorador(a): %s\n", nome_jogador);
    printf("HP final: %d/%d\n", hp_jogador, hp_maximo);
    printf("Pontuacao: %d\n", pontuacao);

    if (pontuacao >= 1000) {
        imprimir("Ranking: Lenda das Ilhas\n");
    } else if (pontuacao >= 600) {
        imprimir("Ranking: Explorador Veterano\n");
    } else if (pontuacao >= 300) {
        imprimir("Ranking: Aventureiro\n");
    } else {
        imprimir("Ranking: Novato\n");
    }

    mostrar_inventario();
}

// ===================== CENAS DA HISTORIA =====================

// Escolha entre as duas trilhas. Retorna 1 (direita) ou 2 (esquerda)
int escolher_caminho(void) {
    int escolha;
    int tentativas = 0;

    mudar_cor(14);
    imprimir("\nUtilizando aquele pequeno barco barato que voce havia comprado, voce consegue chegar a ilha. Voce caminha ate encontrar uma bifurcacao na estrada. Ambos os caminhos parecem que vao te levar ao mesmo lugar. Qual caminho voce ira escolher?\n");
    mudar_cor(15);
    imprimir("1 - Direita\n");
    imprimir("2 - Esquerda\n");
    escolha = ler_opcao(1, 2);

    // O caminho da esquerda so leva ao destino na terceira tentativa
    while (escolha == 2 && tentativas < 2) {
        mudar_cor(14);
        if (tentativas == 0) {
            imprimir("Apos seguir pelo caminho do lado esquerdo por um tempo, voce percebe que retornou para a mesma bifurcacao pela qual ja havia passado.\n");
        } else {
            imprimir("Apos seguir pelo caminho do lado esquerdo por mais tempo ainda, voce percebe que retornou novamente para a mesma bifurcacao pela qual ja havia passado.\n");
        }
        mudar_cor(15);
        imprimir("1 - Ir para a Direita\n");
        imprimir("2 - Continuar indo para a Esquerda\n");
        escolha = ler_opcao(1, 2);
        tentativas++;
    }
    return escolha;
}

// Grande salao com o altar (igual nos dois caminhos). Retorna 1 se o jogador continua vivo
int salao_do_altar(const char *intro) {
    int escolha;
    int opcao_max = 1;
    char buffer[100];

    mudar_cor(14);
    imprimir(intro);
    imprimir("o local nao estava muito escuro, uma vez que a luz da lua o iluminava. Com isso, era possivel ver algo similar ao interior de uma igreja com diversos assentos e um altar. Entretanto, havia cabecas humanoides com barbas em formato de tentaculos esculpidas nos pilares do lugar.\n");
    mudar_cor(15);
    imprimir("1 - Procurar algo no altar\n");
    imprimir("2 - Procurar nos cantos da sala\n");
    escolha = ler_opcao(1, 2);

    if (escolha == 2) {
        mudar_cor(14);
        imprimir("Procurando algo de valor que pudesse ter passado despercebido nos cantos da sala, voce encontra uma passagem bloqueada por diversas raizes.\n");
        if (facao == 1) {
            imprimir("\nFelizmente, voce possui um facao e pode cortar essas raizes.\n");
            imprimir("Apos passar pelas raizes cortadas, voce encontra uma salinha com algumas pedras preciosas dentro. Depois de guardar essas pedras na sua bolsa, voce decide voltar e procurar algo no altar.\n");
            pontuacao += 150;
        } else {
            imprimir("Infelizmente, voce nao possui uma ferramenta que possa cortar silenciosamente essas raizes. Com isso, o melhor e voltar e procurar alguma coisa no altar.\n");
        }
    }

    mudar_cor(14);
    imprimir("\nProcurando algo de valor no altar, voce encontra um cetro com a ponta em um formato que simboliza a criatura esculpida nos pilares deste lugar. Voce decide pega-lo, dado que parecia ser feito de alguma pedra valiosa. Alem disso, voce tambem encontra uma caixa trancada com um cadeado e uma chave verde em cima.\n");
    cetro = 1;
    pontuacao += 200;

    // Menu dinamico: so aparecem as opcoes que o jogador consegue usar
    mudar_cor(15);
    imprimir("1 - Sair da sala com as coisas que voce encontrou e testar a chave na porta com diversos ornamentos.\n");
    if (facao == 1) {
        opcao_max++;
        sprintf(buffer, "%d - Tentar abrir a caixa usando o facao.\n", opcao_max);
        imprimir(buffer);
    }
    if (chave_simples == 1) {
        opcao_max++;
        sprintf(buffer, "%d - Utilizar a Chave Simples.\n", opcao_max);
        imprimir(buffer);
    }
    escolha = ler_opcao(1, opcao_max);

    if (escolha != 1) { // abriu a caixa
        mudar_cor(14);
        imprimir("Dentro da caixa havia um colar com um pingente de uma pedra que parece uma esmeralda. Isso deve valer um bom dinheiro e, por algum motivo, tambem faz voce se sentir protegido.\n");
        colar_hp = 1;
        hp_maximo = 60;
        hp_jogador += 20;
        pontuacao += 100;
    }

    // Se o jogador ainda nao enfrentou ninguem, e emboscado ao sair
    if (combate == 0) {
        mudar_cor(14);
        imprimir("Ao sair do local, voce e descuidado e acaba sendo emboscado por uma ");
        mudar_cor(12);
        imprimir("figura encapuzada");
        mudar_cor(14);
        imprimir(" e inicia um COMBATE.\n");
        mudar_cor(15);
        if (luta_cultista() == 0) {
            return 0;
        }
    }
    return 1;
}

// Porta ornamental do caminho da esquerda (Monstro de Tentaculos)
void porta_esquerda(void) {
    int escolha;

    mudar_cor(14);
    imprimir("\nSaindo do salao e indo para a porta ornamental que estava trancada, voce decide utilizar a chave verde que encontrou no altar. Ao abrir a porta e entrar, voce se depara com uma sala que possui um pequeno altar com diversas velas e um diamante grande o suficiente para pagar sua divida. Entretanto, voce escuta um barulho de algo se mexendo nas paredes desta sala. Para sua surpresa, nao era nada que voce ja tivesse visto antes, mas sim um ");
    mudar_cor(12);
    imprimir("tentaculo");
    mudar_cor(14);
    imprimir(" maior que um homem... Por mais assustador que seja, para poder quitar sua divida, aquele diamante gigante certamente sera necessario...\n");
    mudar_cor(15);
    
    imprimir("1 - Entrar na sala\n");
    imprimir("2 - Fugir deste templo macabro\n");
    escolha = ler_opcao(1, 2);

    switch (escolha) {
        case 1:
            mudar_cor(14);
            imprimir("Voce junta toda sua coragem e entra na sala determinado a enfrentar esse monstro para conseguir cumprir seu objetivo principal de ser livre de sua divida.\n");
            mudar_cor(15);
            vitoria = func_combate("Monstro de Tentaculos", 35, 12);
            if (vitoria == 0) {
                mudar_cor(12);
                imprimir("\n=====FINAL RUIM=====\n");
                imprimir("O tentaculo pega seu cadaver, joga para fora da sala e fecha a porta, esperando a sua proxima vitima.\n");
                mudar_cor(15);
            } else {
                final_bom();
            }
            break;
        case 2:
            final_neutro();
            break;
    }
}

// Porta ornamental do caminho da direita (Aberracao Ancia)
void porta_direita(void) {
    char texto_boss[500];

    mudar_cor(14);
    imprimir("\nSaindo deste salao, voce volta para aquela porta ornamental e decide tentar abri-la com sua nova chave. Para sua surpresa, ela realmente abre e voce entra em uma sala que possui um pequeno altar com diversas velas e um diamante grande o suficiente para pagar sua divida. Entretanto, tambem havia uma ");
    mudar_cor(12);
    imprimir("figura encapuzada");
    mudar_cor(14);
    imprimir(" ajoelhada na frente do altar.\n");
    mudar_cor(15);
    
    imprimir("1 - Ataca----!??... opcao do jogador interrompida-\n");

    mudar_cor(14);
    sprintf(texto_boss, "Por algum motivo, aquela figura comeca a rir... Segundos depois, o pescoco da figura vira para que o olhar dela encontre o seu. Voce, %s, fica paralisado de medo e essa ", nome_jogador);
    imprimir(texto_boss);
    mudar_cor(12);
    imprimir("monstruosidade");
    mudar_cor(14);
    imprimir(" te ataca.\n");
    mudar_cor(15);

    sangramento = 1;
    vitoria = func_combate("Aberracao Ancia", 40, 10);

    if (vitoria == 0) {
        mudar_cor(12);
        imprimir("\n=====FINAL RUIM=====\n");
        imprimir("Voce e comido ainda vivo por esta criatura e tem uma morte horrivel e grotesca.\n");
        imprimir("Eu sei que voce vai voltar.\n");
        mudar_cor(15);
    } else {
        final_bom();
    }
}

// ---------------- CAMINHO DA ESQUERDA ----------------
void caminho_esquerdo(void) {
    int escolha;

    mudar_cor(14);
    imprimir("\nApos mais algumas horas caminhando pelo caminho esquerdo, voce finalmente encontra um buraco na parte de tras de uma estrutura. O interior do local esta muito escuro e voce pode escutar pessoas falando uma lingua estranha la dentro.\n");
    mudar_cor(15);
    imprimir("1 - Se aproximar para tentar enxergar melhor\n");
    imprimir("2 - Esperar o barulho parar\n");
    if (lanterna == 1) {
        imprimir("3 - Iluminar o local com sua lanterna\n");
    }
    escolha = ler_opcao(1, (lanterna == 1) ? 3 : 2);

    switch (escolha) {
        case 1: // Se aproximar
            mudar_cor(14);
            imprimir("Voce estava tentando se aproximar, mas sem querer acaba tropecando na raiz de uma arvore, fazendo um pouco de barulho. Para o seu azar, uma ");
            mudar_cor(12);
            imprimir("figura humanoide encapuzada");
            mudar_cor(14);
            imprimir(" escutou o som, veio na sua direcao e te encontrou...\n");
            
            mudar_cor(15);
            imprimir("1 - Atacar.\n");
            imprimir("2 - Tentar conversar com a figura.\n");
            escolha = ler_opcao(1, 2);
            if (escolha == 2) {
                mudar_cor(14);
                imprimir("A figura te esfaqueia, e agora voce esta sangrando.\n");
                mudar_cor(15);
                sangramento = 1;
            }
            if (luta_cultista() == 0) return;
            break;

        case 2: // Esperar o barulho parar
            mudar_cor(14);
            imprimir("Voce e uma pessoa esperta e sabe que, seja la quem estiver la dentro, provavelmente nao o recebera de bracos abertos, tomando assim a sabia decisao de esperar o barulho parar.\n");
            imprimir("Mais ou menos 20 minutos se passaram, as vozes finalmente pararam de falar e voce entra na estrutura.\n");
            mudar_cor(15);
            combate = 0;
            break;

        case 3: // Usar a lanterna
            mudar_cor(14);
            imprimir("Voce ilumina o interior da estrutura com a sua lanterna. Para o seu azar, o barulho de pessoas falando era de fato de pessoas conversando... O que voce esperava? De qualquer forma, agora uma ");
            mudar_cor(12);
            imprimir("figura encapuzada");
            mudar_cor(14);
            imprimir(" esta vindo na sua direcao com uma faca na mao.\n");
            mudar_cor(15);
            
            if (luta_cultista() == 0) return;
            break;
    }

    mudar_cor(14);
    imprimir("\nVoce entra nesta estrutura e decide analisar o interior dela em busca de algo para pagar sua divida, claro... encontrando assim 2 barras de ouro. Observando outros detalhes do local, e possivel ver que as paredes estao infestadas de vinhas, o chao tem um pouco de musgo e o que aparentam ser pegadas indo na direcao de uma sala um pouco mais iluminada. Entretanto, voce tambem encontra 2 outros possiveis caminhos: ambos sao portas, 1 porta com diversos ornamentos trancada com uma fechadura verde e a outra que esta levemente aberta.\n");
    mudar_cor(15);
    pontuacao += 200;
    imprimir("1 - Seguir as pegadas.\n");
    imprimir("2 - Entrar na porta levemente aberta\n");
    escolha = ler_opcao(1, 2);

    if (escolha == 1) { // Seguir as pegadas
        if (combate == 0) {
            mudar_cor(14);
            imprimir("Voce e cauteloso e segue as pegadas silenciosamente. Ao entrar na sala iluminada, e possivel visualizar uma figura de costas fazendo alguma coisa em cima de algo que parecia ser um altar.\n");
            mudar_cor(15);
            imprimir("1 - Atacar a figura por tras.\n");
            ler_opcao(1, 1);
            mudar_cor(14);
            imprimir("Voce rapidamente neutraliza o ser encapuzado, evitando um combate.\n");
            combate = 1;
        } else {
            mudar_cor(14);
            imprimir("As pegadas que estavam no chao provavelmente eram da figura que voce havia eliminado recentemente.\n");
        }
        imprimir("Analisando a sala iluminada, e possivel visualizar algumas escrituras na parede. Analisando-as melhor, voce consegue ler a frase \"Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn\", e embaixo desta frase havia um altar com o que parecia ser um anel levemente ensanguentado.\n");
        imprimir("Pegando o anel, voce o observa melhor e ve que ele tem um pequeno diamante. Com isso, decide guarda-lo na sua bolsa e seguir pelo caminho da porta levemente aberta.\n");
        mudar_cor(15);
        
        anel = 1;
        pontuacao += 150;
    }

    // Porta levemente aberta (todos os caminhos chegam aqui)
    if (salao_do_altar("\nA porta levemente aberta levava para uma grande sala, ") == 0) return;
    porta_esquerda();
}

// ---------------- CAMINHO DA DIREITA ----------------
void caminho_direito(void) {
    int escolha;

    mudar_cor(14);
    imprimir("\nSeguindo pela direita, voce encontra o que parece ser um templo antigo e que aparenta ter sido abandonado ha muito tempo...\n");
    mudar_cor(15);
    imprimir("1 - Analisar a entrada do templo.\n");
    imprimir("2 - Entrar no templo.\n");
    escolha = ler_opcao(1, 2);

    if (escolha == 1) {
        mudar_cor(14);
        if (lanterna == 1) {
            imprimir("Ao analisar o templo utilizando sua lanterna, voce ve uma frase escrita na parede: \"Templo do nosso senhor Cthulhu\", alguns tentaculos esculpidos na parede e 2 barras de ouro jogadas no chao. Alem disso, iluminando os cantos da entrada, voce encontra algumas moedas e um colar com um pingente de uma pedra que parece um rubi. Isso deve valer um bom dinheiro, mas que, por algum motivo, tambem te traz uma sensacao de forca...\n");
            colar_forca = 1;
            pontuacao += 200 + 50 + 100; // barras + moedas + colar
        } else {
            imprimir("Ao analisar o templo, voce ve uma frase escrita na parede: \"Templo do nosso senhor Cthulhu\", alguns tentaculos esculpidos na parede e 2 barras de ouro jogadas no chao.\n");
            pontuacao += 200;
        }
    }

    // Entrando no templo
    mudar_cor(14);
    imprimir("\nEntrando no templo, voce se depara com diversos corredores escuros que se bifurcam em varios caminhos e levam a incontaveis salas. Apos andar por um tempo, algo chama sua atencao: dentro de uma das camaras, voce percebe algo brilhando, possivelmente mais barras de ouro.\n");
    mudar_cor(15);
    imprimir("1 - Ir diretamente na direcao do brilho.\n");
    imprimir("2 - Nao arriscar e continuar explorando o templo.\n");
    if (lanterna == 1) {
        imprimir("3 - Utilizar sua lanterna para ver se existem armadilhas por perto.\n");
    }
    escolha = ler_opcao(1, (lanterna == 1) ? 3 : 2);

    switch (escolha) {
        case 1:
            mudar_cor(14);
            imprimir("Cegado pela possibilidade de encontrar mais tesouros para conseguir pagar sua divida, voce vai na direcao do brilho. Ao entrar na camara, voce esbarra em um conjunto de ossos que estava pendurado na entrada do lugar. Voce nao sabe se sao de fato ossos humanos, mas o mais preocupante e que o barulho que voce fez ao colidir com eles parece ter chamado a atencao de algo ou alguem para a sua direcao. Voce se agiliza para pegar o que de fato era uma barra de ouro no centro da camara, mas na hora de sair, uma ");
            mudar_cor(12);
            imprimir("figura encapuzada");
            mudar_cor(14);
            imprimir(" bloqueia seu caminho.\n");
            mudar_cor(15);
            
            pontuacao += 100;
            if (luta_cultista() == 0) return;
            break;
        case 2:
            mudar_cor(14);
            imprimir("Seja la o que fosse aquele brilho, este lugar provavelmente esta cheio de armadilhas e voce deu sorte de ainda nao ter encontrado nenhuma...\n");
            mudar_cor(15);
            break;
        case 3:
            mudar_cor(14);
            imprimir("Voce utiliza sua lanterna para iluminar o caminho e ve um conjunto de ossos que estava pendurado na entrada do lugar. Voce nao sabe se sao de fato ossos humanos, o que te da um arrepio na espinha. Apos se abaixar para evitar encostar nesses ossos, voce entra na camara, pega o que de fato era uma barra de ouro e sai.\n");
            mudar_cor(15);
            pontuacao += 100;
            break;
    }

    mudar_cor(14);
    imprimir("\nSeguindo por esses corredores, voce encontra uma porta extremamente detalhada com ornamentos similares aos que voce viu na entrada do templo. Apos tentar abri-la, voce percebe que ela esta trancada. Analisando a fechadura, voce sabe que uma chave qualquer nao abriria essa porta; sera preciso voltar aqui depois.\n");
    mudar_cor(15);

    if (salao_do_altar("\nSeguindo em frente, voce finalmente chega a algo que nao e um corredor ou outra camara, mas sim uma grande sala: ") == 0) return;
    porta_direita();
}

// ===================== PROGRAMA PRINCIPAL =====================

int main(void) {
    int caminho;
    char texto_inicial[1000];

    // --- Apresentacao inicial ---
    mudar_cor(15);
    imprimir("Digite o nome do seu explorador: ");
    if (scanf(" %49[^\n]", nome_jogador) != 1) {
        strcpy(nome_jogador, "Explorador");
    }
    limpar_buffer();

    mudar_cor(14);
    sprintf(texto_inicial, "\nVoce e %s, um(a) explorador(a) que estava precisando desesperadamente de dinheiro para pagar uma divida. Voce ouve boatos de que uma ilha nao tao distante do litoral guarda tesouros que podem quitar essa divida, entao decide ir para la em busca desses tesouros. Com isso, voce vai a uma loja clandestina para comprar um pequeno barco. Como o dinheiro so permite que voce compre mais 2 itens para levar, voce tera que escolher entre:\n\n", nome_jogador);
    imprimir(texto_inicial);
    mudar_cor(15);

    // --- Itens iniciais ---
    escolher_itens_iniciais();
    mostrar_inventario();

    // --- Decisoes principais ---
    caminho = escolher_caminho();

    if (caminho == 2) {
        caminho_esquerdo();
    } else {
        caminho_direito();
    }

    // --- Pontuacao e resumo ---
    tela_final();
    
    mudar_cor(15); // Reseta a cor no fim da execucao
    return 0;
}