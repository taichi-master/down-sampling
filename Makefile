src = src
include = $(src)/include

down: down.o image.o modal.o
	g++ down.o image.o modal.o -lpthread -o down

down.o: $(src)/down.cpp
	g++ -c $(src)/down.cpp -o down.o

image.o: $(src)/image.cpp $(include)/image.h
	g++ -c $(src)/image.cpp -o image.o

modal.o: $(src)/modal.cpp $(include)/modal.h
	g++ -c $(src)/modal.cpp -o modal.o

test: test.cpp
	g++ test.cpp -Izi_lib -Izi_lib/external/include -lpthread -lrt -o test

clean:
	rm *.o
	rm down
