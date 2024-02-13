#ifndef CLINIC_MANAGEMENT_H
#define CLINIC_MANAGEMENT_H
typedef struct Patient{
	char name[60];
	u16 age;
	char gender;//F for femal and M for male
	u32 id;
	u32 reservedSlot;
	struct Patient *next;
}patient;
typedef struct Slot{
	u32 id;
	char time[30];
	u8 isAvailable;
	u32 reservedForPatient;
	
}slot;
extern patient *head;
void cancelReservation(void);
void intializeSlots(void);
patient* idSearch(patient**head ,u32 id);
u8 validSolt(u8 slotid);
void reserveSlot(void);
void displayAvailableSlots(void);
void valid_id(patient**head ,u32 id);
void Edit_patient_record();
void clearInputBuffer(void);
patient* add_new_patient(patient*head,char name[],char gender,u16 age,u32 id);
u8 is_patient_exist(patient**head,u32 id);
void addPatient(void);
void feature_selection_for_admin(void);
void AdminMode(void);
void view_today_reservations(void);
void view_patient_record(void);
void feature_selection_for_user(void);
void UserMode(void);

#endif