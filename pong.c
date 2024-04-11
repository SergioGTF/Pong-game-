#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 60;
const int BALL_SIZE = 10;

enum GameState {
    MENU,
    MODE_SELECTION,
    PLAYING,
    TUTORIAL,
    EXIT
};

enum GameMode {
    PLAYER_VS_PLAYER,
    PLAYER_VS_AI
};

void close_game(bool* doexit, int* gameState) {
    *doexit = true;
    *gameState = EXIT;
}

int main() {
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_FONT* font = NULL;

    bool key[ALLEGRO_KEY_MAX] = { false };
    bool redraw = true;
    bool doexit = false;
    bool pause = false; // Variável para controlar a pausa

    float paddle1_y = SCREEN_HEIGHT / 2.0 - PADDLE_HEIGHT / 2.0;
    float paddle2_y = SCREEN_HEIGHT / 2.0 - PADDLE_HEIGHT / 2.0;
    float ball_x = SCREEN_WIDTH / 2.0 - BALL_SIZE / 2.0;
    float ball_y = SCREEN_HEIGHT / 2.0 - BALL_SIZE / 2.0;
    float ball_dx = -5.0, ball_dy = 5.0;

    int player1_score = 0;
    int player2_score = 0;

    int gameState = MENU;
    int gameMode = PLAYER_VS_PLAYER; // Modo padrão: jogador vs jogador

    if (!al_init()) {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        fprintf(stderr, "Falha ao criar o display.\n");
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Falha ao criar a fila de eventos.\n");
        al_destroy_display(display);
        return -1;
    }

    timer = al_create_timer(1.0 / 60.0);
    if (!timer) {
        fprintf(stderr, "Falha ao criar o temporizador.\n");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return -1;
    }

    if (!al_init_font_addon()) {
        fprintf(stderr, "Falha ao inicializar o addon de fonte.\n");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        return -1;
    }

    font = al_create_builtin_font();
    if (!font) {
        fprintf(stderr, "Falha ao carregar a fonte.\n");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        return -1;
    }

    al_install_keyboard();
    al_init_primitives_addon();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);

    while (!doexit) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (!pause && gameState == PLAYING) { // Verifica se o jogo não está pausado
                // Lógica do jogo aqui
                if (key[ALLEGRO_KEY_W]) {
                    paddle1_y -= 10.0;
                }
                if (key[ALLEGRO_KEY_S]) {
                    paddle1_y += 10.0;
                }
                if (gameMode == PLAYER_VS_PLAYER) {
                    if (key[ALLEGRO_KEY_UP]) {
                        paddle2_y -= 10.0;
                    }
                    if (key[ALLEGRO_KEY_DOWN]) {
                        paddle2_y += 10.0;
                    }
                }
                else if (gameMode == PLAYER_VS_AI) {
                    // Ajuste da velocidade de reação da IA
                    float ai_speed = 5.0;

                    // Refinamento da previsão da bola
                    float future_ball_y = ball_y + ball_dy * ((SCREEN_WIDTH - PADDLE_WIDTH - ball_x) / ball_dx);

                    // Implementação de estratégias de defesa e ataque
                    float target_y;
                    if (future_ball_y > paddle2_y + PADDLE_HEIGHT / 2) {
                        target_y = paddle2_y + ai_speed; // Defesa
                    }
                    else if (future_ball_y < paddle2_y + PADDLE_HEIGHT / 2) {
                        target_y = paddle2_y - ai_speed; // Defesa
                    }
                    else {
                        target_y = paddle2_y; // Ataque
                    }

                    // Introdução de aleatoriedade
                    target_y += rand() % 21 - 10; // Adiciona uma variação aleatória de -10 a 10

                    // Limita o movimento da raquete da IA dentro dos limites da tela
                    if (target_y < 0) {
                        target_y = 0;
                    }
                    else if (target_y + PADDLE_HEIGHT > SCREEN_HEIGHT) {
                        target_y = SCREEN_HEIGHT - PADDLE_HEIGHT;
                    }

                    // Movimento suave da raquete da IA em direção à posição alvo
                    if (paddle2_y < target_y) {
                        paddle2_y += ai_speed; // Move para baixo
                    }
                    else if (paddle2_y > target_y) {
                        paddle2_y -= ai_speed; // Move para cima
                    }
                }

                ball_x += ball_dx;
                ball_y += ball_dy;

                // Verifica se a raquete atingiu o limite superior ou inferior do display
                if (paddle1_y < 0) {
                    paddle1_y = 0;
                }
                else if (paddle1_y + PADDLE_HEIGHT > SCREEN_HEIGHT) {
                    paddle1_y = SCREEN_HEIGHT - PADDLE_HEIGHT;
                }

                if (paddle2_y < 0) {
                    paddle2_y = 0;
                }
                else if (paddle2_y + PADDLE_HEIGHT > SCREEN_HEIGHT) {
                    paddle2_y = SCREEN_HEIGHT - PADDLE_HEIGHT;
                }

                // Colisão com as paredes
                if (ball_y < 0 || ball_y > SCREEN_HEIGHT - BALL_SIZE) {
                    ball_dy = -ball_dy;
                }

                // Colisão com as raquetes
                if (ball_x <= PADDLE_WIDTH && ball_y >= paddle1_y && ball_y <= paddle1_y + PADDLE_HEIGHT) {
                    ball_dx = -ball_dx;
                }
                if (ball_x >= SCREEN_WIDTH - PADDLE_WIDTH - BALL_SIZE && ball_y >= paddle2_y && ball_y <= paddle2_y + PADDLE_HEIGHT) {
                    ball_dx = -ball_dx;
                }
                // Resetar a bola se sair pela esquerda ou direita
                if (ball_x < 0) {
                    ball_x = SCREEN_WIDTH / 2.0 - BALL_SIZE / 2.0;
                    ball_y = SCREEN_HEIGHT / 2.0 - BALL_SIZE / 2.0;
                    player2_score++;
                }
                if (ball_x > SCREEN_WIDTH - BALL_SIZE) {
                    ball_x = SCREEN_WIDTH / 2.0 - BALL_SIZE / 2.0;
                    ball_y = SCREEN_HEIGHT / 2.0 - BALL_SIZE / 2.0;
                    player1_score++;
                }
            }
            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_W:
                key[ALLEGRO_KEY_W] = true;
                break;
            case ALLEGRO_KEY_S:
                key[ALLEGRO_KEY_S] = true;
                break;
            case ALLEGRO_KEY_UP:
                key[ALLEGRO_KEY_UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                key[ALLEGRO_KEY_DOWN] = true;
                break;
            case ALLEGRO_KEY_P: // Tecla P para pausar o jogo
                if (gameState == PLAYING) {
                    pause = !pause; // Inverte o estado de pausa
                }
                break;
            case ALLEGRO_KEY_1:
                if (gameState == MENU) {
                    gameState = MODE_SELECTION;
                }
                break;
            case ALLEGRO_KEY_2:
                if (gameState == MODE_SELECTION) {
                    gameMode = PLAYER_VS_AI;
                    gameState = PLAYING;
                }
                break;
            case ALLEGRO_KEY_3:
                if (gameState == MENU || gameState == MODE_SELECTION) {
                    doexit = true; // Encerra o programa
                }
                break;
            case ALLEGRO_KEY_4:
                if (gameState == MENU) {
                    gameState = TUTORIAL;
                }
                break;
            case ALLEGRO_KEY_5:
                if (gameState == MENU) {
                    doexit = true; // Encerra o programa
                }
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_W:
                key[ALLEGRO_KEY_W] = false;
                break;
            case ALLEGRO_KEY_S:
                key[ALLEGRO_KEY_S] = false;
                break;
            case ALLEGRO_KEY_UP:
                key[ALLEGRO_KEY_UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                key[ALLEGRO_KEY_DOWN] = false;
                break;
            }
        }

        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            doexit = true;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Desenha as raquetes e a bola
            if (gameState == PLAYING) {
                al_draw_filled_rectangle(0, paddle1_y, PADDLE_WIDTH, paddle1_y + PADDLE_HEIGHT, al_map_rgb(255, 255, 255));
                al_draw_filled_rectangle(SCREEN_WIDTH - PADDLE_WIDTH, paddle2_y, SCREEN_WIDTH, paddle2_y + PADDLE_HEIGHT, al_map_rgb(255, 255, 255));
                al_draw_filled_circle(ball_x, ball_y, BALL_SIZE / 2, al_map_rgb(255, 255, 255));

                // Desenha a pontuação dos jogadores
                char player1_score_str[15];
                char player2_score_str[15];
                snprintf(player1_score_str, sizeof(player1_score_str), "Player 1: %d", player1_score);
                snprintf(player2_score_str, sizeof(player2_score_str), "Player 2: %d", player2_score);
                al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, player1_score_str);
                al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH - 10, 10, ALLEGRO_ALIGN_RIGHT, player2_score_str);

                // Desenha mensagem de pausa se o jogo estiver pausado
                if (pause) {
                    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "PAUSADO");
                }
            }

            // Desenha o nome do jogo
            al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 20, ALLEGRO_ALIGN_CENTER, "Pong's Game");

            // Desenha o menu
            if (gameState == MENU) {
                al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 80, ALLEGRO_ALIGN_CENTER, "MENU");
                al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40, ALLEGRO_ALIGN_CENTER, "1. Selecionar Modo");
                al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "2. Tutorial");
                al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40, ALLEGRO_ALIGN_CENTER, "3. Sair");
            }
            // Desenha o menu de seleção de modo
            else if (gameState == MODE_SELECTION) {
                al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40, ALLEGRO_ALIGN_CENTER, "SELECIONAR MODO");
                al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "2. Jogar contra IA");
                al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40, ALLEGRO_ALIGN_CENTER, "3. Jogar contra outro jogador");
            }

            // Desenha o tutorial
            else if (gameState == TUTORIAL) {
                al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40, ALLEGRO_ALIGN_CENTER, "TUTORIAL");
                // Adicione instruções de jogo aqui
            }
            al_flip_display();
        }
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}
