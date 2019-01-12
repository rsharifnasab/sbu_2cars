
Texture menu_background, welcome_texture, start_texture, play_texture, sound_texture, no_sound_texture, music_texture, no_music_texture, score_texture,menu_score_tex;

SDL_Rect sound_rect,music_rect, play_rect;

bool first_time= true;

bool show_menu_textures()
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

  if(!first_time) SBDL::showTexture( menu_score_tex , (screen_width - menu_score_tex.width ) / 2, screen_height/1.2 );

  SBDL::updateRenderScreen();
  return true;
}


bool load_menu_textures(std::string text_title)
{
  menu_background = SBDL::loadTexture( "assets/MenuBackground.png" );

  Font * welc_font = SBDL::loadFont("assets/Font/gobold.ttf",17);
  welcome_texture = SBDL::createFontTexture(welc_font , text_title, 100, 240, 33);

  Font * start_font = SBDL::loadFont("assets/Font/gobold.ttf",25);
  start_texture = SBDL::createFontTexture(start_font , "press SPACE to start", 20, 140, 133);

  sound_texture = SBDL::loadTexture( "assets/Button/Sound.png" );
  no_sound_texture = SBDL::loadTexture( "assets/Button/SoundDisabled.png" );
  sound_rect = { 0 , screen_height - icon_size , icon_size , icon_size };

  music_texture = SBDL::loadTexture( "assets/Button/Music.png" );
  no_music_texture = SBDL::loadTexture( "assets/Button/MusicDisabled.png" );
  music_rect = { (int)1.5 *  icon_size , screen_height - icon_size , icon_size , icon_size };

  play_texture = SBDL::loadTexture( "assets/Button/Play.png" );
  play_rect = { screen_width - icon_size , screen_height - icon_size , icon_size , icon_size };

  Font * menu_score_font = SBDL::loadFont("assets/Font/gobold.ttf",25);
  menu_score_tex = SBDL::createFontTexture(menu_score_font , "SCORE : " + std::to_string(score) , 30, 140, 50);


  return true;
}


bool menu(std::string text_title = main_windows_title)
{
  first_time = text_title == main_windows_title;
  load_menu_textures(text_title);
  show_menu_textures();

  while( SBDL::isRunning() )
  {
    SBDL::updateEvents();

    if (SBDL::keyHeld(SDL_SCANCODE_SPACE)) return true;
    if (SBDL::Mouse.clicked())
    {
      if ( SBDL::mouseInRect( play_rect ) ) return true;
      if ( SBDL::mouseInRect( sound_rect ) ) sound_state = !sound_state;
      if ( SBDL::mouseInRect( music_rect ) )
      {
        if (music_state) SBDL::stopMusic();
        else SBDL::playMusic(game_music, -1);
        music_state = !music_state;
      }
    }
    show_menu_textures();
    SBDL::delay(delay_time);
  }
  return true;
}
