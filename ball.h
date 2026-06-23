#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib> // For rand()

class Ball {
private:
    sf::CircleShape ballShape; // The visual representation of the ball
    float pos_x, pos_y;       // Coordinates for the ball's current position
    float ballSpeed;           // Base speed multiplier for the ball
    float ballPixelPerSecX;    // Speed of the ball on the horizontal (X) axis
    float ballPixelPerSecy;    // Speed of the ball on the vertical (Y) axis
    int moveX; // Direction multiplier for X-axis (1 = Right, -1 = Left)
    int moveY; // Direction multiplier for Y-axis (1 = Down, -1 = Up)

public:
    Ball();  // Constructor: Initializes the ball when created

    sf::CircleShape returnShape(); // Returns the ball's shape so it can be drawn

    void upadteBall(sf::Time &dt); // Moves the ball based on elapsed time (Delta Time)

    // Collision handler functions
    void ballBounceRight();
    void ballBounceLeft();
    void ballBounceTop(int &score, bool &incScore); // Handles top bounce and scoring
    void ballBounceBottom(bool &incScore, int &live); // Handles bottom bounce (losing a life)
    void ballTochesBat(sf::FloatRect batBound, bool &incScore); // Handles bouncing off the player's bat
};