//	Simple Student Database Management System 
#include<stdio.h>
#include<stdlib.h>	//system(), exit()
#include<conio.h>

void addStudent();
void studentRecord();
void searchStudent();
void delete();

struct student{
	char firstName[20];
	char lastName[20];
	int rollNo;
	char class[10];
	char  vill[20];
	float per;
};

FILE *fp;
struct student info;

void main(){

	int ch;
	while(ch != 5){
		system("cls");
		printf("\n\n\t\t\t======STUDENT DATABASE MANAGEMENT SYSTEM======\n");
		printf("\n\t\t\t\t  1. Add Student Record");
		printf("\n\t\t\t\t  2. Show Student Record");
		printf("\n\t\t\t\t  3. Search Student");
		printf("\n\t\t\t\t  4. Delete Record");
		printf("\n\t\t\t\t  5. Exit");
		printf("\n\t\t\t\t  ______________________\n");
		printf("\n\t\t\t\t");
		scanf("%d", &ch);
		
		switch(ch){
			case 1:
				system("cls");
				addStudent();
				system("cls");
				break;
				
			case 2: 
				system("cls");
				studentRecord();
				printf("\t\t\t\tPress any key to exit\n");
				getch();
				system("cls");
				break;
				
			case 3:
				system("cls");
				searchStudent();
				printf("\t\t\t\tPress any key to exit\n");
				getch();
				system("cls");
				break;
				
			case 4:
				system("cls");
				delete();
				printf("\t\t\t\tPress any key to exit\n");
				getch();
				system("cls");
				break;
				
			case 5:
				system("cls");
				printf("\n\t\t\tThank you, for used this software.\n\n");
				exit(0);
				break;
			
			default: 
				system("cls");
				getch();
				printf("\n\t\t\tEnter a valid number");
				printf("\t\t\t\tPress any key to exit\n");
				getch(); 
		}
		
	}

}

void addStudent(){
	char another;
	do{
		system("cls");
		printf("\n\n\t\t\t======ADD STUDENT INFORMATION======\n");
		fp = fopen("studentInformation.txt", "ab"); 
		printf("\n\t\t\tEnter first name : ");
		scanf("%s", &info.firstName);
		printf("\n\t\t\tEnter last name : ");
		scanf("%s", &info.lastName);
		printf("\n\t\t\tEnter roll number : ");
		scanf("%d", &info.rollNo);
		printf("\n\t\t\tEnter class : ");
		scanf("%s", &info.class);
		printf("\n\t\t\tEnter address : ");
		scanf("%s", &info.vill);
		printf("\n\t\t\tEnter percentage : ");
		scanf("%f", &info.per);
		printf("\n\t\t\t___________________\n");
		
		if(fp == NULL){
			fprintf(stderr, "\t\t\tCan't open file\n");
		}else{
			printf("\t\t\tRecord stored sucessfully\n");
		}
		
		fwrite(&info, sizeof(struct student), 1, fp);
		fclose(fp);
		
		printf("\t\t\tDo you want to add another record?(y/n) : ");
		scanf("%c", &another);
		getch();
	}while(another == 'y' || another == 'Y');
}

void studentRecord(){
	fp = fopen("studentInformation.txt", "r");
	printf("\n\n\t\t\t======STUDENT INFORMATIONS======\n\n");
	
	if(fp == NULL){
		fprintf(stderr, "\t\t\tCan't open file\n");
	}else{
		printf("\t\t\t\tRecords\n");
		printf("\t\t\t\t----------\n\n");
	}
	
	while(fread(&info, sizeof(struct student), 1, fp)){
		printf("\n\t\t\t\tStudent Name : %s %s", info.firstName, info.lastName);
		printf("\n\t\t\t\tRoll No.     : %d", info.rollNo);
		printf("\n\t\t\t\tClass.       : %s", info.class);
		printf("\n\t\t\t\tAddress      : %s", info.vill);
		printf("\n\t\t\t\tPercentage   : %f", info.per);
		printf("\n\t\t\t\t_____________________________\n");
	}
	fclose(fp);
	getch();
}

void searchStudent(){
	int rollNo, found = 0;
	fp = fopen("studentInformation.txt", "r");
	printf("\t\t\t\t======SEARCH STUDENT RECORD======\n");
	printf("\t\t\tEnter Roll No. : ");
	scanf("%d", &rollNo);
	
	while(fread(&info, sizeof(struct student), 1, fp)){
		
		if(info.rollNo == rollNo){
			found = 1;
			printf("\n\t\t\t\tStudent Name : %s %s", info.firstName, info.lastName);
			printf("\n\t\t\t\tRoll No.     : %d", info.rollNo);
			printf("\n\t\t\t\tClass.       : %s", info.class);
			printf("\n\t\t\t\tAddress      : %s", info.vill);
			printf("\n\t\t\t\tPercentage   : %f", info.per);
			printf("\n\t\t\t\t_____________________________\n");
		}
	}
	if(!found){
		printf("\t\t\tRecord Not found");
	}
	fclose(fp);
	getch();
}

void delete(){
	FILE *ft;
	int rollNo, found = 0;
	printf("\t\t\t\t======DELETE STUDENT RECORD======\n\n");
	printf("\t\t\tEnter Roll No. : ");
	scanf("%d", &rollNo);
	
	fp = fopen("studentInformation.txt", "r");
	ft = fopen("temp.txt", "w");
	if(fp == NULL){
		fprintf(stderr, "\t\t\tCan't open file\n");
	}
	while(fread(&info, sizeof(struct student), 1, fp)){
		if(info.rollNo == rollNo){
			found = 1;
		}else{
			fwrite(&info, sizeof(struct student), 1, ft);
		}
	}
	fclose(fp);
	fclose(ft);
	
	if(found){
		remove("studentInformation.txt");
		rename("temp.txt", "studentInformation.txt");
		printf("\n\t\t\tRecord Deleted Sucessfully\n");
	}
	if(!found){
		printf("\n\t\t\tRecord Not Found\n");
	}
	getch();
}

//17:10