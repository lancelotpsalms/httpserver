PROJECT=httpserver
CC = g++
BIN_DIR=../bin
OBJ_DIR=$(BIN_DIR)
LIBS=-L/usr/local/lib/ -lglog
INCLUDE_DIR=../include
#CPPFLAGS = -g -I$(INCLUDE_DIR) -DDEBUG -Wno-deprecated
CPPFLAGS = -g -I$(INCLUDE_DIR) -Wno-deprecated 
LDFLAGS = -ldl
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
$(PROJECT):$(OBJECTS)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CPPFLAGS) $(LDFLAGS) $(LIBS)
$(OBJ_DIR)/%.o:%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(LDFLAGS)
clean:
	rm $(OBJ_DIR)/*.o

