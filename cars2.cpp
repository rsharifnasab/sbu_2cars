#include "SBDL.h"
#include <iostream>
 #include "lib.h"

//  - - - - -some basic settings - - - -
const unsigned int FPS = 60;
const unsigned int delay_time = 1000 / FPS;


// seting up screen and rects size;
const unsigned int screen_width = 500;
const unsigned int screen_height = 800;
const unsigned int divider_width = 6;
const unsigned int divider_height = screen_height;



bool load_first_textute()
{


}

bool load_menu()
{
  SBDL::clearRenderScreen();
  Texture menu_background = SBDL::loadTexture( "assets/MenuBackground.png" );
  SBDL::showTexture( menu_background , 0 , 0 );
	SBDL::updateRenderScreen();
  //SBDL::delay(10000);
}

bool init()
{
  SBDL::InitEngine ("2CARS", screen_width , screen_height);
}


int main()
{
  std::cout << "hello welcometo this game,\n if you are seeing this, maybe sdl problem or it hadnt develped yet \n";
  init();
  load_menu();

  while (true)
  {
    break; //TODO

  }


  return 0;
}
