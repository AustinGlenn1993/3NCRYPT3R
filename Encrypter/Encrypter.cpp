// Encrypter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//includs for tiny file dialog
#include <stdio.h>
#include <string.h>
#include "tinyfiledialogs.h"

//includes for file saving and console input output
#include <iostream>
#include <fstream>
#include <string>



using namespace std;

//global variables
bool run = true;
string fullPath = "";
int dataSize = 2;
char* dataBuffer;

//filters for the tinyfiledialog
char const* lFilterPatterns[3] = { "*.txt", "*.text", "*."};


//global functions
void printData()
	{
		cout << "Current File Path: --------------------------------------------------" << endl;
		cout <<	fullPath << endl;
		cout << endl << "Current Data PREVIEW: -----------------------------------------------" << endl;

		//Display a PREVIEW of Data NO GREATER THAN 1500 BYTES
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
		for (int x = 0; x < loop; x++)
		{
			displayText += dataBuffer[x];
		}
		cout << displayText << endl;




		//If all Data could not be shown.
		if (loop >= 1500)
		{
			cout << endl << endl << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << "...........MORE DATA EXISTS, BUT IS TOO MUCH TO PREVIEW.........." << endl;
			cout << "-------------------------------END-------------------------------" << endl << endl << endl;
		}
		else
		{
			cout << endl << endl << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << "......................ALL DATA PREVIEWING ABOVE.................." << endl;
			cout << "-------------------------------END-------------------------------" << endl << endl << endl;
		}
		
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



//classes used
class IO
{
public:
	/*   THIS FUNCTION IS DEPRECATED WITH THE INRODUCTION OF TINY FILE DIALOG
	void setFullPath()
	{
		//folder for filepath
		string filePath = "FILES";
		string fileName;

		cout << "What is the name of the file you are encrypting?" << endl;
		cin >> fileName;

		fullPath = filePath + "/" + fileName;
	}
	*/

	void fullPathToCompliant()
	{
		//for loop to replace all backward slashes that are interpreted as escape codes
		//to backslashes that are interpretted as forward slashes that are not escape codes
		for (int x = 0; x < (int)fullPath.size(); x++)
		{
			if (fullPath[x] == '\\')
			{
				fullPath[x] = '/';
			}

		}
	}

	void openFileBinary()
	{
		//creates the char const for saving the file
		char const* lTheOpenFileName;

		//open the open file dialog
		lTheOpenFileName = tinyfd_openFileDialog(
			"Open File",
			"",
			3,
			lFilterPatterns,
			NULL,
			0);

		//sets full path to the returned path
		fullPath = lTheOpenFileName;

		//ensures file path complies with c++ library and fstream
		fullPathToCompliant();

		//creates the stream obj
		ifstream openObj;

		//trys to opens the streaming file
		try {
			openObj.open(fullPath, ios::in|ios::binary);
		}
		catch (...)
		{
			cout << "There was an error opening this file." << endl;
		}

		//ERROR CHECKING
		if (openObj)
		{
			//if openObj was successful

			//gets size of file
			openObj.seekg(0, openObj.end);
			dataSize = (int)openObj.tellg();
			openObj.seekg(0, openObj.beg);

			//initializes dataBuffer to array of 'xsize'
			dataBuffer = new char[dataSize]();

			//reads file to the BUFFER in the amount of XSIZE
			openObj.read(reinterpret_cast<char*>(dataBuffer), dataSize);

			//close the stream
			openObj.close();

			cout << "File located at: " << fullPath << endl;
			cout << "Size of file: " << dataSize << " bytes." << endl;
			cout << "..." << endl;
			cout << "All " << openObj.gcount() << " bytes read successfully." << endl;
			cout << "Read from File complete." << endl << endl;
		}
		else
		{
			std::cout << "Error: only " << openObj.gcount() << " bytes could be read." << endl;
			cout << "Read from File complete with errors." << endl << endl;
		}

		system("PAUSE");
	}

	void closeFileBinary()
	{
		//creates the char const for saving the file
		char const* lTheSaveFileName;

		//open save file dialog
		lTheSaveFileName = tinyfd_saveFileDialog(
			"let us save this password",
			"passwordFile.txt",
			2,
			lFilterPatterns,
			NULL);

		//sets full path to the returned path
		fullPath = lTheSaveFileName;

		//ensures file path complys with c++ library and fstream
		fullPathToCompliant();

		//creates the stream obj
		ofstream closeObj;

		try {
			//opens the file
			closeObj.open(fullPath, ios::out|ios::binary);
		}
		catch (...)
		{
			cout << "There was an error opening this file." << endl;
		}

		//ERROR CHECKING
		if (closeObj)
		{
			//write the data to file
			closeObj.write(reinterpret_cast<char*>(dataBuffer), dataSize);

			//close the stream
			closeObj.close();

			cout << "File located at: " << fullPath << endl;
			cout << "Size of file: " << dataSize << " bytes." << endl;
			cout << "..." << endl;
			cout << "All " << dataSize << " byte of data written successfully." << endl;;
			cout << "Print to File complete." << endl << endl;
		}
		else
		{
			cout << "Print to File complete with errors." << endl << endl;
		}

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
		int revolver = 0;

		system("CLS");
		cout << "Please wait while your data is being encrypted.";

		for (int x = 0; x <= dataSize; x++)
		{
			//creates temporary character holder and sets the tchar integer to the int casted from the x position in the for loop
			int tCharData = (int)dataBuffer[x];
			//gets the int code of the first character in the key
			int tCharKey = (int)key[revolver];



			//algorithum for encryption
			tCharData += tCharKey;


			//executes adjusting the data to the new encryption
			dataBuffer[x] = (char)tCharData;


			if (revolver >= (int)key.size())
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

		for (int x = 0; x <= dataSize; x++)
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
				io.openFileBinary();
				break;
			case 5:
				io.closeFileBinary();
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



//main functions
int main()
{
	//testing
	string defaultValue = "Hello World. Welcome to the 3NCRYPT3R. Bro its lit.";
	dataSize = (defaultValue.size() + 1);
	dataBuffer = new char[dataSize]();
	defaultValue.copy(dataBuffer, dataSize);


	tinyfd_messageBox(
		"Welcome",
		"Program Started Successfully\nWelcome to 3NCRYPT3R",
		"ok",
		"info",
		1);

	Prompter prg;
	while (run == true)
	{
		prg.takeCommand();
	}
}

