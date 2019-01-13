#include <bits/stdc++.h>
#include <exception>
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
  std::ifstream HS_S ("high_score.txt");
  if (HS_S.is_open())
  {
      getline (HS_S,HS);
      high_score = std::stoi(HS);
      HS_S.close();
  }
  else std::cout << "error in opening file\n";
  return true;
}


bool init_music()
{
  try{
    game_music = SBDL::loadMusic("./assets/Sounds/music.wav");
    if(music_state) SBDL::playMusic(game_music, -1);
    score_sound = SBDL::loadSound("assets/Sounds/score.wav");
    die1_sound = SBDL::loadSound("assets/Sounds/die1.wav");
    die2_sound = SBDL::loadSound("assets/Sounds/die2.wav");
    return true;
  }
  catch (int e){
    std::cout << "An exception occurred. Exception Nr. " << e << '\n';
    return false;
  }
}

bool init()
{
  SBDL::InitEngine ("2CARS Game", screen_width, screen_height);
  srand(time(0));

  car_r_pos = rand()%2;
  car_l_pos = rand()%2;

  block_turn = (rand()%2 == 0)?left:right;

  init_high_score();
  init_music();

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
  // create score texture moved to show_game_texture becasue of every time change
  return true;
}

bool show_game_texture()
{
  SBDL::showTexture( background , 0 , 0 );

  for (unsigned short i = 0; i < 3; i++){
    if(right_block[i].is_moving)
        SBDL::showTexture( *(right_block[i].tex) , car_r_x[right_block[i].pos] , right_block[i].y );
    if(left_block[i].is_moving)
      SBDL::showTexture( *(left_block[i].tex) , car_l_x[left_block[i].pos] , left_block[i].y );
  }

  SBDL::showTexture( car_r_tex , car_r_x[car_r_pos] , max_car_height );
  SBDL::showTexture( car_l_tex , car_l_x[car_l_pos] , max_car_height );

	score_tex = SBDL::createFontTexture(score_font , "SCORE : " + std::to_string(score) + " HIGHSCORE : " + std::to_string(high_score) , 30, 220, 50);
  SBDL::showTexture( score_tex , screen_width * 0.27 ,screen_height - score_tex.height );

  return true;
}

bool delay_handle(int start_time)
{
    unsigned int delay_time = 1000 / FPS;
    unsigned int loop_time = SBDL::getTime() - start_time;

  	if ( loop_time < delay_time )
		  SBDL::delay( delay_time - loop_time );
    return true;
}

bool score_add()
{
    score++;
    FPS += harder ; //todo
    if (score > high_score)
    {
      high_score = score;
      std::ofstream myfile;
      myfile.open ("high_score.txt");
      myfile << high_score << "\n";
      myfile.close();
    }
  return true;
}


bool kind_rand()
{
  short int r = rand()%11;
  if (r<4) return false;
  return true;
}

bool init_block(obj& a,obj_pos pos)
{
  if (a.is_moving) return false;
  a.y = block_start_point;
  a.should_eat = kind_rand();
  a.pos = (rand()%2==1) ? left : right;
  a.is_moving = true;

  if(a.should_eat){
    if(pos == right) a.tex = &good_r_tex;
    else  a.tex = &good_l_tex;
  }
  else{
    if(pos == right) a.tex = &bad_r_tex;
    else  a.tex = &bad_l_tex;
  }
  return true;
}

bool kill_block(obj& a)
{
  if(a.should_eat && sound_state)  SBDL::playSound(score_sound, 1);
  if(a.should_eat) score_add();
  a.is_moving = false;
  a.y = block_start_point;
  return true;
}


bool new_block()
{
  static long int milisec = 0;
  milisec++;
  if(milisec < block_rate) return false;
  milisec %= block_rate;
  if (block_turn == left)
  {
    init_block(left_block[left_block_index],left);
    block_turn = right;
    left_block_index = (left_block_index+1)%3;
  }
  else
  {
    init_block(right_block[right_block_index],right);
    block_turn = left;
    right_block_index = (right_block_index+1)%3;
  }
  return true;
}


bool block_move()
{
  for(int i=0;i<3;i++)
  {
    left_block[i].y += (left_block[i].is_moving * block_V);
    right_block[i].y += (right_block[i].is_moving * block_V);

    if(left_block[i].y > screen_height+icon_size) left_block[i].is_moving = false;
    if(right_block[i].y > screen_height+icon_size) right_block[i].is_moving = false;
  }
  return true;
}

bool play_sound(sound_type s)
{
    if(!sound_state) return false;
    if (s == score_s) SBDL::playSound(score_sound,1);
    if (s == die1_s) SBDL::playSound(die1_sound,1);
    if (s == die2_s) SBDL::playSound(die2_sound,1);
    return true;
}

bool hit_check()
{
  SDL_Rect car_r_rect = { car_r_x[car_r_pos] ,  max_car_height , car_r_tex.width , car_r_tex.height };
  SDL_Rect car_l_rect = { car_l_x[car_l_pos] ,  max_car_height , car_l_tex.width , car_l_tex.height };

    for (unsigned short i = 0; i < 3; i++)
    {
      if(right_block[i].is_moving)
      {
          SDL_Rect right_block_rect = { car_r_x[right_block[i].pos] ,  right_block[i].y , icon_size , icon_size  };
          if ( SBDL::hasIntersectionRect( right_block_rect,car_r_rect ) )
          {
            if (right_block[i].should_eat) kill_block(right_block[i]);
            else { play_sound(die1_s); menu(Game_Over); }
          }
          if(right_block[i].y > screen_height && right_block[i].should_eat)
            { play_sound(die2_s); menu(Game_Over); }
      }
      if(left_block[i].is_moving)
      {
          SDL_Rect left_block_rect = { car_l_x[left_block[i].pos] ,  left_block[i].y , icon_size , icon_size  };
          if ( SBDL::hasIntersectionRect( left_block_rect,car_l_rect ) )
          {
            if (left_block[i].should_eat) kill_block(left_block[i]);
            else { play_sound(die1_s); menu(Game_Over); }
          }
          if(left_block[i].y > screen_height && left_block[i].should_eat)
            { play_sound(die2_s); menu(Game_Over); }
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

    new_block();
    block_move();
    hit_check();

    SBDL::updateEvents();
    handle_keyboard();

    show_game_texture();
    SBDL::updateRenderScreen();
    delay_handle(start_time);
}
  return 0;
}
