// LIBRARIES AND NAMESPACES #########################################

#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <cmath>

using namespace std;


// PARAMETERS (GLOBAL CONSTS) #######################################

const int logic_void_pixel = 0;
const int logic_fruit_pixel = 2;

const char blit_void_pixel = '.';
const char blit_full_pixel = '@';

const int screen_width = 20;
const int screen_height = 10;
const int screen_size = screen_width*screen_height;

const int initial_position = 2;
const int initial_sense = +1;  // left=-1, right=+1, up=-width, down=+width;

const int period_mili = 300;


// FUNCTIONS #######################################################

int get_tail_sense(int* screen, int tail, int sense){
    if      (tail%screen_width!=0               && screen[tail-1]               ==-1            )   return -1;              // tail isnt in left wall and left square comes from right
    else if (tail/screen_width!=0               && screen[tail-screen_width]    ==-screen_width )   return -screen_width;   // tail isnt in ceil and up square comes from bottom 
    else if (tail%screen_width!=screen_width-1  && screen[tail+1]               ==+1            )   return +1;              // tail isnt in right wall and right square comes from left
    else if (tail/screen_width!=screen_height-1 && screen[tail+screen_width]    ==+screen_width )   return +screen_width;   // tail isnt in floor and down square comes from up
    else                                                                                            return sense;   //should enter here only while snake_size=1
}


// MAIN ############################################################

int main(){

 
    // SETUP GAME ##################################################

    bool is_game_over = false;

    // logic pixels
    // setted in parameters

    // blit pixels
    // setted in parameters

    // screen
    int screen[screen_size];  // create screen
    for (int i = 0; i<=screen_size; i++) screen[i] = logic_void_pixel;  // set screen as an array full of void

    // input values array
    bool is_key_pressed[4];  // < ^ > v order

    // randomness and fruit
    srand(time(NULL));
    int r;
    int fruit = rand()%screen_size;
    screen[fruit] = logic_fruit_pixel;


    // SETUP SNAKE #################################################

    int snake_size = 1;

    int past_tail;
    int new_tail = initial_position;

    int past_head;
    int new_head = initial_position;

    int sense = initial_sense;  // left=-1, right=+1, up=-width, down=+width;  // will be plotted in screen as a logic pixel


    // GAME LOOP ###################################################

    while (!is_game_over){


        // TIMING ##################################################
        
        this_thread::sleep_for(chrono::milliseconds(period_mili));


        // INPUT ###################################################

        for (int k = 0; k < 4; k++){
            is_key_pressed[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x25\x26\x27\x28"[k])));  // < ^ > v order
        }

        // assign sense. inputs to go backwards are ignored, snake keep his sense
        if      (is_key_pressed[0] == 1 && sense != +1)             sense = -1;
        else if (is_key_pressed[1] == 1 && sense != +screen_width)  sense = -screen_width;
        else if (is_key_pressed[2] == 1 && sense != -1)             sense = +1;
        else if (is_key_pressed[3] == 1 && sense != -screen_width)  sense = +screen_width;

        
        // LOGIC ###################################################

        // snake head projection
        past_head = new_head;
        new_head += sense;

        // check harmfull collision
        if ((new_head%screen_width != past_head%screen_width && new_head/screen_width != past_head/screen_width) || (new_head < 0 || new_head >= screen_size) || ((screen[new_head]!=logic_void_pixel) && (screen[new_head]!=logic_fruit_pixel) && (new_head!=new_tail))){  // check for (hitted wall) or (hitted ceiling or floor) or self colision  // since all operands are int, / works as integer division
            is_game_over = true;
        }
        
        else{  // it was a legal head projection

            if (screen[new_head]==logic_fruit_pixel){  // eated fruit
                snake_size+=1;
                // generate new fruit - create random value from 0 to amount_of_void_squares
                r = rand()%(screen_size - snake_size);
                fruit = 0;
                for (int i = 0; i<r; i++){
                    fruit+=1;
                    while(screen[fruit]!=logic_void_pixel){
                        fruit+=1;
                    }
                }
                screen[fruit] = logic_fruit_pixel;
            }
            else {  // do not eated fruit
                // loses tail
                past_tail = new_tail;
                new_tail += get_tail_sense(screen, new_tail, sense);
                screen[past_tail] = logic_void_pixel;
            }
            // gains head
            screen[new_head] = sense;

        }


        // BLIT ####################################################

        cout << "\033[2J\033[1;1H";  // Clear screen using ANSI escape codes
        for (int x=0; x<screen_height; x++){
            for (int y=0; y<screen_width; y++){
                cout << (screen[x*screen_width+y]==logic_void_pixel ? blit_void_pixel : blit_full_pixel) << ' ';
            }
            cout << endl;
        }

    }


    cout << "\ngame over\n" << endl;
    return 0;
}
