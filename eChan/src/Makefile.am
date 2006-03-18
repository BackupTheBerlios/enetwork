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
                Msg_AC.cpp \
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
                Msg_D.cpp \
                Msg_OM.cpp \
                Bot.cpp \
                BotCService.cpp \
                MsgMonitor.cpp \
                MD5.cpp \
                Crypto.cpp \
                SqlManager.cpp \
                cservice/SqlChannelAccess.cpp \
                cservice/SqlUser.cpp \
                cservice/SqlChannel.cpp \
                cservice/Command.cpp \
                cservice/CommandWHOIS.cpp \
                cservice/CommandQUOTE.cpp \
                cservice/CommandLOGIN.cpp \
                cservice/CommandUP.cpp \
                cservice/CommandDOWN.cpp \
                cservice/CommandOP.cpp \
                cservice/CommandDEOP.cpp \
                cservice/CommandVOICE.cpp \
                cservice/CommandDEVOICE.cpp \
                cservice/CommandHELLO.cpp \
                cservice/CommandREGISTER.cpp \
                cservice/SQL.cpp

eChan_LDFLAGS = -L$(MYSQLPP_LIB) -lmysqlpp
eChan_CXXFLAGS = -I../include/ -I../ -Icservice/include/ -I$(MYSQLPP_INCLUDE) -I$(MYSQL_INCLUDE)

EXTRA_DIST = cservice/include/Command.h \
             cservice/include/CommandLOGIN.h \
             cservice/include/CommandQUOTE.h \
             cservice/include/CommandWHOIS.h \
             cservice/include/CommandUP.h \
             cservice/include/CommandDOWN.h \
             cservice/include/CommandOP.h \
             cservice/include/CommandDEOP.h \
             cservice/include/CommandVOICE.h \
             cservice/include/CommandDEVOICE.h \
             cservice/include/CommandHELLO.h \
             cservice/include/SQL.h \
             cservice/include/SqlUser.h \
             cservice/include/SqlChannel.h \
             cservice/include/SqlChannelAccess.h \
             cservice/sql/channelaccess.sql \
             cservice/sql/channels.sql \
             cservice/sql/users.sql

bindir = ../bin
