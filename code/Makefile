This is an easier to use and modify makefile, but it is slightly more difficult to read than the simple one:

#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc
CXX = g++

# define any compile-time flags
CFLAGS = -Wall -g -std=c++14 

# define any directories containing header files other than /usr/include
#
INCLUDES = -I./external -I../external  -I./gTangle

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =  -L./lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lpthread -lm 

# define the C source files
SRCS = 		 gTangle/animator.cpp\
			 gTangle/animator_matrix.cpp\
			 gTangle/clipper_methods.cpp\
			 gTangle/csg_tree.cpp\
			 gTangle/draw.cpp\
			 gTangle/expansion_manager.cpp\
			 gTangle/grammar_core.cpp\
			 gTangle/input_figures.cpp\
			 gTangle/main_timeline.cpp\
			 gTangle/operator.cpp\
			 gTangle/rule.cpp\
			 gTangle/shape.cpp\
			 gTangle/svg.cpp\
			 gTangle/tangle_utilities.cpp\
			 gTangle/time_manager.cpp\
			 external/jsonxx.cpp\
			 external/format.cpp\
			 external/clipper/clipper.cpp\
			 external/nanovg/nanovg.cpp\

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.cpp=.o)

# define the executable file 
MAIN = tangles

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:	$(MAIN)
				@echo  Simple compiler named mycc has been compiled

$(MAIN):	$(OBJS)
			$(CXX) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)

.cpp.o:
				$(CXX) $(CFLAGS) $(INCLUDES) -c $<  -o $@ 

clean:
				$(RM) *.o *~ $(MAIN)
				$(RM) $(OBJS)

