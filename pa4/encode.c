# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <getopt.h>
# include <stdbool.h>
# include <stdint.h>
# include <ctype.h>
# include <inttypes.h>
# include "huffman.h"
# include "code.h"
# include "queue.h"
# define MAXQSIZE 512 /* for queue  */
# define CHARLEN 256
# define DEF1 0
# define DEF2 255
# define PSEUDOEOF 253 /* accounts for end of file  */



void loadHist(uint32_t *hist, char *str);
queue *loadQueue(uint32_t *hist);
void printQ(queue *q);
void buildHT(queue *q);
void printCodes(code *table);
void htToFile(FILE* out, treeNode *t, code *c);
void compress(FILE *fIn, FILE *fOut, treeNode *t, code *c);
uint32_t key = {0xdeadd00d};
bool vMode = false;
int main(int argc, char *argv[])
{
	char inFile[100]; /* -i, input file required*/
	char outFile[100]; /* -o, optional for output file */
	bool putFile = false;
	bool inFileSet = false; /*input file set */

	uint32_t hist[256] = {0};
	code c, symTable[256];
	char opt;
	while ((opt = getopt(argc, argv, "i:o:v")) != -1)
	{
		switch(opt)
		{
			case 'i':
			{
				inFileSet = true;
				strcpy(inFile, optarg);
				break;
			}
			case 'o': 
			{
				putFile = true;
				strcpy(outFile, optarg);
				break;
			}
			case 'v': 
			{
				vMode = true;
				break;
			}
		}
	}
	if (!inFileSet)
	{
		printf("Error! Usage: encode -i inputFilename.txt\n");
		exit(4);
	}
	/* assign occurance values and histogram key to input characters */
	loadHist(hist, inFile);
	/* sort into priority queue, from least or greatest occurance */
	queue *pQ =loadQueue(hist);
	/*printQ(pQ);*/
	/* build huffman tree with characters/values from priority queue */
	buildHT(pQ);
	initCodesTables(symTable, 256);
	c = newCode();
	/*printTree(&pQ->Q[pQ->head], 0);*/
	/* put together code based on  huffman tree (0's for left and 1's for right) */
	buildCode(&pQ->Q[pQ->head], &c, symTable); /* root node:&pQ->Q[pQ->head] */
	/*printCodes(symTable);*/
	/*compress input text*/
	FILE *fIn = fopen(inFile, "r");
	if (fIn == NULL)
	{
		printf("Failed to open file %s", inFile);
		exit(4);
	}
	FILE *fOut;
	if (putFile)
	{
		fOut = fopen(outFile, "wb");

		if (fOut == NULL)
		{
			printf("Failed to open file %s", outFile);
			exit(4);
		}
	}
	else
	{
		fOut = stdout;
	}
	compress(fIn, fOut, &pQ->Q[pQ->head], symTable);
	delQueue(pQ);
	fclose(fIn);
	fclose(fOut);
	/* printf("compresssion complete\n"); */

}

/* assign occurance values and histogram key to input characters */
 void loadHist(uint32_t *hist, char *str)
{
	int c;
	/* open, read, close input file */
	FILE *fp = fopen(str, "r");
	if (fp == NULL)
	{
		printf("Failed to open file %s", str);
		exit(4);
	}
	/* assign symbol(number) to each character and find number of occurances*/
	while(!feof(fp))
	{
		c = fgetc(fp);
		hist[c]++;
	}
	fclose(fp);
	hist[DEF1]++;
	hist[DEF2]++;
	/*hist[PSEUDOEOF]++;*/
}

/* sort into priority queue, from least or greatest occurance */
queue *loadQueue(uint32_t *hist)
{
	queue *nQ = newQueue(1024);
	treeNode * nn;
	for (int i = 0; i < CHARLEN; ++i)
	{
		if (hist[i] != 0)
		{
			nn = newNode(i,true,hist[i]);
			if (!enqueue(nQ, nn))
			{
				printf("error, failed to insert node %d\n", i);
				exit(4);
			}
			free(nn);
		}
	}
	return nQ;
}
/*used to test code, not called in final main method */
void printQ(queue *q)
{
	for (uint32_t i = q->head; i < q->tail; ++i)
	{
		printf("priority queue: %u symbol= %u, count= %lu\n",i, q->Q[i].symbol,q->Q[i].count);
	}
	printf("-----------------------------------------\n");
}
/* build huffman tree with characters/values from priority queue */
void buildHT(queue *q)
{
	treeNode *left, *right, *jn; /*joint node*/
	while(q->head <= q->tail)
	{
		if (q->head+1 >= q->tail)
		{
			break;
		}
		left = &q->Q[q->head++];
		right = &q->Q[q->head++];
		/*(void) dequeue(q,&left);
		(void) dequeue(q,&right);
		printf("left: %c %lu\n", left.symbol, left.count);
		printf("right: %c %lu\n", right.symbol, right.count);*/
		jn = join(left,right);
		if (!enqueue(q, jn))
		{
			printf("error, failed to join nodes %lu %lu\n", left->count, right->count);
			exit(4);
		}
		free(jn);
		/*q->head +=2;*/
	}

}

void printCodes(code *table)
{
	for (int i = 0; i < 256; ++i)
	{
		if (table[i].l > 0)
		{
			printf("sym %d, bits %u\n", i, table[i].l);
		}
	}
}

/* from huffman tree to output */
void htToFile(FILE *out, treeNode *t, code *c)
{
	uint16_t leafCount=0;
	uint16_t treeSize=0;
	for (int i = 0; i < 256; ++i)
	{
		if (c[i].l > 0)
		{
			leafCount++;
		}
	}
	treeSize= (3*leafCount)-1;
	fwrite(&treeSize,2,1,out);
	if (vMode)
	{
		printf("Tree Size is %u\n",treeSize);
	}
	dumpTree(t, out);
	return;
}



void compress(FILE *in, FILE *out, treeNode *t, code *c)
{
	int ch, bitCount = 0; 
	code *s;
	uint8_t *encoded = (uint8_t *) calloc(1,sizeof(uint8_t));
	uint8_t bitVal = 0;
	uint32_t i;
	fseek(in,0,SEEK_END);
	uint64_t fs = ftell(in);
	uint64_t outFS = 0;
	fseek(in,0,SEEK_SET);
	/*1. magic number*/
	fwrite(&key, 4,1, out);
	/*2. write size of original number*/
	fwrite(&fs,8,1, out);
	if (vMode)
	{
		printf("Input file size is %lu\n",fs);
	}
	/*3. leaf count and huffman tree*/
	htToFile(out, t, c);
	/*4.encoding*/
	bool pEOF = false;
	while(!pEOF)
	{	/*read till end of file*/
		if (!feof(in))
		{
			ch = fgetc(in);
			if (ch == EOF)
			{
				continue;
			}
		}
		else
		{
			break;
			pEOF = true;
		}
		s = &c[ch]; /*code table */
		/* loops though number of bits for the character */
		/*printf("%c ", ch);
		for(uint32_t j = 0; j < s->l; j++)
		{
			bitVal = (s->bits[j>>3] & (0x1<<(j%8))) >> (j%8);
			printf("%d", bitVal);
		}
		printf("\n");
		bitVal = 0;*/
		for (i = 0; i < s->l; ++i)
		{
			if (bitCount == 8)
			{
				for(uint32_t j = 0; j < 8; j++)
				{
					bitVal = (encoded[0] & (0x1<<(j%8))) >> (j%8);
				}
				fprintf(out, "%c", *encoded);
				outFS++;
				*encoded = 0;
				bitCount = 0;
			}
			/*encoded<<=1;
			bitVal = s->bits[i>>3] & (0x1<<(i%8)); */
			bitVal = (s->bits[i>>3] & (0x1<<(i%8))) >> (i%8);

			if (bitVal==0)
			{
				encoded[0]&= ~(0x1<<(bitCount%8));
				for(uint32_t j = 0; j < 8; j++)
				{
					bitVal = (encoded[0] & (0x1<<(j%8))) >> (j%8);
				}
				/*printf("%d", bitVal);*/
			}
			else
			{
				encoded[0]|= (0x1<<(bitCount%8));
			
				for(uint32_t j = 0; j < 8; j++)
				{
					bitVal = (encoded[0] & (0x1<<(j%8))) >> (j%8);
				}
				/*printf("%d", bitVal);*/
			}
			bitCount++;
		}
	}
	if (bitCount>0)
	{
		/*left justify bits */ 
		/*for (int i = 8- bitCount; i > 0; --i)
		{
			encoded<<=1;

		}*/
		fprintf(out, "%c",*encoded);
		outFS++;
	}
	if (vMode)
	{
		printf("Written %lu bytes. Compression:%.2f%%\n",outFS,outFS/(float)fs*100);
	}
	free(encoded);
}





