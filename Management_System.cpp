#include <iostream>
#include <windows.h>
#include <conio.h>
#include <regex>
#include <fstream>

using namespace std;

// Function Prototypes

void StartupMenu();
void USMS();
void mainUSMS();
void hideCursor();
void disableCursor();
int wherey();
void printspace();
void gotoxy(int x, int y);
void setColor(int colorCode);

void signup();
void storinglogindata(string new_user, string new_pass, string new_phone, string new_email, string new_role);
void readlogindata();
void writedatinfile();
void writedatinfile1();
void signin();

void MainMenu();
void subMenuBeforeMainMenu(string submenu);
void submenu(string submenu);
void displayscreen();
void displayscreen1();
void displaytime();

void SportsSocietyMainMenu();
void ProgrammingSocietiesMainMenu();
void CreativeArtSocietiesMainMenu();
void AcedemicSocietiesMainMenu();
void SocialandRecreationalSocietyMainMenu();
void ReligiousandSpirtualSocietyMainMenu();
void CulturalSocietiesMainMenu();
void ArtisticSocietiesMainMenu();
void GamingSocietiesMainMenu();
void PoliticalOrActivistSocietiesMainMenu();

void AdminsMenu();
void StudentMenu();

void storesocietydata(string sn, string sd, string sp);
void readsocietydata();
void addsociety();
void updatesociety();
void removesociety();
void displayadminsociety();
void displaystudentsociety();

void storememberdata(string mu, string me, string mp);
void readmemberdata();
void addmember();
void updatemember();
void removemember();
void displaymember_admin();
void displaymember_student();

void giveFeedback();
void displayfeedback();
void storefeedback(string f);
void loadfeedback();

void editevent();
void displayevent();

void submitRequest();
void displayrequests();
void storereq();
void loadreq();

void editsocietymission();
void displaysocietymission();

void storedonation(string don);
void loaddonation();
void displaydonation();
void donateToSociety();

bool is_username_exist(string usern);
bool is_phone_exist(string phonen);
bool is_email_exist(string em);
bool is_valid_user(string un, string p);
string get_role(string un);
string getfile(string record, int field);
bool isString(string str);
bool isInteger(string str);

// Arrays

string username[100];
string password[100];
string contact_number[100];
string email[100];
string role[100];
string requests[100];
string society_member_username[100];
string society_member_email[100];
string society_member_phone[100];
string feedbackss[100];
string society_name[100];
string soceiety_des[100];
string society_pres[100];
string donation_amount[100];
string event[1] = {"This society is going to have a big event this friday 30 Feb 2022 at 2pm"};
string mission[1] = {"This objective of the society is to excel in it's mission"};

// Counters
int num_societies = 0;
int num_users = 0;
int num_feedb = 0;
int num_members = 0;
int num_request = 0;
int num_donations = 0;
int num_signups = -1;

bool flag = false;
regex email_regex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

int main()
{
    if (flag == false)
    {
        readlogindata();
        readsocietydata();
        readmemberdata();
        loadfeedback();
        loadreq();
        loaddonation();
    }
    flag = true;
    hideCursor();
    disableCursor();
    string option;
    int currentSelection = 1;
    int key;
    while (true)
    {

        displayscreen1();
        subMenuBeforeMainMenu("Login");
        if (currentSelection == 1)
        {
            setColor(9); // Blue color
            cout << "  >";
        }
        else
        {
            setColor(11);
            cout << "   ";
        }
        cout << "   Sign Up" << endl;
        if (currentSelection == 2)
        {
            setColor(9); // Blue color
            cout << "  >";
        }
        else
        {
            setColor(11);
            cout << "   ";
        }
        cout << "   Sign In" << endl;
        if (currentSelection == 3)
        {
            setColor(9); // Blue color
            cout << "  >";
        }
        else
        {
            setColor(11);
            cout << "   ";
        }
        cout << "   Exit" << endl;

        // handle user input
        key = getch();

        if (key == 72)
        { // up arrow key
            if (currentSelection > 1)
            {
                currentSelection--;
            }
            else if (currentSelection == 1)
            {
                currentSelection = 3;
            }
        }

        else if (key == 80)
        { // down arrow key
            if (currentSelection < 3)
            {
                currentSelection++;
            }
            else if (currentSelection == 3)
            {
                currentSelection = 1;
            }
        }

        else if (key == 13)
        { // enter key
            if (currentSelection == 1)
            {
                displayscreen1();
                subMenuBeforeMainMenu("SignUp");
                signup();
                getch();
            }
            else if (currentSelection == 2)
            {
                displayscreen1();
                subMenuBeforeMainMenu("SignIn");
                signin();
                getch();
            }
            else if (currentSelection == 3)
            {
                exit(0);
            }
            else
            {
                cout << "Invalid choice" << endl;
                getch();
            }
        }
    }
}

// LOGIN DATA

void storinglogindata(string new_user, string new_pass, string new_phone, string new_email, string new_role)
{
    fstream newfile1;
    newfile1.open("login.txt", ios::app);
    newfile1 << new_user << ",";
    newfile1 << new_pass << ",";
    newfile1 << new_phone << ",";
    newfile1 << new_email << ",";
    newfile1 << new_role << endl;
    newfile1.close();
}

void readlogindata()
{
    string record;
    fstream newfile1;
    newfile1.open("login.txt", ios::in);
    while (getline(newfile1, record))
    {
        username[num_users] = getfile(record, 1);
        password[num_users] = getfile(record, 2);
        email[num_users] = getfile(record, 3);
        contact_number[num_users] = getfile(record, 4);
        role[num_users] = getfile(record, 5);
        num_users++;
    }
    newfile1.close();
}

bool is_username_exist(string usern)
{
    for (int i = 0; i < num_users; i++)
    {
        if (usern == username[i])
        {
            return true;
        }
    }
    return false;
}

bool is_phone_exist(string phonen)
{
    for (int i = 0; i < num_users; i++)
    {
        if (phonen == contact_number[i])
        {
            return true;
        }
    }
    return false;
}

bool is_email_exist(string em)
{
    for (int i = 0; i < num_users; i++)
    {
        if (em == email[i])
        {
            return true;
        }
    }
    return false;
}
void signup()
{
    string usern, em, phonen, pass, rolee;

    cout << "Enter Username:";
    cin >> usern;
    if (is_username_exist(usern))
    {
        cout << "Username already exists" << endl;
        return;
    }

    cout << "Enter Password:";
    cin >> pass;

    int currenty = wherey();
input_phone:
    gotoxy(0, currenty);
    printspace();
    gotoxy(0, currenty);
    cout << "Enter Phone Number:";
    cin >> phonen;
    if (!(isInteger(phonen)))
    {
        cout << "Invalid input! Please enter a valid Phone Number. " << endl;
        getch();
        goto input_phone;
    }
    if (is_phone_exist(phonen))
    {
        cout << "Phone Number already in use" << endl;
        return;
    }

    int currentye = wherey();
input_email:
    gotoxy(0, currentye);
    printspace();
    gotoxy(0, currentye);
    cout << "Enter Email:";
    cin >> em;
    if (!(regex_match(em, email_regex)))
    {
        cout << "Invalid email address." << endl;
        getch();
        goto input_email;
    }
    if (is_email_exist(em))
    {
        cout << "Email already in use" << endl;
        return;
    }

    int currentyr = wherey();
input_role:
    gotoxy(0, currentyr);
    printspace();
    gotoxy(0, currentyr);
    cout << "Enter role(admin/student):";
    cin >> rolee;
    if (!(isString(rolee)))
    {
        cout << "Invalid input! Please enter a valid Role. " << endl;
        getch();
        goto input_role;
    }

    string new_user = usern;
    string new_pass = pass;
    string new_phone = phonen;
    string new_email = em;
    string new_role = rolee;
    storinglogindata(new_user, new_pass, new_email, new_phone, new_role);
    username[num_users] = new_user;
    password[num_users] = new_pass;
    email[num_users] = new_email;
    contact_number[num_users] = new_phone;
    role[num_users] = new_role;
    num_users++;
    num_signups++;
    cout << "Sign up Successfully";
}

bool is_valid_user(string un, string p)
{
    for (int i = 0; i < num_users; i++)
    {
        if (username[i] == un && password[i] == p)
        {
            return true;
        }
    }
    return false;
}

string get_role(string un)
{
    for (int i = 0; i < num_users; i++)
    {
        if (username[i] == un)
        {
            return role[i];
        }
    }
    return "";
}

void signin()
{
    string option;
    string un, p;
    cout << "Enter Username:";
    cin >> un;
    cout << "Enter Password:";
    cin >> p;

    if (is_valid_user(un, p))
    {
        string role1 = get_role(un);

        if (role1 == "Admin" || role1 == "admin")
        {
            setColor(10);
            cout << endl
                 << "        Welcome, " << un << "!" << endl;
            getch();
            displayscreen();
            MainMenu();
            setColor(15);
            cout << "Enter opton:";
            cin >> option;
            displayscreen();
            AdminsMenu();
            getch();
        }
        else if (role1 == "Student" || role1 == "student")
        {
            setColor(10);
            cout << endl
                 << "        Welcome, " << un << "!" << endl;
            getch();
            displayscreen();
            MainMenu();
            setColor(15);
            cout << "Enter opton:";
            cin >> option;
            displayscreen();
            StudentMenu();
            getch();
        }
        else
        {
            setColor(4);
            cout << "Invalid role";
        }
    }
    else
    {
        setColor(4);
        cout << "Incorrect Username or Password";
    }
}

// Displaying Menus Data

void StartupMenu()
{
    setColor(9); // Blue color
    cout << "1.     Sign Up" << endl;
    cout << "2.     Sign In" << endl;
    cout << "3.     Exit" << endl;
    setColor(15); // Blue color
}

void USMS()
{
    setColor(6);

    cout << "     $$\\   $$\\  $$$$$$\\  $$\\      $$\\  $$$$$$\\  " << endl;
    cout << "     $$ |  $$ |$$  __$$\\ $$$\\    $$$ |$$  __$$\\ " << endl;
    cout << "     $$ |  $$ |$$ /  \\__|$$$$\\  $$$$ |$$ /  \\__|" << endl;
    cout << "     $$ |  $$ |\\$$$$$$\\  $$\\$$\\$$ $$ |\\$$$$$$\\  " << endl;
    cout << "     $$ |  $$ | \\____$$\\ $$ \\$$$  $$ | \\____$$\\ " << endl;
    cout << "     $$ |  $$ |$$\\   $$ |$$ |\\$  /$$ |$$\\   $$ |" << endl;
    cout << "     \\$$$$$$  |\\$$$$$$  |$$ | \\_/ $$ |\\$$$$$$  |" << endl;
    cout << "      \\______/  \\______/ \\__|     \\__| \\______/ " << endl
         << endl
         << endl;
}
void mainUSMS()
{
    setColor(14);
    cout << "     $$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$\\ $$$$$$$$\\ $$$$$$$$\\ $$$$$$\\ $$$$$$$$\\  $$$$$$\\     $$\\   $$\\ $$$$$$$$\\ $$$$$$$$\\ " << endl;
    cout << "    $$  __$$\\ $$  __$$\\ $$  __$$\\ \\_$$  _|$$  _____|\\__$$  __|\\_$$  _|$$  _____|$$  __$$\\    $$ |  $$ |$$  _____|\\__$$  __|" << endl;
    cout << "    $$ /  \\__|$$ /  $$ |$$ /  \\__|  $$ |  $$ |         $$ |     $$ |  $$ |      $$ /  \\__|   $$ |  $$ |$$ |         $$ |   " << endl;
    cout << "    \\$$$$$$\\  $$ |  $$ |$$ |        $$ |  $$$$$\\       $$ |     $$ |  $$$$$\\    \\$$$$$$\\     $$ |  $$ |$$$$$\\       $$ |   " << endl;
    cout << "     \\____$$\\ $$ |  $$ |$$ |        $$ |  $$  __|      $$ |     $$ |  $$  __|    \\____$$\\    $$ |  $$ |$$  __|      $$ |   " << endl;
    cout << "    $$\\   $$ |$$ |  $$ |$$ |  $$\\   $$ |  $$ |         $$ |     $$ |  $$ |      $$\\   $$ |   $$ |  $$ |$$ |         $$ |   " << endl;
    cout << "    \\$$$$$$  | $$$$$$  |\\$$$$$$  |$$$$$$\\ $$$$$$$$\\    $$ |   $$$$$$\\ $$$$$$$$\\ \\$$$$$$  |$$\\\\$$$$$$  |$$$$$$$$\\    $$ |   " << endl;
    cout << "     \\______/  \\______/  \\______/ \\______|\\________|   \\__|   \\______|\\________| \\______/ \\__|\\______/ \\________|   \\__|   " << endl
         << endl
         << endl;
}

void MainMenu()
{
    setColor(11);
    subMenuBeforeMainMenu("Main Menu");
    string option;
    cout << "Select the category of the society:" << endl
         << endl;
    cout << "1.     Sports Societies" << endl;
    cout << "2.     Programming Societies" << endl;
    cout << "3.     Creative Art Societies" << endl;
    cout << "4.     Acedemic Societies" << endl;
    cout << "5.     Social and Recreational Societies" << endl;
    cout << "6.     Religious and Spirtual Societies" << endl;
    cout << "7.     Cultural Societies" << endl;
    cout << "8.     Artistic Societies" << endl;
    cout << "9.     Gaming Societies" << endl;
    cout << "10.    Political or activist Societies" << endl;
    setColor(4);
    cout << "11.    Exit" << endl;
    setColor(15);
    cout << "Enter option:";
    cin >> option;
    while (true)
    {
        displayscreen();
        if (option == "1")
        {
            submenu("Sports Society Menu");
            SportsSocietyMainMenu();
        }
        else if (option == "2")
        {
            submenu("Programming Society Menu");
            ProgrammingSocietiesMainMenu();
        }
        else if (option == "3")
        {
            submenu("Creative Art Society Menu");
            CreativeArtSocietiesMainMenu();
        }
        else if (option == "4")
        {
            submenu("Academic Society Menu");
            AcedemicSocietiesMainMenu();
        }
        else if (option == "5")
        {
            submenu("Social And Recreational Society Menu");
            SocialandRecreationalSocietyMainMenu();
        }
        else if (option == "6")
        {
            submenu("Religious And Spirual Society Menu");
            ReligiousandSpirtualSocietyMainMenu();
        }
        else if (option == "7")
        {
            submenu("Cultural Society Menu");
            CulturalSocietiesMainMenu();
        }
        else if (option == "8")
        {
            submenu("Artistic Society Menu");
            ArtisticSocietiesMainMenu();
        }
        else if (option == "9")
        {
            submenu("Gaming Society Menu");
            GamingSocietiesMainMenu();
        }
        else if (option == "10")
        {
            submenu("Political Society Menu");
            PoliticalOrActivistSocietiesMainMenu();
        }
        else if (option == "11")
        {
            main();
        }
        else
        {
            setColor(4);
            cout << "Invalid choice";
            getch();
            displayscreen();
            MainMenu();
        }
        break;
    }
}

void SportsSocietyMainMenu()
{
    cout << "Select any of the given societies:" << endl
         << endl;
    cout << "1.     Cricket Club" << endl;
    cout << "2.     Running Club" << endl;
    cout << "3.     Athletics Club" << endl;
    cout << "4.     Vollyball Club" << endl;
    cout << "5.     Tennis Club" << endl;
    cout << "6.     Swimming Club" << endl;
    cout << "7.     Squash Club" << endl;
    cout << "8.     Running Club" << endl;
    cout << "9.     Weight Lifting Club" << endl;
    cout << "10.    Martial Art Society" << endl;
    cout << "11.    Football Club" << endl;
    cout << "12.    Badminton Club" << endl;
    cout << "13.    Basketball Club" << endl;
    cout << "14.    Hockey Club" << endl;
    cout << "15.    Cross Country Club" << endl;
}
void ProgrammingSocietiesMainMenu()
{
    cout << "Select any of the given societies:" << endl
         << endl;
    cout << "1.     Computer Science Club" << endl;
    cout << "2.     Coding Society" << endl;
    cout << "3.     Hacker's Club" << endl;
    cout << "4.     Programmer's Society" << endl;
    cout << "5.     Tech Society" << endl;
    cout << "6.     Software Development Club" << endl;
    cout << "7.     Web Development Club" << endl;
    cout << "8.     Mobile Application Development Club" << endl;
    cout << "9.     Artificial Intelligence Society" << endl;
    cout << "10.    Cyber Security Club" << endl;
    cout << "11.    Game Development Club" << endl;
}
void CreativeArtSocietiesMainMenu()
{
    cout << "Select any of the given societies:" << endl
         << endl;
    cout << "1.     Photography Club" << endl;
    cout << "2.     Art Society" << endl;
    cout << "3.     Film Society" << endl;
    cout << "4.     Theater Club" << endl;
    cout << "5.     Creative Writing Society" << endl;
    cout << "6.     Poetry Club" << endl;
    cout << "7.     Graphic Design Society" << endl;
    cout << "8.     Animation Club" << endl;
    cout << "9.     Fashion Club" << endl;
    cout << "10.    Craft Society" << endl;
}
void AcedemicSocietiesMainMenu()
{
    cout << "Select any of the given societies:" << endl
         << endl;
    cout << "1.     Maths Club" << endl;
    cout << "2.     Science Club" << endl;
    cout << "3.     Engineering Club" << endl;
    cout << "4.     Bussiness Club" << endl;
    cout << "5.     Economics Society" << endl;
    cout << "6.     Political Science Club" << endl;
    cout << "7.     Phiosophy Society" << endl;
    cout << "8.     History Club" << endl;
    cout << "9.     English Club" << endl;
    cout << "10.    Literature Society" << endl;
    cout << "11.    Psychology Club" << endl;
    cout << "12.    Sociology Club" << endl;
    cout << "13.    Physics Club" << endl;
    cout << "14.    Biology Club" << endl;
    cout << "15.    Chemistry  Club" << endl;
}
void SocialandRecreationalSocietyMainMenu()
{
    cout << "Select any of the given societies:" << endl
         << endl;
    cout << "1.     Adventure Club" << endl;
    cout << "2.     Outdoor Activities Society" << endl;
    cout << "3.     Travel Club" << endl;
    cout << "4.     Environmental Club" << endl;
    cout << "5.     Board Game Society" << endl;
    cout << "6.     Food Club" << endl;
    cout << "7.     Human Rights Advocacy Group" << endl;
    cout << "8.     Student Government Association" << endl;
    cout << "9.     Debate Club" << endl;
    cout << "10.    Book Club" << endl;
}
void ReligiousandSpirtualSocietyMainMenu()
{
    cout << "Select any of the given societies:" << endl
         << endl;
    cout << "1.     Muslim Student Association" << endl;
    cout << "2.     Islamic Society" << endl;
    cout << "3.     Quran Study Group" << endl;
    cout << "4.     Prayer and Dhikr Circlr" << endl;
    cout << "5.     Da'wah Club" << endl;
    cout << "6.     Islamic Cultural Society" << endl;
    cout << "7.     Islamic Education Society" << endl;
    cout << "8.     Islamic Awareness Society" << endl;
    cout << "9.     Islamic Finance Society" << endl;
    cout << "10.     Halaqa(Study Circle)" << endl;
}

void CulturalSocietiesMainMenu()
{
    cout << "Select any of the given societies:" << endl
         << endl;
    cout << "1.     International Student Association" << endl;
    cout << "2.     African Cultural Society" << endl;
    cout << "3.     Asian Cultural Society" << endl;
    cout << "4.     Cultural Society" << endl;
    cout << "5.     Latin American Cultural Society" << endl;
    cout << "6.     Middle Eastern Cultural Society" << endl;
    cout << "7.     Native American Cultural Society" << endl;
    cout << "8.     Pacific Islander Cultural Society" << endl;
    cout << "9.     Caribbean Cultural Society" << endl;
    cout << "10.    South Asian Cultural Society" << endl;
    cout << "11.    Southeast Asian Cultural Society" << endl;
    cout << "12.    American Culture Society" << endl;
    cout << "13.    Australian Cultural Society" << endl;
    cout << "14.    Canadian Cultural Society" << endl;
    cout << "15.    New Zealand Cultural Society" << endl;
}

void ArtisticSocietiesMainMenu()
{
    cout << "Select any of the given societies:" << endl
         << endl;
    cout << "1.     Photography Club" << endl;
    cout << "2.     Film Society" << endl;
    cout << "3.     Drama Club" << endl;
    cout << "4.     Dance Collective" << endl;
    cout << "5.     Fine Arts Society" << endl;
    cout << "6.     Poetry Club" << endl;
    cout << "7.     Writing Workshop" << endl;
    cout << "8.     Graphic Design Club" << endl;
    cout << "9.     Interactive Media Club" << endl;
    cout << "10.    Digital Art Society" << endl;
    cout << "11.    Architecture Club" << endl;
    cout << "12.    Fashion Society" << endl;
    cout << "13.    Culinary Arts Society" << endl;
    cout << "14.    Glassblowing Society" << endl;
    cout << "15.    Performing Arts Society" << endl;
}

void GamingSocietiesMainMenu()
{
    cout << "Select any of the given societies:" << endl
         << endl;
    cout << "1.     Esports Club" << endl;
    cout << "2.     Tabletop Gaming Society" << endl;
    cout << "3.     Console Gaming Society" << endl;
    cout << "4.     PC Gaming Society" << endl;
    cout << "5.     Virtual Reality Club" << endl;
    cout << "6.     Mobile Gaming Society" << endl;
    cout << "7.     Retro Gaming Society" << endl;
    cout << "8.     Adventure Gaming Society" << endl;
    cout << "9.     Strategy Gaming Society" << endl;
    cout << "10.    Role-Playing Gaming Society" << endl;
    cout << "11.    Fighting Game Society" << endl;
    cout << "12.    Real-Time Strategy Society" << endl;
    cout << "13.    Survival Gaming Society" << endl;
    cout << "14.    First-Person Shooter Society" << endl;
    cout << "15.    Video Game Development Club" << endl;
}

void PoliticalOrActivistSocietiesMainMenu()
{
    cout << "Select any of the given societies:" << endl
         << endl;
    cout << "1.     Student Government Association" << endl;
    cout << "2.     College Republicans" << endl;
    cout << "3.     Environmental Action Group" << endl;
    cout << "4.     Advocacy Society" << endl;
    cout << "5.     Racial Justice League" << endl;
    cout << "6.     Economic Justice Alliance" << endl;
    cout << "7.     Disability Rights Group" << endl;
    cout << "8.     Animal Rights Society" << endl;
    cout << "9.     Human Rights Campaign" << endl;
    cout << "10.    Social Justice Alliance" << endl;
    cout << "11.    Voter Registration and Advocacy Club" << endl;
}

// Admin Menu

void AdminsMenu()
{
    setColor(11);
    submenu("Admin Menu");
    string option;
    cout << "1.     Add a Society" << endl;
    cout << "2.     Update a Society" << endl;
    cout << "3.     Remove a Society" << endl;
    cout << "4.     Display all the socities " << endl;
    cout << "5.     Check the feedback of the society" << endl;
    cout << "6.     Add a member in society" << endl;
    cout << "7.     Remove a member from Society" << endl;
    cout << "8.     Update a member of society" << endl;
    cout << "9.     Display the members of Society" << endl;
    cout << "10.    Edit the upcoming events of Society" << endl;
    cout << "11.    Display the upcoming events of Society" << endl;
    cout << "12.    Display the requests from the members of Society" << endl;
    cout << "13.    Edit the Society's mission and objectives folder" << endl;
    cout << "14.    See the donation from the members of society" << endl;
    cout << "15.    Display the Society's mission and objectives folder" << endl;
    setColor(4);
    cout << "16.    Exit" << endl;
    setColor(15);
    cout << "Enter option:";
    cin >> option;
    while (true)
    {
        displayscreen();
        if (option == "1")
        {
            addsociety();
        }
        else if (option == "2")
        {
            updatesociety();
        }
        else if (option == "3")
        {
            removesociety();
        }
        else if (option == "4")
        {
            displayadminsociety();
        }
        else if (option == "5")
        {
            displayfeedback();
        }
        else if (option == "6")
        {
            addmember();
        }
        else if (option == "7")
        {
            removemember();
        }
        else if (option == "8")
        {
            updatemember();
        }
        else if (option == "9")
        {
            displaymember_admin();
        }
        else if (option == "10")
        {

            editevent();
        }
        else if (option == "11")
        {

            displayevent();
        }
        else if (option == "12")
        {
            displayrequests();
        }
        else if (option == "13")
        {
            editsocietymission();
        }
        else if (option == "14")
        {
            displaydonation();
        }
        else if (option == "15")
        {
            displaysocietymission();
        }
        else if (option == "16")
        {
            MainMenu();
            getch();
            displayscreen();
            AdminsMenu();
            break;
        }
        else
        {
            setColor(4);
            cout << "Invalid option";
        }
        getch();
        displayscreen();
        AdminsMenu();
        break;
    }
}

// student Menu

void StudentMenu()
{
    setColor(11);
    submenu("Student Menu");
    string option;
    cout << "1.     Register Yourself" << endl;
    cout << "2.     Update Your Information" << endl;
    cout << "3.     Remove yourself if you are registered:" << endl;
    cout << "4.     Display the members of Society" << endl;
    cout << "5.     Display all the socities " << endl;
    cout << "6.     Give a feedback about the society" << endl;
    cout << "7.     See all the upcoming events" << endl;
    cout << "8.     Check the reviews about the society" << endl;
    cout << "9.     Submit a request" << endl;
    cout << "10.    View the society mission and objectives" << endl;
    cout << "11.    Donate to the society" << endl;
    setColor(4);
    cout << "12.    Exit" << endl;
    setColor(15);
    cout << "Enter option:";
    cin >> option;
    while (true)
    {
        displayscreen();
        if (option == "1")
        {
            addmember();
        }
        else if (option == "2")
        {
            updatemember();
        }
        else if (option == "3")
        {
            removemember();
        }
        else if (option == "4")
        {
            displaymember_student();
        }
        else if (option == "5")
        {
            displaystudentsociety();
        }
        else if (option == "6")
        {
            giveFeedback();
        }
        else if (option == "7")
        {
            displayevent();
        }
        else if (option == "8")
        {
            displayfeedback();
        }
        else if (option == "9")
        {

            submitRequest();
        }
        else if (option == "10")
        {
            displaysocietymission();
        }
        else if (option == "11")
        {
            donateToSociety();
        }
        else if (option == "12")
        {
            MainMenu();
            getch();
            displayscreen();
            StudentMenu();
            break;
        }
        else
        {
            setColor(4);
            cout << "Invalid option";
        }
        getch();
        displayscreen();
        StudentMenu();
        break;
    }
}

// Storing And Loading Data
void writedatinfile()
{
    fstream newfile2;
    newfile2.open("societydata.txt", ios::out);
    for (int i = 0; i < num_societies; i++)
    {
        newfile2 << society_name[i] << ",";
        newfile2 << soceiety_des[i] << ",";
        newfile2 << society_pres[i] << endl;
    }
    newfile2.close();
}

void writedatinfile1()
{
    fstream newfile3;
    newfile3.open("memberdata.txt", ios::out);
    for (int i = 0; i < num_members; i++)
    {
        newfile3 << society_member_username[i] << ",";
        newfile3 << society_member_email[i] << ",";
        newfile3 << society_member_phone[i] << endl;
    }
    newfile3.close();
}
void storesocietydata(string sn, string sd, string sp)
{
    fstream newfile2;
    newfile2.open("societydata.txt", ios::app);
    newfile2 << sn << ",";
    newfile2 << sd << ",";
    newfile2 << sp << endl;
    newfile2.close();
}

void readsocietydata()
{
    string record;
    fstream newfile2;
    newfile2.open("societydata.txt", ios::in);
    while (getline(newfile2, record))
    {
        society_name[num_societies] = getfile(record, 1);
        soceiety_des[num_societies] = getfile(record, 2);
        society_pres[num_societies] = getfile(record, 3);
        num_societies++;
    }
    newfile2.close();
}

void storememberdata(string mu, string me, string mp)
{
    fstream newfile3;
    newfile3.open("memberdata.txt", ios::app);
    newfile3 << mu << ",";
    newfile3 << me << ",";
    newfile3 << mp << endl;
    // newfile3 << role[num_signups] << endl;
    newfile3.close();
}

string getfile(string record, int field)
{
    int countcomma = 1;
    string item;
    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ',')
        {
            countcomma++;
        }
        else if (countcomma == field)
        {
            item = item + record[x];
        }
    }
    return item;
}

void readmemberdata()
{
    string record;
    fstream newfile3;
    newfile3.open("memberdata.txt", ios::in);
    while (getline(newfile3, record))
    {

        society_member_username[num_members] = getfile(record, 1);
        society_member_email[num_members] = getfile(record, 2);
        society_member_phone[num_members] = getfile(record, 3);
        num_members++;
    }
    newfile3.close();
}

void storefeedback(string f)
{
    fstream newfile2;
    newfile2.open("feedbackdata.txt", ios::app);
    newfile2 << f << endl;
    newfile2.close();
}

void loadfeedback()
{
    string feedback;
    fstream newfile2;
    newfile2.open("feedbackdata.txt", ios::in);
    while (getline(newfile2, feedback))
    {
        feedbackss[num_feedb] = feedback;
        num_feedb++;
    }
    newfile2.close();
}

void storereq(string req)
{
    fstream newfile4;
    newfile4.open("requestsdata.txt", ios::app);
    newfile4 << req << endl;
    newfile4.close();
}

void loadreq()
{
    string req;
    fstream newfile4;
    newfile4.open("requestsdata.txt", ios::in);
    while (getline(newfile4, req))
    {
        requests[num_request] = req;
        num_request++;
    }
    newfile4.close();
}

void storedonation(string don)
{
    fstream newfile5;
    newfile5.open("donationdata.txt", ios::app);
    newfile5 << don << endl;
    newfile5.close();
}

void loaddonation()
{
    string d;
    fstream newfile5;
    newfile5.open("donationdata.txt", ios::in);
    while (getline(newfile5, d))
    {
        donation_amount[num_donations] = d;
        num_donations++;
    }
    newfile5.close();
}

// Admin And Student Functionalities

void addsociety()
{
    int currentyn = wherey();
input_name_again:
    gotoxy(0, currentyn);
    printspace();
    gotoxy(0, currentyn);
    cout << " Enter Society Name:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, society_name[num_societies]);
    if (!(isString(society_name[num_societies])))
    {
        cout << "Invalid input! Please enter a valid Society Name. " << endl;
        getch();

        goto input_name_again;
    }

    int currentyd = wherey();
input_des_again:
    gotoxy(0, currentyd);
    printspace();
    gotoxy(0, currentyd);
    cout << "Enter Society decription:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, soceiety_des[num_societies]);
    if (!(isString(soceiety_des[num_societies])))
    {
        cout << "Invalid input! Please enter a valid Society Description. " << endl;
        getch();

        goto input_des_again;
        ;
    }

    int currentyp = wherey();
input_pres_again:
    gotoxy(0, currentyp);
    printspace();
    gotoxy(0, currentyp);
    cout << "Enter Society president:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, society_pres[num_societies]);
    if (!(isString(society_pres[num_societies])))
    {
        cout << "Invalid input! Please enter a valid Society's President Name. " << endl;
        getch();

        goto input_pres_again;
    }

    if (isString(society_name[num_societies]) && isString(soceiety_des[num_societies]) && isString(society_pres[num_societies]))
    {
        storesocietydata(society_name[num_societies], soceiety_des[num_societies], society_pres[num_societies]);
        num_societies++;
    }
    cout << " Press any key to continue..." << endl;
}

void updatesociety()
{
    bool flag = false;
    string p_s_n, n_s_n;
    cout << " Enter Society's previous name: " << endl;
    cin.clear();
    cin.sync();
    getline(cin, p_s_n);
    cout << " Enter Society's new name:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, n_s_n);
    for (int i = 0; i < num_societies; i++)
    {
        if (p_s_n == society_name[i])
        {
            society_name[i] = n_s_n;
            flag = true;
            writedatinfile();
        }
    }
    if (flag == false)
    {
        cout << "Society name not found!" << endl;
    }
    cout << " Press any key to continue..." << endl;
}

void removesociety()
{
    bool flag = false;
    string rns;
    cout << " Enter Society's name which you want to remove:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, rns);
    for (int i = 0; i < num_societies; i++)
    {
        if (rns == society_name[i])
        {
            society_name[i] = " ";
            flag = true;
            writedatinfile();
        }
    }
    if (flag == false)
    {
        cout << "Society name not found!" << endl;
    }
    cout << " Press any key to continue..." << endl;
}

void displayadminsociety()
{
    setColor(8);
    cout << "   Societies     \t\tSociety Prseidents\t\tSociety Descriptions" << endl
         << endl;
    for (int i = 0; i < num_societies; i++)
    {
        if (society_name[i] == " ")
        {
            continue;
        }
        setColor(4);
        cout << i + 1 << ". ";
        setColor(7);
        cout << society_name[i] << "\t\t" << society_pres[i] << "\t\t\t" << soceiety_des[i] << endl;
    }
}

void displaystudentsociety()
{
    setColor(8);
    cout << "    Societies    " << endl
         << endl;
    for (int i = 0; i < num_societies; i++)
    {
        if (society_name[i] == " ")
        {
            continue;
        }
        setColor(4);
        cout << i + 1 << ".";
        setColor(7);
        cout << society_name[i] << endl;
    }
}

void addmember()
{
    int currentyu = wherey();
input_name_again:
    gotoxy(0, currentyu);
    printspace();
    gotoxy(0, currentyu);
    cout << " Enter Username:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, society_member_username[num_members]);
    if (!(isString(society_member_username[num_societies])))
    {
        cout << "Invalid input! Please enter a valid Username. " << endl;
        getch();

        goto input_name_again;
    }

    int currentyr = wherey();
input_email_again:
    gotoxy(0, currentyr);
    printspace();
    gotoxy(0, currentyr);
    cout << " Enter Email:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, society_member_email[num_members]);
    if (!(regex_match(society_member_email[num_members], email_regex)))
    {
        cout << "Invalid email address." << endl;
        getch();
        goto input_email_again;
    }

    int currentyp = wherey();
input_phone_again:
    gotoxy(0, currentyp);
    printspace();
    gotoxy(0, currentyp);
    cout << " Enter Contact Number:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, society_member_phone[num_members]);
    if (!(isInteger(society_member_phone[num_societies])))
    {
        cout << "Invalid input! Please enter a valid Society Name. " << endl;
        getch();

        goto input_phone_again;
    }

    if (isString(society_member_username[num_societies]) && isInteger(society_member_phone[num_societies]) && regex_match(society_member_email[num_members], email_regex))
    {
        storememberdata(society_member_username[num_members], society_member_email[num_members], society_member_phone[num_members]);
        num_members++;
    }

    cout << " Press any key to continue..." << endl;
}

void updatemember()
{
    bool flag = false;
    string pu, nu;
    cout << " Enter member's previous username: " << endl;
    cin.clear();
    cin.sync();
    getline(cin, pu);
    cout << " Enter member's new username:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, nu);
    for (int i = 0; i < num_members; i++)
    {
        if (pu == society_member_username[i])
        {
            society_member_username[i] = nu;
            writedatinfile1();
            flag = true;
        }
    }
    if (flag == false)
    {
        cout << "Member name not found!" << endl;
    }
    cout << " Press any key to continue..." << endl;
}

void removemember()
{
    bool flag = false;
    string rm;
    cout << " Enter Member's name which you want to remove:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, rm);
    for (int i = 0; i < num_members; i++)
    {
        if (rm == society_member_username[i])
        {
            society_member_username[i] = " ";
            writedatinfile1();
            flag = true;
        }
    }
    if (flag == false)
    {
        cout << "Member name not found!" << endl;
    }
    cout << " Press any key to continue..." << endl;
}

void displaymember_admin()
{
    setColor(8);
    cout << "Members  \t\t\tEmails     \t\t\tPhone#" << endl
         << endl;

    for (int i = 0; i < num_members; i++)
    {
        if (society_member_username[i] == " ")
        {
            continue;
        }
        setColor(7);
        cout << society_member_username[i] << "\t\t\t\t" << society_member_email[i] << "\t\t\t" << society_member_phone[i] << endl;
    }
}

void displaymember_student()
{
    setColor(8);
    cout << "Members" << endl;

    for (int i = 0; i < num_members; i++)
    {
        if (society_member_username[i] == " ")
        {
            continue;
        }
        setColor(7);
        cout << society_member_username[i] << endl;
    }
}

void giveFeedback()
{

    int currentyf = wherey();
input_feedback_again:
    gotoxy(0, currentyf);
    printspace();
    gotoxy(0, currentyf);
    cout << " Write your feedback:" << endl;
    cin.ignore();
    getline(cin, feedbackss[num_feedb]);
    if (!(isString(feedbackss[num_feedb])) || feedbackss[num_feedb] == "")
    {
        cout << "Invalid Input! Please enter a Valid Feedback " << endl;
        getch();

        goto input_feedback_again;
    }
    else
    {
        storefeedback(feedbackss[num_feedb]);
        num_feedb++;
    }
    cout << " Press any key to continue..." << endl;
}

void displayfeedback()
{
    if (num_feedb == 0)
    {
        cout << "No feedbacks to display" << endl;
    }
    else
    {
        for (int i = 0; i < num_feedb; i++)
        {
            setColor(6);
            cout << username[i] << " : ";
            setColor(1);
            cout << feedbackss[i] << endl;
        }
    }
}

void editevent()
{
    int currentyp = wherey();
input_event_again:
    gotoxy(0, currentyp);
    printspace();
    gotoxy(0, currentyp);
    string n_event;
    cout << " Write the Upcoming events: " << endl;
    cin.clear();
    cin.sync();
    getline(cin, n_event);
    if (n_event == " " || n_event == "")
    {
        cout << "This section cannot be left blank!" << endl;
        goto input_event_again;
    }
    else
    {
        event[0] = n_event;
    }
    cout << " Press any key to continue..." << endl;
}

void displayevent()
{
    setColor(2);
    cout << event[0];
}

void submitRequest()
{
    int currentyp = wherey();
input_request_again:
    gotoxy(0, currentyp);
    printspace();
    gotoxy(0, currentyp);
    string request;
    cout << " Write your request:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, requests[num_request]);
    if (!(isString(requests[num_request])) || requests[num_request] == "")
    {
        cout << "Invalid Input! Please enter Request in a correct syntax " << endl;
        getch();
        goto input_request_again;
    }
    else
    {
        storereq(requests[num_request]);
        num_request++;
    }
    cout << "  Press any key to continue..." << endl;
}

void displayrequests()
{
    if (num_request == 0)
    {
        cout << "No requests at this time";
    }
    for (int i = 0; i < num_request; i++)
    {
        setColor(6);
        cout << i + 1 << ".";
        setColor(1);
        cout << requests[i] << endl;
    }
}

void editsocietymission()
{
    int currentyp = wherey();
input_mission_again:
    gotoxy(0, currentyp);
    printspace();
    gotoxy(0, currentyp);
    string n_mission;
    cout << " Write the society's new missions and objectives:" << endl;
    cin.clear();
    cin.sync();
    getline(cin, n_mission);
    if (n_mission == " " || n_mission == "")
    {
        cout << "This section cannot be left blank!" << endl;
        goto input_mission_again;
    }
    else
    {
        mission[0] = n_mission;
    }
    // cout << " Press any key to continue..." << endl;
}

void displaysocietymission()
{
    setColor(2);
    cout << mission[0];
}

void donateToSociety()
{
    int currentyp = wherey();
input_donation_again:
    gotoxy(0, currentyp);
    printspace();
    gotoxy(0, currentyp);
    string donation;
    cout << " Enter the amount you want to donate in Rupees:";
    cin.clear();
    cin.sync();
    getline(cin, donation_amount[num_donations]);
    if (!(isInteger(donation_amount[num_donations])) && donation_amount[num_donations] == "")
    {
        cout << "Invalid Input! Please enter Donation in a correct syntax " << endl;
        getch();
        goto input_donation_again;
    }
    else
    {
        storedonation(donation_amount[num_donations]);
        num_donations++;
    }
    cout << " Press any key to continue..." << endl;
}

void displaydonation()
{
    if (num_donations == 0)
    {
        cout << "No donations at this time";
    }
    for (int i = 0; i < num_donations; i++)
    {
        setColor(6);
        cout << username[i + 1] << " : ";
        setColor(1);
        cout << donation_amount[i];
        setColor(4);
        cout << " Rs" << endl;
    }
}

// Sub Menus

void subMenuBeforeMainMenu(string submenu)
{
    setColor(11);
    string message = submenu + " Menu";
    cout << "             " << message << endl;
    cout << "-----------------------------------" << endl;
}

void submenu(string submenu)
{
    setColor(11);
    string message = " Main Menu > " + submenu;
    cout << "            " << message << endl;
    cout << "    -----------------------------------------------" << endl;
}

// Time and Main Headers

void clearscreen()
{
    cout << "Press any key to Continue.." << endl;
    getch();
    system("cls");
}

void displaytime()
{
    setColor(15);
    cout << "Date: " << __DATE__ << endl;
    cout << "Time:" << __TIME__ << endl
         << endl
         << endl;
}

void displayscreen()
{
    system("cls");
    displaytime();
    USMS();
}

void displayscreen1()
{
    system("cls");
    displaytime();
    mainUSMS();
}

// For hiding curssor

void hideCursor()
{

    HANDLE console;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;
    cursor.bVisible = false;
    SetConsoleCursorInfo(console, &cursor);
}

void disableCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &info);
}
// For Setting Colors
void setColor(int colorCode)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, colorCode);
}

// Valdation Functions

bool isString(string str)
{
    char c;
    for (int i = 0; i < str.length(); i++)
    {
        if ((!isalpha(str[i])) && str[i] != ' ')
        {
            return false;
        }
    }
    return true;
}
bool isInteger(string str)
{

    for (int i = 0; i < str.length(); i++)
    {
        if ((!isdigit(str[i])) && str[i] != ' ')
        {
            return false;
        }
    }
    return true;
}

int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(
            GetStdHandle(STD_OUTPUT_HANDLE),
            &csbi))
        return -1;
    return csbi.dwCursorPosition.Y;
}

void printspace()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}