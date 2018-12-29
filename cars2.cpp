#include "SBDL.h"
#include <iostream>
#include <bits/stdc++.h>
 #include "lib.h"


const unsigned int FPS = 60;
const unsigned int delay_time = 1000 / FPS;


const unsigned int screen_width = 500;
const unsigned int screen_height = 800;

const unsigned short int icon_size   = 60;
bool music_state = true;
bool sound_state = true;

bool car_r_pos = true;
bool car_l_pos = true;


bool show_menu_textures(Texture menu_background, Texture welcome_texture,
Texture start_texture ,Texture play_texture,
Texture  sound_texture, Texture  no_sound_texture,
Texture music_texture , Texture  no_music_texture )
{
  SBDL::clearRenderScreen();

  SBDL::showTexture( menu_background , 0 , 0 );
  SBDL::showTexture( welcome_texture , (screen_width - welcome_texture.width ) / 2 ,screen_height/7 );
  SBDL::showTexture( start_texture , (screen_width - start_texture.width ) / 2, screen_height/2.2 );
  SBDL::showTexture( play_texture ,  screen_width - icon_size , screen_height - icon_size );

  if (sound_state) SBDL::showTexture( sound_texture , 0 , screen_height - icon_size );
  else SBDL::showTexture( no_sound_texture , 0 , screen_height - icon_size );

  if (music_state) SBDL::showTexture( music_texture ,(int) 1.5 *  icon_size , screen_height - icon_size );
  else SBDL::showTexture( no_music_texture , (int) 1.5 *  icon_size , screen_height - icon_size );

  SBDL::updateRenderScreen();
  return true;
}

bool menu()
{
  Texture menu_background = SBDL::loadTexture( "assets/MenuBackground.png" );

  Font * welc_font = SBDL::loadFont("assets/Font/gobold.ttf",17);
  Texture welcome_texture = SBDL::createFontTexture(welc_font , "welcome to 2CARS :)", 100, 240, 33);

  Font * start_font = SBDL::loadFont("assets/Font/gobold.ttf",25);
  Texture start_texture = SBDL::createFontTexture(start_font , "press SPACE to start", 20, 140, 133);

  Texture sound_texture = SBDL::loadTexture( "assets/Button/Sound.png" );
  Texture no_sound_texture = SBDL::loadTexture( "assets/Button/SoundDisabled.png" );
  SDL_Rect sound_rect = { 0 , screen_height - icon_size , icon_size , icon_size };

  Texture music_texture = SBDL::loadTexture( "assets/Button/Music.png" );
  Texture no_music_texture = SBDL::loadTexture( "assets/Button/MusicDisabled.png" );
  SDL_Rect music_rect = { (int)1.5 *  icon_size , screen_height - icon_size , icon_size , icon_size };

  Texture play_texture = SBDL::loadTexture( "assets/Button/Play.png" );
  SDL_Rect play_rect = { screen_width - icon_size , screen_height - icon_size , icon_size , icon_size };


  while( SBDL::isRunning() )
  {
    SBDL::updateEvents();

    if (SBDL::keyHeld(SDL_SCANCODE_SPACE)) return true;
    if (SBDL::Mouse.clicked())
    {
      if ( SBDL::mouseInRect( play_rect ) ) return true;
      if ( SBDL::mouseInRect( sound_rect ) ) sound_state = !sound_state;
      if ( SBDL::mouseInRect( music_rect ) ) music_state = !music_state;
    }

    show_menu_textures(menu_background, welcome_texture,
    start_texture, play_texture,
    sound_texture, no_sound_texture,
    music_texture , no_music_texture );

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
  menu();

  SBDL::updateRenderScreen();
  //SBDL::delay(10000);

  while (true)
  {
    break; //TODO

  }


  return 0;
}
