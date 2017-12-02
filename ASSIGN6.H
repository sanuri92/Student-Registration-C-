#include <stdio.h>


#define LT(a,b) ((a)<(b))
#define GT(a,b) ((a)>(b))
#define EQ(a,b) ((a)==(b))
#define MAXLIST 100

typedef enum{FALSE,TRUE} Boolean;
typedef int Position;
typedef int KeyType;

typedef struct
{
    char Stu_no[15];
    char Name[15];
    char Gender;
    char Grade;
    KeyType key;
}ListEntry;

typedef struct
{
    ListEntry entry[MAXLIST];
    int count;
}List;

void Error(const char *message)
{
    fprintf(stderr,"Error %s\n",message);
    //exit(1);
}

void Warning(const char *message)
{
    fprintf(stderr,"Warning %s\n",message);
}

void CreateList(List *l)
{
    l->count=0;     //"count==0" represent empty state of the list instead of "count==-1"
}

Boolean IsListEmpty(const List *l)
{
    return(l->count==0);
}

Boolean IsListFull(const List *l)
{
    return(l->count==MAXLIST);
}

int ListSize(const List *l)
{
    return(l->count);
}

void InsertLast(ListEntry x,List *l)
{
    if(IsListFull(l))
	Warning("Attempt to insert at the end of a full list");
    else
	l->entry[++l->count-1]=x;
}

void RetrieveList(Position p,ListEntry *x,const List *l)
{
    if(IsListEmpty(l))
	Error("Attempt to retrieve an entry from an empty list");
    else if(p<0||p>=ListSize(l))
	Error("Attempt to retrieve at a position not in the list");
    else
	*x=l->entry[p];
}

void TraverselList(const List *l,void (*visit)(ListEntry,int))
{
	int i;
	for(i=0;i<l->count;i++)
	       (*visit)(l->entry[i],i+1);
}

int RecBinary1(List list,KeyType target,int bottom,int top)
{
    int middle=-1;
    if(bottom<top)
    {
	middle=(top+bottom)/2;
	if(GT(target,list.entry[middle].key))
	    middle=RecBinary1(list,target,middle+1,top);
	else
	    middle=RecBinary1(list,target,bottom,middle);
    }
    else if(bottom==top)
	if(EQ(target,list.entry[top].key))
	    middle=top;
    return middle;
}

void Swap(Position a,Position b,List *list)
{
    ListEntry temp=list->entry[a];
    list->entry[a]=list->entry[b];
    list->entry[b]=temp;
}

Position Partition(List *list,Position low,Position high)
{
    ListEntry pivot;
    Position i,pivotpos;
    Swap(low,(low+high)/2,list);
    pivot=list->entry[low];
    pivotpos=low;
    for(i=low+1;i<=high;i++)
	if(LT(list->entry[i].key,pivot.key))
	    Swap(++pivotpos,i,list);
    Swap(low,pivotpos,list);
    return pivotpos;
}

void RecQuickSort(List *list,Position low,Position high)
{
    Position pivotpos;
    if(low<high)
    {
	pivotpos=Partition(list,low,high);
	RecQuickSort(list,low,pivotpos-1);
	RecQuickSort(list,pivotpos+1,high);
    }
}

void QuickSort(List *list)
{
    RecQuickSort(list,0,list->count-1);
}
