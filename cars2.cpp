#include "SBDL.h"
#include <iostream>
 #include "lib.h"

//  - - - - -some basic settings - - - -
const unsigned int FPS = 60;
const unsigned int delay_time = 1000 / FPS;


// seting up screen and rects size;
const unsigned int screen_width = 500;
const unsigned int screen_height = 800;



bool show_menu_textures()
{



}

bool load_menu()
{
  const unsigned short int menu_item_size   = 60;
  bool music_state = true;
  bool sound_state = true;


  SBDL::clearRenderScreen();
  Texture menu_background = SBDL::loadTexture( "assets/MenuBackground.png" );
  SBDL::showTexture( menu_background , 0 , 0 );


  // - - - - write welcome - --
  Font * welc_font = SBDL::loadFont("assets/Font/gobold.ttf",17);
  Texture welcome_texture = SBDL::createFontTexture(welc_font , "welcome to 2CARS :)", 100, 240, 33);
  SBDL::showTexture( welcome_texture , (screen_width - welcome_texture.width ) / 2 ,screen_height/7 );


  // - - - - write start - --
  Font * start_font = SBDL::loadFont("assets/Font/gobold.ttf",25);
  Texture start_texture = SBDL::createFontTexture(start_font , "press SPACE to start", 20, 140, 133);
  SBDL::showTexture( start_texture , (screen_width - start_texture.width ) / 2, screen_height/2.2 );


  // create and show sound texture
  Texture sound_texture = SBDL::loadTexture( "assets/Button/Sound.png" );
  Texture no_sound_texture = SBDL::loadTexture( "assets/Button/SoundDisabled.png" );
  SBDL::showTexture( sound_texture , 0 , screen_height - menu_item_size );
  SDL_Rect sound_rect = { 0 , screen_height - menu_item_size , menu_item_size , menu_item_size };

  // create and show music texture
  Texture music_texture = SBDL::loadTexture( "assets/Button/Music.png" );
  Texture no_music_texture = SBDL::loadTexture( "assets/Button/MusicDisabled.png" );
  SBDL::showTexture( music_texture ,(int) 1.5 *  menu_item_size , screen_height - menu_item_size );
  SDL_Rect music_rect = { (int)1.5 *  menu_item_size , screen_height - menu_item_size , menu_item_size , menu_item_size };


  // create and show play texture
  Texture play_texture = SBDL::loadTexture( "assets/Button/Play.png" );
  SBDL::showTexture( play_texture ,  screen_width - menu_item_size , screen_height - menu_item_size );
  SDL_Rect play_rect = { screen_width - menu_item_size , screen_height - menu_item_size , menu_item_size , menu_item_size };



  SBDL::updateRenderScreen();


  while( SBDL::isRunning() ) // handle if start button pressed or not
  {

    SBDL::updateEvents();

    if (SBDL::keyHeld(SDL_SCANCODE_SPACE)) break;
    if (SBDL::Mouse.clicked())
    {
      if ( SBDL::mouseInRect(play_rect)) music_check(music_state);
      if ( SBDL::mouseInRect(sound_rect)) sound_check(sound_state);
    }
    SBDL::delay(delay_time);

  }

  return true;
}

bool init()
{
  SBDL::InitEngine ("2CARS Game", screen_width , screen_height);

  return true;
}


int main()
{
  init();
  load_menu();

  SBDL::updateRenderScreen();
  //SBDL::delay(10000);

  while (true)
  {
    break; //TODO

  }


  return 0;
}
