CPP = g++
CPARAM = -W -Wall -c -I../include/
OBJS = main.o Socket.o ConfParser.o tools.o Msg.o Msg_EB.o Msg_N.o Msg_S.o PreServerMsg.o Msg_B.o Channel.o Client.o MsgTokenizer.o Network.o Server.o SocketException.o debug.o Msg_G.o
.SUFFIXES: .o .cpp

.cpp.o:
	$(CPP) $< -o @$ $(CPARAM)

all: eChan

eChan:
	$(CPP) $(OBJS) -W -Wall -I../include -o ../bin/eChan

main.o:
	$(CPP) -o main.o $(CPARAM) main.cpp

Socket.o:
	$(CPP) -o Socket.o $(CPARAM) Socket.cpp

ConfParser.o:
	$(CPP) -o ConfParser.o $(CPARAM) ConfParser.cpp

tools.o:
	$(CPP) -o tools.o $(CPARAM) tools.cpp

Msg.o:
	$(CPP) -o Msg.o $(CPARAM) Msg.cpp

Msg_EB.o:
	$(CPP) -o Msg_EB.o $(CPARAM) Msg_EB.cpp

Msg_N.o:
	$(CPP) -o Msg_N.o $(CPARAM) Msg_N.cpp

Msg_S.o:
	$(CPP) -o Msg_S.o $(CPARAM) Msg_S.cpp

PreServerMsg.o:
	$(CPP) -o PreServerMsg.o $(CPARAM) PreServerMsg.cpp

Msg_B.o:
	$(CPP) -o Msg_B.o $(CPARAM) Msg_B.cpp

Msg_G.o:
	$(CPP) -o Msg_G.o $(CPARAM) Msg_G.cpp

Channel.o:
	$(CPP) -o Channel.o $(CPARAM) Channel.cpp

Client.o:
	$(CPP) -o Client.o $(CPARAM) Client.cpp

MsgTokenizer.o:
	$(CPP) -o MsgTokenizer.o $(CPARAM) MsgTokenizer.cpp

Network.o:
	$(CPP) -o Network.o $(CPARAM) Network.cpp

Server.o:
	$(CPP) -o Server.o $(CPARAM) Server.cpp

SocketException.o:
	$(CPP) -o SocketException.o $(CPARAM) SocketException.cpp

debug.o:
	$(CPP) -o debug.o $(CPARAM) debug.cpp

main.o: main.cpp
Channel.o: Channel.cpp
Client.o: Client.cpp
MsgTokenizer.o: MsgTokenizer.cpp
Network.o: Network.cpp
Server.o: Server.cpp
SocketException.o: SocketException.cpp
Socket.o: Socket.cpp
ConfParser.o: ConfParser.cpp
tools.o: tools.cpp
Msg.o: Msg.cpp
debug.o: debug.cpp
Msg_S.o: Msg_S.cpp
PreServerMsg.o: PreServerMsg.cpp
Msg_B.o: Msg_B.cpp
Msg_EB.o: Msg_EB.cpp
Msg_N.o: Msg_N.cpp
Msg_G.o: Msg_G.cpp
eChan: $(OBJS)

eChan: main.o \
       Socket.o \
       Channel.o \
       Client.o \
       ConfParser.o \
       tools.o \
       Msg.o \
       debug.o \
       MsgTokenizer.o \
       Network.o \
       Server.o \
       SocketException.o \
       Msg_S.o \
       PreServerMsg.o \
       Msg_B.o \
       Msg_EB.o \
       Msg_N.o \
       Msg_G.o


clean:
	rm -f $(OBJS)
