const unsigned int FPS = 60;
const unsigned int delay_time = 1000 / FPS;

const unsigned int screen_width = 500;
const unsigned int screen_height = 650;
const int max_car_height = screen_height * 0.73;

const unsigned short int icon_size   = 60;

const double harder = 1.0001;
unsigned int block_V = 3;



bool music_state = false;
bool sound_state = false;

int car_r_x[] = { screen_width * 5/8  - icon_size/2 , screen_width * 7/8 - icon_size/2 };
int car_l_x[] = { screen_width * 1/8  - icon_size/2,  screen_width * 3/8 - icon_size/2 };

bool car_r_pos = true;
bool car_l_pos = true;

std::string main_windows_title = "welcome to 2CARS :)";

const unsigned int score_rate = 200;
Font * score_font;
int score = 0;
int high_score=0;
