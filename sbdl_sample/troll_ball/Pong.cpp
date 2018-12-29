
/*
To compile with g++:
g++ Pong.cpp -o Pong -std=c++11 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
*/

#include "SBDL.h"

struct Cor { 
	int x, y;
};

int main () {

	const int windowWidth = 600;
	const int windowHeight = 400;
	SBDL::InitEngine( "Pong-v2", windowWidth, windowHeight );	//Sakhtan-e Panjere-e Jadid
	
	/*
	TexturehaaE ke daakhel-e baaZ estefade mishavand... 
	Az texture baraaye zakhire-e aks estefade mishavad ma'moolan 
	*/
	Texture racketTexture = SBDL::loadTexture( "assets/racket.png" );	
	Texture ballTexture = SBDL::loadTexture( "assets/ball.png" );
	Texture restartTexture = SBDL::loadTexture( "assets/Restart.png" );
	
	const int FPS = 25;
	const int delay = 1000 / FPS;
	
	/*
	Mokhtasaat-e Toop o Racket
	*/	
	Cor ballCor = { 200, 100 };
	Cor racketCor = { 300, 300 };
	
	//Sor'at-e Toop
	int ballVelX = 5;
	int ballVelY = 6;
	
	//Sor'at-e Racket
	int racketVelX = 7;
	
	//Moshakhas Mikonad ke bakhtim yaa na
	bool lose = false;
	
	while ( SBDL::isRunning() ) {	// Ta vaghti ke taraf baaZ ro nabaste bood:
	
		int loopStartTime = SBDL::getTime();	//Zamaan-e shoroo'-e halghe ro too-e loopStartTime negah midaarim
	
		SBDL::updateEvents();	//Eventhaa-e ettefaagh oftaade ro update kon
		
		if ( lose ) { //Agar bakhte bood
			SBDL::showTexture( restartTexture, ( windowWidth - restartTexture.width ) / 2, ( windowHeight - restartTexture.height ) / 2 );	//Dokme-e restart ro neshoon bede
			SDL_Rect restartRect = { ( windowWidth - restartTexture.width ) / 2, ( windowHeight - restartTexture.height ) / 2, restartTexture.width, restartTexture.height };	//mokhtasaat-e dokme-e restart
			SBDL::updateRenderScreen();	//safhe ro update kon
			while ( SBDL::isRunning() ) {	// Ta vaghti ke taraf baaZ ro nabaste bood:
				SBDL::updateEvents();	//Eventhaa ro update kon
				if ( SBDL::mouseInRect( restartRect ) && SBDL::Mouse.clicked() ) {	//Agar roo-e restart click kard
					lose = false;	//baaZ gharaare az avval shoroo' beshe
					ballCor = { 200, 100 };	//Mokhtasaat-e toop ro reset mikonim
					SBDL::showTexture( ballTexture, ballCor.x, ballCor.y );	//toop ro neshoon midim
					SBDL::updateRenderScreen();	//safhe ro update mikonim
					break;	//va az while khaarej mishim :)) 
				}
			}
			
		}
		
		else { //age nabaakhte bood va baaZ dar jaryan bood
		
			SBDL::clearRenderScreen();	//Safhe ro sefid kon
		
			ballCor.x += ballVelX;	
			ballCor.y += ballVelY;	//Toop ro harekat bede 
			
			//Sharthaa-e marboot be barkhod-e toop ba haashieHaa-e safhe
			if ( ballCor.x + ballTexture.width >= windowWidth || ballCor.x < 0 ) 
				ballVelX *= -1;
			if ( ballCor.y < 0 )
				ballVelY *= -1;
		
			//Shart-e marboot be baakhtan-e taraf
			if ( ballCor.y + ballTexture.height >= windowHeight ) {
				lose = true;
			}
			
			// baraa-e Mokhtasaat-e toop o racket ye SDL_Rect misaazim... ke befahmim ba ham barkhkord kardan yaa na
			SDL_Rect ballRect = { ballCor.x, ballCor.y, ballTexture.width, ballTexture.height };
			SDL_Rect racketRect = { racketCor.x, racketCor.y, racketTexture.width, racketTexture.height };
			if ( SBDL::hasIntersectionRect( ballRect, racketRect ) ) {	//Age toop khorde bood be racket
				ballVelY *= -1;	//Dge naroo paaEn, boro baalaa!
			}
		
			//Toop o Racket ro bezR to safhe
			SBDL::showTexture( racketTexture, racketCor.x, racketCor.y );
			SBDL::showTexture( ballTexture, ballCor.x, ballCor.y );
		
			//Safhe ro update kon
			SBDL::updateRenderScreen();

			//FPS ro daastaan kon
			int elapsedTime = SBDL::getTime() - loopStartTime;
			if ( elapsedTime < delay ) 
				SBDL::delay( delay - elapsedTime );
			
		}
	
	}

}

