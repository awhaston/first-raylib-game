#include "raylib.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 450 
#define WIDTH 800 
#define FPS 60

typedef struct {
    int speed;
    Rectangle rect;
} player;

void init_player(player *player){
    player->speed = 10;
    Rectangle rect = {40, 40, 40, 60};
    player->rect = rect;

}

void draw_player(player *player) {
    DrawRectangle(player->rect.x, player->rect.y, player->rect.width, player->rect.height, WHITE);
}

void move_player(player *player) {
    if (IsKeyDown(KEY_RIGHT)) {
        if (player->rect.x + player->speed > WIDTH) player->rect.x = 0;
        else player->rect.x += player->speed;
    } else if (IsKeyDown(KEY_LEFT)) {
        if (player->rect.x - player->speed < 0) player->rect.x = WIDTH - player->rect.width;
        else player->rect.x -= player->speed;
    }
    // Put an else if we only want the player to move in one direction at a time
    if (IsKeyDown(KEY_UP)) {
        if (player->rect.y - player->speed < 0) player->rect.y = HEIGHT - player->rect.height;
        else player->rect.y -= player->speed;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        if (player->rect.y + player->speed > HEIGHT) player->rect.y = 0;
        else player->rect.y += player->speed;
    }
}

void reset_player(player *player){
    player->rect.y = (float) HEIGHT / 2;
    player->rect.x = (float) WIDTH / 2;
}

typedef struct {
    Rectangle rect;
} coin;

void init_coin(coin *coin) {
    Rectangle rect = {10, 10, 10, 10};
    coin->rect = rect;
}

void reposition_coin(coin *coin) {
    int random = rand();
    coin->rect.y = random % HEIGHT;
    coin->rect.x = random % WIDTH;
}

int detect_collision(player *player, coin *coin){
    if (CheckCollisionRecs(player->rect, coin->rect)){
        return 1;
    } else {
        return 0;
    }
}

void draw_coin(coin *coin){
    DrawRectangle(coin->rect.x, coin->rect.y, coin->rect.width, coin->rect.height, YELLOW);
}


int main(void) {
  InitWindow(WIDTH, HEIGHT, "raylib [core] example - basic window");


  SetTargetFPS(FPS);

  player player;
  coin coin;
  int score = 0;
  char scoreText[100] = "Score: 0";

  init_player(&player);
  init_coin(&coin);

  InitAudioDevice();

  Sound coin_sound = LoadSound("./resources/coin.wav");

  while (!WindowShouldClose()) {
    // UPDATE
    move_player(&player);

    if(detect_collision(&player, &coin)) {
        score++;
        reposition_coin(&coin);
        PlaySound(coin_sound);

        reset_player(&player);
        snprintf(scoreText, 100, "Score: %i", score);
    }


    // DRAWING
    BeginDrawing();
        ClearBackground(BLACK);

        DrawText(scoreText, WIDTH / 2 - 50, HEIGHT / 3, 20, LIGHTGRAY);
        draw_player(&player);
        draw_coin(&coin);
    EndDrawing();
  }

  CloseWindow();
  CloseAudioDevice();

  return 0;
}
