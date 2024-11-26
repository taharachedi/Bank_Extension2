# Bank Management System 💼💰

## Overview 🌟

This C++ program is a comprehensive **Bank Management System** that allows users to manage clients, transactions, and user accounts. The system is designed to handle various operations such as adding, deleting, updating, and finding clients, as well as managing user permissions and transactions.

## Features 🚀

### Client Management 🧑‍💼
- **List Clients**: Display a list of all clients. 📋
- **Add New Client**: Add a new client to the system. ➕
- **Delete Client**: Delete a client from the system. ❌
- **Update Client Info**: Update existing client information. 🔄
- **Find Client**: Search for a client by account number. 🔍

### Transaction Management 💸
- **Deposit**: Deposit money into a client's account. 💹
- **Withdraw**: Withdraw money from a client's account. 💸
- **Total Balances**: Display the total balance of all clients. 💰

### User Management 👤
- **List Users**: Display a list of all users. 📋
- **Add New User**: Add a new user to the system. ➕
- **Delete User**: Delete a user from the system. ❌
- **Update User**: Update existing user information. 🔄
- **Find User**: Search for a user by username. 🔍

### Permissions Management 🔐
- **Access Control**: Manage user permissions to control access to different functionalities. 🛡️

## Code Structure 🏗️

### Data Structures 📊
- **stClient**: Structure to hold client information.
- **stUser**: Structure to hold user information.

### Enumerations 🔢
- **enMainMenuePermissions**: Defines permissions for different functionalities.
- **enManageUsersMenueOptions**: Options for managing users.
- **enTransactionsMenueOptions**: Options for transaction management.
- **enMainMenueOptions**: Main menu options.

### Functions 🛠️
- Comprehensive functions for managing clients, users, transactions, and permissions (refer to the code comments for details).

## How to Run 🚀

1. **Compile the Code**: Use a C++ compiler to compile the code.
   ```bash
   g++ -o bank_management_system main.cpp
