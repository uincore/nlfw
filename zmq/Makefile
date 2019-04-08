#CC = clang
#CXX = clang++

BASEDIR = ./

UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

WARN_FLAGS = -Werror=implicit-function-declaration \
             -Werror=incompatible-pointer-types \
             -Werror=int-conversion \
             -Werror=return-type \
             -Werror=format-extra-args \
             -Wno-deprecated-declarations

CFLAGS = -std=gnu11 -g -fPIC -O2 $(WARN_FLAGS)
CXXFLAGS = -std=c++11 -g -fPIC -O2 $(WARN_FLAGS)

ifeq ($(UNAME_S),Darwin)
	ZMQ_LIBS = -L/usr/local/lib -lzmq
else ifeq ($(OPTEST),1)
	ZMQ_LIBS = -lzmq
else ifeq ($(UNAME_M),x86_64)
	EXTERNAL := ../../external
	ZMQ_FLAGS = -I$(EXTERNAL)/zmq/include
	ZMQ_LIBS = -L$(EXTERNAL)/zmq/lib -l:libzmq.a
else ifeq ($(UNAME_M),aarch64)
	ZMQ_FLAGS = -I$(PHONELIBS)/zmq/aarch64/include
	ZMQ_LIBS = -L$(PHONELIBS)/zmq/aarch64/lib -l:libzmq.a
	CXXFLAGS += -lgnustl_shared
endif

CWD := $(shell pwd)


all:hwclient hwserver

hwclient: hwclient.c
	$(CC) -fPIC -o '$@' $^ \
	-I. \
	$(CFLAGS) \
    	$(ZMQ_FLAGS) \
    	$(ZMQ_LIBS)


hwserver: hwserver.c
	$(CC) -fPIC -o '$@' $^ \
	-I. \
	$(CFLAGS) \
    	$(ZMQ_FLAGS) \
    	$(ZMQ_LIBS)


clean:
	rm -rf hwclient
	rm -rf hwserver
	rm -rf *.dSYM
