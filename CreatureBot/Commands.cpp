#include "Commands.h"

Commands::Commands()
{
	this->creaturewindow = NULL;
}

Commands::~Commands()
{
}

void Commands::windowcheck(HWND& creaturewindow, std::string window, LPCSTR& windowName)
{
	windowName = window.c_str();
	creaturewindow = FindWindow(NULL, windowName);
	std::string windowcheck;

	if (creaturewindow != NULL)
	{
		windowcheck = "Window Found!";
	}
	else
	{
		windowcheck = "Window Not Found!";
	}

	std::cout << windowcheck << std::endl;
}

void Commands::processCommands(std::string& reply, HWND& creaturewindow, INPUT& ip, std::vector<WPARAM>& wparam, std::vector<LPARAM>& lparam)
{
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	std::regex re("!(.+)@.+ PRIVMSG #([^\\s]+) :(.*)");
	std::smatch match;
	std::regex_search(reply, match, re);
	std::cout << std::endl;
	std::cout << "User: " << match[1] << std::endl;
	std::cout << "Channel: " << match[2] << " Message: " << match[3] << std::endl;

	
	if (match[3] == "!next")
	{
		std::cout << "Next Command Received!" << std::endl;
		if (creaturewindow != NULL)
		{
			SendMessage(creaturewindow, WM_KEYDOWN, VK_TAB, 0);
			SendMessage(creaturewindow, WM_CHAR, VK_TAB, 9);
			Sleep(300);
			SendMessage(creaturewindow, WM_KEYUP, VK_TAB, 1);
		}

	}
	else if (match[3] == "!feed")
	{
		std::cout << "Feed Command Received!" << std::endl;
		//GetWindowRect();
		SetForegroundWindow(creaturewindow);
		ShowWindow(creaturewindow, SW_MAXIMIZE);
		SetCursorPos(625, 250);

		for (int i = 0; i < 2; i++)
		{
			ip.ki.wVk = VK_CONTROL;
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			ip.ki.wVk = VK_SHIFT;
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Press the "V" key
			ip.ki.wVk = 'E';
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			Sleep(300);

			// Release the "V" key
			ip.ki.wVk = 'E';
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));

			ip.ki.wVk = VK_SHIFT;
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));


			ip.ki.wVk = VK_CONTROL;
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));
			Sleep(800);
		}
	}
	else if (match[3] == "!home")
	{
		std::cout << "First Room Command Received!" << std::endl;

		SendMessage(creaturewindow, WM_KEYDOWN, VK_HOME, 0);
		Sleep(300);
		SendMessage(creaturewindow, WM_KEYUP, VK_HOME, 1);
	}
	else if (match[3] == "!end")
	{
		std::cout << "Last Room Command Received!" << std::endl;

		SendMessage(creaturewindow, WM_KEYDOWN, VK_END, 0);
		Sleep(300);
		SendMessage(creaturewindow, WM_KEYUP, VK_END, 1);
	}
	else if (match[3] == "!metanext")
	{
		std::cout << "Next MetaRoom Command Received" << std::endl;

		SendMessage(creaturewindow, WM_KEYDOWN, VK_NEXT, 0);
		Sleep(300);
		SendMessage(creaturewindow, WM_KEYUP, VK_NEXT, 1);
	}
	else if (match[3] == "!metalast")
	{
		std::cout << "Previous MetaRoom Command Received" << std::endl;

		SendMessage(creaturewindow, WM_KEYDOWN, VK_PRIOR, 0);
		Sleep(300);
		SendMessage(creaturewindow, WM_KEYUP, VK_PRIOR, 1);
	}
	else if (match[3] == "!love")
	{
		std::cout << "Love Time!" << std::endl;

		SetForegroundWindow(creaturewindow);
		SetFocus(creaturewindow);
		SetCursorPos(500, 300);

		wparam.emplace_back('L');
		wparam.emplace_back('O');
		wparam.emplace_back('V');
		wparam.emplace_back('E');
		wparam.emplace_back('T');
		wparam.emplace_back('I');
		wparam.emplace_back('M');
		wparam.emplace_back('E');


		lparam.emplace_back(108);
		lparam.emplace_back(111);
		lparam.emplace_back(118);
		lparam.emplace_back(101);
		lparam.emplace_back(116);
		lparam.emplace_back(105);
		lparam.emplace_back(109);
		lparam.emplace_back(101);

		for (int i = 0; i < 4; i++)
		{
			SendMessage(creaturewindow, WM_KEYDOWN, wparam[i], 0);
			SendMessage(creaturewindow, WM_CHAR, wparam[i], lparam[i]);
			Sleep(100);
			SendMessage(creaturewindow, WM_KEYUP, wparam[i], 1);
			
		}

		SendMessage(creaturewindow, WM_KEYDOWN, VK_SPACE, 0);
		SendMessage(creaturewindow, WM_CHAR, VK_SPACE, 32);
		Sleep(100);
		SendMessage(creaturewindow, WM_KEYUP, VK_SPACE, 1);

		for (int i = 4; i < wparam.size(); i++)
		{
			SendMessage(creaturewindow, WM_KEYDOWN, wparam[i], 0);
			SendMessage(creaturewindow, WM_CHAR, wparam[i], lparam[i]);
			Sleep(100);
			SendMessage(creaturewindow, WM_KEYUP, wparam[i], 1);
			
		}
		
		SendMessage(creaturewindow, WM_KEYDOWN, VK_RETURN, 0);
		SendMessage(creaturewindow, WM_CHAR, VK_RETURN, 13);
		Sleep(100);
		SendMessage(creaturewindow, WM_KEYUP, VK_RETURN, 1);

		wparam.clear();
		lparam.clear();
	}
	else if (match[3] == "!war")
	{
		std::cout << "War Time!" << std::endl;
		SetForegroundWindow(creaturewindow);
		SetFocus(creaturewindow);
		SetCursorPos(500, 300);

		wparam.emplace_back('W');
		wparam.emplace_back('A');
		wparam.emplace_back('R');
		wparam.emplace_back('T');
		wparam.emplace_back('I');
		wparam.emplace_back('M');
		wparam.emplace_back('E');

		lparam.emplace_back(119);
		lparam.emplace_back(97);
		lparam.emplace_back(114);
		lparam.emplace_back(116);
		lparam.emplace_back(105);
		lparam.emplace_back(109);
		lparam.emplace_back(101);

		for (int i = 0; i < 3; i++)
		{
			SendMessage(creaturewindow, WM_KEYDOWN, wparam[i], 0);
			SendMessage(creaturewindow, WM_CHAR, wparam[i], lparam[i]);
			Sleep(100);
			SendMessage(creaturewindow, WM_KEYUP, wparam[i], 1);

		}

		SendMessage(creaturewindow, WM_KEYDOWN, VK_SPACE, 0);
		SendMessage(creaturewindow, WM_CHAR, VK_SPACE, 32);
		Sleep(100);
		SendMessage(creaturewindow, WM_KEYUP, VK_SPACE, 1);

		for (int i = 3; i < wparam.size(); i++)
		{
			SendMessage(creaturewindow, WM_KEYDOWN, wparam[i], 0);
			SendMessage(creaturewindow, WM_CHAR, wparam[i], lparam[i]);
			Sleep(100);
			SendMessage(creaturewindow, WM_KEYUP, wparam[i], 1);

		}

		SendMessage(creaturewindow, WM_KEYDOWN, VK_RETURN, 0);
		SendMessage(creaturewindow, WM_CHAR, VK_RETURN, 13);
		Sleep(100);
		SendMessage(creaturewindow, WM_KEYUP, VK_RETURN, 1);

		wparam.clear();
		lparam.clear();

	}


 
}
