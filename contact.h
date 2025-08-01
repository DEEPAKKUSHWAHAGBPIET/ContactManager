// contact.h
#ifndef CONTACT_H
#define CONTACT_H

#define MAX_NAME 50
#define MAX_PHONE 15
#define MAX_EMAIL 50

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} Contact;

extern int contactCount;
extern Contact* contacts;

void loadContactsFromFile();
void saveContactsToFile();
void addContact();
void viewAllContacts();
void searchContactByName();
void searchContactByNumber();
void updateContact();
void deleteContact();
void sortContactsByName();
void importContactsFromCSV(const char* filename);
void exportContactsToCSV(const char* filename);

#endif
