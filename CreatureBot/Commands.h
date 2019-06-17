#pragma once
#include <Windows.h>
#include <iostream>
#include <regex>
#include <vector>
class Commands
{
public:
	Commands();
	~Commands();



	void windowcheck(HWND& creaturewindow, std::string window, LPCSTR& windowName);
	void processCommands(std::string& reply, HWND& creaturewindow, INPUT& ip, std::vector<WPARAM>& wparam, std::vector<LPARAM>& lparam);

	HWND creaturewindow;

	INPUT ip;

	LPCSTR windowName;

	std::vector<WPARAM> wparam;
	std::vector<LPARAM> lparam;
};
