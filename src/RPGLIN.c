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
    imprimir("Digite o nome do seu explorador (sem espacos): ");
    scanf("%49s", nome_jogador);

    // Cria a variável para montar a história com o nome
    char texto_inicial[1000];
    sprintf(texto_inicial, "\nVoce e %s, um(a) explorador(a) que estava desesperadamente precisando de dinheiro para pagar uma divida. Voce ouve boatos de que uma ilha nao tao distante do litoral guarda tesouros que podem quitar esta divida, entao voce decide ir para la em busca destes tesouros. Com isso, voce vai em uma loja clandestina para comprar um pequeno barco e como o dinheiro so permite que voce compre mais 2 itens para levar voce tera de escolher entre: \n\n", nome_jogador);
    
    // Imprime a história montada
    imprimir(texto_inicial);

    imprimir("1- Facao --> 6 de dano\n");
    imprimir("2 - Pistola com 6 municoes --> 10 de dano por municao\n");
    imprimir("3 - Lanterna --> ilumina lugares escuros\n");
    imprimir("4 - 2 Ataduras --> curam x de vida e param sangramento\n");
    
    scanf("%d", &escolha);
    
    if (escolha == 1){
        imprimir("1 - Pistola com 6 municoes --> 10 de dano por municao\n");
        imprimir("2 - Lanterna --> ilumina lugares escuros\n");
        imprimir("3 - 2 Ataduras --> curam x de vida e param sangramento\n");
        facao = 1;
        scanf("%d", &escolha);
        if (escolha == 1){
            pistola = 1;
            municao = 6;
        }
        if (escolha == 2){
            lanterna = 1;
        }
        if (escolha == 3){
            ataduras = 2;
        }
    }else if (escolha == 2){
        imprimir("1- Facao --> 6 de dano\n");
        imprimir("2 - Lanterna --> ilumina lugares escuros\n");
        imprimir("3 - 2 Ataduras --> curam x de vida e param sangramento\n");
        pistola = 1;
        municao = 6;
        scanf("%d", &escolha);
        if (escolha == 1){
            facao = 1;
        }
        if (escolha == 2){
            lanterna = 1;
        }
        if (escolha == 3){
            ataduras = 2;
        }
    }else if (escolha == 3){
        imprimir("1- Facao --> 6 de dano\n");
        imprimir("2 - Pistola com 6 municoes --> 10 de dano por municao\n");
        imprimir("3 - 2 Ataduras --> curam x de vida e param sangramento\n");
        lanterna = 1;
        scanf("%d", &escolha);
        if (escolha == 2){
            pistola = 1;
            municao = 6;
        }
        if (escolha == 1){
            facao = 1;
        }
        if (escolha == 3){
            ataduras = 2;
        }
    }else if (escolha == 4){
        imprimir("1- Facao --> 6 de dano\n");
        imprimir("2 - Pistola com 6 municoes --> 10 de dano por municao\n");
        imprimir("3 - Lanterna --> ilumina lugares escuros\n");
        ataduras = 2;
        scanf("%d", &escolha);
        if (escolha == 2){
            pistola = 1;
            municao = 6;
        }
        if (escolha == 3){
            lanterna = 1;
        }
        if (escolha == 1){
            facao = 1;
        }
    }
    imprimir("\nInventario: \n");
    if (facao == 1){
        imprimir("Facao --> 6 de dano\n");
    }
    if (lanterna == 1){
        imprimir("Lanterna --> ilumina lugares escuros\n");
    }
    if (pistola == 1){
        imprimir("Pistola com 6 municoes --> 10 de dano por municao\n");
    }
    if (ataduras == 2){
        imprimir("2 Ataduras --> curam vida e param sangramento\n");
    }
    
    imprimir("\nUtilizando aquele pequeno barco barato que voce havia comprado, voce consegue chegar na ilha voce caminha ate que vc encontra uma bifurcacao na estrada ambos os caminhos parecem que vao te levar ao mesmo lugar, qual caminho voce ira escolher?\n");
    imprimir("1 - Direita\n");
    imprimir("2 - Esquerda\n");
    scanf("%d", &escolha);
    // PROCESSO DE ENTRAR PELO LADO ESQUERDO
    if (escolha == 2){
        imprimir("Apos seguir pelo caminho do lado esquerdo por um tempo, voce percebe que voce havia retornado para a mesma bifurcacao que voce ja havia passado\n");
    imprimir("1 - Ir para a Direita\n");
    imprimir("2 - Continuar indo para a Esquerda\n");
        scanf("%d", &escolha);
    }
    if (escolha == 2){
        imprimir("Apos seguir pelo caminho do lado esquerdo por mais tempo ainda, voce percebe que voce havia retornado novamente para a mesma bifurcacao que voce ja havia passado\n");
    imprimir("1 - Ir para a Direita\n");
    imprimir("2 - Continuar indo para a Esquerda\n");
        scanf("%d", &escolha);
    }
    // LADO ESQUERDO
    if (escolha == 2){
        imprimir("Apos mais algumas horas caminhando pelo caminho esquerdo, voce finalmente encontra um buraco na parte de tras de uma estrutura, o interior do local esta muito escuro e voce pode escutar pessoas falando uma lingua estranha la dentro.\n");
    imprimir("1 - Se aproximar para tentar enxergar melhor\n");
    imprimir("2 - Esperar o barulho parar\n");
    if (lanterna == 1){
            imprimir("3 - iluminar o local com sua lanterna\n");
        }
    scanf("%d", &escolha);
    if (escolha == 1){ // se aproximar pra enxergar melhor
        imprimir("Voce estava tentando se aproximar mas sem querer acaba tropecando na raiz de uma arvore, fazendo um pouco de barulho, para o seu azar uma figura humanoide encapuzada escutou o som veio na sua direcao e te encontrou...\n");
        imprimir("1 - Atacar.\n");
        imprimir("2 - Tentar conversar com a figura.\n");
        scanf("%d", &escolha);
        if (escolha == 1){
            
            vitoria = func_combate("Cultista Encapuzado", 15, 6);

            if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como saacrificio para o Deus maligno que ela cultua\n");
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
                            escolha = 0;
                    }
                    if (vitoria == 1){
                        imprimir("Analisando o corpo da figura para ver oq ela tinha, a figura nao tinha nada de valioso mas uma chave chama sua atencao, ela provavelmente deve abrir algo importante.\n");
                        combate = 1;
                    }
                } // if da escolha 2 "Conversar"
    } 
    if (escolha == 3){ // usar a lanterna
        imprimir("voce ilumina o interior da estrutura com a sua lanterna, para o seu azar o barulho de pessoas falando era de fato pessoas falando... oque voce esperava? de qualquer forma, agora uma figura encapuzada esta vindo na sua direcao com uma faca na mao.\n");
        
        vitoria = func_combate("Cultista Encapuzado", 15, 6);

        if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como sacrificio para o Deus maligno que ela cultua\n");
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
        imprimir("1 - Seguir as pegadas.\n");
        imprimir("2 - Entrar na porta levemente aberta\n");
        scanf("%d", &escolha);
    }
    if (escolha == 1){ // pegadas
        if (combate == 0){
            imprimir("voce e cauteloso e segue as pegada silenciosamente, ao entrar dentro da sala iluminada e possivel visualizar uma figura de costas fazendo alguma coisa em  cima de algo que parecia ser um altar.\n");
            imprimir("1 - atacar a figura por tras.\n");
            scanf("%d", &escolha);
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
            imprimir("1 - procurar algo no altar\n");
            imprimir("2 - procurar nos cantos da sala\n");
            scanf("%d", &escolha);
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
            imprimir("1 - Sair da sala as coisas que voce encontrou e testar a chave na porta com diversos ornamentos.\n");
            if (facao == 1 && chave_simples == 1){
                imprimir("2 - Tentar abrir a caixa usando o facao.\n");
                imprimir("3 - Utilizar a Chave Simples.\n");
            }
            if (chave_simples == 1 && facao == 0){
                imprimir("2 - Utilizar a Chave Simples.\n");
            }
            if (chave_simples == 0 && facao == 1){
                imprimir("2 - Tentar abrir a caixa usando o facao.\n");
            }
            scanf("%d", &escolha);
            if (escolha == 2 || escolha == 3){
                imprimir("Dentro da caixa havia um colar com um pingente de uma pedra que parece esmeralda, isto deve valer um bom dinheiro, mas que por algum motivo tambem faz voce se sentir protegido\n");
                colar_hp = 1;
            escolha = 1;
            }
            if (escolha == 1){ // sair do altar e voltar para a porta
                if (combate == 0){ // verifica se o jogador teve um combate antes
                    imprimir("Saindo do local voce e descuidado e acaba sendo emboscado por uma figura encapuzada e inicia um COMBATE\n");
                        
                        vitoria = func_combate("Cultista Encapuzado", 15, 6);

                        if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como sacrificio para o Deus maligno que ela cultua\n");
                            escolha = 0;
                    }
                    if (vitoria == 1){
                        imprimir("Analisando o corpo da figura para ver oq ela tinha, a figura nao tinha nada de valioso mas uma chave chama sua atencao, ela provavelmente deve abrir algo importante\n");
                        combate = 1;
                    }
                }
    }
            if (combate == 1){
                    imprimir("\nSaindo do salao e indo para a porta ornamental que estava trancada, voce decide utilizar a chave verde que voce encontrou no altar, assim abrindo a porta e entrando em uma sala que tinha um pequeno altar com diversas velas e um diamante grande o suficiente para pagar sua divida, entretanto, voce escuta um barulho de algo se mexendo nas paredes desta sala, para sua surpresa nao era nada que voce tenha visto antes, mas sim um tentaculo maior do que um homem... por mais assustador que seja para poder quitar sua divida aquele diamante gigante certamente sera necessario...\n");
                    imprimir("1 - Entrar na sala\n");
                    imprimir("2 - Fugir deste templo macabro\n");
                    scanf("%d", &escolha);
                    if (escolha == 1){
                        imprimir("Voce junta toda sua coragem e entra dentro da sala determinado a enfrentar este monstro para conseguir cumprir seu objetivo principal de conseguir ser livre de sua divida.\n");
                        
                    vitoria = func_combate("Monstro de Tentaculos", 35, 12);

                    if (vitoria == 0){
                        imprimir("=====FINAL RUIM=====\n");
                        imprimir("O tentaculo pega seu cadaver joga para fora da sala e fecha a porta, esperando a sua proxima vitima.\n");
                        escolha = 0;
                    }
                    if (vitoria == 1){
                        imprimir("=====FINAL BOM=====\n");
                        imprimir("Apos a luta, voce sai correndo para fora daquele templo sabendo que oque voce ja havia encontrado era muito mais  do que o suficiente para pagar sua divida! assim, voltando para o seu barquinho e fugindo daquela ilha.\n");
                        imprimir("Voce consegue pagar toda sua divida e viver uma vida de luxo pelos proximos anos sem se preocupar em trabalhar de novo!\n");
                        escolha = 0;
                    }
                    }
                    if (escolha == 2){
                        imprimir("=====FINAL NEUTRO=====\n");
                        imprimir("voce sai correndo para fora daquele templo esperando que oque voce ja havia encontrado era milagrosamente o suficiente para pagar sua divida... voce volta para o seu barquinho e foge daquela ilha.\n");
                        imprimir("Com isso, voce consegue pagar parte de sua divida mas ainda tera de trabalhar o resto de sua vida para se tornar livre dela... felizmente pagar parte do valor fez o seu cobrador nao tomar uma medida mais radical contra voce...\n");
                        escolha = 0;
                    }
                    }
                }
        
    
    } 
    }// chaves lado ESQUERDO
// LADO DIREITO
    if (escolha == 1){
        imprimir("Seguindo pela Direita voce encontra oque parece ser um templo antigo e que aparenta ter sido abandonado ha muito tempo...\n");
        imprimir("1 - Analisar a entrada do templo.\n");
        imprimir("2 - Entrar no templo.\n");
        scanf("%d", &escolha);
        
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
    imprimir("1 - ir diretamente na direcao do brilho.\n");
    imprimir("2 - nao arriscar e continuar explorando o templo.\n");
    if (lanterna == 1){
        imprimir("3 - Utilizar sua lanterna para ver se existem armadilhas por perto.\n");   
    }
        scanf("%d", &escolha);
        if (escolha == 1){
            imprimir("Cegado pela possibilidade de encontrar mais tesouros para conseguir pagar sua divida voce vai na direcao do brilho, entrando na camara voce bate em um conjunto de ossos q estava pendurado na entrada do lugar, voce nao sabe se sao de fato ossos humanos, mas o mais preocupante e que o barulho que voce fez colidindo com eles parece ter chamado a atencao de algo ou alguem para a sua direcao, voce se agiliza para pegar oque de fato era uma barra de ouro no centro da camara mas na hora de sair, uma figura encapuzada bloqueia seu caminho.\n");
                
            vitoria = func_combate("Cultista Encapuzado", 15, 6);

            if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como saacrificio para o Deus maligno que ela cultua\n");
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
            imprimir("1 - procurar algo no altar\n");
            imprimir("2 - procurar nos cantos da sala\n");
            scanf("%d", &escolha);
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
            imprimir("1 - Sair da sala com as coisas que voce encontrou e testar a chave na porta com diversos ornamentos.\n");
            if (facao == 1 && chave_simples == 1){
                imprimir("2 - Tentar abrir a caixa usando o facao.\n");
                imprimir("3 - Utilizar a Chave Simples.\n");
            }
            if (chave_simples == 1 && facao == 0){
                imprimir("2 - Utilizar a Chave Simples.\n");
            }
            if (chave_simples == 0 && facao == 1){
                imprimir("2 - Tentar abrir a caixa usando o facao.\n");
            }
            scanf("%d", &escolha);
            if (escolha == 2 || escolha == 3){
                imprimir("Dentro da caixa havia um colar com um pingente de uma pedra que parece esmeralda, isto deve valer um bom dinheiro, mas que por algum motivo tambem faz voce se sentir protegido\n");
                colar_hp = 1;
            escolha = 1;
            }
            if (escolha == 1){ // sair do altar e voltar para a porta
                if (combate == 0){ // verifica se o jogador teve um combate antes
                    imprimir("Saindo do local voce e descuidado e acaba sendo emboscado por uma figura encapuzada e inicia um COMBATE\n");
                        
                    vitoria = func_combate("Cultista Encapuzado", 15, 6);

                        if (vitoria == 0){
                            imprimir("=====FINAL RUIM=====\n");
                            imprimir("A figura encapuzada ganha de voce e te usa como sacrificio para o Deus maligno que ela cultua\n");
                    }
                    if (vitoria == 1){
                        imprimir("Analisando o corpo da figura para ver oq ela tinha, a figura nao tinha nada de valioso mas uma chave chama sua atencao, ela provavelmente deve abrir algo importante\n");
                        combate = 1;
                    }
                }
                if (combate == 1){
                    imprimir("\nSaindo deste salao voce volta para aquela porta ornamental e decide tentar abri-la com sua nova chave, para sua surpresa ela realmente abre e voce entra em uma sala que tinha um pequeno altar com diversas velas e um diamante grande o suficiente para pagar sua divida, entretanto, tambem havia uma figura encapuzada ajoelhada na frente do altar\n");
                    imprimir("1 - Ataca----!??... opcao do jogador interrompida-\n");
                    
                    // --- MUDANÇA AQUI: Inserindo o nome na descrição do Boss ---
                    char texto_final_boss[500];
                    sprintf(texto_final_boss, "Por algum motivo aquela figura comeca a rir... segundos depois o pescoco da figura vira para que o olhar dela encontre o seu, voce, %s, esta paralisado de medo e esta monstruosidade te ataca.\n", nome_jogador);
                    imprimir(texto_final_boss);
                    
                    sangramento = 1;
                    
                    vitoria = func_combate("Aberracao Ancia", 40, 10);

                    if (vitoria == 0){
                        imprimir("=====FINAL RUIM=====\n");
                        imprimir("voce e comido ainda vivo por esta criatura e tem uma morte horrivel e grotesca.\n");
                        imprimir("Eu sei que voce vai voltar\n");
                    }
                    if (vitoria == 1){
                        imprimir("=====FINAL BOM=====\n");
                        imprimir("Apos a luta, voce sai correndo para fora daquele templo sabendo que oque voce ja havia encontrado era muito mais  do que o suficiente para pagar sua divida! assim, voltando para o seu barquinho e fugindo daquela ilha.\n");
                        imprimir("Voce consegue pagar toda sua divida e viver uma vida de luxo pelos proximos anos sem se preocupar em trabalhar de novo!\n");
                    }
                }
            }
        }
        }
        }
    }
    return 0;
}