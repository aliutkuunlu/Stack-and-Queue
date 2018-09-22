#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void Read_File(char* s, char** matrix);
int File_Line_Count(char* s);
void push (char x, int *top, char array[]);
void pop (int *top);
bool isStackEmpty(int *top);
bool isStackFull(int *top, int maxSize);
void showStack(int *top, char array[], FILE* output);
void enQueue(char x, int *pRear, int *pFront, char array[], int size);
void deQueue(int *pRear, int *pFront, int size);
bool isQueueEmpty(int *pFront);
bool isQueueFull(int *pRear, int *pFront, int maxSize);
void split(char** matrix,char** result, int lineCount);

typedef struct {
        int qSize;
        int sSize;
        int rear;
        int front;
        int top;
        int historyTop;
        char* queue;
        char* stack;
        char* history;

    }Item;

int main(int argc, char* argv[])
    {
        int lineCount1 = File_Line_Count(argv[1]);
        int lineCount2 = File_Line_Count(argv[2]);
        char** input1;
        input1 = (char**)malloc(lineCount1* sizeof(char*));
        char** input2;
        input2 = (char**)malloc(lineCount2* sizeof(char*));
        int i,j,k,l,item,command;
        int sizes = 1;
        char element;

        for(i = 0; i < lineCount1; i++)
            {
                input1[i] = (char *)malloc(5* sizeof(char));
            }
        for(j = 0; j < lineCount2; j++)
            {
                input2[j] = (char *)malloc(7* sizeof(char));
            }
        Read_File(argv[1], input1);
        Read_File(argv[2], input2);
        int itemSize = atoi(input1[0]);
        int commandSize = atoi(input2[0]);
        Item* clientsServer;
        clientsServer = (Item*)malloc(itemSize* sizeof(Item));

        char** splitInput1;
        splitInput1 = (char**)malloc(2*lineCount1* sizeof(char*));
        for(k = 0; k < 2*lineCount1; k++)
            {
                splitInput1[k] = (char *)malloc(5* sizeof(char));
            }
        char** splitInput2;
        splitInput2 = (char**)malloc(3*lineCount2* sizeof(char*));
        for(l = 0; l < 3*lineCount2; l++)
            {
                splitInput2[l] = (char *)malloc(7* sizeof(char));
            }
        split(input2,splitInput2,lineCount2);
        split(input1,splitInput1,lineCount1);
        /* this for loop initialize the items*/
        for (item=0; item<itemSize; item++)
            {
                clientsServer[item].front = -1;
                clientsServer[item].rear = -1;
                clientsServer[item].top = -1;
                clientsServer[item].historyTop = -1;
                clientsServer[item].qSize = atoi(splitInput1[sizes]);
                clientsServer[item].sSize = atoi(splitInput1[sizes + 1]);
                clientsServer[item].queue = (char*)malloc(clientsServer[item].qSize* sizeof(char));
                clientsServer[item].stack = (char*)malloc(clientsServer[item].sSize* sizeof(char));
                clientsServer[item].history = (char*)malloc(commandSize* sizeof(char));
                sizes += 2;
            }

        /*this for loop read the commands*/
        for (command = 1; command <= commandSize*3 - 2 ; command +=3)
            {
                if( splitInput2[command][0] == 'A')
                    {
                        if (isQueueFull(&clientsServer[atoi(splitInput2[command+1]) -1].rear, &clientsServer[atoi(splitInput2[command+1]) -1].front, clientsServer[atoi(splitInput2[command+1]) -1].qSize))
                            {
                                push('1', &clientsServer[atoi(splitInput2[command+1]) -1].historyTop, clientsServer[atoi(splitInput2[command+1]) -1].history);
                            }
                        else
                            {
                                enQueue(splitInput2[command+2][0], &clientsServer[atoi(splitInput2[command+1]) -1].rear, &clientsServer[atoi(splitInput2[command+1]) -1].front, clientsServer[atoi(splitInput2[command+1]) -1].queue, clientsServer[atoi(splitInput2[command+1]) -1].qSize );
                            }
                    }
                else if ( splitInput2[command][0] == 'I')
                    {
                        if(isStackFull(&clientsServer[atoi(splitInput2[command+1]) -1].top, clientsServer[atoi(splitInput2[command+1]) -1].sSize))
                            {
                                push('2', &clientsServer[atoi(splitInput2[command+1]) -1].historyTop, clientsServer[atoi(splitInput2[command+1]) -1].history);
                            }
                        else
                            {
                                push(splitInput2[command+2][0], &clientsServer[atoi(splitInput2[command+1]) -1].top, clientsServer[atoi(splitInput2[command+1]) -1].stack );
                            }
                    }
                else if ( splitInput2[command][0] == 'S')
                    {
                        if ((isStackEmpty(&clientsServer[atoi(splitInput2[command+1]) -1].top)) && isQueueEmpty(&clientsServer[atoi(splitInput2[command+1]) -1].front))
                            {
                                push('3', &clientsServer[atoi(splitInput2[command+1]) -1].historyTop, clientsServer[atoi(splitInput2[command+1]) -1].history);
                            }
                        else if (isStackEmpty(&clientsServer[atoi(splitInput2[command+1])  -1].top))
                            {
                                element = clientsServer[atoi(splitInput2[command+1])  -1].queue[clientsServer[atoi(splitInput2[command+1]) -1].front];
                                if(isQueueFull(&clientsServer[itemSize - 1].rear, &clientsServer[itemSize - 1].front, clientsServer[itemSize - 1].qSize))
                                    {
                                        push('1', &clientsServer[itemSize - 1].historyTop, clientsServer[itemSize - 1].history);
                                    }
                                else
                                    {
                                        enQueue(element, &clientsServer[itemSize - 1].rear, &clientsServer[itemSize - 1].front, clientsServer[itemSize - 1].queue, clientsServer[itemSize - 1].qSize);
                                    }
                                push(element, &clientsServer[atoi(splitInput2[command+1]) -1].historyTop, clientsServer[atoi(splitInput2[command+1]) -1].history);
                                deQueue(&clientsServer[atoi(splitInput2[command+1])  -1].rear, &clientsServer[atoi(splitInput2[command+1]) -1].front, clientsServer[atoi(splitInput2[command+1])  -1].qSize);
                            }
                        else
                            {
                                element = clientsServer[atoi(splitInput2[command+1]) -1].stack[clientsServer[atoi(splitInput2[command+1]) -1].top];
                                if(isQueueFull(&clientsServer[itemSize - 1].rear, &clientsServer[itemSize - 1].front, clientsServer[itemSize - 1].qSize))
                                    {
                                        push('1', &clientsServer[itemSize - 1].historyTop, clientsServer[itemSize - 1].history);
                                    }
                                else
                                    {
                                        enQueue(element, &clientsServer[itemSize - 1].rear, &clientsServer[itemSize - 1].front, clientsServer[itemSize - 1].queue, clientsServer[itemSize - 1].qSize);
                                    }
                                push(element, &clientsServer[atoi(splitInput2[command+1]) -1].historyTop, clientsServer[atoi(splitInput2[command+1]) -1].history);
                                pop(&clientsServer[atoi(splitInput2[command+1]) -1].top);
                            }
                    }
                else if ( splitInput2[command][0] == 'O')
                    {
                        if(isStackEmpty(&clientsServer[itemSize - 1].top) && isQueueEmpty(&clientsServer[itemSize - 1].front))
                            {
                                push('3', &clientsServer[itemSize - 1].historyTop, clientsServer[itemSize - 1].history );
                            }
                        else if (isStackEmpty(&clientsServer[itemSize - 1].top))
                            {
                                element = clientsServer[itemSize - 1].queue[clientsServer[itemSize - 1].front];
                                push(element, &clientsServer[itemSize - 1].historyTop, clientsServer[itemSize - 1].history );
                                deQueue(&clientsServer[itemSize - 1].rear, &clientsServer[itemSize - 1].front, clientsServer[itemSize - 1].qSize);
                            }
                        else
                            {
                                element = clientsServer[itemSize - 1].stack[clientsServer[itemSize - 1].top];
                                push(element, &clientsServer[itemSize - 1].historyTop, clientsServer[itemSize - 1].history );
                                pop(&clientsServer[itemSize - 1].top);
                            }
                    }
                else
                    {
                        printf("Wtong command format!!\n");
                    }
            }
        FILE* output = fopen(argv[3], "w");
        if (output == NULL)
            {
                printf("Error opening file!\n");
                exit(1);
            }

        int r;
        for (r= 0; r<itemSize; r++)
            {
                showStack(&clientsServer[r].historyTop, clientsServer[r].history, output);
            }
        fclose(output);
        free(input1);
        free(input2);
        free(clientsServer);
        free(splitInput1);
        free(splitInput2);
        return 0;

    }

void showStack(int *top, char array[], FILE* output)
    {
        int i;
        for (i = 0; i <= (*top) ; i++)
            {
                if(i== (*top))
                {
                    printf("%c", array[i]);
                    fprintf(output,"%c",array[i]);
                }
                else
                {
                    printf("%c ", array[i]);
                    fprintf(output,"%c ",array[i]);
                }
            }
        printf("\n");
        fprintf(output, "\n");
    }
void enQueue(char x, int *pRear, int *pFront, char array[], int size)
    {
        if(*pFront == -1)
            {
                *pFront = 0;
            }
        (*pRear) = ((*pRear)+1) % size;
        array[*pRear] = x;
    }

void deQueue(int *pRear, int *pFront, int size)
    {
        if (*pFront == *pRear)
            {
                *pFront = -1;
                *pRear = -1;
            }
        else
            {
                *pFront = ((*pFront) + 1) % size;
            }
    }
bool isQueueEmpty(int *pFront)
    {
        if(*pFront == -1)
            return true;
        else
            return false;
    }

bool isQueueFull(int *pRear, int *pFront, int maxSize)
    {
        if ((*pRear == (*pFront)-1) || ((*pFront== 0) && (*pRear == maxSize -1)))
            {
                return  true;
            }
        else
            return  false;
    }

void push (char x, int *top, char array[])
    {
        array[++(*top)] = x;
    }
void pop (int *top)
    {
        (*top)--;
    }

bool isStackEmpty(int *top)
    {
        if(*top == -1)
            return  true;
        else
            return  false;
    }
bool isStackFull(int *top, int maxSize)
    {
        if(*top == maxSize-1)
            return true;
        else
            return false;
    }



void Read_File(char* s, char** matrix)
    {
        int i = 0;
        FILE* input_file;
        char buff[1000];
        input_file = fopen(s, "r");
        if(!input_file){
                return;
            }
        while(fgets(buff, 1000, input_file) != NULL){
                strcpy(matrix[i], buff);
                i = i+1;
            }
        fclose(input_file);
    }

int File_Line_Count(char* s)
    {
        int count = 0;
        FILE* input_file;
        char buff[1000];
        input_file = fopen(s, "r");
        if(!input_file){
                return -1;
            }
        while(fgets(buff, 1000, input_file) != NULL){
                count++;
            }
        fclose(input_file);
        return count;
    }
void split(char** matrix,char** result, int lineCount)
    {
        int coulmn = 0;
        int j=0;
        int i;
        for (i = 0; i <lineCount ; ++i)
            {
                char *token = strtok(matrix[i], " \r\n");

                // Keep printing tokens while one of the
                // delimiters present in str[].

                while (token != NULL)
                    {
                        if(token != "")
                            strcpy(result[j],token);
                        j++;
                        coulmn++;
                        token = strtok(NULL, " \r\n");
                    }
            }

        // Returns first token


    }