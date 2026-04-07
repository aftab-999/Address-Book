#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<unistd.h>

int uniquename(char temp[] , AddressBook *addressBook){
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].name , temp)==0){
            printf("Please enter unique name , as name already exists 🚫");
            return 1 ;
        }
    }return 0 ;
}


int uniquephone(char temp[] , AddressBook *addressBook){
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].phone , temp)==0){
            printf("Please enter unique phone , as phone already exists 🚫");
            return 1 ;
        }
    }return 0 ;
}

int uniqueemail(char temp[] , AddressBook *addressBook){
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].email , temp)==0){
            printf("Please enter unique email , as email already exists 🚫");
            return 1 ;
        }
    }return 0 ;
}
int validatename(char temp[]){
    int i=0; 
    while(temp[i]!='\0'){
        if((temp[i]>='a' && temp[i]<='z') || (temp[i]>='A' && temp[i]<='Z') || (temp[i] == ' ')){
            i++;
        }else {
            printf("Please enter valid name 🚫");
            return 1 ;
        }
    }return 0 ;
}


int validatephone(char temp[]){
    int i=0; 
    while(temp[i]!='\0'){
        if(temp[i]>='0' && temp[i]<='9'){
            i++;
        }
        else {
            
          printf("\nPlease enter valid phone number 🚫");
            
            return 1 ;
        }
    }/*if(i<10 || i>10){
            printf("\nPlease enter correct 10 digit phone number 🚫");
            return 1 ;
        }*/
          
    return 0 ;
}


int validateemail(char temp[]){
    char target[] = "@" ;
    char com[] = ".com" ;
    if(strstr(temp,target)==NULL){
     printf("Entered email is invalid '@' is missing ❓");
     return 1 ;
    }
    if(strstr(temp,com)==NULL){
        printf("Entered email is invalid '.com' is missing ❓");
        return 1 ;
    }
     return 0 ;
}

void listContacts(AddressBook *addressBook, int sortCriteria) {
    Contact dummy ;
    // Sort contacts based on the chosen criteria
   switch(sortCriteria){
    case 1 : 
    printf("🔸Sorting based on Names - \n");
    // logic of sorting by names 
     for(int i=0;i<(*addressBook).contactCount;i++){
        for(int j=i+1;j<(*addressBook).contactCount ;j++){
            if(strcmp((*addressBook).contacts[i].name , (*addressBook).contacts[j].name) > 0){
             dummy = (*addressBook).contacts[i];
             (*addressBook).contacts[i] = (*addressBook).contacts[j];
             (*addressBook).contacts[j] = dummy ;
            }
        
        } ;
    } 
    // addressBook.contacts[i].name[i]
    break ;

    case 2 : 
    printf("🔸Sorting based on Phone Numbers - ");
    // logic of sorting by Phone numbers -  
    
     for(int i=0;i<addressBook->contactCount-1;i++){
        for(int j=i+1;j<addressBook->contactCount;j++){
            if(strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].phone)>0){
                dummy = addressBook->contacts[i] ; 
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = dummy ; 
            }
        }
     }

    break ;

    case 3 : 
    printf("🔸 Sorting based on Email - ");
    // logic of sorting by Email -  
    for(int i=0;i<addressBook->contactCount-1;i++){
        for(int j=i+1;j<addressBook->contactCount;j++){
            if(strcmp(addressBook->contacts[i].email , addressBook->contacts[j].email)>0){
                dummy = addressBook->contacts[i] ; 
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = dummy ;
            }
        }
    }
    break ;

    default:
    printf("Selection choice is Invalid .❌ ");
    return ;
   } 

   printf("--------------------------------------\n");
   printf("INDEX\tNAME\tPHONE\tEMAIL\n\n");
   for(int i=0;i<addressBook->contactCount;i++){
   printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
   }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
  loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    printf("------------CREATE CONTACT MENU----------------\n");
	char temp[50] ;
    do{
    printf("\n🟨 Enter the name - ");
    scanf(" %[^\n]",temp);
    }while(validatename(temp) | uniquename(temp , addressBook));
    strcpy(addressBook->contacts[addressBook->contactCount].name , temp);
    
    char temp1[10] ;
    do{
    printf("\n🟨 Enter the phone - ");
    scanf(" %[^\n]",temp1);
    }while(validatephone(temp1) | uniquephone(temp1 , addressBook));
    strcpy(addressBook->contacts[addressBook->contactCount].phone , temp1);
    
    
    char temp2[50] ;
    do{
    printf("\n🟨 Enter the email - ");
    scanf(" %[^\n]",temp2);
    }while(validateemail(temp2) | uniqueemail(temp2 , addressBook));
    strcpy(addressBook->contacts[addressBook->contactCount].email , temp2);
   // saveContactsToFile(addressBook);
    addressBook->contactCount++ ;

    printf("\n-----------------------------------------------\n");
    printf("Contact created Successfully ! ✅\n");
    printf("\n-----------------------------------------------\n");

}

int searchContact(AddressBook *addressBook) {
    /* Define the logic for search */
    int opt ; 
    char temp[20] ;
    int count = 0 ;
    printf("Enter option 1 - Search by name\nEnter option 2 - Search by phone\nEnter option 3 - Search by email\n Enter option : ");
    scanf("%d",&opt);
    switch(opt){
        case 1 :
        
        do{
        printf("🟨 Enter the name : ");
        scanf(" %[^\n]",temp);
        }while(validatename(temp));
         printf("\nINDEX\tNAME\tPHONE\tEMAIL\n");
        printf("-----------------------------------------\n");
        for(int i=0;i<addressBook->contactCount;i++){
        if(strcasestr(addressBook->contacts[i].name,temp)!=0){
         count++ ;
                printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            } 
        }
        if(count<1){
            printf("No Match Found ! 💢");
            return 0 ;
         }
        count = 0 ;
        return 1 ;
        break;

        case 2 :
        //int count = 0 ;
        do{
        printf("🟨 Enter the phone: ");
        scanf(" %[^\n]",temp);
        }while(validatephone(temp));
        //int sizeoftemp = strlen(temp);
         printf("\nINDEX\tNAME\tPHONE\tEMAIL\n");
        printf("-----------------------------------------\n");
        for(int i=0;i<addressBook->contactCount;i++){
        if(strcasestr(addressBook->contacts[i].phone , temp )!=0){
            count++ ;
         printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
        }if(count<1){
            printf("No Match Found !💢");
            return 0 ;
         }
        count = 0 ;
        return 1 ;
        break;

        case 3 :
        //int count = 0 ;
        do{
        printf("🟨 Enter the email : ");
        scanf(" %[^\n]",temp);
        }while(validateemail(temp));
       // int sizeoftemp = strlen(temp);
        printf("\nINDEX\tNAME\tPHONE\tEMAIL\n");
         printf("-----------------------------------------\n");
        for(int i=0;i<addressBook->contactCount;i++){
        if(strcasestr(addressBook->contacts[i].email , temp )==0){
            count++;
                printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);       
                
            }
        }if(count<1){
            printf("No Match Found ! 💢");
            return 0 ;
         }
        count = 0 ;
        return 1 ;
        break;

        default:
        printf("You entered invalid option ❌");
    }return 1 ;
}

void editContact(AddressBook *addressBook){
 int index , opt ;  
 if(!searchContact(addressBook))
    return ;

printf("\nEnter the index to edit contact ----> ");
scanf("%d",&index);
getchar() ;
if(index<0 || index>addressBook->contactCount){
    printf("\nEnter index between 0 and Number of Contacts present in Book 🚫");
}edit:
printf("\n🟢Option 1 - For editing Name \n🟢Option 2 - For editing Phone \n🟢Option 3 - For editing Email\n");
printf("🟨Enter Option ---> ");
scanf("%d",&opt);
getchar();
char var[50] ;
switch(opt){
  case 1 :
  do{
        printf("🔸Enter NEW name - ");
        scanf("%s",var);
        getchar();
  } while(validatename(var) | uniquename(var , addressBook));    
   strcpy(addressBook->contacts[index-1].name,var);
   printf("\n------------------------------------------\n");
   printf("Name edited successfully ✅");       
   printf("\n------------------------------------------\n");
   break;

  case 2 :
  do{
        printf("🔸Enter NEW phone - ");
        scanf("%s",var);
        getchar();
       }while(validatephone(var) | uniquephone(var , addressBook))  ;
          strcpy(addressBook->contacts[index-1].phone,var);
        printf("\n------------------------------------------\n");
        printf("Phone number edited successfully ✅");
        printf("\n------------------------------------------\n");
          break;

  case 3 :
  do{
        printf("🔸Enter NEW email - ");
        scanf("%s",var);
        getchar();
  }while(validateemail(var) | uniqueemail(var , addressBook));
  strcpy(addressBook->contacts[index-1].email,var);
  printf("\n------------------------------------------\n");
  printf("Email edited successfully ✅");
  printf("\n------------------------------------------\n");
        break;

  default :
  printf("\nYou entered invalid option ❌");
  goto edit;

}

}

void deleteContact(AddressBook *addressBook)
{
    int index ;
    if(!searchContact(addressBook)) 
    return ;
    edit1:
    printf("\nEnter the index to Delete the contact --> ");
    scanf("%d",&index);
    
    if(index<0 || index>addressBook->contactCount){
        printf("You have entered invalid Index ❌");
        goto edit1;
    }
    for(int i=index-1;i<addressBook->contactCount;i++){
        strcpy(addressBook->contacts[i].name , addressBook->contacts[i+1].name);
    }
    addressBook->contactCount-- ;
   printf("\n------------------------------------------\n");
   printf("Contact deleted successfully ✅");
   printf("\n------------------------------------------\n");
    
}
