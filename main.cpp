#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>

//  g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -o prog -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system

using namespace sf;
using namespace std;

const int WIDTH = 2560, HEIGHT = 1440, MAX_ITER = 10000;
const float CHANGE_X = 0.233, CHANGE_Y = 0.655, ZOOM = 888888888.00;

int main()
{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Mandelbrot Gen", Style::Close | Style::None);
    
    RectangleShape pixel = RectangleShape(Vector2f(1.0f, 1.0f));
    pixel.setPosition(Vector2f(0.0f, 0.0f));

    

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
        }
        window.clear();
        for(int x = 1; x < WIDTH; x++) {
            for (int  y = 1; y < HEIGHT; y++) {
                double dx = ((double)x - (double)WIDTH * 0.5)/ZOOM - CHANGE_X;
                double dy = ((double)y - (double)HEIGHT * 0.5)/ZOOM - CHANGE_Y;
                double a = dx;
                double b = dy;
                //draw white
                // pixel.setFillColor(Color::White);
                // pixel.setPosition(Vector2f(x, y));
                // window.draw(pixel);
                for(double t = 1; t < MAX_ITER; t++) {
                    double d = a*a-b*b+dx;
                    b = 2*a*b+dy;
                    a = d;
                    if(d>MAX_ITER) {
                        //draw pixel
                        pixel.setFillColor(Color(t, t*0.5, t*4.0f));
                        pixel.setPosition(Vector2f(x, y));
                        window.draw(pixel);
                        cout << "drawn at: " << x << ' ' << y << endl;
                        break;
                    }
                }
            }
        }
        
        window.display();
        cout << "sleeping" << endl;
        usleep(20012001302190321);
        
    }

    return 0;
}
