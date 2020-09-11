#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <utility>

using namespace std;
using namespace sf;

// velicina igraca 50 * 50;

struct polje{
  int x, y, boja;
} PossiblePlaces[24];

struct provjera{
    int p , d , t;
};

polje Pos1[9], Pos2[9];
int bio[24];
int biot[16];


int main()
{
    RenderWindow window(VideoMode(600 , 600), "Mlin - Luka" , Style::Default);
    Texture background;
    background.loadFromFile(".../Texture/background.png");
    Sprite BG(background);
    BG.setPosition(0 , 0);
    BG.setTextureRect(IntRect(0, 0 , 600 , 600));

    Texture player1;
    Texture player2;
    player1.loadFromFile(".../Texture/igrac1.png");
    player2.loadFromFile(".../Texture/igrac2.png");
    Sprite P1(player1);
    Sprite P2(player2);

    P1.setOrigin(24 , 24);
    P2.setOrigin(24 , 24);

    for(int i = 0; i < 9; i++){
        Pos1[i].boja = 0; // 0 je crna
        Pos2[i].boja = 1; // 1 je bijela
    }

    polje PossiblePlaces[] = { // s lijeva na desno a onda na nize
    43 , 43, -1,
    300, 43, -1,
    556, 43, -1,
    128, 128, -1,
    300, 128, -1,
    471, 128, -1,
    214, 214, -1,
    300, 214, -1,
    385, 214, -1,
    42, 300, -1,
    128, 300, -1,
    214, 300, -1,
    385, 300, -1,
    470, 300, -1,
    556, 300, -1,
    214, 385, -1,
    300, 385, -1,
    385, 385, -1,
    128, 471, -1,
    300, 471, -1,
    471, 471, -1,
    42, 556, -1,
    300, 556, -1,
    556, 556, -1
    };

    int PF = 0;
    bool game = false;
    bool premjesti = false;
    bool jedi = false;
    int mjesto, bo;
    while(window.isOpen()){
        if(PF == 18) game = true;

        Event e;
        window.draw(BG);
        while(window.pollEvent(e)){
            if(e.type == Event::Closed) window.close();
            if(e.type == Event::MouseButtonPressed){
                if(game == false && e.mouseButton.button == Mouse::Left && jedi == false){ // postavljanje figurica
                    Vector2i localPosition = Mouse::getPosition(window);
                    for(int i =  0; i < 24; i++){
                        if(localPosition.x >= PossiblePlaces[i].x - 5 && localPosition.x <= PossiblePlaces[i].x + 5 && localPosition.y >= PossiblePlaces[i].y - 5 && localPosition.y <= PossiblePlaces[i].y + 5 && bio[i] == 0){
                            bio[i] = 1;
                            if(PF%2 == 0) PossiblePlaces[i].boja = 1;
                            else PossiblePlaces[i].boja = 0;
                            PF++;
                            break;
                        }
                    }
                }
                if(game == true && e.mouseButton.button == Mouse::Left && premjesti == false && jedi == false){// biranje
                    Vector2i localPosition = Mouse::getPosition(window);
                    for(int i =  0; i < 24; i++){
                        if(localPosition.x >= PossiblePlaces[i].x - 15 && localPosition.x <= PossiblePlaces[i].x + 15 && localPosition.y >= PossiblePlaces[i].y - 15 && localPosition.y <= PossiblePlaces[i].y + 15 && bio[i] == 1){
                            premjesti = true;
                            bo = PossiblePlaces[i].boja;
                            mjesto = i;
                            break;
                        }
                    }
                }
                if(game == true && e.mouseButton.button == Mouse::Left && premjesti == true && jedi == false){
                    Vector2i localPosition = Mouse::getPosition(window);
                    for(int i =  0; i < 24; i++){
                        if(localPosition.x >= PossiblePlaces[i].x - 15 && localPosition.x <= PossiblePlaces[i].x + 15 && localPosition.y >= PossiblePlaces[i].y - 15 && localPosition.y <= PossiblePlaces[i].y + 15 && bio[i] == 0){
                            bio[mjesto] = 0;
                            premjesti = false;
                            bio[i] = 1;
                            PossiblePlaces[mjesto].boja = -1;
                            PossiblePlaces[i].boja = bo;
                            break;
                        }
                    }
                }
                if(e.mouseButton.button == Mouse::Left && jedi == true){
                    Vector2i localPosition = Mouse::getPosition(window);
                    for(int i =  0; i < 24; i++){
                        if(localPosition.x >= PossiblePlaces[i].x - 15 && localPosition.x <= PossiblePlaces[i].x + 15 && localPosition.y >= PossiblePlaces[i].y - 15 && localPosition.y <= PossiblePlaces[i].y + 15 && bio[i] == 1){
                            jedi = false;
                            PossiblePlaces[i].boja = -1;
                            bio[i] = 0;
                            break;
                        }
                    }
                }
            }
        }

        /////provjera trica//////
        /*

        1    2    3
          4  5  6
            789
        101112131415
            161718
         19 20  21
        22  23   24*/
        provjera Prov[16] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        0, 9, 21,
        3, 10, 18,
        6, 11, 15,
        1, 4, 7,
        16, 19, 22,
        8, 12, 17,
        5, 13, 20,
        2, 14, 23
        };
        /*system("CLS");
        for(int i = 0; i < 24; i++){
            printf("%d : %d\n",i,  PossiblePlaces[i].boja);
        }*/
        for(int i = 0; i < 16; i++){
            if(PossiblePlaces[Prov[i].p].boja == PossiblePlaces[Prov[i].d].boja &&  PossiblePlaces[Prov[i].t].boja == PossiblePlaces[Prov[i].d].boja && PossiblePlaces[Prov[i].p].boja != -1){
                if(biot[i] == 0){
                    biot[i] = 1;
                    jedi = true;
                    break;
                }
            }
            else if(biot[i] == 1) biot[i] = 0;


        }

        ////////crtanje//////////
        for(int i = 0; i < 24; i++){
            if(PossiblePlaces[i].boja != -1){
                if(PossiblePlaces[i].boja == 1){
                    P2.setPosition(PossiblePlaces[i].x , PossiblePlaces[i].y);
                    window.draw(P2);
                }
                else{
                    P1.setPosition(PossiblePlaces[i].x , PossiblePlaces[i].y);
                    window.draw(P1);
                }
            }
        }

        window.display();
    }

    return 0;
}

/**


@luka_bur3k

*/
