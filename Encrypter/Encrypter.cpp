// Encrypter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

//global variables
bool run = true;
string fullPath = "";
int dataSize = 2;
char* dataBuffer;


//global functions
void printData()
	{
		cout << "Current File Path: " << endl;
		cout <<	fullPath << endl;
		cout << "Current Data PREVIEW: " << endl;

		//Display a PREVIEW of Data
		string displayText = "";
		int loop = dataSize;
		if (dataSize > 1500)
		{
			loop = 1500;
		}
		else
		{
			loop = dataSize;
		}
		for (unsigned x = 0; x < loop; x++)
		{
			displayText += dataBuffer[x];
		}
		cout << displayText << endl;


		//add lots of space between data and next key
		cout << endl << endl << "------------------END------------------" << endl << endl << endl;
	}

void typeWriter(string x)
{
	string fullText;
	string subText;
	bool fin = true;

	cout << "Write whatever data in ASCII code to be submitted." << endl;
	cout << "Hitting the return key (enter) will submit a new line." << endl;
	cout << "Once a new line has been submitted, you may not edit it. Proofread carefully." << endl;
	cout << "To start over and clear the slate. Submit a new line. Type '/clear' and submit it." << endl;
	cout << "TWhen you are finished typing. Submit a new line. Type '/finish' and submit it." << endl;
	cout << "------------------------------ Begin Typing ------------------------------" << endl << endl;
	
	
	//command line
	if (x == "edit")
	{
		cout << fullText << endl;
	}
	else if (x == "clear")
	{
		fullText = "";
	}


	//loop and write data
	while (fin)
	{
		getline(cin, subText);

		//if != finish write to subtext
		if (subText == "/finish")
		{
			fin = false;
			break;
			cout << "------------------------------ Data Submitted ------------------------------";
		}
		else if (subText == "/clear")
		{
			system("CLS");
			fullText = "";
		}
		else
		{
			//cout << subText << endl;
			fullText = fullText + subText + "\n";
		}
	}


	//creates new char array the size of the fullText
	dataSize = ((fullText.size() + 1));
	dataBuffer = new char[dataSize]();
	fullText.copy(dataBuffer, dataSize);

	system("PAUSE");
}




class IO
{
public:
	void setFullPath()
	{
		string filePath = "FILES/";
		string fileName;

		cout << "What is the name of the file you are encrypting?" << endl;
		cin >> fileName;

		fullPath = filePath + fileName;
	}

	void openFileBinary(string path)
	{
		//creqates the stream obj
		ifstream openObj;

		//opens the streaming file
		try {
			openObj.open(path, ios::in|ios::binary);
		}
		catch (...)
		{
			cout << "There was an error opening this file." << endl;
		}

		//gets size of file
		//creates an array on the heap and allocates memory to read to
		openObj.seekg(0, openObj.end);
		dataSize = (int)openObj.tellg();
		openObj.seekg(0, openObj.beg);

		//creates a pointer to a char dynamically allocated on the heap
		//initializes an array of 'xsize'
		dataBuffer = new char[dataSize]();
		//reads file to the BUFFER in the amount of XSIZE
		openObj.read(reinterpret_cast<char*>(dataBuffer), dataSize);
		//converts the char* to a string literal



		//ERROR CHECKING
		if (openObj)
		{
			cout << "Size of file: " << dataSize << " bytes" << endl;
			std::cout << "All " << openObj.gcount() << " bytes read successfully." << endl;
		}
		else
		{
			std::cout << "Error: only " << openObj.gcount() << " bytes could be read";
		}

		//close the stream
		openObj.close();

		cout << "Read from File complete." << endl << endl;
		//printData();
		system("PAUSE");
	}

	void closeFileBinary(string path)
	{
		//creates the stream obj
		ofstream closeObj;

		try {
			//opens the file
			closeObj.open(path, ios::out|ios::binary);
		}
		catch (...)
		{
			cout << "There was an error opening this file." << endl;
		}

		
		//write the data to file
		closeObj.write(reinterpret_cast<char*>(dataBuffer), dataSize);

		//ERROR CHECKING
		if (closeObj)
		{
			std::cout << "All " << "" << " characters written successfully.";
		}
		else
		{
			std::cout << "Error: only " << "some of the bits" << " could be written";
		}

		//close the stream
		closeObj.close();

		cout << "Print to File complete." << endl << endl;
		printData();
		system("PAUSE");
	}
};

class Cipher
{
private:
	string key;


public:
	void askForKey()
	{
		cout << "What key would you like to use for Encryption/Decryption?" << endl;
		cin >> key;
		cout << endl << endl;
	}

	void encrypt()
	{
		unsigned int revolver = 0;

		system("CLS");
		cout << "Please wait while your data is being encrypted.";

		for (unsigned int x = 0; x <= dataSize; x++)
		{
			//creates temporary character holder and sets the tchar integer to the int casted from the x position in the for loop
			int tCharData = (int)dataBuffer[x];
			//gets the int code of the first character in the key
			int tCharKey = (int)key[revolver];



			//algorithum for encryption
			tCharData += tCharKey;


			//executes adjusting the data to the new encryption
			dataBuffer[x] = (char)tCharData;


			if (revolver >= key.size())
			{
				revolver = 0;
			}
			else
			{
				revolver++;
			}

		}

		system("CLS");
		cout << endl << "File Encryption Complete." << endl;
		cout << endl << endl;
		printData();
		system("PAUSE");
	}

	void decrypt()
	{
		unsigned int revolver = 0;

		system("CLS");
		cout << "Please wait while your data is being decrypted.";

		for (unsigned int x = 0; x <= dataSize; x++)
		{
			//creates temporary character holder and sets the tchar integer to the int casted from the x position in the for loop
			int tCharData = (int)dataBuffer[x];
			//gets the int code of the first character in the key
			int tCharKey = (int)key[revolver];



			//algorithum for encryption
			tCharData -= tCharKey;


			//executes adjusting the data to the new encryption
			dataBuffer[x] = (char)tCharData;


			if (revolver >= key.size())
			{
				revolver = 0;
			}
			else
			{
				revolver++;
			}
		}


		system("CLS");
		cout << "File Decryption Complete." << endl;
		cout << endl << endl;
		printData();
		system("PAUSE");
	}

};

class Prompter
{
public:
	//initializes classes as objects
	IO io;
	Cipher psy;

	void takeCommand()
	{
		//INFO AND INPUT
		system("CLS");
		printData();
		cout << endl << endl;


		cout << "Please choose from one of the following commands" << endl;
		cout << "1) Print Data" << endl;
		cout << "2) Encrypt" << endl;
		cout << "3) Decrypt" << endl;
		cout << "4) Read from File" << endl;
		cout << "5) Print to File" << endl;
		cout << "6) New ASCII data" << endl;
		cout << "7) Edit ASCII data" << endl;
		cout << "0) Exit" << endl;
		cout << "Choose your command by entering the number" << endl;

		int command;
		cin >> command;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			command = 100;
			
		}
		


		

		//RESPONSE
		system("CLS");

		try {
			switch (command)
			{
			
			case 0:
				exitProgram();
				break;
			case 1:
				printData();
				break;
			case 2:
				psy.askForKey();
				psy.encrypt();
				break;
			case 3:
				psy.askForKey();
				psy.decrypt();
				break;
			case 4:
				io.setFullPath();
				io.openFileBinary(fullPath);
				break;
			case 5:
				io.setFullPath();
				io.closeFileBinary(fullPath);
				break;
			case 6:
				typeWriter("clear");
				break;
			case 7:
				typeWriter("edit");
				break;
			case 100:
				cout << "You must enter a number for a command." << endl;
				system("PAUSE");
				break;
			default:
				cout << "There was an error" << endl;
				system("PAUSE");
				break;
			}
		}
		catch (...)
		{
			cout << "There was a fatal error" << endl;
			system("PAUSE");
		}
	}

	void exitProgram()
	{
		cout << "Terminating Program";
		run = false;
		exit(0);
	}
};




int main()
{
	//testing
	string defaultValue = "Hello World. Welcome to the 3NCRYPT3R. Bro its lit.";
	dataSize = (defaultValue.size() + 1);
	dataBuffer = new char[dataSize]();
	defaultValue.copy(dataBuffer, dataSize);


	Prompter prg;
	while (run == true)
	{
		prg.takeCommand();
	}
}

