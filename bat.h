#include <SFML/Graphics.hpp>

using namespace sf;

class Bat {
private:
    RectangleShape batShape; // Visual representation of the paddle
    float batSpeed;          // Base speed of the bat
    float batPixelPerSec;    // Speed calculation for smooth movement

public:
    Bat(); // Constructor to initialize the bat
    void moveLeft(Time &dt);  // Function to move the bat left
    void moveRight(Time &dt); // Function to move the bat right
    RectangleShape returnShape(); // Function to pass the shape for drawing
};
