//
//  main.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 10/25/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using namespace std;
using namespace sf;

int main(int, char const**) {
    Vector2<unsigned int> window_size(800, 600);
    bool isFocused = true;
    RenderWindow window(VideoMode(window_size.x, window_size.y), "3D Graphics!");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::Resized:
                    window_size = window.getSize();
                    break;
                case Event::LostFocus:
                    isFocused = false;
                    break;
                case Event::GainedFocus:
                    isFocused = true;
                    break;
                case Event::KeyReleased:
                    switch (event.key.code) {
                        case Keyboard::Escape:
                            window.close();
                            break;
                    }
                    break;
            }
        }

        window.clear();

        window.display();
    }

    return EXIT_SUCCESS;
}
