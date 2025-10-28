# 🛫 Airline Reservation System (C++) – OOP Seminar Project

This project is a **console-based airline reservation system** written entirely in **C++** as part of a **university OOP seminar project**.  
It demonstrates key **Object-Oriented Programming principles** such as **encapsulation**, **inheritance**, **polymorphism**, and **abstraction** — all implemented within a single `.cpp` source file.

---

## 📚 Overview
The system allows users to:
- Add and manage flights  
- Make and cancel reservations  
- View passenger and flight details  
- Store and load data from files  

All logic, classes, and file handling are implemented in a single source file for simplicity.

---

## 🧠 Object-Oriented Concepts Used

| Concept | Where It’s Used | Description |
|----------|----------------|--------------|
| **Encapsulation** | Private attributes in classes like `Flight`, `Passenger`, and `Reservation` are accessed through public methods. | Protects data and ensures control over how attributes are read or modified. |
| **Inheritance** | `Ticket` class serves as a base, with subclasses such as `EconomyTicket` or `BusinessTicket`. | Demonstrates code reuse and specialization of behavior. |
| **Polymorphism** | Virtual methods (e.g., `calculatePrice()`) overridden in derived ticket classes. | Allows the same function call to behave differently depending on object type. |
| **Abstraction** | Abstract base class (`Ticket`) defines pure virtual methods for child classes. | Hides complex details and provides a unified interface for ticket handling. |
| **File Handling** | Used to store flight and reservation data persistently in text or binary files. | Demonstrates use of `fstream` for reading and writing data between sessions. |
| **Composition** | The `Reservation` class contains both a `Flight` and a `Passenger` object. | Represents the real-world relationship between flights and passengers. |

---

## 🗂️ Project Structure
```
oop-c-airline-reservation-system/
├── main.cpp      # Full implementation of the system
└── README.md     # Project documentation
```

---

## 🛠️ How to Compile & Run

1️⃣ **Clone the repository**
```bash
git clone https://github.com/leonserka/oop-c-airline-reservation-system-.git
cd oop-c-airline-reservation-system-
```

2️⃣ **Compile the project**
```bash
g++ main.cpp -o airline_system
```

3️⃣ **Run the executable**
```bash
./airline_system
```

---

## 🧩 Technologies & Concepts
- **Language:** C++ (C++11 or newer)  
- **Paradigm:** Object-Oriented Programming (OOP)  
- **File Handling:** Data persistence via `fstream`  
- **Interface:** Console-based menu system  

---

## 🚧 Future Improvements
- Separate classes into header (`.h`) and implementation (`.cpp`) files  
- Add GUI using Qt or SFML  
- Replace file storage with a database (e.g., SQLite/MySQL)  
- Add authentication system (admin/user roles)

---

## 📄 License
This project is open-source under the MIT License — feel free to use, modify, and learn from it.

---

## ✍️ Author
**Leon Serka**  
[https://github.com/leonserka](https://github.com/leonserka)
