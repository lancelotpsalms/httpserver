CC = g++
OBJ_DIR=../obj
BIN_DIR=../bin
INCLUDE_DIR=../include
#CPPFLAGS = -g -I$(INCLUDE_DIR) -DDEBUG -Wno-deprecated
CPPFLAGS = -g -I$(INCLUDE_DIR) -Wno-deprecated 
LDFLAGS = -ldl
http:axbserver.o main.o axbserver.o epollpoller.o looper.o socketutil.o connectionmanager.o slab.o request.o responsebuilderchain.o responsebuilderchain.o
	$(CC) -o $(BIN_DIR)/$@ $^ $(CPPFLAGS) $(LDFLAGS)
clean:
	rm *.o

