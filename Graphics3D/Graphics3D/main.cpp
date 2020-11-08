//
//  main.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 10/25/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "image.hpp"

using namespace std;
using namespace sf;


int main(int, char const**) {
    bool isFocused = true;
    int width = 800, height = 600;
    image img("/Users/michael/ComputerScience/Engine3D/Graphics3D/Graphics3D/Resources/bmp256.bmp");
    unsigned int w = img.width(), h = img.height();
    RenderWindow window(VideoMode(w, h), "3D Graphics!");
    window.setFramerateLimit(60);

    Texture texture;
    texture.create(w, h);
    Uint8* pData = new Uint8[4*w*h];
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            pData[4*((h-i-1)*w+j)+0] = (Uint8) img.get(j, i)->r();
            pData[4*((h-i-1)*w+j)+1] = (Uint8) img.get(j, i)->g();
            pData[4*((h-i-1)*w+j)+2] = (Uint8) img.get(j, i)->b();
            pData[4*((h-i-1)*w+j)+3] = (Uint8) img.get(j, i)->a();
        }
    }
    texture.update(pData);
    Sprite sprite(texture);
    sprite.setTextureRect(IntRect(0,0,w,h));
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::Resized:
                    width = window.getSize().x;
                    height = window.getSize().y;
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
        window.draw(sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}
