# indicate how the object files are to be created
CC         := gcc 
CFLAGS     := -g -O3 -fopenmp
# CC		   := icc
# CFLAGS     := -g -O3 -qopenmp -axCORE-AVX2  

driver.o : driver.c
	$(CC) $(CFLAGS) -c driver.c

all:kseq.h helper.h helper.c driver.c align.h align.c
		$(CC) $(CFLAGS) helper.c driver.c align.c -o align1 -lz -lm

clean:
	rm *.o 
