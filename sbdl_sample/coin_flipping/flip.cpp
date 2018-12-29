
#include <iostream>

#include "SBDL.h"

struct FlippingThing {
	//Te'daad-e framehaa
	int size;
	//aaraayeE ke gharaare toosh frameHaa ro zakhire konim
	Texture *images;
	//Address-e Folderi ke framehaamoon tooshan
	std::string folderAddress;
	//adadi ke moshakhas mikonad man az aaraaye-e image, baayad kodaam frame raa be kaarbar neshaan daham
	int currentIndex;
};

int main () { 

	// saakhtan-e safhe o in joor chizaa
	const int windowWidth = 500, windowHeight = 500;
	SBDL::InitEngine( "Some Flipping Coin", windowWidth, windowHeight );

	// Yek sekke-e Charkhaan Misaazim...
	FlippingThing flippingCoin;
	flippingCoin.images = new Texture[ 6 ];
	flippingCoin.size = 6;
	flippingCoin.currentIndex = 0;
	flippingCoin.folderAddress = "coins/";
	for ( int i = 0; i < flippingCoin.size; i++ ) {
		//Agar motevajjeh nemishavid ke injaa che ettefaghi dar haal-e oftaadan ast, chap kardan-e temp (va yaa chizhaa-e dige) ro emtehan konid
		std::string temp = flippingCoin.folderAddress + std::to_string( i + 1 );
		temp.append( ".png" );
		flippingCoin.images[i] = SBDL::loadTexture( temp );
//		std::cout << temp << std::endl;
	}
	
	const int FPS = 10;
	const int delay = 1000 / FPS;
	
	while ( SBDL::isRunning() ) {
	
		SBDL::updateEvents();
		int loopStartTime = SBDL::getTime();
	
		SBDL::clearRenderScreen();

//		baa tavajjoh be in ke baayad kodaam frame-e sekke ra neshaan dahim, oon frame ro neshoon bede
//		On menha be khaater-e ine ke sekke howl-e markazesh becharkhe... age motevajjeh nemishid ke chetori in ettefagh daare miofte, roo-e kaghaz baraa-e khodetoon mohaasebe konid.		
		SBDL::showTexture( flippingCoin.images[ flippingCoin.currentIndex ], 100 - flippingCoin.images[flippingCoin.currentIndex].width / 2, 100 );
		// az in be ba'd baayad frame-e ba'D ro neshoon bedam! pas in index ro ye doone ezaafe mikonam.
		flippingCoin.currentIndex++;
		//age reside boodi be tah-e aaraye, az avval shoroo' kon dobRe!
		if ( flippingCoin.currentIndex >= flippingCoin.size )
			flippingCoin.currentIndex = 0;
		
		SBDL::updateRenderScreen();
		
		int elapsedTime = SBDL::getTime() - loopStartTime;
		if ( elapsedTime < delay ) 
			SBDL::delay( delay - elapsedTime );
	
	}
	
	return 0;

}

