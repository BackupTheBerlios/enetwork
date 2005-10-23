CPP = g++
CPARAM = -W -Wall -c -I../../include/ -Iinclude/ -g
OBJS = CommandWHOIS.o CommandQUOTE.o

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

Command.o: $(OBJS)
CommandWHOIS.o: CommandWHOIS.cpp
CommandQUOTE: CommandQUOTE.cpp

clean:
	rm -f $(OBJS) Command.o

