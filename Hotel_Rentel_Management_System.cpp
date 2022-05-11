
#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include <pqxx/pqxx> 

//hotel_rentel_management_system

using namespace std;
using namespace pqxx;
class hotel
{
private:
    char c1;
public:
    const char* sql;

    int showInfoMenu();
    void addrooms();
    void deleterooms();
    void updaterooms();
    void selectrooms();
};
class search1
{
public:
    int  room_search();
    int room_type();
    int floor_num();
    int room_rent();
    int date();
};
class guest_info
{
private:
    char c1;
public:
    const char* sql;

    int showguestInfoMenu();
    void addguest();
    void check_out();
    void report();
    int vacancy();
    int occupied();
    int history();
};


void hotel::addrooms()
{
    system("CLS");


    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            int room_num, room_rent;

            string room_type, floor_num;
            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*      INSERTING ROOM INFORMATION SCREEN     *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;



                cout << "Enter the Room number      :"; cin >> room_num;

                cout << "Enter the ROOM TYPE        :"; cin >> room_type;
                cout << "Enter the FLOOR NUMBER     :"; cin >> floor_num;
                cout << "Enter the ROOM RENT        :"; cin >> room_rent;



                std::string sql = "insert into hotel_rooms_info values(" + std::to_string(room_num) + "," + "'" + (room_type)+"'" + ", \
            " + "'" + (floor_num)+"'" + "," + std::to_string(room_rent) + ", 'No' )";


                work W(C);
                W.exec(sql);
                W.commit();
                cout << " Do you want to you continue to add Rooms Information ... press (y/n)";
                cin >> c1;
            } while (c1 == 'y');

            cout << "Rooms Information records created successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }

    showInfoMenu();

}
void hotel::deleterooms()
{
    system("CLS");

    try {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open()) {



            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*       REMOVING ROOM INFORMATION SCREEN     *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;


                int room_num;
                cout << "Enter the Room number to be Delete :"; cin >> room_num;


                std::string sql = "delete from hotel_rooms_info where room_Number = (" + std::to_string(room_num) + ")";


                work W(C);

                W.exec(sql);
                W.commit();
                cout << endl;
                cout << "Do you want to delete Rooms information again?... press (y/n)";
                cin >> c1;

            } while (c1 == 'y');
            cout << endl;
            cout << "Rooms information Records Deleted Successfully" << endl;
            _getch();
        }
        else {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }

    showInfoMenu();
}
void hotel::updaterooms()
{
    system("CLS");

    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*      UPDATION OF ROOM INFORMATION SCREEN   *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;

                string u_choice, u_col;
                int room_num;
                cout << "Enter the Room number that need to be updated:"; cin >> room_num;
                cout << endl;

                cout << "Enter the Field that need to be updated" << endl;;
                
                cout << "\t=> Room_type  " << endl;
                cout << "\t=> Floor_number " << endl;
                cout << "\t=> Room_rent " << endl;
                

                cout << "Enter your choice of field : ";cin >> u_col;

                if (u_col == "Room_type" || u_col == "Floor_number" || u_col == "Room_rent" )
                {

                    
                    cout << "Enter the updatation: ";cin >> u_choice;
                    
                    std::string sql = "update hotel_rooms_info set " + (u_col)+" = " + "'" + (u_choice)+"'" + "  where room_number = (" +std::to_string(room_num) + ")";

                    work W(C);

                    W.exec(sql);
                    W.commit();
                    cout << "Do you want to you continue to update ?... press [y/n]";
                    cin >> c1;
                }
                else
                {
                    cout << endl;
                    cout << "Entered Field is incorrect\n";
                    cout << "Please re-Enter your choice correctly:";
                    _getch();
                    updaterooms();
                }
            } while (c1 == 'y');

            cout << "Room's Records Updated successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    showInfoMenu();
}
void hotel::selectrooms()
{
    system("CLS");
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            int room_num;
            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*           ROOM INFORMATION SCREEN          *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;


                cout << endl << endl;
                cout << "Enter the Room number : "; cin >> room_num;
                cin.ignore();
                cout << endl;
                cout << "Room number Entered : " << room_num;

                std::string sql = "select * from hotel_rooms_info where room_number = (" + std::to_string(room_num) + ")";

                work W(C);
                cout << endl << endl;
                cout << "Room's Information :" << endl << endl;

                result R(W.exec(sql));
                for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                    cout << "\t Room_Number     = " << c[0].as<int>() << endl;
                    cout << "\t Room_type       = " << c[1].as<string>() << endl;
                    cout << "\t Floor_Number    = " << c[2].as<string>() << endl;
                    cout << "\t Room_rent       = " << c[3].as<int>() << endl;
                    cout << "\t Occupied Status = " << c[4].as<string>() << endl;


                }
                W.commit();
                cout << endl;
                cout << "Do you want to you continue to Search Rooms information again... press [y/n]";
                cin >> c1;
            } while (c1 == 'y');

        }

        else
        {
            cout << "Can't open database" << endl;

        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }

    showInfoMenu();

}

int search1::room_type()
{

    char c1;

    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            string room_type;int t = 1;


            do
            {

                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*               SEARCHING ROOMS              *" << endl;
                cout << setw(60) << "*            ACCORDING TO ROOM TYPE          *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl << endl;

                
                
                cout << "Room Types:  " << endl;
                cout << " => Delux       " << endl;
                cout << " => Family_suit " << endl;
                cout << " => AC          " << endl;
                cout << " => Non-AC      " << endl;
                cout << " => Standard    " << endl<<endl;

                cout << "Enter The Type of Room For Searching : " << endl;

                cin >> room_type;


                std::string sql = " select Room_Number,Floor_Number,Room_rent from hotel_rooms_info where Room_type = (""'" + (room_type)+"'" + ")";
                work W(C);
                cout << endl << endl;
                cout << "Room type wise Room Details:" << endl << endl;

                
                cout << "=============================================================" << endl;
                cout << "|S.No      |  ROOM_NUMBER  |   FLOOR_NUMBER  |   ROOM_RENT  |" << endl;
                cout << "=============================================================" << endl;
                result R(W.exec(sql));

                for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                    cout << "|" << t << "\t   |\t" << c[0].as<int>() << "\t   |\t" << c[1].as<string>()<< "\t     |" << " \t" << c[2].as<int>() << "\t    |" << endl;
                    t++;
                }
                cout << "-------------------------------------------------------------" << endl;

                W.commit();
                cout << "Do you want to you continue to Search again... press [y/n]";
                cin >> c1;
            } while (c1 == 'y');
        }
        else
        {
            cout << "Can't open database" << endl;

        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    room_search();
}
int search1::floor_num()
{    char c1;

    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {


            do
            {

                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*               SEARCHING ROOMS              *" << endl;
                cout << setw(60) << "*           ACCORDING TO FLOOR NUMBER        *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl << endl;

                string floor_num;int t = 1;

                cout << "Enter The Floor Number To Search the Room: "; cin >> floor_num;


                std::string sql = " select Room_Number , Room_type, Room_rent from hotel_rooms_info where floor_number = (""'" + (floor_num)+"'" + ")";
                work W(C);
                cout << endl << endl;
                cout << "Room Details according to Floor Number:" << endl << endl;

                
                cout << "=============================================================================" << endl;
                cout << "|S.No      |  ROOM_NUMBER  |         ROOM_TYPE          |      ROOM_RENT    |" << endl;
                cout << "=============================================================================" << endl;
                result R(W.exec(sql));

                for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                    cout << "|" << t << "\t   |\t"  << c[0].as<int>() << "\t   |\t" << setw(10)<< setw(10) << c[1].as<string>() << setw(10) << "\t|" << " \t" << c[2].as<int>() << "\t    |" << endl;

                    t++;
                }
                cout << "-----------------------------------------------------------------------------" << endl;

                W.commit();
                cout << "Do you want to you continue to Search again... press [y/n]";
                cin >> c1;
            } while (c1 == 'y');
        }
        else
        {
            cout << "Can't open database" << endl;

        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    room_search();
}
int search1::room_rent()
{
    char c1;

    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {


            do
            {

                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*               SEARCHING ROOMS              *" << endl;
                cout << setw(60) << "*           ACCORDING TO PRICE RANGE         *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl << endl;

                int room_rent, room_rent1,t = 1;
                
                cout << "Enter The Minimum Price of Room to Search :"; cin >> room_rent;
                cout << "Enter The Maximum Price of Room to Search :"; cin >> room_rent1;


                std::string sql = " select Room_Number , Room_type, floor_number,room_rent from hotel_rooms_info where room_rent >= (" + std::to_string(room_rent) +") and room_rent <=("+ std::to_string(room_rent1) + ")";
                work W(C);
                cout << endl << endl;
                cout << "Room Details according to Price of a Room:" << endl << endl;


                cout << "=====================================================================================" << endl;
                cout << "|S.No      |  ROOM_NUMBER  |       ROOM_TYPE      |     FLOOR_NUMBER |   ROOM_RENT  |" << endl ;
                cout << "=====================================================================================" << endl;
                result R(W.exec(sql));               
                for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                    cout <<"|" << t << "\t   |\t" << c[0].as<int>() << "\t   |\t" << setw(10) << c[1].as<string>() << "\t  |\t" << c[2].as<string>() <<"\t     |"<<" \t" << c[3].as<int>() << "\t    |" << endl;
                    t++;
                }
                cout << "-------------------------------------------------------------------------------------" << endl;

                W.commit();
                cout << endl << endl;
                cout << "Do you want to you continue to Search again... press [y/n]";
                cin >> c1;
            } while (c1 == 'y');
        }
        else
        {
            cout << "Can't open database" << endl;

        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }

    room_search();
}
int search1::date()
{
    char c1;

    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*                                            *" << endl;
                cout << setw(60) << "*               SEARCHING ROOMS              *" << endl;
                cout << setw(60) << "*    ACCORDING TO DATE OF GUEST CHECK-IN     *" << endl;
                cout << setw(60) << "*                                            *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl << endl;

                string date;int t = 1;

                cout << "Enter The Date To Search the Room Ocuppied: "; cin >> date;


                std::string sql = " select a.room_number,a.room_type,a.floor_number,b.first_name,b.mobile_number,b.city,b.check_in_date,a.room_rent \
                    from hotel_rooms_info as a, guest_info as b   \
                where b.check_in_date = (""'" + (date)+"'" + ")\
                    and a.room_number = b.room_alloted_number\
                    and a.occupied_status = 'No' ";
                    
                    
                work W(C);
                cout << endl << endl;
                cout << "Room Details according to Date :" << endl << endl;

                cout << "==============================================================================================================================================================" << endl;
                cout << "|S.No      |  ROOM_NUMBER  |  ROOM_TYPE   |   FLOOR_NUMBER   |    NAME     |    MOBILE_NUMBER     |         CITY           |    Check_IN Date    | ROOM_RENT |" << endl;
                cout << "==============================================================================================================================================================" << endl;
                result R(W.exec(sql));
                for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                    cout << "|" << t << "\t   |\t" << c[0].as<int>() << "\t   |\t" << c[1].as<string>() << "\t  |\t" << c[2].as<string>() << "\t     |" << " \t" << c[3].as<string>() << "\t   |\t" << c[4].as<double>() << "\t  |\t" << c[5].as<string>() << "\t   |   \t"<< c[6].as<string>() << "\t | " << c[7].as<int>() << "\t     |" << endl;
                    t++;
                }
                cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

                W.commit();
                cout << "Do you want to you continue to Search again... press [y/n]";
                cin >> c1;
            } while (c1 == 'y');
        }
        else
        {
            cout << "Can't open database" << endl;

        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    room_search();
}


void guest_info::addguest()
{
    system("CLS");

    const char* sql1;
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {



            double mob_num,room_all;
            string check_in;

            string first_name,last_name,mail,city;
            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*          ALLOTING ROOM FOR  GUEST          *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;



                cout << "Enter the First Name          :"; cin >> first_name;
                cout << "Enter the Last Name           :"; cin >> last_name;
                cout << "Enter the Mobile Number       :"; cin >> mob_num;
                cout << "Enter the Email-Id            :"; cin >> mail;
                cout << "Enter the CITY                :"; cin >> city;

                cout << "Enter the ROOM Alloted Number :"; cin >> room_all;


                cout << "Enter the Check-IN Date  [yyyy-mm-dd]      :"; cin >> check_in;

                std::string sql = "insert into guest_info  values(""'" +(first_name) +"'"+ "," + "'" + (last_name)+"'" + ", \
            " + std::to_string(mob_num) + "," + "'" + (mail)+"'" + ", " + "'" + (city)+"'" + "," + std::to_string(room_all) + ","+"'" +(check_in) +"'"")";
              
               std::string sql1="update hotel_rooms_info set occupied_status = 'Yes'\
                where room_number = ("+std::to_string(room_all)+ ")";

                work W(C);
                W.exec(sql);
                W.exec(sql1);
                W.commit();
                cout << endl;
                cout << " Do you want to you continue to add Guest Allotment ... press (y/n)";
                cin >> c1;
                
            } while (c1 == 'y');

            cout << "Guest records created successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }

    showguestInfoMenu();

}
void guest_info::check_out()
{
    system("CLS");
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            double mob_num, room_all;
            string  check_out;

            
            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*            GUEST Check-Out SCREEN          *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;

                cout << "Enter the Alloted Room Number :"; cin >> room_all;
                cout << "Enter the Mobile Number for Checking-out  :"; cin >> mob_num;

                cout << "Enter the Check-OUT Date [yyyy-mm-dd]     :"; cin >> check_out;

                std::string sql = "update guest_info set check_out_date =(" "'" + (check_out)+"'" + ") \
                    where mobile_number =(" + std::to_string(mob_num) + ")";

                std::string sql1 = "update hotel_rooms_info  set occupied_status = 'No'\
                where room_number = (" + std::to_string(room_all) + ")";

                work W(C);
                W.exec(sql);
                W.exec(sql1);
                W.commit();
                cout << endl;
                cout << " Do you want to you continue to add Guest Information ... press (y/n)";
                cin >> c1;

            } while (c1 == 'y');

            cout << "Guest Checked out successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }

    showguestInfoMenu();
}


void delay(unsigned int mseconds) {
    // Storing start time 
    clock_t startTime = clock();
    // looping till required time is not acheived 
    while (clock() < (startTime + mseconds));
}
void title() {
    cout << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t**************************************************" << endl;
    cout << "\t\t\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t\t\t*                    WELCOME TO                  *" << endl;
    cout << "\t\t\t\t\t\t*           HOTEL RENTAL MANAGEMENT SYSTEM       *" << endl;
    cout << "\t\t\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t\t\t**************************************************" << endl;
}
void exitSys() {
    system("cls");
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t*********************************************" << endl;
    cout << "\t\t\t\t\t\t*                                           *" << endl;
    cout << "\t\t\t\t\t\t*        You have exited the system!        *" << endl;
    cout << "\t\t\t\t\t\t*                 Thank You!                *" << endl;
    cout << "\t\t\t\t\t\t*        For Using Choosing Our Hotel!      *" << endl;
    cout << "\t\t\t\t\t\t*                                           *" << endl;
    cout << "\t\t\t\t\t\t*********************************************" << endl;
    cout << "\t\t\t\t\t\t   Press enter to exit the program!" << endl;
    (void)_getch();
    exit(0);
}
int menu()
{
    system("cls");
    search1 room;
    hotel rooms;
    guest_info guest;
    int opt;
    cout << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t*         1. Manage Hotel Rooms informations      *" << endl;
    cout << "\t\t\t\t\t\t*         2. Search Rooms in Hotel                *" << endl;
    cout << "\t\t\t\t\t\t*         3. Manage Guest Check-in/Ckeck-out      *" << endl;
    cout << "\t\t\t\t\t\t*         4. Report                               *" << endl;
    cout << "\t\t\t\t\t\t*         5. Exit                                 *" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\tPlease enter your choose: "; cin >> opt;
    cin.ignore();
    switch (opt) {
    case 1: {
        system("cls");
        rooms.showInfoMenu();
    }
          break;

    case 2: {
        system("cls");
        room.room_search();
    }
          break;

    case 3: {
        system("cls");
        guest.showguestInfoMenu();
    }
          break;
    case 4: {
        system("cls");
        guest.report();
    }
          break;

    case 5: {
        system("cls");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t*********************************************" << endl;
        cout << "\t\t\t\t\t\t*                                           *" << endl;
        cout << "\t\t\t\t\t\t*        You have exited the system!        *" << endl;
        cout << "\t\t\t\t\t\t*                 Thank You!                *" << endl;
        cout << "\t\t\t\t\t\t*        For Using Choosing Our Hotel!      *" << endl;
        cout << "\t\t\t\t\t\t*                                           *" << endl;
        cout << "\t\t\t\t\t\t*********************************************" << endl;
        cout << endl << endl << endl;
        exit(0);
    }
          break;

    default: {
        system("cls");
        cout << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t   Sorry! The system do not have this function!" << endl;
        cout << "\t\t\t\t\t\tPress any key to continue!" << endl;
        (void)getchar();
        menu();
    }

           return 0;


    }

}
void loginScreen() {
   

    string userName;
    string password, get_password;
    connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
    int test = 0;
    bool check = false;
    system("CLS");

    do {
        system("cls");
        title();
        cout << endl;

        cout << "\t\t\t\t\t\t   ********************************************" << endl;
        cout << "\t\t\t\t\t\t   *                LOGIN SCREEN              *" << endl;
        cout << "\t\t\t\t\t\t   ********************************************" << endl;

        cout << endl;
        cout << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t   Username: ";
        cin >> userName;
        cout << "\t\t\t\t\t\t   Password: ";
        cin >> password;
        cin.ignore();
        std::string sql = "select Password from Login_credentials where User_name = (""'" + (userName)+"'" + ")";
        work W(C);

        result R(W.exec(sql));
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {

            get_password = c[0].as<string>();
        }
        W.commit();
        if (get_password == password)
        {
            cout << endl << endl << endl;
            cout << "\t\t\t\t\t\t   Login successfully!" << endl;
            cout << "\t\t\t\t\t\t   Press any key to continue!";
            (void)_getch();


            menu();
            check = true;

        }

        else {
            system("cls");
            test++;
            cout << endl << endl << endl << endl << endl << endl;
            cout << "\t\t\t\t\t\tYou are only allowed to try 3 times. You just have " << (3 - test) << " times left!" << endl;
            cout << "\t\t\t\t\t\tPress any key to continue!" << endl;
            (void)getchar();
            if (test == 3) {
                cout << "\t\t\tYou have entered the wrong username or password 3 times and you are not allowed to login to the system!" << endl;
                (void)getchar();
                exitSys();

            }
        }
    } while (!check);



}


int search1::room_search()
{
    system("cls");

    int opt1;
    cout << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t*       1. Search Rooms By Room Type              *" << endl;
    cout << "\t\t\t\t\t\t*       2. Search Rooms By Floor Number           *" << endl;
    cout << "\t\t\t\t\t\t*       3. Search Rooms By Room Rent              *" << endl;
    cout << "\t\t\t\t\t\t*       4. Search Rooms By Date                   *" << endl;
    cout << "\t\t\t\t\t\t*       5. Main Menu                              *" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\tPlease enter your choose: "; cin >> opt1;
    cin.ignore();
    switch (opt1) {
    case 1: {
        system("cls");
        room_type();
    }
          break;

    case 2: {
        system("cls");
        floor_num();
    }
          break;
    case 3: {
        system("cls");
        room_rent();
    }
          break;
    case 4: {
        date();
    }
          break;
    case 5: {
        menu();
    }
          break;

    default: {
        system("cls");
        cout << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t   Sorry! The system do not have this function!" << endl;
        cout << "\t\t\t\t\t\tPress any key to continue!" << endl;
        (void)getchar();
        menu();
    }
           return 0;

    }

}
int hotel::showInfoMenu() {
    system("cls");
   
    int option;
    cout << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t*         1. Add Room informations                *" << endl;
    cout << "\t\t\t\t\t\t*         2. Modify Room informations             *" << endl;
    cout << "\t\t\t\t\t\t*         3. Delete Room informations             *" << endl;
    cout << "\t\t\t\t\t\t*         4. Search Room informations             *" << endl;
    cout << "\t\t\t\t\t\t*         5. Main Menu                            *" << endl;
    cout << "\t\t\t\t\t\t*         6. Exit                                 *" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\tPlease enter your choose: "; cin >> option;
    cin.ignore();
    switch (option) {
    case 1: {
        system("cls");
        addrooms();
    }
          break;

    case 2: {
        system("cls");
        updaterooms();
    }
          break;

    case 3: {
        system("cls");
        deleterooms();
    }
          break;

    case 4: {
        system("cls");
        selectrooms();
    }
          break;
    case 5: {
        system("cls");
        menu();
    }
          break;

    case 6: {
        system("cls");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t***********************************************" << endl;
        cout << "\t\t\t\t\t\t*                                             *" << endl;
        cout << "\t\t\t\t\t\t*          You have exited the system!        *" << endl;
        cout << "\t\t\t\t\t\t*       Thank you for Choosing our Hotel!!    *" << endl;
        cout << "\t\t\t\t\t\t*                                             *" << endl;
        cout << "\t\t\t\t\t\t***********************************************" << endl;
        exit(0);
    }
          break;

    default: {
        system("cls");
        cout << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t   Sorry! The system do not have this function!" << endl;
        cout << "\t\t\t\t\t\tPress any key to continue!" << endl;
        (void)getchar();
        showInfoMenu();
    }
    }

}

int guest_info::showguestInfoMenu()
{
    system("cls");
  
    int option;
    cout << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t*         1. Guest Check In                       *" << endl;
    cout << "\t\t\t\t\t\t*         2. Guest Check Out                      *" << endl;
    cout << "\t\t\t\t\t\t*         3. Main Menu                            *" << endl;
    cout << "\t\t\t\t\t\t*         4. Exit                                 *" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\tPlease enter your choose: "; cin >> option;
    cin.ignore();
    switch (option) {
    case 1: {
        system("cls");
        addguest();
    }
          break;

    case 2: {
        system("cls");
        check_out();
    }
          break;

    case 3: {
        system("cls");
        menu();
    }
          break;

    case 4: {
        system("cls");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t***********************************************" << endl;
        cout << "\t\t\t\t\t\t*                                             *" << endl;
        cout << "\t\t\t\t\t\t*          You have exited the system!        *" << endl;
        cout << "\t\t\t\t\t\t*       Thank you for Choosing our Hotel!!    *" << endl;
        cout << "\t\t\t\t\t\t*                                             *" << endl;
        cout << "\t\t\t\t\t\t***********************************************" << endl;
        exit(0);
    }
          break;

    default: {
        system("cls");
        cout << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t   Sorry! The system do not have this function!" << endl;
        cout << "\t\t\t\t\t\tPress any key to continue!" << endl;
        (void)getchar();
        showguestInfoMenu();
    }
    }

}
void guest_info::report()
{
    system("cls");

    int option;
    cout << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t*         1. Vacant Rooms                         *" << endl;
    cout << "\t\t\t\t\t\t*         2. Occupied Rooms                       *" << endl;
    cout << "\t\t\t\t\t\t*         3. Room Allotment History               *" << endl;
    cout << "\t\t\t\t\t\t*         4. Main Menu                            *" << endl;
    cout << "\t\t\t\t\t\t*         5. Exit                                 *" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\tPlease enter your choose: "; cin >> option;
    cin.ignore();
    switch (option) {
    case 1: {
        system("cls");
         vacancy();
    }
          break;

    case 2: {
        system("cls");
        occupied();
    }
          break;
    case 3: {
        system("cls");
        history();
    }
          break;

    case 4: {
        system("cls");
        menu();
    }
          break;

    case 5: {
        system("cls");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t***********************************************" << endl;
        cout << "\t\t\t\t\t\t*                                             *" << endl;
        cout << "\t\t\t\t\t\t*          You have exited the system!        *" << endl;
        cout << "\t\t\t\t\t\t*       Thank you for Choosing our Hotel!!    *" << endl;
        cout << "\t\t\t\t\t\t*                                             *" << endl;
        cout << "\t\t\t\t\t\t***********************************************" << endl;
        exit(0);
    }
          break;

    default: {
        system("cls");
        cout << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t   Sorry! The system do not have this function!" << endl;
        cout << "\t\t\t\t\t\tPress any key to continue!" << endl;
        (void)getchar();
        showguestInfoMenu();
    }
    }


}
int guest_info::vacancy()
{
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            int t = 1;


            do
            {

                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*             SEARCHING VACANT ROOMS         *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl << endl;



                std::string sql = " select Room_Number,room_type,Floor_Number,Room_rent from hotel_rooms_info where occupied_status = 'No'";
                work W(C);
                cout << endl << endl;
                


                cout << "=====================================================================================" << endl;
                cout << "|S.No      |  ROOM_NUMBER  |       ROOM_TYPE      |     FLOOR_NUMBER |   ROOM_RENT  |" << endl;
                cout << "=====================================================================================" << endl;
                result R(W.exec(sql));
                for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                    cout << "|" << t << "\t   |\t" << c[0].as<int>() << "\t   |\t" <<setw(10) << c[1].as<string>() << "\t  |\t" << c[2].as<string>() << "\t     |" << " \t" << c[3].as<int>() << "\t    |" << endl;
                    t++;
                }
                cout << "-------------------------------------------------------------------------------------" << endl;

                W.commit();
                cout << "Do you want to you continue to Search again... press [y/n]";
                cin >> c1;
            } while (c1 == 'y');
        }
        else
        {
            cout << "Can't open database" << endl;

        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    report();

}
int guest_info::occupied()
{
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            int t = 1;


            do
            {

                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*                 OCCUPIED ROOMS             *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl << endl;


                std::string sql = "select a.room_number, b.first_name, a.room_type, a.floor_number, b.mobile_number,\
                     b.city, b.check_in_date, a.room_rent from hotel_rooms_info as a, guest_info as b\
                where a.occupied_status = 'Yes' and a.room_number = b.room_alloted_number";

                work W(C);
                cout << endl << endl;



                cout << "=============================================================================================================================================================================" << endl;
                cout << "|S.No      |  ROOM_NUMBER  |     NAME     |         ROOM_TYPE        | FLOOR_NUMBER|    MOBILE_NUMBER     |         CITY          |    Check_IN Date      |   ROOM_RENT     |" << endl;
                cout << "=============================================================================================================================================================================" << endl;
                result R(W.exec(sql));
                for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                    cout << "|" << t << "\t   |\t" << c[0].as<int>() << "\t   |\t" << c[1].as<string>() << "\t  |\t" << setw(10) << c[2].as<string>() << "\t     |" << " \t" << c[3].as<string>() << "\t   |\t" << c[4].as<double>() << "\t  |\t" << c[5].as<string>() << "\t   |\t" << c[6].as<string>() << "\t  |\t" << c[7].as<int>()<< "\t    |" << endl;
                    t++;
                }

                cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

                W.commit();
                cout << "Do you want to you continue to Search again... press [y/n]";
                cin >> c1;
            } while (c1 == 'y');
        }
        else
        {
            cout << "Can't open database" << endl;

        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    report();

}
int guest_info::history()
{

    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            int t = 1;
            do
            {

                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*             ROOM ALLOTMENT HISTORY         *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl << endl;
                int room_num;
                cout << "Enter The Room Number To Search the Room History: "; cin >> room_num;

                std::string sql = "select a.room_number,a.room_type,a.floor_number,b.first_name,b.mobile_number,b.city,b.check_in_date,b.check_out_date,a.room_rent\
                    from hotel_rooms_info as a, guest_info as b\
                where a.room_number =(" + std::to_string(room_num) +") and b.room_alloted_number = (" + std::to_string(room_num) + ")";

                work W(C);
                cout << endl << endl;



                cout << "======================================================================================================================================================================" << endl;
                cout << "|S.No      |  ROOM_NUMBER  |  ROOM_TYPE   |   FLOOR_NUMBER   |    NAME     |    MOBILE_NUMBER     |      CITY      | Check_IN Date|    Check_OUT Date    | ROOM_RENT |" << endl;
                cout << "======================================================================================================================================================================" << endl;
                result R(W.exec(sql));
                for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                    cout << "|" << t << "\t   |\t" << c[0].as<int>() << "\t   |\t" << c[1].as<string>() << "\t  |\t" << c[2].as<string>() << "\t     |" << " \t" << c[3].as<string>() << "\t   |\t" << c[4].as<double>() << "\t  |\t" << c[5].as<string>() << "\t   |   \t" << c[6].as<string>()  <<" | \t" << c[7].as<string>() << "\t | " << c[8].as<int>() << "\t     |" << endl;
                    t++;
                }
                cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

                W.commit();
                cout << "Do you want to you continue to Search again... press [y/n]";
                cin >> c1;
            } while (c1 == 'y');
        }
        else
        {
            cout << "Can't open database" << endl;

        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    report();

}


int main_screen()
    {
    
    system("Color DE");
    system("CLS");
    title();
    cout << endl << "\t\t\t\t\t\t\tPress any Key to continue!" << endl << endl;
    _getch();
    cout << "\t\t\t\t\t\tLoading";
    for (int process = 0; process < 36; process++) {
        delay(50);
        cout << ".";
    }
    loginScreen();


    
    return 0;
     }

    int main()
    {
      main_screen();
    return 0;
}

