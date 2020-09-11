#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
#include <utility>
#include <cstring>

using namespace std;
using namespace sf;

pair <int ,int>  used[25][18];

int likovi[6][4] = {    //sR   // bL

    1 , 3 , 5 , 7, // I    3      0
    0 , 3 , 2 , 5, // S    3      1
    0 , 3 , 2 , 1, // O    3      2
    1 , 3 , 2 , 5, // T    3      3
    1 , 3 , 4 , 5, // RL   3      4
    0 , 3 , 1 , 5 // L    3      5

};

struct locc{
    int x, y;
} a[4], b[4];

int score = 0;

int main()
{
    RenderWindow window(VideoMode(800, 576) , "Tetris - Luka" , Style::Default);
    Texture screen;
    screen.loadFromFile("Textures/Tetristiles1.png");
    Sprite s(screen);
    s.setTextureRect(IntRect(0,0,32,32));
    Clock sat;
    float timer = 0, delay = 0.3; // sekunde

    int pomak = 0, lik = -1;
    bool rot = false;
    bool check = false;
    int boja = 0;

    while(window.isOpen()){
        float times = sat.getElapsedTime().asSeconds();
        sat.restart();
        timer += times;
        // exit //
        Event e;
        while(window.pollEvent(e)){

            if(e.type == Event::Closed) window.close();
            if(e.type == Event::KeyPressed){
                if(e.key.code == Keyboard::Right) pomak = 1;
                else if(e.key.code == Keyboard::Left) pomak = -1;

                if(e.key.code == Keyboard::Down) delay = 0.05;
                else delay = 0.3;

                if(e.key.code == Keyboard::Up) rot = true;
            }
            else delay = 0.3;
        }

        window.clear(Color::White);

        // likovi //
        if(lik == -1){
            srand(time(NULL));
            lik = rand()%6;
            for(int i = 0; i < 4; i++){
                a[i].x = likovi[lik][i] % 2;
                a[i].y = likovi[lik][i] / 2;
                b[i] = a[i];
            }
        }

        // timer //
        int  t = 0;
        if(timer > delay){
            timer = 0;
            t = 1;
        }

        // draw //
        if(check == false)
        for(int i = 0; i < 4; i++){
            b[i] = a[i];
            if(rot == true){
                int x = a[i].y - a[1].y;  // broji se od 0 na dalje !!!
                int y = a[i].x - a[1].x;
                a[i].x = a[1].x - x;
                a[i].y = a[1].y + y;
             }
            a[i].y += t;
            a[i].x += pomak;
            if(a[i].x < 0 || a[i].x * 32 >= 800 ) check = true;
            if(a[i].y * 32 >= 576 || used[a[i].x][a[i].y].first == 1){
                if(pomak == 0){
                    check = true;
                    lik = -1;
                }
                else check = true;
            }
        }

        // provjera //
        if(check == true){
            score += 1;
            check = false;
            for(int i = 0; i < 4; i++){
                a[i] = b[i];
                if(b[i].y == 0) window.close(); // exit u slucaju game over
                s.setPosition( b[i].x * 32 , b[i].y * 32);
                window.draw(s);
            }
        }
        else{
            for(int i = 0; i < 4; i++){
                s.setPosition( a[i].x * 32 , a[i].y * 32);
                window.draw(s);
            }
        }

        // novi lik //
        if(lik == -1){
          for(int i = 0; i < 4; i++){
            used[b[i].x][b[i].y].first = 1;
            used[b[i].x][b[i].y].second = boja;
          }
          srand(time(NULL));
          int newB = rand()%5;
          boja = newB;
        }


        // check lines //
        for(int j = 0; j < 18 ; j++){
            bool je = true;
            for(int i = 0; i < 25; i++){
                if(used[i][j].first == 0){
                    je = false;
                    break;
                }
            }
            if(je == true){
                score += 10;
                for(int i = 0; i < 25; i++){
                    used[i][j].first = 0;
                }
                for(int k = j - 1; k >= 0; k--){
                    for(int l = 0; l < 25; l++){
                        used[l][k + 1].first = used[l][k].first;
                        used[l][k + 1].second = used[l][k].second;
                    }
                }
                for(int i = 0; i < 25; i++){
                    used[i][0].first = 0;
                }
            }
        }

        // stari blokovi //
        for(int i = 0; i < 25 ; i++){
            for(int j = 0; j < 18; j++){
                if(used[i][j].first == 1){
                    s.setPosition( i * 32 , j * 32);
                    s.setTextureRect(IntRect(used[i][j].second * 32, 0 , 32 , 32));
                    window.draw(s);
                }
            }
        }

        // ostalo //
        s.setTextureRect(IntRect(boja * 32, 0 , 32 , 32));
        pomak = 0;
        rot = false; // pazi
        printf("%d", score);
        system("CLS");
        window.display();
    }

    return 0;
}


/**

@luka_bur3k

*/

