# 🚆 Train Ticket Booking System (C Project)

A console-based **Train Ticket Booking System** in C.  
This project demonstrates file handling, structures and CRUD operations for managing train and ticket data.

---

## 📌 Features
- Add new train details (number, name, route, timings, seats, price).
- Update existing train information while preserving booked seats.
- Display all trains with arrival/departure times, price, and seat availability.
- Delete train records safely.
- Search trains by source/destination and book tickets with automatic PNR generation.
- View ticket details using Train No. or PNR.
- Cancel tickets and restore seat availability.
- Input validation for time format, seat count, and gender.

---

## 🛠 Tech Stack
- **Language:** C
- **Data Storage:** Binary files (`train.dat`, `tickets.dat`)
- **Concepts Used:** Structures, File Handling, Validation Functions

---
## 🎯 Learning Outcomes
- Practical use of **structures** in C programming.  
- Handling **binary files** for persistent data storage.  
- Implementing **CRUD operations** in a real-world scenario.  
- Input validation and error handling in user-driven applications.  

---
## How to Compile & Run
```bash
# Compile
gcc ticket_booking.c -o ticket_booking

# Run
./ticket_booking
