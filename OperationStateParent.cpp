#include<stdio.h>
#include<tchar.h>
#include<windows.h>

int _tmain(int argc, TCHAR* argv[])
{
    STARTUPINFO si = {0, };
    PROCESS_INFORMATION pi;
    DWORD state;

    si.cb = sizeof(si);
    si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
    si.dwX = 100;
    si.dwY = 200;
    si.dwXSize = 300;
    si.dwYSize = 200;
    si.lpTitle = _T("return & exit");

    TCHAR command[] = _T("OperationStateChild.exe");

    CreateProcess (NULL, command,
    NULL, NULL, TRUE,
    CREATE_NEW_CONSOLE,
    NULL, NULL,
    &si, &pi
    );

    for (DWORD i=0; i<100000; i++)//child프로세스가 연산을 마칠때까지 기다리기위함,
        for(DWORD i=0; i<100000; i++);

        //WaitForSingleObject(pi.hProcess, INFINITE);

    GetExitCodeProcess(pi.hProcess, &state);
    if(state == STILL_ACTIVE)//위에 반복문 돌동안 연산이 끝나지않을경우
        _tprintf(_T("STILL_ACTIVE \n\n"));
    
    else
        _tprintf(_T("state : %d \n\n"), state);//만약 반복문이 돌동안 연산이 끝났을 경우 종료코드확인.
    
    //CloseHandle(pi.hProcess);

    return 0;
    
}