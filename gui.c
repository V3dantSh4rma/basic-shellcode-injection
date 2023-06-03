#include <Windows.h>

int main(){
    int mBox = MessageBox(NULL, "Do you like the music genre Techno?", ":)", MB_YESNOCANCEL);
    switch(mBox){
        case IDYES:
            MessageBox(NULL, "Me too. :)", ":)", MB_OK);
            break;
        case IDNO:
            MessageBox(NULL, "It's okay to have a different music taste.", ":)", MB_OK);
            break;
        case IDCANCEL:
            MessageBox(NULL, "Goodbye. :)", ":)", MB_OK);
            break;
    }
    return EXIT_SUCCESS;
}