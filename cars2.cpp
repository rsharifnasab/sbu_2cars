#include <bits/stdc++.h>
#include "SBDL.h"
#include "consts.h"
#include "menu.h"


Texture background,score_tex,
 car_r_tex, car_l_tex,
  bad_r_tex, bad_l_tex,
   good_r_tex, good_l_tex;


bool init_high_score()
{
  std::string HS="";
  std::ifstream HSS ("high_score.txt");
  if (HSS.is_open())
  {
      getline (HSS,HS);
      high_score = std::stoi(HS);
      HSS.close();
  }
  else std::cout << "error in opening file\n";
  return true;
}

bool init()
{
  SBDL::InitEngine ("2CARS Game", screen_width, screen_height);

  srand(time(0));
  car_r_pos = rand()%2;
  car_l_pos = rand()%2;

  init_high_score();
  //  Music*  game_music = SBDL::loadMusic("./assets/Sounds/score.wav");
  //  SBDL::playMusic(game_music, -1);
  //Mix_Music *gMusic = NULL;
//  gMusic = Mix_LoadMUS( "m.wav" );
//  if( gMusic == NULL )
//  {
//    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
//  }
  return true;
}

bool make_game_harder()
{
  block_V *= harder ;
  return true;
}


bool handle_keyboard()
{
  if (SBDL::keyPressed(SDL_SCANCODE_RIGHT)) car_r_pos = !car_r_pos;
  if (SBDL::keyPressed(SDL_SCANCODE_LEFT))  car_l_pos = !car_l_pos;
  if (SBDL::keyPressed(SDL_SCANCODE_P)) menu("Game Paused");

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

  score_font = SBDL::loadFont("assets/Font/gobold.ttf",27);

  return true;
}

bool show_game_texture()
{
  SBDL::showTexture( background , 0 , 0 );
  SBDL::showTexture( car_r_tex , car_r_x[car_r_pos] , max_car_height );
  SBDL::showTexture( car_l_tex , car_l_x[car_l_pos] , max_car_height );

	score_tex = SBDL::createFontTexture(score_font , "SCORE : " + std::to_string(score) , 30, 140, 50);
  SBDL::showTexture( score_tex , screen_width * 0.27 ,screen_height - score_tex.height );
  return true;
}

bool delay_handle(int start_time)
{
    unsigned int loop_time = SBDL::getTime() - start_time;
  	if ( loop_time < delay_time )
		  SBDL::delay( delay_time - loop_time );
    return true;
}

bool score_handle()
{
  const unsigned int ms_max = 200;
  static long int milisec = 0;
  milisec++;
  if(milisec > ms_max)
  {
    milisec %= ms_max;
    score++;
    if (score > high_score)
    {
      high_score = score;
      std::ofstream myfile;
      myfile.open ("high_score.txt");
      myfile << high_score << "\n";
      myfile.close();
    }
  }
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
    score_handle();
    make_game_harder();

    SBDL::updateEvents();
    handle_keyboard();

    show_game_texture();
    SBDL::updateRenderScreen();
    delay_handle(start_time);
}
  return 0;
}
