
#include<stdio.h>
#include<stdlib.h>
#include<tchar.h>
#include<locale.h>
#include<windows.h>

//수정중

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[]
	= _T("'%s'은(는) 실행할 수 있는 프로그램이 아닙니다. \n");
	
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
			_fputts(_T("명령어 처리를 종료합니다. \n"), stdout);
			break;
		}
	}
	return 0;
}



int CmdReadTokenize(void)
{
	TCHAR * token; //문자열형 token 포인터변수 선언
	_fputts( _T("Best command Prompt>> "), stdout);
	_getts(cmdString);//cmdString에서 엔터를 입력받을때까지 문자열 입력받음
	token = _tcstok(cmdString, seps);//token에는 , /t /n이 입력될때마다 그 다음 문자열을 저장한다
	int tokenNum = 0;
	while(token != NULL)
	{
		_tcscpy( cmdTokenList[tokenNum++], StrLower(token) );//cmdTokenList에 StrLower을 복사
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
	else if( !_tcscmp(cmdTokenList[0], _T("start")) ) //새창에 start 뒤에 붙인 명령어 실행
	{
		if(tokenNum>1){ //echo 함수가 있을때
			for(int i=1; i<tokenNum; i++)
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		_stprintf(cmdStringWithOption, _T("%s %s"), _T("CmdProject.exe"), optString);
		}
		else//start만 있을때
			_stprintf(cmdStringWithOption, _T("%s"), _T("CmdProject.exe"));
			
		isRun = CreateProcess(NULL,cmdStringWithOption,NULL, NULL,
		TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else if( !_tcscmp(cmdTokenList[0], _T("echo")) ) // 문자열을 그대로 출력
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

TCHAR * StrLower(TCHAR *pStr)//대소문자 변환
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
