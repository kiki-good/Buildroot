#ifndef _BUMPER_H
#define _BUMPER_H


struct params {
  char *process;
  int  prio;
  int  policy;
  int  processCount;
struct params *next; // single entry linked list
};

unsigned int getProcessID ( struct params *head );
void *addEntry ( char *szParameters,struct params *head );
int checkProcessName ( struct params *head, char *process, int *prio, int *policy );
int readInputFile ( char *inFile );
void *init_application ( void );
void destory_application(struct params *head);

// Globals 
struct params *processList;


#endif
