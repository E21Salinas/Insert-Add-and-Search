#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct info {
	string Name;
	long SSN;
	int Age;
	string Address;
};

void printInfo(info Info) {
	cout << "Name: " << Info.Name << '\n';
	cout << "SSN: " << Info.SSN << '\n';
	cout << "Age: " << Info.Age << '\n';
	cout << "Address: " << Info.Address << endl << endl;
}

void printArray(info Info[], int value){
	for (int j = 0; j <= value; j++) {
		cout << '\n';
		printInfo(Info[j]);

		if (Info[j+1].Name == "") {
			break;
		}
	}
}

void sortArray(info Info[], int i) {
	for (int x = 0; x < i-1; x++) {
		for (int y = 0; y < i-1; y++) {
			if (Info[y + 1].Name < Info[y].Name)
			{
				info TEMP;
				TEMP = Info[y];
				Info[y] = Info[y + 1];
				Info[y + 1] = TEMP;
			}
		}
	}
}

int findStruct(info Found[], info Info[], int i) {
	string answer;
	char cont;
	int y = 0;

	while (true) {

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
				getline(last, substr, ',');

					if (answer == substr)
					{
						printInfo(Info[x]);
						Found[y] = Info[x];
						y++;
					}
			}
			
			
		}
		else if ((cont == 'N') || (cont == 'n')) {
			cout << "Thanks for Searching with Us!" << endl;
			break;
		}
	}
	return (y);
}

int addInfo(info Info[], int value) {
	while (true) {
		char answer;
		info temp;
		cout << "Would you like to add in a Person? (Y/N): ";
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

			Info[value] = temp;

			value++;
		}
		
		if ((answer == 'N') || (answer =='n')){
			cout << "Thanks for your time!" << endl;
			break;
		}
		answer = NULL;
	}
	
	return (value);
}

int main() {
	info Info[25];
	info Found[25];
	ifstream myfile("a1.txt");
	string line;
	long temp;
	int val;
	
	int i = 0;
	

	if (myfile.is_open()){
		while (true) {
			if (myfile.eof()){
				break;
			}
			getline(myfile, line);
			Info[i].Name = line;

			getline(myfile, line);
			temp = atol(line.c_str());
			Info[i].SSN = temp;

			getline(myfile, line);
			stringstream nline(line);
			nline >> val;
			Info[i].Age = val;

			getline(myfile, line);
			Info[i].Address = line;
			i++;

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

	int j;
	j = findStruct(Found, Info, i);

	cout << '\n';
	cout << "List of found Individuals" << endl;
	printArray(Found, j);
	

	return (0);
}