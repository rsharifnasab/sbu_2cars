
reset: compile
	@reset
	@./cars2.exe
run: compile
	@./cars2.exe
compile:
#	@g++ cars2.cpp -o cars2.exe -std=c++17
	@g++ cars2.cpp -o cars2.exe -std=c++17 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
clean:
#	@rm *.exe
	@rm cars2.exe
