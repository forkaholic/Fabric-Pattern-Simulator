SRC = src/main.cpp
INCL_DIRS = -I../libgraphics/include -I../libutil/include -Iinclude
LIB_DIRS = -L../libgraphics/lib -L../libutil/lib -Llib
LIBS = -lgraphics -lutil -lglew32 -lopengl32 -lfreeglut


make:
	g++ -g -c -o shaderfuncs.o src/shaderfuncs.cpp -Iinclude $(INCL_DIRS) $(LIB_DIRS) $(LIBS)
	g++ -g -o out.exe $(SRC) shaderfuncs.o $(INCL_DIRS) $(LIB_DIRS) $(LIBS)
	@del *.o
	@.\out.exe
