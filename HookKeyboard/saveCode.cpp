/*
	// if wParam and lParam get key information
	if (nCode == HC_ACTION) 
	{
		// wParam has WM_KEYDOWN, WM_KEYUP, WM_SYSKEYDOWN, WM_SYSKEYUP
		// lParam contains key information
			if (wParam ==  WM_KEYDOWN) {
			keyInfo = (PKBDLLHOOKSTRUCT) lParam;
			
			// convert key info
			
			switch (keyInfo->vkCode) 
			{
			case VK_LSHIFT:
				strcpy(keyName, "LShift");
				break;
			case VK_RSHIFT:
				strcpy(keyName, "RShift");
				break;
			case VK_LCONTROL:
				strcpy(keyName, "LCtrl");
				break;
			case VK_RCONTROL:
				strcpy(keyName, "RCtrl");
				break;
			case VK_LWIN:
				strcpy(keyName, "LWin");
				break;
			case VK_LMENU:
				strcpy(keyName, "LAlt");
				break;
			case VK_RMENU:
				strcpy(keyName, "RAlt");
				break;
			case VK_SPACE:
				strcpy(keyName, "Space");
				break;
			case VK_BACK:
				strcpy(keyName, "BackSpace");
				break;
			case VK_CAPITAL:
				strcpy(keyName, (GetKeyState(VK_CAPITAL)) ? "CAP_OFF" : "CAP_ON");
				break;
			case VK_RETURN:
				strcpy(keyName, "Enter");
				break;
			default:
				keyName[0] = keyInfo->vkCode;
				keyName[1] = '\0';
			break;
			}

			std::cout << keyName << std::endl;			
		}	
	}	*/