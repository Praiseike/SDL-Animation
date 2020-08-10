animation: animation.cpp
	g++ animation.cpp -o animation -lSDL2 -lSDL2_image

clean:
	rm *.o
