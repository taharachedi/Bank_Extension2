#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Client.txt";
const string UsersFileName = "Users.txt";


enum enMainMenuePermissions { 
    pAll = -1, pListClients = 1, pAddNewCLient = 2, pDeleteClient = 4, pUpdateClient = 8,
    pFindClient = 16, pTransactions = 32, pManageUsers = 64
}; 

enum enManageUsersMenueOptions {
    eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
};

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };

enum enMainMenueOptions {
    eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClientInfo = 4, 
    eFindClient = 5, eShowTransactionsMenue = 6, eManageUsers = 7, Logout = 8
}; 

struct stUser {
    string UserName;
    string Password;
    int Permissions;

    bool Mark_User_For_Delete = false;
};

stUser CurrentUser;



void Show_Main_Menue_Screen();
void Show_Transactions_Menue_Screen();
void Show_Manage_Users_Menue_Screen(); 
bool Check_Access_Permissions(enMainMenuePermissions Permission);
void Login(); 
void Show_Access_Denied_Msg();  




struct stClient
{
    string Account_Number;
    string PIN_Code;
    string Name;
    string Phone;
    double Account_Balance;
    bool Mark_Client_For_Delete = false;
};


vector <string> Split_String(string S1, string Delimiter = "#//#") { 

    short Pos = 0;
    string sWord;

    vector <string> vString; 

    while ((Pos = S1.find(Delimiter)) != std::string::npos) {

        sWord = S1.substr(0, Pos);

        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, Pos + Delimiter.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}



stClient Convert_ClientLineData_To_Record(string Line, string Delimiter = "#//#") {

    vector <string> vRecord = Split_String(Line);
    stClient Client;

    Client.Account_Number = vRecord[0];
    Client.PIN_Code = vRecord[1];
    Client.Name = vRecord[2];
    Client.Phone = vRecord[3];
    Client.Account_Balance = stod(vRecord[4]); //Cast String To Double

    return Client;
}



vector <stClient> Load_Client_Data_From_File(string FileName) {

    fstream My_File;

    vector <stClient> vClient;
    string Line;
    stClient Client;

    My_File.open(FileName, ios::in);  // Read Mode

    if (My_File.is_open())
    {
        while (getline(My_File, Line)) {

            Client = Convert_ClientLineData_To_Record(Line);
            vClient.push_back(Client);
        }

        My_File.close();
    }

    return vClient;
}



void Print_Client_Record_Line(stClient Client) {

    cout << left << "|" << setw(15) << Client.Account_Number;
    cout << left << "|" << setw(10) << Client.PIN_Code;
    cout << left << "|" << setw(38) << Client.Name;
    cout << left << "|" << setw(12) << Client.Phone;
    cout << left << "|" << setw(12) << Client.Account_Balance;
}



void Show_Clients_List() {

    if (!Check_Access_Permissions(enMainMenuePermissions::pListClients))
    {
        Show_Access_Denied_Msg();   
        return;
    }

    vector <stClient> vClient = Load_Client_Data_From_File(ClientsFileName);

    cout << "\t\t\t Client List (" << vClient.size() << ") Client(s). \n";

    cout << "\n----------------------------------------------------------------------------------------\n";
    cout << left << "|" << setw(15) << "Account Number";
    cout << left << "|" << setw(10) << "PIN Code";
    cout << left << "|" << setw(38) << "Client Name";
    cout << left << "|" << setw(12) << "Phone";
    cout << left << "|" << setw(12) << "Balance";

    cout << "\n----------------------------------------------------------------------------------------\n";

    if (vClient.size() == 0)
    {
        cout << "\n\n\t\t\t No Clients Available in The System! ";
    }
    else
    {
        for (stClient& Client : vClient)
        {
            Print_Client_Record_Line(Client);
            cout << endl;
        }
    }

    cout << "\n----------------------------------------------------------------------------------------\n";
}




string Convert_ClientRecordData_To_Line(stClient Client, string Delimiter = "#//#") {

    string Line = "";

    Line += Client.Account_Number + Delimiter;
    Line += Client.PIN_Code + Delimiter;
    Line += Client.Name + Delimiter;
    Line += Client.Phone + Delimiter;
    Line += to_string(Client.Account_Balance);

    return Line;
}


bool Client_Exists_By_Account_Number(string Account_Number, string FileName) {

    fstream My_File;

    My_File.open(FileName, ios::in); // Read Mode

    if (My_File.is_open())
    {
        string Line;
        stClient Client;

        while (getline(My_File, Line)) {

            Client = Convert_ClientLineData_To_Record(Line); 

            if (Client.Account_Number == Account_Number)
            {
                My_File.close();
                return true;
            }

        }
        My_File.close();
    }

    return false;
}



stClient Read_NewClient() {

    stClient Client;

    cout << "\nEnter Account Number? ";
    getline(cin >> ws, Client.Account_Number);

    while (Client_Exists_By_Account_Number(Client.Account_Number, ClientsFileName)) {

        cout << "\nClient With [" << Client.Account_Number << "] Already Exists! Enter Another Account Number? ";
        getline(cin >> ws, Client.Account_Number);
    }


    cout << "\nEnter PIN Code? ";
    getline(cin, Client.PIN_Code);

    cout << "\nEnter Name? ";
    getline(cin, Client.Name);

    cout << "\nEnter Phone? ";
    getline(cin, Client.Phone);

    cout << "\nEnter Account Balance? ";
    cin >> Client.Account_Balance;


    return Client;
}


void Add_DataLine_To_File(string FileName, string Line) {

    fstream My_File;

    My_File.open(FileName, ios::out | ios::app);

    if (My_File.is_open())
    {
        My_File << Line << endl;

        My_File.close();
    }
}


void Add_New_Client() {

    stClient Client = Read_NewClient();

    Add_DataLine_To_File(ClientsFileName, Convert_ClientRecordData_To_Line(Client));
}



void Add_New_Clients() {

    char Answer = 'Y';

    do
    {
        cout << "Adding New Client : \n\n";

        Add_New_Client(); 

        cout << "\nClient Added Successfully, Do U Want To Add More Client ? (Y/N) ";
        cin >> Answer;

    } while (toupper(Answer) == 'Y');

}

void Show_Add_New_Clients_Screen() {

    if (!Check_Access_Permissions(enMainMenuePermissions::pAddNewCLient))
    {
        Show_Access_Denied_Msg();
        return;
    }

    cout << "\n----------------------------------------------\n";
    cout << "\t\t Add New CLients Screen ";
    cout << "\n----------------------------------------------\n";

    Add_New_Clients(); 
}




vector <stClient> Save_ClientData_To_File(string FileName, vector<stClient> vClient) {

    fstream My_File;
    string Line;

    My_File.open(FileName, ios::out);

    if (My_File.is_open())
    {
        for (stClient& Client : vClient)
        {
            if (Client.Mark_Client_For_Delete == false) {

                Line = Convert_ClientRecordData_To_Line(Client);
                My_File << Line << endl;
            }
        }

        My_File.close();
    }
    return vClient;
}



bool Find_Client_By_Account_Number(string Account_Number, vector <stClient> vClient, stClient& Client_Info) {

    for (stClient& Client : vClient)
    {
        if (Client.Account_Number == Account_Number) {

            Client_Info = Client;
            return true;
        }
    }
    return false;
}



bool Mark_Client_For_Delete_By_Account_Number(string Account_Number, vector<stClient>& vClient) {

    for (stClient& Client : vClient)
    {
        if (Client.Account_Number == Account_Number) {

            Client.Mark_Client_For_Delete = true;
            return true;
        }
    }
    return false;
}



string Read_Client_Account_Number() {
    string Account_Number = "";

    cout << "\nPlease Enter Account Number : ";
    cin >> Account_Number;

    return Account_Number;
}


void Print_Client_Card(stClient Client) {

    cout << "\nThe Following Are The Client Details : \n";

    cout << "\n----------------------------------------------\n";
    cout << "Account Number      : " << Client.Account_Number << endl;
    cout << "PIN Code            : " << Client.PIN_Code << endl;
    cout << "Name                : " << Client.Name << endl;
    cout << "Phone               : " << Client.Phone << endl;
    cout << "Account Balance     : " << Client.Account_Balance << endl;
    cout << "\n----------------------------------------------\n";
}

bool Delete_Client_By_Account_Number(string Account_Number, vector <stClient>& vClient) {

    stClient Client;
    char Answer = 'n';

    if (Find_Client_By_Account_Number(Account_Number, vClient, Client))
    {
        Print_Client_Card(Client);

        cout << "\n\nAre U Sure U Want Delete This Account :(Y/N) ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            Mark_Client_For_Delete_By_Account_Number(Account_Number, vClient);
            Save_ClientData_To_File(ClientsFileName, vClient);

            // Refresh
            vClient = Load_Client_Data_From_File(ClientsFileName);

            cout << "\n\nClient Deleted Successfully! ";
            return true;
        }
    }

    else
    {
        cout << "\nClient With Account Number [" << Account_Number << "] Not Found! ";
        return false;
    }

}


void Show_Delete_Client_Screen() {

    if (!Check_Access_Permissions(enMainMenuePermissions::pDeleteClient))
    {
        Show_Access_Denied_Msg();
        return;
    }

    cout << "\n--------------------------------------------------\n";
    cout << "\t\t Delete Client Screen ";
    cout << "\n--------------------------------------------------\n";

    string Account_Number = Read_Client_Account_Number();
    vector <stClient> vClient = Load_Client_Data_From_File(ClientsFileName);


    Delete_Client_By_Account_Number(Account_Number, vClient);
}





stClient Change_Client_Record(string Account_Number) {

    stClient Client;

    Client.Account_Number = Account_Number;

    cout << "\nEnter  PIN Code : ";
    getline(cin >> ws, Client.PIN_Code);

    cout << "\nEnter Name : ";
    getline(cin, Client.Name);

    cout << "\nEnter Phone : ";
    getline(cin, Client.Phone);

    cout << "\nEnter Account Balance : ";
    cin >> Client.Account_Balance;

    return Client;
}


bool Update_Client_Info_By_Account_Number(string Account_Number, vector<stClient>& vClient) {

    stClient Client;
    char Answer = 'n';

    if (Find_Client_By_Account_Number(Account_Number, vClient, Client))
    {
        Print_Client_Card(Client);

        cout << "\n\nAre U Sure U Want Update This Client? (Y/N) ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            for (stClient& C : vClient)
            {
                if (C.Account_Number == Account_Number)
                {
                    C = Change_Client_Record(Account_Number); 
                    break;
                }
            }

            Save_ClientData_To_File(ClientsFileName, vClient);

            cout << "\n\nClient Updated Successfully! ";
            return true;
        }

    }
    else
    {
        cout << "\nClient With Account Number (" << Account_Number << ") is Not Found! ";
        return false;
    }
}


void Show_Update_Client_Info_Screen() {

    if (!Check_Access_Permissions(enMainMenuePermissions::pUpdateClient))
    {
        Show_Access_Denied_Msg();
        return;
    }

    cout << "\n--------------------------------------------------\n";
    cout << "\t\t Update Client Info Screen ";
    cout << "\n--------------------------------------------------\n";

    string Account_Number = Read_Client_Account_Number();
    vector<stClient> vClient = Load_Client_Data_From_File(ClientsFileName);

    Update_Client_Info_By_Account_Number(Account_Number, vClient);
}






void Show_Find_Client_Screen() {

    if (!Check_Access_Permissions(enMainMenuePermissions::pFindClient))
    {
        Show_Access_Denied_Msg();
        return;
    }

    cout << "\n--------------------------------------------------\n";
    cout << "\t\t Find Client Screen ";
    cout << "\n--------------------------------------------------\n";

    string Account_Number = Read_Client_Account_Number();
    vector <stClient> vClient = Load_Client_Data_From_File(ClientsFileName);

    stClient Client;

    if (Find_Client_By_Account_Number(Account_Number, vClient, Client))
    {
        Print_Client_Card(Client);
    }
    else
    {
        cout << "\nClient With Account Number [" << Account_Number << "] is Not Found! ";
    }
}



void Show_End_Screen() {

    cout << "\n--------------------------------------------------\n";
    cout << "\t\t Program Ends : -)";
    cout << "\n--------------------------------------------------\n";
}



void Go_Back_To_Main_Menue() {

    cout << "\n\n\nPress Any Key To Go Back To Main Menue...\n";
    system("pause>0");


    Show_Main_Menue_Screen();
}



short Read_Main_Menue_Option() {

    short Choice = 1;

    do
    {
        cout << "\nChoose What Do U want To Do Twiiha ? [1 => 8]? \n";
        cin >> Choice;

    } while (Choice < 1 || Choice > 8);


    return Choice;
}


void Perform_Main_Menue_Option(enMainMenueOptions Option) {

    switch (Option)
    {

    case enMainMenueOptions::eListClients:

        system("cls");
        Show_Clients_List();
        Go_Back_To_Main_Menue();

        break;


    case enMainMenueOptions::eAddNewClient:

        system("cls");
        Show_Add_New_Clients_Screen();
        Go_Back_To_Main_Menue();

        break;


    case enMainMenueOptions::eDeleteClient:

        system("cls");
        Show_Delete_Client_Screen();
        Go_Back_To_Main_Menue();

        break;


    case enMainMenueOptions::eUpdateClientInfo:

        system("cls");
        Show_Update_Client_Info_Screen();
        Go_Back_To_Main_Menue();

        break;


    case enMainMenueOptions::eFindClient:

        system("cls");
        Show_Find_Client_Screen();
        Go_Back_To_Main_Menue();

        break;


    case enMainMenueOptions::eShowTransactionsMenue:

        system("cls");
        Show_Transactions_Menue_Screen();

        break;


    case enMainMenueOptions::eManageUsers:

        system("cls");
        Show_Manage_Users_Menue_Screen();

        break;


    case enMainMenueOptions::Logout:

        system("cls");
        Login();

        break;
    }

}




double Read_Deposit_Amount() {

    double Deposit = 0;

    cout << "\nPlease Enter Deposit Amount : ";
    cin >> Deposit;

    return Deposit;
}


bool Deposit_Balance_To_Client_By_Account_Number(string Account_Number, vector<stClient>& vClient, double Amount) {


    char Answer = 'n';

    cout << "\n\nAre U Sure U Want Perform This Transaction? (Y/N) ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {

        for (stClient& Client : vClient)
        {
            if (Client.Account_Number == Account_Number) {

                Client.Account_Balance += Amount;
                Save_ClientData_To_File(ClientsFileName, vClient);

                cout << "\n\nDone Successfully, New Balance = " << Client.Account_Balance;

                return true;
            }
        }

        return false;
    }

}


void Show_Deposit_Screen() {


    cout << "\n=================================================\n";
    cout << "\t\t Deposit Screen";
    cout << "\n=================================================\n";

    string Account_Number = Read_Client_Account_Number(); 
    vector <stClient> vClient = Load_Client_Data_From_File(ClientsFileName);

    stClient Client; 

    while (!Find_Client_By_Account_Number(Account_Number, vClient, Client)) {

        cout << "\nClient With [" << Account_Number << "] Does Not Exist! \n";
        Account_Number = Read_Client_Account_Number();
    }

    Print_Client_Card(Client);

    double Deposit_Amount = Read_Deposit_Amount();

    Deposit_Balance_To_Client_By_Account_Number(Account_Number, vClient, Deposit_Amount);
}



double Read_Withdraw_Amount() {

    double Withdraw = 0;

    cout << "\nPlease Enter Withdraw Amount : ";
    cin >> Withdraw;

    return Withdraw;
}


void Show_Withdraw_Screen() {

    cout << "\n=================================================\n";
    cout << "\t\t Withdraw Screen";
    cout << "\n=================================================\n";

    string Account_Number = Read_Client_Account_Number();
    vector <stClient> vClient = Load_Client_Data_From_File(ClientsFileName);

    stClient Client;

    while (!Find_Client_By_Account_Number(Account_Number, vClient, Client)) {

        cout << "\nClient With [" << Account_Number << "] Does Not Exist! \n";

        Account_Number = Read_Client_Account_Number();
    }

    Print_Client_Card(Client);

    double Withdraw_Amount = Read_Withdraw_Amount();


    while (Withdraw_Amount > Client.Account_Balance) {

        cout << "\nAmount Exceeds The Balance, U can Withdraw Up To : " << Client.Account_Balance;

        cout << "\nPlease Enter Another Amount : ";
        cin >> Withdraw_Amount;
    }


    Deposit_Balance_To_Client_By_Account_Number(Account_Number, vClient, Withdraw_Amount * -1);
}


void Print_Client_Record_Balance_Line(stClient Client) {

    cout << left << "| " << setw(18) << Client.Account_Number;
    cout << left << "| " << setw(28) << Client.Name;
    cout << left << "| " << setw(12) << Client.Account_Balance;
}



void Show_Total_Balances_Screen() {

    vector <stClient> vClient = Load_Client_Data_From_File(ClientsFileName);

    cout << "\n\t\t\t Balances List (" << vClient.size() << ") Client(s).";

    cout << "\n-------------------------------------------------------------\n";

    cout << left << "| " << setw(18) << " Account Number";
    cout << left << "| " << setw(28) << " Client Name";
    cout << left << "| " << setw(12) << " Balance";

    cout << "\n-------------------------------------------------------------\n";

    double Total_Balances = 0;

    if (vClient.size() == 0)
    {
        cout << "\n\n\t\t\t No Clients Available in The System! ";
    }

    else
    {

        for (stClient& Client : vClient)
        {
            Total_Balances += Client.Account_Balance;

            Print_Client_Record_Balance_Line(Client);
            cout << endl;
        }
    }

    cout << "\n-------------------------------------------------------------\n";

    cout << "\n\t\t\t  Total Balances = " << Total_Balances << endl;
}



void Go_Back_To_Transactions_Menue() {

    cout << "\n\n\nPress Any Key To Go Back To Transactions Menue...\n";
    system("pause>0");

    Show_Transactions_Menue_Screen();
}



short Read_Transactions_Menue_Option() {

    short Choice = 1;

    do
    {
        cout << "\nChoose What Do U want To Do Twiiha ? [1 => 4]? \n";
        cin >> Choice;

    } while (Choice < 1 || Choice > 4);

    return Choice;
}



void Perform_Transactions_Menue_Option(enTransactionsMenueOptions Option) {

    switch (Option)
    {
    case enTransactionsMenueOptions::eDeposit:

        system("cls");
        Show_Deposit_Screen();
        Go_Back_To_Transactions_Menue();

        break;

    case enTransactionsMenueOptions::eWithdraw:

        system("cls");
        Show_Withdraw_Screen();
        Go_Back_To_Transactions_Menue();

        break;

    case enTransactionsMenueOptions::eShowTotalBalance:

        system("cls");
        Show_Total_Balances_Screen();
        Go_Back_To_Transactions_Menue();

        break;

    case enTransactionsMenueOptions::eShowMainMenue:

        Show_Main_Menue_Screen();

    }

}




void Show_Transactions_Menue_Screen() {

    if (!Check_Access_Permissions(enMainMenuePermissions::pTransactions))
    {
        Show_Access_Denied_Msg();
        Go_Back_To_Main_Menue();
        return;
    }

    system("cls");

    cout << "\n=================================================\n";
    cout << "\t\tTransactions Menue Screen";
    cout << "\n=================================================\n";


    cout << "\t [1] Deposit. \n";
    cout << "\t [2] Withdraw. \n";
    cout << "\t [3] Total balances. \n";
    cout << "\t [4] Main Menue. \n";

    cout << "\n=================================================\n";


    Perform_Transactions_Menue_Option((enTransactionsMenueOptions)Read_Transactions_Menue_Option());
}






stUser Convert_UserLineData_To_Record(string Line, string Delimiter = "#//#") {

    vector <string> vUser = Split_String(Line);
    stUser User;

    User.UserName = vUser[0];
    User.Password = vUser[1];
    User.Permissions = stoi(vUser[2]);

    return User;
}



vector <stUser> Load_User_Data_From_File(string FileName) {

    vector <stUser> vUser;

    fstream My_File;
    My_File.open(FileName, ios::in); 

    if (My_File.is_open())
    {
        string Line;
        stUser User;

        while (getline(My_File, Line)) {

            User = Convert_UserLineData_To_Record(Line);
            vUser.push_back(User);
        }
        My_File.close();
    }
    return vUser;
}





void Print_User_Record_Line(stUser User) {

    cout << "|" << left << setw(18) << User.UserName;
    cout << "|" << left << setw(10) << User.Password;
    cout << "|" << left << setw(10) << User.Permissions;
}

void Show_Users_List() {

    vector <stUser> vUser = Load_User_Data_From_File(UsersFileName); 

    cout << "\n\t\t  Users List (" << vUser.size() << ") User(s). ";

    cout << "\n-----------------------------------------------------\n";

    cout << "|" << left << setw(18) << "UserName";
    cout << "|" << left << setw(10) << "Password";
    cout << "|" << left << setw(10) << "Permission";

    cout << "\n-----------------------------------------------------\n";


    if (vUser.size() == 0)
    {
        cout << "\n\n\t\t\t No Users Available in The System! ";
    }
    else
    {
        for (stUser& User : vUser)
        {
            Print_User_Record_Line(User);
            cout << endl;
        }
    }

    cout << "\n-----------------------------------------------------\n";
}



string Convert_UserRecordData_To_Line(stUser User, string Delimiter = "#//#") {

    string Line = "";

    Line += User.UserName + Delimiter;
    Line += User.Password + Delimiter;
    Line += to_string(User.Permissions);

    return Line;
}


bool User_Exists_By_UserName(string UserName, string FileName) {

    fstream My_File;

    My_File.open(FileName, ios::in);

    if (My_File.is_open())
    {
        string Line;
        stUser User;

        while (getline(My_File, Line)) {

            User = Convert_UserLineData_To_Record(Line);

            if (User.UserName == UserName)
            {
                My_File.close();
                return true;
            }
        }
        My_File.close();
    }
    return false;
}




int Read_Permissions_ToSet() {

    int Permission = 0;
    char Answer = 'n';

    cout << "\nDo U Want To Give Full Access? (Y/N)? ";
    cin >> Answer; 

    if (toupper(Answer) == 'Y')
    {
        return -1; 
    }

    cout << "\nDo U Want To Give Access To : \n";   

    cout << "\nShow Client List? (Y/N)? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permission += enMainMenuePermissions::pListClients;


    cout << "\nAdd New Client? (Y/N)? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permission += enMainMenuePermissions::pAddNewCLient;

    cout << "\nDelete Client? (Y/N)? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permission += enMainMenuePermissions::pDeleteClient;

    cout << "\nUpdate Client? (Y/N)? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permission += enMainMenuePermissions::pUpdateClient;

    cout << "\nFind CLient? (Y/N)? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permission += enMainMenuePermissions::pFindClient;

    cout << "\nTransactions? (Y/N)? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permission += enMainMenuePermissions::pTransactions;

    cout << "\nManage Users? (Y/N)? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permission += enMainMenuePermissions::pManageUsers;



    return Permission;
}


stUser Read_New_User() {
    stUser User;

    cout << "Enter UserName? ";
    getline(cin >> ws, User.UserName);

    while (User_Exists_By_UserName(User.UserName, UsersFileName)) { 

        cout << "User With [" << User.UserName << "] Already Exists, Enter Another UserName? ";
        getline(cin >> ws, User.UserName);
    }

    cout << "Enter Password? ";
    getline(cin >> ws, User.Password);

    User.Permissions = Read_Permissions_ToSet();

    return User;
}


void Add_New_User() {

    stUser User = Read_New_User();

    Add_DataLine_To_File(UsersFileName, Convert_UserRecordData_To_Line(User));
}


void Add_New_Users() {

    char Choice = 'Y';

    do
    {
        cout << "\nAdding New User: \n\n";
        Add_New_User();

        cout << "\nUser Added Successfully, Do U Want To Add More Users(Y/N)? ";
        cin >> Choice;

    } while (toupper(Choice) == 'Y');

}



void Show_Add_New_User_Screen() {

    cout << "\n------------------------------------------\n";
    cout << "\t Add New User Screen ";
    cout << "\n------------------------------------------\n";

    Add_New_Users();
}



bool Find_User_By_Name(string UserName, vector<stUser> vUser, stUser& User_Info) {

    for (stUser& User : vUser)
    {
        if (User.UserName == UserName)
        {
            User_Info = User;
            return true;
        }

    }
    return false;
}


bool Mark_User_For_Delete_By_UserName(string UserName, vector<stUser>& vUser) {

    for (stUser& User : vUser)
    {
        if (User.UserName == UserName)
        {
            User.Mark_User_For_Delete = true;
            return true;
        }

    }
    return false;
}

vector<stUser> Save_UserData_To_File(string FileName,vector <stUser> vUser) {

    fstream My_File;
    string Line;

    My_File.open(FileName, ios::out); 

    if (My_File.is_open())
    {
        for (stUser& User : vUser)
        {
            if (User.Mark_User_For_Delete == false)
            {
                Line = Convert_UserRecordData_To_Line(User);
                My_File << Line << endl;
            }

        }
        My_File.close();
    }
    return vUser;
}


void Print_User_Card(stUser User) {

    cout << "\nThe Following are The User Details : \n";
    
    cout << "\n-------------------------------------";
    cout << "\n UserName    : " << User.UserName;
    cout << "\n Password    : " << User.Password;
    cout << "\n Permissions : " << User.Permissions;
    cout << "\n-------------------------------------\n";

}


bool Delete_User_By_UserName(string UserName,vector <stUser>& vUser) {

    if (UserName == "Admin") { 
        cout << "\n\nU Cannot Delete This User! Masd9tiiix";
        return false;
    }
        
    stUser User; 
    char Choice = 'n'; 

    if (Find_User_By_Name(UserName,vUser, User))
    {
        Print_User_Card(User);

        cout << "\n\nAre U Sure U Want Delete This User? (Y/N)? ";
        cin >> Choice;

        if (toupper(Choice) == 'Y')
        {
            Mark_User_For_Delete_By_UserName(UserName, vUser);
            Save_UserData_To_File(UsersFileName, vUser);

            // Refresh Clients
            vUser = Load_User_Data_From_File(UsersFileName);
            cout << "\n\nUser Deleted Successfully! ";
            return true;
        }

    }
    else
    {
        cout << "\nUser With UserName [" << UserName << "] is Not Found! ";
        return false;
    }
}

string Read_UserName() {

    string UserName = "";

    cout << "\nPlease Enter UserName? \n";
    getline(cin >> ws, UserName);

    return UserName;
}


void Show_Delete_Users_Screen() {

    cout << "\n------------------------------------------\n";
    cout << "\t Delete Users Screen ";
    cout << "\n------------------------------------------\n";

    string UserName = Read_UserName();
    vector<stUser> vUser = Load_User_Data_From_File(UsersFileName);

    Delete_User_By_UserName(UserName, vUser);
}



stUser Change_User_Record(string UserName) {

    stUser User;

    User.UserName = UserName;

    cout << "Enter Password? ";
    getline(cin >> ws, User.Password);

    User.Permissions = Read_Permissions_ToSet();

    return User;
}


bool Update_User_By_UserName(string UserName, vector <stUser>& vUser) {

    stUser User;
    char Choice = 'Y'; 

    if (Find_User_By_Name(UserName,vUser,User)) 
    {
        Print_User_Card(User);

        cout << "\n\nAre U Sure U Want Update This User? Y/N ? ";
        cin >> Choice;

        if (toupper(Choice) == 'Y')
        {
            for (stUser& U : vUser) 
            {
                if (U.UserName == UserName) { 

                    U = Change_User_Record(UserName); 
                    break;
                }
            }

            Save_UserData_To_File(UsersFileName, vUser);

            cout << "\n\nUser Updated Sucessefully! ";
            return true;
        }
    }

    else
    {
        cout << "\nUser With UserName [" << UserName << "] is Not Found! ";
        return false;
    }
}

void Show_Update_Users_Screen() {

    cout << "\n------------------------------------------\n";
    cout << "\t Update Users Screen ";
    cout << "\n------------------------------------------\n";

    string UserName = Read_UserName();
    vector<stUser> vUser = Load_User_Data_From_File(UsersFileName);

    Update_User_By_UserName(UserName, vUser);
}


void Show_Find_User_Screen() {

    cout << "\n------------------------------------------\n";
    cout << "\t Find Users Screen ";
    cout << "\n------------------------------------------\n";
    
    string UserName = Read_UserName();
    vector <stUser> vUser = Load_User_Data_From_File(UsersFileName);

    stUser User;  

    if (Find_User_By_Name(UserName, vUser, User)) 
    {
        Print_User_Card(User);
    }
    else
    {
        cout << "\n User With Name [" << UserName << "] is Not Found! ";

    }
}



bool Check_Access_Permissions(enMainMenuePermissions Permission) {

    if (CurrentUser.Permissions == enMainMenuePermissions::pAll)
        return true;

    if ((Permission & CurrentUser.Permissions) == Permission)
        return true;

    else
        return false;
    
}


void Show_Access_Denied_Msg() {

    cout << "\n------------------------------------------\n";
    cout << "Acces Denied, \nU Don't Have Permission To Do This, \nPlease Contact Ur Admin!";
    cout << "\n------------------------------------------\n";
}


void Back_To_Manage_Users_Menue_Screen() {

    cout << "\n\n\nPress Any Key To Go Back To Manage Users Menue Screen...\n";
    system("pause>0");

    Show_Manage_Users_Menue_Screen();
}



enManageUsersMenueOptions Read_Manage_Users_Menue_Option() {
    short Option;

    do
    {
        cout << "Choose What Do U want To Do Twiha? [1 To 6]? ";
        cin >> Option;

    } while (Option < 1 || Option > 6);

    return (enManageUsersMenueOptions)Option;
}



void Perform_Manage_Users_Menue_Screen_Option(enManageUsersMenueOptions Option) {

    switch (Option)
    {
    case enManageUsersMenueOptions::eListUsers:

        system("cls");
        Show_Users_List(); 
        Back_To_Manage_Users_Menue_Screen();

        break;

    case enManageUsersMenueOptions::eAddNewUser:

        system("cls");
        Show_Add_New_User_Screen();
        Back_To_Manage_Users_Menue_Screen();

        break;


    case enManageUsersMenueOptions::eDeleteUser:

        system("cls");
        Show_Delete_Users_Screen();
        Back_To_Manage_Users_Menue_Screen();

        break;

    case enManageUsersMenueOptions::eUpdateUser:

        system("cls");
        Show_Update_Users_Screen();
        Back_To_Manage_Users_Menue_Screen();

        break;

    case enManageUsersMenueOptions::eFindUser:

        system("cls");
        Show_Find_User_Screen(); 
        Back_To_Manage_Users_Menue_Screen();

        break;


    case enManageUsersMenueOptions::eMainMenue:

        Show_Main_Menue_Screen();

    }
}



void Show_Manage_Users_Menue_Screen() {

    if (!Check_Access_Permissions(enMainMenuePermissions::pManageUsers))
    {
        Show_Access_Denied_Msg();
        Go_Back_To_Main_Menue();
        return;
    }

    system("cls");

    cout << "\n=================================================\n";
    cout << "\t  Manage Users Menue Screen";
    cout << "\n=================================================\n";

    cout << "\t  [1] List Users. \n";
    cout << "\t  [2] Add New User. \n";
    cout << "\t  [3] Delete User. \n";
    cout << "\t  [4] Update User. \n";
    cout << "\t  [5] Find User. \n";
    cout << "\t  [6] Main Menue. ";

    cout << "\n=================================================\n";

    Perform_Manage_Users_Menue_Screen_Option((enManageUsersMenueOptions)Read_Manage_Users_Menue_Option());
}




void Show_Main_Menue_Screen() {

    system("cls");

    cout << "\n=================================================\n";
    cout << "\t\tMain Menue Screen";
    cout << "\n=================================================\n";

    cout << "\t [1] Show Client List.\n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client.\n";
    cout << "\t [4] Update Client Info.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Transactions. \n";
    cout << "\t [7] Manage Users.\n";
    cout << "\t [8] Logout. ";

    cout << "\n=================================================\n";
     
    Perform_Main_Menue_Option((enMainMenueOptions)Read_Main_Menue_Option());
}



void Show_Login_Screen() {

    system("cls");

    cout << "\n---------------------------------------------\n";
    cout << "\t\t Login Screen ";
    cout << "\n---------------------------------------------\n";
}


bool Find_User_By_UserName_And_Passwrod(string UserName, string Password, stUser& User_Info) {

    vector <stUser> vUser = Load_User_Data_From_File(UsersFileName);

    for (stUser& User : vUser)
    {
        if (User.UserName == UserName && User.Password == Password) {

            User_Info = User;
            return true;
        }

    }
    return false;
}


bool Load_User_Info(string UserName, string Passwrod) {

    if (Find_User_By_UserName_And_Passwrod(UserName, Passwrod, CurrentUser))
        return true;

    else
        return false;
}


void Login() {

    bool Login_Faild = false;
    string UserName, Password;

    do
    {
        Show_Login_Screen();

        if (Login_Faild) {
            cout << "Invalid UserName/Password! \n";
        }

        cout << "\nEnter UserName? ";
        getline(cin >> ws, UserName);

        cout << "Enter Password? ";
        getline(cin >> ws, Password);

        Login_Faild = !Load_User_Info(UserName, Password);

    } while (Login_Faild);

    Show_Main_Menue_Screen();
}



int main()
{
    system("color f3");

    Login();

    system("pause>0");
    return 0;
}