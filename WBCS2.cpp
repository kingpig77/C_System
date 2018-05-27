#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<locale.h>

int main(void)
{
	_wsetlocale(LC_ALL, L"korean");	
	wchar_t str[] = L"ABC";
	int size = sizeof(str);
	int len = wcslen(str);
	
	wprintf(L"Array Size : %d \n", size);
	wprintf(L"문자열 Length : %d \n", len);
	
	system("pause");
}