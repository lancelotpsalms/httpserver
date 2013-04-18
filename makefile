CC = g++
OBJ_DIR=obj
BIN_DIR=bin
CPPFLAGS = -g
INCLUDE_DIR=include
LDFLAGS = -ldl
http:luaserver.o main.o luaengine.o luascript.o request.o responsemanager.o
	$(CC) -o http main.o request.o luaserver.o luaengine.o luascript.o responsemanager.o liblua52.a $(CPPFLAGS) $(LDFLAGS)
	mv http ./bin/http -f
clean:
	rm *.o

