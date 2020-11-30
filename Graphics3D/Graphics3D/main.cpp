//
//  main.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 10/25/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "image.hpp"
#include "matrix.hpp"

using namespace std;
//using namespace sf;


int main(int, char const**) {
    matrix<float> a({
        {1, 2},
        {3, 4},
    });
    matrix<float> b({
        {5, 6},
        {7, 8},
    });
    matrix<float> c({
        {9, 10},
        {11, 12},
    });
    matrix<float> d({
        {13, 14},
        {15, 16},
    });
    matrix<matrix<float>> m({
        vector<matrix<float>>{a, b},
        vector<matrix<float>>{c, d},
    });
    
    
    
    
    
//    bool isFocused = true;
//    int width = 127, height = 64;
//    string s = "/Users/michael/ComputerScience/Engine3D/Graphics3D/Graphics3D/Resources/g/";
//    image imgs[27] = {
//        image(s+"pal1"+".bmp"),
//        image(s+"pal1bg"+".bmp"),
//        image(s+"pal1wb"+".bmp"),
//        image(s+"pal4"+".bmp"),
//        image(s+"pal4gs"+".bmp"),
//        image(s+"pal4rle"+".bmp"),
//        image(s+"pal8-0"+".bmp"),
//        image(s+"pal8"+".bmp"),
//        image(s+"pal8gs"+".bmp"),
//        image(s+"pal8nonsquare"+".bmp"),
//        image(s+"pal8os2"+".bmp"),
//        image(s+"pal8rle"+".bmp"),
//        image(s+"pal8topdown"+".bmp"),
//        image(s+"pal8v4"+".bmp"),
//        image(s+"pal8v5"+".bmp"),
//        image(s+"pal8w124"+".bmp"),
//        image(s+"pal8w125"+".bmp"),
//        image(s+"pal8w126"+".bmp"),
//        image(s+"rgb16-565"+".bmp"),
//        image(s+"rgb16-565pal"+".bmp"),
//        image(s+"rgb16"+".bmp"),
//        image(s+"rgb16bfdef"+".bmp"),
//        image(s+"rgb24"+".bmp"),
//        image(s+"rgb24pal"+".bmp"),
//        image(s+"rgb32"+".bmp"),
//        image(s+"rgb32bf"+".bmp"),
//        image(s+"rgb32bfdef"+".bmp")
//    };
//    unsigned int w, h, img=0;
//    RenderWindow window(VideoMode(127, 64), "3D Graphics!");
//    window.setFramerateLimit(60);
//    Texture texture;
//    Sprite sprite;
//    w = imgs[img].width();
//    h = imgs[img].height();
//    texture.create(w, h);
//    Uint8* pData = new Uint8[4*w*h];
//
//    for (int i = 0; i < h; i++) {
//        for (int j = 0; j < w; j++) {
//            pData[4*((h-i-1)*w+j)+0] = (Uint8) imgs[img].get(j, i)->r();
//            pData[4*((h-i-1)*w+j)+1] = (Uint8) imgs[img].get(j, i)->g();
//            pData[4*((h-i-1)*w+j)+2] = (Uint8) imgs[img].get(j, i)->b();
//            pData[4*((h-i-1)*w+j)+3] = (Uint8) imgs[img].get(j, i)->a();
//        }
//    }
//    texture.update(pData);
//    sprite = Sprite(texture, IntRect(0, 0, w, h));
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            switch (event.type) {
//                case Event::Closed:
//                    window.close();
//                    break;
//                case Event::Resized:
//                    width = window.getSize().x;
//                    height = window.getSize().y;
//                    break;
//                case Event::LostFocus:
//                    isFocused = false;
//                    break;
//                case Event::GainedFocus:
//                    isFocused = true;
//                    break;
//                case Event::KeyReleased:
//                    switch (event.key.code) {
//                        case Keyboard::Escape:
//                            window.close();
//                            break;
//                        case Keyboard::Space:
//                            img = (img+1)%27;
//                            w = imgs[img].width();
//                            h = imgs[img].height();
//                            texture.create(w, h);
//                            Uint8* pData = new Uint8[4*w*h];
//
//                            for (int i = 0; i < h; i++) {
//                                for (int j = 0; j < w; j++) {
//                                    pData[4*((h-i-1)*w+j)+0] = (Uint8) imgs[img].get(j, i)->r();
//                                    pData[4*((h-i-1)*w+j)+1] = (Uint8) imgs[img].get(j, i)->g();
//                                    pData[4*((h-i-1)*w+j)+2] = (Uint8) imgs[img].get(j, i)->b();
//                                    pData[4*((h-i-1)*w+j)+3] = (Uint8) imgs[img].get(j, i)->a();
//                                }
//                            }
//                            texture.update(pData);
//                            sprite = Sprite(texture, IntRect(0, 0, w, h));
//                    }
//                    break;
//            }
//        }
//
//        window.clear();
//        window.draw(sprite);
//        window.display();
//    }

    return EXIT_SUCCESS;
}
