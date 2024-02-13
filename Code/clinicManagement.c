#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"TYPESSTD.h"
#include"clinicManagement.h"
patient *head=NULL;
slot slots[5];
void intializeSlots(void){
	for(u8 i=0;i<5;i++){
		slots[i].id=i+1;
		switch(i){
		case 0:
			strcpy(slots[i].time, "2:00pm to 2:30pm");
			break;
		case 1:
			strcpy(slots[i].time, "2:30pm to 3:00pm");
			break;
		case 2:
			strcpy(slots[i].time, "3:00pm to 3:30pm");
			break;
		case 3:
			strcpy(slots[i].time, "4:00pm to 4:30pm");
			break;
		case 4:
			strcpy(slots[i].time, "4:30pm to 5:00pm");
			break;
			
		}
		slots[i].isAvailable =1;
	}
}
patient* idSearch(patient**head ,u32 id){
	patient* current=*head;
	while(current!=NULL){
		if(current->id==id){
			return current;
			
		}
		current=current->next;
	}
	return NULL;
}
void clearInputBuffer(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Admin Mode/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

void AdminMode(void){
	u32 password;
	u32 correct_password=1234;
	u8 num_of_tries=0;
	
	do{
		printf("Please enter Password : ");
		scanf("%d",&password);
		if(password!=correct_password){
			num_of_tries++;
			printf("Incorrect password. please try again,you strill have %d Tries\n",3-num_of_tries);
			
			
		}else{
			break;
		}
		if(num_of_tries==3){
			printf("Too many incorrect tries. Exitting...\n");
			exit(0);
		}
	}while(num_of_tries<=3);
	printf("Welcome to admin mode!\n");	
	//admin features
	feature_selection_for_admin();

}
void feature_selection_for_admin(void){
	printf("----------------------------------------------------\n");

	printf("To add patient enter : 1\n");
	printf("To Edit patient enter : 2\n");
	printf("To reserve a slot with the doctor enter : 3\n");
	printf("To cancel reservation enter : 4\n");
	u8 feature;
	printf("Please choose a feature : ");
	fflush(stdout);
	scanf("%d",&feature);
	printf("----------------------------------------------------\n");

	clearInputBuffer();
	switch(feature){
	case 1:
		//Add new patient record
		addPatient();
		
		break;
	case 2:
		//Edit patient record
		Edit_patient_record();
		break;
	case 3:
		//Reserve a slot with the doctor
		reserveSlot();
		break;
	case 4:
		//Cancel reservation
		cancelReservation();
		break;
	}
	
}

///////////////////////////1-Add new patient record////////////////////////////////////

void addPatient(void){
	char name[60];
	u16 age;
	char gender;//F for femal and M for male
	u32 id;
	printf("Enter patient name : ");
	fflush(stdout);
	scanf("%s",&name);
	clearInputBuffer();
	char newName[60];
	strcpy(newName,name);
	printf("Enter patient Gender (F for femal and M for male): ");
	fflush(stdout);
	scanf("%c",&gender);
	clearInputBuffer();
	printf("Enter patient age : ");
	fflush(stdout);
	scanf("%d",&age);
	clearInputBuffer();
	printf("Enter patient ID : ");
	fflush(stdout);
	scanf("%d",&id);
	clearInputBuffer();
	if(is_patient_exist(&head,id)==0){
			
		head=add_new_patient(head,newName,gender,age,id);
	}
}
u8 is_patient_exist(patient**head,u32 id){
	patient *current=*head;
	while(current!=NULL){
		if(current->id==id){
			printf("Rejected operation. Patient with the same ID already exists\n");
			return 1;
		}
		current=current->next;
	}
	return 0;
}
patient* add_new_patient(patient*head,char name[],char gender,u16 age,u32 id){
	patient* new_patient=(patient*)malloc(sizeof(patient));
	if(new_patient==NULL){return NULL;}

	strcpy(new_patient->name, name);
	new_patient->gender=gender;
	new_patient->id=id;
	new_patient->age=age;
	new_patient->next=NULL;
	if(head==NULL){
		head=new_patient;
	}
	else{
		patient*temp=head;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=new_patient;
		
	}
	printf("New Patient added completely\n");

	
	return head;
}

//////////////////////////////2-Edit patient record////////////////////////////////////


void Edit_patient_record(){
	u32 id;
	printf("Please enter patient ID you want to edit : ");
	scanf("%d",&id);
	clearInputBuffer();

	valid_id(&head,id);
	
}

void valid_id(patient**head ,u32 id){
	patient* current=*head;
	while(current!=NULL){
		if(current->id==id){
			u8 edit;
			printf("Enter data you want tot edit :\n");
			printf("Do you want to edit name?(for yes pres 1 and no press 0 ):");
			fflush(stdout);scanf("%d",&edit);
			clearInputBuffer();

			if(edit==1){
				printf("Please enter name: ");
				char name[60];
				fflush(stdout);scanf("%s",&name);
				clearInputBuffer();

				/*for(int i=0;i<sizeof(current->name)&&name[i]!='\0';i++){
					current->name[i]=name[i];
				}*/
				strcpy(current->name, name);
			}
			printf("Do you want to edit age?(for yes pres 1 and no press 0 ):");
			fflush(stdout);scanf("%d",&edit);
			clearInputBuffer();

			if(edit==1){
				printf("Please enter age: ");
				u16 age;
				fflush(stdout);scanf("%d",&age);
				clearInputBuffer();

				current->age=age;

			}
			printf("Do you want to edit gender?(for yes pres 1 and no press 0 ):");
			fflush(stdout);			scanf("%d",&edit);	clearInputBuffer();

			if(edit==1){
				printf("Please enter gender: ");
				char gender;
				fflush(stdout);
				scanf("%c",&gender);	clearInputBuffer();

				current->gender=gender;

			}
			printf("Patient information edited completely\n");
			return ;
		}
		current=current->next;
	}
	printf("incorrect ID, no patient with this ID\n");
}

/////////////////////3-Reserve a slot with the doctor////////////////////////////////////


void displayAvailableSlots(void){
	printf("Available slots :\n");
	int cnt=0;
	for(u8 i=0;i<5;i++){
		if(slots[i].isAvailable==1){
			cnt++;		printf("%d. %s\n",slots[i].id,slots[i].time);
		}
	}
	if(cnt==0){
		printf("No available slots\n");
	}
}
u8 validSolt(u8 slotid){
	if(slotid>=1&&slotid<=5&&slots[slotid-1].isAvailable==1){
		return 1;
	}return 0;
}
void reserveSlot(void){
	displayAvailableSlots();
	u32 patientID;
	printf("please enter the ID of the patient you want to reserve slot for : ");
	fflush(stdout);
	scanf("%d",&patientID);
	clearInputBuffer();
	u32 ID=patientID;
	while(idSearch(&head,ID)==NULL){
		printf("You enter invalid ID,there is no patient with this ID,please try to enter patient ID again : ");
		fflush(stdout);
		scanf("%d",&patientID);
		clearInputBuffer();
		ID=patientID;
	}
	u8 slotID;
	printf("please enter number of slot you want to reserve : ");
	fflush(stdout);	
	scanf("%d",&slotID);	
	clearInputBuffer();
	if(validSolt(slotID)==1){
		printf("Slot %s with slot ID %d reserved for patient ID %d.\n",slots[slotID-1].time,slots[slotID-1].id,ID);
		slots[slotID-1].isAvailable=0;
		slots[slotID-1].reservedForPatient=ID;
		patient* current=idSearch(&head,ID);
		current->reservedSlot=slotID;
	}else{
		printf("Invalid slot ID or slot already reserved.\n");
	}

}

//////////////////////////////4-Cancel reservation////////////////////////////////////
void cancelReservation(void){
	u32 patientID;
	printf("Please enter the ID of the patient to cancel the reservation: ");
	fflush(stdout);
	scanf("%d",&patientID);
	clearInputBuffer();

	while(idSearch(&head,patientID)==NULL){
		printf("You enter invalid ID,there is no patient with this ID to cancel reservation for him,please try to enter patient ID again : ");
		fflush(stdout);
		scanf("%d",&patientID);
		clearInputBuffer();
	}
	patient *selectedPatient =idSearch(&head,patientID);
	slots[(selectedPatient->reservedSlot)-1].isAvailable=1;
	////another way
	for(u8 i=0;i<5;i++){
		if(slots[i].reservedForPatient==patientID){
			slots[i].isAvailable=1;
			break;
		}
	}
	printf("Reservation Canceled completely\n");

}
///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////User Mode/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void UserMode(void){
	printf("Welcome to user mode!\n");	
	//user features
	feature_selection_for_user();	
}
void feature_selection_for_user(void){
	printf("----------------------------------------------------\n");

	printf("To View patient record enter : 1\n");
	printf("To View today reservations enter : 2\n");
	u8 feature;
	printf("Please choose a feature : ");
	fflush(stdout);
	scanf("%d",&feature);
	printf("----------------------------------------------------\n");
	clearInputBuffer();
	switch(feature){
	case 1:
		//View patient record
		view_patient_record();
		
		break;
	case 2:
		//View today’s reservations
		 view_today_reservations();
		break;
		
	}
}
//////////////////////////////1-View patient record////////////////////////////////////

void view_patient_record(void){
	u32 patientID;
	printf("Please enter the ID of the patient to cancel the reservation: ");
	fflush(stdout);
	scanf("%d",&patientID);
	clearInputBuffer();

	while(idSearch(&head,patientID)==NULL){
		printf("You enter invalid ID,there is no patient with this ID to view his record,please try to enter patient ID again : ");
		fflush(stdout);
		scanf("%d",&patientID);
		clearInputBuffer();
	}
	patient *selectedPatient =idSearch(&head,patientID);
	printf("The basic information for patient of ID = %d :\n",patientID);
	printf("Patient name is : %s\n",selectedPatient->name);
	printf("Patient age is : %d\n",selectedPatient->age);
	printf("Patient gender is : %c\n",selectedPatient->gender);
	

}

//////////////////////////////2-View today’s reservations//////////////////////////////

void view_today_reservations(void){
	printf("Today reservation : \n");
	for(u8 i=0;i<5;i++){
		if(slots[i].isAvailable==0){
			printf("Slot %s reserved for patient ID %d.\n",slots[i].time,slots[i].reservedForPatient);
		}
	}
}

