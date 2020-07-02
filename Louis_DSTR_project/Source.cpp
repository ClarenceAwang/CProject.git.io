#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;


struct Date
{
    int date, month, year;
};
const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct user 
{
    private:
        string username;
        string password;
        int loginattempt = 0;

    public:
        void mainsystem();
};

struct Tutordata
{

    int TutorID;
    string tutorname;
    string datejoined;
    string dateterminated;
    int payrate;
    string phonenum;
    string address;
    string TCentrecode;
    string TCentrename;
    string subjectcode;
    double rating;
    
        
    Tutordata* nextadd;
    Tutordata* back;
        
}*head, * temp, *tail,*previous,*newhead,*newtail,*newnode ;

Tutordata* createnewdata(int TutorID, string tutorname, string datejoined, string dateterminated, int payrate,
    string phonenum, string address, string TCentrecode, string TCentrename,
    string subjectcode, double rating);




void insertdataintolist(int TutorID, string tutorname, string datejoined, string dateterminated, int payrate,
    string phonenum, string address, string TCentrecode, string TCentrename,
    string subjectcode, double rating);

void insertintoIDsortedlist(int TutorID, string tutorname, string datejoined, string dateterminated, int payrate,
    string phonenum, string address, string TCentrecode, string TCentrename,
    string subjectcode, double rating);

void insertintoPayratesortedlist(int TutorID, string tutorname, string datejoined, string dateterminated, int payrate,
    string phonenum, string address, string TCentrecode, string TCentrename,
    string subjectcode, double rating);

void insertintoPerformancesortedlist(int TutorID, string tutorname, string datejoined, string dateterminated, int payrate,
    string phonenum, string address, string TCentrecode, string TCentrename,
    string subjectcode, double rating);


void displaytutorlist();
void searchTutorID();
void searchTutorRating();
void displayIDsortedlist();
void displayPayratesortedlist();
void displayPerformancesortedlist();
void deletetutor(int TutorID);
void edittutordateterminate(int tutorID, string newdateterminated);
void edittutoraddress(int tutorID, string newaddress);
void edittutorphonenum(int tutorID, string newphonenum);



int LeapYears(Date da)
{
    int year = da.year;

    // Check if the current year needs to be considered 
    // for the count of leap years or not 
    if (da.month <= 2)
        year--;

    // An year is a leap year if it is a multiple of 4, 
    // multiple of 400 and not a multiple of 100. 
    return year / 4 - year / 100 + year / 400;
}

// This function returns number of days between two given 
// dates 
int getDifference(Date date1, Date date2)
{
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1' 

    // initialize count using years and day 
    long int num1 = date1.year * 365 + date1.date;

    // Add days for months in given date 
    for (int i = 0; i < date1.month - 1; i++)
        num1 += monthDays[i];

    // Since every leap year is of 366 days, 
    // Add a day for every leap year 
    num1 += LeapYears(date1);

    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2' 

    long int num2 = date2.year * 365 + date2.date;
    for (int i = 0; i < date2.month - 1; i++)
        num2 += monthDays[i];
    num2 += LeapYears(date2);

    // return difference between two counts 
    return (num2 - num1);
}

int getLocalDate(string date_Terminated)
{

    string date, localday, localmonth, localyear, termday, termmonth, termyear;
    int result, onedate, onemonth, oneyear, term_d, term_m, term_y;
    char buffer[80];
    // Declaring argument for time() 
    time_t timet;

    // Declaring variable to store return value of 
    // localtime() 
    struct tm* ti;

    // Applying time() 
    time(&timet);

    // Using localtime() 
    ti = localtime(&timet); 
    //localtime error message override  
    //go to project > properties
    // then click drop down c++/c
    // select preprocessor > preprocessor definition
    // Edit Preprocessor Definitions and add _CRT_SECURE_NO_WARNINGS last empty line.
      
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", ti);

    date = buffer;

    localday = date.substr(0, 2);
    localmonth = date.substr(3, 2);
    localyear = date.substr(6, 4);
    termday = date_Terminated.substr(0, 2);
    termmonth = date_Terminated.substr(3, 2);
    termyear = date_Terminated.substr(6, 4);


    onedate = stoi(localday); onemonth = stoi(localmonth); oneyear = stoi(localyear);
    term_d = stoi(termday); term_m = stoi(termmonth); term_y = stoi(termyear);

    result = getDifference({ term_d, term_m, term_y }, { onedate, onemonth, oneyear });

    return result;
}

void insertdataintolist(int TutorID, string tutorname, string datejoined, string dateterminated, int payrate,
    string phonenum, string address, string TCentrecode, string TCentrename,
    string subjectcode, double rating)
{

    newnode = new Tutordata;
    Tutordata* newnode = createnewdata(TutorID, tutorname, datejoined, dateterminated, payrate, phonenum, address, TCentrecode, TCentrename,
        subjectcode, rating);
    newnode->TutorID = TutorID;
    newnode->tutorname = tutorname;
    newnode->datejoined = datejoined;
    newnode->dateterminated = dateterminated;
    newnode->payrate = payrate;
    newnode->phonenum = phonenum;
    newnode->address = address;
    newnode->TCentrecode = TCentrecode;
    newnode->TCentrename = TCentrename;
    newnode->subjectcode = subjectcode;
    newnode->rating = rating;
 
    newnode->nextadd = NULL;
    newnode->back = NULL;

    if (head == NULL)
    {
        head = tail = newnode;
    }
    else
    {
        newnode->back = tail;
        tail->nextadd = newnode;
        tail = newnode;

    }

}

void edittutordateterminate(int tutorID, string newdateterminated)
{
    temp = head; bool check = false;
    cout << string(40, '=') << endl;
    while (temp != NULL)
    {
        if (tutorID == temp->TutorID)
        {
            cout << "List before change: " << endl << endl;
            cout << "Tutor ID: " << temp->TutorID << endl;
            cout << "Name: " << temp->tutorname << endl;
            cout << "Date Joined: " << temp->datejoined << endl;
            cout << "Date Terminated: " << temp->dateterminated << endl;
            temp->dateterminated = newdateterminated;
            cout << "Pay rate: " << temp->payrate << endl;
            cout << "Phone: " << temp->phonenum << endl;
            cout << "Address: " << temp->address << endl;
            cout << "Tuition centre code: " << temp->TCentrecode << endl;
            cout << "Tuition centre name: " << temp->TCentrename << endl;
            cout << "Subject code: " << temp->subjectcode << endl;
            cout << "Rating: " << temp->rating << endl << endl;
            cout << string(40, '=') << endl;
            cout << "List after change: " << endl << endl;
            temp = temp->nextadd;
            check = true;

        }
        temp = temp->nextadd;
    }
    if (check == false)
        cout << "Record Not Found! No changes allowed!" << endl << endl;

    displaytutorlist();
    cout << endl;

}

void edittutorphonenum(int tutorID, string newphonenum)
{
    temp = head; bool check = false;
    cout << string(40, '=') << endl;
    while (temp != NULL)
    {
        if (tutorID == temp->TutorID)
        {
            cout << "List before change: " << endl << endl;
            cout << "Tutor ID: " << temp->TutorID << endl;
            cout << "Name: " << temp->tutorname << endl;
            cout << "Date Joined: " << temp->datejoined << endl;
            cout << "Date Terminated: " << temp->dateterminated << endl;
            cout << "Pay rate: " << temp->payrate << endl;
            cout << "Phone: " << temp->phonenum << endl;
            temp->phonenum = newphonenum;
            cout << "Address: " << temp->address << endl;
            cout << "Tuition centre code: " << temp->TCentrecode << endl;
            cout << "Tuition centre name: " << temp->TCentrename << endl;
            cout << "Subject code: " << temp->subjectcode << endl;
            cout << "Rating: " << temp->rating << endl << endl;
            cout << string(40, '=') << endl;
            cout << "List after change: " << endl << endl;
            temp = temp->nextadd;
            check = true;

        }
        temp = temp->nextadd;
    }
    if (check == false)
        cout << "Record Not Found! No name changes allowed!" << endl << endl;

    displaytutorlist();
    cout << endl;

    

}

void edittutoraddress(int tutorID, string newaddress)
{
    temp = head; bool check = false;
    cout << string(40, '=') << endl;
    while (temp != NULL)
    {
        if (tutorID == temp->TutorID)
        {
            cout << "List before change: " << endl << endl;
            cout << "Tutor ID: " << temp->TutorID << endl;
            cout << "Name: " << temp->tutorname << endl;
            cout << "Date Joined: " << temp->datejoined << endl;
            cout << "Date Terminated: " << temp->dateterminated << endl;
            cout << "Pay rate: " << temp->payrate << endl;
            cout << "Phone: " << temp->phonenum << endl;
            cout << "Address: " << temp->address << endl;
            temp->address = newaddress;
            cout << "Tuition centre code: " << temp->TCentrecode << endl;
            cout << "Tuition centre name: " << temp->TCentrename << endl;
            cout << "Subject code: " << temp->subjectcode << endl;
            cout << "Rating: " << temp->rating << endl;
            cout << string(40, '=') << endl << endl;
            cout << "List after change: " << endl << endl;
            temp = temp->nextadd;
            check = true;

        }
        temp = temp->nextadd;
    }
    if (check == false)
        cout << "Record Not Found! No name changes allowed!" << endl << endl;

    displaytutorlist();
    cout << endl;

}

void displaytutorlist()
{
    //step 1:
    temp = head;

    //step 2:
    while (temp != NULL) {
        cout << "Tutor ID: " << temp->TutorID << endl; 
        cout << "Name: " << temp->tutorname << endl; 
        cout << "Date Joined: " << temp->datejoined << endl;
        cout << "Date Terminated: " << temp->dateterminated << endl;
        cout << "Pay rate: " << temp->payrate << endl; 
        cout << "Phone: " << temp->phonenum << endl; 
        cout << "Address: " << temp->address << endl; 
        cout << "Tuition centre code: " << temp->TCentrecode << endl;
        cout << "Tuition centre name: " << temp->TCentrename << endl;
        cout << "Subject code: " << temp->subjectcode << endl;
        cout << "Rating: " << temp->rating << endl << endl;
        temp = temp->nextadd;
    }
    cout << endl;
}

void searchTutorID() {
    int TutorID;
    cout << "Enter the ID: ";
    cin >> TutorID;
    cout << endl;
    int flag = 0;
    int count = 1;
    temp = head;
    Tutordata* previous = NULL;
    

    while (temp != NULL) {

        if (TutorID == temp->TutorID)
        {
            cout << "Tutor ID: " << temp->TutorID << endl;
            cout << "Name: " << temp->tutorname << endl;
            cout << "Date Joined: " << temp->datejoined << endl;
            cout << "Date Terminated: " << temp->dateterminated << endl;
            cout << "Pay rate: " << temp->payrate << endl;
            cout << "Phone: " << temp->phonenum << endl;
            cout << "Address: " << temp->address << endl;
            cout << "Tuition centre code: " << temp->TCentrecode << endl;
            cout << "Tuition centre name: " << temp->TCentrename << endl;
            cout << "Subject code: " << temp->subjectcode << endl;
            cout << "Rating: " << temp->rating << endl << endl;
            flag = 1;
            break;

        }
        else
        {
            temp = temp->nextadd;
        }
    }
        if (flag == 0)
        {
            cout << "Data does not exist" << endl;

        }
    
}

void searchTutorRating()
{
    int marker;
    double Rating;
    cout << "Enter the Rating: ";
    cin >> Rating;
    cout << endl;
    
    int count = 1;
    temp = head;
    Tutordata* previous = NULL;
    

    while (temp != NULL) {
        

        if (Rating == temp->rating) {
            cout << "Tutor ID: " << temp->TutorID << endl;
            cout << "Name: " << temp->tutorname << endl;
            cout << "Date Joined: " << temp->datejoined << endl;
            cout << "Date Terminated: " << temp->dateterminated << endl;
            cout << "Pay rate: " << temp->payrate << endl;
            cout << "Phone: " << temp->phonenum << endl;
            cout << "Address: " << temp->address << endl;
            cout << "Tuition centre code: " << temp->TCentrecode << endl;
            cout << "Tuition centre name: " << temp->TCentrename << endl;
            cout << "Subject code: " << temp->subjectcode << endl;
            cout << "Rating: " << temp->rating << endl << endl;
            marker = 1;
            temp = temp->nextadd;
            
           
        }
        else  
        {
            temp = temp->nextadd;
            
        }
        
    }
    if (marker == 0)
    {
        cout << "Data does not exist" << endl;

    }


}
    Tutordata* createnewdata(int TutorID, string tutorname, string datejoined, string dateterminated, int payrate,
        string phonenum, string address, string TCentrecode, string TCentrename,
        string subjectcode, double rating) {
    //step 1: create a dynamic empty structure
    Tutordata* createnewdata = new Tutordata;

    //step2: add information to the stucture
    createnewdata->TutorID = TutorID;
    createnewdata->tutorname = tutorname;
    createnewdata->datejoined = datejoined;
    createnewdata->dateterminated = dateterminated;
    createnewdata->payrate = payrate;
    createnewdata->phonenum = phonenum;
    createnewdata->address = address;
    createnewdata->TCentrecode = TCentrecode;
    createnewdata->TCentrename = TCentrename;
    createnewdata->subjectcode = subjectcode;
    createnewdata->rating = rating;
    createnewdata->nextadd = NULL;

    //step 3: return the address to the previous function
    return createnewdata;
}

    Tutordata* createnewsort(int TutorID)
    {
        Tutordata* createnewsort = new Tutordata;
        createnewsort->TutorID = TutorID;

        return createnewsort;

    }
void HRmainmenu()
{
    int sign;
    int choice2;
    int TutorID;
    string tutorname;
    string datejoined;
    string dateterminated;
    int payrate;
    string phonenum;
    string address;
    string TCentrecode;
    string TCentrename;
    string subjectcode;
    double rating;
    int choice;
    cout << "*******************************************************************" << endl;
    cout << "1. Add a Tutor Record" << endl;
    cout << "2. Display All Records" << endl; 
    cout << "3. Search a tutor by Tutor ID" << endl;
    cout << "4. Search Tutors by Rating" << endl;
    cout << "5. Sort and display tutor by ID in ascending order" << endl;
    cout << "6. Sort and display tutor by pay rate in ascending order" << endl;
    cout << "7. Sort and display tutor by overall performance in ascending order" << endl;
    cout << "8. Modify a tutor record" << endl;
    cout << "9. Delete a tutor record" << endl;
    cout << "10. Logout" << endl;
    cout << "*******************************************************************" << endl;
    cout << "Please enter desired number: " << endl;
    cin >> choice;

    switch (choice) 
    {
    case 1:
        cout << "Insert tutor details" << endl;
        cout << "TutorID: ";
        cin >> TutorID;

        while (head != NULL)
        {
            if (TutorID == head->TutorID)
            {
                cout << "record existed" << endl;
                cout << "Please enter non existing ID" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize> ::max(), '\n');
                cin >> TutorID;
                continue;
            }
            else
            {
                break;
            }
            
           
        }
        while (!cin)
        {
            if (!cin)
            {
                cout << "Please enter an integer : ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize> ::max(), '\n');
                cin >> TutorID;
                continue;
            }
            else
            {
                break;
            }
            

        }

        

        cout << "Name: ";
        cin.ignore();
        getline(cin, tutorname);
        cout << "Date joined (dd/mm/yy) : ";
        cin >> datejoined;
        cout << "Date terminated: ";
        cin >> dateterminated;
        cout << "Pay rate (hourly): ";
        cin >> payrate;
        while (!cin)
        {
            if (!cin)
            {
                cout << "Please enter an integer : ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize> ::max(), '\n');
                cin >> payrate;
                continue;
            }
            else
            {
                break;
            }


        }
        cout << "Phone number: ";
        cin >> phonenum;
        cout << "Address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Tution centre code: ";
        cin >> TCentrecode;
        cout << "Tuition centre name: ";
        cin.ignore();
        getline(cin, TCentrename);
        cout << "Subject: ";
        cin >> subjectcode;
        cout << "Rating: ";
        cin >> rating;
        while (!cin)
        {
            if (!cin)
            {
                cout << "Please enter an integer : ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize> ::max(), '\n');
                cin >> rating;
                continue;
            }
            else
            {
                break;
            }

        }
        insertdataintolist(TutorID, tutorname,datejoined,dateterminated, payrate,
            phonenum, address, TCentrecode, TCentrename,
            subjectcode, rating);
        cout << "\nList: " << endl;
        displaytutorlist();
       
        //add record
        cout << "Press enter to continue";
        cin.ignore();
        cin.get();
        cout << endl;
        HRmainmenu();

    case 2:
        cout << "Tutor list" << endl;
        displaytutorlist();
        
        //display all records
        cout << "Press enter to continue";
        cin.ignore();
        cin.get();
        cout << endl;
        HRmainmenu();


    case 3:
        searchTutorID();
        
        
        //search by ID
        cout << "Press enter to continue";
        cin.ignore();
        cin.get();
        cout << endl;
        HRmainmenu();

    case 4:
        searchTutorRating();
       
        
        
        //search by rating
        cout << "Press enter to continue";
        cin.ignore();
        cin.get();
        cout << endl;
        HRmainmenu();

    case 5:
        newhead = newtail = NULL; //start empty
        temp = head; // refer the old list
        while (temp != NULL)
        {
            insertintoIDsortedlist(temp->TutorID,temp->tutorname,temp->datejoined, temp->dateterminated, temp->payrate,temp->phonenum, temp->address, temp->TCentrecode, temp->TCentrename, temp->subjectcode, temp->rating);
            temp = temp->nextadd;
        }
        displayIDsortedlist();
        
        //sort ID ascend
        cout << "Press enter to continue";
        cin.ignore();
        cin.get();
        cout << endl;
        HRmainmenu();

    case 6:
        newhead = newtail = NULL; //start empty
        temp = head; // refer the old list
        while (temp != NULL)
        {
            insertintoPayratesortedlist(temp->TutorID, temp->tutorname, temp->datejoined, temp->dateterminated, temp->payrate, temp->phonenum, temp->address, temp->TCentrecode, temp->TCentrename, temp->subjectcode, temp->rating);
            temp = temp->nextadd;
        }
        displayPayratesortedlist();
        
        //sort pay ascend
        cout << "Press enter to continue";
        cin.ignore();
        cin.get();
        cout << endl;
        HRmainmenu();

    case 7:
        cout << "Tutor list sorted by rating in ascending order" << endl;
        newhead = newtail = NULL; //start empty
        temp = head; // refer the old list
        while (temp != NULL)
        {
            insertintoPerformancesortedlist(temp->TutorID, temp->tutorname, temp->datejoined, temp->dateterminated, temp->payrate, temp->phonenum, temp->address, temp->TCentrecode, temp->TCentrename, temp->subjectcode, temp->rating);
            temp = temp->nextadd;
        }
        displayPerformancesortedlist();
        
        //sort rating ascend
        cout << "Press enter to continue";
        cin.ignore();
        cin.get();
        cout << endl;
        HRmainmenu();

    case 8:
        cout << "Select which information to modify" << endl;
        cout << "1. Date terminated: " << endl;
        cout << "2. Address: " << endl;
        cout << "3. Phone number: " << endl;
        cin >> choice2;
        if (choice2 == 1)
        {
            
            string newdateterminate;
            cout << "Enter tutor id: " << endl;
            cin >> TutorID;
            while (!cin)
            {
                if (!cin)
                {
                    cout << "Please enter an integer : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize> ::max(), '\n');
                    cin >> TutorID;
                    continue;
                }
                else
                {
                    break;
                }

            }
            cout << "Enter Date terminated: ";
            cin >> newdateterminate;
            edittutordateterminate(TutorID, newdateterminate);
        }
        else if (choice2 == 2)
        {
            string newaddress;
            cout << "Enter tutor id: " << endl;
            cin >> TutorID;
            while (!cin)
            {
                if (!cin)
                {
                    cout << "Please enter an integer : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize> ::max(), '\n');
                    cin >> TutorID;
                    continue;
                }
                else
                {
                    break;
                }

            }
            cout << "Enter new address: ";
            cin.ignore();
            getline(cin, newaddress);
            edittutoraddress(TutorID, newaddress);
        }
        else if (choice2 == 3)
        {
            string newphonenum;
            cout << "Enter tutor id: " << endl;
            cin >> TutorID;
            while (!cin)
            {
                if (!cin)
                {
                    cout << "Please enter an integer : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize> ::max(), '\n');
                    cin >> TutorID;
                    continue;
                }
                else
                {
                    break;
                }

            }
            cout << "Enter new phone number: ";
            cin >> newphonenum;
            edittutorphonenum(TutorID, newphonenum);
        }


        cout << "Press enter to continue";
        cin.ignore();
        cin.get();
        cout << endl;
        HRmainmenu();

    case 9:
        
        cout << "Select tutor to delete: ";
        cin >> TutorID;
        

        while (!cin)
        {
            if (!cin)
            {
                cout << "Please enter an integer : ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize> ::max(), '\n');
                cin >> TutorID;
                continue;
            }
            else
            {
                break;
            }

        }   
            deletetutor(TutorID);
        

   
        //delete tutor
        cout << "Press enter to continue";
        cin.ignore();
        cin.get();
        cout << endl;
        HRmainmenu();

    case 10:
        cout << "LOGOUT INITIATED" << endl;
        break;


    default:
        cout << "ERROR, enter (1-10) please" << endl << endl;
        HRmainmenu();
    }
   

}



void user :: mainsystem() {

    while (loginattempt < 5)
    {
        cout << "Enter a username: " << endl;
        cin >> username;
        cout << "Enter a password: " << endl;
        cin >> password;


        if (username == "HR" && password == "HR123")
        {
            cout << "Welcome to eXcel Tuition Centre!, you are logged in as an HR manager." << endl;
            HRmainmenu();
        }
        else
        {
            cout << "Invalid login attempt. Please try again." << endl;
            loginattempt++;
        }

    }
    if (loginattempt == 5)
    {
        cout << "Too many login attempts! The program will now terminate."<< endl;
        
    }


}




int main()
{

    tail = NULL;
    head = NULL;
    insertdataintolist(1, "Heimrich Oppenheimer","04/05/2018","04/05/2025", 150,"+60456789988", "Test Street", "BukitJ", "eXcel Tuition Centre Bukit Jalil", "Science", 4.5);
    insertdataintolist(2, "Samuel Hayden","07/12/2006","07/12/2025", 500, "+60456789077", "Test Street", "BukitJ", "eXcel Tuition Centre Bukit Jalil", "Demonology", 5);
    insertdataintolist(3, "Sergei Popov", "05/06/2016", "05/06/2025", 400, "+60678906454", "Test Street", "BukitJ", "eXcel Tuition Centre Bukit Jalil", "Russian Language", 4);
    insertdataintolist(4, "Hans", "17/08/2010", "17/08/2019", 350, "+60785674988", "Test Street", "BukitJ", "eXcel Tuition Centre Bukit Jalil", "German Language", 3);
    insertdataintolist(5, "Max Hass", "22/10/2016", "22/10/2025", 250, "+60786785644", "Test Street", "BukitJ", "eXcel Tuition Centre Bukit Jalil", "History", 5);
    insertdataintolist(6, "Snickers", "25/03/2017", "25/03/2025", 650, "+60238764509", "Test Street", "BukitJ", "eXcel Tuition Centre Bukit Jalil", "Pastry", 4);
    insertdataintolist(7, "Levi", "15/04/2005", "15/04/2020", 500, "+60783456755", "Test Street", "BukitJ", "eXcel Tuition Centre Bukit Jalil", "Science", 3.5);
    insertdataintolist(8, "kevin", "22/04/2010", "22/04/2025", 300, "+60128694577", "Test Street", "BukitJ", "eXcel Tuition Centre Bukit Jalil", "English", 4);
    insertdataintolist(9, "Jack", "12/03/2019", "12/03/2025", 450, "+60785760233", "Test Street", "BukitJ", "eXcel Tuition Centre Bukit Jalil", "Chinese Language", 5);
    insertdataintolist(10, "Suhardani", "01/07/2015", "01/07/2018", 250, "+60450684566", "Test Street", "BukitJ", "eXcel Tuition Centre Bukit Jalil", "Mechatronic", 1);

    user Admin;
    Admin.mainsystem();
         
}

void displayPayratesortedlist()
{
    temp = newhead; //ortail if u wan reverse
    while (temp != NULL)
    {
        //cout << fixed << setprecision(1);
        cout << "Tutor ID: " << temp->TutorID << endl;
        cout << "Name: " << temp->tutorname << endl;
        cout << "Date joined: " << temp->datejoined << endl;
        cout << "Date terminated: " << temp->dateterminated << endl;
        cout << "Pay rate: " << temp->payrate << endl;
        cout << "Phone: " << temp->phonenum << endl;
        cout << "Address: " << temp->address << endl;
        cout << "Tuition centre code: " << temp->TCentrecode << endl;
        cout << "Tuition centre name: " << temp->TCentrename << endl;
        cout << "Subject code: " << temp->subjectcode << endl;
        cout << "Rating: " << temp->rating << endl << endl;
        temp = temp->nextadd; // back for reverse
    }
    cout << endl;


}
void displayIDsortedlist()
{
    temp = newhead; //ortail if u wan reverse
    while (temp != NULL)
    {
        //cout << fixed << setprecision(1);
        cout << "Tutor ID: " << temp->TutorID << endl;
        cout << "Name: " << temp->tutorname << endl;
        cout << "Date joined: " << temp->datejoined << endl;
        cout << "Date terminated: " << temp->dateterminated << endl;
        cout << "Pay rate: " << temp->payrate << endl;
        cout << "Phone: " << temp->phonenum << endl;
        cout << "Address: " << temp->address << endl;
        cout << "Tuition centre code: " << temp->TCentrecode << endl;
        cout << "Tuition centre name: " << temp->TCentrename << endl;
        cout << "Subject code: " << temp->subjectcode << endl;
        cout << "Rating: " << temp->rating << endl << endl;
        temp = temp->nextadd; // back for reverse
    }
    cout << endl;

}

void displayPerformancesortedlist()
{
    temp = newhead; //ortail if u wan reverse
    while (temp != NULL)
    {
        //cout << fixed << setprecision(1);
        cout << "Tutor ID: " << temp->TutorID << endl;
        cout << "Name: " << temp->tutorname << endl;
        cout << "Date joined: " << temp->datejoined << endl;
        cout << "Date terminated: " << temp->dateterminated << endl;
        cout << "Pay rate: " << temp->payrate << endl;
        cout << "Phone: " << temp->phonenum << endl;
        cout << "Address: " << temp->address << endl;
        cout << "Tuition centre code: " << temp->TCentrecode << endl;
        cout << "Tuition centre name: " << temp->TCentrename << endl;
        cout << "Subject code: " << temp->subjectcode << endl;
        cout << "Rating: " << temp->rating << endl << endl;
        temp = temp->nextadd; // back for reverse
    }
    cout << endl;

}

void insertintoIDsortedlist(int TutorID, string tutorname, string datejoined, string dateterminated, int payrate,
    string phonenum, string address, string TCentrecode, string TCentrename,
    string subjectcode, double rating)
{
    newnode = new Tutordata;
    newnode->TutorID = TutorID;
    newnode->tutorname = tutorname;
    newnode->datejoined = datejoined;
    newnode->dateterminated = dateterminated;
    newnode->payrate = payrate;
    newnode->phonenum = phonenum;
    newnode->address = address;
    newnode->TCentrecode = TCentrecode;
    newnode->TCentrename = TCentrename;
    newnode->subjectcode = subjectcode;
    newnode->rating = rating;
    newnode->nextadd = NULL;
    newnode->back = NULL;



    //situation 1: no list yet
    if (newhead == NULL)
    {
        newhead = newtail = newnode;
    }
    //situation 2: node in the list but id <= first value , then insert to front
    else if (TutorID <= newhead->TutorID)
    {
        newnode->nextadd = newhead;
        newhead->back = newnode;
        newhead = newnode;
    }
    //situation 3: id > head value
    else
    {
        Tutordata* newtemp = newhead;
        while (newtemp->nextadd != NULL)
        {
            if (TutorID <= newtemp->nextadd->TutorID)
                break;
            newtemp = newtemp->nextadd;
        }
        newnode->nextadd = newtemp->nextadd;
        newnode->back = newtemp;
        if (newtemp->nextadd == NULL) // if newtemp is tail, this attached in the behind as tail
        {
            newtail = newnode;
        }
        else
        {
            newtemp->nextadd->back = newnode; // means behind got stg, newtemp not the last node
        }
        newtemp->nextadd = newnode;
    }
}

void insertintoPayratesortedlist(int TutorID, string tutorname, string datejoined, string dateterminated, int payrate,
    string phonenum, string address, string TCentrecode, string TCentrename,
    string subjectcode, double rating)
{
    newnode = new Tutordata;
    newnode->TutorID = TutorID;
    newnode->tutorname = tutorname;
    newnode->datejoined = datejoined;
    newnode->dateterminated = dateterminated;
    newnode->payrate = payrate;
    newnode->phonenum = phonenum;
    newnode->address = address;
    newnode->TCentrecode = TCentrecode;
    newnode->TCentrename = TCentrename;
    newnode->subjectcode = subjectcode;
    newnode->rating = rating;
    newnode->nextadd = NULL;
    newnode->back = NULL;



    //situation 1: no list yet
    if (newhead == NULL)
    {
        newhead = newtail = newnode;
    }
    //situation 2: node in the list but id <= first value , then insert to front
    else if (payrate <= newhead->payrate)
    {
        newnode->nextadd = newhead;
        newhead->back = newnode;
        newhead = newnode;
    }
    //situation 3: id > head value
    else
    {
        Tutordata* newtemp = newhead;
        while (newtemp->nextadd != NULL)
        {
            if (payrate <= newtemp->nextadd->payrate)
                break;
            newtemp = newtemp->nextadd;
        }
        newnode->nextadd = newtemp->nextadd;
        newnode->back = newtemp;
        if (newtemp->nextadd == NULL) // if newtemp is tail, this attached in the behind as tail
        {
            newtail = newnode;
        }
        else
        {
            newtemp->nextadd->back = newnode; // means behind got stg, newtemp not the last node
        }
        newtemp->nextadd = newnode;
    }

}

void insertintoPerformancesortedlist(int TutorID, string tutorname, string datejoined, string dateterminated, int payrate,
    string phonenum, string address, string TCentrecode, string TCentrename,
    string subjectcode, double rating)
{
    newnode = new Tutordata;
    newnode->TutorID = TutorID;
    newnode->tutorname = tutorname;
    newnode->datejoined = datejoined;
    newnode->dateterminated = dateterminated;
    newnode->payrate = payrate;
    newnode->phonenum = phonenum;
    newnode->address = address;
    newnode->TCentrecode = TCentrecode;
    newnode->TCentrename = TCentrename;
    newnode->subjectcode = subjectcode;
    newnode->rating = rating;
    newnode->nextadd = NULL;
    newnode->back = NULL;



    //situation 1: no list yet
    if (newhead == NULL)
    {
        newhead = newtail = newnode;
    }
    //situation 2: node in the list but id <= first value , then insert to front
    else if (rating <= newhead->rating)
    {
        newnode->nextadd = newhead;
        newhead->back = newnode;
        newhead = newnode;
    }
    //situation 3: id > head value
    else
    {
        Tutordata* newtemp = newhead;
        while (newtemp->nextadd != NULL)
        {
            if (rating <= newtemp->nextadd->rating)
                break;
            newtemp = newtemp->nextadd;
        }
        newnode->nextadd = newtemp->nextadd;
        newnode->back = newtemp;
        if (newtemp->nextadd == NULL) // if newtemp is tail, this attached in the behind as tail
        {
            newtail = newnode;
        }
        else
        {
            newtemp->nextadd->back = newnode; // means behind got stg, newtemp not the last node
        }
        newtemp->nextadd = newnode;
    }

}

void deletetutor(int TutorID)
{

            if (head == NULL) //situation 1 check whether list is empty or nah
            {
                cout << "this is an empty list\n no deletion is needed\n";
            }
            else if (TutorID == head->TutorID)// situation 2 check the recuired deleted id is in first location or not
            {
                int sign;
                temp = head;
                sign = (getLocalDate(temp->dateterminated));

                if (sign >= 180)
                {
                    temp = head->nextadd;
                    cout << head->TutorID << " is deleted now\n";
                    delete head;
                    head = temp;
                }
                else
                {
                    cout << "Record unavaiable to because tutor has not been terminated or terminated record is less than 6 month " << endl;
                    
                }
            }
            else // situation 3 search the id location and delete
            {
                temp = head;
                Tutordata* previous = NULL; // create 2 pointers
                while (TutorID != temp->TutorID)// check whether the required deleted id same as current id
                {
                    previous = temp;//search again by setting the previous location
                    temp = temp->nextadd;//find the new location

                    if (temp == NULL)// when reach the new location, find out is it the end list or not
                    {
                        cout << "No value is in the list so no deletion needed\n" << endl;
                        return;// if already end list, break the loop and return
                    }
                }
                //found id then deletion started
                previous->nextadd = temp->nextadd;// move the previous location next pointer to the third location  and skip the second location
                cout << temp->TutorID << " is deleted now\n";
                delete temp;

            }


}

