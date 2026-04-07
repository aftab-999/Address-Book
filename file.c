#include <stdio.h>
#include "file.h"
#include<unistd.h>

void saveContactsToFile(AddressBook *addressBook) {
  int i;
  FILE *fp ;
  fp = fopen("contacts.csv","w");
  if(fp==NULL){
    printf("\nFILE NOT FOUND ❌\n");
  }
  for(i=0;i<addressBook->contactCount;i++){
    fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name ,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  }fclose(fp) ;

  for(int i=0;i<=100;i++){
    printf("\t\t\t✅ Saving Contacts %d...✅\r",i);
    fflush(stdout);
    if(i==100){
        usleep(500000);
    }usleep(10000);
  }
  printf("\nContacts changes Saved...✅ \n");
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp ;
    fp = fopen("contacts.csv","r");
    if(fp == NULL){
        printf("FILE NOT FOUND\n");
        return ;
    }
    while((fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email))==3){
        addressBook->contactCount++;
    }
    fclose(fp) ;
}
