#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combate.h"
#include "estado.h"
#include "formatacao.h"
#include "geral.h"

// objeto de escolha
int escolha = 0;
//itens do inventario
int lanterna = 0;
int colar_forca = 0;
int chave_simples = 0;
int facao = 0;
int colar_hp = 0;
int ataduras = 0;
int municao = 0;
int pistola = 0;
int anel = 0;
int cetro = 0;

int sangramento = 0;
int combate = 0;
int vitoria = 1;
int hp_maximo = 40;
int hp_jogador = 40;
int pontuacao = 0;
char nome_jogador[50];

int main(void) {
    
    // Pergunta o nome do jogador logo de cara
    mudar_cor(15);
    imprimir("Digite o nome do seu explorador (sem espacos): ");
    scanf("%49s", nome_jogador);
    limpar_buffer();
    mudar_cor(14);

    // Cria a variável para montar a história com o nome
    char texto_inicial[1000];
    sprintf(texto_inicial, "\nVoce e %s, um(a) explorador(a) que estava desesperadamente precisando de dinheiro para pagar uma divida. Voce ouve boatos de que uma ilha nao tao distante do litoral guarda tesouros que podem quitar esta divida, entao voce decide ir para la em busca destes tesouros. Com isso, voce vai em uma loja clandestina para comprar um pequeno barco e como o dinheiro so permite que voce compre mais 2 itens para levar voce tera de escolher entre: \n\n", nome_jogador);
    
    // Imprime a história montada
    imprimir(texto_inicial);

    mudar_cor(15);
    escolher_itens_iniciais();
    mudar_cor(14);
    mostrar_inventario();
    
    imprimir("\nUtilizando aquele pequeno barco barato que voce havia comprado, voce consegue chegar na ilha voce caminha ate que vc encontra uma bifurcacao na estrada ambos os caminhos parecem que vao te levar ao mesmo lugar, qual caminho voce ira escolher?\n");
    escolha = escolher_menu(2, "Direita", "Esquerda");
    // PROCESSO DE ENTRAR PELO LADO ESQUERDO
    if (escolha == 2){
        imprimir("Apos seguir pelo caminho do lado esquerdo por um tempo, voce percebe que voce havia retornado para a mesma bifurcacao que voce ja havia passado\n");
        escolha = escolher_menu(2, "Ir para a Direita", "Continuar indo para a Esquerda");
    }
    if (escolha == 2){
        imprimir("Apos seguir pelo caminho do lado esquerdo por mais tempo ainda, voce percebe que voce havia retornado novamente para a mesma bifurcacao que voce ja havia passado\n");
        escolha = escolher_menu(2, "Ir para a Direita", "Continuar indo para a Esquerda");
    }
    // LADO ESQUERDO
    if (escolha == 2){
        imprimir("Apos mais algumas horas caminhando pelo caminho esquerdo, voce finalmente encontra um buraco na parte de tras de uma estrutura, o interior do local esta muito escuro e voce pode escutar pessoas falando uma lingua estranha la dentro.\n");
    escolha = lanterna
        ? escolher_menu(3, "Se aproximar para tentar enxergar melhor", "Esperar o barulho parar", "Iluminar o local com sua lanterna")
        : escolher_menu(2, "Se aproximar para tentar enxergar melhor", "Esperar o barulho parar");
    if (escolha == 1){ // se aproximar pra enxergar melhor
        imprimir("Voce estava tentando se aproximar mas sem querer acaba tropecando na raiz de uma arvore, fazendo um pouco de barulho, para o seu azar uma ");
        mudar_cor(12);
        imprimir("figura humanoide encapuzada");
        mudar_cor(14);
        imprimir(" escutou o som veio na sua direcao e te encontrou...\n");
        escolha = escolher_menu(2, "Atacar", "Tentar conversar com a figura");
        if (escolha == 1){
            
            vitoria = func_combate("Cultista Encapuzado", 15, 6);

            if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como saacrificio para o Deus maligno que ela cultua\n");
                            imprimir("                            ,--.\n"
           "                           {    }\n"
           "                           K,   }\n"
           "                          /  ~Y`\n"
           "                     ,   /   /\n"
           "                    {_'-K.__/\n"
           "                      `/-.__L._\n"
           "                      /  ' /`\\_}\n"
           "                     /  ' /\n"
           "             ____   /  ' /\n"
           "      ,-'~~~~    ~~/  ' /_\n"
           "    ,'             ``~~~  ',\n"
           "   (                        Y\n"
           "  {                         I\n"
           " {      -                    `,\n"
           " |       ',                   )\n"
           " |        |   ,..__      __. Y\n"
           " |    .,_./  Y ' / ^Y   J   )|\n"
           " \\           |' /   |   |   ||\n"
           "  \\          L_/    . _ (_,.'(\n"
           "   \\,   ,      ^^\"\"' / |      )\n"
           "     \\_  \\          /,L]     /\n"
           "       '-_~-,       ` `   ./`\n"
           "          `'{_            )\n"
           "              ^^\\..___,.--`     BURRAO\n");
                    }
                    if (vitoria == 1){
                        combate = 1;
                    }
                } // if da escolha 1 "Atacar"
        if (escolha == 2){
            imprimir("A figura te esfaqueia, agora voce esta sangrando.\n");
            sangramento = 1;
            
            vitoria = func_combate("Cultista Encapuzado", 15, 6);

            if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como saacrificio para o Deus maligno que ela cultua\n");
                            imprimir("                            ,--.\n"
           "                           {    }\n"
           "                           K,   }\n"
           "                          /  ~Y`\n"
           "                     ,   /   /\n"
           "                    {_'-K.__/\n"
           "                      `/-.__L._\n"
           "                      /  ' /`\\_}\n"
           "                     /  ' /\n"
           "             ____   /  ' /\n"
           "      ,-'~~~~    ~~/  ' /_\n"
           "    ,'             ``~~~  ',\n"
           "   (                        Y\n"
           "  {                         I\n"
           " {      -                    `,\n"
           " |       ',                   )\n"
           " |        |   ,..__      __. Y\n"
           " |    .,_./  Y ' / ^Y   J   )|\n"
           " \\           |' /   |   |   ||\n"
           "  \\          L_/    . _ (_,.'(\n"
           "   \\,   ,      ^^\"\"' / |      )\n"
           "     \\_  \\          /,L]     /\n"
           "       '-_~-,       ` `   ./`\n"
           "          `'{_            )\n"
           "              ^^\\..___,.--`     BURRAO\n");
                            escolha = 0;
                    }
                    if (vitoria == 1){
                        imprimir("Analisando o corpo da figura para ver oq ela tinha, a figura nao tinha nada de valioso mas uma chave chama sua atencao, ela provavelmente deve abrir algo importante.\n");
                        combate = 1;
                    }
                } // if da escolha 2 "Conversar"
    } 
    if (escolha == 3){ // usar a lanterna
        imprimir("voce ilumina o interior da estrutura com a sua lanterna, para o seu azar o barulho de pessoas falando era de fato pessoas falando... oque voce esperava? de qualquer forma, agora uma ");
        mudar_cor(12);
        imprimir("figura encapuzada");
        mudar_cor(14);
        imprimir(" esta vindo na sua direcao com uma faca na mao.\n");
        
        vitoria = func_combate("Cultista Encapuzado", 15, 6);

        if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como sacrificio para o Deus maligno que ela cultua\n");
                            imprimir("                            ,--.\n"
           "                           {    }\n"
           "                           K,   }\n"
           "                          /  ~Y`\n"
           "                     ,   /   /\n"
           "                    {_'-K.__/\n"
           "                      `/-.__L._\n"
           "                      /  ' /`\\_}\n"
           "                     /  ' /\n"
           "             ____   /  ' /\n"
           "      ,-'~~~~    ~~/  ' /_\n"
           "    ,'             ``~~~  ',\n"
           "   (                        Y\n"
           "  {                         I\n"
           " {      -                    `,\n"
           " |       ',                   )\n"
           " |        |   ,..__      __. Y\n"
           " |    .,_./  Y ' / ^Y   J   )|\n"
           " \\           |' /   |   |   ||\n"
           "  \\          L_/    . _ (_,.'(\n"
           "   \\,   ,      ^^\"\"' / |      )\n"
           "     \\_  \\          /,L]     /\n"
           "       '-_~-,       ` `   ./`\n"
           "          `'{_            )\n"
           "              ^^\\..___,.--`     BURRAO\n");
                    }
                    if (vitoria == 1){
                        imprimir("Analisando o corpo da figura para ver oque ela tinha, a figura nao tinha nada de valioso mas uma chave chama sua atencao, ela provavelmente deve abrir algo importante.\n");
                        combate = 1;
                    }
    }
    if (escolha == 2){ // Esperar o barulho parar
        imprimir("Voce e uma pessoa esperta e sabe que seja la quem esta la dentro provavelmente nao te recebera de bracos abertos, assim tomando a sabia escolha de esperar o barulho parar.\n");
        imprimir("Mais ou menos 20 minutos se passaram e as vozes finalmente pararam de falar e voce entra dentro da estrutura.\n");
        combate = 0;
    }
    if (hp_jogador > 0) { // Só continua a história se sobreviveu
        imprimir("\nVoce entra dentro desta estrutura e decide analisar o interior dela, em busca de algo para pagar sua divida claro... encontrando assim 2 barras de ouro, observando outros detalhes do local e possivel ver que as paredes estao infestadas de vinhas e o chao tem um pouco de musgo e oque aparenta ser pegadas indo para a direcao de uma sala um pouco mais iluminada, entretanto voce tambem encontra 2 outros possiveis caminhos, ambos sao portas, 1 porta com diversos ornamentos trancadas com uma fechadura verde e a outra que esta levemente aberta.\n");
        escolha = escolher_menu(2, "Seguir as pegadas", "Entrar na porta levemente aberta");
    }
    if (escolha == 1){ // pegadas
        if (combate == 0){
            imprimir("voce e cauteloso e segue as pegada silenciosamente, ao entrar dentro da sala iluminada e possivel visualizar uma figura de costas fazendo alguma coisa em  cima de algo que parecia ser um altar.\n");
            escolha = escolher_menu(1, "Atacar a figura por tras");
            if (escolha == 1){
                imprimir("Voce rapidamente neutraliza o ser encapuzado evitando um combate\n");
                combate = 1;
            }
        }
        if (combate == 1){
           imprimir("As pegadas que estavam no chao provavelmente e da figura que vc havia eliminado recentemente, analisando a sala iluminada, e possivel visualizar algumas escrituras na parede, analisando-as melhor vc consegue uma frase 'Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn', e em baixo desta frase estava um altar com oq parecia ser um anel levemente ensanguentado.\n");
            imprimir("pegando o anel voce o observa melhor e  ve que ele tem um pequeno diamante nele, com isso voce decide guarda-lo na sua bolsa e seguir pelo caminho da porta levemente aberta\n");
            escolha = 2;
        } // apos o combate
        } // pegadas
    if (escolha == 2){ // Porta levemente aberta
        imprimir("\nA porta levemente aberta levava para uma grande sala, o local nao estava muito escuro uma vez que a luz da lua podia ilumina-lo, com isso era possivel de ver algo similar com o interior de uma igreja com diversos assentos e um altar, entretanto, haviam cabecas humanoides com uma barba em formato de tentaculos esculpidas nos pilares do lugar.\n");
            escolha = escolher_menu(2, "Procurar algo no altar", "Procurar nos cantos da sala");
        if (escolha == 2){
            imprimir("Procurando algo de valor que voce possa nao ter percebido nos cantos da sala, voce encontra uma passagem bloqueada por diversas raizes.\n");
            if (facao == 1){
                imprimir("\nFelizmente voce possue um facao e pode cortar estas raizes.\n");
                imprimir("Passando pelas raizes cortadas existia uma salinha com algumas pedras preciosas dentro, apos guardar estas pedras na sua bolsa voce decide voltar e procurar algo no altar.\n");
                escolha = 1;
            }
            if (facao == 0){
                imprimir("Infelizmente voce nao possui uma ferramenta que possa cortar silenciosamente estas raizes, com isso o melhor e voltar e procurar alguma coisa no altar.\n");
                escolha = 1;
            }
        }
        if (escolha == 1){
            imprimir("\nProcurando algo de valor no altar voce encontra um cetro com a ponta em um formato que simboliza a criatura esculpida nos pilares deste lugar, voce decide pega-lo, dado que ele parecia ser feito de alguma pedra valiosa, alem disso voce tambem encontra uma caixa trancada com um cadeado e uma chave verde em cima.\n");
            const char *opcoes_caixa[3] = {
                "Sair da sala e testar a chave na porta com diversos ornamentos",
                NULL,
                NULL
            };
            int quantidade_opcoes = 1;
            if (facao) opcoes_caixa[quantidade_opcoes++] = "Tentar abrir a caixa usando o facao";
            if (chave_simples) opcoes_caixa[quantidade_opcoes++] = "Utilizar a Chave Simples";
            escolha = selecionar_opcao(quantidade_opcoes, opcoes_caixa);
            if (escolha == 2 || escolha == 3){
                imprimir("Dentro da caixa havia um colar com um pingente de uma pedra que parece esmeralda, isto deve valer um bom dinheiro, mas que por algum motivo tambem faz voce se sentir protegido\n");
                colar_hp = 1;
            escolha = 1;
            }
            if (escolha == 1){ // sair do altar e voltar para a porta
                if (combate == 0){ // verifica se o jogador teve um combate antes
                    imprimir("Saindo do local voce e descuidado e acaba sendo emboscado por uma ");
                    mudar_cor(12);
                    imprimir("figura encapuzada");
                    mudar_cor(14);
                    imprimir(" e inicia um COMBATE\n");
                        
                        vitoria = func_combate("Cultista Encapuzado", 15, 6);

                        if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como sacrificio para o Deus maligno que ela cultua\n");
                            imprimir("                            ,--.\n"
           "                           {    }\n"
           "                           K,   }\n"
           "                          /  ~Y`\n"
           "                     ,   /   /\n"
           "                    {_'-K.__/\n"
           "                      `/-.__L._\n"
           "                      /  ' /`\\_}\n"
           "                     /  ' /\n"
           "             ____   /  ' /\n"
           "      ,-'~~~~    ~~/  ' /_\n"
           "    ,'             ``~~~  ',\n"
           "   (                        Y\n"
           "  {                         I\n"
           " {      -                    `,\n"
           " |       ',                   )\n"
           " |        |   ,..__      __. Y\n"
           " |    .,_./  Y ' / ^Y   J   )|\n"
           " \\           |' /   |   |   ||\n"
           "  \\          L_/    . _ (_,.'(\n"
           "   \\,   ,      ^^\"\"' / |      )\n"
           "     \\_  \\          /,L]     /\n"
           "       '-_~-,       ` `   ./`\n"
           "          `'{_            )\n"
           "              ^^\\..___,.--`     BURRAO\n");
                            escolha = 0;
                    }
                    if (vitoria == 1){
                        imprimir("Analisando o corpo da figura para ver oq ela tinha, a figura nao tinha nada de valioso mas uma chave chama sua atencao, ela provavelmente deve abrir algo importante\n");
                        combate = 1;
                    }
                }
    }
            if (combate == 1){
                    imprimir("\nSaindo do salao e indo para a porta ornamental que estava trancada, voce decide utilizar a chave verde que voce encontrou no altar, assim abrindo a porta e entrando em uma sala que tinha um pequeno altar com diversas velas e um diamante grande o suficiente para pagar sua divida, entretanto, voce escuta um barulho de algo se mexendo nas paredes desta sala, para sua surpresa nao era nada que voce tenha visto antes, mas sim um ");
                    mudar_cor(12);
                    imprimir("tentaculo");
                    mudar_cor(14);
                    imprimir(" maior do que um homem... por mais assustador que seja para poder quitar sua divida aquele diamante gigante certamente sera necessario...\n");
                    escolha = escolher_menu(2, "Entrar na sala", "Fugir deste templo macabro");
                    if (escolha == 1){
                        imprimir("Voce junta toda sua coragem e entra dentro da sala determinado a enfrentar este monstro para conseguir cumprir seu objetivo principal de conseguir ser livre de sua divida.\n");
                        
                    vitoria = func_combate("Monstro de Tentaculos", 35, 12);

                    if (vitoria == 0){
                        imprimir("=====FINAL RUIM=====\n");
                        imprimir("O tentaculo pega seu cadaver joga para fora da sala e fecha a porta, esperando a sua proxima vitima.\n");
                        imprimir("                            ,--.\n"
           "                           {    }\n"
           "                           K,   }\n"
           "                          /  ~Y`\n"
           "                     ,   /   /\n"
           "                    {_'-K.__/\n"
           "                      `/-.__L._\n"
           "                      /  ' /`\\_}\n"
           "                     /  ' /\n"
           "             ____   /  ' /\n"
           "      ,-'~~~~    ~~/  ' /_\n"
           "    ,'             ``~~~  ',\n"
           "   (                        Y\n"
           "  {                         I\n"
           " {      -                    `,\n"
           " |       ',                   )\n"
           " |        |   ,..__      __. Y\n"
           " |    .,_./  Y ' / ^Y   J   )|\n"
           " \\           |' /   |   |   ||\n"
           "  \\          L_/    . _ (_,.'(\n"
           "   \\,   ,      ^^\"\"' / |      )\n"
           "     \\_  \\          /,L]     /\n"
           "       '-_~-,       ` `   ./`\n"
           "          `'{_            )\n"
           "              ^^\\..___,.--`     BURRAO\n");
                        escolha = 0;
                    }
                    if (vitoria == 1){
                        imprimir("=====FINAL BOM=====\n");
                        imprimir("Apos a luta, voce sai correndo para fora daquele templo sabendo que oque voce ja havia encontrado era muito mais  do que o suficiente para pagar sua divida! assim, voltando para o seu barquinho e fugindo daquela ilha.\n");
                        imprimir("Voce consegue pagar toda sua divida e viver uma vida de luxo pelos proximos anos sem se preocupar em trabalhar de novo!\n");
                        imprimir("||====================================================================||\n"
        "||//$\\\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\///$\\||\n"
        "||(100)==================| FEDERAL RESERVE NOTE |================(100)||\n"
        "||\\\\$//        ~         '------========--------'                \\\\$//||\n"
        "||<< /        /$\\              // ____ \\\\                         \\ >>||\n"
        "||>>|  12    //L\\\\            // ///..) \\\\         L38036133B   12 |<<||\n"
        "||<<|        \\\\ //           || <||  >\\  ||                        |>>||\n"
        "||>>|         \\$/            ||  $$ --/  ||        One Hundred     |<<||\n"
        "||<<|      L38036133B        *\\\\  |\\_/  //* series                 |>>||\n"
        "||>>|  12                     *\\\\/___\\_//*   1989                  |<<||\n"
        "||<<\\      Treasurer     ______/Franklin\\________     Secretary 12 />>||\n"
        "||//$\\                 ~|UNITED STATES OF AMERICA|~               /$\\\\||\n"
        "||(100)===================  ONE HUNDRED DOLLARS =================(100)||\n"
        "||\\\\$//\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\\$||\n"
        "||====================================================================||\n");
                        escolha = 0;
                    }
                    }
                    if (escolha == 2){
                        imprimir("=====FINAL NEUTRO=====\n");
                        imprimir("voce sai correndo para fora daquele templo esperando que oque voce ja havia encontrado era milagrosamente o suficiente para pagar sua divida... voce volta para o seu barquinho e foge daquela ilha.\n");
                        imprimir("Com isso, voce consegue pagar parte de sua divida mas ainda tera de trabalhar o resto de sua vida para se tornar livre dela... felizmente pagar parte do valor fez o seu cobrador nao tomar uma medida mais radical contra voce...\n");
                        imprimir(" _______________________\n"
           "| .-------------------. |\n"
           "| | REP. FED. BRASIL  | |\n"
           "| |                   | |\n"
           "| |      / \\          | |\n"
           "| |     / * \\         | |\n"
           "| |    /_____\\        | |\n"
           "| |                   | |\n"
           "| |       CTPS        | |\n"
           "| |                   | |\n"
           "| | CARTEIRA DE TRAB. | |\n"
           "| '-------------------' |\n"
           "|_______________________|\n");
                        escolha = 0;
                    }
                    }
                }
        
    
    } 
    }// chaves lado ESQUERDO
// LADO DIREITO
    if (escolha == 1){
        imprimir("Seguindo pela Direita voce encontra oque parece ser um templo antigo e que aparenta ter sido abandonado ha muito tempo...\n");
        escolha = escolher_menu(2, "Analisar a entrada do templo", "Entrar no templo");
        
            if (escolha == 1){
                if (lanterna == 1){
                    imprimir("Ao analisar o templo utilizando sua lanterna voce le uma frase escrita na parede 'Templo do nosso senhor Cthulhu', alguns tentaculos esculpidos na parede, e 2 barras de ouro e ele so tem a opcao de Entrar no templo apos isso, caso ele tenha uma lanterna ele encontra algumas moedas na entrada e um colar com um pingente de uma pedra que parece rubi, isto deve valer um bom dinheiro, mas que por algum motivo tambem te tras a sensacao de forca?\n");
                    colar_forca = 1;
                    escolha = 2;
                }else{
                imprimir("Ao analisar o templo voce le uma frase escrita na parede 'Templo do nosso senhor Cthulhu', alguns tentaculos esculpidos na parede, e 2 barras de ouro.\n");
                    escolha = 2;
                }
            }
        // Entrando no Templo
        if(escolha == 2){
                imprimir("\nEntrando no templo vc se depara com diversos corredores escuros que se bifurcam em diversos caminhos que levam a incontaveis salas, apos andar por um tempo algo chama sua atencao, dentro de uma das camaras vc percebe algo brilhando, possivelmente mais barras de ouro.\n");
        escolha = lanterna
            ? escolher_menu(3, "Ir diretamente na direcao do brilho", "Nao arriscar e continuar explorando o templo", "Utilizar sua lanterna para procurar armadilhas")
            : escolher_menu(2, "Ir diretamente na direcao do brilho", "Nao arriscar e continuar explorando o templo");
        if (escolha == 1){
            imprimir("Cegado pela possibilidade de encontrar mais tesouros para conseguir pagar sua divida voce vai na direcao do brilho, entrando na camara voce bate em um conjunto de ossos q estava pendurado na entrada do lugar, voce nao sabe se sao de fato ossos humanos, mas o mais preocupante e que o barulho que voce fez colidindo com eles parece ter chamado a atencao de algo ou alguem para a sua direcao, voce se agiliza para pegar oque de fato era uma barra de ouro no centro da camara mas na hora de sair, uma ");
            mudar_cor(12);
            imprimir("figura encapuzada");
            mudar_cor(14);
            imprimir(" bloqueia seu caminho.\n");
                
            vitoria = func_combate("Cultista Encapuzado", 15, 6);

            if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como saacrificio para o Deus maligno que ela cultua\n");
                            imprimir("                            ,--.\n"
           "                           {    }\n"
           "                           K,   }\n"
           "                          /  ~Y`\n"
           "                     ,   /   /\n"
           "                    {_'-K.__/\n"
           "                      `/-.__L._\n"
           "                      /  ' /`\\_}\n"
           "                     /  ' /\n"
           "             ____   /  ' /\n"
           "      ,-'~~~~    ~~/  ' /_\n"
           "    ,'             ``~~~  ',\n"
           "   (                        Y\n"
           "  {                         I\n"
           " {      -                    `,\n"
           " |       ',                   )\n"
           " |        |   ,..__      __. Y\n"
           " |    .,_./  Y ' / ^Y   J   )|\n"
           " \\           |' /   |   |   ||\n"
           "  \\          L_/    . _ (_,.'(\n"
           "   \\,   ,      ^^\"\"' / |      )\n"
           "     \\_  \\          /,L]     /\n"
           "       '-_~-,       ` `   ./`\n"
           "          `'{_            )\n"
           "              ^^\\..___,.--`     BURRAO\n");
                    }
            if (vitoria == 1){
                imprimir("Analisando o corpo da figura para ver oque ela tinha, a figura nao tinha nada de valioso mas uma chave chama sua atencao, ela provavelmente deve abrir algo importante.\n");
                combate = 1;
                chave_simples = 1;
                    }
            escolha = 0;
        }
        if (escolha == 2){
            imprimir("Seja la oque era aquele brilho este lugar provavelmente esta cheio de armadilhas e voce deu sorte de ainda nao ter encontrado nenhuma...\n");
            escolha = 0;
        }           
        if (escolha == 3){
            imprimir("voce utiliza sua lanterna para iluminar o caminho e voce ve um conjunto de ossos que estava pendurado na entrada do lugar, voce nao sabe se sao de fato ossos humanos oque te da um arrepio na espinha, apos se abaixar para evitar encostar nestes ossos voce entra na camara pega oque de fato era uma barra de ouro e sai.\n");
            escolha = 0;
            }
        if (hp_jogador > 0 && escolha == 0){ // Só segue a exploração se estiver vivo
            imprimir("\nSeguindo estes corredores voce encontra uma porta extremamente detalhada com ornamentos similares aos que voce viu na entrada do templo, apos tentar abri-la voce percebe que ela esta trancada e analisando a fechadura voce sabe que uma chave qualquer nao abriria esta porta, e possivel voltar aqui depois.\n");
            imprimir("\nSeguindo em frente voce finalmente chega em algo que nao e um corredor ou outra camara mas sim uma grande sala, o local nao estava muito escuro uma vez que a luz da lua podia ilumina-lo, com isso era possivel de ver algo similar com o interior de uma igreja com diversos assentos e um altar, entretanto, haviam cabecas humanoides com uma barba em formato de tentaculos esculpidas nos pilares do lugar.\n");
            escolha = escolher_menu(2, "Procurar algo no altar", "Procurar nos cantos da sala");
        if (escolha == 2){
            imprimir("Procurando algo de valor que voce possa nao ter percebido nos cantos da sala, voce encontra uma passagem bloqueada por diversas raizes.\n");
            if (facao == 1){
                imprimir("\nFelizmente voce possue um facao e pode cortar estas raizes.\n");
                imprimir("Passando pelas raizes cortadas existia uma salinha com algumas pedras preciosas dentro, apos guardar estas pedras na sua bolsa voce decide voltar e procurar algo no altar.\n");
                escolha = 1;
            }
            if (facao == 0){
                imprimir("Infelizmente voce nao possue uma ferramenta que possa cortar silenciosamente estas raizes, com isso o melhor e voltar e procurar alguma coisa no altar.\n");
                escolha = 1;
            }
        }
        if (escolha == 1){
            imprimir("\nProcurando algo de valor no altar voce encontra um cetro com a ponta em um formato que simboliza a criatura esculpida nos pilares deste lugar, voce decide pega-lo, dado que ele parecia ser feito de alguma pedra valiosa, alem disso voce tambem encontra uma caixa trancada com um cadeado e uma chave verde em cima.\n");
            const char *opcoes_caixa[3] = {
                "Sair da sala e testar a chave na porta com diversos ornamentos",
                NULL,
                NULL
            };
            int quantidade_opcoes = 1;
            if (facao) opcoes_caixa[quantidade_opcoes++] = "Tentar abrir a caixa usando o facao";
            if (chave_simples) opcoes_caixa[quantidade_opcoes++] = "Utilizar a Chave Simples";
            escolha = selecionar_opcao(quantidade_opcoes, opcoes_caixa);
            if (escolha == 2 || escolha == 3){
                imprimir("Dentro da caixa havia um colar com um pingente de uma pedra que parece esmeralda, isto deve valer um bom dinheiro, mas que por algum motivo tambem faz voce se sentir protegido\n");
                colar_hp = 1;
            escolha = 1;
            }
            if (escolha == 1){ // sair do altar e voltar para a porta
                if (combate == 0){ // verifica se o jogador teve um combate antes
                    imprimir("Saindo do local voce e descuidado e acaba sendo emboscado por uma ");
                    mudar_cor(12);
                    imprimir("figura encapuzada");
                    mudar_cor(14);
                    imprimir(" e inicia um COMBATE\n");
                        
                    vitoria = func_combate("Cultista Encapuzado", 15, 6);

                        if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como sacrificio para o Deus maligno que ela cultua\n");
                             imprimir("                            ,--.\n"
           "                           {    }\n"
           "                           K,   }\n"
           "                          /  ~Y`\n"
           "                     ,   /   /\n"
           "                    {_'-K.__/\n"
           "                      `/-.__L._\n"
           "                      /  ' /`\\_}\n"
           "                     /  ' /\n"
           "             ____   /  ' /\n"
           "      ,-'~~~~    ~~/  ' /_\n"
           "    ,'             ``~~~  ',\n"
           "   (                        Y\n"
           "  {                         I\n"
           " {      -                    `,\n"
           " |       ',                   )\n"
           " |        |   ,..__      __. Y\n"
           " |    .,_./  Y ' / ^Y   J   )|\n"
           " \\           |' /   |   |   ||\n"
           "  \\          L_/    . _ (_,.'(\n"
           "   \\,   ,      ^^\"\"' / |      )\n"
           "     \\_  \\          /,L]     /\n"
           "       '-_~-,       ` `   ./`\n"
           "          `'{_            )\n"
           "              ^^\\..___,.--`     BURRAO\n");
                    }
                    if (vitoria == 1){
                        imprimir("Analisando o corpo da figura para ver oq ela tinha, a figura nao tinha nada de valioso mas uma chave chama sua atencao, ela provavelmente deve abrir algo importante\n");
                        combate = 1;
                    }
                }
                if (combate == 1){
                    imprimir("\nSaindo deste salao voce volta para aquela porta ornamental e decide tentar abri-la com sua nova chave, para sua surpresa ela realmente abre e voce entra em uma sala que tinha um pequeno altar com diversas velas e um diamante grande o suficiente para pagar sua divida, entretanto, tambem havia uma ");
                    mudar_cor(12);
                    imprimir("figura encapuzada");
                    mudar_cor(14);
                    imprimir(" ajoelhada na frente do altar\n");
                    // --- MUDANÇA AQUI: Inserindo o nome na descrição do Boss ---
                    char texto_final_boss[500];
                    sprintf(texto_final_boss, "Por algum motivo aquela figura comeca a rir... segundos depois o pescoco da figura vira para que o olhar dela encontre o seu, voce, %s, esta paralisado de medo e esta ", nome_jogador);
                    imprimir(texto_final_boss);
                    mudar_cor(12);
                    imprimir("monstruosidade");
                    mudar_cor(14);
                    imprimir(" te ataca.\n");

                    sangramento = 1;
                    
                    vitoria = func_combate("Aberracao Ancia", 40, 10);

                    if (vitoria == 0){
                        imprimir("=====FINAL RUIM=====\n");
                        imprimir("voce e comido ainda vivo por esta criatura e tem uma morte horrivel e grotesca.\n");
                        imprimir("Eu sei que voce vai voltar\n");
                        imprimir("                            ,--.\n"
           "                           {    }\n"
           "                           K,   }\n"
           "                          /  ~Y`\n"
           "                     ,   /   /\n"
           "                    {_'-K.__/\n"
           "                      `/-.__L._\n"
           "                      /  ' /`\\_}\n"
           "                     /  ' /\n"
           "             ____   /  ' /\n"
           "      ,-'~~~~    ~~/  ' /_\n"
           "    ,'             ``~~~  ',\n"
           "   (                        Y\n"
           "  {                         I\n"
           " {      -                    `,\n"
           " |       ',                   )\n"
           " |        |   ,..__      __. Y\n"
           " |    .,_./  Y ' / ^Y   J   )|\n"
           " \\           |' /   |   |   ||\n"
           "  \\          L_/    . _ (_,.'(\n"
           "   \\,   ,      ^^\"\"' / |      )\n"
           "     \\_  \\          /,L]     /\n"
           "       '-_~-,       ` `   ./`\n"
           "          `'{_            )\n"
           "              ^^\\..___,.--`     BURRAO\n");
                    }
                    if (vitoria == 1){
                        imprimir("=====FINAL BOM=====\n");
                        imprimir("Apos a luta, voce sai correndo para fora daquele templo sabendo que oque voce ja havia encontrado era muito mais  do que o suficiente para pagar sua divida! assim, voltando para o seu barquinho e fugindo daquela ilha.\n");
                        imprimir("Voce consegue pagar toda sua divida e viver uma vida de luxo pelos proximos anos sem se preocupar em trabalhar de novo!\n");
                        imprimir("||====================================================================||\n"
        "||//$\\\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\///$\\||\n"
        "||(100)==================| FEDERAL RESERVE NOTE |================(100)||\n"
        "||\\\\$//        ~         '------========--------'                \\\\$//||\n"
        "||<< /        /$\\              // ____ \\\\                         \\ >>||\n"
        "||>>|  12    //L\\\\            // ///..) \\\\         L38036133B   12 |<<||\n"
        "||<<|        \\\\ //           || <||  >\\  ||                        |>>||\n"
        "||>>|         \\$/            ||  $$ --/  ||        One Hundred     |<<||\n"
        "||<<|      L38036133B        *\\\\  |\\_/  //* series                 |>>||\n"
        "||>>|  12                     *\\\\/___\\_//*   1989                  |<<||\n"
        "||<<\\      Treasurer     ______/Franklin\\________     Secretary 12 />>||\n"
        "||//$\\                 ~|UNITED STATES OF AMERICA|~               /$\\\\||\n"
        "||(100)===================  ONE HUNDRED DOLLARS =================(100)||\n"
        "||\\\\$//\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\\$||\n"
        "||====================================================================||\n");
                    }
                }
            }
        }
        }
        }
    }
    mudar_cor(0);
    return 0;
}