// set private and public
// breakdown game steps

#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <cmath>

using namespace std;


/*
 ██████  ██       ██████  ██████   █████  ██           ██████  ██████  ███    ██ ███████ ████████ ███████
██       ██      ██    ██ ██   ██ ██   ██ ██          ██      ██    ██ ████   ██ ██         ██    ██
██   ███ ██      ██    ██ ██████  ███████ ██          ██      ██    ██ ██ ██  ██ ███████    ██    ███████
██    ██ ██      ██    ██ ██   ██ ██   ██ ██          ██      ██    ██ ██  ██ ██      ██    ██         ██
 ██████  ███████  ██████  ██████  ██   ██ ███████      ██████  ██████  ██   ████ ███████    ██    ███████
 */

const int amount_of_players = 1;
const int period_mili = 700;


/*
███████  ██████ ██████  ███████ ███████ ███    ██      ██████  ██       ██████  ██████   █████  ██      ███████
██      ██      ██   ██ ██      ██      ████   ██     ██       ██      ██    ██ ██   ██ ██   ██ ██      ██
███████ ██      ██████  █████   █████   ██ ██  ██     ██   ███ ██      ██    ██ ██████  ███████ ██      ███████
     ██ ██      ██   ██ ██      ██      ██  ██ ██     ██    ██ ██      ██    ██ ██   ██ ██   ██ ██           ██
███████  ██████ ██   ██ ███████ ███████ ██   ████      ██████  ███████  ██████  ██████  ██   ██ ███████ ███████
*/

const int logic_void_pixel = 0;  // logic_snake_pixel is the snake_sense for that square
const int logic_fruit_pixel = 2;

const char blit_void_pixel = '.';
const char blit_full_pixel = '@';

const int screen_width = 5;
const int screen_height = 4;
int screen[screen_width * screen_height];
const int screen_size = screen_width * screen_height;

int amount_of_void_squares = screen_size - amount_of_players;  // += SIZE WHEN SNAKE DIES


int fruit_position;
int r;

void generate_fruit(){  // create random value from 0 to amount_of_void_squares - them plot fruit_position on it
    amount_of_void_squares--;
    r = (rand()%(amount_of_void_squares)) + 1;
    fruit_position = 0;
    // consider if r = 0 and 0 is occupied
    for (int i = 0; i<r; i++){
        fruit_position++;
        while(screen[fruit_position] != logic_void_pixel) fruit_position++;  // skip occupied values on counting
    }
    screen[fruit_position] = logic_fruit_pixel;
}

void blit(){
    //cout << "\033[2J\033[1;1H";  // Clear screen using ANSI escape codes
    cout << "\n\n\n\n\n";
    for (int x=0; x < screen_height; x++){
        for (int y=0; y < screen_width; y++) {
            cout << (screen[x * screen_width + y] == logic_void_pixel ? blit_void_pixel : blit_full_pixel) << ' ';
        }
        cout << endl;
    }
}


/*
███████ ███    ██  █████  ██   ██ ███████     ███████ ████████ ██████  ██    ██  ██████ ████████
██      ████   ██ ██   ██ ██  ██  ██          ██         ██    ██   ██ ██    ██ ██         ██
███████ ██ ██  ██ ███████ █████   █████       ███████    ██    ██████  ██    ██ ██         ██
     ██ ██  ██ ██ ██   ██ ██  ██  ██               ██    ██    ██   ██ ██    ██ ██         ██
███████ ██   ████ ██   ██ ██   ██ ███████     ███████    ██    ██   ██  ██████   ██████    ██
*/

struct snake{
    bool isAlive = true;

    int size = 1;

    const int initial_position, initial_sense;

    bool is_key_pressed[4];  // < ^ > v order
    const string keys_addresses;

    int past_tail, past_head;
    int new_tail, new_head;

    int sense;  // left=-1, right=+1, up=-width, down=+width;  // will be plotted in screen as a logic pixel

    void read_input(){
        for (int k = 0; k < 4; k++){
            this->is_key_pressed[k] = (0x8000 & GetAsyncKeyState((unsigned char)(this->keys_addresses[k])));  // < ^ > v order
        }
    }

    void set_head_sense(){  // inputs to go backwards are ignored, snake head keep its sense
        // in arduino use 4 buttons with posedge interrupt
        if      (this->is_key_pressed[0] == 1 && this->sense != +1)             this->sense = -1;
        else if (this->is_key_pressed[1] == 1 && this->sense != +screen_width)  this->sense = -screen_width;
        else if (this->is_key_pressed[2] == 1 && this->sense != -1)             this->sense = +1;
        else if (this->is_key_pressed[3] == 1 && this->sense != -screen_width)  this->sense = +screen_width;
    }

    int get_tail_sense(){
        if      (this->new_tail%screen_width!=0                 && screen[this->new_tail-1]             ==-1            )   return -1;              // tail isnt in left wall     and left square comes from right
        else if (this->new_tail/screen_width!=0                 && screen[this->new_tail-screen_width]  ==-screen_width )   return -screen_width;   // tail isnt in ceil          and up square comes from bottom
        else if (this->new_tail%screen_width!=screen_width-1    && screen[this->new_tail+1]             ==+1            )   return +1;              // tail isnt in right wall    and right square comes from left
        else if (this->new_tail/screen_width!=screen_height-1   && screen[this->new_tail+screen_width]  ==+screen_width )   return +screen_width;   // tail isnt in floor         and down square comes from up
        else                                                                                                                return this->sense;     //should enter here only while snake.size=1
    }

    snake(int initial_position, int initial_sense, string keys_addresses) : initial_position(initial_position), initial_sense(initial_sense), keys_addresses(keys_addresses){
        new_tail = initial_position;
        new_head = initial_position;
        sense = initial_sense;
    }

};


/*
███████ ██    ██ ███    ██  ██████ ████████ ██  ██████  ███    ██ ███████
██      ██    ██ ████   ██ ██         ██    ██ ██    ██ ████   ██ ██
█████   ██    ██ ██ ██  ██ ██         ██    ██ ██    ██ ██ ██  ██ ███████
██      ██    ██ ██  ██ ██ ██         ██    ██ ██    ██ ██  ██ ██      ██
██       ██████  ██   ████  ██████    ██    ██  ██████  ██   ████ ███████
*/



/*
███    ███  █████  ██ ███    ██
████  ████ ██   ██ ██ ████   ██
██ ████ ██ ███████ ██ ██ ██  ██
██  ██  ██ ██   ██ ██ ██  ██ ██
██      ██ ██   ██ ██ ██   ████
*/

int main(){

    /*
    ███████ ███████ ████████ ██    ██ ██████       ██████   █████  ███    ███ ███████
    ██      ██         ██    ██    ██ ██   ██     ██       ██   ██ ████  ████ ██
    ███████ █████      ██    ██    ██ ██████      ██   ███ ███████ ██ ████ ██ █████
         ██ ██         ██    ██    ██ ██          ██    ██ ██   ██ ██  ██  ██ ██
    ███████ ███████    ██     ██████  ██           ██████  ██   ██ ██      ██ ███████
     */

    bool is_game_over = false;


    // PLAYERS
    
    snake jobert(0, 1, "\x25\x26\x27\x28");
    snake* players[amount_of_players] = {&jobert};


    // RANDOMNESS AND INITIAL FRUIT

    srand(time(NULL));
    // for c in range amount of fruits
    generate_fruit();


    /*
     ██████   █████  ███    ███ ███████     ██       ██████   ██████  ██████  
    ██       ██   ██ ████  ████ ██          ██      ██    ██ ██    ██ ██   ██ 
    ██   ███ ███████ ██ ████ ██ █████       ██      ██    ██ ██    ██ ██████  
    ██    ██ ██   ██ ██  ██  ██ ██          ██      ██    ██ ██    ██ ██      
     ██████  ██   ██ ██      ██ ███████     ███████  ██████   ██████  ██
     */

    while (!is_game_over){


        // TIMING ##################################################

        this_thread::sleep_for(chrono::milliseconds(period_mili));


        // INPUT ###################################################

        // for player in players
        jobert.read_input();

        jobert.set_head_sense();


        // LOGIC ###################################################

        // snake head projection
        jobert.past_head = jobert.new_head;
        jobert.new_head += jobert.sense;

        // check harmfull collision
        if ((jobert.new_head%screen_width != jobert.past_head%screen_width && jobert.new_head/screen_width != jobert.past_head/screen_width)  // check hitted wall: x1!=x2 and y1!=y2
            || (jobert.new_head < 0 || jobert.new_head >= screen_size)  // check hitted ceilling
            || ((screen[jobert.new_head]!=logic_void_pixel) && (screen[jobert.new_head]!=logic_fruit_pixel) && (jobert.new_head!=jobert.new_tail))){  // check hitted itself

            is_game_over = true;
        }

        else{  // it was a legal head projection

            if (screen[jobert.new_head]==logic_fruit_pixel){  // eated fruit
                jobert.size++;
                generate_fruit();
            }
            else {  // do not eated fruit
                // loses tail
                jobert.past_tail = jobert.new_tail;
                jobert.new_tail += jobert.get_tail_sense();
                screen[jobert.past_tail] = logic_void_pixel;
            }
            // gains head
            screen[jobert.new_head] = jobert.sense;
        }


        // BLIT ####################################################

        blit();


    }


    cout << "\ngame over\n" << endl;
    return 0;
}
