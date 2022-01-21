#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

//To store information from formatted txt file
struct info {
	string Name;
	long SSN;
	int Age;
	string Address;
};

//prints a singular info struct
void printInfo(info Info) {
	cout << "Name: " << Info.Name << '\n';
	cout << "SSN: " << Info.SSN << '\n';
	cout << "Age: " << Info.Age << '\n';
	cout << "Address: " << Info.Address << endl << endl;
}

//prints an array of info structs
void printArray(info Info[], int value){
	for (int j = 0; j <= value; j++) {
		cout << '\n';
		printInfo(Info[j]);

		if (Info[j+1].Name == "") {
			break;
		}
	}
}

//sorts the array in ascending fasion with bubble sort
void sortArray(info Info[], int i) {
	info TEMP;
	for (int x = 0; x < i-1; x++) {
		for (int y = 0; y < i-1; y++) {
			if (Info[y + 1].Name < Info[y].Name) //compares strings
			{
				TEMP = Info[y];
				Info[y] = Info[y + 1];
				Info[y + 1] = TEMP;
			}
		}
	}
}

//finding a specific info struct by last name
int findStruct(info Found[], info Info[], int i) {
	string answer;
	char cont;
	int y = 0;

	while (true) {
		//asks user if they would like to look for someone
		cout << "Would you like to find Person? (Y/N): ";
		cin >> cont;
		cout << endl;

		if ((cont == 'Y') || (cont == 'y')) {
			cout << "Who would you like to find?: ";
			cin >> answer;
			cout << endl;

			for (int x = 0; x < i; x++) {
				stringstream last(Info[x].Name);
				string substr;
				getline(last, substr, ','); //parses last till it finds a ',' and saves the first portion into substr

					if (answer == substr)
					{
						printInfo(Info[x]);
						Found[y] = Info[x]; //search history
						y++;
					}
			}
			
			
		}
		else if ((cont == 'N') || (cont == 'n')) {
			cout << "Thanks for Searching with Us!" << endl;
			break;
		}
	}
	return (y); //returns value that represents how many structs are in the array
}

//function to add info
int addInfo(info Info[], int value) {
	while (true) {
		char answer;
		info temp;
		cout << "Would you like to add in a Person? (Y/N): "; //asks user if they would like to add anyone
		cin >> answer;
		cout << endl;

		if ((answer == 'Y') || (answer == 'y')){
			cout << "Input Name in format -> Last,First: ";
			cin >> temp.Name;

			cout << "Input your 9 digit SSN: ";
			cin >> temp.SSN;

			cout << "Input your Age: ";
			cin >> temp.Age;

			cout << "Input your Address: ";
			cin.ignore();
			getline(cin, temp.Address);

			Info[value] = temp; //adds info to array (last in)

			value++;//increments count so that information isn't overwritten in the same info struct
		}
		
		if ((answer == 'N') || (answer =='n')){
			cout << "Thanks for your time!" << endl;
			break;
		}
		answer = NULL;
	}
	
	return (value);//returns int of new amount in the array
}

int main() {
	//initializing
	info Info[25];
	info Found[25];
	ifstream myfile("a1.txt");
	string line;
	long temp;
	int val;
	
	int i = 0;
	int j;
	

	if (myfile.is_open()){
		while (true) {
			if (myfile.eof()){ //reads till end of file
				break;
			}
			//reads in the name
			getline(myfile, line); 
			Info[i].Name = line;

			//reads in SSN but has to convert string to long
			getline(myfile, line); 
			temp = atol(line.c_str());
			Info[i].SSN = temp;

			//reads in age and converts string to int
			getline(myfile, line);
			stringstream nline(line);
			nline >> val;
			Info[i].Age = val;

			//reads in Address
			getline(myfile, line);
			Info[i].Address = line;
			i++;

			//This is used so that the line of empty space isn't picked up in a struct
			getline(myfile, line);
		}
	}
	else {
		cout << "No file found.";
	}

	myfile.close();


	i = addInfo(Info, i);

	sortArray(Info, i);
	
	printArray(Info, i);

	
	j = findStruct(Found, Info, i);

	//Only activates if a search occured
	if (j > 0) {
		cout << '\n';
		cout << "List of found Individuals" << endl;
		printArray(Found, j);
	}
	

	return (0);
}