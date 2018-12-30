#include <bits/stdc++.h>
#include "SBDL.h"

const unsigned int FPS = 60;
const unsigned int delay_time = 1000 / FPS;


const unsigned int screen_width = 500;
const unsigned int screen_height = 800;
const int max_car_height = screen_height * 0.63;

const unsigned double harder = 1.00001;
unsigned int block_V = 3;

//const int max_car_width = icon_size;


bool music_state = true;
bool sound_state = true;

#include "menu.h"

bool paused = false;

bool car_r_pos = true;
bool car_l_pos = true;

int car_r_x[] = { screen_width * 5/8  - icon_size/2 , screen_width * 7/8 - icon_size/2 };
int car_l_x[] = { screen_width * 1/8  - icon_size/2,  screen_width * 3/8 - icon_size/2 };




bool init()
{
  SBDL::InitEngine ("2CARS Game", screen_width , screen_height);

  srand(time(0));

  car_r_pos = rand()%2;
  car_l_pos = rand()%2;

  return true;
}



int main()
{
  init();
  menu();

  Texture background = SBDL::loadTexture( "assets/Background.png" );
  Texture car_r_tex = SBDL::loadTexture( "assets/Cars/BlueCar.png" );
  Texture car_l_tex = SBDL::loadTexture( "assets/Cars/RedCar.png" );

  Texture bad_r_tex = SBDL::loadTexture( "assets/Obstacle/BlueRectangle.png" );
  Texture bad_l_tex = SBDL::loadTexture( "assets/Obstacle/RedRectangle.png" );

  Texture good_r_tex = SBDL::loadTexture( "assets/Obstacle/BlueCircle.png" );
  Texture good_l_tex = SBDL::loadTexture( "assets/Obstacle/RedCircle.png" );


  while( SBDL::isRunning() )
  {
     unsigned int start_time = SBDL::getTime();

    SBDL::updateEvents();

    if (SBDL::keyPressed(SDL_SCANCODE_RIGHT)) car_r_pos = !car_r_pos;
    if (SBDL::keyPressed(SDL_SCANCODE_LEFT))  car_l_pos = !car_l_pos;
    if (SBDL::keyHeld(SDL_SCANCODE_P))
    {
      paused = true; // pause TODO
      // pause_menu()
    }
    if (SBDL::keyHeld(SDL_SCANCODE_Q)) return 0;

    SBDL::showTexture( background , 0 , 0 );
    SBDL::showTexture( car_r_tex , car_r_x[car_r_pos] , max_car_height );
    SBDL::showTexture( car_l_tex , car_l_x[car_l_pos] , max_car_height );

    SBDL::updateRenderScreen();



    unsigned int loop_time = SBDL::getTime() - start_time;
		if ( loop_time < delay_time )
		  SBDL::delay( delay_time - loop_time );
  }


  return 0;
}
