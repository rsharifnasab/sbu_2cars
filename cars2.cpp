#include <bits/stdc++.h>
#include "SBDL.h"

const unsigned int FPS = 60;
const unsigned int delay_time = 1000 / FPS;


const unsigned int screen_width = 500;
const unsigned int screen_height = 800;


bool music_state = true;
bool sound_state = true;

bool car_r_pos = true;
bool car_l_pos = true;

#include "menu.h"


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
