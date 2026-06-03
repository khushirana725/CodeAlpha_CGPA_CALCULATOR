#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

//Class created to validate user-entered input values using template function

class InputValidator {
public:
    template <typename T>
    static T getValidInput(const string& prompt, T minVal = 0, T maxVal = 10000) {
        T val;
        while (true) {
            cout << prompt;
            cin >> val;
            
            if (cin.fail() || val < minVal || val > maxVal) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "INVALID INPUT! Please enter a value between " << minVal << " and " << maxVal << ".\n";
            } else {
                cin.ignore(1000, '\n'); // Clear trailing newline to prevent getline skips!
                return val;
            }
        }
    }
};

//A class is created for subject data

class Subject{
    private:
      string subName;
      string subGrade;
      float credit;
      float gradePoint;
      void assignGrade();
    public:
      void input();
      void display() const;
      float getGradePoint() const{return gradePoint;};
      float getCredit() const{return credit;};
      float getCreditPoint() const{return credit*gradePoint;};
      string getSubName()const {return subName;};
      string getSubGrade()const {return subGrade;};
};

// A data member function named INPUT is created to get input from user

void Subject::input(){
    cout<<"Enter Subject Name: ";
    getline(cin,subName);

// taking input for credit annd validating it...

    credit=InputValidator::getValidInput<float>("Enter Credit(Minimum 0.5): ",0.5f,10.0f);

// taking input for grade point and validating it...

    gradePoint = InputValidator::getValidInput<float>("Enter Grade Point (0 - 10): ", 0.0f, 10.0f);

//automatically assigning grade using grade point criteria ^_^

    assignGrade();
    cout<<"Grade Assigned: "<<subGrade<<endl;

}


// A data member function assignGrade is created 
//so that user will not have to enter the grades manually 
//but the algo will identify on the basis of grade points

void Subject::assignGrade(){
    if (gradePoint>=9)       subGrade="O";
    else if(gradePoint>=8)   subGrade="A+";
    else if(gradePoint>=7)   subGrade="A";
    else if(gradePoint>=6)   subGrade="B+";
    else if(gradePoint>=5)   subGrade="B";
    else if(gradePoint>=4)   subGrade="C";
    else                     subGrade="F";
}

void Subject::display() const{
    cout<<left
        <<setw(35)<<subName
        <<setw(12)<<subGrade
        <<setw(12)<<credit
        <<setw(15)<<gradePoint
        <<setw(15)<<getCreditPoint()
        <<endl;
} 


int main(){
    string studentName;
    cout<<"ENTER STUDENT NAME: ";
    getline(cin,studentName);

    cout<<fixed<<setprecision(2);
    
    int sem=1,totalSem;
    float totalPoint=0,totalCredit=0,cgpa;

//taking input for total semesters  completed till now and validating the value...

    totalSem=InputValidator::getValidInput<int>("SEMESTER COMPLETED TILL NOW: ",1,10);    

    ofstream fout("record.txt",ios::app);
    if(!fout){
        cout<<"FILE ERROR...!!!";
        return 1;
    }
    fout<<"STUDENT NAME: "<<studentName<<endl;
    fout<<fixed<<setprecision(2);
//While loop will calculate the cgpa 

    while(sem<=totalSem){
        cout<<"\n========== SEMESTER "<<sem<<" ==========\n";
        int n;

//taking value for number of subjects in semester and validating the value...

        n=InputValidator::getValidInput<int>("ENTER NUMBER OF SUBJECTS: ",1,20);

        float gpa,semPoint=0,semCredit=0;
        
        vector<Subject> s(n);

//loop to get input from the user

        for(int i=0;i<n;i++){
            cout<<"ENTER THE DETAILS FOR SUBJECT "<<i+1<<endl;
            s[i].input();}
        
        cout<<"\n--------------------------------------------------------------\n";
        cout<<left
            <<setw(35)<<"SUBJECT"
            <<setw(12)<<"GRADE"
            <<setw(12)<<"CREDIT"
            <<setw(15)<<"GRADE POINT"
            <<setw(15)<<"CREDIT POINT"
            <<endl;
        cout<<"--------------------------------------------------------------\n";

//loop to calculate the details of subjects entered by user and calculate the totalSemesterPoints and Credits

        for(int i=0;i<n;i++){
            s[i].display();
            semPoint+=s[i].getCreditPoint();
            semCredit+=s[i].getCredit();
            cout<<endl;
        }
        fout << "\nSEMESTER " << sem << endl;
        fout << left
             << setw(35) << "SUBJECT"
             << setw(12) << "GRADE"
             << setw(12) << "CREDIT"
             << setw(15) << "GRADE POINT"
             << setw(15) << "CREDIT POINT"
             << endl;

        fout << "---------------------------------------------------------------------\n";

        for(int i=0;i<n;i++){
            fout << left
                 << setw(35) << s[i].getSubName()
                 << setw(12) << s[i].getSubGrade()
                 << setw(12) << s[i].getCredit()
                 << setw(15) << s[i].getGradePoint()
                 << setw(15) << s[i].getCreditPoint()
                 << endl;
        }
//here the condition will check for any exception created via semesterCredit  
        
        gpa = (semCredit != 0) ? (semPoint / semCredit) : 0.0f;
        
        cout<<"\n-------------------------------------------------"<<endl;
        cout<<"SEMESTER "<<sem<<" SGPA: "<<gpa<<endl;
        cout<<"\n-------------------------------------------------"<<endl;

        totalPoint+=semPoint;
        totalCredit+=semCredit;
        
        fout<<"\nSGPA: "<<gpa<<endl;

        sem++;
    }
//calculating cgpa and checking for any exception created via TotalCredit
    
    cgpa = (totalCredit != 0) ? (totalPoint / totalCredit) : 0.0f;
   
    fout<<"CGPA: "<<cgpa<<endl;
    fout.close();

    cout<<"\nSTUDENT NAME: "<<studentName<<endl;
    cout<<"\n-------------------------------------------------"<<endl;
    cout<<"CGPA: "<<cgpa;
    cout<<"\n-------------------------------------------------"<<endl;
    return 0;
}
