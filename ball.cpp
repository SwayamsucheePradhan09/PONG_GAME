#include "ball.h" // Include our blueprint

// Constructor sets up the ball's initial state
Ball::Ball() {
    ballShape.setFillColor(Color::White); // Set ball color to white
    ballShape.setRadius(40); // Set the radius of the ball to 40 pixels
    
    pos_x = 60 + rand() % 1870; // Spawn ball at a random horizontal position
    pos_y = 60; // Spawn ball near the top of the screen
    ballShape.setPosition(pos_x, pos_y); // Apply the starting coordinates
    
    moveY = 1; // Start moving downwards
    moveX = 1; // Start moving to the right
    ballSpeed = 5; // Base speed
    
    // Calculate pixels per second to ensure smooth movement regardless of framerate
    ballPixelPerSecX = 1980 / ballSpeed; 
    ballPixelPerSecy = 1020 / ballSpeed; 
}

// Returns the shape to the main game loop for drawing
CircleShape Ball::returnShape() {
    return(ballShape);
}

// Updates the ball's position every frame
void Ball::upadteBall(Time &dt) {
    float x = ballShape.getPosition().x; // Get current X
    float y = ballShape.getPosition().y; // Get current Y   
    // Move the ball based on direction, time passed, and speed
    x = x + moveX * dt.asSeconds() * ballPixelPerSecX;
    y = y + moveY * dt.asSeconds() * ballPixelPerSecy;
    ballShape.setPosition(x, y); // Apply new position
}

// Reverses horizontal direction if it hits the right wall (Assuming 1980 is screen width)
void Ball::ballBounceRight() {
    if(ballShape.getPosition().x > 1900)
        moveX = -1; // Change direction to Left
}

// Reverses horizontal direction if it hits the left wall
void Ball::ballBounceLeft() {
    if(ballShape.getPosition().x < 0)
        moveX = 1; // Change direction to Right
}

// Handles bouncing off the ceiling and increasing the player's score
void Ball::ballBounceTop(int &score, bool &incScore) {
    if(ballShape.getPosition().y < 0) {
        moveY = 1; // Change direction to Down
        if(incScore) {
            score = score + 1; // Increase score only if bat was hit
            incScore = false; // Reset scoring flag until next bat hit
        }
    }
}
void Ball::ballBounceBottom(bool &incScore, int &live) {
    if(ballShape.getPosition().y > 940) {
        moveY = -1; // Bounce it back up
        if (!incScore) {
            live = live - 1; // Player loses a life (ball missed by bat)
        }
        incScore = false; // Reset flag - ball must hit bat again to score
        // Reset ball to a starting position
        pos_x = 60 + rand() % 1870;
        pos_y = 60;
        ballShape.setPosition(pos_x, pos_y);
        moveX = (rand() % 2 == 0) ? 1 : -1; // Random horizontal direction
    }
}
// Handles collision with the bat
void Ball::ballTochesBat(FloatRect batBound, bool &incScore) {
    if(ballShape.getGlobalBounds().intersects(batBound) && !incScore) {
        moveY = -1; // Bounce upwards
        incScore = true; // Allow the player to score on the next top bounce
    }
}
