const unsigned int FPS = 100;
const unsigned int delay_time = 1000 / FPS;

const unsigned int screen_width = 500;
const unsigned int screen_height = 750;
const int max_car_height = screen_height * 0.73;

const unsigned short int icon_size   = 60;

const double harder = -1;
const unsigned int block_V = 2;



bool music_state = false;
bool sound_state = false;

int car_r_x[] = { screen_width * 5/8  - icon_size/2 , screen_width * 7/8 - icon_size/2 };
int car_l_x[] = { screen_width * 1/8  - icon_size/2,  screen_width * 3/8 - icon_size/2 };

bool car_r_pos = true;
bool car_l_pos = true;

std::string main_windows_title = "welcome to 2CARS :)";

const unsigned int score_rate = 200;
Font * score_font = NULL;
int score = 0;
int high_score=0;

Music*  game_music = NULL;
Sound* sound1 = NULL; //TODO

enum obj_pos { left,right };
enum Kind {circle , square};
const short int block_start_point = 20;
struct obj
{
  bool should_eat = true;
  bool is_moving = false;
  obj_pos pos = left;
  int y = block_start_point;
  Texture* tex;
};

obj left_block [3];
obj right_block [3];
unsigned short int left_block_index =0 ;
unsigned short int right_block_index =0 ;
obj_pos block_turn= right;
const unsigned int block_rate = 150; //TODO
