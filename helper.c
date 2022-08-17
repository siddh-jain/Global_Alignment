#define _XOPEN_SOURCE

#include <sys/time.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)


void tick(struct timeval *t)
{
    gettimeofday(t, NULL);
}

double tock(struct timeval *t)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return(double) (now.tv_sec - t->tv_sec) + 
    ((double)(now.tv_usec - t->tv_usec)/1000000.);
}

void RandomVector(int n, float *A)
{
    for(int i=0; i < n; ++i) {
        A[i] = (float) rand()/RAND_MAX;
    }
}

char* readFasta(char *filename)
{
    gzFile fp;
	kseq_t *seq;
	int l;
	fp = gzopen(filename, "r");
	seq = kseq_init(fp);
	while ((l = kseq_read(seq)) >= 0) {
		// printf("name: %s\n", seq->name.s);
		// if (seq->comment.l) printf("comment: %s\n", seq->comment.s);
		// printf("seq: %s\n", seq->seq.s);
		// if (seq->qual.l) printf("qual: %s\n", seq->qual.s);
        return seq->seq.s;
	}
	// printf("return value: %d\n", l);
	kseq_destroy(seq);
	gzclose(fp);
}