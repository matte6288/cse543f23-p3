struct element_type {
	int type;
	void *data;
	struct element_type *next;
	struct element_type *prev;
};

typedef struct element_type element;


typedef struct {
	element *head;
} list;


/**********************************************************************

    Function    : init
    Description : initialize list
    Inputs      : list - list object
    Outputs     : 0 if successfully completed, -1 if failure

***********************************************************************/
extern int init( list *l );

/**********************************************************************

    Function    : insert
    Description : Insert element in list after (optional) element
    Inputs      : list - list object
                  new - new element to insert
                  after - optional element to insert after (if null, place at head)
    Outputs     : 0 if successfully completed, -1 if failure

***********************************************************************/
extern int insert( list *l, element *new, element *after );

/**********************************************************************

    Function    : get
    Description : get element that matches 
    Inputs      : list - list object
                  name - name of object to retrieve
                  cmp - comparison function 
    Outputs     : 0 if successfully completed, -1 if failure

***********************************************************************/
extern element *get( list *l, void *obj, int(*cmp)(element *e, void *obj));


/**********************************************************************

    Function    : pos
    Description : retrieve position in list of element
    Inputs      : list - list object
                  obj - object to match from elements in list
                  cmp - function for comparison
    Outputs     : 0 if successfully completed, -1 if failure

***********************************************************************/
extern int pos( list *l, void *obj, int(*cmp)(element *e, void *obj));