CC=g++
CFLAGS=-std=c++0x -g -pthread -Wall -lSDL2 -lSDL2_image -lSDL2_ttf
EXEC=bin/game bin/test

all: $(EXEC)

bin/game: obj/Timer.o obj/Moves.o obj/Movement.o obj/Fighters.o obj/Player.o obj/Position.o obj/Health.o obj/Map.o obj/Input.o obj/CircularBuffer.o obj/SpriteManager.o obj/Box_Interface.o obj/BoxArea.o obj/TextArea.o obj/Interface_Elements.o obj/Slider.o obj/Interface.o obj/Ihm.o obj/Boxcolliders.o obj/Game.o obj/mainJeu.o
	$(CC) -o $@ $^ $(CFLAGS)

bin/test: obj/Timer.o obj/Moves.o obj/Movement.o obj/Fighters.o obj/Player.o obj/Position.o obj/Health.o obj/Map.o obj/Input.o obj/CircularBuffer.o obj/SpriteManager.o obj/Box_Interface.o obj/BoxArea.o obj/TextArea.o obj/Interface_Elements.o obj/Slider.o obj/Interface.o obj/Ihm.o obj/Boxcolliders.o obj/Game.o obj/mainTest.o
	$(CC) -o $@ $^ $(CFLAGS)

obj/Timer.o: src/core/Timer.cpp src/core/Timer.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Moves.o: src/core/Moves.cpp src/core/Moves.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Movement.o: src/core/Movement.cpp src/core/Movement.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Fighters.o: src/core/Fighters.cpp src/core/Fighters.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Player.o: src/core/Player.cpp src/core/Player.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Position.o: src/core/Position.cpp src/core/Position.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Health.o:src/core/Health.cpp src/core/Health.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Map.o: src/txt/Map.cpp src/txt/Map.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Input.o: src/txt/Input.cpp src/txt/Input.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/CircularBuffer.o: src/core/CircularBuffer.cpp src/core/CircularBuffer.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/SpriteManager.o: src/sdl2/SpriteManager.cpp src/sdl2/SpriteManager.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Box_Interface.o: src/sdl2/Box_Interface.cpp src/sdl2/Box_Interface.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/BoxArea.o: src/sdl2/BoxArea.cpp src/sdl2/BoxArea.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/TextArea.o: src/sdl2/TextArea.cpp src/sdl2/BoxArea.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Interface_Elements.o: src/sdl2/Interface_Element.cpp src/sdl2/Interface_Element.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Slider.o: src/sdl2/Slider.cpp src/sdl2/Slider.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Interface.o: src/sdl2/Interface.cpp src/sdl2/Interface.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Ihm.o: src/sdl2/Ihm.cpp src/sdl2/Ihm.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Boxcolliders.o: src/sdl2/Boxcolliders.cpp src/sdl2/Boxcolliders.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Game.o: src/txt/Game.cpp src/txt/Game.h
	$(CC) -o $@ -c $< $(CFLAGS)

obj/mainJeu.o: src/core/mainJeu.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/mainTest.o: src/core/mainTest.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f obj/*.o core

mrproper: clean
	rm -f $(EXEC)
