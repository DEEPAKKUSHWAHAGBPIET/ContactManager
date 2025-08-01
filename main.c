// main.c
#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

void menu() {
    int choice;
    do {
        printf("\n------ Contact Manager ------\n");
        printf("1. Add New Contact\n");
        printf("2. View All Contacts\n");
        printf("3. Search Contact by Name\n");
        printf("4. Search Contact by Number\n");
        printf("5. Update Contact\n");
        printf("6. Delete Contact\n");
        printf("7. Sort Contacts by Name\n");
        printf("8. Import from CSV\n");
        printf("9. Export to CSV\n");
        printf("10. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewAllContacts(); break;
            case 3: searchContactByName(); break;
            case 4: searchContactByNumber(); break;
            case 5: updateContact(); break;
            case 6: deleteContact(); break;
            case 7: sortContactsByName(); break;
            case 8: importContactsFromCSV("contactList.csv"); break;
            case 9: exportContactsToCSV("contacts.csv"); break;
            case 10: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 10);
}

int main() {
    loadContactsFromFile();
    menu();
    free(contacts);
    return 0;
}
