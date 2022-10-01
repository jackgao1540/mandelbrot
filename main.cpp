#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>

//  g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -o prog -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system

using namespace sf;
using namespace std;

const int WIDTH = 1600, HEIGHT = 900;

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
                double dx = ((double)x - (double)WIDTH * 0.5)/100000.0 - 0.233;
                double dy = ((double)y - (double)HEIGHT * 0.5)/100000.0 - 0.655;
                double a = dx;
                double b = dy;
                for(double t = 1; t < 200; t++) {
                    double d = a*a-b*b+dx;
                    b = 2*a*b+dy;
                    a = d;
                    if(d>200) {
                        //draw pixel
                        pixel.setFillColor(Color(t *3, t, t/2));
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
