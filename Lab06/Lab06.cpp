#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
    Image greenScreen;
    Image background;

    if (!greenScreen.loadFromFile("images/yoda.png"))
    {
        cout << "Couldn't load yoda.png\n";
        return 1;
    }

    if (!background.loadFromFile("images/alebrije.png"))
    {
        cout << "Couldn't load alebrije.png\n";
        return 1;
    }

    // Make sure both images are the same size.
    if (greenScreen.getSize() != background.getSize())
    {
        cout << "Images must be the same size.\n";
        return 1;
    }

    Image result = greenScreen;

    Vector2u size = greenScreen.getSize();

    for (unsigned int y = 0; y < size.y; y++)
    {
        for (unsigned int x = 0; x < size.x; x++)
        {
            Color pixel = greenScreen.getPixel(x, y);

            if (pixel == Color(32, 214, 23))
            {
                result.setPixel(
                    x,
                    y,
                    background.getPixel(x, y)
                );
            }
        }
    }

    Texture texture;
    texture.loadFromImage(result);

    Sprite sprite;
    sprite.setTexture(texture);

    RenderWindow window(
        VideoMode(result.getSize().x, result.getSize().y),
        "Result"
    );

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}