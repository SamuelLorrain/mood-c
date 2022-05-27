a.out: main.o view.o mood_math.o map.o texture.o
	gcc main.o view.o mood_math.o map.o texture.o -lGL -lGLU -lglut -lm

main.o: main.c
	gcc -c main.c -lGL -lGLU -lglut -lm -o main.o

view.o: view.c view.h texture.o
	gcc -c view.c -lGL -lGLU -lglut -lm -o view.o

mood_math.o: mood_math.c mood_math.h
	gcc -c mood_math.c -lGL -lGLU -lglut -lm -o mood_math.o

map.o: map.c map.h
	gcc -c map.c -lGL -lGLU -lglut -lm -o map.o

texture.o: texture/texture.c texture/texture.h
	gcc -c texture/texture.c -lGL -lGLU -lglut -lm -o texture.o
