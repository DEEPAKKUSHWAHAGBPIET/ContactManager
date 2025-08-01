#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "utils.h"

int contactCount = 0;
Contact* contacts = NULL;
const char* FILENAME = "contacts.dat";
const char* FILENAME1 = "contacts.txt";

extern Contact *contacts;
extern int contactCount;

int isPhoneExists(const char *phone) {
     for (int i = 0; i < contactCount; i++) {
          if (strcmp(contacts[i].phone, phone) == 0)
          return 1;
     }
     return 0;
}

int isEmailExists(const char *email) {
     for (int i = 0; i < contactCount; i++) {
          if (strcmp(contacts[i].email, email) == 0)
          return 1;
     }
     return 0;
}

// ---------------- Load/Save from/to Binary File ----------------

void loadContactsFromFile() {
    FILE* file = fopen(FILENAME, "rb");
    if (file) {
        fseek(file, 0, SEEK_END);
        contactCount = ftell(file) / sizeof(Contact);
        rewind(file);

        contacts = (Contact*)malloc(contactCount * sizeof(Contact));
        fread(contacts, sizeof(Contact), contactCount, file);
        fclose(file);
    }
}

void saveContactsToFile() {
    FILE* file = fopen(FILENAME, "wb");
    if (file) {
        fwrite(contacts, sizeof(Contact), contactCount, file);
        fclose(file);
    }
}

// ---------------- Add Contact with Validation ----------------

void addContact() {
    Contact newContact;

    // Get Name (not empty)
    do {
        printf("Enter Name: ");
        getchar(); // clear buffer
        fgets(newContact.name, MAX_NAME, stdin);
        newContact.name[strcspn(newContact.name, "\n")] = 0;

        if (strlen(newContact.name) == 0)
            printf("Name cannot be empty. Try again.\n");

    } while (strlen(newContact.name) == 0);

    // Get and validate Phone
    do {
        printf("Enter 10-digit Phone Number: ");
        fgets(newContact.phone, MAX_PHONE, stdin);
        newContact.phone[strcspn(newContact.phone, "\n")] = 0;

        if (!isValidPhone(newContact.phone))
            printf("Invalid phone number. Try again.\n");
        else if (isPhoneExists(newContact.phone))
            printf("Phone number already exists. Enter a different number.\n");

    } while (!isValidPhone(newContact.phone) || isPhoneExists(newContact.phone));

    // Get and validate Email
    do {
        printf("Enter Email: ");
        fgets(newContact.email, MAX_EMAIL, stdin);
        newContact.email[strcspn(newContact.email, "\n")] = 0;

        if (!isValidEmail(newContact.email))
            printf("Invalid email format. Try again.\n");
        else if (isEmailExists(newContact.email))
            printf("Email already exists. Enter a different email.\n");

    } while (!isValidEmail(newContact.email) || isEmailExists(newContact.email));

    // Store Contact
    contacts = realloc(contacts, (contactCount + 1) * sizeof(Contact));
    contacts[contactCount++] = newContact;
    saveContactsToFile();

    printf("Contact added successfully.\n");
}

// ---------------- View, Search, Update, Delete ----------------

void viewAllContacts() {
    if (contactCount == 0) {
        printf("No contacts found.\n");
        return;
    }

    printf("\n---- Contact List ----\n");
    for (int i = 0; i < contactCount; i++) {
        printf("Name  : %s\n", contacts[i].name);
        printf("Phone : %s\n", contacts[i].phone);
        printf("Email : %s\n\n", contacts[i].email);
    }
}

void searchContactByName() {
    char name[MAX_NAME], tempName[MAX_NAME];
    printf("Enter name to search: ");
    getchar();
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = 0;
    strcpy(tempName, name);
    toLowerCase(tempName);

    int found = 0;
    for (int i = 0; i < contactCount; i++) {
        char currentName[MAX_NAME];
        strcpy(currentName, contacts[i].name);
        toLowerCase(currentName);
        if (strstr(currentName, tempName)) {
            printf("Name  : %s\n", contacts[i].name);
            printf("Phone : %s\n", contacts[i].phone);
            printf("Email : %s\n\n", contacts[i].email);
            found = 1;
        }
    }
    if (!found) printf("Contact not found.\n");
}

void searchContactByNumber() {
    char number[MAX_PHONE];
    printf("Enter phone number to search: ");
    getchar();
    fgets(number, MAX_PHONE, stdin);
    number[strcspn(number, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].phone, number) == 0) {
            printf("Name  : %s\n", contacts[i].name);
            printf("Phone : %s\n", contacts[i].phone);
            printf("Email : %s\n\n", contacts[i].email);
            found = 1;
        }
    }
    if (!found) printf("Contact not found.\n");
}

void updateContact() {
    char name[MAX_NAME];
    printf("Enter name of contact to update: ");
    getchar();
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            printf("Enter new Phone: ");
            fgets(contacts[i].phone, MAX_PHONE, stdin);
            contacts[i].phone[strcspn(contacts[i].phone, "\n")] = 0;

            printf("Enter new Email: ");
            fgets(contacts[i].email, MAX_EMAIL, stdin);
            contacts[i].email[strcspn(contacts[i].email, "\n")] = 0;

            saveContactsToFile();
            printf("Contact updated successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

void deleteContact() {
    char name[MAX_NAME];
    printf("Enter name of contact to delete: ");
    getchar();
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            for (int j = i; j < contactCount - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            contactCount--;
            contacts = realloc(contacts, contactCount * sizeof(Contact));
            saveContactsToFile();
            printf("Contact deleted successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

int compareContacts(const void* a, const void* b) {
    return strcmp(((Contact*)a)->name, ((Contact*)b)->name);
}

void sortContactsByName() {
    if (contactCount == 0) {
        printf("No contacts to sort.\n");
        return;
    }

    qsort(contacts, contactCount, sizeof(Contact), compareContacts);
    saveContactsToFile();
    printf("Contacts sorted by name.\n");
}

// ---------------- CSV Import/Export ----------------

void importContactsFromCSV(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open %s\n", filename);
        return;
    }

    char line[200];
    int importedCount = 0, skippedCount = 0;

    while (fgets(line, sizeof(line), file)) {
        Contact c;
        if (sscanf(line, "%49[^,],%14[^,],%49[^\n]", c.name, c.phone, c.email) == 3) {
            if (isValidPhone(c.phone) && isValidEmail(c.email)) {

                // Check for duplicate phone and email
                int duplicate = 0;
                for (int i = 0; i < contactCount; i++) {
                    if (strcmp(contacts[i].phone, c.phone) == 0 || strcmp(contacts[i].email, c.email) == 0) {
                        duplicate = 1;
                        break;
                    }
                }

                if (!duplicate) {
                    contacts = realloc(contacts, (contactCount + 1) * sizeof(Contact));
                    contacts[contactCount++] = c;
                    importedCount++;
                } else {
                    skippedCount++;
                }
            } else {
                skippedCount++;
            }
        }
    }

    fclose(file);
    saveContactsToFile();
    printf("Imported %d new contacts from %s, skipped %d duplicates or invalid entries.\n", importedCount, filename, skippedCount);
}


void exportContactsToCSV(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Could not write to %s\n", filename);
        return;
    }

    for (int i = 0; i < contactCount; i++) {
        fprintf(file, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }

    fclose(file);
    printf("Contacts exported to %s\n", filename);
}
