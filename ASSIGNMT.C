#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ASSIGN6.h">



void DisplayData(ListEntry x,int i)
{
    printf("\n Record - %d\n",i);
    printf("%s\t",x.Stu_no);
    printf("%s\t",x.Name);
    printf("%c\t",x.Gender);
    printf("%c\n",x.Grade);
}

	void PrintEntry(ListEntry x){
	printf("%s\t",x.Stu_no);
	printf("%s\t",x.Name);
	printf("%c\t",x.Gender);
	printf("%c\n",x.Grade);
}

	void EnterData(List *l)
	{
		int i=-1;
		ListEntry x;
		char c[2];
	do
	{
	printf("*Enter Student Details of Student %d..\n",++i+1);
	printf("* Enter Student number:");
	scanf("%s",x.Stu_no);
	printf("* Name of the student:");
	scanf("%s",x.Name);
	printf("* Gender Enter(M/F):");
	scanf("%s",&x.Gender);
	printf("* Grade:");
	scanf("%s",&x.Grade);
		x.key=(int)(x.Grade);
		InsertLast(x,l);
	printf("Do you want to add More Student Details ?(Y,N):");
	scanf("%s",c);
    }
    while(!strcmpi("Y",c));
}

void SearchDetails(List *l,char Grade)
{
    KeyType key=(int)(Grade);
    ListEntry x;
    Position matched[MAXLIST],matchcount,pos;
    pos=RecBinary1(*l,key,0,ListSize(l)-1);
    if(pos!=-1)
    {
	matched[0]=pos;
	for(matchcount=1;pos!=-1;matchcount++)
	{
	    pos=RecBinary1(*l,key,matched[matchcount-1]+1,ListSize(l)-1);
	    if(pos!=-1)
		matched[matchcount]=pos;
	}
	printf("Following Record(s) have found\n");
	printf("Student Number\tName\tGender\tGrade\n");
	for(pos=0;pos<matchcount-1;pos++)
	{
	    RetrieveList(matched[pos],&x,l);
	    PrintEntry(x);
	}
    }
    else
	printf("No record Exist\n");
}



int main()
{
    List l;
    char c[2],Grade;
    clrscr();
    CreateList(&l);

    printf("---------------------- Student Details System ------------------\n\n");
    EnterData(&l);
    printf("Please enter Y to View Student Details\n");
    scanf("%s",c);
    TraverselList(&l,&DisplayData);
    printf("Please Enter Y to Sort \n");
    scanf("%s",c);
    QuickSort(&l);
    printf("Please enter Y to Display Sorted data\n");
    scanf("%s",c);
    TraverselList(&l,&DisplayData);
    printf("\nSearch Data\n");
    do
    {
	printf("Please enter Grade: ");
	scanf("%s",&Grade);
	SearchDetails(&l,Grade);
	printf("\n\nDo you want to Search Again(Y,N)?:");
	scanf("%s",c);
    }while(!strcmpi("Y",c));

    getch();
    return 0;
}