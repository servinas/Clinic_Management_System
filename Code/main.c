/*
===================================================================================================
* Auther : Servinas Hassan Mohamed
* Object : Clinic mangement system
===================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"TYPESSTD.h"
#include"clinicManagement.h"

int main(void){
	intializeSlots();
	while(1){
		u8 mode;
		printf("----------------------------------------------------\n");

		printf("For admin mode enter : 1\n");
		printf("For user mode enter : 2\n");
		printf("If you want to exit enter : 3\n");
		printf("Please choose your mode : ");
		scanf("%d",&mode);
		printf("----------------------------------------------------\n");

		switch (mode){
		case 1:
			//admin mode 
			AdminMode();
			break;
		case 2:
			//user mode
			UserMode();
			break;
		case 3:
			//exiting....
			return 0;
			break;
			

		}

		
	}
	
	
	return 0;
} 