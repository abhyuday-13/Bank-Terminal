# 💳 Bank Terminal (Cpp)

---

## 📚 Table of Contents

- [💳 Bank Terminal (Cpp)](#-bank-terminal-cpp)
  - [📚 Table of Contents](#-table-of-contents)
  - [📖 Introduction](#-introduction)
  - [✨ Features](#-features)
  - [🚀 Getting Started](#-getting-started)
    - [🔧 Prerequisites](#-prerequisites)
    - [📅 Installation](#-installation)
    - [💻 Running the Program](#-running-the-program)
  - [🧑‍💼 Usage](#-usage)
    - [🏦 Sample Interaction](#-sample-interaction)
  - [📁 Project Structure](#-project-structure)
  - [🤝 Contributing](#-contributing)
  - [🧠 Future Improvements \& Ideas](#-future-improvements--ideas)
  - [📃 License](#-license)
  - [🙏 Acknowledgments](#-acknowledgments)

---

## 📖 Introduction

**Bank Terminal (Cpp)** is a command-line banking simulation built with C++.
It lets users create accounts, authenticate via secure PIN, and perform banking actions like deposits, withdrawals, and balance checks — all through a fun, interactive terminal UI!

This project showcases file handling, OOP concepts, input validation, and CLI UX — a perfect mini-project for CS students and curious devs!

---

## ✨ Features

- 🆕 **Account Creation** – Sign up with your name, username, PIN, and an opening balance  
- 🔐 **PIN Authentication** – 4-digit secure login with PIN confirmation  
- 💰 **Deposit Funds** – Deposit money and get instant balance updates  
- 💸 **Withdraw Funds** – Withdraw with live validation  
- 🧾 **Transaction Receipts** – Printed with timestamps and reference numbers  
- 💼 **Balance Inquiry** – View your current balance  
- 📁 **Persistent Storage** – All data saved in `users.txt`  
- 🎨 **Animations & Color Formatting** – Eye-pleasing terminal output  
- 🚧 **Modular & Extendable** – Future support planned for logs, deletion, etc.

---

## 🚀 Getting Started

### 🔧 Prerequisites

- C++17 compiler (`g++`, `clang++`, or Visual Studio)
- A terminal or command prompt

### 📅 Installation

1. **Clone this repository**

```bash
git clone https://github.com/abhyuday-13/Bank-Terminal.git
cd Bank-Terminal
```

2. **Compile the program**

```bash
g++ -std=c++17 -o bank_terminal bank_terminal.cpp
```

### 💻 Running the Program

On Linux/macOS:

```bash
./bank_terminal
```

On Windows:

```bash
.\bank_terminal.exe
```

---

## 🧑‍💼 Usage

Just run it and follow the menu!

### 🏦 Sample Interaction

```text
===========================
   Bank of Boom & Busts
===========================
1. Login
2. Create New Account
3. Exit
===========================
Enter your choice: 2
Enter Your Full Name: John Doe
Enter username: johnd
Set a 4-digit PIN: 1234
Confirm your PIN: 1234
Initial deposit amount ($): 500
Account created successfully!
Name: John Doe
Username: johnd
Balance: $500.00
```

After login:

```text
+-----------------------------+
|     Banking Options         |
+-----------------------------+
| 1. Deposit                  |
| 2. Withdraw                 |
| 3. Check Balance            |
| 4. Logout                   |
+-----------------------------+
Enter Your Choice: 1
Enter amount to deposit: $250
-------- Transaction Receipt --------
Transaction Type: Deposit
Amount: $250.00
New Balance: $750.00
Date: Jul 04 2025  Time: 15:45:12
Bank Ref: #482391
-------------------------------------
```

---

## 📁 Project Structure

```text
Bank-Terminal-Cpp/
│
├── bank_terminal.cpp     # Main source file
├── bank_terminal.exe     # Compiled Windows binary (optional)
├── users.txt             # Data file (auto-generated on runtime)
├── README.md             # This file!
```

---

## 🤝 Contributing

Contributions are welcome! 🙌

1. Fork the repo  
2. Create a new branch: `git checkout -b feature/awesome-stuff`  
3. Commit changes: `git commit -m "Add cool stuff"`  
4. Push your branch: `git push origin feature/awesome-stuff`  
5. Open a Pull Request  

---

## 🧠 Future Improvements & Ideas

- 🔒 Encrypted PIN storage  
- 👁️ Masked input field for PIN entry  
- 🔁 Login retry limits  
- 💹 Comma-separated currency formatting ($10,000.00)  
- 📊 CSV import/export support  
- 🕒 Transaction history logs  
- 🧱 Full OOP-based class refactor (Bank, Account, Transaction, etc.)  

---

## 📃 License

This project is licensed under the [MIT License](LICENSE).

---

## 🙏 Acknowledgments

- Inspired by classic CLI finance sims  
- Built with ❤️ in C++ to master file I/O and OOP  
- Dedicated to learners and hobby coders like YOU! 💻✨
>
