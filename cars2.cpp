#include <bits/stdc++.h>
#include "SBDL.h"

const unsigned int FPS = 60;
const unsigned int delay_time = 1000 / FPS;

const unsigned int screen_width = 500;
const unsigned int screen_height = 800;
const int max_car_height = screen_height * 0.63;

const double harder = 1.0001;
unsigned int block_V = 3;

bool music_state = true;
bool sound_state = true;

#include "menu.h"

bool paused = false;

bool car_r_pos = true;
bool car_l_pos = true;

int car_r_x[] = { screen_width * 5/8  - icon_size/2 , screen_width * 7/8 - icon_size/2 };
int car_l_x[] = { screen_width * 1/8  - icon_size/2,  screen_width * 3/8 - icon_size/2 };

Texture background,
 car_r_tex, car_l_tex,
  bad_r_tex, bad_l_tex,
   good_r_tex, good_l_tex;

bool init()
{
  SBDL::InitEngine ("2CARS Game", screen_width , screen_height);

  srand(time(0));

  car_r_pos = rand()%2;
  car_l_pos = rand()%2;

  return true;
}


bool make_game_harder()
{
  block_V *= harder ;
  return true;
}


bool pause() // TODO
{
  paused = true;
  std::cout << "paused "<< std::endl;
  while( SBDL::isRunning() )
  {
    SBDL::updateEvents();
    if (SBDL::keyPressed(SDL_SCANCODE_P)) paused = false; // p to resume

    if (!paused) break;
  }
  return true;
}


bool handle_keyboard()
{
  if (SBDL::keyPressed(SDL_SCANCODE_RIGHT)) car_r_pos = !car_r_pos;
  if (SBDL::keyPressed(SDL_SCANCODE_LEFT))  car_l_pos = !car_l_pos;
  if (SBDL::keyPressed(SDL_SCANCODE_P)) menu("Game Paused");
    //pause(); // p to pause

  return true;
}


bool load_game_texture()
{
  background = SBDL::loadTexture( "assets/Background.png" );
  car_r_tex = SBDL::loadTexture( "assets/Cars/BlueCar.png" );
  car_l_tex = SBDL::loadTexture( "assets/Cars/RedCar.png" );

  bad_r_tex = SBDL::loadTexture( "assets/Obstacle/BlueRectangle.png" );
  bad_l_tex = SBDL::loadTexture( "assets/Obstacle/RedRectangle.png" );

  good_r_tex = SBDL::loadTexture( "assets/Obstacle/BlueCircle.png" );
  good_l_tex = SBDL::loadTexture( "assets/Obstacle/RedCircle.png" );

  return true;  SBDL::showTexture( background , 0 , 0 );
    SBDL::showTexture( car_r_tex , car_r_x[car_r_pos] , max_car_height );
    SBDL::showTexture( car_l_tex , car_l_x[car_l_pos] , max_car_height );


}

bool show_game_texture()
{
  SBDL::showTexture( background , 0 , 0 );
  SBDL::showTexture( car_r_tex , car_r_x[car_r_pos] , max_car_height );
  SBDL::showTexture( car_l_tex , car_l_x[car_l_pos] , max_car_height );

}

bool delay_handle(int start_time)
{
    unsigned int loop_time = SBDL::getTime() - start_time;
  	if ( loop_time < delay_time )
		  SBDL::delay( delay_time - loop_time );
    return true;
}

int main()
{
  init();
  menu();
  load_game_texture();

  while( SBDL::isRunning() )
  {
    unsigned int start_time = SBDL::getTime();

    make_game_harder();

    SBDL::updateEvents();
    handle_keyboard();

    show_game_texture();
    SBDL::updateRenderScreen();
    delay_handle(start_time);
}

  return 0;
}
