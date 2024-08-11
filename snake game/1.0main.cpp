// LIBRARIES ###################################################

#include <iostream>
#include <deque>
#include <vector>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <cmath>
using namespace std;

// FUNCTIONS ###################################################

bool check_self_colision(int new_head, deque<int> positions){
    bool self_colision = false;
    positions.pop_front();
    for (int position: positions){
        if (new_head == position){
            self_colision = true;
            break;
        }
    }
    return self_colision;
}


// GAME ########################################################

int main(){


    // SETUP GAME ##################################################

    char empty = '.';
    char full = '@';

    int width = 8, height = 8, size = width*height;  // also change arrays sizes on their initializations
    char screen[64];  // gonna store all visualizable
    for (int i = 0; i<=size; i++) screen[i] = empty;  // set screen as an array full of 0s

    bool is_game_over = false;

    bool is_key_pressed[4];  // < ^ > v order

    srand(time(NULL));
    int r;

    vector<int> to_turn_off;  // contains tail
    int fruit = rand()%64;
    vector<int> to_turn_on = {fruit};  // contains head and fruit




    // SETUP SNAKE ##################################################

    int initial_position = 32;
    int past_head, new_head;
    deque<int> positions = {initial_position};  // all squares occupied by snake
    int sense = +1;  // left-1, right+1, up-width, down+width;


    // GAME LOOP ###################################################

    while (!is_game_over){


        // TIMING ##################################################
        
        this_thread::sleep_for(chrono::milliseconds(500));


        // INPUT ###################################################

        for (int k = 0; k < 4; k++){
            is_key_pressed[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x25\x26\x27\x28"[k])));
        }

        // this if-else block assign sense. inputs to go backwards are ignored, snake keep his sense
        if      (is_key_pressed[0] == 1 && sense != +1)     sense = -1;
        else if (is_key_pressed[1] == 1 && sense != +width) sense = -width;
        else if (is_key_pressed[2] == 1 && sense != -1)     sense = +1;
        else if (is_key_pressed[3] == 1 && sense != -width) sense = +width;

        
        // LOGIC ###################################################

        past_head = positions.back();  // positions is a deque, wich do not have a end, so try to access positions[-1] throws a segmentation fault error
        new_head = past_head+sense;

        if ((new_head%8 != past_head%8 and int(new_head)/8 != int(past_head)/8) || (new_head < 0 or new_head > 63) || check_self_colision(new_head, positions)){  // check for (hitted wall) or (hitted ceiling or floor) or self colision
            is_game_over = true;
        }
        
        else{  // it was a legal move
            // gains head
            positions.push_back(new_head);
            to_turn_on.push_back(new_head);

            if (new_head==fruit){  // eated fruit
                // generate new fruit - create random value from 0 to amount_of_blank_squares
                r = rand()%(64 - positions.size());
                fruit = 0;
                for (int i = 0; i<r; i++){
                    fruit+=1;
                    while(screen[fruit]==full){
                        fruit+=1;
                    }
                }
                to_turn_on.push_back(fruit);
            }
            else{  // do not eated fruit

                // loses tail
                int tail = positions[0];
                positions.pop_front();
                to_turn_off.push_back(tail);
            }
        }


        // RENDER OUTPUT ###########################################


 
        // DRAW ####################################################

        for (int i = to_turn_off.size()-1; i>=0; i--){
            screen[to_turn_off[i]] = empty;
            to_turn_off.pop_back();
        }

        for (int i = to_turn_on.size()-1; i>=0; i--){
            screen[to_turn_on[i]] = (full);
            to_turn_on.pop_back();
        }


        // BLIT ####################################################

        cout << "\033[2J\033[1;1H";  // Clear screen using ANSI escape codes
        for (int x=0; x<height; x++){
            for (int y=0; y<width; y++){
                cout<<screen[x*width+y]<<' ';
            }
            cout << endl;
        }

    }

    cout << "\ngame over\n" << endl;
    return 0;
}
