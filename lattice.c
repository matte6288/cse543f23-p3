#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/stat.h>

/* Project Include Files */
#include "utils.h"
#include "linked-list.h"
#include "lattice.h"
#include "monitor.h"

/* Globals */
list lattice;
list label_mapping;
list trans_mapping;


/**********************************************************************

    Function    : addLattice
    Description : Add levels - add from low to high levels
    Inputs      : fh - output file pointer
                  low - name of lower level
                  high - name of higher level
    Outputs     : 0 if successfully completed, -1 if failure

***********************************************************************/
int addLattice( FILE *fh, char *low, char *high ){

    /* Check if low level already exists in lattice */	
	element *lowElt = get( &lattice, low, &matchLevelName );
	/* if no low already, must make one */
	if ( !lowElt ) {
		/* make new level for low */
		level *l = (level *) malloc(sizeof(level));
		l->len = strlen( low );
		l->name = (char *) malloc( l->len );
		strncpy( l->name, low, l->len );

		/* make new element for low in lattice */
		lowElt = (element *) malloc(sizeof(element));
		lowElt->type = E_LEVEL;
		lowElt->data = (void *)l;
		lowElt->next = NULL;

		/* add to lattice */
		insert( &lattice, lowElt, NULL );
		fprintf( fh, "AddLattice[p%d]: level: %s \n", cmdCt, low );
	}

    /* Check if high level already exists in lattice */	
	element *highElt = get( &lattice, high, &matchLevelName );
	/* if no high already, must make one */
	if ( !highElt ) {
        /* make new level for high */
        level *l = (level *) malloc(sizeof(level));
        l->len = strlen( high );
        l->name = (char *) malloc( l->len );
        strncpy( l->name, high, l->len );

        /* make new element for high in lattice */
        highElt = (element *) malloc(sizeof(element));
        highElt->type = E_LEVEL;
        highElt->data = (void *)l;
        highElt->next = NULL;

        /* add to lattice */
        insert( &lattice, highElt, lowElt );
        fprintf( fh, "AddLattice[p%d]: level: %s > %s \n", cmdCt, high, low );
    }

    return 0;
}



/**********************************************************************

    Function    : addLabelPolicy
    Description : Add mapping from name to level
    Inputs      : fh - output file pointer
                  name - name (prefix) of objects at level
                  level - name of level
    Outputs     : 0 if successfully completed, -1 if failure

***********************************************************************/
int addLabelPolicy( FILE *fh, char *name, char *level ){

    element *new;

	/* hint - find lattice level for map */
	/* YOUR CODE GOES HERE */

    /* hint - make mapping node */
	/* YOUR CODE GOES HERE */

	/* hint - create element for label_mapping */
	/* YOUR CODE GOES HERE */

    /* add the above element to label mappings */ 
	insert( &label_mapping, new, NULL );	
	fprintf( fh, "AddLabelPolicy[p%d]: Add mapping for name %s to level %s\n", cmdCt, name, level );	
	return 0;
}



/**********************************************************************

    Function    : addTransPolicy
    Description : Add mapping from name to level
    Inputs      : fh - output file pointer
                  subj_level - level of subject of op
                  obj_level - level of object of op
                  new_level - resultant level of subj or obj (op-dependent)
                  op - operation (rwx)
                  ttype - transition type (process or file)
    Outputs     : 0 if successfully completed, -1 if failure

***********************************************************************/
int addTransPolicy( FILE *fh, char *subj_level, char *obj_level, char* new_level, int op, int ttype ){

    element *new;

	/* get subject, object, new levels */
	/* YOUR CODE GOES HERE */

	/* check if any level is missing */
	if ( /* Condition when any level is not found */ /* YOUR CODE GOES HERE */ ) {
		fprintf( fh, "ERROR AddTransPolicy[p%d]: One/More levels not found for mapping.\n", cmdCt);
		return -1;
	}

	/* make trans node */
	/* YOUR CODE GOES HERE */

	/* create element for trans mapping */
	/* YOUR CODE GOES HERE */	

    /* add to trans mapping */
	insert( &trans_mapping, new, NULL );
	fprintf( fh, "AddTransPolicy[p%d]: on %s, if subject level is %s and object level is %s, \n\t\t\t then transition %s to level %s\n", cmdCt, 
                    (( op == O_EXEC ) ? "EXEC" : (( op == O_READ ) ? "READ" : "WRITE" )), subj_level, obj_level, (( ttype == T_PROC ) ? "PROCESS" : "FILE"), new_level );

	return 0;
}



/**********************************************************************

    Function    : Match Functions
    Description : Find if node name matches supplied object
    Inputs      : element - element to check 
                  obj - object to match on
    Outputs     : 0 if successfully completed, -1 if failure

***********************************************************************/

//Matches using Level Name
int matchLevelName( element *e, void *obj ){

	if ( strncmp( (char *)obj, ((level *)(e->data))->name, ((level *)(e->data))->len ) == 0 ) 
		return 1;
	return 0;
}

//Matches using Map Name
int matchMapName( element *e, void *obj ){

    if ( strncmp( (char *)obj, ((map *)(e->data))->name, ((map *)(e->data))->len ) == 0 ) 
		return 1;
	return 0;
}

//Matches using Level Object
int matchLevel( element *e, void *obj ){

    return( ((level *)(e->data)) == (level *)obj );
}

//Matches using Trans Object
int matchTrans( element *e, void *obj ){

    trans *t1, *t2;
	t1 = (trans *)e->data;
	t2 = (trans *)obj;

	return( (t1->subj == t2->subj) &&
		(t1->obj == t2->obj) &&
		(t1->op == t2->op) );
}