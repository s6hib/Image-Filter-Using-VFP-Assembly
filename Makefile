CC = g++
CCFLAGS = -Wall -Wextra -std=c++2a -O3 -mfpu=neon -Dcimg_display=0 -fexceptions 
STUDENT = -Dstudent_darken

a.out: main.o student_darken.o
	$(CC) $(CCFLAGS) main.o student_darken.o

student_darken.o: student_darken.s
	as -mfpu=neon -o student_darken.o student_darken.s

main.o: main.cc
	$(CC) $(CCFLAGS) $(STUDENT) -c main.cc

clean:
	rm -rf *.o a.out output.*
