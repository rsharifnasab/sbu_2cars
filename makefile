
reset: reset_compile
	@./cars2.exe

run: compile
	@./cars2.exe

compile:
		@g++ cars2.cpp -o cars2.exe -Wall -std=c++17 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

reset_compile:
	@reset
	@g++ cars2.cpp -o cars2.exe -Wall -std=c++17 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

clean:
	@rm *.exe
	#@rm cars2.exe
