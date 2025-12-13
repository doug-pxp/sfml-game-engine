#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

int main() {

	const int SCREEN_WIDTH = 1600;
	const int SCREEN_HEIGHT = 1200;

	std::cout << "Welcome To SFML for beginners" << std::endl;

	// ------------------------------------------------------------
	// TODO: Initialize SFML Window
	// ------------------------------------------------------------
	// Create an 800x600 window (read these values from the config file)
	// Set a frame rate limit to avoid excessive CPU usage

	sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "Game window");
	window.setFramerateLimit(60);

	// ------------------------------------------------------------
	// TODO: Load Configuration File
	// ------------------------------------------------------------
	// Open the config file (config.txt)
	// Read window dimensions
	// Read font file path, font size, and font color (R G B)
	// For each remaining line:
	//   - Identify whether it's "Circle" or "Rectangle"
	//   - Read the name of the shape
	//   - Read position (x, y)
	//   - Read speed (xSpeed, ySpeed)
	//   - Read color (R, G, B)
	//   - Read extra shape-specific properties:
	//        Circle → radius
	//        Rectangle → width, height
	// Store all shapes in a vector of objects (base class recommended)
	std::string line;

	std::ifstream configFile("config.txt");

	if (configFile.is_open()) {
		while (std::getline(configFile, line)) {
			std::cout << line << std::endl;
		}
		configFile.close();
	}
	else {
		std::cout << "Unable to open config.txt file." << std::endl;
	}

	// ------------------------------------------------------------
	// TODO: Create Shape Objects
	// ------------------------------------------------------------
	// For a Circle:
	//   - Create an SFML CircleShape with the given radius
	//   - Set its position using the top-left origin (SFML default)
	//   - Set its fill color
	//   - Store its speed for later movement
	//
	// For a Rectangle:
	//   - Create an SFML RectangleShape with width and height
	//   - Set its position (top-left corner)
	//   - Set its fill color
	//   - Store its speed
	sf::RectangleShape rectangle({120.f, 50.f});
	rectangle.setFillColor(sf::Color(100, 250, 50));
	rectangle.setPosition({10,20});


	// ------------------------------------------------------------
	// TODO: Load the Font
	// ------------------------------------------------------------
	// Load the font file provided in the config
	// Create an sf::Text object for each shape's name
	// Set its font, size, and color (from config file)
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
    std::cout << "Failed to load font\n";
	}


	// ------------------------------------------------------------
	// TODO: Center Shape Name Text
	// ------------------------------------------------------------
	// For each shape:
	//   - Determine the shape's bounding box
	//   - Calculate the exact center of that box
	//   - Position the text so the center of the string aligns to that point
	// Notes:
	//   - Text centering is tricky because SFML text origin is not at the center
	//   - You can change the origin or adjust manually
	//   - Being slightly off-center is acceptable per assignment instructions


	// ------------------------------------------------------------
	// TODO: Movement & Bouncing Logic
	// ------------------------------------------------------------
	// Every frame, for every shape:
	//   - Update its position using its stored (xSpeed, ySpeed)
	//   - Check for collision with window boundaries:
	//       * If left < 0 → reverse xSpeed
	//       * If right > windowWidth → reverse xSpeed
	//       * If top < 0 → reverse ySpeed
	//       * If bottom > windowHeight → reverse ySpeed
	// Make sure detection uses the shape's top-left coordinate plus width/height
	sf::Vector2f velocity = {500.f, 500.f};

	// ------------------------------------------------------------
	// TODO: Drawing
	// ------------------------------------------------------------
	// Every frame:
	//   - Clear the window
	//   - Draw each shape
	//   - Draw each shape's name centered on the shape
	//   - Display the window


	// ------------------------------------------------------------
	// TODO: Game Loop
	// ------------------------------------------------------------
	// While the window is open:
	//   - Process events (close window, escape key, etc.)
	//   - Update movement & bouncing
	//   - Draw everything
	sf::Clock clock;
	
	// run the program as long as the window is open
		while (window.isOpen())
		{
			float dt = clock.restart().asSeconds();
			// check all the window's events that were triggered since the last iteration of the loop
			while (const std::optional event = window.pollEvent())
			{
				// "close requested" event: we close the window
				if (event->is<sf::Event::Closed>())
					window.close();
			}

			// clear the window with black color
			window.clear(sf::Color::Black);

			// draw everything here...
			// window.draw(...)
			float left = rectangle.getPosition().x;
			float right = rectangle.getPosition().x + rectangle.getSize().x;
			float up = rectangle.getPosition().y;
			float down = rectangle.getPosition().y + rectangle.getSize().y;

			if (left < 0 || right > SCREEN_WIDTH){
				velocity.x = velocity.x * -1;
			}

			if (up < 0 || down > SCREEN_HEIGHT){
				velocity.y = velocity.y * -1;
			}

			rectangle.move(velocity * dt);
			window.draw(rectangle);


			// end the current frame
			window.display();
		}

	// ------------------------------------------------------------
	// TODO: Cleanup / Testing
	// ------------------------------------------------------------
	// Verify all shapes load correctly
	// Verify circles and rectangles bounce properly
	// Verify speed values (including negative speeds) move correctly
	// Verify text appears near the center of each shape
	// Ensure shapes never start outside the window (assumption allowed)
	// Test multiple shapes moving at once

	system("PAUSE");
	return 0;
}