// LIBRARIES AND NAMESPACES #########################################

#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <cmath>

using namespace std;


// PARAMETERS (GLOBAL CONSTS) #######################################

const int amount_of_players = 1;
const int period_mili = 700;


// SCREEN STRUCT ####################################################

struct{
    const int logic_void_pixel = 0;  // logic_snake_pixel is the snake_sense for that square
    const int logic_fruit_pixel = 2;

    const char blit_void_pixel = '.';
    const char blit_full_pixel = '@';

    const int width = 4;
    const int height = 3;
    int screen[4*3];
    const int size = width*height;

    int amount_of_void_squares = size-amount_of_players;  // += SIZE WHEN SNAKE DIES

    void generate_fruit(){  // create random value from 0 to amount_of_void_squares - them plot fruit on it
        amount_of_void_squares--;
        int r = rand()%(amount_of_void_squares);
        int fruit = 0;
        for (int i = 0; i<r; i++){
            fruit++;
            while(screen[fruit]!=logic_void_pixel) fruit++;
        }
        screen[fruit] = logic_fruit_pixel;
    }

    void blit(){
        cout << "\033[2J\033[1;1H";  // Clear screen using ANSI escape codes
        for (int x=0; x<height; x++){
            for (int y=0; y<width; y++) cout << (screen[x*width+y]==logic_void_pixel ? blit_void_pixel : blit_full_pixel) << ' ';
            cout << endl;
        }
    }

} screen;


// SNAKE STRUCT #####################################################

struct snake{
    bool isAlive = true;

    int size = 1;

    const int initial_position, initial_sense;

    bool is_key_pressed[4];  // < ^ > v order
    const string keys_addresses;

    int past_tail, new_tail;
    int past_head, new_head;

    int sense;  // left=-1, right=+1, up=-width, down=+width;  // will be plotted in screen as a logic pixel

    void read_input(){
        for (int k = 0; k < 4; k++){
            this->is_key_pressed[k] = (0x8000 & GetAsyncKeyState((unsigned char)(this->keys_addresses[k])));  // < ^ > v order
        }
    }
    void set_head_sense(){  // inputs to go backwards are ignored, snake head keep its sense
        if      (this->is_key_pressed[0] == 1 && this->sense != +1)             this->sense = -1;
        else if (this->is_key_pressed[1] == 1 && this->sense != +screen.width)  this->sense = -screen.width;
        else if (this->is_key_pressed[2] == 1 && this->sense != -1)             this->sense = +1;
        else if (this->is_key_pressed[3] == 1 && this->sense != -screen.width)  this->sense = +screen.width;
    }
    int get_tail_sense(){
        if      (this->new_tail%screen.width!=0                 && screen.screen[this->new_tail-1]             ==-1            )   return -1;              // tail isnt in left wall     and left square comes from right
        else if (this->new_tail/screen.width!=0                 && screen.screen[this->new_tail-screen.width]  ==-screen.width )   return -screen.width;   // tail isnt in ceil          and up square comes from bottom 
        else if (this->new_tail%screen.width!=screen.width-1    && screen.screen[this->new_tail+1]             ==+1            )   return +1;              // tail isnt in right wall    and right square comes from left
        else if (this->new_tail/screen.width!=screen.height-1   && screen.screen[this->new_tail+screen.width]  ==+screen.width )   return +screen.width;   // tail isnt in floor         and down square comes from up
        else                                                                                                                return this->sense;     //should enter here only while snake.size=1
    }

    snake(int initial_position, int initial_sense, string keys_addresses) : initial_position(initial_position), initial_sense(initial_sense), keys_addresses(keys_addresses){
        new_tail = initial_position;
        new_head = initial_position;
        sense = initial_sense;
    }

};


// FUNCTIONS #######################################################



// MAIN ############################################################

int main(){

 
    // SETUP GAME ##################################################

    bool is_game_over = false;

    
    // players
    /* keys addresses
    "\x25\x26\x27\x28" keys left up right down
    "" keys a w d s
    */
    snake jobert(0, 1, "\x25\x26\x27\x28"); 
    snake* players[amount_of_players] = {&jobert};

    // randomness and initials fruit
    srand(time(NULL));
    // for c in range amount of fruits
    screen.generate_fruit();


    // GAME LOOP ###################################################

    while (!is_game_over){


        // TIMING ##################################################
        
        this_thread::sleep_for(chrono::milliseconds(period_mili));


        // INPUT ###################################################

        jobert.read_input();

        jobert.set_head_sense();

        
        // LOGIC ###################################################

        // snake head projection
        jobert.past_head = jobert.new_head;
        jobert.new_head += jobert.sense;

        // check harmfull collision
        if ((jobert.new_head%screen.width != jobert.past_head%screen.width && jobert.new_head/screen.width != jobert.past_head/screen.width) || (jobert.new_head < 0 || jobert.new_head >= screen.size) || ((screen.screen[jobert.new_head]!=screen.logic_void_pixel) && (screen.screen[jobert.new_head]!=screen.logic_fruit_pixel) && (jobert.new_head!=jobert.new_tail))){  // check for (hitted wall) or (hitted ceiling or floor) or self colision
            is_game_over = true;
        }
        
        else{  // it was a legal head projection

            if (screen.screen[jobert.new_head]==screen.logic_fruit_pixel){  // eated fruit
                jobert.size++;
                screen.generate_fruit();
            }
            else {  // do not eated fruit
                // loses tail
                jobert.past_tail = jobert.new_tail;
                jobert.new_tail += jobert.get_tail_sense();
                screen.screen[jobert.past_tail] = screen.logic_void_pixel;
            }
            // gains head
            screen.screen[jobert.new_head] = jobert.sense;
        }


        // BLIT ####################################################

        screen.blit();


    }


    cout << "\ngame over\n" << endl;
    return 0;
}
