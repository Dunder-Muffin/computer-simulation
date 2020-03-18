CC = g++
CFLAGS = -Wall -lglut -lGLU -lGL -O3 -ggdb -g -lm
all: 1 2 3 4 

1: 1st.cpp
	$(CC) $< $(CFLAGS) -o run1
2: 2nd.cpp
	$(CC) $< $(CFLAGS) -o run2 
3: 3rd.cpp
	$(CC) $< $(CFLAGS)  -o run3
4: 4th.cpp
	$(CC) $< $(CFLAGS)  -o run4
5: 5th.cpp
	$(CC) $< $(CFLAGS)  -o run5
clean:
	rm run*

