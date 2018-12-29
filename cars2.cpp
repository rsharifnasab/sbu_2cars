#include "SBDL.h"
#include <iostream>
 #include "lib.h"

//  - - - - -some basic settings - - - -
const unsigned int FPS = 60;
const unsigned int delay_time = 1000 / FPS;


// seting up screen and rects size;
const unsigned int screen_width = 768;
const unsigned int screen_height = 1024;
const unsigned int divider_width = 6;
const unsigned int divider_height = screen_height;



bool load_first_textute()
{


}

bool init()
{
  SBDL::InitEngine ("2CARS", screen_width , screen_height);
  load_first_textute();
}


int main()
{
  std::cout << "hello welcometo this game,\n if you are seeing this, maybe sdl problem or it hadnt develped yet \n";
  while (true)
  {


  }


  return 0;
}
