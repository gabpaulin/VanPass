#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

// Enumeração para teclas de função
enum FunctionKey {
    FKEY_F1 = 59,
    FKEY_F2 = 60,
    FKEY_F3 = 61
};

// Função para exibir uma mensagem usando MessageBoxW
void showMessage(const wchar_t* message, const wchar_t* title, UINT type) {
    MessageBoxW(NULL, message, title, type);
}

// Função para realizar o bypass do Vanguard
void Bypass() {
    // Configuração para desativar serviços relacionados ao Vanguard
    system("sc config vgc start= disabled");
    system("sc config vgk start= disabled");

    // Para os serviços VGC e VGK
    system("net stop vgc");
    system("net stop vgk");

    // Encerra o processo vgtray.exe se estiver em execução
    system("taskkill /IM vgtray.exe");

    // Exibe mensagens de conclusão e opcional de reinicialização
    showMessage(L"Done bypassing Vanguard", L"BYPASS", MB_OK | MB_ICONINFORMATION);
    showMessage(L"You may need to reboot your system. (OPTIONAL)", L"ADMIN", MB_OK | MB_ICONEXCLAMATION);
}

// Função para limpar o buffer de entrada
void clearInputBuffer() {
    while (_kbhit()) {
        _getch();
    }
}

// Função para exibir o menu e processar as opções
void displayMenu() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 600, TRUE);

    bool exitMenu = false;

    while (!exitMenu) {
        system("cls");
        std::cout << "\n\n";
        std::cout << "   [F1] Bypass Vanguard" << std::endl;
        std::cout << "   [F2] Check Vanguard Status" << std::endl;
        std::cout << "   [F3] Exit" << std::endl;

        char key = _getch();
        if (key == 0) {
            key = _getch(); // Lê o código da tecla de função

            switch (key) {
            case FKEY_F1:
                Beep(400, 500);
                system("cls");
                Bypass();
                break;
            case FKEY_F2:
                Beep(400, 500);
                system("cls");
                system("sc query vgc");
                system("sc query vgk");
                std::cout << "\n\n Press any key to return...";
                _getch();
                break;
            case FKEY_F3:
                Beep(400, 500);
                exitMenu = true;
                break;
            default:
                std::cout << "\nInvalid option. Please try again." << std::endl;
                break;
            }
            clearInputBuffer(); // Limpa o buffer de entrada para evitar entradas indesejadas
        }
    }
}

int main() {
    displayMenu(); // Chama o menu principal
    return 0;
}
