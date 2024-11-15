//font: https://patorjk.com/software/taag/#p=display&f=ANSI%20Regular&t=Type%20Something%20





// LIBRARIES AND NAMESPACES #########################################

#include <LedControl.h>


// MATRIX SETTINGS ##################################################

const int din_pin = 4;
const int load_pin = 3;
const int clk_pin = 2;
LedControl matrix = LedControl(din_pin, clk_pin, load_pin, 1);

/*
███████  ██████ ██████  ███████ ███████ ███    ██      ██████  ██       ██████  ██████   █████  ██      ███████
██      ██      ██   ██ ██      ██      ████   ██     ██       ██      ██    ██ ██   ██ ██   ██ ██      ██
███████ ██      ██████  █████   █████   ██ ██  ██     ██   ███ ██      ██    ██ ██████  ███████ ██      ███████
     ██ ██      ██   ██ ██      ██      ██  ██ ██     ██    ██ ██      ██    ██ ██   ██ ██   ██ ██           ██
███████  ██████ ██   ██ ███████ ███████ ██   ████      ██████  ███████  ██████  ██████  ██   ██ ███████ ███████
*/

const int logic_void_pixel = 0;  // logic_snake_pixel is the snake_sense for that square
const int logic_fruit_pixel = 2;

const int screen_width = 8;
const int screen_height = 8;
const int screen_size = screen_width * screen_height;
int screen[screen_size];  // x=n%h, y=n/w

int amount_of_void_squares = screen_size;  // += SIZE WHEN SNAKE DIES

int fruit_position;
int r;

void generate_fruit(){  // create random value from 0 to amount_of_void_squares - them plot fruit_position on it
    
    r = random(amount_of_void_squares);

    fruit_position = 0;
    
    while(screen[fruit_position] != logic_void_pixel) fruit_position++;  // consider if r = 0 and 0 is occupied

    for (int i = 0; i<r; i++){
        fruit_position++;
        while(screen[fruit_position] != logic_void_pixel) fruit_position++;  // skip occupied values on counting
    }
    screen[fruit_position] = logic_fruit_pixel;
    amount_of_void_squares--;

}

void blit(){
    for (int i = 0; i< screen_size; i++){
      matrix.setLed(0, i/screen_width, i%screen_height, screen[i]!=logic_void_pixel);
      if (screen[i]==logic_fruit_pixel){
      }
    }
}

void clear(int* amount_of_void_squares){
  memset(screen, logic_void_pixel, screen_size * sizeof(int));
  *amount_of_void_squares = screen_size;
  matrix.clearDisplay(0);
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

    const int x_pin, y_pin, sw_pin;

    const int joystick_sensibility = 20;

    char pressed_key;

    int past_tail, past_head;
    int current_tail, new_head;

    int sense;  // left=-1, right=+1, up=-width, down=+width;  // will be plotted in screen as a logic pixel

    void read_input(){
      int x = analogRead(this->x_pin) - 512;
      int y = analogRead(this->y_pin) - 512;
      int sw = digitalRead(this->sw_pin);
      
      if (abs(x)>joystick_sensibility || abs(y)>joystick_sensibility) {  // only update pressed_key if input is greater than joystick_sensibility
        if (abs(x)>abs(y))  this->pressed_key = (x<0 ? 'l' : 'r');
        else                this->pressed_key = (y<0 ? 'u' : 'd');
      }
    }

    void set_head_sense(){  // can be merged with read_input()
        // inputs to go backwards are ignored, snake head keep its sense
        // use 4 buttons with posedge interrupt
        if      (this->pressed_key == 'l' && this->sense != +1)             this->sense = -1;
        else if (this->pressed_key == 'u' && this->sense != +screen_width)  this->sense = -screen_width;
        else if (this->pressed_key == 'r' && this->sense != -1)             this->sense = +1;
        else if (this->pressed_key == 'd' && this->sense != -screen_width)  this->sense = +screen_width;
    }

    int get_tail_sense(){
        if      (this->current_tail%screen_width!=0                 && screen[this->current_tail-1]             ==-1            )   return -1;              // tail isnt in left wall     and left square comes from right
        else if (this->current_tail/screen_width!=0                 && screen[this->current_tail-screen_width]  ==-screen_width )   return -screen_width;   // tail isnt in ceil          and up square comes from bottom
        else if (this->current_tail%screen_width!=screen_width-1    && screen[this->current_tail+1]             ==+1            )   return +1;              // tail isnt in right wall    and right square comes from left
        else if (this->current_tail/screen_width!=screen_height-1   && screen[this->current_tail+screen_width]  ==+screen_width )   return +screen_width;   // tail isnt in floor         and down square comes from up
        else                                                                                                                return this->sense;     //should enter here only while snake.size=1
    }

    snake(int initial_position, char initial_sense, int x_pin, int y_pin, int sw_pin) : initial_position(initial_position), pressed_key(initial_sense), x_pin(x_pin), y_pin(y_pin), sw_pin(sw_pin){
      past_tail = initial_position;
      current_tail = initial_position;
      new_head = initial_position;
      switch(initial_sense){
        case 'l': sense = -1;               break;
        case 'u': sense =  -screen_width;   break;
        case 'r': sense = +1;               break;
        case 'd': sense = +screen_width;    break;
      }
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
void wait_input(int* players, int amount_of_players, int delaytime, int iterations){
  for (int i = 0; i<iterations; i++){
    for (int p = 0; p<amount_of_players; p++){
      players[p].read_input();
    }
    delay(delaytime/iterations);
  }
}
*/
/*
███████ ███████ ████████ ██    ██ ██████  
██      ██         ██    ██    ██ ██   ██ 
███████ █████      ██    ██    ██ ██████  
     ██ ██         ██    ██    ██ ██      
███████ ███████    ██     ██████  ██      
*/
void setup() {+++++++

  matrix.shutdown(0, false);
  matrix.setIntensity(0, 0);
  matrix.clearDisplay(0);

  randomSeed(analogRead(0));
}


/*
██       ██████   ██████  ██████  
██      ██    ██ ██    ██ ██   ██ 
██      ██    ██ ██    ██ ██████  
██      ██    ██ ██    ██ ██      
███████  ██████   ██████  ██      
*/
void loop() {  // 1 iteration = 1 match


    /*
    ███████ ███████ ████████ ██    ██ ██████      ███    ███  █████  ████████  ██████ ██   ██ 
    ██      ██         ██    ██    ██ ██   ██     ████  ████ ██   ██    ██    ██      ██   ██ 
    ███████ █████      ██    ██    ██ ██████      ██ ████ ██ ███████    ██    ██      ███████
         ██ ██         ██    ██    ██ ██          ██  ██  ██ ██   ██    ██    ██      ██   ██ 
    ███████ ███████    ██     ██████  ██          ██      ██ ██   ██    ██     ██████ ██   ██ 
    */

    bool is_game_over = false;
    
    const int period_mili = 200;  


    // PLAYERS
    const int amount_of_players = 1;

    snake jobert(24, 'r', A6, A7, 12);
    snake* players[amount_of_players] = {&jobert};  // auto add player in players[] on construction

    pinMode(jobert.x_pin, INPUT);  // for p in range amount of players
    pinMode(jobert.y_pin, INPUT);
    pinMode(jobert.sw_pin, INPUT_PULLUP);


    // SCREEN
    clear(&amount_of_void_squares);
    screen[jobert.new_head] = jobert.sense;
    blit();

    amount_of_void_squares-=amount_of_players;

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

      delay(period_mili);


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
          || ((screen[jobert.new_head]!=logic_void_pixel) && (screen[jobert.new_head]!=logic_fruit_pixel) && (jobert.new_head!=jobert.current_tail))){  // check hitted itself

          is_game_over = true;
      }

      else{  // it was a legal head projection

          if (screen[jobert.new_head]==logic_fruit_pixel){  // eated fruit
              jobert.size++;
              generate_fruit();
          }
          else {  // do not eated fruit
              // loses tail
              jobert.past_tail = jobert.current_tail;
              jobert.current_tail += jobert.get_tail_sense();
              screen[jobert.past_tail] = logic_void_pixel;
          }
          // gains head
          screen[jobert.new_head] = jobert.sense;
      }


      // BLIT ####################################################
      blit();


  }

}
