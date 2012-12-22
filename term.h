#ifndef TERM__H
#define TERM__H

#ifdef _WIN32
#  include <windows.h>
#endif

#ifdef _WIN32
static HANDLE                     hConsoleOutput = 0;
static CONSOLE_SCREEN_BUFFER_INFO csbi;
#endif

void clear() {

#ifdef _WIN32
    if ( hConsoleOutput == 0 )
    {
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);
    }
#endif

    fflush(stdout);
#ifdef _WIN32
    {
        COORD point;
        DWORD dummy;
        DWORD count;

        point.X = 0;
        point.Y = 0;
        count   = csbi.dwSize.X * csbi.dwSize.Y;

        FillConsoleOutputCharacter(hConsoleOutput, ' ', count, point, &dummy);
        SetConsoleCursorPosition(hConsoleOutput, point);
    }
#else
        printf("\033[H\033[2J");
#endif
    fflush(stdout);
}

void pause() {
    printf("Press enter to continue\n");
    
    while (fgetc(stdin) != '\n')
        ;

    clear();
}

#endif