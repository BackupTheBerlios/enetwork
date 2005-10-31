CPP = g++
CPARAM = -W -Wall -c -I../../include/ -Iinclude/ -I/usr/local/include/ -g
OBJS = CommandWHOIS.o CommandQUOTE.o CommandLOGIN.o

.SUFFIXES: .o .cpp
.cpp.o:
	$(CPP) $< -o @$ $(CPARAM)

all: Command.o

Command.o:
	$(CPP) -o Command.o $(CPARAM) Command.cpp

CommandWHOIS.o:
	$(CPP) -o CommandWHOIS.o $(CPARAM) CommandWHOIS.cpp

CommandQUOTE.o:
	$(CPP) -o CommandQUOTE.o $(CPARAM) CommandQUOTE.cpp

CommandLOGIN.o:
	$(CPP) -o CommandLOGIN.o $(CPARAM) CommandLOGIN.cpp

Command.o: $(OBJS)
CommandWHOIS.o: CommandWHOIS.cpp
CommandQUOTE.o: CommandQUOTE.cpp
CommandLOGIN.o: CommandLOGIN.cpp

clean:
	rm -f $(OBJS) Command.o

