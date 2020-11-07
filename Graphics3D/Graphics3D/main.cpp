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
    image img("/Users/michael/ComputerScience/Engine3D/Graphics3D/Graphics3D/Resources/Shapes.bmp");
    unsigned int w = img.width(), h = img.height();
    RenderWindow window(VideoMode(w, h), "3D Graphics!");
    window.setFramerateLimit(60);

    Texture texture;
    texture.create(w, h);
    Uint8* pData = new Uint8[4*w*h];
    
//    for (int i = 0; i < w*h; i+=4) {
//        pData[i+0] = img.get(i%w, i/w)->a();
//        pData[i+1] = img.get(i%w, i/w)->r();
//        pData[i+2] = img.get(i%w, i/w)->g();
//        pData[i+3] = img.get(i%w, i/w)->b();
//        img.get(i%w, i/w)->print();
//    }
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            pData[i*w+j+0] = img.get(j, i)->a();
            pData[i*w+j+1] = img.get(j, i)->r();
            pData[i*w+j+2] = img.get(j, i)->g();
            pData[i*w+j+3] = img.get(j, i)->b();
//            img.get(j, i)->print();
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
