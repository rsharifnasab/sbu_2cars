
#include <iostream>
#include <fstream>
#include <algorithm>

#include "SBDL.h"

struct FlippingThing {
	int size;
	Texture *images = nullptr;
	std::string folderAddress = "coins/";
	int currentIndex;
	bool active = false;
};

/*
Yek flippingthing migirad, va meghdaardehiHaa-e avvalie-e aan ra anjaam midahad!
*/
void initializeFlippingCoin( FlippingThing &flipping ) {
	flipping.images = new Texture[ 6 ];
	flipping.size = 6;
	flipping.currentIndex = 0;
	for ( int i = 0; i < flipping.size; i++ ) {
		std::string temp = flipping.folderAddress + std::to_string( i + 1 );
		temp.append( ".png" );
		flipping.images[i] = SBDL::loadTexture( temp );
		//std::cout << "\"" << temp << "\"" << std::endl;
//		std::cout << flipping.images[i].width << std::endl;
	}
}

int main () { 

//	streami ke be file-e mored-e nazaremoon vasl mishe... ba komakesh gharaare mohtaviaat-e file ro bekhoonim
	std::ifstream fin( "pattern" );
	int linesCounter = 0;
	int eachLineLength = 0;
//	while ( fin.good() ){ 
	std::string temp;
	// baa in while gharaare te'dad-e khathaa va tool-e har khat ro be dast biaarim
	while ( getline( fin, temp ) ){
//		std::string temp;
//		std::getline( fin, temp );
		eachLineLength = std::max( eachLineLength, (int) (temp.size()) );
		linesCounter++;
	}
//	std::cout << linesCounter << std::endl;
//	baa tavajjoh be te'dad-e sekkeHaa dar har satr, va hamchenin te'dad-e satrHaa, andaaze-e safhe ro moshakhas mikonam.
	int windowWidth = eachLineLength * 120;
	int windowHeight = linesCounter * 120;
	SBDL::InitEngine( "Some Flipping Stuff", windowWidth, windowHeight );
	
//	aaraayeE ke sekkeHaa-e charkhaan raa dar khod negah midaarad
	FlippingThing **coinsAr = new FlippingThing*[ linesCounter ];
	for ( int i = 0; i < linesCounter; i++ )
		coinsAr[i] = new FlippingThing[ eachLineLength ];
//	aaraayeE ke moshakhas mikonad ke dar har noghte aayaaa sekke daarim, yaa oon khoone khaalie!	
	int **grid = new int*[ linesCounter ];
	for ( int i = 0; i < linesCounter; i++ )
		grid[i] = new int[ eachLineLength ];
	
	// baa do ta dastoor-e ba'di, be ifstreamemoon migim ke bargard avval-e file!
	fin.clear();
	fin.seekg( 0, std::ios::beg );
	int lineCounterTemp = 0;
	//aaraayeHaa-e grid va coinsAr ro meghdaarDehi mikonim baa tavajjoh be file
	while ( getline( fin, temp ) ) {
		if ( !temp.empty() ) {
			for ( int i = 0; i < temp.size(); i++ ){
				grid[lineCounterTemp][i] = ( temp[i] - '0' );
				if ( grid[lineCounterTemp][i] == 1 ) {
					initializeFlippingCoin( coinsAr[lineCounterTemp][i] );
//					std::cout << coinsAr[lineCounterTemp][i].images[0].underneathTexture << std::endl;
				}
			}
		}
		lineCounterTemp++;
	}
	
	const int FPS = 25;
	const int delay = 1000 / FPS;
	
/*	for ( int i = 0; i < linesCounter; i++ ) {
		for ( int j = 0; j < eachLineLength; j++ ) 
			std::cout << grid[i][j];
		std::cout << std::endl;
	}
	
	for ( int i = 0; i < linesCounter; i++ ) {
		for ( int j = 0; j < eachLineLength; j++ )
			std::cout << coinsAr[i][j].active;
		std::cout << std::endl;
	}*/
	
	SBDL::showTexture( coinsAr[0][0].images[ 0 ], 0, 0 );
	
	int counter = 0;
	//counter gharaar ast ke jolo-e charkhesh-e biravie-e sekkeHaa raa begirad... be estefaadeHaaE ke azash too-e while kardam deghat konid
	
	while ( SBDL::isRunning() ) {
	
		counter++;
	
		SBDL::updateEvents();
		int loopStartTime = SBDL::getTime();
		
		SBDL::clearRenderScreen();
		
		//kaar-e khaasi nakardam inja... yaadetoone file-e ghabli ro? baraa-e charkhesh-e ye sekke? hamoon karhaa ro for zadam va roo-e hame-e sekkeHaa anjaam daadam!
		//oonjaaE ke showTexture ro seda zadam, be raveshi ke estefaade kardam baraa-e moshakhas kardan-e jaa-e texture deghat konid!
		for ( int i = 0; i < linesCounter; i++ ) 
			for ( int j = 0; j < eachLineLength; j++ ) { 
				if ( grid[i][j] == 1 ){
					SBDL::showTexture( coinsAr[i][j].images[ coinsAr[i][j].currentIndex ], 120 * j + 60 - coinsAr[i][j].images[coinsAr[i][j].currentIndex].width / 2, 120 * i );
					if ( counter > 2 )
						coinsAr[i][j].currentIndex = (coinsAr[i][j].currentIndex + 1) % coinsAr[i][j].size;
				}
			}
		if ( counter > 2 )
			counter = 0;
		SBDL::updateRenderScreen();
		
		int elapsedTime = SBDL::getTime() - loopStartTime;
		if ( elapsedTime < delay ) 
			SBDL::delay( delay - elapsedTime );
	
	}
	
	return 0;

}

