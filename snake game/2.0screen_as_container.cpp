// LIBRARIES ###################################################

#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <cmath>
using namespace std;


// FUNCTIONS ###################################################

int get_tail_sense(int* screen, int tail, int sense){
    if      (tail%8!=0 && screen[tail-1] == -1)     return -1;  // tail isnt in left wall and left square comes from right
    else if (tail/8!=0 && screen[tail-8] == -8)     return -8;  // tail isnt in ceil and up square comes from bottom 
    else if (tail%8!=7 && screen[tail+1] == +1)     return +1;  // tail isnt in right wall and right square comes from left
    else if (tail/8!=7 && screen[tail+8] == +8)     return +8;  // tail isnt in floor and down square comes from up
    else                                            return sense;  //should enter here only in first move
}


// MAIN ########################################################

int main(){


    // SETUP GAME ##################################################

    bool is_game_over = false;

    // logic pixels
    int void_pixel = 0;
    //int snake_pixel = 1;  // use sense instead, to get tail sense after
    int fruit_pixel = 2;

    // blit pixels
    char blit_void_pixel = '.';
    char blit_snake_pixel = '@';
    char blit_fruit_pixel = 'o';
    char buffer_ch;

    // screen
    int screen_width = 8, screen_height = 8, screen_size = screen_width*screen_height;
    int screen[screen_size];  // gonna store all visualizable
    for (int i = 0; i<=screen_size; i++) screen[i] = void_pixel;  // set screen as an array full of void

    // input values array
    bool is_key_pressed[4];  // < ^ > v order

    // randomness and fruit
    srand(time(NULL));
    int r;
    int fruit = rand()%screen_size;
    screen[fruit] = fruit_pixel;


    // SETUP SNAKE ##################################################

    int snake_size = 1;
    int position = 32;

    int past_tail;
    int new_tail = position;

    int past_head;
    int new_head = position;

    int sense = +1;  // left=-1, right=+1, up=-width, down=+width;




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
        else if (is_key_pressed[1] == 1 && sense != +screen_width) sense = -screen_width;
        else if (is_key_pressed[2] == 1 && sense != -1)     sense = +1;
        else if (is_key_pressed[3] == 1 && sense != -screen_width) sense = +screen_width;

        
        // LOGIC ###################################################

        // snake head projection
        past_head = new_head;
        new_head += sense;

        // check harmfull collision
        if ((new_head%8 != past_head%8 && new_head/8 != past_head/8) || (new_head < 0 || new_head > 63) || ((screen[new_head]!=void_pixel) && (screen[new_head]!=fruit_pixel) && (new_head!=new_tail))){  // check for (hitted wall) or (hitted ceiling or floor) or self colision  // since all operands are int, / works as integer division
            is_game_over = true;
        }
        
        else{  // it was a legal move

            if (screen[new_head]==fruit_pixel){  // eated fruit
                snake_size+=1;
                // generate new fruit - create random value from 0 to amount_of_void_squares
                r = rand()%(screen_size - snake_size);
                fruit = 0;
                for (int i = 0; i<r; i++){
                    fruit+=1;
                    while(screen[fruit]!=void_pixel){
                        fruit+=1;
                    }
                }
                screen[fruit] = fruit_pixel;
            }
            else {  // do not eated fruit
                // loses tail
                past_tail = new_tail;
                new_tail += get_tail_sense(screen, new_tail, sense);
                screen[past_tail] = void_pixel;
            }
            // gains head
            screen[new_head] = sense;

        }


        // BLIT ####################################################

        cout << "\033[2J\033[1;1H";  // Clear screen using ANSI escape codes
        cout << "# # # # # # # # # #" << endl;
        for (int x=0; x<screen_height; x++){
            cout << "# ";
            for (int y=0; y<screen_width; y++){
                switch (screen[x*screen_width+y]){
                    case 0: buffer_ch = ' '; break;
                    case -1: buffer_ch = '<'; break;
                    case -8: buffer_ch = '^'; break;
                    case +1: buffer_ch = '>'; break;
                    case +8: buffer_ch = 'v'; break;
                    case +2: buffer_ch = 'o'; break;
                }
                if (x*screen_width+y == new_head){
                    buffer_ch = '#';
                }
                cout<<buffer_ch<<' ';
            }
            cout << '#' << endl;
        }
        cout << "# # # # # # # # # #" << endl;


    }

    cout << "\ngame over\n" << endl;
    return 0;
}
