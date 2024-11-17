#include <iostream>
#include <vector>
#include<cmath>
#include <algorithm>
using namespace std;

class  date //function to compare  two date
{   public:
    date(){} //default constructor
   
    int date_of_month;
    int month;
    int year;

    //consturctor
    date(int date, int month, int year ) : date_of_month(date) ,month(month), year(year) {}

    // Overload the '==' operator to compare two dates
   friend  bool operator==(const date & d, const date& c) ;
};
 bool operator==(const date & d, const date& c)  {
        return (d.date_of_month == c.date_of_month) && (c.month == d.month) && (c.year == d.year);
    }

class info :public date
{   public:
    string emp_id;
    string Name;
    string Address;
    double salary;
    date date_Of_Joining;
    date DOB;
    char level;
    string designation;

    //constructor
    info(string emp_id, string Name, string Address, double salary, date DOB,date doj, char level, string designation)
    {
       this->emp_id=emp_id;
       this->Name=Name;

       this->Address=Address;
       this->salary=salary;
       date_Of_Joining =doj;
       this->DOB=DOB;
       this->level=level;
       this->designation =designation;
    }
    info(){}
    void Employee_data() 
    {
        cout<<"enter employee id ";
        string emp_id;
        cin>>emp_id;
        this->emp_id=emp_id;
    }

    // Overload the '==' operator to compare two info structs
    bool operator==(const info& i) const {
        return (emp_id==emp_id)&&(Name == i.Name) && (salary == i.salary) && (level==i.level)
              && (date_Of_Joining == i.date_Of_Joining) && (DOB == i.DOB) && (designation == i.designation);
    }
};

class Emp_DBMS
{

public:
    vector<info> DB;    // Dynamic size, no need to specify an initial size
    // Method to insert an employee record
    int insert(const info& i1)
    {
        // Check if the employee already exists in the DB
        auto it = find(DB.begin(), DB.end(), i1);
        if (it != DB.end()) {
            // Employee already exists, do not insert
            cout << "Employee already exists!" << endl;
            return 0;  // Indicate failure
        }
         else {
            // Employee does not exist, insert into the vector
            DB.push_back(i1);
            
            // Sort the database by date of joining (DOJ) and DOB
            sort(DB.begin(), DB.end(), [](const info& a, const info& b) {
                // First compare by DOJ
                if (a.date_Of_Joining.year != b.date_Of_Joining.year)
                    return a.date_Of_Joining.year < b.date_Of_Joining.year;
                if (a.date_Of_Joining.month != b.date_Of_Joining.month)
                    return a.date_Of_Joining.month < b.date_Of_Joining.month;
                if (a.date_Of_Joining.date_of_month != b.date_Of_Joining.date_of_month)
                    return a.date_Of_Joining.date_of_month < b.date_Of_Joining.date_of_month;

                // If DOJ is same, compare by DOB
                if (a.DOB.year != b.DOB.year)
                    return a.DOB.year < b.DOB.year;
                if (a.DOB.month != b.DOB.month)
                    return a.DOB.month < b.DOB.month;
                return a.DOB.date_of_month < b.DOB.date_of_month;
            });

            cout << "Employee inserted successfully!" << endl;
            return 1;  // Indicate success
        }
    }

    // Display method that can either take a vector or display DB if no vector is passed
void display(const vector<info>& X = {}) const
{
    // If no vector is passed, display DB (the class member)
    if (X.empty()) {
        for (const auto& e : DB) {
            cout << "Employee ID: " << e.emp_id << "  Name: " << e.Name 
                 << ", Salary: " << e.salary << ", DOJ: " 
                 << e.date_Of_Joining.date_of_month << "/" << e.date_Of_Joining.month << "/" 
                 << e.date_Of_Joining.year << ", Level: " << e.level 
                 << ", DOB: " << e.DOB.date_of_month << "/" << e.DOB.month << "/" 
                 << e.DOB.year << ", Designation: " << e.designation << endl;
        }
    }
    // If a vector is passed, display that vector
    else {
        for (const auto& e : X) {
            cout << "Employee ID: " << e.emp_id << "  Name: " << e.Name 
                 << ", Salary: " << e.salary << ", DOJ: " 
                 << e.date_Of_Joining.date_of_month << "/" << e.date_Of_Joining.month << "/" 
                 << e.date_Of_Joining.year << ", Level: " << e.level 
                 << ", DOB: " << e.DOB.date_of_month << "/" << e.DOB.month << "/" 
                 << e.DOB.year << ", Designation: " << e.designation << endl;
        }
    }
}

void delete_rec(const string& emp_id, const string& emp_Name)// if we add Db as parameter it is giving error
 {
    // Search for the employee record in the DB
    auto it = find_if(DB.begin(), DB.end(), [&](const info& e) {
        return e.emp_id == emp_id && e.Name == emp_Name;
    });

    // Check if the employee is found
    if (it != DB.end()) {
        // Employee found, delete the record
        DB.erase(it);
        cout << "Employee with ID " << emp_id << " and Name " << emp_Name << " deleted successfully." << endl;
    } else {
        // Employee not found
        cout << "Employee with ID " << emp_id << " and Name " << emp_Name << " not found!" << endl;
    }
}

 //
    int update(vector<info>& DB)
    {   
        string  id;
        cout<<" enter your id to update "<<endl;
        cin>>id;
        auto it=find_if(DB.begin(), DB.end(), [&](const info& e)
        {
            return e.emp_id==id;
        }
        );
        if(it==DB.end())
        {
            cout<<"employee not found !"<<endl;
            return 0;
        }
        //now update the value
        cout<<"enter update name "<<endl;
        string n;
        cin>>n;
        it->Name=n;
        
        string add ;
        cout<<"enter updated address "<<endl;
        cin>>add;
        it->Address=add;

        char lev;
        cout<<"enter your updated level ,if not update ,then previous one  ";
            cin>>lev;
        it->level=lev;

        if(it->level=='B')
        {
            it->salary=it->salary + it->salary *0.20;
        }
        else if(it->level =='C')
        {
            it->salary=it->salary +it->salary *0.40;
        }

         sort(DB.begin(), DB.end(), [](const info& a, const info  b) {
                // First compare by DOJ
                if (a.date_Of_Joining.year != b.date_Of_Joining.year)
                    return a.date_Of_Joining.year < b.date_Of_Joining.year;
                if (a.date_Of_Joining.month != b.date_Of_Joining.month)
                    return a.date_Of_Joining.month < b.date_Of_Joining.month;
                if (a.date_Of_Joining.date_of_month != b.date_Of_Joining.date_of_month)
                    return a.date_Of_Joining.date_of_month < b.date_Of_Joining.date_of_month;

                // If DOJ is same, compare by DOB
                if (a.DOB.year != b.DOB.year)
                    return a.DOB.year < b.DOB.year;
                if (a.DOB.month != b.DOB.month)
                    return a.DOB.month < b.DOB.month;
                return a.DOB.date_of_month < b.DOB.date_of_month;
            });
         cout << "Employee inserted successfully!" << endl;
            return 1;  // Indicate success
        
    }
//use iterator
 void find_level(const string& emp_id, const string& emp_Name)
 {
    //seach the record in company database
    auto it= find_if(DB.begin(), DB.end(), [&](const info& e)
    {
        return e.emp_id==emp_id  && e.Name==emp_Name;
    });
    cout<<"level of employee "<<emp_Name<<" "<<it->level<<endl;
 }
vector<int>level_list;//give level of each 
    vector<int> getNumEmployees(vector<info>DB)
    {   int Acount=0,Bcount=0,Ccount=0;
        for( auto  & e:DB)
        {
            if(e.level=='A')
            {
                Acount++;
            }
           else if(e.level=='B')
            {
                Bcount++;
            }
           else  if(e.level=='C')
            {
                Ccount++;
            }
        }        
        level_list.push_back(Acount);
        level_list.push_back(Bcount);
        level_list.push_back(Ccount);
        return level_list;
    }
    bool isEmpty(auto DB)
    {
        if(!DB.size())
        return true;

        else return false;
    }
    bool isFull(auto DB)
    {
        int max_size=10;
        if(DB.size()==max_size)
        return true;

        else return false;
    }

    //uniqu in list,, removal of dumplicate
    vector<info>listunique(vector<info>& duplicate)
    {
        vector<info>unique_vector;
        for(const auto& x : duplicate)
        {
            auto it= find_if(unique_vector.begin(), unique_vector.end(),[&](const info& e)
            {
                return e.emp_id==x.emp_id && e.Name==x.Name;
            });

            if(it==unique_vector.end())//this means no t exist duplicate
            {
                unique_vector.push_back(x);
            }
            else 
            {
                if(x.level > it->level)
                {
                    *it=x;
                }
            }
        }
        return unique_vector;
    }

    //intersection of two list
    vector<info>unionList(vector<info> list1, vector<info>list2)
    {
        //we shoul merge two union list
        vector<info>ans;
        //step 1 add employe from list 1 to list 3
        for(auto& e: list1)
        {
         ans.push_back(e);
        }
        for(auto& e:list2)
        {
            ans.push_back(e);
        }
        //now sort the list
         sort(ans.begin(), ans.end(), [](const info& a, const info  b) {
                // First compare by DOJ
                if (a.date_Of_Joining.year != b.date_Of_Joining.year)
                    return a.date_Of_Joining.year < b.date_Of_Joining.year;
                if (a.date_Of_Joining.month != b.date_Of_Joining.month)
                    return a.date_Of_Joining.month < b.date_Of_Joining.month;
                if (a.date_Of_Joining.date_of_month != b.date_Of_Joining.date_of_month)
                    return a.date_Of_Joining.date_of_month < b.date_Of_Joining.date_of_month;

                // If DOJ is same, compare by DOB
                if (a.DOB.year != b.DOB.year)
                    return a.DOB.year < b.DOB.year;
                if (a.DOB.month != b.DOB.month)
                    return a.DOB.month < b.DOB.month;
                return a.DOB.date_of_month < b.DOB.date_of_month;
            });
        return ans;

    }

    vector<info>common_emp(vector<info>list1, vector<info>list2)
    {
        vector<info>list3;

    }
   

};


int main()
{
    Emp_DBMS COMPANY;
    
    info emp1 = {"E123","John","xyb", 50000.0, date{15, 5, 2020}, date{25, 12, 1990},'A', "Engineer"};
    info emp2 = {"M50","Alice","pqi", 60000.0, date{1, 1, 2021}, date{5, 7, 1992},'B', "Manager"};
    info emp3 = {"D12","Bob","abc", 55000.0, date{15, 5, 2020}, date{15, 8, 1991},'C', "Designer"};
    
    COMPANY.insert(emp1);
    COMPANY.insert(emp2);
    COMPANY.insert(emp3);

    // Displaying sorted records
    COMPANY.display(COMPANY.DB);

    vector<int>Emp_num;
    //Emp_num=db.getNumEmployees(db.DB); DB is inaccesible hence we make public
    Emp_num=COMPANY.getNumEmployees(COMPANY.DB); //for level
    for(auto x:Emp_num)
    {
        cout<<x<<" ";
    }
    info emp4;
    emp4.Employee_data();
    COMPANY.insert(emp4);

    COMPANY.display(COMPANY.DB);
    COMPANY.update(COMPANY.DB);
   //update the employee detail

vector<info> duplicate = {
    {"E123", "John", "Address1", 50000.0, date{15, 5, 2020}, date{25, 12, 1990}, 'A', "Engineer"},
    {"M50", "Alice", "Address2", 60000.0, date{1, 1, 2021}, date{5, 7, 1992}, 'B', "Manager"},
    {"E123", "John", "Address3", 55000.0, date{15, 5, 2021}, date{25, 12, 1990}, 'B', "Engineer"},
    {"M50", "Alice", "Address4", 65000.0, date{15, 3, 2022}, date{5, 7, 1992}, 'A', "Manager"}
};



   vector<info>list1, list2;
   info emp5= {"E123", "John", "Address1", 50000.0, date{15, 5, 2020}, date{25, 12, 1990}, 'A', "Engineer"};
    info emp6 {"M50", "Alice", "Address2", 60000.0, date{1, 1, 2021}, date{5, 7, 1992}, 'B', "Manager"};
    list1.push_back(emp5);
    list1.push_back(emp6);

    info emp7 = {"Mrt0","dhruv","address3",  120000.0, date{1, 1, 2021}, date{5, 7, 1992},'B', "Worker"};
    info emp8 = {"Dii12","Bob","address 4 ", 55000.0, date{15, 5, 2020}, date{15, 8, 1991},'C', "Designer"};

    cout<<"displaying employee after removal duplicate employee  "<<endl;
    vector<info>dup=COMPANY.listunique(duplicate);
    COMPANY.display(dup);
    

    list2={emp7,emp8};

    vector<info>union_list;
   union_list=COMPANY.unionList(list1, list2);

   //to print union list 
   cout<<"displaying union list "<<endl;
   COMPANY.display(union_list);
   COMPANY.delete_rec("M50", "Alice");


    
    
    return 0;
}