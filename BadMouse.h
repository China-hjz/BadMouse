#pragma once
#include "allHeader.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <sys/stat.h>

using namespace std;

#define eventKey(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //���ָ������������Ƿ񱻰���
#define SetColor(COLOR) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | COLOR); //����������ɫ
#define RED FOREGROUND_RED //��ɫ
#define GREEN FOREGROUND_GREEN //��ɫ
#define BLUE FOREGROUND_BLUE //��ɫ
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN //��ɫ
#define WHITE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED //��ɫ
#define Click(events) mouse_event(events, 0, 0, 0, 0 ) //�����
#define LeftClick MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP //������
#define RightClick MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP //����һ�

typedef void vfunc(void); //��������

void SetTitle(const char* Title); //���ñ���
void SetWinSize(int wide, int high); //���ô��ڴ�С
void clears(bool flag); //����
void HideCursor(); //���ع�꣨�������
void ShowCursor(); //��ʾ���
void SetPos(int x, int y); //���ù���ڿ���̨�ϵ��������
template<typename _Tstr> void print(_Tstr text); //�ڹ��λ���������
template<typename _Tstr> void print(_Tstr text, int PosX, int PosY); //�ڿ���̨��ĳ�������������
template<typename _Tstr> void print(_Tstr text, WORD colors, int PosX, int PosY); //�ڿ���̨��ĳ���������ָ����ɫ������
template<typename _Tstr> void print(_Tstr text, WORD colors); //�ڹ��λ�����ָ����ɫ������
void eventLoop(vector<WORD> event, vector<vfunc*> handle); //�¼�ѭ������
void sleep_cout(string cout_str, double sleep_time); //���ʱ���������ַ�

void bubblsort(int* target, int len); //ָ��ʽð�����������ã�
size_t getFileSize(const char* fileName); //��ȡ�ļ���С�������ã�


void SetTitle(const char* Title) //���ñ���
{
	char command[100];
	sprintf_s(command,"title %s",Title);
	system(command);
}
void SetWinSize(int wide, int high)
{
	char command[100];
	sprintf_s(command,"mode con:cols=%d lines=%d",wide,high);
	system(command);
}

void clears(bool flag = 3) {//�����Ļ 
	if (flag == 1) {//˫����
		HANDLE hStdOut; CONSOLE_SCREEN_BUFFER_INFO csbi; DWORD count; DWORD cellCount; COORD homeCoords = { 0, 0 };
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE) return;
		if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
		cellCount = csbi.dwSize.X * csbi.dwSize.Y;
		if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count)) return;
		if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;
		SetConsoleCursorPosition(hStdOut, homeCoords);
	}
	else if (flag == 0) {//������
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coordScreen = { 0, 0 };
		SetConsoleCursorPosition(hConsole, coordScreen);
	}
	else {
		system("cls");
	}


}
void HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false; 
	SetConsoleCursorInfo(handle, &CursorInfo);
}
void ShowCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = true;
	SetConsoleCursorInfo(handle, &CursorInfo);
}
void SetPos(int x, int y)
{
	HANDLE hout;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
}
template<typename _Tstr> void print(_Tstr text)
{
	cout << text;
}
template<typename _Tstr> void print(_Tstr text, int PosX, int PosY)
{
	SetPos(PosX,PosY);
	print(text);
}
template<typename _Tstr> void print(_Tstr text, WORD colors, int PosX, int PosY)
{
	SetPos(PosX,PosY);
	print(text, colors);
}
template<typename _Tstr> void print(_Tstr text, WORD colors)  
{
	SetColor(colors);
	print(text);
	SetColor(WHITE);
}


void eventLoop(vector<WORD> event, vector<vfunc*> handle)
{
	while (1)
	{
		for (int i = 0; i < event.size(); i++)
		{
			if (eventKey(event[i]))
			{
				(*handle[i])();
				while (eventKey(event[i]));
			}
		}
	}
}

void bubblsort(int* target, int len) 
{
	for (int i = 0; !(i == len - 1); i++)
	{
		for (int j = 0; !(j == len - i - 1); j++)
		{
			if (*(target + j) > *(target + j + 1))
			{
				int temp = *(target + j);
				*(target + j) = *(target + j + 1);
				*(target + j + 1) = temp;
			}
		}
	}
}

void sleep_cout(string cout_str, double sleep_time = 0.2)
{
	string str = cout_str;
	if (0 == str.length()) { return; }
	for (int i = 0; i < str.length(); i++)
	{
		cout << str[i];
		Sleep(sleep_time * 1000);
	}
}

size_t getFileSize(const char* fileName) {

	if (fileName == NULL) {
		return -1;
	}

	struct stat statbuf;
	stat(fileName, &statbuf);
	size_t filesize = statbuf.st_size;

	return filesize;
}
