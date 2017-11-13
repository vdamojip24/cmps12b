# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <inttypes.h>
# include <stdint.h>
# include <stdbool.h>
# include "stack.h"
# include "string.h"
# include "huffman.h" 
# include <ctype.h>
# include <getopt.h>

# define MAGIC 0xdeadd00d 

	/* This file decodes the file that has "encoded data".
 	* The format file the file is:
 	*	MAGIC = 0xDEADD00D
 	*	original size (8 bytes)
 	*	tree size (2 bytes)
 	*	Nodes: in format with a combination of Is and Ls
 	*	Encoded symbols
 	*/
uint8_t VERBOSE = 0;

//checks bit, operates on it, and returns
int checkBit (char c, int n)
{
	return (c & (1 << n));
}

int main(int argc, char *argv[])
{
    char *sFile;//character pointer that 
    FILE* ifd = NULL;//input file variable
    FILE* ofd = stdout;//output file variable that writes to stdout if not specified
    unsigned int magic;//magic number from the encoded file
    int readSize;//variable to store the amount of bites we read
    uint64_t dataSize;//size of the data 
    uint16_t treeSize;//size of the tree
    uint32_t decodedSize = 0;// size of the decoded file
    treeNode *currentNode;//treeNode pointer of the current node 
    char symbol, readSymbol;//characters of the symbol and the symbol that we read
    uint8_t *savedTree;//pointer to the savedTree
    treeNode *rootNode;//the root node of the entire tree
    bool inputFile = false;//variable to see if there is an input file
    int loopC;//loop count for the while loop 
    char opt;//character for getopt
	
    //getopt method that allows you to use flags when running program
	while ((opt = getopt(argc, argv, "i:o:v")) != -1)
	{
		switch(opt)//switch statement for possible flags
		{
			case 'i':
			{
				inputFile = true;//sets inputFile to true because there is an input file
				ifd = fopen(optarg, "r+b");//opens the file
				sFile = optarg;//sets whatever is inputted to sFile
				if(ifd == NULL)//error checking if the file cannot be open
			    {
					printf("Unable to open input file %s\n", optarg);
					return -1;
			    }
				break;
			}
			case 'o': 
			{
				ofd = fopen(optarg, "w");//opens the file into the output file
				if(ofd == NULL)//error checking if the file cannot open to the output file
			    {
					printf("Unable to open output file %s\n", optarg);
					return -1;
			    }
				break; 
			}
			case 'v': 
			{
				VERBOSE = 1;//sets the boolean to true so that all the verbose stats will be printed
				break; 
			}
		}
	}

	//error checking if there is no input file
	if(!inputFile)
	{
		printf("Error! Input file required.\n");
		exit(4);
	}

    readSize = fread(&magic, 1, sizeof(magic), ifd);//reads the magic number    
    if(readSize != sizeof(magic))//error checking if unable to read 
    {
		printf("Unable to read magic from %s size %d\n", sFile, readSize);
		return -1;
    }
    
    readSize = fread(&dataSize, 1, sizeof(dataSize), ifd);//reads the data size
    if(readSize != sizeof(dataSize))//error checking if unable to read 
    {
		printf("Unable to read data size from %s size %d\n", sFile, readSize);
		return -1;
    }
    
    readSize = fread(&treeSize, 1, sizeof(treeSize), ifd);//reads the tree size
    if(readSize != sizeof(treeSize))//error checking if unable to read
    {
		printf("Unable to read data size from %s size %d\n", sFile, readSize);
		return -1;
    }
    
    //Load the Symbols for Huffman Tree in savedTree
	savedTree = malloc(sizeof(uint8_t) * treeSize);//allocates memory for the tree created
	fread(savedTree, 1, treeSize, ifd);
	//create the huffman tree
	rootNode = loadTree(savedTree, treeSize);//the rootnode is created as the first node of the tree after loading the tree
    currentNode = rootNode;//sets the currentNode to the rootNode since there is now only one node left
    readSize = 0;//resets the readSize to 0 to start from beginning

    while (1) 
    {
    	
		readSize = fread(&readSymbol, 1, sizeof(readSymbol), ifd);//reads the readSymbol one character at a time
    	if (readSize < 1)//checks to see when the readSize becomes less than 1 and if wer reache the end of the file we break
    	{//deleted semicolon
	    	if (feof(ifd))
	    	{
	    		break;
	    	}
	    	else//error checking again 
	    	{
	    		printf("Error! Processed %u bytes, Should have Processed %u bytes", (unsigned int)decodedSize, (unsigned int)dataSize);
		    	fclose(ifd);
		    	fclose(ofd);
		    	return -1;
	    	}
    	}

		loopC = 0;//loops through the symbol
		while (loopC <= 7) 
    	{

			
			if (checkBit(readSymbol,loopC) == 0)//if we are at a 0, then move left
			{
				currentNode = currentNode->left;
			}
			else//if we are not a 0, then wer are at a 1, and move right
			{
				currentNode = currentNode->right;
			}
		
			if (currentNode->leaf)//if we are at a leaf, then get the symbol of that leaf node
			{
				symbol = currentNode->symbol;//gets symbol of the current node
				if (decodedSize < dataSize) 
				{ 
					fputc(symbol,ofd);//if we come across a leaf, then write the data to output file 
					decodedSize++;
				}
	    		currentNode = rootNode;//once we come across a leaf, start again from root 
			}
			loopC++;//increments loop counter
		}

	}

    if (VERBOSE)//method that prints out the verbose statistics
    {
    	printf("decodedSize: %u bits & treeSize: %d\n", decodedSize*8, treeSize);
    }

    free(savedTree);//frees up memory 
    savedTree = NULL;//sets pointer to NULL for good coding practice
    delTree(rootNode);//deletes the tree and frees up memory
    fclose(ifd);//closes the input file
    fclose(ofd);//closes the output file
    return 0;
}
