cc = g++
#Add new classes to this OBJS, Ex: NewClass.o
OBJS =   player.o invader.o bullet.o  barrier.o ScreenGen.o gameEngine.o main.o
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread


main :  $(OBJS) #If this is updated, it only compiles the file that was updated
	${cc}  $(OBJS) -o spaceInvaders $(LIBS) 

#Here you should add the files here. Ex: NewClass: NewClass.h, Only changed files will be compiled
barrier.o : barrier.h
player.o : player.h
invader.o : invader.h
bullet.o : bullet.h
gameEngine.o : gameEngine.h 
ScreenGen.o:  ScreenGen.h gameEngine.h
main.o : ScreenGen.h	player.h

#These rules bellow are implicit in the rules above
#main.cpp ScreenGen.h #If this is updated, it only compiles this files
#	${cc} -c main.cpp
#ScreenGen.cpp ScreenGen.h #If this is updated, it only compiles this files
#	${cc} -c ScreenGen.cpp 

clean:
	$(RM) main $(OBJS)
