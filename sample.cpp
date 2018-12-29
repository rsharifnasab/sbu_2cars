
/*
To compile with g++:
g++ Pong.cpp -o Pong -std=c++11 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
*/
	
	Texture racketTexture = SBDL::loadTexture( "assets/racket.png" );	
	
	while ( SBDL::isRunning() )

	
		int loopStartTime = SBDL::getTime();

			int elapsedTime = SBDL::getTime() - loopStartTime;
			if ( elapsedTime < delay ) 
				SBDL::delay( delay - elapsedTime );

	
		SBDL::updateEvents();
		

SBDL::showTexture( restartTexture, ( windowWidth - restartTexture.width ) / 2, ( windowHeight - restartTexture.height ) / 2 );	


SDL_Rect restartRect = { ( windowWidth - restartTexture.width ) / 2, ( windowHeight - restartTexture.height ) / 2, restartTexture.width, restartTexture.height };

SBDL::updateRenderScreen();	//safhe ro update kon


if ( SBDL::mouseInRect( restartRect ) && SBDL::Mouse.clicked() ) 
		
SDL_Rect ballRect = { ballCor.x, ballCor.y, ballTexture.width, ballTexture.height };

SBDL::showTexture( racketTexture, racketCor.x, racketCor.y );

			
