// STILL HAS ANALOGIC METHODS


//font: https://patorjk.com/software/taag/#p=display&f=ANSI%20Regular&t=Type%20Something%20


/*
██████   █████   ██████ ██   ██ ██       ██████   ██████  
██   ██ ██   ██ ██      ██  ██  ██      ██    ██ ██       
██████  ███████ ██      █████   ██      ██    ██ ██   ███ 
██   ██ ██   ██ ██      ██  ██  ██      ██    ██ ██    ██ 
██████  ██   ██  ██████ ██   ██ ███████  ██████   ██████  


  *organizar escopos
  *declare non-const global variables, initialize only in match setup
  *there are variables being declared in loop()

  *snake pressed_key solves fast2click backward move bug

  *consideer what functions may be performed in delay
    buzz, blink head

  *allow 1 pixel snake to run backwards

  *blinking head (and tail? should help on very large snakes)

  *easy mode: input only is assigned if dont kill snake immediatly - snake just dye when encurralated

  *amount of fruits proportional to snake size
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
  const int buzzer_pin = 5;
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

  const int din_pin = 4;
  const int load_pin = 3;
  const int clk_pin = 2;

  const LedControl matrix = LedControl(din_pin, clk_pin, load_pin, 1);


  const int logic_void_pixel = 0;  // logic_snake_pixel is the snake_sense for that square
  const int logic_fruit_pixel = 2;

  const int width = 8;
  const int height = 8;
  const int size = width * height;
  int screen[8*8];  // x=n%w, y=n/w

  int amount_of_void_squares;


  void generate_fruit(){  // create random value from 0 to amount_of_void_squares - them plot fruit on it
      
    int r = random(amount_of_void_squares);

    int fruit_position = 0;
    
    while(screen[fruit_position] != logic_void_pixel) fruit_position++;  // consider if r = 0 and 0 is occupied

    for (int i = 0; i<r; i++){
      fruit_position++;
      while(screen[fruit_position] != logic_void_pixel) fruit_position++;  // skip occupied values on counting
    }
    screen[fruit_position] = logic_fruit_pixel;
    amount_of_void_squares--;

  }

  void blit(){
    for (int i = 0; i< size; i++){
      matrix.setLed(0, i/width, i%width, screen[i]!=logic_void_pixel);
      if (screen[i]==logic_fruit_pixel){
      }
      }
  }

  void reset(){
    memset(screen, logic_void_pixel, size * sizeof(int));
    amount_of_void_squares = size;
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

  const int x_pin, y_pin, sw_pin;
  const int joystick_sensibility = 60;

  const int initial_position, initial_sense;


  // non-consts ###################################################

  int past_tail, past_head;
  int current_tail, new_head;

  int sense;  // left=-1, right=+1, up=-width, down=+width;  // will be plotted in screen as a logic pixel

  int size;

  bool eated_fruit;


  // functions ####################################################

  /* JOYSTICK
  void wait_input(int delaytime, int iterations){  // works a lot better if snake has attribute pressed key
    for (int i = 0; i<iterations; i++){
      jobert.read_input();
      delay(delaytime/iterations);
    }
  }
  */


  void interrupt_left(){
    if (this->sense!=+1 || this->size==1) this->sense = -1;
  }
    void interrupt_right(){
    if (this->sense!=-1 || this->size==1) this->sense = +1;
  }
    void interrupt_up(){
    if (this->sense!=+screen.width || this->size==1) this->sense = -screen.width;
  }
    void interrupt_down(){
    if (this->sense!=-screen.width || this->size==1) this->sense = +screen.width;
  }

  char get_input(){
    int x = analogRead(this->x_pin) - 512;
    int y = analogRead(this->y_pin) - 512;
    int sw = digitalRead(this->sw_pin);
    
    if (abs(x)>joystick_sensibility || abs(y)>joystick_sensibility){  // only return input if it is greater than joystick_sensibility
      if (abs(x)>abs(y))  return (x<0 ? 'l' : 'r');
      else                return (y<0 ? 'u' : 'd');
    }
    else{
      return 'n';
    }
  }


  void easy_set_head_sense(char pressed_key){
    // only turns if side is void - allow size 1 snake to run backwards
    if (pressed_key != 'n'){
      if      (pressed_key == 'l' &&  this->new_head%screen.width!=0              &&  ( screen.screen[this->new_head-1]             ==screen.logic_void_pixel ||  screen.screen[this->new_head-1]           ==this->current_tail )) this->sense = -1;  // cant be in left wall, must be void or new_tail or fruit
      else if (pressed_key == 'u' &&  this->new_head/screen.width!=0              &&  ( screen.screen[this->new_head-screen.width]  ==screen.logic_void_pixel ||  screen.screen[this->new_head-screen.width]==this->current_tail )) this->sense = -screen.width;
      else if (pressed_key == 'r' &&  this->new_head%screen.width!=screen.width-1 &&  ( screen.screen[this->new_head+1]             ==screen.logic_void_pixel ||  screen.screen[this->new_head+1]           ==this->current_tail )) this->sense = +1;
      else if (pressed_key == 'd' &&  this->new_head/screen.width!=0)  this->sense = +screen.width;
      }

  }

  void set_head_sense_left(){
    if  (this->sense != +1 || this->size==1) this->sense = -1;
  }
  void set_head_sense_right(){
    if  (this->sense != -1  || this->size==1) this->sense = +1;
  }
  void set_head_sense_up(){
    if  (this->sense != -screen.width  || this->size==1) this->sense = +screen.width;
  }
  void set_head_sense_down(){
    if  (this->sense != +screen.width  || this->size==1) this->sense = -screen.width;
  }

  /*
  void set_head_sense(char pressed_key){
    // inputs to go backwards are ignored, snake head keep its sense
    if (pressed_key != 'n'){
      if      (pressed_key == 'l' && this->sense != +1)             this->sense = -1;
      else if (pressed_key == 'u' && this->sense != +screen.width)  this->sense = -screen.width;
      else if (pressed_key == 'r' && this->sense != -1)             this->sense = +1;
      else if (pressed_key == 'd' && this->sense != -screen.width)  this->sense = +screen.width;
      }

  }
  */

  int get_tail_sense(){
    if      (this->current_tail%screen.width!=0                 && screen.screen[this->current_tail-1]             ==-1            ) return -1;              // tail isnt in left wall     and left square comes from right
    else if (this->current_tail/screen.width!=0                 && screen.screen[this->current_tail-screen.width]  ==-screen.width )  return -screen.width;   // tail isnt in ceil          and up square comes from bottom
    else if (this->current_tail%screen.width!=screen.width-1    && screen.screen[this->current_tail+1]             ==+1            )  return +1;              // tail isnt in right wall    and right square comes from left
    else if (this->current_tail/screen.width!=screen.height-1   && screen.screen[this->current_tail+screen.width]  ==+screen.width )  return +screen.width;   // tail isnt in floor         and down square comes from up
    else                                                                                                                              return this->sense;     //should enter here only while snake.size=1
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

  snake(int initial_position, char initial_sense, int x_pin, int y_pin, int sw_pin) : initial_position(initial_position), initial_sense(initial_sense), x_pin(x_pin), y_pin(y_pin), sw_pin(sw_pin){

  }

};


// INITIALIZATION ###################################################

snake jobert(24, 'r', A6, A7, 6);


/*
███████ ███████ ████████ ██    ██ ██████       ██     ██  
██      ██         ██    ██    ██ ██   ██     ██       ██ 
███████ █████      ██    ██    ██ ██████      ██       ██ 
     ██ ██         ██    ██    ██ ██          ██       ██ 
███████ ███████    ██     ██████  ██           ██     ██ 
*/

void setup() {

  Serial.begin(9600);

  screen.matrix.shutdown(0, false);
  screen.matrix.setIntensity(0, 0);
  screen.matrix.clearDisplay(0);

  randomSeed(analogRead(0));

  pinMode(jobert.x_pin, INPUT);
  pinMode(jobert.y_pin, INPUT);
  pinMode(jobert.sw_pin, INPUT_PULLUP);
  
  pinMode(buzzer.buzzer_pin, OUTPUT);



  pinMode(21, INPUT_PULLUP); 
  pinMode(20, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(18), interrupt_left, FALLING);
  attachInterrupt(digitalPinToInterrupt(19), interrupt_right, FALLING);
  attachInterrupt(digitalPinToInterrupt(20), interrupt_up, FALLING);
  attachInterrupt(digitalPinToInterrupt(21), interrupt_down, FALLING);

}

void interrupt_left(){
  jobert.interrupt_left();
  Serial.println("DOWN");
}
void interrupt_right(){
  jobert.interrupt_right();
  Serial.println("UP");
}
void interrupt_up(){
  jobert.interrupt_up();
  Serial.println("LEFT");
}
void interrupt_down(){
  jobert.interrupt_down();
  Serial.println("RIGHT");
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
  
  const int period = 230;  


  // SCREEN
  screen.reset();
  screen.screen[jobert.new_head] = jobert.sense;
  screen.amount_of_void_squares -= 1;  // for jobert

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
      tone(buzzer.buzzer_pin, 300);
      delay(period/5);
      tone(buzzer.buzzer_pin, 700);
      delay(period*2/5);
      tone(buzzer.buzzer_pin, 1100);
      delay(period/5);
      noTone(buzzer.buzzer_pin);
      delay(period/5);
    }
    else {
      delay(period);
    }


    // INPUT ########################################################



    // LOGIC ########################################################

    jobert.eated_fruit = false;

    // snake head projection
    jobert.past_head = jobert.new_head;
    jobert.new_head = jobert.new_head + jobert.sense;

    // check harmfull collision
    if  (   ( (jobert.new_head%screen.width != jobert.past_head%screen.width) && (jobert.new_head/screen.width != jobert.past_head/screen.width)    )  // hitted wall: x1!=x2 and y1!=y2
        ||  ( (jobert.new_head < 0) || (jobert.new_head >= screen.size)                                                                             )  // hitted ceilling or floor
        ||  ( (screen.screen[jobert.new_head]!=screen.logic_void_pixel) && (screen.screen[jobert.new_head]!=screen.logic_fruit_pixel) && (jobert.new_head!=jobert.current_tail)))  // hitted itself
    {
      is_game_over = true;
    }

    else  // it was a legal head projection
    {  
      if (screen.screen[jobert.new_head]==screen.logic_fruit_pixel)  // eated fruit
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
        screen.screen[jobert.past_tail] = screen.logic_void_pixel;
      }
      // gains head
      screen.screen[jobert.new_head] = jobert.sense;
    }


    // BLIT #########################################################
    screen.blit();

  }

}
