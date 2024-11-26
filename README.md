# 🏦 Bank Extension 2 - Client Management System 💼

> **A console-based application for managing client data with advanced features such as transaction tracking, client management, and file storage. 🛠️**

---

## 🌟 Project Overview

Welcome to **Bank Extension 2**, an improved version of the Bank Client Management System. This console-based C++ application provides an intuitive interface for administrators to manage clients, track transactions, handle deposits and withdrawals, and maintain a complete transaction history. All client and transaction data is securely stored in a text file (`Client.txt`), ensuring persistence across sessions.

---

## ✨ Features

### 👥 **Client Management**
- ➕ **Add New Clients**: Input client details including account number, name, phone number, and initial balance.
- 📝 **Update Client Information**: Modify existing client records such as name, phone number, and balance.
- ❌ **Delete Clients**: Remove clients from the system by specifying their account number.
- 🔍 **Search for Clients**: Easily locate clients by account number and view their details.
- 🗂️ **View All Clients**: Display a list of all clients currently stored in the system.

### 💸 **Transaction Management**
- 💰 **Deposit Funds**: Add funds to a client's account. Every deposit is recorded in the transaction history.
- 💸 **Withdraw Funds**: Allow withdrawals, ensuring sufficient balance, and log every transaction for transparency.
  
### 📜 **Transaction History**
- 🗂️ **Track Transactions**: View a complete history of deposits and withdrawals for each client.
- 🗓️ **Transaction Records**: Transactions include date, amount, and type (deposit/withdrawal).

### 💾 **Data Persistence**
- 📝 All client and transaction data is saved in a file (`Client.txt`), ensuring persistence across multiple program runs and sessions.

---

## ⚙️ How It Works

### Core Components
1. **User Interaction**:
   - Administrators interact with a simple console menu to select operations like Add, Update, Delete, Deposit, Withdraw, and View Transaction History.
   - User inputs are validated for correctness before being processed.

2. **Operations**:
   - **Add Clients**: Administrators can add new clients to the system with their details and initial balance.
   - **Update Clients**: Modify existing client information, including name, phone number, and balance.
   - **Delete Clients**: Remove a client from the system by entering their account number.
   - **Search for Clients**: Locate a client using their account number.
   - **View All Clients**: Display a list of all clients in the system.
   - **Deposit**: Increase a client’s balance by adding funds to their account. Every deposit is logged with transaction details.
   - **Withdraw**: Reduce a client’s balance by processing a withdrawal, ensuring sufficient funds are available. Withdrawals are also logged.

3. **File Management**:
   - Client data and transaction history are stored in `Client.txt`, using delimiters for easy parsing and retrieval.
   - Efficient file handling ensures that data is properly read, written, and updated.

4. **Menu Navigation**:
   - A simple menu offers clear options to manage clients, perform transactions, view transaction history, and exit the program.
   - Users can also navigate back to previous menu options.

---

## 🎯 Learning Outcomes

This project demonstrates key concepts in C++:
- ✅ **File Handling**: Learn to store and manage data with file I/O operations, ensuring persistence.
- ✅ **Modular Design**: Use functions for different operations, improving code organization and reusability.
- ✅ **Input Validation**: Ensure all user inputs are properly validated to prevent errors and ensure data integrity.
- ✅ **Control Structures**: Apply loops, conditionals, and switch statements to handle logic in a structured way.
- ✅ **Transaction Management**: Implement a system to efficiently track both deposits and withdrawals for each client.

---

## 👥 Users

### 🧑‍💼 **Administrator**
- The **Administrator** has full access to the system and can:
  - Add, update, and delete clients.
  - View the list of all clients.
  - Perform deposit and withdrawal operations for any client.
  - View transaction histories for all clients.
  
### 👨‍💻 **Client**
- The **Client** can:
  - View their own account balance and transaction history.
  - Request deposits and withdrawals (with admin assistance).

---

## 🏁 Ready to Explore?

### 🚀 How to Run
1. **Download** the repository to your local machine.
2. **Compile** the C++ code using your preferred IDE or compiler (e.g., `g++` in terminal).
3. **Run** the compiled program and start managing clients and transactions!

