#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>
#define offset 1

struct phonebook{
	char name[30];              //employee
   char number[30];
	char address[30];

   };
//--------------------------------------
struct node{
	struct phonebook pemp;
   struct node *pprev;
   struct node *pnext;
   };
//-----------------
void printphonebook(int location);
struct phonebook* filldata(void);
struct node* create_node(struct phonebook *data);
int search_node_name(struct phonebook *data);
int add_node(struct phonebook *data);
int insert_node(struct phonebook *data,int location);
int delete_node(int location);
int printphonebookloc(int location);
struct phonebook* filldataname();
int search_node_number(struct phonebook *data);
struct phonebook* filldatanumber();
int edit_node(struct phonebook *data);
int writetofile(struct node *phead2);
int readfromfile(void);
void lineeditor(char *word,int num,int start,int y);
void starting(void);
void writingtab(void);
void readingtab(void);
int numbervalidation(char number[]);
int search_node_name1(struct phonebook *data);
//-----------------------------
void menu(int x1,int y1);
int  highlight(int n,int x2);
//---------------------------------
void free_list();
void sorting(void);
struct node *phead;
struct node *ptail;

//---------------------
int main (){
char ch;
int n,x,y,check = 0;
x=1;y=1;

//textbackground(2);
//clrs
starting();
highlight(y,x);


do
{
	ch=getch();
   switch(ch)
	{
		case 0 :
   		ch=getch();
    		if(ch==80)     // down arrow
         {
         	gotoxy(x+offset,y+1+offset); y=y+1;
    			if (y==(10)) { gotoxy(1+offset,1+offset); x=1; y=1; }
      		highlight(x,y);
         }

      	else if (ch==72)   //up arrow
         {
         	gotoxy(x+offset,y-1); y=y-1;
    			if (y==(0)) { gotoxy(1+offset,9+offset); x=1; y=9; }
      		highlight(x,y);
         }
      	else if (ch==71) {gotoxy(1+offset,1+offset); x=1; y=1;highlight(x,y);; } //home
      	else if (ch==79) {gotoxy(x+offset,9+offset); x=1; y=9;highlight(x,y);; } // end
      break;

   	case 13 :    //when press enter " new menu "
   		if (y==1)
      	{
         	textbackground(0);
      		clrscr();
            starting();
      		if(add_node(filldata())){
            gotoxy(8,8);
            printf ("you added new contact successfully");
            }
            sorting();
         	menu (x,y);
      	}
      	else if (y == 2)             //edit contacts "search by name and edit contact"
      	{
         	//textbackground(0);
      		clrscr();
            starting();
            if(edit_node(filldataname())){
            	gotoxy(8,11);
               printf("You edited the contact successfully :D ");          // cant find the contact
            }
            else{
            	gotoxy(8,8);
               printf("NO contact with this name \"press any key to back to main menu \" ");
            }
         	menu (x,y);
      	}
      	else if (y == 3)                       // delete the contact
      	{
         	textbackground(0);
      		clrscr();
            starting();
         	if(delete_node(search_node_name(filldataname()))){
            	gotoxy(8,8);
               printf("The contact is deleted successfully");
            }
            else{
             	gotoxy(8,8);
               printf("NO contact with this name\"press any key to back to main menu\"");
            }
         	menu (x,y);
         }
         else if (y == 4)                  //search for contact by name
      	{
         	textbackground(0);
      		clrscr();
            starting();
         	if(!printphonebookloc(search_node_name(filldataname()))){
            	gotoxy(8,8);
               printf("NO contact with this name\"press any key to back to main menu\"");
            }
         	menu (x,y);
         }
         else if (y == 5)    // search for contact by number
      	{
         	textbackground(0);
      		clrscr();
            starting();
				if(!printphonebookloc(search_node_number(filldatanumber()))){
            	gotoxy(8,8);
               printf("NO contact with this number\"press any key to back to main menu\"");
            }
         	menu (x,y);
         }
         else if (y == 6)        //writing from file
      	{
         	textbackground(0);
            clrscr();
            starting();


            if(writetofile(phead)){
            	writingtab();
      		}
            else{
            	gotoxy(8,8);
            	printf("Can't Save The phonebook");
            }
         	menu (x,y);
         }
         else if (y == 7)       // read from file
      	{
         	textbackground(0);
      		clrscr();
            starting();
            n=readfromfile();
            readingtab();
            sorting();
            if (!n){printf("Can't load contacts"); clrscr(); }
         	menu (x,y);
         }
         else if (y == 8)                //exit from program
      	{
         	textbackground(0);
      		clrscr();
            starting();
         	printphonebook(0);
         	menu (x,y);
         }
      	else if (y == 9)
      	{
      	ch=27;
      	}
   }
}while(ch!=27) ;   // when i pressed escab exit






return 0 ;
}

//******************************    sorting     *********************************
void sorting(void){        //sorting function
   	int i;
      struct node *ptr,*min,*y;
      min=(struct node*)malloc (sizeof(struct node));
      ptr=phead;
      while(ptr){   //if there is list(not empty list)
      	y=ptr;
      	while(y){

            if (strcmp(ptr->pemp.name,y->pemp.name)>0)//compare the contact with the rest of list
            {
      			strcpy(min->pemp.name,y->pemp.name);      //copy the smaller value in min
               strcpy(min->pemp.number,y->pemp.number);
               strcpy(min->pemp.address,y->pemp.address);

      			strcpy(y->pemp.name,ptr->pemp.name);
               strcpy(y->pemp.number,ptr->pemp.number);
               strcpy(y->pemp.address,ptr->pemp.address);

        		   strcpy(ptr->pemp.name,min->pemp.name);
               strcpy(ptr->pemp.number,min->pemp.number);
               strcpy(ptr->pemp.address,min->pemp.address);

            }      //end if
            y=y->pnext;    //move this pointer to compare the same value with another value in list
         }         //end second while
         ptr=ptr->pnext;  // change the value which compared with all values in list
      }       //end first while
      free(min);
}   //end fun
//****************************** fill data ***************************
struct phonebook* filldata(){ //fill data in each node of list
      int i=0;
		char *editor;
      struct phonebook *ptr1;
   	ptr1 = (struct phonebook*)malloc (sizeof(struct phonebook)); // find palce in heap to put data in it
      gotoxy(2,2);
   	printf("enter the contact name : ");
		lineeditor(ptr1->name,30,26,2); // read the value
      gotoxy(2,3);
      printf("enter the contact Number : ");
      lineeditor(ptr1->number,30,28,3);
      while(!numbervalidation(ptr1->number)){       // number validation
      	gotoxy(2,3);
			printf("enter the contact Number : ");
         printf("                              ");

      	lineeditor(ptr1->number,30,28,3);
      }     // end while

      gotoxy(2,4);
      printf("enter the contact Address :  ");
      lineeditor(ptr1->address,30,30,4);
      return ptr1;
}     //end function

//****************************** fill data for search by name ***************************
struct phonebook* filldataname(){  //search for a node by name and return location
      struct phonebook *ptr1;
   	ptr1 = (struct phonebook*)malloc (sizeof(struct phonebook)); // find palce in heap to put data in it
      gotoxy(2,2);
   	printf("enter the name : ");
      lineeditor(ptr1->name,30,20,2);
      return ptr1;
}      //end function
//****************************** fill data for search by number ***************************
struct phonebook* filldatanumber(){               //search for a node by number and return location
      struct phonebook *ptr1;
   	ptr1 = (struct phonebook*)malloc (sizeof(struct phonebook));// find palce in heap to put data in it
      gotoxy(2,2);
   	printf("enter the number : ");
      lineeditor(ptr1->number,30,20,2);
      return ptr1;
}    //end function


//***************************** print node ------------------------------------
void printphonebook(int location)  //print function with location
{
	struct node *ptr;
   int i=0,n;
   ptr=phead; //start from first node
	while(ptr!=NULL){  //check if the list is not empty
   	gotoxy(2,2+i);
		printf("the contact  name   : %s",ptr->pemp.name);
      gotoxy(2,3+i);
   	printf("the contact number  : %s",ptr->pemp.number);
      gotoxy(2,4+i);
   	printf("the contact address : %s ",ptr->pemp.address);
      gotoxy(2,5+i);
      for(n=0;n<17;n++)
		putchar('?');


      ptr=ptr->pnext ;  //move to next node
      i=i+4;
   }  //end while
}    //end function
//-----------------------------print needed node only-----------------------------------
int printphonebookloc(int location) //ptint data founded by location
{  int loc=0,check = 0 ,n;
	struct node *ptr;
   ptr=phead;
   clrscr();
   starting();
	while(loc!=location&&ptr!=NULL){ //if not reatch to needed node or not reatch the end of list
      ptr=ptr->pnext ;  //move to next node
      loc++;
   }  //end while
   if(ptr){  //if found the node then print it
   	gotoxy(2,2);
		printf("Name    : %s",ptr->pemp.name);
      gotoxy(2,3);
   	printf("Number  : %s",ptr->pemp.number);
      gotoxy(2,4);
   	printf("Address : %s ",ptr->pemp.address);
      gotoxy(2,5);
      for(n=0;n<60;n++)
		printf("?");
      check = 1;
   }  //end if
   return check;
}    //end function

 //************************** create node --------------------------------------
struct node* create_node(struct phonebook *data){ //to creat the node
	struct node *ptr;
   ptr=(struct node*)malloc (sizeof(struct node));  //to find place in the heap
   if (ptr){              //if the place is founded

   	strcpy(ptr->pemp.name,data->name);
      strcpy(ptr->pemp.number,data->number);
      strcpy(ptr->pemp.address,data->address);
      ptr->pprev=NULL;
      ptr->pnext=NULL;
   } //end of
   return ptr;
}//end function
//************************** add node ------------------------------------------
int add_node(struct phonebook *data){  //to add a new contact to the list
	int retval=0;
   struct node *ptr;
   ptr = create_node (data); //call function to creat and fill the node before add it
   if (ptr){       //cheack if the node is created
   		if(phead==NULL)  //cheack if the list is empty
      		phead=ptail=ptr;
         else{             //cheack if the list is not empty
         	ptail->pnext=ptr;
         	ptr->pprev=ptail;
         	ptail=ptr;
      	}//end else
      	return 1;
   } //end frst if
   return retval;
}      //end function

//********************search for node by name-----------------------------------
int search_node_name(struct phonebook *data){             //search for a node by name
	int loc = 0;
	struct node *pcurrent;
   pcurrent=phead;

   	while(pcurrent && strcmp(pcurrent->pemp.name,data->name)!= 0){    //check if the list not reatch the end and the node is not founded yet
      	loc++;
   		pcurrent=pcurrent->pnext; //move to next node

   	}//end while

   return loc;
}     //end function
//********************search for node by name for read from file -----------------------------------
int search_node_name1(struct phonebook *data){    //search for a node by number
	int loc = 0,check = 0;
	struct node *pcurrent;
   pcurrent=phead;

   	while(pcurrent && strcmp(pcurrent->pemp.name,data->name)!= 0){ //check if the list not reatch the end and the node is not founded yet
      	loc++;
   		pcurrent=pcurrent->pnext;
   	}  //end while
     if(pcurrent != NULL && strcmp(pcurrent->pemp.name,data->name) == 0){ // if the list not reatch the end and the node is  founded
         check = 1;
      } //end if
   return check;
}  //end function
//------------------------------------------------------------------------------
//********************search for node by number---------------------------------
//------------------------------------------------------------------------------
int search_node_number(struct phonebook *data){ //search for a node by number
	int loc=0;
	struct node *pcurrent;
   pcurrent=phead;
   while(pcurrent&&strcmp(pcurrent->pemp.number,data->number)!=0) //check if the list not reatch the end and the node is not founded yet
   {
   	pcurrent=pcurrent->pnext;    //move to next node to search in it
      loc++;
   }     //end while
   return loc;
}        //end function
//********************Edit node-----------------------------------
int edit_node(struct phonebook *data)//edit available node
{
	int loc=0;
	struct node *pcurrent;
   pcurrent=phead;
   while(pcurrent&&strcmp(pcurrent->pemp.name,data->name)!=0)//check if the list is not empty
   {
   	pcurrent=pcurrent->pnext; //move to next node
      loc++;
   }
   printphonebookloc(loc); //print founded node
   if(pcurrent){ //if the list not ended yet
   	gotoxy(2,6);
   	printf("enter the name : ");
      lineeditor(pcurrent->pemp.name,30,20,6);
      gotoxy(2,7);
   	printf("enter the Number : ");
      lineeditor(pcurrent->pemp.number,30,20,7);
      while(!numbervalidation(pcurrent->pemp.number)){ //if the number entered is not a string
      	gotoxy(2,7);
   		printf("enter the Number :                                           ");
      	lineeditor(pcurrent->pemp.number,30,20,7);
      } //end while
      gotoxy(2,8);
   	printf("enter the Address :  ");
      lineeditor(pcurrent->pemp.address,30,20,8);
      loc = 1;
   } //end if
   else{     //if ueser enter string
   	loc = 0;
   }  //end else
   return loc;
}  //end function
//**************************delete Node ----------------------------------------
int delete_node(int location){
	int retval=0,i;
   struct node *pcurrent;
   if (phead){
   	if(location == 0){ // if node is first node
      	if(phead==ptail){//if linked list contain only one node
         	pcurrent=phead;
            phead=ptail=NULL;
         }
         else{  //if linked list contain more than one node
         	pcurrent=phead;
            phead=phead->pnext;
            phead->pprev=NULL;
         }
      }
      else{ //if node is not first node
      	pcurrent=phead;
         for(i=0;i<location;i++){  //used to move on all nodes
         	if(pcurrent){
            	pcurrent=pcurrent->pnext;
            }
         }
         if(pcurrent){  //check if pcurrent is not null
         	if(pcurrent==ptail){//if the pointer is on last node
            	ptail=ptail->pprev;//make tail is previous of this node
               ptail->pnext=NULL; //make next null
            }
            else{
            	pcurrent->pprev->pnext=pcurrent->pnext;//make next pointer of previous node is equal next of current node
               pcurrent->pnext->pprev=pcurrent->pprev;//make next pointer of previous node is equal previous of current node
            }
         }
      }

   free(pcurrent);  //free pointer
   return retval=1;
	}
   return retval=0;
}//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//-----------------------pop menu ----------------------------------------------
//------------------------------------------------------------------------------
//////////////////////
void menu(int x1,int y1)     //new menu
{
	getch();
   clrscr();                 // highlight when back from new menu
   starting();
   highlight(x1,y1);
}

////////////////////////
int highlight(int x2,int n)    //highlight the active menu
{
x2=x2+offset;
n=n+offset;
gotoxy(1+offset,1+offset);//position of Add new record option in menu
printf("Add new record");
gotoxy(1+offset,2+offset);//position of Edit record option in menu
printf("Edit record");
gotoxy(1+offset,3+offset);//position of delete record option in menu
printf("delete record");
gotoxy(1+offset,4+offset); //position of Search for a Record by Name option in menu
printf("Search for a Record by Name");
gotoxy(1+offset,5+offset);   //position of Search for a Record by Phone option in menu
printf("Search for a Record by Phone");
gotoxy(1+offset,6+offset);  //position of Save all Records to a file option in menu
printf("Save all Records to a file");
gotoxy(1+offset,7+offset); //position of Read all Records from file option in menu
printf("Read all Records from file");
gotoxy(1+offset,8+offset); //position of print all numbers    TEST option in menu
printf("print all numbers    TEST");
gotoxy(1+offset,9+offset); //position of Exit option in menu
printf("Exit");
switch(n) //switch for position of cursor
      {
      	case 1+offset :
         	gotoxy(x2,n);
         	textbackground(4);
            cprintf("Add new record");
            textbackground(0);
            break;
         case 2+offset :
         	gotoxy(x2,n);
         	textbackground(4);cprintf("Edit record");textbackground(0);
            break;
         case 3+offset :
         	gotoxy(x2,n);
         	textbackground(4);cprintf("delete record");textbackground(0);
            break;
         case 4+offset :
         	gotoxy(x2,n);
         	textbackground(4);cprintf("Search for a Record by Name");textbackground(0);
            break;
         case 5+offset :
         	gotoxy(x2,n);
         	textbackground(4);cprintf("Search for a Record by Phone");textbackground(0);
            break;
         case 6+offset :
         	gotoxy(x2,n);
         	textbackground(4);cprintf("Save all Records to a file");textbackground(0);
            break;
         case 7+offset :
         	gotoxy(x2,n);
         	textbackground(4);cprintf("Read all Records from file");textbackground(0);
            break;
         case 8+offset :
         	gotoxy(x2,n);
         	textbackground(4);cprintf("print all numbers    TEST");textbackground(0);
            break;
         case 9+offset :
         	gotoxy(x2,n);
         	textbackground(4);cprintf("Exit");textbackground(0);
            break;

         }

         return x2 ;
}
//---------------------------------------------------------------------------
//------------------------------write to file--------------------------------
//----------------------------------------------------------------------------
int writetofile(struct node *phead2){
	struct phonebook contact;
   struct node *ptr;
   FILE *fptr;
   int retval=0;
   fptr = fopen("test.txt", "w"); //open file to write in it
   ptr=phead2;
   if(fptr){
   	while(ptr){
   		fprintf(fptr,"%s\n",ptr->pemp.name); //read contact name from file
         fprintf(fptr,"%s\n",ptr->pemp.number);//read contact  number  from file
         fprintf(fptr,"%s\n",ptr->pemp.address); //read contact  address from file
      	ptr=ptr->pnext;
   	}
      retval = 1;
   }
   fclose(fptr);
   return retval;

}

//------------------------------------------------------------------------------
//-------------------------------read from file --------------------------------
//------------------------------------------------------------------------------
int readfromfile(){
	int check,retval=1;
	struct phonebook *contact;
   FILE *fptr;
   contact = (struct phonebook*)malloc (sizeof(struct phonebook)); //read contact name , number , address from file
   fptr = fopen("test.txt", "r+"); //read from file
   if(fptr){
   	fscanf(fptr,"%s",contact->name);  //read contact name  from file
      fscanf(fptr,"%s",contact->number);//read contact number from file
      fscanf(fptr,"%s",contact->address);//read  contact address from file
      check = search_node_name1(contact);//used to check if contact found or not
      if(check == 0)  //the contact is not found
      {
      	add_node(contact); //adding node
      }
   	while(!feof( fptr )){
			fscanf(fptr,"%s%s%s\n",contact->name,contact->number,contact->address);
		if(!search_node_name1(contact))//check if contact found or not
      {
   		add_node(contact); //adding node
      }
   	}
      free(contact);
      return retval;
   }
   retval=0;
   fclose(fptr);
   return retval;
}
//------------------------------------------------------------------------------
//------------------------------ SCANF function---------------------------------
//------------------------------------------------------------------------------

void lineeditor(char *word,int num,int start,int y){
char nav,*address;
int flag=0;      //flag for while loop
int insertflag=0;//to indicate insert mode
int current=1;  //position of cursor in string
int end=1;    //end of string
int del; //used for backspace
address=word;
gotoxy(68,24);
printf("normal mode");
while (flag!=1)
	{
      if(current!=num)gotoxy((current+start),y);   // to make cursor stop at the end of line
      else gotoxy((current+start)-1,y);
   	nav=getch();

      switch(nav)
      {
      	case 13:                                  //enter
         	if(current == 1)
            	word[0] = 0;
      		flag=1;
      		break;


      	case 27:                                 //esc
      		flag=1;
         	break;

      	case 8:                                 //backspace
         	if (current!=1&&end!=1)              //codition of no char is pressed blank page
            {
            	current--;
            	gotoxy((current+start),y);
            	printf(" ");                     //print space instead of the char
            	gotoxy((current+start),y);
               for(del=current+1;del<end;del++)  // condition for current not equal end make backstep for all char till end
            	{
            		word[del-2]=word[del-1];
            	}
            	for(del=current;del<end-1;del++)   // print all char till end
            	{
            		printf("%c",word[del-1]);
            	}
               gotoxy(((end+start)-1),y);                  // replace last char with space on screen
               printf(" ");
               end--;
               word[end-1]=0;                  // replace last char with null in array
               gotoxy((current+start),y);
            }
            break;

         case 46:                                //delete
         	if (current!=end)
            {

         		for(del=current+1;del<end;del++)
            	{
            		word[del-2]=word[del-1];
            	}
            	for(del=current;del<end-1;del++)
            	{
            		printf("%c",word[del-1]);
            	}
               gotoxy(((end+start)-1),y);
               printf(" ");
            	gotoxy((current+start),y);
               end--;
               word[end-1]=0;                  // replace last char with null in array
            }
            break;
      }

      if(isprint(nav)&&nav!=46)
      {
         switch(insertflag)                   //flag for insert and normal mode
         {
         	case 1:        //insert mode
            	if (current==num)                    // codition for end of line
               {
               	word[current-2]=nav;             // print in last char place
               	word[current-1]=0;
      				gotoxy(((current+start)-1),y);
      				printf("%c",word[current-2]);
                  gotoxy(((current+start)-1),y);
               }
               else
               {
      				word[current-1]=nav;
      				gotoxy(current+start,y);
      				printf("%c",word[current-1]);
               	end=strlen(word)+1;
               	if (current<num)
         				current++;
               	else
               		current=current;
               }
               break;

            case 0:                                       //normal mode
               if(current==end&&current!=num&&end!=num)     // condition of not reached the end of line
               {
               	word[current-1]=nav;
               	word[current]=0;
      				gotoxy((current+start),y);
      				printf("%c",word[current-1]);
         			current++;
         			end=strlen(word)+1;
               }
               else if (current==num&&end==num)             //if reached the end of line
               {
               	/*for(del=end-2;del>=current-1;del--)
            		{
            			word[39]=word[del];
            		}*/
                  word[current-2]=nav;
               	word[num]=0;
      				gotoxy(((current+start)-1),y);
      				printf("%c",word[current-2]);
                  gotoxy(((current+start)-1),y);
            		/*for(del=current;del<39;del++)
            		{
            			printf("%c",word[del]);
            		}
                 	gotoxy(current,y);*/
               }

               else                                       //condition of the cursor not at end of line
               {
            		for(del=end-2;del>=current-1;del--)
            		{
            			word[del+1]=word[del];
            		}
               	if (end!=num) end++;
               	word[current-1]=nav;
               	word[end-1]=0;
      				gotoxy((current+start),y);
      				printf("%c",word[current-1]);

            		for(del=current;del<=end-1;del++)
            		{
            			printf("%c",word[del]);
            		}
                  current++;
               	gotoxy((current+start),y);
               }
            break;
          }

      }
///////////////////////////////////////////////////////////////////
		if (nav==0)                  // extended key
      {
      	nav=getch();
   		switch(nav)
      	{
      		case 77:               //right
            	if (current<end)
               {
         			current++;
            		gotoxy((current+start),y);
               }
            	break;
            case 75:               //left
            	if (current>1)
               {
         			current--;
            		gotoxy((current+start),y);
               }
            	break;
            case 71:  //home
        			current=1;
            	gotoxy((current+start),y);
              	break;
            case 79:                        //end
               current=end;
            	gotoxy(end,y);
              	break;
            case 82:                //insert
            	if (insertflag==1)                  // to change mode from extended to normal
               {
						insertflag=0;
                  gotoxy(68,24);
            		printf("normal mode");
 					}
               else
               {
               	insertflag=1;                // to change mode form normal to extended
               	gotoxy(68,24);
            		printf("insert mode");
               }
            break;
      	}
      }

      if (end>num-1)
      {
         end=num;
      }
   }
}

//------------------------------------------------------------------------------
//----------------------------------border--------------------------------------
//------------------------------------------------------------------------------
void starting()
{
char i;
gotoxy(1,1);
putchar('É');   //character used in drawing border
for(i=0;i<78;i++)
	putchar('Í'); //character used in drawing border
putchar('»'); //character used in drawing border
gotoxy(1,23);
putchar('È'); //character used in drawing border
for(i=0;i<78;i++)
	putchar('Í'); //character used in drawing border
putchar('¼');  //character used in drawing border
for(i=2;i<23;i++){
	gotoxy(1,i);
	cprintf("º");  //character used in drawing border
}
for(i=2;i<23;i++){
	gotoxy(80,i);
	cprintf("º");  //character used in drawing border
}
gotoxy(2,1);
}
//------------------------------------------------------------------------------
//---------------------------- reading tab-------------------------------------
//------------------------------------------------------------------------------
void readingtab()
{
	char i;
	int n;
	gotoxy(8,4);
	putchar('É');  //character used in drawing border
	for(i=0;i<60;i++)
		putchar('Í'); //character used in drawing border
	putchar('»');   //character used in drawing border
	gotoxy(8,7);
	putchar('È');  //character used in drawing border
	for(i=0;i<60;i++)
		putchar('Í');  //character used in drawing border
	putchar('¼');  //character used in drawing border
	for(i=5;i<7;i++){
		gotoxy(8,i);
		cprintf("º"); //character used in drawing border
   }
	for(i=5;i<7;i++){
		gotoxy(69,i);
		cprintf("º");  //character used in drawing border
   }
	gotoxy(28,7);
	printf("Reading from file");
	for(i=0;i<59;i++){
		for(n=0;n<40000000;n++){}
		gotoxy(9+i,5);
		textbackground(4);cprintf("  ");
      gotoxy(9+i,6);
		textbackground(4);cprintf("  ");
	}
	gotoxy(28,7);
	printf("Reading completed");
	textbackground(0);
}
//------------------------------------------------------------------------------
//---------------------------- writing tab-------------------------------------
//------------------------------------------------------------------------------
void writingtab()
{
char i;
int n;
gotoxy(8,4);
putchar('É'); //character used in drawing border
for(i=0;i<60;i++)
	putchar('Í');  //character used in drawing border
putchar('»');   //character used in drawing border
gotoxy(8,7);
putchar('È'); //character used in drawing border
for(i=0;i<60;i++)
	putchar('Í');   //character used in drawing border
putchar('¼');   //character used in drawing border
for(i=5;i<7;i++){
	gotoxy(8,i);
	cprintf("º");  //character used in drawing border
}
for(i=5;i<7;i++){
	gotoxy(69,i);
	cprintf("º");  //character used in drawing border
}
gotoxy(28,7);
printf("writing to file");
for(i=0;i<59;i++){
	for(n=0;n<40000000;n++){
   }
	gotoxy(9+i,5);
	textbackground(4);cprintf("  ");
	gotoxy(9+i,6);
	textbackground(4);cprintf("  ");
	}
gotoxy(28,7);
printf("writing completed");
textbackground(0);
}

//-------------------------------- validation ----------------------------------

//--------------------------- number validation --------------------------------

int numbervalidation(char number[]){
   int check,retval = 1,i = 0;
	while(number[i] != NULL){   //check if number is not null
   	check = number[i];
      if (check < 48 || check > 57){  //check if number is intger or not(0->9)
      	retval = 0;
      }

      i++;
   }
   return retval;
}








