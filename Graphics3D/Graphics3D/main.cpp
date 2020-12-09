//
//  main.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 10/25/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include <SFML/Graphics.hpp>
//#include <iostream>
#include "image.hpp"
#include "matrix.hpp"
#include "camera.hpp"

using namespace std;
using namespace sf;


int main(int, char const**) {
    camera c;
    bool isFocused = true;
    int width = 127, height = 64;
    string s = "/Users/michael/ComputerScience/Engine3D/Graphics3D/Graphics3D/Resources/g/";
    /*image imgs[27] = {
        image(s+"pal1"+".bmp"),
        image(s+"pal1bg"+".bmp"),
        image(s+"pal1wb"+".bmp"),
        image(s+"pal4"+".bmp"),
        image(s+"pal4gs"+".bmp"),
        image(s+"pal4rle"+".bmp"),
        image(s+"pal8-0"+".bmp"),
        image(s+"pal8"+".bmp"),
        image(s+"pal8gs"+".bmp"),
        image(s+"pal8nonsquare"+".bmp"),
        image(s+"pal8os2"+".bmp"),
        image(s+"pal8rle"+".bmp"),
        image(s+"pal8topdown"+".bmp"),
        image(s+"pal8v4"+".bmp"),
        image(s+"pal8v5"+".bmp"),
        image(s+"pal8w124"+".bmp"),
        image(s+"pal8w125"+".bmp"),
        image(s+"pal8w126"+".bmp"),
        image(s+"rgb16-565"+".bmp"),
        image(s+"rgb16-565pal"+".bmp"),
        image(s+"rgb16"+".bmp"),
        image(s+"rgb16bfdef"+".bmp"),
        image(s+"rgb24"+".bmp"),
        image(s+"rgb24pal"+".bmp"),
        image(s+"rgb32"+".bmp"),
        image(s+"rgb32bf"+".bmp"),
        image(s+"rgb32bfdef"+".bmp")
    };*/
    
    RenderWindow window(VideoMode(127, 64), "3D Graphics!");
    window.setFramerateLimit(60);
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
        
        window.display();
    }

    return EXIT_SUCCESS;
}
