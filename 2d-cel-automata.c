#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


/*
 * Basic automata structure
 * # ::= alive
 *   ::= dead
 *
 * string of cells: ## ### #
 *                  len = 8
 *                  # alive = 6
 *                  # dead = 2
 */

// create the automata
/*
char* CreateAutomata( int length ) 
{
    char* automata = malloc(length);
    return automata;
}*/

const int rule[8][4] = {
    {0, 0, 0, 0}, //0
    {0, 0, 1, 1}, //1
    {0, 1, 0, 1}, //2
    {0, 1, 1, 1}, //3
    {1, 0, 0, 0}, //4
    {1, 0, 1, 1}, //5
    {1, 1, 0, 1}, //6
    {1, 1, 1, 0}  //7
};

int randomFillAutomata(int *automata, int automataSize)
{
    time_t t;
    srand((unsigned) time(&t));
    for ( int i = 0 ; i < automataSize ; i++)
    {
        automata[i] = rand() % 2;
    }

    return 0;
}
int printAutomata( int* automata, int automataSize)
{
    // print current automata state
    for( int i = 0 ; i < automataSize ; i++)
    {
        if (automata[i] == 1)
        {
            printf("%c", 35);
        }
        else
            printf("%c", 95);
    }
    printf("\n");
    return 0;
}

int checkCells( int *automata, int automataSize)
{
    for( int i = 1 ; i < automataSize - 1 ; i++ )
    {
        printf("%d%d%d\n", automata[i-1],automata[i],automata[i+1]);
        printf("%d\n", automata[i-1]*4 + automata[i]*2 + automata[i+1]*1);
    }
}

/*
 * Returns index of the rule being looked at
 *  - Automata is the automata
 *  - automataSize is the number of cells in the automata
 *  - cellNo is the index of the automata being looked at
 */
int evolveCell( int *automata, int automataSize, int cellNo)
{
    int firstBit, secondBit, thirdBit, ruleNo;
    /*
        if (cellNo == 0)
        {
            firstBit = 0;
        }
        else
        {
            firstBit = automata[cellNo-1];
        }


        if (cellNo == automataSize - 1)
            thirdBit = 0;
        else
            thirdBit = automata[cellNo+1];
*/
        firstBit = cellNo == 0 ? 0 : automata[cellNo - 1];
        secondBit = automata[cellNo];
        thirdBit = cellNo == automataSize ? 0 : automata[cellNo + 1];

        ruleNo = firstBit * 4 + secondBit * 2 + thirdBit;
        printf("In [%d] used rule: %d\n",cellNo, ruleNo);
        return rule[ruleNo][3];
        
}


int* evolveAutomata( int *automata, int *auxAutomata, int automataSize )
{
    for( int i = 0 ; i < automataSize ; i++ )
    {
        //auxAutomata[i] = evolveCell(automata, automataSize, i);
        evolveCell(automata, automataSize, i);
    }
    return auxAutomata;
}

int main (int argc, char* argv[])
{
    
    int automataSize = 5;

    if (argc < 2) automataSize = 5;
    else automataSize = atoi(argv[1]);

    int *automata = (int*) calloc(automataSize, sizeof(int));

    int *auxAutomata = (int*) calloc(automataSize, sizeof(int));

    automata[0] = 1;
    automata[1] = 1;
    automata[2] = 0;
    automata[3] = 1;
    automata[4] = 0;
    
    //randomFillAutomata( automata, automataSize );
    
    while(1)
    {
    auxAutomata = automata;
    printAutomata( automata, automataSize );
    automata = evolveAutomata(automata, auxAutomata, automataSize);
    //evolveAutomata(automata, auxAutomata, automataSize);

    //for ( int i = 0 ; i < automataSize ; i++)
    //    printf("%d",checkRule(automata, automataSize, i));
    //printf("\n");
    usleep(1000000);
    }

    //printf("%d\n", checkRule( automata, automataSize, automataSize - 1));
    

    return 0;
}
