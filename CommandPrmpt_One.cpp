
#include<stdio.h>
#include<stdlib.h>
#include<tchar.h>
#include<locale.h>
#include<windows.h>

//������

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[]
	= _T("'%s'��(��) ������ �� �ִ� ���α׷��� �ƴմϴ�. \n");
	
TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int CmdReadTokenize(void);
int CmdProcessing(int);
TCHAR * StrLower(TCHAR *);

int _tmain(int argc, TCHAR * argv[])
{
	_tsetlocale(LC_ALL, _T("Korean"));
	
	if(argc > 2)
	{
		for(int i=1; i<argc; i++)
			_tcscpy(cmdTokenList[i-1], argv[i]);
		CmdProcessing(argc-1);
	}
	
	DWORD isExit;//unsigned long -> DWORD
	while(1)
	{
		int tokenNum = CmdReadTokenize();
		
		if(tokenNum==0)
			continue;
		
		isExit = CmdProcessing(tokenNum);
		if(isExit == TRUE)
		{
			_fputts(_T("��ɾ� ó���� �����մϴ�. \n"), stdout);
			break;
		}
	}
	return 0;
}



int CmdReadTokenize(void)
{
	TCHAR * token; //���ڿ��� token �����ͺ��� ����
	_fputts( _T("Best command Prompt>> "), stdout);
	_getts(cmdString);//cmdString���� ���͸� �Է¹��������� ���ڿ� �Է¹���
	token = _tcstok(cmdString, seps);//token���� , /t /n�� �Էµɶ����� �� ���� ���ڿ��� �����Ѵ�
	int tokenNum = 0;
	while(token != NULL)
	{
		_tcscpy( cmdTokenList[tokenNum++], StrLower(token) );//cmdTokenList�� StrLower�� ����
		token = _tcstok(NULL, seps);
	}
	
	return tokenNum;
}

int CmdProcessing(int tokenNum)
{
	BOOL isRun;
	STARTUPINFO si = {0,};
	PROCESS_INFORMATION pi;
	
	TCHAR cmdStringWithOption[STR_LEN] = {0,};
	TCHAR optString[STR_LEN] = {0,};
	
	if( !_tcscmp(cmdTokenList[0], _T("exit")) )
	{
		return TRUE;
	}
	else if( !_tcscmp(cmdTokenList[0], _T("start")) ) //��â�� start �ڿ� ���� ��ɾ� ����
	{
		if(tokenNum>1){ //echo �Լ��� ������
			for(int i=1; i<tokenNum; i++)
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		_stprintf(cmdStringWithOption, _T("%s %s"), _T("CmdProject.exe"), optString);
		}
		else//start�� ������
			_stprintf(cmdStringWithOption, _T("%s"), _T("CmdProject.exe"));
			
		isRun = CreateProcess(NULL,cmdStringWithOption,NULL, NULL,
		TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else if( !_tcscmp(cmdTokenList[0], _T("echo")) ) // ���ڿ��� �״�� ���
	{
		for(int i=1; i<tokenNum; i++)
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		_tprintf(_T("echo message : %s \n"), optString);
	}
	else
	{
		_tcscpy(cmdStringWithOption, cmdTokenList[0]);
		
		for(int i=1; i<tokenNum; i++)
			_stprintf(cmdStringWithOption, _T("%s %s"), cmdStringWithOption, cmdTokenList[i]);
		
		isRun =	CreateProcess ( NULL, cmdStringWithOption, NULL, NULL,
		TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		
		if(isRun == FALSE)
		_tprintf(ERROR_CMD, cmdTokenList[0]);
	}
	
	return 0;
}

TCHAR * StrLower(TCHAR *pStr)//��ҹ��� ��ȯ
{
	TCHAR *ret = pStr;
	
	while(*pStr)
	{
		if(_istupper(*pStr))
			*pStr = _totlower(*pStr);
		pStr++;
	}
	
	return ret;
}
