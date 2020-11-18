This is an easier to use and modify makefile, but it is slightly more difficult to read than the simple one:

#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc
CXX = g++ -w
FIND = find

# define any compile-time flags
CFLAGS = -Wall -g -std=c++14  -DNANOVG_GL2  -DGL_GLEXT_PROTOTYPES

# define any directories containing header files other than /usr/include
#
INCLUDES = -I./external -I../external  -I./tinygrammar -I/usr/local/include/GLFW

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =  -L./lib -L/usr/local/lib/

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lpthread -lm -lglfw3 -ldl  -lXrandr -lX11   -lrt -ldl -lX11 -lGL -lGLU 

# define the C source files
SRCS = tinygrammar/draw.cpp\
			 tinygrammar/expansion_manager.cpp\
			 tinygrammar/grammar_core.cpp\
			 tinygrammar/model.cpp\
			 tinygrammar/operator.cpp\
			 tinygrammar/rule.cpp\
			 tinygrammar/shape.cpp\
			 tinygrammar/svg.cpp\
			 tinygrammar/tangle_utilities.cpp\
			 external/jsonxx.cpp\
			 external/format.cpp\
			 external/clipper/clipper.cpp\
			 external/nanovg/nanovg.cpp\
			 external/nanovg/nanovg_gl2.cpp\
			#  external/imgui/imgui.cpp\
			#  external/imgui/imgui_demo.cpp\
			#  external/imgui/imgui_draw.cpp\
			#  external/imgui/imgui_impl_glfw.cpp

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
MAIN = main_prog
# MAIN = main_tag_svg main_timeline

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean all

all:	$(MAIN)
				@echo  Simple compiler named mycc has been compiled


# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)

.cpp.o:
				$(CXX) $(CFLAGS) $(INCLUDES) -c $<  -o $@

# main_tag_svg:	$(OBJS) tinygrammar/main_tag_svg.o
# 			$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LFLAGS) $(LIBS)

# main_timeline:	$(OBJS) tinygrammar/main_timeline.o
# 			$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LFLAGS) $(LIBS)

main_prog:	$(OBJS) tinygrammar/main.o
			$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LFLAGS) $(LIBS)

clean:
				$(RM) *.o *~ $(MAIN)
				$(RM) $(OBJS)
				$(FIND) . -name "*.o" -exec rm '{}' \;
