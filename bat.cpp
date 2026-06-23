#include "bat.h" // Include the bat blueprint

using namespace sf;

// Constructor sets the initial size, color, and position of the bat
Bat::Bat() {
    batShape.setFillColor(Color::White); // Make it white
    batShape.setSize(Vector2f(400, 10)); // Set width to 400 and height to 10 pixels
    
    // Position it horizontally centered and near the bottom of the screen
    batShape.setPosition(1980 / 2.0f - 200, 1020 - 40); 
    
    batSpeed = 5; // Base speed
    batPixelPerSec = 1980 / batSpeed; // Calculate movement speed per second
}

// Moves the bat left based on frame time
void Bat::moveLeft(Time &dt) {
    float x = batShape.getPosition().x;
    float y = batShape.getPosition().y;
    
    x = x - (batPixelPerSec * dt.asSeconds()); // Calculate new X position
    
    if (x < 0) {
        x = 0; // Prevent the bat from moving past the left edge of the screen
    }
    
    batShape.setPosition(x, y); // Apply new position
}

// Moves the bat right based on frame time
void Bat::moveRight(Time &dt) {
    float x = batShape.getPosition().x;
    float y = batShape.getPosition().y;  
    x = x + (batPixelPerSec * dt.asSeconds()); // Calculate new X position
    
    if (x > 1580) { // 1980 (screen width) - 400 (bat width) = 1580
        x = 1580; // Prevent the bat from moving past the right edge
    }
    
    batShape.setPosition(x, y); // Apply new position
}
// Returns the bat's shape for drawing
RectangleShape Bat::returnShape() {
    return batShape;
}
