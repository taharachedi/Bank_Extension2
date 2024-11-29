


# 🏦 Bank (Extension_1) 💼

> **A simple console-based application to manage client and user data with file storage and intuitive operations. 🛠️**

---

## 🌟 Project Overview

This C++ project simulates a **Bank Management System** 🏦 that allows the user (an administrator) to manage client and user data. The system provides functionalities like adding, deleting, updating, and viewing client and user information. Additionally, it supports financial transactions such as deposits and withdrawals, displays total balances, and ensures secure data persistence by storing all client and user details in text files.

---

## ✨ Features

### 📋 Client Management
- ➕ **Add New Clients**: Input details such as account number, name, phone number, PIN, and balance.
- 📝 **Update Client Details**: Modify existing records like names, phone numbers, and balances.
- ❌ **Delete Clients**: Remove clients from the system by specifying their account number.
- 🔍 **Search for Clients**: Easily locate clients by account number and display their details.
- 🗂️ **View All Clients**: Display a comprehensive list of all clients in the system.

### 💸 Transactions
- 💰 **Deposit Funds**: Add money to client accounts and log deposits.
- 💳 **Withdraw Money**: Deduct funds, ensuring sufficient balance.
- 📊 **View Total Balances**: Show overall bank holdings.

### 🔒 Data Security
- **Persistent Storage**: Client and user data is securely stored in `Client.txt` and `Users.txt` for future use.
- **Validation**: Enforce unique account numbers and accurate data entry.
- **Simple File-Based Database**: Efficiently manage all client and user data.


### 🧑‍💼 User Management
- ➕ **Add New Users**: Input details such as username, password, and permissions.
- 📝 **Update User Details**: Modify existing user records like passwords and permissions.
- ❌ **Delete Users**: Remove users from the system by specifying their username.
- 🔍 **Search for Users**: Easily locate users by username and display their details.
- 🗂️ **View All Users**: Display a comprehensive list of all users in the system.




### Permissions Management 🔐
- **Access Control**: Manage user permissions to control access to different functionalities. 🛡️


## 🔒 Permission Levels

The system supports multiple permission levels:
- 🌐 Full Access
- 📋 View Clients
- ➕ Add Clients
- ❌ Delete Clients
- ✏️ Update Clients
- 🔍 Find Clients
- 💱 Manage Transactions
- 👥 Manage Users

---

## ⚙️ How It Works

### Core Components
1. **User Input**:
   - Administrators interact with a console-based menu to select operations like Add, Update, Delete, Deposit, and Withdraw.
   - All user inputs are validated before being processed.

2. **Operations**:
   - **Add Clients/Users**: Administrators can enter new client/user details, including initial balance for clients.
   - **Update Records**: Modify client/user details, such as changing names, updating contact information, or adjusting balances.
   - **Delete Clients/Users**: Remove client/user records based on the account number/username.
   - **Search Clients/Users**: Retrieve a client's/user's information by entering their account number/username.
   - **View All Clients/Users**: Display a complete list of all client/user records stored in the system.
   - **Deposit**: Increase a client's balance by depositing funds into their account. Each deposit is recorded with the date, amount, and transaction type.
   - **Withdraw**: Withdraw funds from a client’s account, ensuring that the balance is sufficient.

3. **File Management**:
   - Client data are stored in `Client.txt`, using delimiters for easy parsing.
   - User data are stored in `Users.txt`, using delimiters for easy parsing.
   - Efficient file handling ensures data is accurately read, written, and updated in the text files.

4. **Menu Navigation**:
   - The menu offers easy navigation between operations, including options to add clients/users, perform transactions, and exit the program.
   - Users can also return to previous menus at any point.

---

## ⚙️ Technologies Used

- **Language**: C++
- **Programming Paradigm**: Procedural
- **File Handling**: File I/O for data persistence
- **Data Structures**: Vectors for dynamic client and user management

---


## 🎯 Learning Outcomes

This project demonstrates several key C++ programming concepts:
- ✅ **File Handling**: Learn to store and retrieve data using file I/O operations, ensuring persistence.
- ✅ **Modular Design**: Functions are used for each operation, making the code organized and reusable.
- ✅ **Error Handling**: Input validation and error checking ensure the integrity of data and smooth user experience.
- ✅ **Control Structures**: Utilize loops, conditionals, and switch statements for handling complex logic.
- ✅ **Transaction Management**: Efficiently manage both deposit and withdrawal transactions, and maintain a full history of all financial activities.

---

## 🏁 Ready to Explore?

### 🚀 How to Run
1. **Download** the repository to your local machine.
2. **Compile** the C++ code using your favorite IDE or compiler (e.g., `g++` in terminal).
3. **Run** the compiled program and begin managing client and user data and transactions with ease!

---

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


---



## 📚 Further Improvements

- 🔒 **Encryption**: Implement encryption for sensitive data like PIN codes and passwords.
- 🗄️ **Database Integration**: Replace text files with a relational database for more robust data management.
- 🖥️ **GUI**: Develop a graphical user interface for a more user-friendly and intuitive experience.
- 📜 **Logging**: Add a logging system to track all transactions and administrative activities for better monitoring and auditing.

---

## 📜 License

This project is open-source. Use it, modify it, share it! 🎉

Feel free to fork, modify, and use this project as a starting point for your own C++ applications! 🚀

- [ ] 📊 Enhanced reporting
- [ ] 🌐 Web interface
- [ ] 🔐 Two-factor authentication
- [ ] 💾 Database integration

**Enjoy Banking, Simplified!** 💳🏧

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

