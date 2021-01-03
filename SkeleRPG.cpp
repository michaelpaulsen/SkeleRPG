#include <iostream>
#include <chrono>
#include "../../../Skele_lib/utils/WinApiScreen.h"
#include "../../../Skele_lib/utils/Utils.h"
#include "../../../Skele_lib/RPG_Lib/includeAll.h"
Skele_lib::CustomWinAPI::screen::Screen s = Skele_lib::CustomWinAPI::screen::Screen(171, 43); 
Skele_lib::RPG::Player player1 = Skele_lib::RPG::Player( );
std::chrono::time_point<std::chrono::system_clock> Tp1 = std::chrono::system_clock::now();
std::chrono::time_point<std::chrono::system_clock> Tp2;
float fps = 30; 
int main()
{
    int index; 
    long int frame = 0; 
    s.setActive(); 
    while (frame < 100000) {
        for (int y = 0; y < s.getScreenHeight(); y++ ) {
            for (int x = 0; x < s.getScreenWidth(); x++) {
                index = y * s.getScreenWidth() + x; /// calculate the index for the screen array and store it 
                /* clear the screen
                * this needs to happen or there would be streaking think ms solitaire 
                */
                s.screen[index] = ' ';
                if (x == player1.x) { 
                    if (y == player1.y) {
                        switch (player1.dir) { 
                            /*
                            change what "sprite" is shown based off of what direction the player is facing
                            should be a virtual function in the Skele_lib::RPG::Player class
                            */
                            case Skele_lib::RPG::Direction::North :{
                                s.screen[index] = 0x31d;
                                break;
                            }
                            case Skele_lib::RPG::Direction::East: {
                                s.screen[index] = 0x319;
                                break;
                            }
                            case Skele_lib::RPG::Direction::South: {
                                s.screen[index] = 0x31e;
                                break; 
                            }
                            case Skele_lib::RPG::Direction::West: {
                                s.screen[index] =0x31f;
                                break; 
                            }
                        }
                    }
                }
            }
        }
        /*display the frame number*/
        if (player1.y != 0) {
            if (player1.x > 3) {
                s.screen[0] = Skele_lib::Utils::intToChar(Skele_lib::Utils::getNthdigit(frame, 1000));
                s.screen[1] = Skele_lib::Utils::intToChar(Skele_lib::Utils::getNthdigit(frame, 100));
                s.screen[2] = Skele_lib::Utils::intToChar(frame % 10);
            }
        }
        
        
        /*
        * move the player
        * should be a virtual function in the Skele_lib::RPG::Player Class
        */
        if (Skele_lib::Utils::GetKeyDown('W') || Skele_lib::Utils::GetKeyDown(VK_UP)) {
            player1.move(1); 
        }
        if (Skele_lib::Utils::GetKeyDown('S') || Skele_lib::Utils::GetKeyDown(VK_DOWN)) {
            player1.move(3);
        }
        if (Skele_lib::Utils::GetKeyDown('D') || Skele_lib::Utils::GetKeyDown(VK_RIGHT)) {
            player1.move(2);
        }
        if (Skele_lib::Utils::GetKeyDown('A') || Skele_lib::Utils::GetKeyDown(VK_LEFT)) {
            player1.move(4);
        }
        /*wrap around code */
        if (player1.x <= 0) {
            player1.x = s.getScreenWidth() - 3;
        }
        if (player1.x >= s.getScreenWidth()) {
            player1.x =  3;
        }
        if (player1.y <= 0) {
            player1.y = s.getScreenHeight() - 3;
        }
        if (player1.y >= s.getScreenHeight()) {
            player1.y =  3;
        }
        
        /*
        * wait loop 
        * should be a member of the screen Skele_lib::CustomWinAPI::screen::Screen class 
        */
        Tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> difference = Tp2 - Tp1;
        while (difference.count() < (float)1.0 / fps)
        {
            Tp2 = std::chrono::system_clock::now();
            difference = Tp2 - Tp1;
        }
        /**reset the chrono time*/
        Tp1 = std::chrono::system_clock::now();
        s.writeScreen();
        frame++;
       
    }
}