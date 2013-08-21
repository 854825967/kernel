include makefile.depend

CXX = g++
CC = gcc
LD = ld
RM = rm -f
CXXFLAGS += -Wall -D__LINUX_64__

DEBUG_OBJS = Debug/XXAL_chat.o Debug/main.o
RELEASE_OBJS = Release/XXAL_chat.o Release/main.o


.PHONY: debug release clean

debug :	$(DEBUG_OBJS)
	$(CXX) -shared -o libchat.so ./Debug/*.o
release: $(RELEASE_OBJS)
	$(CXX) -shared -o libchat.so ./Release/*.o


Debug/%.o: %.c
	$(CXX) -c $(CXXFLAGS) -D _DEBUG -pg -g -fPIC $< -o $@

Debug/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -D _DEBUG -pg -g -fPIC $< -o $@

Release/%.o : %.c
	$(CXX) -c $(CXXFLAGS) -O -fPIC $< -o $@

Release/%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -O -fPIC $< -o $@

clean:
	find ./ -name "*.o" | xargs rm -f

