
/***************************************************************************
 *   Copyright (C) 2010 by BSkyB
 *   Richard Parsons
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/* N.B. */
/* this program is supplied WITHOUT any warranty whatsoever		  */

/*==========================================================================

This program is used for the mass changing of process priorities by name
The syntax is as follows
	./bumber [cfgfile]

The config file uses the following syntax
#this is a comment
process_name,POLICY,priority

Default is RR , but valid policies are
  RR, FIFO and OTHER

priority is a value from 0..99

e.g.

#Telnet priority
telnetd,RR,37

=============================================================================*/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sched.h>
#include "bumper.h"

int main ( int argc, char *argv[] )
{

	if ( argc != 2 )
	{
		printf ( "Error: Usage is %s [config file]\n",argv[0] );
		return EXIT_FAILURE;
	}
	processList = init_application();
	if ( readInputFile ( argv[1] ) < 0 )
	{
		printf ( "Error: Could not open %s\n",argv[1] );
		return EXIT_FAILURE;
	}
	getProcessID ( processList );
	destory_application(processList);
	return EXIT_SUCCESS;
}

void *init_application ( void )
{
  return NULL;
}

void destory_application(struct params *head)
{
    struct params *next;

    if (head == NULL)
      return;

   next = head;

   while (next != NULL)
     {
        void *nptr = next->next;
        free(next->process);
        free(next);
        next = nptr;
     }
}

int readInputFile ( char *inFile )
{
	FILE *fp;
	int rc = -1;
	char inLine[101];

	if ( ( fp = fopen ( inFile, "r" ) ) == NULL )
		return rc;

	while ( fgets ( inLine, 100, fp ) !=NULL )
	{
		if ( inLine[0] == '#' )
			continue;

		processList = addEntry ( inLine,processList );
	}
	fclose ( fp );
	return 1;
}


void *addEntry ( char *szParameters,struct params *head )
{
	struct params *entry;
	struct params *lastPtr=head;
	void *retPtr=head;
	char process[512];
	char policy[512];
	char prio[512];
	if ( strlen ( szParameters ) > 511 )  // small saniy check..
		return head;
	if ( strlen ( szParameters ) < 5 )  // small saniy check..
		return head;

	int rc = sscanf ( szParameters,"%[^','],%[^','],%[^',']",process,policy,prio );
	if ( rc == 3 )
	{
		int pVal = atoi(prio);
		if ( ( pVal < 0 ) || ( pVal > 100 ) )
		{
			printf ( "Error : Process %s Priority %i OUT OF BOUNDS of 0..99\n",process,pVal );
			return head;
		}
		entry = malloc ( sizeof ( struct params ) );
		entry->next=head;
		entry->process = malloc ( strlen ( process ) +1 );
		strcpy ( entry->process,process );
		entry->prio = pVal;
		entry->policy = SCHED_RR;
		entry->processCount=0;

		if ( !strcasecmp ( policy,"RR" ) )
		{
			entry->policy = SCHED_RR;
		}
		else if ( !strcasecmp ( policy,"OTHER" ) )
		{
			entry->policy = SCHED_OTHER;
		}
		else if ( !strcasecmp ( policy,"FIFO" ) )
		{
			entry->policy = SCHED_FIFO;
		}
		printf ( "Process %s [Priority %i] [Policy %s (%i)]\n",entry->process,entry->prio,policy,entry->policy );
	}
	else
	{
		return head;
	}
	return entry;
}


int checkProcessName ( struct params *head, char *process, int *prio, int *policy)
{
	int rc = -1;
	struct params *itr = head;
	int length = -1;
	
	for ( itr=head;itr != NULL;itr=itr->next )
	{
		length = strlen(itr->process);
		if ( strncmp ( process,itr->process,length ) == 0 )
		{
			*prio = itr->prio;
			*policy = itr->policy;
			itr->processCount++;
			rc = 1;
			break;
		}
	}
	return rc;
}


int findChar ( char *inString,char character )
{
	int a;

	for ( a=0;a<strlen ( inString );a++ )
	{
		if ( inString[a] == character )
			return a;
	}
	return -1;
}


int readStat ( char *exe, char *target_name )
{
	FILE *fp;
	int rc = -1;
	char inLine[512];



	if ( ( fp = fopen ( exe, "r" ) ) == NULL )
	{
		printf ( "Failed to open %s\n",exe );
		return rc;
	}

	char *retChar = fgets ( inLine, 100, fp );
	if ( retChar == NULL )
	{
		close ( fp );
		return rc;
	}

	int start = findChar ( inLine,'(' );
	int end = findChar ( inLine,')' );

	if ( ( start > 0 ) && ( end >0 ) )
	{
		memset ( target_name,0, ( end-start ) +1 );
		memcpy ( target_name,inLine+start+1, ( end-start )-1 );
		rc = 1;
	}

	fclose ( fp );
	return rc;
}


unsigned int getProcessID ( struct params *head )
{
	DIR *dir_p;
	struct dirent *dir_entry_p;
	DIR *dir_t;
	struct dirent *dir_entry_t;
	char dir_name[512]; // Horrible.. but will do
	char target_name[512];  // Horrible.. but will do
	int target_result;
	char exe_link[512];  // yuk
	int errorcount;
	int result;
	int prio;
	int policy;

	errorcount=0;
	result=0;
	dir_p = opendir ( "/proc/" );
	while ( NULL != ( dir_entry_p = readdir ( dir_p ) ) )
	{
		if ( strspn ( dir_entry_p->d_name, "0123456789" ) == strlen ( dir_entry_p->d_name ) )
		{
			strcpy ( dir_name, "/proc/" );
			strcat ( dir_name, dir_entry_p->d_name );
			strcat ( dir_name, "/task/" );
			dir_t = opendir ( dir_name );
			if (NULL == dir_t)
			{
			        continue;
			}
			/* a process may contain several threads, who details are held in the /proc/<pid>/task directory */
			while ( NULL != ( dir_entry_t = readdir ( dir_t ) ) )
			{
				if ( strspn ( dir_entry_t->d_name, "0123456789" ) == strlen ( dir_entry_t->d_name ) )
				{
					strcpy ( dir_name, "/proc/" );
					strcat ( dir_name, dir_entry_p->d_name );
					strcat ( dir_name, "/task/" );
					strcat ( dir_name, dir_entry_t->d_name );
					strcat ( dir_name, "/" );
					exe_link[0] = 0;
					strcat ( exe_link, dir_name );
					strcat ( exe_link, "stat" );
					target_result = readStat ( exe_link, target_name );
					if ( target_result > 0 )
					{
						//printf ( "Checking for %s\n",target_name );

						if ( checkProcessName ( head,target_name,&prio,&policy) > 0 )
						{
							struct sched_param sp;
							// calc pid of process
							result = atoi ( dir_entry_t->d_name );
							/* thread not been set before, so set priority and policy as per config file */
							sp.sched_priority = prio;

							if ( sched_setscheduler ( result, policy, &sp ) < 0 )
							{
								printf ( "Failed to set %s (%i) [Policy %i] [Priority %i]\n", target_name, result,policy,prio );
							}
							else
								printf ( "Priority set %s (%i)\n", target_name, result );
						}
					}
				}
			}
		}
	}
	closedir ( dir_p );
	return result;
}
