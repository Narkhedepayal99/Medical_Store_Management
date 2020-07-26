//============================================================================
// Name        : final.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class medicine
{
    char med[30];
    int id;
    float price;
public:

    int stock;
    void accept();
    void display();

    char* getMedname(){return med;}

    int getMedid(){return id;}
};

void medicine :: accept()
{
    cout << "\nEnter Medicine Name:";
    cin >> med;
    cout << "Enter Medicine Id:";
    cin >> id;
    cout << "Enter Stock Present:";
    cin >> stock;
    cout << " Enter price:";
    cin >> price;
}

void medicine :: display()
{
    cout << "\n\nMedicine Name:" << med;
    cout << "\nMedicine id:" << id;
    cout << "\nQuantity:" << stock;
    cout << "\nPrice:" << price;
}


void createFile(){
    int n;
    ofstream out;
    medicine m;
    out.open("Pharmacy");
    cout << "\nHow many Medicines are you going to Enter ? ";
    cin >> n;

    for(int i=0;i<n;i++)
    {
         m.accept();
         out.write((char *) &m,sizeof(m));
    }
    out.close();
}

void displayFile()
{
    ifstream in;
	medicine m;
	in.open("Pharmacy");
	while(in)
	{
		in.read((char*) &m,sizeof(m));
		if(in.eof()!=0)
			break;
		m.display();
	}
	in.close();
}

void addMedicine()
{
    medicine m;
	ofstream out;
	out.open("Pharmacy",ios::app);
	m.accept();
    cout << "\nAdding Medicine....";
	out.write((char*) &m,sizeof(m));
	out.close();
	char y;
	cout << "\nDo you want to Display the Stock ? ";
	cin  >> y;
	if(y == 'y' || y == 'Y')
        displayFile();
    cout << "\nDo you want to add More Medicines ? ";
    cin >> y;
    if(y == 'y' || y == 'Y')
        addMedicine();
}

void findMed()
{
    medicine m;
	ifstream in;
	int flag=0,ch,id;
	char name[20];
	char y;

	cout << "\nSearch for a Medicine";
	cout << "\n1.Name";
	cout << "\n2.Id";
	cout<<"\nEnter your choice:";
	cin>>ch;
	switch (ch)
	{
	case 1:
		{
			cout << "\nEnter Name of Medicine to be searched:";
			cin >> name;
			in.open("Pharmacy");
			while(in)
			{
				in.read((char*) &m,sizeof(m));
				if(in.eof()!=0)
					break;
				if(strcmp(name,m.getMedname())==0)
				{
					flag=1;
					cout<<"\n***Medicine is Available***";
					m.display();
					break;
				}
			}
			if(flag==0)
				cout<<"\n***Medicine not Available***";
			in.close();
			break;
		}
	case 2:
		{
			cout << "\nEnter Medicine id to be searched:";
			cin >> id;
			in.open("Pharmacy");
			while(in)
			{
				in.read((char*) &m,sizeof(m));
				if(in.eof()!=0)
					break;
				if(id == m.getMedid())
				{
					flag=1;
					cout<<"\n***Medicine is Available***";
					m.display();
					break;
				}
			}
			if(flag==0)
				cout<<"\n***Medicine is not Available***";
			in.close();
			break;
		}
	default:
		cout<<"\nPlease enter a correct choice";
		break;
	}

	cout << "\nDo you want to Find any other medicines ? ";
	cin >> y;

	if(y == 'y' || y == 'Y')
        findMed();
}




void updateStock()
{
	int flag = 0,pos;
	fstream file;
	file.open("Pharmacy",ios::in|ios::out);
	medicine m;
	char name[20];
	cout << "\nEnter Name of Medicine whose Stock is to be Updated:";
	cin >> name;

	while(file)
	{
		file.read((char*) &m,sizeof(m));
		if(file.eof()!=0)
			break;
		if(strcmp(name,m.getMedname())==0)
		{
			flag=1;
			cout<<"\n***Medicine Found***\nDetails are:";
			m.display();

			cout<<"\nEnter updated details:";
			m.accept();
			pos = -1*sizeof(m);
			file.seekp(pos,ios::cur);
			file.write((char*)&m,sizeof(m));
			break;
		}
    }
    if(flag==0)
    cout<<"\n***Medicine not Available***";
	file.close();

    char ch;
	cout << "\nDo you want to Update any other Stocks ? ";
	cin >> ch;
	if(ch == 'y' || ch == 'Y')
        updateStock();
}

void buyMedicine(){
        char name[30],y;
        medicine m;
        fstream file;
        int i,flag = 0;


        cout << "\nEnter Name of Medicine you want to Buy:";
			cin >> name;
			file.open("Pharmacy");
			while(file)
			{
				file.read((char*) &m,sizeof(m));
				if(file.eof()!=0)
					break;
				if(strcmp(name,m.getMedname())==0)
				{
					flag=1;
					cout<<"\n***Medicine is Available***";
					cout << "\nHow many Quantity Sold?";
					cin >> i;
					m.stock = m.stock - i;
					m.display();
					int pos=-1*sizeof(m);
					file.seekp(pos,ios::cur);
					file.write((char*)&m,sizeof(m));
					break;
				}
			}
			if(flag==0)
				cout<<"\n***Medicine not Available***";
			file.close();

        cout << "\nDo you want to Buy More medicines? ";
        cin >> y;

        if(y == 'y'|| y == 'Y')
            buyMedicine();
}


int main()
{
        int ch;
        do{
        cout << "\nWhat Operation do you want to perform?";
        cout << "\n1.Create A File";
        cout << "\n2.Display File";
        cout << "\n3.Add a Medicine";
        cout << "\n4.Check Availability of a Medicine";
        cout << "\n5.Update Stock";
        cout << "\n6.Buy Medicine";
        cout << "\n7.Exit";
        cout << "\nEnter your Choice:";
        cin >> ch;

        switch(ch){

    case 1:
        cout << "\n********************";
        cout << "\nCreating File....";
        createFile();
        cout << "\nFile created....";
        cout << "\n********************";
        break;

    case 2:
        cout << "\n********************";
        cout << "\nDisplaying File....";
        displayFile();
        cout << "\n********************";
        break;

    case 3:
        cout << "\n********************";
        addMedicine();
        cout << "\n********************";
        break;

    case 4:
        cout << "\n********************";
        findMed();
        cout << "\n********************";
        break;

    case 5:
        cout << "\n********************";
        updateStock();
        cout << "\nStock updated....";
        cout << "\n********************";
        break;

    case 6:
        cout << "\n********************";
        buyMedicine();
        cout << "\n********************";
        break;

    case 7:
        break;

    default:
        cout << "\nPlease Enter a Appropriate Choice!!!";

    }
        }while(ch != 7);
}
