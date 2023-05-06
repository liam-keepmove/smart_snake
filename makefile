object=Point.o Tools.o Food.o Snake.o RectMap.o Controller.o main.o

all:$(object)
	g++ -g -std=c++17 $(object) -lpthread -lncursesw -o start.out

Point.o:Point.hpp Point.cpp
	g++ -g -std=c++17 -c Point.cpp

Tools.o:Point.hpp Tools.hpp Tools.cpp
	g++ -g -std=c++17 -c Tools.cpp

Food.o:Point.hpp RectMap.hpp Snake.hpp Food.hpp Food.cpp
	g++ -g -std=c++17 -c Food.cpp 

Snake.o:Tools.hpp Point.hpp RectMap.hpp Snake.hpp Snake.cpp
	g++ -g -std=c++17 -c Snake.cpp

RectMap.o:Point.hpp RectMap.hpp RectMap.cpp
	g++ -g -std=c++17 -c RectMap.cpp

Controller.o:RectMap.hpp Snake.hpp Food.hpp Controller.hpp Controller.cpp
	g++ -g -std=c++17 -c Controller.cpp

main.o:Snake.hpp RectMap.hpp Food.hpp Controller.hpp main.cpp
	g++ -g -std=c++17 -c main.cpp

clean:$(object)
	rm -rf $(object)
