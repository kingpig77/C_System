#include<stdio.h>
#include<windows.h>

#define DIR_LEN MAX_PATH+1

int main(int argc, char* argv[])
{
    STARTUPINFO si = {0, };
    PROCESS_INFORMATION pi;

    si.cb = sizeof(si);
    si.dwXSize = 50;
    si.dwYSize = 60;
    si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
    si.lpTitle = "CreateProcess Test";

    char command[]="calc.exe";
    char cDir[DIR_LEN];
    BOOL state;

    GetCurrentDirectory(DIR_LEN, cDir);
    fputs(cDir, stdout);
    fputs("\n", stdout);

    state = CreateProcess(
        NULL,
        command,
        NULL, NULL, TRUE,
        CREATE_NEW_CONSOLE,
        NULL, NULL, &si, &pi
    );

    if(state!=0)
    fputs("Creation OK! \n", stdout);

    else
    fputs("Creation Fail! \n", stdout);

    return 0;
}