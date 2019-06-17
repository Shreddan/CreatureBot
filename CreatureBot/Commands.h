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



	void windowcheck(HWND creaturewindow);
	void processCommands(std::string& reply, HWND& creaturewindow, INPUT& ip, std::vector<WPARAM>& wparam, std::vector<LPARAM>& lparam);

	HWND creaturewindow = FindWindow(NULL, "Docking Station - Engine 2.296 B195 - Autokill enabled");
	INPUT ip;

	std::vector<WPARAM> wparam;
	std::vector<LPARAM> lparam;
};
