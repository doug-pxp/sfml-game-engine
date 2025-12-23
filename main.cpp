#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

int main() {

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
unsigned int windowWidth = 0;
unsigned int windowHeight = 0;

std::string type;

std::ifstream configFile("config.txt");
if (!configFile) {
    std::cout << "Unable to open config.txt file.\n";
     return -1;
}

while (configFile >> type)   // reads the first token of each “line”
{
    if (type == "Window")
    {
        
        configFile >> windowWidth >> windowHeight;

        std::cout << "Window: " << windowWidth << " " << windowHeight << "\n";
        // later: create your sf::RenderWindow here
    }
    else if (type == "Font")
    {
        std::string fontPath;
        int fontSize;
        int r, g, b;

        configFile >> fontPath >> fontSize >> r >> g >> b;

        std::cout << "Font: " << fontPath << " " << fontSize
                  << " " << r << " " << g << " " << b << "\n";
        // later: font.loadFromFile(fontPath), set default text color, etc.
    }
    else if (type == "Rectangle")
    {
        // Rectangle N X Y SX SY R G B W H
        std::string name;
        float x, y, sx, sy;
        int r, g, b;
        float width, height;

        configFile >> name >> x >> y >> sx >> sy >> r >> g >> b >> width >> height;

        std::cout << "Rectangle: " << name
                  << " pos(" << x << "," << y << ")"
                  << " vel(" << sx << "," << sy << ")"
                  << " color(" << r << "," << g << "," << b << ")"
                  << " size(" << width << "," << height << ")\n";

        // later: create sf::RectangleShape, store velocity, etc.
    }
    else if (type == "Circle")
    {
        // Circle N X Y SX SY R G B RADIUS
        std::string name;
        float x, y, sx, sy;
        int r, g, b;
        float radius;

        configFile >> name >> x >> y >> sx >> sy >> r >> g >> b >> radius;

        std::cout << "Circle: " << name
                  << " pos(" << x << "," << y << ")"
                  << " vel(" << sx << "," << sy << ")"
                  << " color(" << r << "," << g << "," << b << ")"
                  << " radius(" << radius << ")\n";

        // later: create sf::CircleShape, store velocity, etc.
    }
    else
    {
        std::cout << "Unknown keyword in config: " << type << "\n";
        // optional: break; or keep going
    }
}
	// ------------------------------------------------------------
	// TODO: Initialize SFML Window
	// ------------------------------------------------------------
	// Create an 800x600 window (read these values from the config file)
	// Set a frame rate limit to avoid excessive CPU usage
	std::cout << "Window dimensions: " << windowWidth << "x" << windowHeight << std::endl;
	
	sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Game window");
	window.setFramerateLimit(60);

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
	sf::Font font("fonts/arial.ttf");
	sf::Text rectangleText(font, "My Rectangle", 14);
	
	rectangleText.setFillColor(sf::Color::White);

	// Set position later after centering	
	sf::FloatRect bounds = rectangleText.getLocalBounds();
	rectangleText.setOrigin(
    {bounds.position.x + bounds.size.x  / 2.f,
    bounds.position.y  + bounds.size.y / 2.f});

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
	sf::Vector2f velocity = {50.f, 50.f};

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

			// [update] the window
			float left = rectangle.getPosition().x;
			float right = rectangle.getPosition().x + rectangle.getSize().x;
			float up = rectangle.getPosition().y;
			float down = rectangle.getPosition().y + rectangle.getSize().y;

			if (left < 0 ){
				rectangle.setPosition({0.f, rectangle.getPosition().y});
				velocity.x = velocity.x * -1;
			}

			if (right > windowWidth){
				rectangle.setPosition({windowWidth - rectangle.getSize().x, rectangle.getPosition().y});
				velocity.x = velocity.x * -1;
			}

			if (up < 0 ){
				rectangle.setPosition({rectangle.getPosition().x, 0.f});
				velocity.y = velocity.y * -1;
			}

			

			if (down > windowHeight){
				rectangle.setPosition({rectangle.getPosition().x, windowHeight - rectangle.getSize().y});
				velocity.y = velocity.y * -1;
			}

			rectangle.move(velocity * dt);
			rectangleText.setPosition(
			{rectangle.getPosition().x + rectangle.getSize().x / 2,
			rectangle.getPosition().y + rectangle.getSize().y / 2});
			
			// [clear] the window with black color
			window.clear(sf::Color::Black);
			
			// [draw] everything here...
			window.draw(rectangle);
			window.draw(rectangleText);

			// [	display] and end the current frame
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