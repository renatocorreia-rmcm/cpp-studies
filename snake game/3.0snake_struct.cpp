// LIBRARIES AND NAMESPACES #########################################

#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <cmath>

using namespace std;


// SNAKE STRUCT #####################################################

struct snake{
    bool isAlive = true;

    int size = 1;

    const int initial_position, initial_sense;

    bool is_key_pressed[4];  // < ^ > v order  // maybe use class to have method snake.getinput - would  use own keys and after would be able to get snake.iskeypressed[k]
    const string keys_addresses;

    int past_tail, new_tail;
    int past_head, new_head;

    int sense;  // left=-1, right=+1, up=-width, down=+width;  // will be plotted in screen as a logic pixel

    snake(int initial_position, int initial_sense, string keys_addresses) : initial_position(initial_position), initial_sense(initial_sense), keys_addresses(keys_addresses){
        new_tail = initial_position;
        new_head = initial_position;
        sense = initial_sense;
    }

};


// PARAMETERS (GLOBAL CONSTS) #######################################

const int amount_of_players = 1;

const int logic_void_pixel = 0;  // logic_snake_pixel is the snake_sense for that square
const int logic_fruit_pixel = 2;

const char blit_void_pixel = '.';
const char blit_full_pixel = '@';

const int screen_width = 4;
const int screen_height = 3;
const int screen_size = screen_width*screen_height;

const int period_mili = 700;


// FUNCTIONS #######################################################

int get_tail_sense(int* screen, snake* player){  // here screen is a pointer that holds the address to screen first element  // here player is a reference to a snake instance - should pass only snake.new_tail as tail instead?
    if      (player->new_tail%screen_width!=0               && screen[player->new_tail-1]               ==-1            )   return -1;              // tail isnt in left wall     and left square comes from right
    else if (player->new_tail/screen_width!=0               && screen[player->new_tail-screen_width]    ==-screen_width )   return -screen_width;   // tail isnt in ceil          and up square comes from bottom 
    else if (player->new_tail%screen_width!=screen_width-1  && screen[player->new_tail+1]               ==+1            )   return +1;              // tail isnt in right wall    and right square comes from left
    else if (player->new_tail/screen_width!=screen_height-1 && screen[player->new_tail+screen_width]    ==+screen_width )   return +screen_width;   // tail isnt in floor         and down square comes from up
    else                                                                                                                    return player->sense;   //should enter here only while snake.size=1
}

void generate_fruit(int* screen, int* amount_of_void_squares){  // set amount_of_void_squares global or create a Game class
    // create random value from 0 to amount_of_void_squares - them plot fruit on it
    *amount_of_void_squares -= 1;
    int r = rand()%(*amount_of_void_squares);
    int fruit = 0;
    for (int i = 0; i<r; i++){
        fruit+=1;
        while(screen[fruit]!=logic_void_pixel){
            fruit+=1;
        }
    }
    screen[fruit] = logic_fruit_pixel;
}


// MAIN ############################################################

int main(){

 
    // SETUP GAME ##################################################

    bool is_game_over = false;

    // screen
    int screen[screen_size];  // create screen 
    for (int i = 0; i<=screen_size; i++) screen[i] = logic_void_pixel;  // set screen as an array full of void

    int amount_of_void_squares = screen_size-amount_of_players;  // -- every generate_fruit()  // += SIZE WHEN SNAKE DIES

    // players
    /*
    "\x25\x26\x27\x28" keys left up right down
    "" keys a w d s
    */
    snake jobert(10, 1, "\x25\x26\x27\x28"); 
    snake* players[amount_of_players] = {&jobert};

    // randomness and fruit
    srand(time(NULL));
    generate_fruit(screen, &amount_of_void_squares);  // pass address to screen first element


    // GAME LOOP ###################################################

    while (!is_game_over){


        // TIMING ##################################################
        
        this_thread::sleep_for(chrono::milliseconds(period_mili));


        // INPUT ###################################################

        for (int k = 0; k < 4; k++){
            jobert.is_key_pressed[k] = (0x8000 & GetAsyncKeyState((unsigned char)(jobert.keys_addresses[k])));  // < ^ > v order
        }

        // assign sense. inputs to go backwards are ignored, snake keep his sense
        if      (jobert.is_key_pressed[0] == 1 && jobert.sense != +1)             jobert.sense = -1;
        else if (jobert.is_key_pressed[1] == 1 && jobert.sense != +screen_width)  jobert.sense = -screen_width;
        else if (jobert.is_key_pressed[2] == 1 && jobert.sense != -1)             jobert.sense = +1;
        else if (jobert.is_key_pressed[3] == 1 && jobert.sense != -screen_width)  jobert.sense = +screen_width;

        
        // LOGIC ###################################################

        // snake head projection
        jobert.past_head = jobert.new_head;
        jobert.new_head += jobert.sense;

        // check harmfull collision
        if ((jobert.new_head%screen_width != jobert.past_head%screen_width && jobert.new_head/screen_width != jobert.past_head/screen_width) || (jobert.new_head < 0 || jobert.new_head >= screen_size) || ((screen[jobert.new_head]!=logic_void_pixel) && (screen[jobert.new_head]!=logic_fruit_pixel) && (jobert.new_head!=jobert.new_tail))){  // check for (hitted wall) or (hitted ceiling or floor) or self colision  // since all operands are int, / works as integer division
            is_game_over = true;
        }
        
        else{  // it was a legal head projection

            if (screen[jobert.new_head]==logic_fruit_pixel){  // eated fruit
                jobert.size+=1;
                generate_fruit(screen, &amount_of_void_squares);
            }
            else {  // do not eated fruit
                // loses tail
                jobert.past_tail = jobert.new_tail;
                jobert.new_tail += get_tail_sense(screen, &jobert);  // pass address to first element of screen
                screen[jobert.past_tail] = logic_void_pixel;
            }
            // gains head
            screen[jobert.new_head] = jobert.sense;

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
