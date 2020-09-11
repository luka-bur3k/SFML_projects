#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

using namespace std;
using namespace sf;

int C, D;
int ScoreL , ScoreR;
int ChangeChecker( int _x , int _y, int Ly ,int Ry);

int main()
{

    RenderWindow window(VideoMode(800 , 600), "Pong - Luka" , Style::Default);
    Texture LeftPaddle, RightPaddle , Ball;

    LeftPaddle.loadFromFile(".../Texture/PaddleL&R.png");
    RightPaddle.loadFromFile(".../Texture/PaddleL&R.png");
    Ball.loadFromFile(".../Texture/Ball.png");

    Sprite LP(LeftPaddle);
    Sprite RP(RightPaddle);
    Sprite B(Ball);

    LP.setOrigin(12 , 75);
    RP.setOrigin(12 , 75);
    B.setOrigin(16 , 16);

    // LP se kreæe po x = 20
    // RP se kreæe po x = 779

    int y1 = 300;
    int y2 = 300;
    int x1 = 20;
    int x2 = 779;

    float BX = 400;
    float BY = 300;
    float Bspeed = 1;
    srand(time(NULL));
    int Bangle = rand()%120 * rand()%20 + rand()%1555;
    Bangle %= 360;
    float DEGTORAD = 0.017453;

    int change = 0;

    Clock clock;
    float timer = 0, delay = 0.002;

    while(window.isOpen()){
        float timee = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += timee;

        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed) window.close();
        }
        change = ChangeChecker(BX , BY, y1 , y2);
        if(timer > delay){
            bool ad = false;
            if(change > 0){ // drzi unutar delaya jer ga ponavlja vise puta izvan
                Bspeed += 0.02;
                if(change == 1) C = Bangle - 270;
                else if(change == 2) C = Bangle - 90;
                else if(change == 3){
                    C = Bangle - 180;
                    ad = true;
                }
                else{
                     if(C > 90) C = Bangle - 360;
                     else C = Bangle;
                     ad = true;
                }

                if(C < 0){
                    if(ad == true) C -= Bspeed*2.23;
                    C = -C;
                    D = -1;
                }
                else{
                    D = 1;
                    C += Bspeed*2.23;
                }

                C = 90 - C;

                //printf("%d %d %d %d\n", C , D ,Bangle, change);
                B.rotate(D * 2 * C);
                Bangle = B.getRotation();
                change = 0;

            }
            else if(change == -1){
                ScoreR++;
                change = -3;
                BX = 400;
                BY = 300;
                srand(time(NULL));
                Bangle = rand()%120 * rand()%20 + rand()%1555;
                Bangle %= 360;
                Bspeed = 1;
            }
            else if(change == -2){
                ScoreL++;
                change = -3;
                BX = 400;
                BY = 300;
                srand(time(NULL));
                Bangle = rand()%120 * rand()%20 + rand()%1555;
                Bangle %= 360;
                Bspeed = 1;
            }

            timer = 0;
            if(Keyboard::isKeyPressed(Keyboard::W)) y1--;
            if(Keyboard::isKeyPressed(Keyboard::S)) y1++;
            if(Keyboard::isKeyPressed(Keyboard::Up)) y2--;
            if(Keyboard::isKeyPressed(Keyboard::Down)) y2++;

            BX += cos(Bangle*DEGTORAD)*Bspeed;
            BY += sin(Bangle*DEGTORAD)*Bspeed;
        }
        window.clear(Color::Black);

        printf("SCORE : %d , %d\n", ScoreL, ScoreR);

        B.setRotation(Bangle);
        B.setPosition(BX , BY);
        window.draw(B);
        LP.setPosition(x1 , y1);
        window.draw(LP);
        RP.setPosition(x2 , y2);
        window.draw(RP);
        window.display();
    }
    return 0;
}


ChangeChecker( int _x , int _y, int Ly ,int Ry){
    int CH = 0;
    if( _y <= 0) CH = 1;
    else if(_y >= 600) CH = 2;
    else if( _x >= 8 && _x <= 32 && _y >= Ly - 75 && _y <= Ly + 75 ) CH = 3;
    else if( _x >= 767 && _x <= 791 && _y >= Ry - 75 && _y <= Ry + 75) CH = 4;
    else if( _x <= 0) CH = -1;
    else if( _x >= 800) CH = -2;
    return CH;
};
