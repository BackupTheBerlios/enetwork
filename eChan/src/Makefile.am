bin_PROGRAMS = eChan
eChan_SOURCES = main.cpp \
                Socket.cpp \
                Channel.cpp \
                Client.cpp \
                ConfigParser.cpp \
                tools.cpp \
                debug.cpp \
                MsgTokenizer.cpp \
                Network.cpp \
                Server.cpp \
                SocketException.cpp \
                Msg_S.cpp \
                PreServerMsg.cpp \
                Msg_B.cpp \
                Msg_EB.cpp \
                Msg_N.cpp \
                Msg_G.cpp \
                Msg_Q.cpp \
                InBuffer.cpp \
                OutBuffer.cpp \
                MsgParseSystem.cpp \
                OutMsgSystem.cpp \
                P10Tokens.cpp \
                Msg_J.cpp \
                Msg_L.cpp \
                Msg_SQ.cpp \
                Msg_M.cpp \
                Msg_K.cpp \
                Msg_CM.cpp \
                Msg_T.cpp \
                Msg_C.cpp \
                Msg_O.cpp \
                Msg_P.cpp \
                Msg_OM.cpp \
                Bot.cpp \
                BotCService.cpp \
                MsgMonitor.cpp \
                cservice/Command.cpp \
                cservice/CommandWHOIS.cpp \
                cservice/CommandQUOTE.cpp

eChan_LDFLAGS = -L$(MYSQLPP_LIB) -lmysqlpp
eChan_CXXFLAGS = -I../include/ -I../ -Icservice/include/ -I$(MYSQLPP_INCLUDE)

EXTRA_DIST = cservice/CommandLOGIN.cpp \
             cservice/include/Command.h \
             cservice/include/CommandLOGIN.h \
             cservice/include/CommandQUOTE.h \
             cservice/include/CommandWHOIS.h \
             cservice/include/CServiceSQL.h \
             cservice/sql/channelaccess.sql \
             cservice/sql/channels.sql \
             cservice/sql/users.sql

bindir = ../bin
