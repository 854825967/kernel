include ../../makefile.depend

CXX = g++
CC = gcc
RM = rm -f
CXXFLAGS += -Wall -D__LINUX_64__

DEBUG_OBJS = Debug/ConfigManage.o
RELEASE_OBJS = Release/ConfigManage.o

.PHONY: debug release clean

debug :	$(DEBUG_OBJS)
	sh ./make.sh debug

release: $(RELEASE_OBJS)
	sh ./make.sh release


Debug/%.o: %.c
ifeq (./Debug, $(wildcard ./Debug))
else
	mkdir ./Debug
endif
	$(CXX) -c $(CXXFLAGS) -D _DEBUG -pg -g $< -o $@
ifeq ($(CURRENT_PATH)/Debug, $(wildcard $(CURRENT_PATH)/Debug))
else
	mkdir $(CURRENT_PATH)/Debug
endif
	cp -f $@ $(CURRENT_PATH)/$@

Debug/%.o: %.cpp
ifeq (./Debug, $(wildcard ./Debug))
else
	mkdir ./Debug
endif
	$(CXX) -c $(CXXFLAGS) -D _DEBUG -pg -g $< -o $@
ifeq ($(CURRENT_PATH)/Debug, $(wildcard $(CURRENT_PATH)/Debug))
else
	mkdir $(CURRENT_PATH)/Debug
endif
	cp -f $@ $(CURRENT_PATH)/$@

Release/%.o : %.c
ifeq (./Release, $(wildcard ./Release))
else
	mkdir ./Release
endif
	$(CXX) -c $(CXXFLAGS) -O $< -o $@
ifeq ($(CURRENT_PATH)/Release, $(wildcard $(CURRENT_PATH)/Release))
else
	mkdir $(CURRENT_PATH)/Release
endif
	cp -f $@ $(CURRENT_PATH)/$@

Release/%.o : %.cpp
ifeq (./Release, $(wildcard ./Release))
else
	mkdir ./Release
endif
	$(CXX) -c $(CXXFLAGS) -O $< -o $@
ifeq ($(CURRENT_PATH)/Release, $(wildcard $(CURRENT_PATH)/Release))
else
	mkdir $(CURRENT_PATH)/Release
endif
	cp -f $@ $(CURRENT_PATH)/$@

clean:
	find ./ -name "*.o" | xargs rm -f

