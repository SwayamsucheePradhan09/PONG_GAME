#pragma once
#include <SFML/Graphics.hpp>

class Bat {
private:
    sf::RectangleShape batShape; // Visual representation of the paddle
    float batSpeed;              // Base speed of the bat
    float batPixelPerSec;        // Speed calculation for smooth movement

public:
    Bat(); // Constructor to initialize the bat
    void moveLeft(sf::Time &dt);  // Function to move the bat left
    void moveRight(sf::Time &dt); // Function to move the bat right
    sf::RectangleShape returnShape(); // Function to pass the shape for drawing
};
