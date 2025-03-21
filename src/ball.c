#include "ball.h"
#include "racket.h"
#include "ai.h"
#include "game.h"
#include <math.h>

Ball ball;

// Previous positions for tracking movement
float racket_prev_y = 0;
float ai_prev_y = 0;

// Constants for ball physics
#define MAX_BALL_SPEED 10.0f
#define MIN_BALL_SPEED 5.0f
#define MAX_ANGLE_FACTOR 0.8f

void ballInit() {
    ball.radius = 7;
    ball.x = 400;
    ball.y = 300;
    ball.vx = 5;
    ball.vy = 5;
    
    // Initialize previous positions
    racket_prev_y = racket.y;
    ai_prev_y = ai.y;
}

void ballRender(SDL_Renderer *renderer, int cx, int cy, int radius){
    for(int y = cy - radius; y <= cy + radius; y++){
        for(int x = cx - radius; x <= cx + radius; x++){
            int dx = x - cx;
            int dy = y - cy;
            if((dx * dx + dy * dy) <= (radius * radius)){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

// Helper function to calculate speed from velocity components
float calculateSpeed(float vx, float vy) {
    return sqrtf(vx * vx + vy * vy);
}

void ballMove(){
    // Update ball position
    ball.x += ball.vx;
    ball.y += ball.vy;
    
    // Check for collisions
    ballCollisionRacket();
    ballCollisionAi();
    ballCollisionWall();
    
    // Update previous positions for next frame
    racket_prev_y = racket.y;
    ai_prev_y = ai.y;
}

void ballCollisionRacket(){
    if(ball.x + ball.radius >= racket.x && 
       ball.x - ball.radius <= racket.x + racket.width && 
       ball.y + ball.radius >= racket.y && 
       ball.y - ball.radius <= racket.y + racket.height)
    {
        // Calculate where on the racket the ball hit (0.0 = top, 1.0 = bottom)
        float hitPosition = (ball.y - racket.y) / racket.height;
        
        // Constrain between 0 and 1
        if(hitPosition < 0.0f) hitPosition = 0.0f;
        if(hitPosition > 1.0f) hitPosition = 1.0f;
        
        // Convert to angle factor (-MAX_ANGLE_FACTOR to +MAX_ANGLE_FACTOR)
        float angleFactor = (hitPosition - 0.5f) * 2.0f * MAX_ANGLE_FACTOR;
        
        // Calculate racket movement since last frame
        float racketMovement = racket.y - racket_prev_y;
        
        // Current ball speed
        float currentSpeed = calculateSpeed(ball.vx, ball.vy);
        
        // Add a bit of speed based on racket movement
        currentSpeed += fabsf(racketMovement) * 0.1f;
        
        // Clamp speed
        if(currentSpeed > MAX_BALL_SPEED) currentSpeed = MAX_BALL_SPEED;
        if(currentSpeed < MIN_BALL_SPEED) currentSpeed = MIN_BALL_SPEED;
        
        // Reverse x direction
        ball.vx = -ball.vx;
        
        // Make sure ball moves away from racket
        if(ball.vx < 0) ball.vx = -fabsf(ball.vx);
        
        // Adjust y velocity based on hit position
        ball.vy = ball.vy + (angleFactor * currentSpeed);
        
        // Add some of the racket's movement to the ball's vertical velocity
        ball.vy += racketMovement * 0.4f;
        
        // Normalize velocity vector to maintain consistent speed
        float newSpeed = calculateSpeed(ball.vx, ball.vy);
        ball.vx = (ball.vx / newSpeed) * currentSpeed;
        ball.vy = (ball.vy / newSpeed) * currentSpeed;
        
        // Prevent ball from getting stuck in the racket
        ball.x = racket.x + racket.width + ball.radius + 1;
    }
}

void ballCollisionAi(){
    if(ball.x + ball.radius >= ai.x && 
       ball.x - ball.radius <= ai.x + ai.width && 
       ball.y + ball.radius >= ai.y && 
       ball.y - ball.radius <= ai.y + ai.height)
    {
        // Calculate where on the AI racket the ball hit (0.0 = top, 1.0 = bottom)
        float hitPosition = (ball.y - ai.y) / ai.height;
        
        // Constrain between 0 and 1
        if(hitPosition < 0.0f) hitPosition = 0.0f;
        if(hitPosition > 1.0f) hitPosition = 1.0f;
        
        // Convert to angle factor (-MAX_ANGLE_FACTOR to +MAX_ANGLE_FACTOR)
        float angleFactor = (hitPosition - 0.5f) * 2.0f * MAX_ANGLE_FACTOR;
        
        // Calculate AI racket movement since last frame
        float aiMovement = ai.y - ai_prev_y;
        
        // Current ball speed
        float currentSpeed = calculateSpeed(ball.vx, ball.vy);
        
        // Add a bit of speed based on AI racket movement
        currentSpeed += fabsf(aiMovement) * 0.1f;
        
        // Clamp speed
        if(currentSpeed > MAX_BALL_SPEED) currentSpeed = MAX_BALL_SPEED;
        if(currentSpeed < MIN_BALL_SPEED) currentSpeed = MIN_BALL_SPEED;
        
        // Reverse x direction
        ball.vx = -ball.vx;
        
        // Make sure ball moves away from AI racket
        if(ball.vx > 0) ball.vx = fabsf(ball.vx);
        
        // Adjust y velocity based on hit position
        ball.vy = ball.vy + (angleFactor * currentSpeed);
        
        // Add some of the AI's movement to the ball's vertical velocity
        ball.vy += aiMovement * 0.4f;
        
        // Normalize velocity vector to maintain consistent speed
        float newSpeed = calculateSpeed(ball.vx, ball.vy);
        ball.vx = (ball.vx / newSpeed) * currentSpeed;
        ball.vy = (ball.vy / newSpeed) * currentSpeed;
        
        // Prevent ball from getting stuck in the AI racket
        ball.x = ai.x - ball.radius - 1;
    }
}

void ballResetPos(){
    ball.x = 400;
    ball.y = 300;
    ball.vx = 5;
}

void ballCollisionWall(){
    // Top and bottom walls
	if(ball.y >= 600 - ball.radius || ball.y <= 0 + ball.radius){
        ball.vy = -ball.vy;
    }
    
    // Left and right walls (scoring)
    if(ball.x >= 800 - ball.radius || ball.x <= 0 + ball.radius){
        SDL_Delay(500);
        ballResetPos();
        game.score += 1;
        ball.vy += 2;
        
        // Increase difficulty - using fixed values instead of MAX_SPEED
        if(racket.speed < 10.0f) {
            racket.speed += 0.5f;
        }
        if(ai.speed < 10.0f) {
            ai.speed += 0.5f;
        }
    }
}

/* 
#include "ball.h"
#include "racket.h"
#include "ai.h"
#include "game.h"

Ball ball;

void ballInit() {
	ball.radius = 7;
	ball.x = 400;
	ball.y = 300;
	ball.vx = 5;
	ball.vy = 5;
}

void ballRender(SDL_Renderer *renderer, int cx, int cy, int radius){
	for(int y = cy - radius; y <= cy + radius; y++){
		for(int x = cx - radius; x <= cx + radius; x++){
			int dx = x - cx;
			int dy = y - cy;
			if((dx * dx + dy * dy) <= (radius * radius)){
				SDL_SetRenderDrawColor(renderer, 255,255,255,255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
	}
}

void ballMove(){
	ball.x += ball.vx;
	ball.y += ball.vy;
	ballCollisionRacket();
	ballCollisionAi();
	ballCollisionWall();
	if(ball.x >= 800 - ball.radius || ball.x <= 0 + ball.radius){
		ball.vx = -ball.vx;
	}
	if(ball.y >= 600 - ball.radius || ball.y <= 0 + ball.radius){
		ball.vy = -ball.vy;
	}
}

void ballCollisionRacket(){
	if(ball.x + ball.radius >= racket.x && ball.x - ball.radius <= racket.x + racket.width && ball.y + ball.radius >= racket.y && ball.y - ball.radius <= racket.y + racket.height){
		ball.vx = -ball.vx;
	}
}

void ballCollisionAi(){
	if(ball.x + ball.radius >= ai.x && ball.x - ball.radius <= ai.x + ai.width && ball.y + ball.radius >= ai.y && ball.y - ball.radius <= ai.y + ai.height){
		ball.vx = -ball.vx;
	}
}

void ballResetPos(){
	ball.x = 400;
	ball.y = 300;
	ball.vx = 5;
}

void ballCollisionWall(){
	if(ball.x >= 800 - ball.radius || ball.x <= 0 + ball.radius){
		SDL_Delay(500);
		ballResetPos();
		game.score+=1;
		ball.vy+=2;
		racket.speed++;
		ai.speed++;
	}
}

*/
