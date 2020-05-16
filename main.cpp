#include <iostream>
#include<windows.h>
#include<mysql.h>
#include <sstream>
#include<stdio.h>

using namespace std;
#define standarddeduction 50000;
int i=0;
struct payee
{
	float empid;
	int taxid;
	int age;
	int basic;
	int hra;
	int sa;
	int lta;
	int hradedu;
	int ltadedu;
	int gti;
	int pfi;
	int mi;
	int savings;
	int total;
	int incomeother;
	int ggti;

}pay;

class tax
{
	public:  int entry();
			 int admin(payee pay);
			 void client(payee pay);
			 int calculate(payee pay);
			 int display(payee pay);
			 void update();
			 void allow();
			 void total();
};

int tax :: entry()
{
	int entry;
		cout<<"*&*&*&*&*&*&*&*&**&*&*&*&*&*&*&*&*&*&**&*&*&*&*&*&*&*&*&*&*&*&**&*&*&**&*&*&*&*&*&*&*&"<<endl;
		cout<<"WELCOME TO TAX CALCULATOR"<<endl;
		cout<<"press 1 to continue if ur admin"<<endl;
		cout<<"press 2 to continue to submit ur income tax reports"<<endl;
		cout<<"press 3 to exit"<<endl;
		cout<<"*&*&*&*&*&*&*&*&**&*&*&*&*&*&*&*&*&*&**&*&*&*&*&*&*&*&*&*&*&*&**&*&*&**&*&*&*&*&*&*&*&"<<endl<<endl;
		cout<<"Enter the CHOICE: ";
		cin>>entry;
    	switch(entry)
    	{
    		case 1: admin(pay);
    				break;
    		case 2: client(pay);
    				break;
    		case 3: exit(0);
    				break;
    		default: cout<< "please enter the correct choice";
    				break;
		}
}

void tax :: client(payee pay)
{
	string dummy;
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "rohan", "rohan", "oopsproject", 0, NULL, 0);
    if(conn){
	cout<<"welcome client"<<endl;
	cout<<"enter the empid"<<endl;
	cin>>pay.empid;
	cout<<"enter the taxid"<<endl;;
	cin>>pay.taxid;
	cout<<"enter the age"<<endl;
	cin>>pay.age;
	cout<<"enter the basic salary"<<endl;
	cin>>pay.basic;
	cout<<"enter the HOUSE RENT ALLOWANCE"<<endl;
	cin>>pay.hra;
	cout<<"enter the special allowance"<<endl;
	cin>>pay.sa;
	cout<<"enter the leave travel allowance"<<endl;
	cin>>pay.lta;
	cout<<"enter the hra deduction"<<endl;
	cin>>pay.hradedu;
	cout<<"enter the leave travel allowance deduction"<<endl;
	cin>>pay.ltadedu;
	cout<<"enter the provident fund total (ARTICLE 80C)"<<endl;
	cin>>pay.pfi;
	cout<<"enter the medical allowance (ARTICLE 80D)"<<endl;
	cin>>pay.mi;
	cout<<"enter the savings (ARTICLE 80TTA)"<<endl;
	cin>>pay.savings;
	cout<<"enter the income from other source"<<endl;
	cin>>pay.incomeother;

	pay.gti=pay.basic+(pay.hra-pay.hradedu)+pay.sa+(pay.lta-pay.ltadedu)-standarddeduction;
	int totaldedu=pay.pfi+pay.savings+pay.mi;
	pay.ggti=pay.gti+pay.incomeother-totaldedu;

	if(pay.ggti<=250000)
	{
		pay.total=0;
	}
	else if(pay.ggti>250000 && pay.ggti<=500000)
	{
		pay.total=pay.ggti*0.05;
	}
	else if(pay.ggti>500000 && pay.ggti<=1000000)
	{
		pay.total=pay.ggti*0.2;
	}
	else
		pay.total=pay.ggti*0.3;
		int qstate=0;
        stringstream ss;
        ss << "INSERT INTO `client` (`Id`, `Taxid`, `Age`, `basicsalary`, `hra`, `specialalowance`, `lta`, `hradedu`, `ltadedu`, `providfund`, `medicalallow`, `savings`, `otherincome`, `totalincometax`) VALUES ('" << pay.empid << "', '" << pay.taxid << "', '" <<pay.age<< "', '" <<pay.basic<< "', '" << pay.hra << "', '" <<pay.sa<< "', '" <<pay.lta<< "', '" <<pay.hradedu<< "', '" <<pay.ltadedu<< "', '" << pay.pfi<< "', '" << pay.mi<< "', '" << pay.savings<< "', '" << pay.incomeother << "', '" << pay.ggti<< "')";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Inserted..." << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        cin >> dummy;
    }

    system("pause");
    system("cls");
 loop: entry();
 goto loop;
}

int tax :: display(payee pay)
{
	MYSQL* conn;
     	string dummy;
   	MYSQL_ROW row;
   	MYSQL_RES* res;
   	conn = mysql_init(0);
   	conn = mysql_real_connect(conn,"localhost","rohan","rohan","oopsproject",0,NULL,0);
   	if(conn){
        int qstate = mysql_query(conn, "SELECT Id, Taxid, Age, basicsalary, hra, specialalowance, lta, hradedu, ltadedu, providfund, medicalallow, savings, otherincome, totalincometax FROM client");
	cout<<" ID "<<"\t | \t"<<"TaxId"<<"\t | \t"<<"Age"<<"\t | \t" <<"Basicsalary"<<"\t | \t" <<"HRA"<<"\t | \t" <<"SPECIALALLOWAN"<<"\t | \t" <<"LTA"<<"\t | \t"<<"HRA dedu"<<"\t | \t"<<"LTA dedu"<<"\t | \t"<<"Providentfunding"<<"\t | \t"<<"MedAllowance"<<"\t | \t"<<"Savings"<<"\t | \t"<<"OtherIncome"<<"\t | \t"<<"IncomeTaxpayable"<<"\t | \t"<<endl<<endl;
        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
                cout << row[0] <<"\t | \t" << row[1] <<"\t | \t" << row[2] <<"\t | \t" << row[3] <<"\t | \t"<< row[4] <<"\t | \t" << row[5] <<"\t | \t"<< row[6] <<"\t | \t"<< row[7] <<"\t | \t"<< row[8] <<"\t | \t"<< row[9] <<"\t | \t" << row[10] <<"\t | \t"<< row[11] <<"\t | \t"<< row[12] <<"\t | \t"<< row[13] <<"\t | \t"<<endl << endl<<endl<<endl;
             }
        }
    }
 cout << "Press B to go back";
    cin >> dummy;
    loop1: admin(pay);
    goto loop1;

    system("pause");
    system("cls");
}

int tax :: admin(payee pay)
{
	int ch;
    cout<<endl<<endl;
    cout<<"*&*&*&*&*&*&*&*&**&*&*&*&*&*&*&*&*&*&**&*&*&*&*&*&*&*&*&*&*&*&**&*&*&**&*&*&*&*&*&*&*&"<<endl;
	cout<< "welcome to admin"<<endl;
	cout<<" press 1 to display all submitted forms"<<endl;
	cout<<" press 2 to exit"<<endl;
	cout<<" press 3 to update particular record of other income"<<endl;
	cout<<" press 4 to view the selected client allowance (extra) details of income tax"<<endl;
	cout<<" press 5 to see total amount of tax needed to be collected from clients "<<endl;
	cout<<"*&*&*&*&*&*&*&*&**&*&*&*&*&*&*&*&*&*&**&*&*&*&*&*&*&*&*&*&*&*&**&*&*&**&*&*&*&*&*&*&*&"<<endl;
	cout<<" Enter the Choice: ";
	cin>>ch;
	cout<<endl<<endl;
	switch(ch)
        {
			case 1:display(pay);
						break;
			case 2:exit(0);
						break;
			case 3:update();
						break;
			case 4:allow();
						break;
			case 5:total();
						break;
			default : cout<<"enter correct choice";
						break;
        }

}


void tax :: update()
{
    string dummy;
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "rohan", "rohan", "oopsproject", 0, NULL, 0);

    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn, "localhost", "rohan", "rohan", "oopsproject", 0, NULL, 0);;

    if(conn){

        int id;;
        int other;
        cout << "Enter ID : ";
        cin >> id;
        cout << "Enter Other income : ";
        cin >> other;


        int qstate1 = 0;

        stringstream ss1;
        ss1 << "UPDATE client SET otherincome=" << other << " WHERE Id = '" << id << "'";

        string query1 = ss1.str();

        const char* q1 = query1.c_str();
        qstate1 = mysql_query(conn2, q1);
        if(qstate1 == 0){
            cout << "Record Updated..." << endl;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
        }

    }

    cout << "Press B to go back";
    cin >> dummy;
    loop2: admin(pay);
    goto loop2;
    system("pause");
    system("cls");
}

void tax :: allow()
{
 MYSQL* conn;
     	string dummy;
   	MYSQL_ROW row;
   	MYSQL_RES* res;
   	conn = mysql_init(0);
   	conn = mysql_real_connect(conn,"localhost","rohan","rohan","oopsproject",0,NULL,0);
		if(conn){
        int qstate = mysql_query(conn, "SELECT  Id,hra,hradedu,lta,ltadedu  FROM client ");
        cout<<" ID \t | \t HRA \t | \t HRADEDU \t | \t LTA \t | \t LTADEDU \t | \t"<<endl;
        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
                cout << row[0] <<"\t | \t"<<row[1] <<"\t | \t"<<row[2] <<"\t\t | \t"<<row[3] <<"\t | \t"<<row[4] <<"\t | \t"<<endl << endl;
             }
        }
    }
 cout << "Press B to go back";
    cin >> dummy;
    loop3: admin(pay);
    goto loop3;
    system("pause");
    system("cls");
}

void tax :: total()
{
    string dummy;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "rohan", "rohan", "oopsproject", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT sum(totalincometax) FROM client");
        cout<<"Total Amount Need to be collected:";
        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
                cout << row[0] << endl << endl;
             }
        }
    }

    cout << "Press B to go back";
    cin >> dummy;
    loop4: admin(pay);
    goto loop4;
    system("pause");
    system("cls");

}

int main()
{
	tax t;
	payee pay;
	t.entry();
	return 0;
}
