//font: https://patorjk.com/software/taag/#p=display&f=ANSI%20Regular&t=Type%20Something%20


/*
██████   █████   ██████ ██   ██ ██       ██████   ██████  
██   ██ ██   ██ ██      ██  ██  ██      ██    ██ ██       
██████  ███████ ██      █████   ██      ██    ██ ██   ███ 
██   ██ ██   ██ ██      ██  ██  ██      ██    ██ ██    ██ 
██████  ██   ██  ██████ ██   ██ ███████  ██████   ██████  


  *declare non-const global variables, initialize only in match setup
  *there are variables being declared in loop()

  *blinking head (and tail? should help on very large snakes)

  *amount of fruits inv proportional to snake size
  *speed inv proportional to snake size
  *chord octave proportional to snake size
*/


/*
██      ██ ██████  ██████   █████  ██████  ██ ███████ ███████ 
██      ██ ██   ██ ██   ██ ██   ██ ██   ██ ██ ██      ██      
██      ██ ██████  ██████  ███████ ██████  ██ █████   ███████ 
██      ██ ██   ██ ██   ██ ██   ██ ██   ██ ██ ██           ██ 
███████ ██ ██████  ██   ██ ██   ██ ██   ██ ██ ███████ ███████ 
*/

#include <LedControl.h>


/*
██████  ██    ██ ███████ ███████ ███████ ██████  
██   ██ ██    ██    ███     ███  ██      ██   ██ 
██████  ██    ██   ███     ███   █████   ██████  
██   ██ ██    ██  ███     ███    ██      ██   ██ 
██████   ██████  ███████ ███████ ███████ ██   ██ 
*/

struct buzzer{
  const int pin = 5;
  const int min_freq = 300;
  const int max_freq = 900;

} buzzer;



/*
███████  ██████ ██████  ███████ ███████ ███    ██     ███████ ████████ ██████  ██    ██  ██████ ████████ 
██      ██      ██   ██ ██      ██      ████   ██     ██         ██    ██   ██ ██    ██ ██         ██    
███████ ██      ██████  █████   █████   ██ ██  ██     ███████    ██    ██████  ██    ██ ██         ██    
     ██ ██      ██   ██ ██      ██      ██  ██ ██          ██    ██    ██   ██ ██    ██ ██         ██    
███████  ██████ ██   ██ ███████ ███████ ██   ████     ███████    ██    ██   ██  ██████   ██████    ██    
*/

struct screen{

  // MATRIX #########################################################

  const int din_pin = 4;
  const int load_pin = 3;
  const int clk_pin = 2;

  const LedControl matrix = LedControl(din_pin, clk_pin, load_pin, 1);


  // ARRAY ##########################################################

  const int void_pixel = 0;  // snake_pixel is the snake_sense for that square
  const int fruit_pixel = 2;

  const int width = 8;
  const int height = 8;
  const int size = width * height;
  int screen[8*8];  // x=n%w, y=n/w

  int amount_of_void_pixels;


  // METHODS ########################################################

  void generate_fruit(){  // create random value from 0 to amount_of_void_squares - them plot fruit on it
      
    int r = random(amount_of_void_pixels);

    int fruit_position = 0;
    
    while(screen[fruit_position] != void_pixel) fruit_position++;  // consider if r = 0 and 0 is occupied

    for (int i = 0; i<r; i++){
      fruit_position++;
      while(screen[fruit_position] != void_pixel) fruit_position++;  // skip occupied values on counting
    }
    screen[fruit_position] = fruit_pixel;
    amount_of_void_pixels--;

  }

  void blit(){
    for (int i = 0; i< size; i++){
      matrix.setLed(0, i/width, i%width, screen[i]!=void_pixel);
      if (screen[i]==fruit_pixel){
      }
      }
  }

  void reset(){
    memset(screen, void_pixel, size * sizeof(int));
    amount_of_void_pixels = size;
    matrix.clearDisplay(0);
  }

} screen;


/*
███████ ███    ██  █████  ██   ██ ███████     ███████ ████████ ██████  ██    ██  ██████ ████████          ██         ██ ███    ██ ██ ████████ ██  █████  ██      ██ ███████  █████  ████████ ██  ██████  ███    ██ 
██      ████   ██ ██   ██ ██  ██  ██          ██         ██    ██   ██ ██    ██ ██         ██             ██         ██ ████   ██ ██    ██    ██ ██   ██ ██      ██    ███  ██   ██    ██    ██ ██    ██ ████   ██ 
███████ ██ ██  ██ ███████ █████   █████       ███████    ██    ██████  ██    ██ ██         ██        ████████████    ██ ██ ██  ██ ██    ██    ██ ███████ ██      ██   ███   ███████    ██    ██ ██    ██ ██ ██  ██ 
     ██ ██  ██ ██ ██   ██ ██  ██  ██               ██    ██    ██   ██ ██    ██ ██         ██             ██         ██ ██  ██ ██ ██    ██    ██ ██   ██ ██      ██  ███    ██   ██    ██    ██ ██    ██ ██  ██ ██ 
███████ ██   ████ ██   ██ ██   ██ ███████     ███████    ██    ██   ██  ██████   ██████    ██             ██         ██ ██   ████ ██    ██    ██ ██   ██ ███████ ██ ███████ ██   ██    ██    ██  ██████  ██   ████ 
*/

struct snake{

  // consts #######################################################

  const int left_pin;
  const int right_pin;
  const int up_pin;
  const int down_pin;
  
  const int initial_position;
  const int initial_sense;


  // non-consts ###################################################

  int past_tail, past_head;
  int current_tail, new_head;

  int sense;  // left=-1, right=+1, up=-width, down=+width;  // will be plotted in screen as a logic pixel

  int size;

  bool eated_fruit;


  // methods ########################################################

  void interrupt_left(){
    if (new_head%screen.width!=0 && ( screen.screen[new_head-1] == screen.void_pixel || screen.screen[new_head-1] == current_tail || screen.screen[new_head-1] == screen.fruit_pixel)) { // (cant be in left wall) AND (must be void OR current_tail OR fruit)
      sense = -1;
    } 
  }
  void interrupt_right(){
    if (new_head%screen.width!=screen.width-1 && ( screen.screen[new_head+1] == screen.void_pixel || screen.screen[new_head+1] == current_tail || screen.screen[new_head+1] == screen.fruit_pixel)) { // (cant be in right wall) AND (must be void OR current_tail OR fruit)
      sense = +1;
    }
  }
  void interrupt_up(){
    if (new_head/screen.width!=0 && (screen.screen[new_head-screen.width] == screen.void_pixel ||  screen.screen[new_head-screen.width]==current_tail  || screen.screen[new_head-screen.width] == screen.fruit_pixel)) { // (cant be in ceilling) AND (must be void OR current_tail OR fruit)
      sense = -screen.width;
    }
  }
  void interrupt_down(){
    if (new_head/screen.width!=screen.height-1 && (screen.screen[new_head+screen.width] == screen.void_pixel ||  screen.screen[new_head+screen.width]==current_tail  || screen.screen[new_head+screen.width] == screen.fruit_pixel)) { // (cant be in floor) AND (must be void OR current_tail OR fruit)
      sense = +screen.width;
    }
  }
  
  int get_tail_sense(){
    if      (current_tail%screen.width!=0                 && screen.screen[current_tail-1]             ==-1            )  return -1;              // tail isnt in left wall     and left square comes from right
    else if (current_tail/screen.width!=0                 && screen.screen[current_tail-screen.width]  ==-screen.width )  return -screen.width;   // tail isnt in ceil          and up square comes from bottom
    else if (current_tail%screen.width!=screen.width-1    && screen.screen[current_tail+1]             ==+1            )  return +1;              // tail isnt in right wall    and right square comes from left
    else if (current_tail/screen.width!=screen.height-1   && screen.screen[current_tail+screen.width]  ==+screen.width )  return +screen.width;   // tail isnt in floor         and down square comes from up
    else                                                                                                                  return sense;           // should enter here only while snake.size=1
  }

  void reset(){
    size = 1;

    past_tail = initial_position;
    current_tail = initial_position;
    new_head = initial_position;

    eated_fruit = false;

    switch(initial_sense){
      case 'l': sense = -1;               break;
      case 'u': sense = -screen.width;    break;
      case 'r': sense = +1;               break;
      case 'd': sense = +screen.width;    break;
    }
  }

  // constructor ##################################################

  snake(int initial_position, char initial_sense, int left_pin, int right_pin, int up_pin, int down_pin) : initial_position(initial_position), initial_sense(initial_sense), left_pin(left_pin), right_pin(right_pin), up_pin(up_pin), down_pin(down_pin){

  }

};


// INITIALIZATION ###################################################

snake jobert(24, 'r', 18, 19, 20, 21);


/*
███████ ███████ ████████ ██    ██ ██████       ██     ██  
██      ██         ██    ██    ██ ██   ██     ██       ██ 
███████ █████      ██    ██    ██ ██████      ██       ██ 
     ██ ██         ██    ██    ██ ██          ██       ██ 
███████ ███████    ██     ██████  ██           ██     ██ 
*/

void setup() {

  screen.matrix.shutdown(0, false);
  screen.matrix.setIntensity(0, 0);
  screen.matrix.clearDisplay(0);

  randomSeed(analogRead(0));
  
  pinMode(buzzer.pin, OUTPUT);



  pinMode(jobert.left_pin, INPUT_PULLUP); 
  pinMode(jobert.right_pin, INPUT_PULLUP);
  pinMode(jobert.up_pin, INPUT_PULLUP);
  pinMode(jobert.down_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(jobert.left_pin), interrupt_left, FALLING);  // falling because its pullup, so is active at low level
  attachInterrupt(digitalPinToInterrupt(jobert.right_pin), interrupt_right, FALLING);
  attachInterrupt(digitalPinToInterrupt(jobert.up_pin), interrupt_up, FALLING);
  attachInterrupt(digitalPinToInterrupt(jobert.down_pin), interrupt_down, FALLING);

}

void interrupt_left(){
  jobert.interrupt_left();
}
void interrupt_right(){
  jobert.interrupt_right();
}
void interrupt_up(){
  jobert.interrupt_up();
}
void interrupt_down(){
  jobert.interrupt_down();
}




/*
██       ██████   ██████  ██████       ██     ██  
██      ██    ██ ██    ██ ██   ██     ██       ██ 
██      ██    ██ ██    ██ ██████      ██       ██ 
██      ██    ██ ██    ██ ██          ██       ██ 
███████  ██████   ██████  ██           ██     ██                                                             
*/

void loop() {  // 1 iteration = 1 match

  /*
  ███████ ███████ ████████ ██    ██ ██████      ███    ███  █████  ████████  ██████ ██   ██ 
  ██      ██         ██    ██    ██ ██   ██     ████  ████ ██   ██    ██    ██      ██   ██ 
  ███████ █████      ██    ██    ██ ██████      ██ ████ ██ ███████    ██    ██      ███████
       ██ ██         ██    ██    ██ ██          ██  ██  ██ ██   ██    ██    ██      ██   ██ 
  ███████ ███████    ██     ██████  ██          ██      ██ ██   ██    ██     ██████ ██   ██ 
  */

  jobert.reset();

  bool is_game_over = false;
  
  const int period = 220;  


  // SCREEN
  screen.reset();
  screen.screen[jobert.new_head] = jobert.sense;
  screen.amount_of_void_pixels -= 1;  // for jobert

  screen.generate_fruit();


  screen.blit();


  /*
   ██████   █████  ███    ███ ███████     ██       ██████   ██████  ██████  
  ██       ██   ██ ████  ████ ██          ██      ██    ██ ██    ██ ██   ██ 
  ██   ███ ███████ ██ ████ ██ █████       ██      ██    ██ ██    ██ ██████  
  ██    ██ ██   ██ ██  ██  ██ ██          ██      ██    ██ ██    ██ ██      
   ██████  ██   ██ ██      ██ ███████     ███████  ██████   ██████  ██
  */

  while (!is_game_over){  // 1 iteration = 1 movement


    // IN-DELAY FUNCTIONS ###########################################


    if (jobert.eated_fruit){
      tone(buzzer.pin, 300);
      delay(period/5);
      tone(buzzer.pin, 700);
      delay(period*2/5);
      tone(buzzer.pin, 1100);
      delay(period/5);
      noTone(buzzer.pin);
      delay(period/5);
    }
    else {
      delay(period);
    }


    // LOGIC ########################################################

    jobert.eated_fruit = false;

    // snake head projection
    jobert.past_head = jobert.new_head;
    jobert.new_head = jobert.new_head + jobert.sense;

    // check harmfull collision
    if  (   ( (jobert.new_head%screen.width != jobert.past_head%screen.width) && (jobert.new_head/screen.width != jobert.past_head/screen.width)    )  // hitted wall: x1!=x2 and y1!=y2
        ||  ( (jobert.new_head < 0) || (jobert.new_head >= screen.size)                                                                             )  // hitted ceilling or floor
        ||  ( (screen.screen[jobert.new_head]!=screen.void_pixel) && (screen.screen[jobert.new_head]!=screen.fruit_pixel) && (jobert.new_head!=jobert.current_tail)))  // hitted itself
    {
      is_game_over = true;
    }

    else  // it was a legal head projection
    {  
      if (screen.screen[jobert.new_head]==screen.fruit_pixel)  // eated fruit
      { 
        jobert.eated_fruit = true;
        jobert.size++;

        screen.generate_fruit();
      }
      else  // do not eated fruit
      {  
        // loses tail
        jobert.past_tail = jobert.current_tail;
        jobert.current_tail += jobert.get_tail_sense();
        screen.screen[jobert.past_tail] = screen.void_pixel;
      }
      // gains head
      screen.screen[jobert.new_head] = jobert.sense;
    }


    // BLIT #########################################################

    screen.blit();

  }

}
