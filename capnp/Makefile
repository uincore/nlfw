#CC = clang
#CXX = clang++

BASEDIR = ./

UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

#WARN_FLAGS = -Werror=implicit-function-declaration \
#             -Werror=incompatible-pointer-types \
#             -Werror=int-conversion \
#             -Werror=return-type \
#             -Werror=format-extra-args \
#             -Wno-deprecated-declarations

CFLAGS = -std=gnu11 -g -fPIC -O2 $(WARN_FLAGS) -I./lib
CXXFLAGS = -std=c++11 -g -fPIC -O2 $(WARN_FLAGS)
EXTRA_LIBS = -lpthread

ifeq ($(UNAME_S),Darwin)
	ZMQ_LIBS = -L/usr/local/lib -lzmq
	CAPNP_LIBS = -L/usr/local/lib -lcapnpc 

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

CEREAL_CXXFLAGS = 
CEREAL_OBJS = cereal/gen/c/log.capnp.o cereal/gen/c/car.capnp.o
CAPN_OBJS   = lib/capn.o lib/capn-malloc.o lib/capn-stream.o

CWD := $(shell pwd)

OBJS = test.o \
       $(CEREAL_OBJS) \
       $(CAPN_OBJS)

DEPS := $(OBJS:.o=.d)

all: test

test: $(OBJS)
	@echo "[ LINK ] $@"
	$(CC) -fPIC -o '$@' $^ \
            $(CEREAL_LIBS) \
            $(ZMQ_LIBS) \
    		$(CAPNP_LIBS)

#            $(EXTRA_LIBS) \

test.o: test.c
	$(CC) -fPIC -c -o '$@' $^ \
	-I. \
	$(CFLAGS) \
		$(EXTRA_LIBS) \
    	$(ZMQ_FLAGS) \
    	$(ZMQ_LIBS)  \
    	$(CAPNP_LIBS)

log.capnp.o: cereal/gen/c/log.capnp.c
	@echo "[ CXX ] $@"
	$(CC) $(CFLAGS) $(CEREAL_CFLAGS) \
           -c -o '$@' '$<'

car.capnp.o: cereal/gen/c/car.capnp.c
	@echo "[ CXX ] $@"
	$(CC) $(CFLAGS) $(CEREAL_CFLAGS) \
           -c -o '$@' '$<'

capn.o: lib/capn.c
	@echo "[ CXX ] $@"
	$(CC) $(CFLAGS) $(CEREAL_CFLAGS) \
           -c -o '$@' '$<'

capn-malloc.o: lib/capn-malloc.c
	@echo "[ CXX ] $@"
	$(CC) $(CFLAGS) $(CEREAL_CFLAGS) \
           -c -o '$@' '$<'

capn-stream.o: lib/capn-stream.c
	@echo "[ CXX ] $@"
	$(CC) $(CFLAGS) $(CEREAL_CFLAGS) \
           -c -o '$@' '$<'


clean:
	rm -rf $(OBJS)
	rm -rf test 
	rm -rf *.dSYM
