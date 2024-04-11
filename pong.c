#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

void linhaCol(int lin, int col);
void box(int lin1, int col1, int lin2, int col2);
int menu(int lin1, int col1, int qtd, char lista[5][40]);
void textColor(int letras, int fundo);

enum
{
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

enum
{
    _BLACK = 0, _BLUE = 16, _GREEN = 32, _CYAN = 48, _RED = 64, _MAGENTA = 80, _BROWN = 96,
    _LIGHTGRAY = 112, _DARKGRAY = 128, _LIGHTBLUE = 144, _LIGHTGREEN = 160, _LIGHTCYAN = 176,
    _LIGHTRED = 192, _LIGHTMAGENTA = 208, _YELLOW = 224, _WHITE = 240
};


void textColor(int letra, int fundo)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);

    CONSOLE_FONT_INFOEX font;
    font.cbSize = sizeof(font);
    font.nFont = 0;
    font.dwFontSize.X = 0;  // Largura da fonte (0 = mantém o mesmo que o padrão)
    font.dwFontSize.Y = 27; // Altura da fonte (24 = tamanho maior)
    font.FontFamily = FF_DONTCARE;
    font.FontWeight = FW_NORMAL;
    wcscpy(font.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
}

void linhaCol(int lin, int col)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { col - 1, lin - 1 });
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void box(int lin1, int col1, int lin2, int col2)
{
    int i, j, tamlin, tamcol;
    tamlin = lin2 - lin1;
    tamcol = col2 - col1;

    for (i = col1; i <= col2; i++)
    {
        linhaCol(lin1, i);
        printf("%c", 196);
        linhaCol(lin2, i);
        printf("%c", 196);
    }

    for (i = lin1; i <= lin2; i++)
    {
        linhaCol(i, col1);
        printf("%c", 179);
        linhaCol(i, col2);
        printf("%c", 179);
    }

    for (i = lin1 + 1; i < lin2; i++)
    {
        for (j = col1 + 1; j < col2; j++)
        {
            linhaCol(i, j); printf(" ");
        }
    }

    linhaCol(lin1, col1);
    printf("%c", 218);
    linhaCol(lin1, col2);
    printf("%c", 191);
    linhaCol(lin2, col1);
    printf("%c", 192);
    linhaCol(lin2, col2);
    printf("%c", 217);
}

void resetTextColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    CONSOLE_FONT_INFOEX font;
    font.cbSize = sizeof(font);
    font.nFont = 0;
    font.dwFontSize.X = 0;  // Largura da fonte 
    font.dwFontSize.Y = 16; // Altura da fonte 
    font.FontFamily = FF_DONTCARE;
    font.FontWeight = FW_NORMAL;
    wcscpy(font.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
}


int menu(int lin1, int col1, int qtd, char lista[5][40])
{
    int opc = 1, lin2, col2, linha, i, tamMaxItem, tecla;

    tamMaxItem = strlen(lista[0]);
    for (i = 1; i < qtd; i++)
    {
        if (strlen(lista[i]) > tamMaxItem)
        {
            tamMaxItem = strlen(lista[i]);
        }
    }
    lin2 = lin1 + (qtd * 2 + 2);
    col2 = col1 + tamMaxItem + 4;

    box(lin1, col1, lin2, col2);

    while (1)
    {
        linha = lin1 + 2;
        for (i = 0; i < qtd; i++)
        {
            if (i + 1 == opc)
            {
                textColor(RED, BLACK);
            }
            else
            {
                textColor(WHITE, BLACK);
            }
            linhaCol(linha, col1 + 2);
            printf("%s", lista[i]);
            linha += 2;
        }

        linhaCol(1, 1);
        tecla = getch();
        linhaCol(22, 1);
        if (tecla == 27)
        {
            opc = 0; break;
        }
        else if (tecla == 13)
        {
            break;
        }
        else if (tecla == 72)
        {
            if (opc > 1)opc--;
        }
        else if (tecla == 80)
        {
            if (opc < qtd)opc++;
        }
    }
    resetTextColor();
    return opc;
}

struct personagem
{

    char nome[50];
    float forca;
    float agilidade;
    float hp;

}; typedef struct personagem personagem;

struct inimigo
{
    char nome[50];
    float agilidade;
    float hp;
    float forca;
}; typedef struct inimigo inimigo;

struct arma
{
    float dano;
}; typedef struct arma arma;

void delay(int seconds)
{
    int mil = 1000 * seconds;
    clock_t stime = clock();
    while (clock() < stime + mil);
}


void iniciarJogo()
{
    system("cls");
    printf("\nJogando...\n\n");

    int esc;


    printf("\t\t\t\t\t================================\n");
    printf("\t\t\t\t\t=        seja bem vindo        =\n");
    printf("\t\t\t\t\t=              ao              =\n");
    printf("\t\t\t\t\t=         serious game         =\n");
    printf("\t\t\t\t\t================================\n");


    // Solicita o nome do personagem ao jogador
    char nome[50];
    printf("Digite o nome do seu personagem: ");
    fgets(nome, 50, stdin);
    fflush(stdin);

    // Exibe o nome informado pelo jogador
    printf("\n\nSeu personagem se chama: %s\n\n", nome);

    system("pause");
    system("cls");

    // Início da aventura
    printf("Sua jornada comeca agora, %s!\n", nome);
    printf("Prepare se para enfrentar desafios e descobrir segredos incriveis!\n\n");

    printf("Escolha seu personagem:\n\n");

    personagem jogador;
    jogador.forca = 0;
    jogador.agilidade = 0;
    jogador.hp = 0;

    personagem mago;
    mago.forca = 5.0;
    mago.agilidade = 7.0;
    mago.hp = 35.0;

    personagem cavaleiro;
    cavaleiro.forca = 10.0;
    cavaleiro.agilidade = 40.0;
    cavaleiro.hp = 100.0;


    personagem arqueiro;
    arqueiro.forca = 10.0;
    arqueiro.agilidade = 30.0;
    arqueiro.hp = 50.0;

    inimigo natasha;
    natasha.forca = 10.0;
    natasha.hp = 150.0;
    natasha.agilidade = 4.0;
    do
    {
        system("cls"); // Limpa a tela
        printf("1- Mago:\n");
        printf("\033[0;35m"); // Muda a cor para roxo
        printf("           /:\\\n");
        printf("          /;:.\\\n");
        printf("         //;:. \\\n");
        printf("        ///;:.. \\\n");
        printf("  --\"////;:... \\\\\\--\n");
        printf("--__   \"--_--\"   __--\n");
        printf("    \"\"\"--_--\"\"\"\n\n\n");

        printf("Forca do Mago: %.2f\n\nDestreza do Mago: %.1f\n\nhp do Mago: %.1f\n\n\n", mago.forca, mago.agilidade, mago.hp);
        printf("\033[0m"); // Retorna a cor ao normal
        printf("\n2- Cavaleiro:\n");
        printf("\033[0;33m"); // Muda a cor para amarelo
        printf("             />\n");
        printf("            /<\n");
        printf("           /<\n");
        printf(" |\\{o}----------------------------------------------------------\n");
        printf("[\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\{*}:::<=============================================->\n");
        printf(" |/{o}----------------------------------------------------------\n");
        printf("           \\<\n");
        printf("            \\<\n");
        printf("             \\>\n");
        printf("\n\n");

        printf("Forca do Cavaleiro: %.1f\n\nDestreza do Cavaleiro: %.1f\n\nSaude do Cavaleiro: %.1f\n\n\n", cavaleiro.forca, cavaleiro.agilidade, cavaleiro.hp);

        printf("\033[0m"); // Retorna a cor ao normal

        printf("Pressione 'P' 2 vezes para ver a proxima pagina ou pressione 'E' para escolher seu personagem.\n");
        if (getch() == 'o')
        {
            system("cls");
            printf("1- Mago:\n");
            printf("\033[0;35m"); // Muda a cor para roxo
            printf("           /:\\\n");
            printf("          /;:.\\\n");
            printf("         //;:. \\\n");
            printf("        ///;:.. \\\n");
            printf("  --\"////;:... \\\\\\--\n");
            printf("--__   \"--_--\"   __--\n");
            printf("    \"\"\"--_--\"\"\"\n\n\n");

            printf("Forca do Mago: %.2f\n\nDestreza do Mago: %.1f\n\nhp do Mago: %.1f\n\n\n", mago.forca, mago.agilidade, mago.hp);
            printf("\033[0m"); // Retorna a cor ao normal
            printf("\n2- Cavaleiro:\n");
            printf("\033[0;33m"); // Muda a cor para amarelo
            printf("             />\n");
            printf("            /<\n");
            printf("           /<\n");
            printf(" |\\{o}----------------------------------------------------------\n");
            printf("[\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\{*}:::<=============================================->\n");
            printf(" |/{o}----------------------------------------------------------\n");
            printf("           \\<\n");
            printf("            \\<\n");
            printf("             \\>\n");
            printf("\n\n");

            printf("Forca do Cavaleiro: %.1f\n\nDestreza do Cavaleiro: %.1f\n\nSaude do Cavaleiro: %.1f\n\n\n", cavaleiro.forca, cavaleiro.agilidade, cavaleiro.hp);

            printf("\033[0m"); // Retorna a cor ao normal

            printf("Pressione 'P' 2 vezes para ver a proxima pagina ou pressione 'E' 3 vezes para escolher seu personagem.\n");
        }
        else if (getch() == 'p')
        {
            system("cls");
            printf("\n3- Arqueiro:\n\n");
            printf("\033[0;32m"); // muda a cor para verde

            printf("          4$$-.                                          \n");
            printf("           4   \".                                        \n");
            printf("           4    ^\\                                        \n");
            printf("           4     $                                        \n");
            printf("           4     'b                                       \n");
            printf("           4      \"b.                                     \n");
            printf("           4        $                                     \n");
            printf("           4        $r                                    \n");
            printf("           4        $F                                    \n");
            printf("-$b========4========$b====*P=-                           \n");
            printf("           4       *$$F                                   \n");
            printf("           4        $$\"                                   \n");
            printf("           4       .$F                                    \n");
            printf("           4       dP                                     \n");
            printf("           4      F                                       \n");
            printf("           4     @                                        \n");
            printf("           4    .                                         \n");
            printf("           J.                                             \n");
            printf("          '$$                                             \n");


            printf("Forca do Arqueiro: %.1f\n\nAgilidade do Arqueiro: %.1f\n\nSaude do Arqueiro: %.1f\n\n", arqueiro.forca, arqueiro.agilidade, arqueiro.hp);

            printf("\033[0m"); // Retorna a cor ao normal

            printf("Pressione 'O' 1 vez para voltar a pagina anterior ou pressione 'E' uma vez para escolher seu personagem.\n");
        }
    } while (getch() != 'e');
    puts("Escolha sua caracteristica:");
    scanf("%d", &esc);
    printf("\n\n");
    fflush(stdin);

    float balanceamento1, balanceamento2, balanceamento3;

    switch (esc)
    {
    case 1:
        balanceamento1 = 20;
        balanceamento2 = 10;
        balanceamento3 = 5;
        jogador.forca = mago.forca;
        jogador.agilidade = mago.agilidade;
        jogador.hp = mago.hp;
        system("cls");
        printf("Seja bem vindo(a) Mago(a) %s", nome);
        system("pause");
        system("cls");
        break;

    case 2:
        balanceamento1 = 3;
        balanceamento2 = 2;
        balanceamento3 = 1;
        jogador.forca = cavaleiro.forca;
        jogador.agilidade = cavaleiro.agilidade;
        jogador.hp = cavaleiro.hp;
        system("cls");
        printf("Seja bem vindo(a) Cavaleiro(a) %s", nome);
        system("pause");
        system("cls");
        break;

    case 3:
        balanceamento1 = 7;
        balanceamento2 = 4;
        balanceamento3 = 2;
        jogador.forca = arqueiro.forca;
        jogador.agilidade = arqueiro.agilidade;
        jogador.hp = arqueiro.hp;
        system("cls");
        printf("\nSeja bem vindo(a) Arqueiro(a) %s", nome);
        system("pause");
        system("cls");
        break;

    }

    printf("\033[1;36m"); // introduzir cor

    //Introdução
    char texto[] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t  * 8888888888            d8888          .d8888b.          8888888888                  d888 *\n"
        "\t\t\t  * 888                  d88888         d88P  Y88b         888                        d8888 *\n"
        "\t\t\t  * 888                 d88P888         Y88b.              888                          888 *\n"
        "\t\t\t  * 8888888            d88P 888          \"Y888b.           8888888                      888 *\n"
        "\t\t\t  * 888               d88P  888             \"Y88b.         888                          888 *\n"
        "\t\t\t  * 888              d88P   888               \"888         888                          888 *\n"
        "\t\t\t  * 888             d8888888888         Y88b  d88P         888                          888 *\n"
        "\t\t\t  * 888            d88P     888          \"Y8888P\"          8888888888                 8888888 *\n\n";

    for (int i = 0; texto[i] != '\0'; i++)
    {
        putchar(texto[i]);
        fflush(stdout);
        Sleep(1);
        if (kbhit())
        {
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t  * 8888888888            d8888          .d8888b.          8888888888                  d888 *\n"
                "\t\t\t  * 888                  d88888         d88P  Y88b         888                        d8888 *\n"
                "\t\t\t  * 888                 d88P888         Y88b.              888                          888 *\n"
                "\t\t\t  * 8888888            d88P 888          \"Y888b.           8888888                      888 *\n"
                "\t\t\t  * 888               d88P  888             \"Y88b.         888                          888 *\n"
                "\t\t\t  * 888              d88P   888               \"888         888                          888 *\n"
                "\t\t\t  * 888             d8888888888         Y88b  d88P         888                          888 *\n"
                "\t\t\t  * 888            d88P     888          \"Y8888P\"          8888888888                 8888888 *\n\n");
            break;
        }
    }
    printf("\n\t\t\t\t\t\t");
    printf("\033[0m");
    system("pause");

    system("cls");

    printf("Ola %sme chamo Girotto, irei ser seu treinador nesta primeira fase...\n\n", nome);
    printf("Prologo:\n\n");
    printf("Neste prologo sera apresentado uma estrutura basica de um programa em C...\n\n");

    printf("\033[35m#include <stdio.h>\n\n");
    printf("\033[0m\n");
    printf("\033[34mint \033[0m main(){\n\n");
    printf("\033[33m\033[34mreturn\033[0m \033[33m\033[1m0\033[0m;\n}\n");
    printf("\n\n\033[31mObservacao: vamos usar a biblioteca stdio.h pois ela apresenta as funcoes basicas para o que iremos aprender no capitulo 1...");
    printf("\033[0m\n\n");

    system("pause");
    system("cls");

    printf("Capitulo 1:\n");
    printf("Imprimindo dados na Tela:\n\n");
    printf("Para imprimir algo do seu desejo na tela iremos usar uma funcao chamada (printf), sua estrutura segue abaixo:\n\n");
    printf("\033[35m#include <stdio.h>\n\n");
    printf("\033[0m\n");
    printf("\033[34mint \033[0m main(){\n\n");
    printf("\033[0mprintf\033[0;33m('');");
    printf("\033[0m\n\n");
    printf("\033[33m\033[34mreturn\033[0m \033[33m\033[1m0\033[0m;\n}\n");
    printf("\033[31mObservacao: Dentro dos parenteses do printf devera ser acompanhado com aspas duplas, e dentro dos parenteses com as aspas voce pode digitar oq quiser...\n");
    printf("\033[31mNUNCA ESQUECA DE BOTAR (;), no final\n\n");
    printf("\033[0m\n\n");

    system("pause");
    system("cls");


    //construção jogo c;

    printf("Agora vamos comecar:\n\n");

    int opc1;

    printf("Um inimigo quer enfrentar voce:\n\n");
    printf("Voce aceita o desafio:\n1- SIM.\n2- NAO.\n");
    scanf("%d", &opc1);
    printf("\n\n");

    system("pause");
    system("cls");

    int escolha_ataque;
    int resposta;

    if (opc1 == 1)
    {
        printf("Batalha aceita...\n\n");
        printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
            "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
            "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
            "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n",
            nome, natasha.forca,
            jogador.forca, natasha.agilidade,
            jogador.agilidade, natasha.hp,
            jogador.hp);

        printf("\033[0m");
    }
    do
    {

        printf("\n\nSua vez. Ataque:\n");
        printf("\n\nEscolha seu ataque:\n\033[31m1- Ataque forte\n2- Ataque medio\n3- Ataque fraco\n.");
        printf("\033[0m\n\n");
        scanf("%d", &escolha_ataque);
        fflush(stdin);

        system("pause");
        system("cls");


        if (escolha_ataque == 1)
        {
            float ataque_forte = jogador.forca * balanceamento1;

            printf("Voce escolheu o ataque forte..\n\n");

            printf("\nEscolha a opcao correta onde o codigo imprima um hello world na tela:\n\n");
            printf("\033[35m"); // Muda a cor para roxo
            printf("\033[35m1- #include <stdio.h>\n\nint main(){\n\nprintf('hello world');\n\nreturn 0;\n\n}\n\n\n");
            printf("\033[34m2- int main(){\n\nprintf('hello world);;\n\nreturn 0;\n\n}\n\n\n");
            printf("\033[32m3- #include <stdio.h>\n\nint main(){\n\nprintf('hello world')\n\nreturn 0;\n\n}\n\n\n");

            printf("\033[0m"); // Retorna a cor ao normal

            printf("Responda: ");
            scanf("%d", &resposta);
            fflush(stdin);

            if (resposta != 1)
            {
                printf("Resposta errada,..... nem uma ataque efetivo\n");
                printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                    "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                    "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                    "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n",
                    nome, natasha.forca,
                    jogador.forca, natasha.agilidade,
                    jogador.agilidade, natasha.hp,
                    jogador.hp);
                system("pause");


                printf("Vez de NATASHA.EXE atacar:");
                printf("Voce recebera , se prepare para esquivar...\n");//colocar para aparecer aos poucos/
                printf("para voce consegui esquivar precisa sortear um valor a cima de (77%%)\n");
                srand(time(NULL));
                printf("Vez de Natasha.exe:\n");
                printf("Voce esta prestes a receber um ataque, se prepare para desviar...\n");//colocar para aparecer aos poucos/
                printf("Para voce conseguir desviar, voce precisa sortear um valor acima de 77!\n\n");
                srand(time(NULL));

                system("pause");
                system("cls");

                int numeroAleatorio = rand() % 100;
                printf("numero sorteado %d\n", numeroAleatorio);

                if (numeroAleatorio < 77)
                {
                    float ataquenatasha = jogador.hp - natasha.forca;

                    printf("Que pena, NATASHA.exe te atacou...\n\n");

                    printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                        "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                        "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                        "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n\n",
                        nome, natasha.forca,
                        jogador.forca, natasha.agilidade,
                        jogador.agilidade, natasha.hp,
                        ataquenatasha);
                    continue;
                }

                else if (numeroAleatorio > 77)
                {
                    printf("UAU, que sorte... ataque novamente\n\n");

                    printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                        "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                        "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                        "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n",
                        nome, natasha.forca,
                        jogador.forca, natasha.agilidade,
                        jogador.agilidade, natasha.hp,
                        jogador.hp);

                    system("pause");
                    system("cls");
                    continue;
                }
            }

            else if (resposta == 1)
            {
                natasha.hp = natasha.hp - ataque_forte;

                printf("Resposta certa.\n");
                printf("Ataque efetivo.\n\n");
                printf("Voce deu: %.1f de dano!\n", ataque_forte);
                printf("HP Restante de NATASHA.exe: %.1f\n", natasha.hp);
                system("pause");
                printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                    "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                    "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                    "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n",
                    nome, natasha.forca,
                    jogador.forca, natasha.agilidade,
                    jogador.agilidade, natasha.hp,
                    jogador.hp);

                system("pause");
                system("cls");
                printf("Vez de NATASHA.EXE atacar:");
                printf("Voce recebera , se prepare para esquivar...\n");//colocar para aparecer aos poucos/
                printf("para voce consegui esquivar precisa sortear um valor a cima de (77%%)\n");
                srand(time(NULL));
                printf("Vez de Natasha.exe:\n");
                printf("Voce esta prestes a receber um ataque, se prepare para desviar...\n");//colocar para aparecer aos poucos/
                printf("Para voce conseguir desviar, voce precisa sortear um valor acima de 77!\n\n");
                srand(time(NULL));

                system("pause");
                system("cls");

                int numeroAleatorio = rand() % 100;
                printf("numero sorteado %d\n", numeroAleatorio);

                if (numeroAleatorio < 77)
                {
                    float ataquenatasha = jogador.hp - natasha.forca;

                    printf("Que pena, NATASHA.exe te atacou...\n\n");

                    printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                        "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                        "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                        "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n\n",
                        nome, natasha.forca,
                        jogador.forca, natasha.agilidade,
                        jogador.agilidade, natasha.hp,
                        ataquenatasha);
                    continue;
                }

                else if (numeroAleatorio > 77)
                {
                    printf("Uau! Que sorte!\n\n");

                    printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                        "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                        "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                        "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n",
                        nome, natasha.forca,
                        jogador.forca, natasha.agilidade,
                        jogador.agilidade, natasha.hp,
                        jogador.hp);

                    system("pause");
                    system("cls");
                    continue;
                }
            }
        }
        /*se o jogador acertar entao na barra de dados dos persoangens da luta
        ira desaperecer a vida anterior da inimida e ira aparecer aos poucos a nova vida dela apos o dano */

        //colocar isso num while para sair ou retornar dependendo da resposta 

        if (escolha_ataque == 2)
        {
            printf("Voce escolheu o ataque medio...\n\n");
            printf("\nEscolha a opcao correta sobre estrututa basica em C:\n\n");
            printf("\033[35m"); // Muda a cor para roxo
            printf("\033[35m1- #include <stdio.h>\n\nint main(){\n\n\n\nreturn 0;\n\n}\n\n\n");
            printf("\033[34m2- #include <studio.h>\n\nint main(){\n\n\n\nreturn 0;\n\n}\n\n\n");
            printf("\033[32m3- #include <stdio.h\n\nint main(){\n\n\n\nreturn 0\n\n}\n\n\n");

            printf("\033[0m"); // Retorna a cor ao normal

            printf("Responda: ");
            scanf("%d", &resposta);
            fflush(stdin);



            if (resposta == 1)
            {
                float ataque_medio = jogador.forca * balanceamento2;

                natasha.hp = natasha.hp - ataque_medio;

                int valor_aleatorio = 0;
                printf("Resposta certa, ataque medio efetuado");
                printf("Voce deu: %.1f de dano!\n", ataque_medio);
                printf("HP Restante de NATASHA.exe: %.1f\n", natasha.hp);


                printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                    "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                    "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                    "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n",
                    nome, natasha.forca,
                    jogador.forca, natasha.agilidade,
                    jogador.agilidade, natasha.hp,
                    jogador.hp);
                system("pause");
                system("cls");

                printf("Voce esta quase vencendo....\n");
                printf("Vez de Natasha.exe:\n");
                printf("Voce esta prestes a receber um ataque, se prepare para desviar...\n");//colocar para aparecer aos poucos/
                printf("Para voce conseguir desviar, voce precisa sortear um valor acima de 77!\n\n");
                srand(time(NULL));

                system("pause");
                system("cls");

                int numeroAleatorio = rand() % 100;
                printf("Numero sorteado: %d\n", numeroAleatorio);

                if (numeroAleatorio < 77)
                {
                    float ataquenatasha = jogador.hp - natasha.forca;

                    printf("Que pena, NATASHA.exe te atacou...\n\n");

                    printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                        "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                        "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                        "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n\n",
                        nome, natasha.forca,
                        jogador.forca, natasha.agilidade,
                        jogador.agilidade, natasha.hp,
                        ataquenatasha);
                    system("pause");
                    system("cls");
                    continue;
                }

                else if (numeroAleatorio > 77)
                {
                    printf("UAU, que sorte... ataque novamente\n\n");

                    printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                        "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                        "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                        "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n",
                        nome, natasha.forca,
                        jogador.forca, natasha.agilidade,
                        jogador.agilidade, natasha.hp,
                        jogador.hp);

                    system("pause");
                    system("cls");
                    continue;
                }
            }

            if (resposta != 1)
            {
                printf("Resposta errada... Seu ataque falhou!\n");
                printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                    "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                    "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                    "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n",
                    nome, natasha.forca,
                    jogador.forca, natasha.agilidade,
                    jogador.agilidade, natasha.hp,
                    jogador.hp);
                system("pause");
                system("cls");

                printf("Vez de Natasha.exe:\n");
                printf("Voce esta prestes a receber um ataque, se prepare para desviar...\n");//colocar para aparecer aos poucos/
                printf("Para voce conseguir desviar, voce precisa sortear um valor acima de 77!\n\n");
                srand(time(NULL));
                int numeroAleatorio = rand() % 100;
                printf("Numero sorteado: %d\n", numeroAleatorio);

                if (numeroAleatorio < 77)
                {
                    float ataquenatasha = jogador.hp - natasha.forca;

                    printf("Que pena, NATASHA.exe te atacou...\n\n");

                    printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                        "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                        "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                        "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n\n",
                        nome, natasha.forca,
                        jogador.forca, natasha.agilidade,
                        jogador.agilidade, natasha.hp,
                        ataquenatasha);
                    system("pause");
                    system("cls");
                    continue;
                }

                else if (numeroAleatorio > 77)
                {
                    printf("UAU, que sorte... ataque novamente\n\n");

                    printf("\033[0;33mNome do inimigo: NATASHA.EXE\t\t\t\033[0;32mNome de seu personagem: %s\n"
                        "\033[0;33mForca da Natasha: %.1f\t\t\t\t\033[0;32mForca de Seu personagem: %.1f\n"
                        "\033[0;33mDestreza da Natasha: %.1f\t\t\t\033[0;32mDestreza de seu personagem: %.1f\n"
                        "\033[0;33mSaude da Natasha: %.1f\t\t\t\t\033[0;32mSaude de seu personagem: %.1f\n",
                        nome, natasha.forca,
                        jogador.forca, natasha.agilidade,
                        jogador.agilidade, natasha.hp,
                        jogador.hp);

                    system("pause");
                    system("cls");
                    continue;
                }
            }
        }
        /*se o jogador acertar entao na barra de dados dos persoangens da luta
        ira desaperecer a vida anterior da inimida e ira aparecer aos poucos a nova vida dela apos o dano */

        if (escolha_ataque == 3)
        {
            int resposta_ataquef = 0;
            printf("Voce escolheu o ataque fraco...");
            printf("responda uma pergunta basica sobre a funcao de printar na tela\n");
            printf("complete a escrita dessa funcao");
            printf("prin_");
            printf("opcao 1- print();\nopcao 2- printf('');\n opcao 3- print'', \n");
            scanf("%d", resposta_ataquef);
            continue;
        }
        /*se o jogador acertar entao na barra de dados dos persoangens da luta
        ira desaperecer a vida anterior da inimida e ira aparecer aos poucos a nova vida dela apos o dano */


        else if (opc1 == 2)
        {
            printf("Continuando...\n\n");
            delay(2);
            break;
        }

        else
        {
            printf("Opcao invalida. Por favor, escolha 1 para SIM ou 2 para NAO.\n\n");
        }
    } while (natasha.hp > 0);



    char texto1[] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t   _____      _         ____       _____        ____  \n"
        "\t\t\t  |  __|    / \\       / ___|     | ____|      |__ \\ \n"
        "\t\t\t  | |_      / _ \\      \\___ \\     |  _|          __) |\n"
        "\t\t\t  |  |    / ___ \\      ___) |    | |__        / __/ \n"
        "\t\t\t  ||     //   \\\\    |/     ||      |_| \n\n";

    for (int i = 0; texto1[i] != '\0'; i++)
    {
        putchar(texto1[i]);
        fflush(stdout);
        Sleep(1);
        if (kbhit())
        {
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t   _____      _         ____       _____        ____  \n"
                "\t\t\t  |  __|    / \\       / ___|     | ____|      |__ \\ \n"
                "\t\t\t  | |_      / _ \\      \\___ \\     |  _|          __) |\n"
                "\t\t\t  |  |    / ___ \\      ___) |    | |__        / __/ \n"
                "\t\t\t  ||     //   \\\\    |/     ||      |_| \n\n");
            break;
        }
    }
}

// Restante do código

int main()
{
    int i;
    int b;
    b = i + 1;

    for (i = 0; i < b; i++)
    {
        b++;
        delay(1.1);
        system("cls");
        delay(1);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t  ==================================================================\n");
        printf("\t\t\t\t\t\t\t\t\t\t  =                                                                =\n");
        printf("\t\t\t\t\t\t\t\t\t\t  = ____            _                    ____                      =\n");
        printf("\t\t\t\t\t\t\t\t\t\t  =/ __|  ___ _ __() ___  _   _ ___   / ___| __ _ _ __ ___   ___ =\n");
        printf("\t\t\t\t\t\t\t\t\t\t  =\\___ \\ / _ \\ '| |/ _ \\| | | / _| | |  _ / _` | ' ` _ \\ / _ \\=\n");
        printf("\t\t\t\t\t\t\t\t\t\t  = __) |  __/ |  | | () | || \\_ \\ | || | (| | | | | | |  __/=\n");
        printf("\t\t\t\t\t\t\t\t\t\t  =|/ \\||  ||\\/ \\,|/  \\|\\,|| || ||\\_|=\n");
        printf("\t\t\t\t\t\t\t\t\t\t  =                                                                =\n");
        printf("\t\t\t\t\t\t\t\t\t\t  ==================================================================\n\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t    Pressione espaco para comecar!\n", i + 1);
        if (kbhit())
        {
            break;
        }
    }

    system("cls");

    int opc;
    char lista[5][40] = { "Jogar", "Tutorial", "Historia", "Desenvolvedores", "exit" };
    while (true)
    {
        opc = menu(10, 10, 5, lista);
        if (opc == 0)
        {
            break;
        }
        switch (opc)
        {




        case 1:

            iniciarJogo();

            system("pause");
            system("cls");
            break;

        case 2:
            system("cls");
            printf("\nVisualizando tutorial...\n\n");

            printf("Para imprimir algo do seu desejo na tela iremos usar uma funcao chamada (printf), sua estrutura segue abaixo:\n\n");
            printf("#include <stdio.h>\n\n");
            printf("int main(){\n");
            printf("\nprintf("");\n");
            printf("\nreturn 0;\n}\n\n");
            printf("Observacao: Dentro dos parenteses do printf devera ser acompanhado com aspas duplas, e dentro dos parenteses com as aspas voce pode digitar oq quiser...\n");
            printf("\n\nNUNCA ESQUECA DE BOTAR (;), no final\n\n");
            system("pause");
            system("cls");
            break;

        case 3:
            system("cls");
            printf("Voce e um Engenheiro da computacao, e esta em um mundo de cheio hackers e misterios.\n");
            printf("Sua jornada comeca em uma pequena vila chamada Villageburg.\n");
            printf("Voce e um heroi destinado a salvar o mundo das trevas que o ameacam.\n\n");

            printf("Ao explorar Villageburg, voce descobre que a vila esta sofrendo com um terrivel malwere.\n");
            printf("Os habitantes estao desaparecendo misteriosamente durante a noite, e uma aura de medo paira sobre o lugar.\n");
            printf("Determinado a ajudar, voce decide investigar a origem desse malwere e encontrar uma maneira de quebra-lo.\n\n");

            printf("Enquanto investiga, voce encontra pistas que levam a uma antiga masmorra nas proximidades, conhecida como a Caverna dos Espiritos.\n");
            printf("Diz a lenda que a caverna eh habitada por hackers malignos que sao responsaveis pelo malwere que assola Villageburg.\n");
            printf("Determinado a enfrentar esse desafio, voce se prepara para entrar na caverna e enfrentar os perigos que a aguardam.\n\n");

            printf("Dentro da caverna, voce enfrenta hackers sombrios e virus.exe mortais, mas sua coragem e determinacao o mantem firme.\n");
            printf("Finalmente, voce chega a camara central, onde encontra o lider dos hackers, um ser poderoso e sinistro.\n");
            printf("Uma batalha epica se inicia, e voce luta com todas as suas forcas para derrotar o mal que ameaca Villageburg.\n\n");

            printf("Com um golpe final, voce derrota o lider dos hackers e quebra o malwere que assolava a vila.\n");
            printf("Os habitantes de Villageburg estao livres do medo e da escuridao, e eles o aclamam como seu salvador e heroi.\n");
            printf("Sua jornada esta apenas comecando, e muitas aventuras e desafios ainda aguardam voce neste mundo magico e cheio de misterios.\n");

            system("pause");
            system("cls");
            break;

        case 4:
            system("cls");
            printf("Desenvolvedores: \n\n");
            printf("\t\t\t\t\t================================\n");
            printf("\t\t\t\t\t=     Ramon Silva de souza     =\n");
            printf("\t\t\t\t\t=             and              =\n");
            printf("\t\t\t\t\t=       Joao Pedro Silva       =\n");
            printf("\t\t\t\t\t=             and              =\n");
            printf("\t\t\t\t\t=       Joao Pedro Maues       =\n");
            printf("\t\t\t\t\t================================\n");

            system("pause");
            system("cls");
            break;

        case 5:
            system("cls");
            printf("\nSaindo...");
            return 0;
        default:
            printf("\nSaindo...");
        }
    }
    textColor(WHITE, _BLACK);
    linhaCol(24, 1);
    printf("");
    return 0;
}