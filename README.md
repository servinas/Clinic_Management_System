# Clinic_Management_System

*Overview:*

This project implements a Clinic Management System in C programming language. It offers functionalities for both administrators and users. Administrators can perform tasks like adding new patient records, editing patient records, and reserving slots with the doctor. Users, on the other hand, can view their appointments and update their information.

*Features:*

_Admin Mode:_

1-Login: Administrators can log in with a default password (1234) and have three attempts to enter the correct password.
2-Add New Patient Record: Admins can add new patient records by providing basic information such as name, age, gender, and a unique ID. Duplicate IDs are not allowed.
3-Edit Patient Record: Admins can edit patient information by entering the patient's ID. If the ID exists, the system allows the admin to update the patient's details.
4-Reserve Slot with the Doctor: Admins can reserve a time slot with the doctor for a patient. The system displays available slots, and the admin can choose a slot for the patient. Once a slot is reserved, it is not available for further reservations.
_User Mode:_

1-View Appointments: Users can view their scheduled appointments with the doctor.
2-Update Information: Users can update their personal information like name, age, and gender.
