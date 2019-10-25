// Encrypter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

//global variables
bool run = true;
string fullPath = "";
string fullData = "Winner Winner Chicken Dinner";

//global functions
void printData()
	{
		cout << "Current Data: " << endl;
		cout << fullData;

		//add lots of space between data and next key
		cout << endl << endl << endl << "------------------END------------------" << endl << endl << endl << endl << endl << endl << endl;
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
	
	void openFile(string path)
	{
		//creqates the stream obj
		ifstream openObj;

		//opens the streaming file
		try {
		openObj.open(path, ios::in);
		}
		catch (...)
		{
			cout << "There was an error opening this file." << endl;
		}

		//creates temp vars on stack for fast reading
		string fileStream;
		char c;
		//reads the characters in one by one
		while (!openObj.eof())
		{
			openObj.get(c);
			fileStream += c;
		}

		//sets main fullText to fileStream data
		fullData = fileStream;

		//close the stream
		openObj.close();


		cout << "Read from File complete." << endl << endl;
		printData();
	}

	void closeFile(string path)
	{
		//creates the stream obj
		ofstream closeObj;

		//opens the file
		closeObj.open(path, ios::out);

		//creates a temp object on the stack for fast writing
		string fileStream = fullData;

		//write the data to file
		closeObj << fileStream;

		//close the stream
		closeObj.close();

		cout << "Print to File complete." << endl << endl;
		printData();
	}
};

class Cipher
{
public:
	string key;

	void askForKey()
	{
		cout << "What key would you like to use for Encryption/Decryption?" << endl;
		cin >> key;
		cout << endl << endl;
	}

	void encrypt()
	{
		unsigned int revolver = 0;

		for (unsigned int x = 0; x <= fullData.size(); x++)
		{
			//creates temporary character holder and sets the tchar integer to the int casted from the x position in the for loop
			int tCharData = (int)fullData[x];
			//gets the int code of the first character in the key
			int tCharKey = (int)key[revolver];



			//algorithum for encryption
			tCharData += tCharKey;
			if (tCharData > 127)
			{
				tCharData -= 127;
			}


			//executes adjusting the data to the new encryption
			fullData[x] = (char)tCharData;


			if (revolver >= key.size())
			{
				revolver = 0;
			}
			else
			{
				revolver++;
			}
		}

		cout << "File Encryption Complete." << endl;
		cout << endl << endl;
		printData();
	}

	void decrypt()
	{
		unsigned int revolver = 0;

		for (unsigned int x = 0; x <= fullData.size(); x++)
		{
			//creates temporary character holder and sets the tchar integer to the int casted from the x position in the for loop
			int tCharData = (int)fullData[x];
			//gets the int code of the first character in the key
			int tCharKey = (int)key[revolver];



			//algorithum for encryption
			tCharData -= tCharKey;
			if (tCharData < 0)
			{
				tCharData += 127;
			}


			//executes adjusting the data to the new encryption
			fullData[x] = (char)tCharData;


			if (revolver >= key.size())
			{
				revolver = 0;
			}
			else
			{
				revolver++;
			}
		}



		cout << "File Decryption Complete." << endl;
		cout << endl << endl;
		printData();
	}

};

class Prompter
{
	//initializes classes as objects
	IO io;
	Cipher psy;

public:

	void takeCommand()
	{
		//INFO AND INPUT
		system("CLS");
		cout << "Current File: " << fullPath << endl;
		cout << "Current Data: " << endl << fullData << endl;
		cout << endl << endl;


		cout << "Please choose from one of the following commands" << endl;
		cout << "1) Print Data" << endl;
		cout << "2) Encrypt" << endl;
		cout << "3) Decrypt" << endl;
		cout << "4) Read from File" << endl;
		cout << "5) Print to File" << endl;
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
				io.openFile(fullPath);
				break;
			case 5:
				io.setFullPath();
				io.closeFile(fullPath);
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
	Prompter prg;
	while (run == true)
	{
		prg.takeCommand();
	}
}

