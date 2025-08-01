# 📇 Contact Manager in C

A simple contact management system written in C that allows users to add, view, search, update, delete, sort, import, and export contacts. Contacts are stored in a CSV file for persistent storage.

---

## ✨ Features

- ✅ Add New Contact
- ✅ View All Contacts
- ✅ Search by Name or Phone Number
- ✅ Update Contact Details
- ✅ Delete a Contact
- ✅ Sort Contacts by Name
- ✅ Import Contacts from CSV (with validation)
- ✅ Export Contacts to CSV
- ✅ Email and Phone number validation
- ✅ Duplicate checks (phone & email must be unique)

---

## 📁 Project Structure

contact_manager/
├── main.c // Entry point
├── contact.c // Core logic for contact operations
├── contact.h // Contact structure & function declarations
├── utils.c // Utility functions like validation
├── utils.h // Utility function declarations
├── contacts.csv // Stores contacts in CSV format
├── contacts.dat // (Optional) Old binary format (not used now)
└── README.md // Project overview



---

## 🧑‍💻 Build & Run

gcc main.c contact.c utils.c -o contact_manager.exe
contact_manager.exe


Notes:
Duplicate names are allowed, but name cannot be empty.
Phone numbers and email IDs must be unique.
