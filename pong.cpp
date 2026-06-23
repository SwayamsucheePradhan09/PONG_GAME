#include <SFML/Graphics.hpp>
#include <sstream> // Needed to convert integers (score) to strings for text
#include <cstdlib> // For rand()
#include "bat.h"   // Include the bat header
#include "ball.h"  // Include the ball header

using namespace std;
using namespace sf;

int main() {
    // 1. Setup Window and View
    VideoMode vm(1980, 1020); // Creates an 800x600 window
    RenderWindow window(vm, "Pong Game!!!"); 
    
    // Creates a "camera" view mapped to a 1980x1020 resolution. 
    // This scales the large coordinates used in your objects to fit the 800x600 window.
    View vw(FloatRect(0, 0, 1980, 1020)); 
    window.setView(vw);
   // 2. Setup Game State Variables
    bool paused = false;
    bool gameOver = false;
    bool acceptInput = true;
    int lives = 3;
    int score = 0;
    bool incScore = false; // Flag to manage when points can be scored

    // 3. Setup Text & Fonts
    Text livesText, scoreText, messageText;
    Font ft;
  
    // IMPORTANT: Make sure the "KOMIKAP_.ttf" file is in your assets folder/working directory!
    ft.loadFromFile("font/KOMIKAP_.ttf"); 
    
    scoreText.setFont(ft);
    scoreText.setFillColor(Color::White);
    scoreText.setCharacterSize(75);
    scoreText.setPosition(20, 20); // Top left corner
    scoreText.setString("Score = 0");

    livesText.setFont(ft);
    livesText.setCharacterSize(75);
    livesText.setFillColor(Color::White);
    livesText.setString("Lives = 3");

    messageText.setFont(ft);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::White);
    messageText.setString("Press Enter to Start!");
     // 4. Instantiate Game Objects
    Bat bat;   // Create the player bat
    Ball ball; // Create the ball

    Clock ct; // Clock to track time
    Time dt;  // Delta time (time passed between frames)

    // --- MAIN GAME LOOP ---
    while (window.isOpen()) {
        dt = ct.restart(); // Get the time passed since last frame
       // --- EVENT POLLING ---
        Event ev;
        while (window.pollEvent(ev)) {
            // Prevent holding a key down from triggering multiple times rapidly
            if (ev.type == Event::KeyReleased && !acceptInput) {
                acceptInput = true;
            }
            if (ev.type == Event::Closed) {
                window.close(); // Close game if window "X" is clicked
            }
               // --- INPUT HANDLING ---
        if (acceptInput) {
            // Enter key resets the game
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                gameOver = false;
                paused = false;
                acceptInput = false;
                incScore = false;
                score = 0;
                lives = 3;
                ball = Ball(); // Re-initialize the ball to starting state
                messageText.setString("Press Enter to Start!");
            }
                    // Spacebar toggles pause state
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                paused = !paused;
                acceptInput = false;
            }
        }
    }
      //// --- GAME LOGIC ---
        if (!paused && !gameOver) {
            if (lives <= 0) {
                // Game Over!
                gameOver = true;
                paused = true;
                lives = 0;
                messageText.setString("Game Over! Press Enter");
                // Center the message text
                FloatRect msgBounds = messageText.getLocalBounds();
                messageText.setPosition(
                    (vw.getSize().x - msgBounds.width) / 2.0f,
                    (vw.getSize().y - msgBounds.height) / 2.0f
                );
            }

            // Move bat based on arrow keys
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                bat.moveLeft(dt);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                bat.moveRight(dt);
            }

            // Update ball position and check all collisions
            ball.upadteBall(dt);
            ball.ballBounceRight();
            ball.ballBounceLeft();
            ball.ballBounceTop(score, incScore);
            ball.ballBounceBottom(incScore, lives);
            
            // Pass the bat's exact current position to the ball to check for collision
            ball.ballTochesBat(bat.returnShape().getGlobalBounds(), incScore);
        }
            // Update Text Strings
            stringstream str_score, str_lives;
            str_score << "Score = " << score;
            str_lives << "Lives = " << lives;
            scoreText.setString(str_score.str());
            livesText.setString(str_lives.str());

            // Dynamically position lives text on the top right
            FloatRect boundsLive = livesText.getLocalBounds();
            float y = 20;
            float x = vw.getSize().x - boundsLive.width - 20;
            livesText.setPosition(x, y);
        
        window.clear(); // Clear the previous frame

        // Draw everything in the current frame
        window.draw(bat.returnShape());
        window.draw(ball.returnShape());
        window.draw(scoreText);
        window.draw(livesText);

        // Draw message text when paused or game over
        if (paused || gameOver) {
            window.draw(messageText);
        }

        window.display(); // Push the frame to the screen

        } // end main game loop

return 0;
}
