#include <iostream>
#include <string>
#include <fstream>
#include <vector> 
#include <sstream>
#include <iomanip>  
#include <cmath>
#include <map>

using namespace std;

// struct for data format 
struct format  
{
    string fileName; // current file name
    bool rightFileExist = false;
    int col;
    int row;
    vector<string> titles;
    vector<int> canCompute;
    vector<vector<int>> data;
};

// struct for variables in correlation function
struct cor_Vars
{
    // x: data 1 
    // y: data 2
    double x_y_total = 0;
    double x_sqr_total = 0;
    double y_sqr_total = 0;
    double x_mean;
    double y_mean;
    double n; // num of elements
};

// FUNCTION 1----------------------------------------------------
bool num_Exist(string); //check if the password have numbers or not 
bool cap_Exist(string); //check if the password have capital letters or not 
bool small_Letter_Exist(string); //check if the password have small letters or not 
bool first_Char_Valid(string); //check if the password's first character is an interger 
bool validate(string pass);//function to validate if the password met the requirement

bool check_User_File_Exist(string);// check if file exist
void createAcc(ofstream &);
void loginAcc(bool & ,bool & ,string & , ofstream &);
void deleteAcc(ofstream &);
void changePass(string, ofstream &);

void display_Login_Menu();
void execute_Login_Menu(int, bool &, bool &, string &, format &, ofstream &);
void loginMenu(format, ofstream &);

// FUNCTION 2-----------------------------------------------------------------
// F2.1 ----------------------------------------------------------------------
void loadDataFile(format &, ofstream &);
void printData(format &, ofstream &);

string getFileName();

void get_Format_n_Data(format &);

vector<string> insert_Str_To_Vec(string);
vector<int> insert_Int_To_Vec(string);

int parseInt(string);
bool check_File_Exist(string);
bool errorExist(format &);

// F2.2 ----------------------------------------------------------------------
void saveData(format &, ofstream&);

// F2.3 ----------------------------------------------------------------------
void saveReport(format &,  ofstream &);

// F2.4 ----------------------------------------------------------------------
void saveHTMLReport(format & ,  ofstream &);

// F2.5 ----------------------------------------------------------------------
auto getTime()
{
    time_t t = time(nullptr);
    return put_time(localtime(&t), "%c");// " %F " couldnt work 
}

void log_Action(ofstream & log, string txt);


// FUNCTION 3-----------------------------------------------------------------
void swap(int & , int & );

void sort(vector<int> &);

double square(double); 

// F3.1 MINIMUM +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findMin(format & ,int ); 

// F3.2 MAXIMUM +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findMax(format & , int ); 

// F3.3 MEDIAN +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findMedian(format & , int ); 
double getMedian(vector<int>& );

// F3.4 MEAN +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findMean(format & , int ); 

// F3.5 VARIANCE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findVar(format & , int ); 

// F3.6 STANDARD DEVIATION +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findSTD(format & , int ); 

// F3.7 CORRELATION +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findCor(format & , int, int); 

string get_Cor_Table (format & , int , int ); 

cor_Vars get_Cor_Vars (format & , int , int );

// F3.8 FIND DISTINCT +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
string findDistinct(format &); 

// F3.9 HISTOGRAM +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
string plotGraph(format & , int ); 
string plot_Histo_Bar(int );

// FUNCTION 4 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
string parseStr(double x); 

string indent(string , int ); 

string get_Report_Content(string , double (*col_Func)(format &, int), format &);  

int getColumn(format &); 

void get2Columns(format &, int & , int & ); 

// F4.1 ----------------------------------------------------
void print_Menu_Opt();
void main_Menu(format &, ofstream &);

void print_Statistics_Opt();
void statisticsMenu(format &, ofstream & log);

void save_Menu(format &, ofstream &);

int getChoice(); 


// F4.3 ------------------------------------------------------------------------------------------------------- 
string get_Min_Report(format &); 

string get_Max_Report(format & ); 

string get_Median_Report(format & ); 

string get_Mean_Report(format & ); 

string get_Var_Report (format & ); 

string get_STD_Report (format & ); 

string get_Cor_Report (format & ); 

string get_Distinct_Report (format &); 

string get_Graph_Report (format &); 

string getReportHeader(format &); 

string get_Full_Report (format &); 

// F4.4 ------------------------------------------------------------------------------------------------------- 
string get_HTML_Report(format &);
string get_HTML_Header();
string get_HTML_Footer();
string HTML_Formatting(string);

string get_Saved_Report(format &, int);
void print_Save_Report_Menu();

int main()
{
    cout << left; // iomanip, setw allign left

    ofstream logFile("log.txt"); // file that stores logs
    format  format_1 ; // struct that has data format 
 
    loginMenu(format_1, logFile); // login menu + main program inside

    return 0;
}

// FUNCTION 1------------------------------------------------------------------

bool num_Exist(string pass) //check if the password have numbers or not 
{
    int count = 0; 
    for(int i = 0; i <= 9; i++)
    {    
        string str1 = to_string(i); 
        if (pass.find(str1) != std::string::npos) 
            count = 1; 
    } 
    if (count == 0)return false;

    return true; 
}

bool cap_Exist(string pass) //check if the password have capital letters or not 
{
        int count = 0; 
        for(int i = 65; i <= 90; i++) 
        {        
            char c = (char)i;   // Type casting 
            string str1(1, c);
              
            if (pass.find(str1) != std::string::npos) 
                count = 1; 
        } 
        if (count == 0) return false; 

        return true;
}

bool small_Letter_Exist(string pass) //check if the password have small letters or not 
{
    int count = 0; 
    for(int i = 90; i <= 122; i++)
    { 
        char c = (char)i; 
        string str1(1, c); 
  
        if (pass.find(str1) != std::string::npos)
        count = 1;
    } 
    if (count == 0) return false; 

    return true;
}

bool first_Char_Valid(string pass) //check if the password's first character is an interger 
{
    int count = 0;

    if(pass[0] != '1' && pass[0] != '2' && pass[0] != '3' &&pass[0] != '4' && pass[0] != '5' && 
       pass[0] != '6' && pass[0] != '7' && pass[0] != '8' && pass[0] != '9' && pass[0] != '0')
    {
        cout << pass[0] << endl;
        count = 1;
    }
    if (count == 0)return false;

    return true;
}

//function to validate if the password met the requirement
bool validate(string pass)
{
    // if something wrong , password is not valid , hence false
    if( !num_Exist(pass))return false;

    if( !cap_Exist(pass))return false;

    if( !small_Letter_Exist(pass))return false;

    if( !first_Char_Valid(pass))return false;
            
    // if nothing goes wrong, password is valid , hence true 
    return true; 
}

//-----------------------------------------------------------------------------------------------------

bool check_User_File_Exist(string username)// check if user file exist
{
    ifstream file("admins\\"+username+".txt"); 

    if(file.fail())
    {
        file.open("users\\"+username+".txt");

        if(file.fail())
        {
            file.close();
            return false;
        }
    }
        
    file.close();
    return true;
}

//Function to register a user (can only be accessed by admin)
void createAcc(ofstream & log)
{    
    string name, type, pass, stat;

    //Display header
    cout << endl << endl << "=================================" << endl << setw(25) << "USER REGISTRATION" << endl << "=================================" << endl;

    //Get username 
    cout << "Enter Username :" << endl;
    cin >> name;

    // loop until valid username is entered
    while(check_User_File_Exist(name))
    {
        cout << "-> Username already exist, returning to login screen" << endl << endl;
        return;
    }

    // get user type 
    cout << "Enter User Type : " << endl << "Administrator = [a]        Buyer = [b]" << endl << endl;
    cin >> type;

    // loop until "a" or "b" is chosen
    while(type != "a" && type != "b")
    {
        cout << "Enter a valid choice : " ;
        cin >> type;
    }

    cout << "Enter Password : " << endl;
    cin >> pass;

    // loop until correct password is entered
    while( !validate(pass))
    {
        cout << "-> Password must starts with a letter and contain a capital letter and a digit,\ntry again\n";
        cin >> pass; 
    }

    //Status is set to active by default and will be changed to deleted when admin use a function to delete it
    stat = "active";

    // input user data in file
    ofstream userData;
    if(type == "a") userData.open("admins\\"+ name + ".txt");
    else userData.open("users\\"+ name + ".txt");
           
    userData << name << endl << type << endl << pass << endl << stat;
    userData.close();

    cout << endl << endl << "-> Successfully Registered!" << endl << endl;
    log_Action(log, "Registered new account");
}

//Login function 
void loginAcc(bool &administrator ,bool &login ,string &current_User , ofstream & log)
{   
    string inputusername, inputpassword , name, type, pass , state;
    
    //Display header
    cout << endl << endl << "=================================" << endl << setw(20) << "USER LOGIN" << endl << "=================================" << endl;
    
    //Get user input of username and password
    cout << "Enter Username : " << endl;
    cin >> inputusername;
    cout << "Enter Password : " << endl;
    cin >> inputpassword;

    //open data files according to input username
    ifstream userData ("admins\\" + inputusername + ".txt");
    if(userData.fail()) userData.open("users\\" + inputusername + ".txt");
   
    userData >> name >> type >> pass >> state; 

    userData.close();

    //if file is found , compare input username and password with username and password in data file.
    if (name == inputusername && pass == inputpassword && state == "active")
    {
        login = true;
        cout << endl << "-> Logged in successfully!" << endl << "Welcome , " << inputusername << endl;
        log_Action(log, "Logged in");

        current_User = inputusername; 

        if (type == "a")                                 
            administrator = true;
        else
            administrator = false;
    }

    //if the user's status is deleted , then display different message
    else if (state == "deleted")
        cout << endl << "-> User has already been deleted by Admin." << endl << endl;

    else  //if not the same as the data in files or file is not found , display certain message
        cout << endl << "-> Username or Password is incorrect!" << endl << endl;
}

//function to delete user account (can only accessed by admin)
void deleteAcc(ofstream & log)
{
    string inputusername , name, type, pass , state;
    
    //display header
    cout << endl << endl;
    cout << "=================================" << endl << setw(24) << "DELETE USER ACCOUNT" << endl << "=================================" << endl;

    //get username
    cout << "Enter Username to be deleted: " << endl;
    cin >> inputusername;

    // if user doesnt exist, terminate function
    if( !check_User_File_Exist(inputusername))
    {
        cout << "-> User does not exist" << endl << endl;
        return;
    }
    // else:

    //search for file with the same name and open the file
    ifstream inputFile ("admins\\" + inputusername + ".txt");
    if(inputFile.fail()) inputFile.open("users\\" + inputusername + ".txt");

    inputFile >> name >> type >> pass >> state; 

    inputFile.close();

    ofstream outputFile;
    if(type == "a") outputFile.open("admins\\"+ name + ".txt");
    else outputFile.open("users\\"+ name + ".txt");

    outputFile << name << endl << type << endl << pass << endl << "deleted";
    outputFile.close();
    cout << endl << "-> User successfully deleted!" << endl << endl;
    log_Action(log, "Deleted account");
    outputFile.close();
}

//function to change user password 
void changePass(string current_User , ofstream & log)
{
    string username, inputpassword , newpass , name, type, pass , state;
    
    //display header
    cout << endl << endl << "=================================" << endl << setw(23) << "CHANGE PASSWORD" << endl << "=================================" << endl;

    //search for file with the same name and open the file
    ifstream userData ("admins\\" + current_User + ".txt");
    if(userData.fail()) userData.open("users\\" + current_User + ".txt");

    userData >> name >> type >> pass >> state; 

    userData.close();

    // get password
    cout << "Enter your current password : " << endl;
    cin >> inputpassword;

    // if wrong password, terminate this function
    if(inputpassword != pass)
    {
        cout << "-> Incorrect password, returning to login screen" << endl << endl;
        return;
    }

    // check if user still active
    if (state == "active")
    {
        cout << "Enter new password : " << endl;
        cin >> newpass;
        
        // loop until new password valid
        if( !validate(newpass))
        {
            cout <<  "-> Password must starts with a letter and contain a capital letter and a digit,\ntry again\n";
            cin >> newpass;
        }

        ofstream userData;
        if(type == "a") userData.open("admins\\"+ current_User + ".txt");
        else userData.open("users\\"+ current_User + ".txt");

        userData << name << endl << type << endl << newpass << endl << state;
        userData.close();
        cout << "-> Successfully changed user password!" << endl << endl;
        log_Action(log, "Changed account password");
    }
    else cout << "-> Unable to change password, as account has already been deleted" << endl << endl;
}

//---------------------------------------------------------------------------------------------------------------
void display_Login_Menu()
{
    cout << "What would you like to do?" << endl;
    cout << "1  -  Create User Account (admins Only)" << endl;
    cout << "2  -  Login to a User Account" << endl;
    cout << "3  -  Delete User Account (admins Only)" << endl;
    cout << "4  -  Change User Password" << endl;
    cout << endl;
    cout << "5  -  >>>> RUN MAIN PROGRAM <<<<" << endl;
    cout << endl;
    cout << "6  -  Logout" << endl;
    cout << "7  -  Exit" << endl;
    cout << endl;
}
void execute_Login_Menu(int choice, bool & administrator, bool & login, string & current_User, format & format_1, ofstream & log)
{
    switch(choice)
    {
        case 1: if(administrator == true && login == true) createAcc(log);
                else cout << "-> You are not logged or not an Admin\n\n";
                break;
        case 2: if(login == false) loginAcc(administrator , login , current_User, log);
                else cout << "-> You are already logged in , log out first before logging in again!\n\n";
                break;
        case 3: if(administrator == true && login == true) deleteAcc(log);
                else cout << "-> You are not logged or not an Admin\n\n";
                break;
        case 4: if(login == true) changePass(current_User, log);
                else cout << "-> You are not logged in\n\n";
                break;
        case 5: if(login == true){ log_Action(log,"Entered main program"); main_Menu(format_1, log); }
                else cout << "-> You are not logged in\n\n";
                break;
        case 6: if(login == true){ login = false; cout << "-> Successfully Logged out!\n\n"; log_Action(log, "Logged out"); }
                else cout << "-> You are not logged in\n\n";
                break;
        case 7: break; // exit
        default: cout << "-> invalid input\n\n"; break;
    }
}

void loginMenu(format format_1, ofstream & log)
{
    int choice;
    string current_User;
    bool administrator = false, login = false;
   
    while(choice != 7)
    {
        // print login screen header
        cout << "=================================" << endl << setw(20) << "LOGIN SCREEN" << endl << "=================================" << endl << endl;
 
        if (login == true) cout << setw(23) << "Logged in as : " << endl << setw(16) << current_User << endl << endl;
        else cout << " * Currently not logged in *" << endl << endl;
        
        display_Login_Menu();

        choice = getChoice();

        execute_Login_Menu(choice, administrator, login, current_User, format_1, log);
    }
}
// FUNCTION 2-----------------------------------------------------------------
// F2.1 ----------------------------------------------------------------------

void loadDataFile(format & format_1, ofstream &log)
{
    cout << "========================================================"<< endl;
    cout << "LOAD DATA" << endl << endl;

    // clear everything (should prob make a clear func, but asg is over so whatvr)
    format_1.fileName.clear();
    format_1.rightFileExist = false;
    format_1.col = 0;
    format_1.row = 0;
    format_1.titles.clear();
    format_1.canCompute.clear();
    format_1.data.clear();
    
    // get file name 
    format_1.fileName = getFileName();

    // check if file exists
    format_1.rightFileExist = check_File_Exist(format_1.fileName);
    if(format_1.rightFileExist)
    {
        // get data format & and data
        get_Format_n_Data (format_1);

        // check for data format error
        if(errorExist(format_1))
        {
            format_1.rightFileExist = false;
            cout << "-> File not loaded, data format error"<< endl <<  endl;
        }
        else
        {
            cout << "-> Data loaded" << endl << endl;
            log_Action(log, "Data loaded");
        }
    }
    else
    {   
        cout << "-> Failed to load file, file doesn't exist"<< endl << endl ;
    }
}
void printData(format & format_1, ofstream & log)
{
        int width = 10;
        cout << "=============================\nData" << endl;

         // print a line
        cout << "----";
        for (int i = 0; i < format_1.col*(width+1); i++)
            cout << '-';
        cout << endl;
        
        // print title
        cout << setw(4) << "Row" << "|";
        for (int i = 0; i < format_1.col; i++)
            cout << setw(width) << format_1.titles[i] << "|";
        cout << endl;
        
        // print a line
        cout << "----";
        for (int i = 0; i < format_1.col*(width+1); i++)
            cout << '-';
        cout << endl;

        // print the numbers
        for (int i = 0; i < format_1.row; i++ )
        {
            cout << setw(4) << i << '|';
            for(int k = 0; k < format_1.col; k++)
                cout << setw(width) << format_1.data[i][k] << "|";

            cout << endl;
        }
        log_Action(log, "Displayed data");
}
string getFileName()
{
    string fileName;

    cout << "Enter file name: ";
    cin >> fileName;
    cout << endl;

    return fileName; 
}

void get_Format_n_Data (format & format_1)// get format and data
{
    ifstream file (format_1.fileName); //open file
    string dummy; // stores data temporarily
    vector<int> row; //temporarily stores the data in a row

    // get format from file
    file >> dummy;
    format_1.col = parseInt(dummy);

    file >> dummy;
    format_1.titles = insert_Str_To_Vec(dummy);

    file >> dummy;
    format_1.canCompute = insert_Int_To_Vec(dummy);

    file >> dummy; 
    format_1.row = parseInt(dummy); 

    // get data
    while(getline(file, dummy))
    {
        if(dummy != "")
        {   
            row = insert_Int_To_Vec(dummy); // extract data from line, then insert to row vector
            format_1.data.push_back(row);  // insert each row into 2d vector
        }
    }

    file.close();
}

vector<string> insert_Str_To_Vec(string line)// used in getformat &()
{
    vector<string> row; // value to be returned
    string x; // temporarily stores each data from getline() func
    stringstream ss (line); // initialize stringstream

    // insert the data into row vector
    while(getline(ss, x,','))
        row.push_back(x); 

    return row;
}

vector<int> insert_Int_To_Vec(string line)// to convert a line from file into a row vector
{
    vector<int> row; // value to be returned
    string temp; // temporarily stores each data in a row
    stringstream ss (line); // initialize stringstream

    // insert the data into row vector
    while(getline(ss, temp,','))
        row.push_back(parseInt(temp)); 

    return row;
}

int parseInt(string x)// to convert string to integer
{
    int num;
    stringstream ss(x);
    ss >> num;
    return num;
}

bool check_File_Exist(string fileName)// check if file exist
{
    ifstream file(fileName);

    if(file.fail())
    {
        return false;
    }

    file.close();
    return true;
}

bool errorExist(format & format_1)// check if file has error (true = error exist)
{
    // check how many titles
    if(format_1.titles.size() != format_1.col)
        return true;

    // check how many canCompute
    if(format_1.canCompute.size() != format_1.col)
        return true;

    // check num of rows of data
    if(format_1.data.size() != format_1.row)
        return true;

    // check how many elements in a row of data
    for(int i = 0; i < format_1.data.size(); i++)
        if(format_1.data[i].size() != format_1.col)
            return true;

    // return false (no error)
    return false;
}

// F2.2 -----------------------------------------------------------------------------
void saveData(format & format_1, ofstream &log)// to save a separate copy of data file 
{
    cout << "--------------------------------------------------------"<< endl;
    cout << "SAVE AS"<< endl << endl;

    ifstream file1 (format_1.fileName);// open data file
    ofstream file2; // file to be saved
    string temp; // temporarily stores a line from data file

    string newFileName = getFileName(); // get new file name
    file2.open(newFileName); // open new file

    // copying data from one file_1 to file_2
    // 1. copy data format 
    for (int i = 0; i < 4; i++)
    {
        file1 >> temp;
        file2 << temp << endl;
    }
    
    // 2. copy data
    for(int i = 0; i < format_1.row; i++)
    {
        file1 >> temp;
        file2 << temp << endl;
    } 
    
    // close files
    file1.close();
    file2.close();

    // msg and log
    cout << "-> Data saved"<< endl << endl;
    log_Action(log, "Saved file");
}

// F2.3 -----------------------------------------------------------------------------
void saveReport(format & format_1, ofstream &log)// to save report in .txt, gets new file name and report content
{
        cout << "--------------------------------------------------------"<< endl;
        cout << "SAVE REPORT" << endl << endl;

        print_Save_Report_Menu();// print options

        int choice = getChoice();// choose what report to save

        if(choice >=1 && choice <= 9) // if choice valid, proceed to save report
        {
            // get new file name
            string fileName = getFileName();

            //open file to be saved
            ofstream file(fileName);

            // insert content
            file <<  get_Saved_Report(format_1,choice); 

            // close file
            file.close();

            // msg and log
            cout << "-> Report saved"<< endl << endl;
            log_Action(log, "Saved report");
        }
        else // if choice invalid , then fail to save report
        {
            cout << "-> Failed to save Report, invalid option"<< endl << endl;
        }
}

// F2.4-----------------------------------------------------------------------
void saveHTMLReport(format & format_1, ofstream &log)// to save report in HTML
{
    cout << "--------------------------------------------------------"<< endl;
    cout << "SAVE HTML REPORT" << endl << endl;

    // get new file name
    string fileName = getFileName();
    fileName += ".html";

    // open new file to save
    ofstream file(fileName);

    // insert content
    file << get_HTML_Report(format_1);

    // close file
    file.close();

    // msg and log
    cout << "-> HTML report saved" << endl << endl;
    log_Action(log, "Saved HTML report");
}

// F2.5 ----------------------------------------------------------------------
void log_Action(ofstream & log, string txt)
{
    log << getTime() << " " << txt << endl;
}

// FUNCTION 3 -------------------------------------------------------------
void swap(int & a, int & b)
{
    int temp = a;
    a = b;
    b = temp;
}

void sort(vector<int> & num)// sort vector
{
    int lowestNum;
    int lowestNumIndex;

    for (int i = 0; i < num.size(); i++)
    {
        lowestNum = num[i];
        lowestNumIndex = i;
        for (int k = i+1; k < num.size(); k++)
        {
            if(lowestNum > num[k])
            {
                lowestNum = num[k];
                lowestNumIndex = k;
            }
        }
        swap(num[i], num[lowestNumIndex]);
        //print(num);
    }
}

double square(double x) // squares a value 
{
    return x*x;
}

// F3.1 MINIMUM +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findMin(format & format_1, int column) // find minimum of a column
{
    int min = format_1.data[0][column];

    for (int i = 1; i < format_1.row; i++)
        if(min > format_1.data[i][column])    
            min = format_1.data[i][column];

    return min;
}

// F3.2 MAXIMUM +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findMax(format & format_1, int column) // find maximum of a column
{
    int max = format_1.data[0][column];

    for (int i = 1; i < format_1.row; i++)
        if(max < format_1.data[i][column])
            max = format_1.data[i][column];

    return max;
}

// F3.3 MEDIAN +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findMedian(format & format_1, int column) // finds median of a column
{
    vector <int> num;

    // extract desired column of data
    for (int i = 0; i < format_1.row; i++)
        num.push_back(format_1.data[i][column]);
    
    // sort that data
    sort(num);

    // get median of said line of data
    return getMedian(num);
}

double getMedian(vector<int>& num) // returns the median of a sorted list of numbers
{
    int midIndex = num.size()/2; ;

    if(num.size()% 2 == 1)//  odd size
        return num[midIndex];

    else // even size
        return double(num[midIndex-1] + num[midIndex])/2;
}

// F3.4 MEAN +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findMean(format & format_1, int column) // finds mean of a column
{
    double total = 0;

    for (int i = 0; i < format_1.row; i++)   
            total += format_1.data[i][column];

    return total/format_1.row;
}

// F3.5 VARIANCE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findVar(format & format_1, int column) // finds variance of a column
{
    double mean = findMean(format_1, column);

    double total = 0;

    for (int i = 0; i < format_1.row; i++)
        total += square((format_1.data[i][column]- mean));
    
    return total / (format_1.row-1);
}

// F3.6 STANDARD DEVIATION +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findSTD(format & format_1, int column) // finds std deviation of a column
{
    return sqrt(findVar(format_1, column));
}

// F3.7 CORRELATION +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double findCor(format & format_1, int col_1, int col_2) // returns correlation value
{
    double output; // value to retured

    cor_Vars v = get_Cor_Vars(format_1, col_1, col_2);

    // find correlation value
    output = (v.x_y_total - v.n * v.x_mean * v.y_mean) /
        (sqrt( v.x_sqr_total - v.n*square(v.x_mean)) * sqrt( v.y_sqr_total - v.n*square(v.y_mean))); 
    
    return output;
    
}
string get_Cor_Table (format & format_1, int col_1, int col_2) // returns correlation variable table
{
    string output; // string to be returned
    cor_Vars v = get_Cor_Vars(format_1, col_1, col_2);
    int data_1, data_2;

    // header
    output += "-----------------------------------\n";
    output += "|x     |y     |xy    |x^2   |y^2   \n";
    output += "-----------------------------------\n";

    // the numbers
    for (int i = 0; i < format_1.row; i++)
    {
        data_1 = format_1.data[i][col_1];
        data_2 = format_1.data[i][col_2];

        output +=   "|" + indent(parseStr(data_1),6) + 
                    "|" + indent(parseStr(data_2),6) +
                    "|" + indent(parseStr(data_1*data_2),6) +
                    "|" + indent(parseStr(square(data_1)),6) +
                    "|" + indent(parseStr(square(data_2)),6);
        output += "\n";
    }

    output += indent("total:", 14);
    output +=   "|"  + indent(parseStr(v.x_y_total),6) +
                "|"  + indent(parseStr(v.x_sqr_total),6) +
                "|"  + indent(parseStr(v.y_sqr_total),6);
    output += "\n-----------------------------------\n";

    output += "\n";

    return output;
}   
cor_Vars get_Cor_Vars (format & format_1, int col_1, int col_2) // get correlation variables
{
    cor_Vars v; // value to be returned

    for (int i = 0; i < format_1.row; i++)
    {
        v.x_y_total += format_1.data[i][col_1]* format_1.data[i][col_2];
        v.x_sqr_total += square(format_1.data[i][col_1]);
        v.y_sqr_total += square(format_1.data[i][col_2]);
    }

    v.x_mean = findMean(format_1, col_1);
    v.y_mean = findMean(format_1, col_2);
    v.n = format_1.row;

    return v;
}

// F3.8 FIND DISTINCT +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
string findDistinct(format & format_1) // finds all distinct numbers in data
{
    string output;
    map<int, int> distinct;

    for (int i = 0; i < format_1.row; i++)
        for (int k = 0; k < format_1.col; k++)
            if(format_1.canCompute[k])
                distinct[format_1.data[i][k]]++;

    output += "---------------\n";
    output += "Numbers |Counts\n"; 
    output += "---------------\n";
    for(auto i : distinct)
        output += indent(parseStr(i.first),8) + "|" +  indent(parseStr(i.second),6) + "\n";
    output += "---------------\n";
    return output;   
}

// F3.9 HISTOGRAM +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
string plotGraph(format & format_1, int column) // retuns the histogram in string 
{
    string output;
    map<int, int> histogram;

    for (int i = 0; i < format_1.row; i++)
        histogram[format_1.data[i][column]]++;

    output += "Counts  Distinct numbers\n";

    for(auto i : histogram)
        output += indent(parseStr(i.second),8) + indent(parseStr(i.first),3)+ "|" + plot_Histo_Bar(i.second) +"\n";

    output += "           +=========+=========+=========+=========+\n";
    output += "           0         10        20        30        40\n";
    return output;
}

string plot_Histo_Bar(int count) // returns each bar of histogram
{
    string output;

    for (int i = 0; i < count; i++)
        output += "=";
    
    return output;
}

// FUNCTION 4 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UTILITY FUNC --------------------------------------------------------------------------------------------------------
string parseStr(double x) // converts int to string
{
    string txt;
    stringstream ss;
    ss << x;
    ss >> txt;
    return txt; 
}

string indent(string txt, int width) // leaves spaces after a word depending on word length(similar to setw())
{
    // number of spaces
    int space = width - txt.size();

    for (int i = 0; i < space; i++) // add spaces to text 
        txt += " ";
    
    return txt;
}

string get_Report_Content(string txt, double (*col_Func)(format &, int), format & format_1) // returns math value for all columns   
{
    string output; // string to be returned

    output += indent(txt, 16) ;

    // get data from all columns
    for (int i = 0; i < format_1.col; i++)
        if(format_1.canCompute[i])
            output += "|" + indent( parseStr(col_Func(format_1, i)), 10);
            
    output += "\n";

    return output;
}

int getColumn(format & format_1) // get column choice for plotting graph
{
    int column;
    cout << getReportHeader(format_1);
    cout << "Please enter columns for finding histogram:"<< endl;
    while(true)
    {
        cout << "column: ";
        cin >> column;
        cout << endl; 

        if(format_1.canCompute[column] && column < format_1.col)
            break;
        else // if column not found, try agaim
        {
            cout << "invalid column, try again" << endl;
            cin.clear();
            cin.ignore(100,'\n');
        }
    }
    return column;
}

void get2Columns(format & format_1, int & col_1, int & col_2) // returns 2 column choices for correlation func
{
    cout << getReportHeader(format_1);
    cout << "Please enter columns 1 & 2 for finding correlation"<< endl;
    while(true)
    {
        cout << "col_1: ";
        cin >> col_1; 
        cout << "col_2: ";
        cin >> col_2;
        cout << endl; 

        if((format_1.canCompute[col_1] && format_1.canCompute[col_2]) && // if column not found, try agaim
            (col_1 < format_1.col && col_2 < format_1.col))
            break;
        else
        {
            cout << "invalid column, try again" << endl;
            cin.clear();
            cin.ignore(100,'\n');
        }
    }
}

// F4.1 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void print_Menu_Opt() // print main menu options
{
    cout << "=========================" << endl;
    cout << "MAIN MENU" << endl;
    cout << "=========================" << endl;
    cout << "1.Load Data" << endl;
    cout << "2.Print Data" << endl;
    cout << "3.Statistical Analysis Menu" << endl;
    cout << "4.Save Menu" << endl;
    cout << "5.Return to login screen " << endl;
}

void main_Menu(format & format_1, ofstream & log)
{
    int choice;
    do// looops until return to login screen
    {
        print_Menu_Opt();
        choice = getChoice();
        switch(choice)
        {
            case 1:loadDataFile(format_1, log); break;
            
            case 2:printData(format_1, log);break;
            
            case 3: statisticsMenu(format_1, log);break;
            
            case 4: save_Menu(format_1, log);break;

            case 5: cout << "-> Returning to login screen...\n\n"; 
                    format_1.rightFileExist = false;
                    log_Action(log, "Returned to login screen");
                    break;    
            
            default: cout << "-> Invalid input\n\n"; break;           
        }  
    } while(choice != 5); 
}

void print_Statistics_Opt() // menu for statisticsMenu()
{
    cout << "=========================" << endl;
    cout << "STATISTICAL ANALYSIS MENU " << endl;
    cout << "=========================" << endl;
    cout << "1. Min Report" << endl;
    cout << "2. Max Report" << endl;
    cout << "3. Median Report" << endl;
    cout << "4. Mean Report" << endl;
    cout << "5. Variance Report" << endl;
    cout << "6. Standard Deviation Report" << endl;
    cout << "7. Correlation Report" << endl;
    cout << "8. Find Distinct Numbers" << endl;
    cout << "9. Plot Histogram" << endl;
    cout << "10.Return" << endl;
}

void statisticsMenu(format & format_1, ofstream & log) // menu to choose what report to cout
{
    if(format_1.rightFileExist) // check if file is loaded
    {
        print_Statistics_Opt();
        int choice = getChoice();   
        switch (choice)
        {
            case 1:  cout << getReportHeader(format_1) << get_Min_Report(format_1);break;
            case 2:  cout << getReportHeader(format_1) << get_Max_Report(format_1);break;
            case 3:  cout << getReportHeader(format_1) << get_Median_Report(format_1);break;
            case 4:  cout << getReportHeader(format_1) << get_Mean_Report(format_1);break;
            case 5:  cout << getReportHeader(format_1) << get_Var_Report(format_1);break;
            case 6:  cout << getReportHeader(format_1) << get_STD_Report(format_1);break;
            case 7:  cout << get_Cor_Report(format_1);break;
            case 8:  cout << get_Distinct_Report(format_1);break;
            case 9:  cout << get_Graph_Report(format_1);break;
            case 10: cout << "-> Returning..." << endl;break;
            default: cout << "-> Invalid input, Returning... " << endl << endl;
                    break;
        }
        if(choice >=1 && choice <= 9)log_Action(log, "Displayed statistics");
    }
    else
    {
        cout << "-> Unable to display statistics, file doesn't exist" << endl << endl;
    }
}

void save_Menu(format & format_1, ofstream & log ) // menu to choose what to save
{
    if(format_1.rightFileExist) // check if file is loaded
    {
        cout << "=========================" << endl;
        cout << "SAVE MENU" << endl;
        cout << "=========================" << endl;
        cout << "1. Save Data" << endl;
        cout << "2. Save Report" << endl;
        cout << "3. Save full HTML report:" << endl;
        cout << "4. Return" << endl;
    
        int choice = getChoice();

        switch(choice)
        {
            case 1: saveData(format_1, log);break;
            case 2: saveReport(format_1, log);break;
            case 3: saveHTMLReport(format_1, log);break;
            case 4: cout << "-> Returning..." << endl;break;
            default: cout << "-> Invalid input, Returning..." << endl << endl;
                    break;
        } 
    }
    else
    {
        cout << "-> Failed to save, file doesn't exist or file error" << endl <<endl;
    }
}

int getChoice() // gets an integer from user, if not integer, return -1
{
    cout << "-----------------------------" << endl;
    cout << "Please Enter Your Choice: ";
   
    int choice;
    if(cin >> choice)
        return choice;
    //else
        cin.clear();
        cin.ignore(100,'\n');
        return -1;
}

// F4.2 / F4.3 ------------------------------------------------------------------------------------------------------- 
string get_Min_Report(format & format_1) // returns minimum of all columns
{
    return get_Report_Content("minimum", &findMin, format_1);
}

string get_Max_Report(format & format_1) // returns maximum of all columns
{
   return get_Report_Content("maximum",  &findMax, format_1);
}

string get_Median_Report(format & format_1) // returns median of all columns
{
   return get_Report_Content("median", &findMedian, format_1);
}

string get_Mean_Report(format & format_1) // returns mean of all columns
{
    return get_Report_Content("mean", &findMean, format_1);
}

string get_Var_Report (format & format_1) // returns variance of all columns
{
   return get_Report_Content("variance", &findVar, format_1);
}

string get_STD_Report (format & format_1) // returns std deviation of all columns
{
   return get_Report_Content("std deviation", &findSTD, format_1);
}

string get_Cor_Report (format & format_1) // returns correlation of 2 columns
{
    string output; // string to be returned
    int col_1, col_2; // 2 columns of choice
 
    
    get2Columns(format_1, col_1, col_2); // get 2 column positions
    cor_Vars v = get_Cor_Vars(format_1, col_1, col_2); // get correlation variables

    double correlation; correlation = findCor(format_1, col_1, col_2); // get correlation value

    // store correlation report in output
    output += "CORRELATION:\n";
    output += get_Cor_Table(format_1, col_1, col_2);
    
    output += "Mean of " + format_1.titles[col_1] +" :" + parseStr(v.x_mean) + "\n";
    output += "Mean of " + format_1.titles[col_2] +" :" + parseStr(v.y_mean) + "\n";
    output += "-> Correlation: " + parseStr(correlation) + "\n\n";

    return output;
}

string get_Distinct_Report (format & format_1) // returns report of distinct numbers
{
    string output;
    output += "DISTINCT NUMBERS:\n";
    output += findDistinct(format_1);

    return output;
}

string get_Graph_Report (format & format_1) // returns a histogram report
{
    string output; // value to be returned

    int column = getColumn(format_1); // get column of choice

    // store report in output
    output += "HISTOGRAM:\n\n";
    output += "column: " + format_1.titles[column] + "\n\n"; 
    output += plotGraph(format_1, column);

    return output;
}

string getReportHeader(format & format_1) // get header for get_Full_Report()
{
    string output;

    // get how many subjects can compute
    int counter = 0; // counts how many subjects can compute
    for (int i = 0; i < format_1.col; i++)
        if(format_1.canCompute[i])
            counter ++;

    // print horizontal line
    for (int i = 0; i < 16; i++)
        output+= "-";

    for (int i = 0; i < counter; i++)
        for (int k = 0; k < 11; k++)
            output += "-";
    output += "\n";

    // print subject titles
    output += indent("",16);
    for (int i = 0; i < format_1.col; i++)
        if(format_1.canCompute[i])
            output += "|" + indent(format_1.titles[i], 10);
    output += "\n";

    // print horizontal line
    for (int i = 0; i < 16; i++)
        output+= "-";

    for (int i = 0; i < counter; i++)
        for (int k = 0; k < 11; k++)
            output += "-";
    output += "\n";

    return output;
}

string get_Full_Report (format & format_1) // returns a complete report
{
    string output;// string to be returned

    // get column titles
    output += getReportHeader(format_1);
    
    // get all report 
    output += 
    get_Min_Report(format_1) + get_Max_Report(format_1)+
    get_Median_Report(format_1) + get_Mean_Report(format_1)+
    get_Var_Report(format_1) + get_STD_Report(format_1)+ 
    "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"+
    get_Cor_Report(format_1) +
    "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"+
     get_Distinct_Report(format_1) +"\n" +
    "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"+
    get_Graph_Report(format_1) + "\n";
    
    return output;
}

// F4.4 ------------------------------------------------------------------------------------------------------- 
string get_HTML_Report(format & format_1)
{
    string output;
    output += get_HTML_Header();
    output += HTML_Formatting(get_Full_Report (format_1));
    output += get_HTML_Footer();    
    return output;
}

string get_HTML_Header()
{
    return "<!doctype html><html lang=\"en\"><head><meta charset=\"UTF-8\"><link rel=\"stylesheet\" href=\"font.css\"><title>HTML REPORT</title>"
    "<style>body{height:100%;margin:10;font-family:monospace;font-size:17px;font-weight:bold;color:black;}</style></head><body>";
}

string get_HTML_Footer()
{    
    return "</body></html>";
}

string HTML_Formatting(string txt) // change text to readable HTML format 
{
    string output; // string to be returned
    stringstream ss (txt); // initialize stringstream
    string dummy; // dummy text

    // replace '\n' with "<br>"
    while(getline(ss, dummy , '\n'))
    {
        output+= dummy;
        output+="<br>";
    }
    stringstream ss2 (output); // initialize 2nd sstream bcuz 1st one won't work
    output.clear();

    // replace ' ' with "&nbsp"
    while(getline(ss2, dummy , ' '))
    {
        output+= dummy;
        output+="&nbsp;";
    }

    return output;
}

string get_Saved_Report(format & format_1, int choice) // get report content to be saved
{
    string output;// string to be returned

    output += getReportHeader(format_1);// header

    switch(choice) // content
        {
            case 1: output += get_Min_Report(format_1);break;
            case 2: output += get_Max_Report(format_1);break;
            case 3: output += get_Median_Report(format_1);break;
            case 4: output += get_Mean_Report(format_1);break;
            case 5: output += get_Var_Report(format_1);break;
            case 6: output += get_STD_Report(format_1);break;
            case 7: output += get_Cor_Report(format_1);break;
            case 8: output += get_Distinct_Report(format_1);break;
            case 9: output += get_Graph_Report(format_1);break;
            default: cout << "-> Invalid input" << endl << endl; break;
        }

    return output;
}

void print_Save_Report_Menu()// print report options
{
    cout << "1. Find Minimum\n";
    cout << "2. Find Maximum\n";
    cout << "3. Find Median\n";
    cout << "4. Find Mean\n";
    cout << "5. Find variance\n";
    cout << "6. Find Standard Deviation\n";
    cout << "7. Find Correlation Between 2 Columns\n";
    cout << "8. Find Distinct Data Members\n";
    cout << "9. Plot Histogram\n";
    cout << "10.Cancel\n\n";
}
