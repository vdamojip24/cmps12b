# include "bf.h"
# include "hash.h"
# include "ll.h"
# include <stdio.h>
# include <stdlib.h>
# include <getopt.h>
# include <ctype.h>

//statistics used
bool moveToFront = 0;
uint32_t seeks = 0;
uint32_t average = 0;
uint32_t dictionary = 0;
uint32_t translations = 0;
uint32_t text = 0;
uint32_t densities = 0;
uint32_t attemptToFind = 0;


char thoughtCrimeMessage[] = "Dear Comrade, \n You have chosen to use degenerate words that may cause hurt  feelings or cause your comrades to think unpleasant thoughts. This is doubleplus bad. To correct your wrongthink and save community consensus we will be sending you to joycamp  administered by Miniluv.\n\nYour errors :\n"; 

char encouragementMessage[] = "Dear Comrade , \n  Submitting your text helps to preserve feelings and prevent badthink . Some of the words that you used are not goodspeak . The list shows how to turn the oldspeak words into newspeak .\n"; // insert the actual message from the assignment statement.

int validateString(char *s, char *converted)//converts the string to lowercase
{
    uint32_t len = strlen(s);
    for(uint32_t i = 0; i < len; ++i)
    {
        if(isalpha(s[i]))
        {
            converted[i] = tolower(s[i]); 
        }
        else if (isdigit(s[i]))
        {
            converted[i] = s[i];
        }
        else
        {
            return -1;  
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    //default sizes
    uint32_t hashTableSize = 10000;
    uint32_t bfSize = 1048576;
    uint32_t printStats = 0;

    char badSpeakFileName[1024] = "badspeak.txt";
    char newSpeakFileName[1024] = "newspeak.txt";
    char c;
    while ((c = getopt (argc , argv , "smbf:h:")) != -1)//flag specified by the user
    {
        switch(c)
        {
            case 's':
                printStats = 1;
            break;

            case 'm':
                moveToFront = 1;
            break;

            case 'b':
                moveToFront = 0;
            break;

            case 'h':
                hashTableSize = atoi(optarg);
            break;

            case 'f':
                bfSize = atoi(optarg);
            break;

            default:
                fprintf(stderr, "Unknown option: %c\n", c);
        }
    }

    char *speak = argv[optind];//inputted word(s) by the user

    //prints all necessary statistics
    printf("printStats = %u moveToFront = %u hashTableSize = %u bloomFilterSize = %u speak = %s %s\n", 
            (uint32_t)printStats, moveToFront, hashTableSize, bfSize , speak , argv[optind+1]);

    // Creating the Bloom Filters
    uint32_t bFilter1Salt[4] = {1, 2, 3, 4};
    bloomF *bFilter1 = newBF(bfSize, bFilter1Salt);
    
    uint32_t bFilter2Salt[4] = {5,6,7,8};
    bloomF *bFilter2 = newBF(bfSize, bFilter2Salt);

    // Fill the enties in the Bloom Filters.
    
    FILE* badSpeakFile = fopen("badspeak.txt", "r");

    //error checking if there is no badspeak file
    if (badSpeakFile == NULL)
    {
        fprintf(stderr, "Error opening the file %s\n", badSpeakFileName);
        exit(0);
    }

    char badSpeakTxt[1024] = "";

    //uses alternate bloom filters for multiple words
    while (fgets(badSpeakTxt,1024,badSpeakFile) != NULL)
    {
       badSpeakTxt[strlen(badSpeakTxt) - 1] = '\0';

       if (dictionary %2 == 0)//word at that specific index
       {
            setBF(bFilter1, badSpeakTxt);
       }
       else
       {
            setBF(bFilter2, badSpeakTxt);
       }

       dictionary++;
    }

    fclose(badSpeakFile);

    // Creating the hash table
    uint32_t hashTableSalt[4] = {9,10,11,12};
    hashTable *ht = newHT(hashTableSize, hashTableSalt);

    FILE *newSpeakFile = fopen(newSpeakFileName, "r");
    
    //error checking for the good words file to see if it exits
    if (newSpeakFile == NULL)
    {
        fprintf(stderr, "Error opening the file %s\n", badSpeakFileName);
        exit(0);
    }

    char newSpeakTxt[2048] = "";

    while (fgets(newSpeakTxt, 2048, newSpeakFile) != NULL)
    {
        newSpeakTxt[strlen(newSpeakTxt) -1] = '\0';

        char oldKey[1024] = "";
        char newKey[1024] = "";

        sscanf(newSpeakTxt, "%s %s", oldKey, newKey);

        insertHT(ht, oldKey, newKey);
         translations++;
    }

    fclose(newSpeakFile);
    
    bool printThoughtCrimeMessage = false;
    bool printEncouragementMessage = false;
    listNode *matchNode = NULL;

    uint32_t indx = optind;//sets the index to the index of the argument number

    while (argv[indx] != NULL)//makes sure there is an argument
    {
        char speak[1024] = "";
        
        text++;
        if (validateString(argv[indx++], speak) == -1)
        {
            continue;
        }

        if (memBF(bFilter1, speak) || memBF(bFilter2, speak))//checks both bloom filters for the word
        {
            if (!printStats && (printThoughtCrimeMessage == 0))
            {
                fprintf(stdout, "%s\n", thoughtCrimeMessage);
                printThoughtCrimeMessage = 1;
            }

            if (!printStats)
            {
                fprintf(stdout, "%s\n", speak);//just prints out the word 
            }
        }
        else if ( (matchNode = findHT(ht, speak)) != NULL)//if the word is found 
        {
            if ( !printStats && (printEncouragementMessage == 0))
            {
                fprintf(stdout, "%s\n", encouragementMessage);
                printEncouragementMessage = 1;
            }

            if (!printStats)
            {
                fprintf(stdout, "%s -> %s \n", matchNode->oldspeak, matchNode->newspeak);//sets the bad word to the new good word
            }
        }
//        else if(!printStats)
//        {
//            fprintf(stdout, "%s \n","Send user to joy camp.\n");
//        }
    }


    if(printStats)//printing out more stats
    {
        fprintf(stdout, "Seeks %u, Average = %f, Dictionary = %u, Translations = %u, Text = %u, Densities = %f, %f \n",
        seeks,
        (float)seeks/(float)attemptToFind,
        dictionary,
        translations,
        text,
        (float)countBF(bFilter1)/(float)bFilter1->l,
        (float)countBF(bFilter2)/(float)bFilter2->l
        );
    }

    delBF(bFilter1);//freeing up memory
    delBF(bFilter2);
    
    //delHT(ht);
    return 0;
}
