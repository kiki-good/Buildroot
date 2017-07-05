################################################################################
#
# [Sky] - Simple makefile to build the amalagated JsonCpp source.
#
# It would have been better to use the standard cmake build, but our version
# of builroot is so old it doesn't support the CMAKETARGETS builder. 
#
################################################################################

CFLAGS = -fPIC -std=c++11 -Wall -Wconversion -Wshadow -Wextra -Werror=conversion

CFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden
CFLAGS += -DJSON_API='__attribute__ ((visibility ("default")))'

LIB_NAME = libjsoncpp.so

SRCS = jsoncpp.cpp
OBJS = $(patsubst %.cpp,%.o,$(SRCS))


%.o: %.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(LIB_NAME): $(OBJS)
	$(LD) -shared -soname,$(LIB_NAME) -o $(LIB_NAME) $(OBJS)

all: $(LIB_NAME)

.PHONY: all 

clean:
	rm -f $(LIB_NAME) *.o


