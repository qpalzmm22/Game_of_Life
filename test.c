#include <stdio.h>
#include <wchar.h>              //For wprintf and wide chars
#include <io.h>                 //For _setmode
#define U_16 0x20000            //U-16 text mode, for the text blocks

const wchar_t shade_block[] = {
    L"▒▒██████▒▒\n"
        "▒████████▒\n"
        "██████████\n"
        "▒████████▒\n"
        "▒▒██████▒▒\n"
};

int main()
{
    _setmode(_fileno(stdout), U_16); //set the output mode to U_16
    wprintf(L"%s\n", shade_block);

    return 0;

}
