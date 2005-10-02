CPP = g++
CPARAM = -W -Wall -c -I../include/ -g
OBJS = main.o Socket.o ConfigParser.o tools.o Msg_EB.o Msg_N.o Msg_S.o PreServerMsg.o Msg_B.o Channel.o Client.o MsgTokenizer.o Network.o Server.o SocketException.o debug.o Msg_G.o Msg_C.o Msg_Q.o InBuffer.o OutBuffer.o InMsgSystem.o MsgParseSystem.o OutMsgSystem.o P10Tokens.o Thread.o Msg_J.o Msg_L.o Msg_SQ.o Msg_M.o Msg_K.o

.SUFFIXES: .o .cpp

.cpp.o:
	$(CPP) $< -o @$ $(CPARAM)

all: eChan

eChan:
	$(CPP) $(OBJS) -W -Wall -I../include -o ../bin/eChan -lpthread

main.o:
	$(CPP) -o main.o $(CPARAM) main.cpp

Socket.o:
	$(CPP) -o Socket.o $(CPARAM) Socket.cpp

ConfigParser.o:
	$(CPP) -o ConfigParser.o $(CPARAM) ConfigParser.cpp

tools.o:
	$(CPP) -o tools.o $(CPARAM) tools.cpp

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

Msg_C.o:
	$(CPP) -o Msg_C.o $(CPARAM) Msg_C.cpp

Msg_Q.o:
	 $(CPP) -o Msg_Q.o $(CPARAM) Msg_Q.cpp

InBuffer.o: 
	$(CPP) -o InBuffer.o $(CPARAM) InBuffer.cpp

OutBuffer.o:
	$(CPP) -o OutBuffer.o $(CPARAM) OutBuffer.cpp

InMsgSystem.o:
	$(CPP) -o InMsgSystem.o $(CPARAM) InMsgSystem.cpp

MsgParseSystem.o:
	$(CPP) -o MsgParseSystem.o $(CPARAM) MsgParseSystem.cpp

OutMsgSystem.o:
	$(CPP) -o OutMsgSystem.o $(CPARAM) OutMsgSystem.cpp

P10Tokens.o:
	$(CPP) -o P10Tokens.o $(CPARAM) P10Tokens.cpp

Thread.o:
	$(CPP) -o Thread.o $(CPARAM) Thread.cpp

Msg_J.o:
	$(CPP) -o Msg_J.o $(CPARAM) Msg_J.cpp

Msg_L.o:
	$(CPP) -o Msg_L.o $(CPARAM) Msg_L.cpp

Msg_SQ.o:
	$(CPP) -o Msg_SQ.o $(CPARAM) Msg_SQ.cpp

Msg_M.o:
	$(CPP) -o Msg_M.o $(CPARAM) Msg_M.cpp

Msg_K.o:
	$(CPP) -o Msg_K.o $(CPARAM) Msg_K.cpp

main.o: main.cpp
Channel.o: Channel.cpp
Client.o: Client.cpp
MsgTokenizer.o: MsgTokenizer.cpp
Network.o: Network.cpp
Server.o: Server.cpp
SocketException.o: SocketException.cpp
Socket.o: Socket.cpp
ConfigParser.o: ConfigParser.cpp
tools.o: tools.cpp
debug.o: debug.cpp
Msg_S.o: Msg_S.cpp
PreServerMsg.o: PreServerMsg.cpp
Msg_B.o: Msg_B.cpp
Msg_EB.o: Msg_EB.cpp
Msg_N.o: Msg_N.cpp
Msg_G.o: Msg_G.cpp
Msg_C.o: Msg_C.cpp
Msg_Q.o: Msg_Q.cpp
InBuffer.o: InBuffer.cpp
OutBuffer.o: OutBuffer.cpp
InMsgSystem.o: InMsgSystem.cpp
MsgParseSystem.o: MsgParseSystem.cpp
OutMsgSystem.o: OutMsgSystem.cpp
P10Tokens.o: P10Tokens.cpp
Thread.o: Thread.cpp
Msg_J.o: Msg_J.cpp
Msg_L.o: Msg_L.cpp
Msg_SQ.o: Msg_SQ.cpp
Msg_M.o: Msg_M.cpp
Msg_K.o: Msg_K.cpp

eChan: $(OBJS)

eChan: main.o \
       Socket.o \
       Channel.o \
       Client.o \
       ConfigParser.o \
       tools.o \
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
       Msg_G.o \
       Msg_C.o \
       Msg_Q.o \
       InBuffer.o \
       OutBuffer.o \
       InMsgSystem.o \
       MsgParseSystem.o \
       OutMsgSystem.o \
       P10Tokens.o \
       Thread.o \
       Msg_J.o \
       Msg_L.o \
       Msg_SQ.o \
       Msg_M.o \
       Msg_K.o

clean:
	rm -f $(OBJS)
