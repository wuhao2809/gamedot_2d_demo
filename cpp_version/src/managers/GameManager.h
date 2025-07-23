#pragma once

class GameManager {
public:
    enum GameState { MENU, PLAYING, GAME_OVER };
    
    GameState currentState = MENU;
    int score = 0;
    float gameTime = 0.0f;
    
    // Screen bounds
    float screenWidth = 480;
    float screenHeight = 720;
    
    // Game settings (will be loaded from JSON later)
    float mobSpawnInterval = 0.5f;
    float scorePerSecond = 10.0f;
    
    void reset() {
        score = 0;
        gameTime = 0.0f;
        currentState = MENU;
    }
    
    void startGame() {
        currentState = PLAYING;
        score = 0;
        gameTime = 0.0f;
    }
    
    void gameOver() {
        currentState = GAME_OVER;
    }
    
    void updateGameTime(float deltaTime) {
        if (currentState == PLAYING) {
            gameTime += deltaTime;
            score += static_cast<int>(scorePerSecond * deltaTime);
        }
    }
};
