#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

void clearInput();
void addNewcustomer();
void listAll();
void deletecustomer();
void modifycustomer();
int findcustomer();
int prompt();
int findnum (int);

typedef struct customer {   
    int number;        
    char name[20];      
    char phone[15];    
    char email[20];	
    char bal[20];           
    struct customer *next;  
    int count;         
    } Customer;
Customer *firstc,*currentc,*newc; 
int cnum = 0; 

int main()
{
    FILE *datafile;
    char *filename = "customerdatabase.dat";
    char ch;
    clrscr();
    firstc = NULL;
    datafile = fopen(filename,"r"); 
    
    if(datafile)	 
    {
	    firstc = (struct customer *)malloc(sizeof(struct customer));
	    currentc = firstc;       
	    while(1) 
     	    {
		    newc = (struct customer *)malloc(sizeof(struct customer));
		    fread(currentc,sizeof(struct customer),1,datafile);
		    if(currentc->next == NULL)   
			    break;
		    currentc->next = newc;       
            currentc->count=0;           
		    currentc = newc;             
	    }
	    fclose(datafile);                
	    cnum = currentc->number;         
        
    }
        
    do
    {
	fflush(stdin);
        puts("\nWelcome To The Customer Management System");
        puts("-- -------------------------------------------");
        puts("1 - Add a New Customer");     
	puts("2 - Delete Customer Details");          
	puts("3 - List all Customers");       
	puts("4 - Modify Customer Details");          
	puts("5 - Find a Customer by name");  
	puts("-- -------------------------------------------");
        puts("Q - Save and quit\n");         
        printf("\tYour choice:");            
        ch = getchar();
	    ch = toupper(ch);
        switch(ch)     
        {
            case '1':
                puts("Add a new Customer\n");
	        fflush(stdin);
                addNewcustomer(); 
                break;
	    case '2':
		puts("Delete a Customer\n");
		deletecustomer();
		break;
	    case '3':
		puts("List all Customers\n");
		listAll();
		break;
	    case '4':
		puts("Modify a Customer Deatails\n");
		modifycustomer();
		break;
	    case '5':
		puts("Find a Customer by name\n");
		findcustomer();
		break;
            case 'Q':
                puts("Save and quit\n");
                default:
                break;
        }
    }
    while(ch != 'Q');

    currentc = firstc;
    
    if(currentc == NULL)
	    return(0);		
				  
    datafile = fopen(filename,"w");   
    
    if(datafile == NULL)
    {
	    printf("Error writing to %s\n",filename);
	    return(1);
    }
    				
    while(currentc != NULL)
    {
	    fwrite(currentc,sizeof(struct customer),1,datafile);
	    currentc = currentc->next;
    }
    fclose(datafile);             
    return(0);
}
void addNewcustomer() 
{
    newc = (struct customer *)malloc(sizeof(struct customer)); 
    if(firstc==NULL)
        firstc = currentc = newc;
    else
    {
        currentc = firstc;       
                                
        while(currentc->next != NULL)currentc = currentc->next;
                                
        currentc->next = newc;  
        currentc = newc;         
    }

    cnum++;
    printf("%27s: %5i\n","customer number",cnum);
    currentc->number = cnum;    
    
    printf("%27s: ","Enter customer name");
    gets(currentc->name);
    printf("%27s: ","Enter Phone number");
    gets(currentc->phone);
    printf("%27s: ","Enter email");
    gets(currentc->email);
     printf("%27s: ","Enter balance");
    gets(currentc->bal);
    printf("customer detail added!");
    currentc->count=0;
    currentc->next = NULL;
}

void listAll() 
{
    if(firstc==NULL)
        puts("There are no Customer details to display!"); 
        
    else
    {
	    printf("%6s %-20s %-15s %-15s %13s\n","Acc.#","Name","Phone","Email","Balance");
        puts("--------------------------------------------------------------------------");           
                           
        currentc=firstc;
        
        do
        {
        
                printf("%6d: %-20s %-15s %-20s %-20s\n",\
                currentc->number,\
                currentc->name,\
                currentc->phone,\
                currentc->email,
                currentc->bal); 
                
        }
        
        while((currentc=currentc->next) != NULL);
    }
}

void deletecustomer()              
{
    int record;
    struct customer *previousa;
    if(firstc==NULL)
    {
        puts("There are no Customer details to delete!");
	return;
    }
    
    listAll();	  
    printf("Enter customer account number to delete: ");
    scanf("%d",&record);
    currentc = firstc;
    
    while(currentc != NULL)
    {
        if(currentc->number == record)
	{
	    if(currentc == firstc)	
		firstc=currentc->next; 
	    else
		previousa->next = currentc->next;
                                        
        free(currentc); 
	    printf("Customer detail %d is deleted!\n",record);
	    return;
	}
	
	else
	{
        previousa = currentc;
	    currentc = currentc->next;
	}
    }
    printf("Customer details %d not found!\n",record);
 }

void modifycustomer()   
{
    int record, result;
    if(firstc==NULL)
    {
        puts("There are no customer details to modify!");
	return;
    }
    
    listAll();		
    printf("Enter customer account number to modify: ");
    scanf("%d",&record);  
    result = findnum(record);
    
    if( result >0 ){
	    printf("Customer %d:\n",currentc->number);
	    printf("Name: %s\n",currentc->name);
	    if(prompt())
		    gets(currentc->name);
	    printf("Phone: %s\n",currentc->phone);
	    if(prompt())
		    gets(currentc->phone);
	    printf("Email: %s\n",currentc->email);
	    if(prompt())
		    gets(currentc->email);
		    printf("Balance: %s\n",currentc->bal);
	    if(prompt())
		    gets(currentc->bal);
		    
	    return;
	}
    printf("Customer details %d was not found!\n",record);
}

int findnum (int recordnum)
{
    int record;
    record = recordnum;
    currentc = firstc;
    while(currentc != NULL)
    {
                   
        if(currentc->number == record)
	     {
           return 1;
         }
         
	else
	{
	    currentc = currentc->next;
	}
    }
    return -1;   
}
int findcustomer() 
{
     char buff[20];
     
     if(firstc==NULL)
	{
        puts("There are no Customer details to find!");
	    return 1;
    }
    
    printf("Enter Customer name: ");
    fflush(stdin);
    gets(buff);
    
    currentc = firstc;
    while(currentc != NULL)
    {
        if( strcmp(currentc->name, buff) == 0 )
	    {
			printf("%6s %-20s %-15s %-20s %-20s \n","Acct#","Name","Phone","Email","Balance");
		
            printf("%6d: %-20s %-15s %-20s %-20s\n",\
            currentc->number,\
            currentc->name,\
            currentc->phone,\
            currentc->email, 
            currentc->bal); 
            return 0;
	    }
		else
		{
			currentc = currentc->next;
		}
    }
    printf("Customer details %s was not found!\n",buff);
          return 1;
}  
 
int prompt()
{
	char ch;
    fflush(stdin);
	printf("Update? (Y to update any other key to not)");
	ch = getchar();
	ch = toupper(ch);
	fflush(stdin);
	if(ch == 'Y')
	{
		printf("Enter new value: ");
		return(1);
	}
	else
		return(0);
}
