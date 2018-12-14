CXX = g++ -std=c++11
CFLAGS = -g -Wall
OBJECTS =  run-MsGame.o MsCell.o MsGame.o

cmdMinesweeper.exe: $(OBJECTS)
	$(CXX) -o $@ $^
	
MsCell.o: MsCell.cpp
	$(CXX) -c $(CFLAGS) $< 

MsGame.o: MsGame.cpp
	$(CXX) -c $(CFLAGS) $< 
	
run-MsGame.o: run-MsGame.cpp
	$(CXX) -c $(CFLAGS) $<
	
clean:
	$(RM) $(OBJECTS)
