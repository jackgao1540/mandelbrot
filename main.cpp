#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>

//  g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -o prog -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system

using namespace sf;
using namespace std;

int WIDTH = 900, HEIGHT = 600, MAX_ITER = 113;
float CHANGE_X = 0.0, CHANGE_Y = 0.0, ZOOM = 1;
float FACTOR = 100, ZOOM_FACTOR = 0.9;

int main()
{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Mandelbrot Gen", Style::Close | Style::None);
    
    RectangleShape pixel = RectangleShape(Vector2f(1.0f, 1.0f));
    pixel.setPosition(Vector2f(0.0f, 0.0f));

    bool viewChanged = true;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Right) {
                    CHANGE_X -= FACTOR / ZOOM;
                    viewChanged = true;
                }
                else if (event.key.code == Keyboard::Left) {
                    CHANGE_X += FACTOR / ZOOM;
                    viewChanged = true;
                }
                else if (event.key.code == Keyboard::Down) {
                    CHANGE_Y -= FACTOR / ZOOM;
                    viewChanged = true;
                }
                else if (event.key.code == Keyboard::Up) {
                    CHANGE_Y += FACTOR / ZOOM;
                    viewChanged = true;
                }
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Right) {
                    ZOOM *= ZOOM_FACTOR;
                    viewChanged = true;
                }
                else if (event.mouseButton.button == Mouse::Left) {
                    ZOOM /= ZOOM_FACTOR;
                    viewChanged = true;
                }
            }
        }
        if (viewChanged) {
            window.clear();
            for(int x = 1; x < WIDTH; x++) {
                for (int  y = 1; y < HEIGHT; y++) {
                    double dx = ((double)x - (double)WIDTH * 0.5)/ZOOM - CHANGE_X;
                    double dy = ((double)y - (double)HEIGHT * 0.5)/ZOOM - CHANGE_Y;
                    double a = dx;
                    double b = dy;
                    for(double t = 1; t < MAX_ITER; t++) {
                        double d = a*a-b*b+dx;
                        b = 2*a*b+dy;
                        a = d;
                        if(d>MAX_ITER) {
                            //draw pixel
                            pixel.setFillColor(Color(t*4.0f, t*0.5, t));
                            pixel.setPosition(Vector2f(x, y));
                            window.draw(pixel);
                            break;
                        }
                    }
                }
            }
            window.display();
            viewChanged=false;
        }
    }

    return 0;
}
