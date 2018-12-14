CXX = g++
CFLAGS = -std=c++14 -g -Wall
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $< 

#Level: level.o
#	$(CXX) -o $@ $^ $(LIBS)



Game: main.o menu.o level.o GuiGrid.o MsCell.o MsGame.o
	$(CXX) -o $@ $^ $(LIBS)

#GuiGrid.exe: GuiGrid.o MsCell.o MsGame.o
#	$(CXX) -o $@ $^ $(LIBS)

clean:
	$(RM) Game *.o $(OBJECTS)
