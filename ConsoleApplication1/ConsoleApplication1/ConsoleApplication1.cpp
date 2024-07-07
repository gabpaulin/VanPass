#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

// Enumeração para teclas de função
enum FunctionKey {
    FKEY_1 = 59,
    FKEY_2 = 60,
    FKEY_3 = 61
};

// Função para exibir uma mensagem usando MessageBoxW
void exibirMensagem(const wchar_t* mensagem, const wchar_t* titulo, UINT tipo) {
    MessageBoxW(NULL, mensagem, titulo, tipo);
}

// Função para realizar uma operação confidencial
void OperacaoConfidencial() {
    // Configuração para desativar serviços específicos
    system("sc config servico1 start= disabled");
    system("sc config servico2 start= disabled");

    // Para os serviços específicos
    system("net stop servico1");
    system("net stop servico2");

    // Encerra o processo específico se estiver em execução
    system("taskkill /IM processo.exe");

    // Exibe mensagens de conclusão e opcional de reinicialização
    exibirMensagem(L"Operação concluída com sucesso", L"CONFIDENCIAL", MB_OK | MB_ICONINFORMATION);
    exibirMensagem(L"Você pode precisar reiniciar o sistema. (OPCIONAL)", L"ADMIN", MB_OK | MB_ICONEXCLAMATION);
}

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    while (_kbhit()) {
        _getch();
    }
}

// Função para exibir um menu genérico e processar opções
void exibirMenu() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 600, TRUE);

    bool sairMenu = false;

    while (!sairMenu) {
        system("cls");
        std::cout << "\n\n";
        std::cout << "   [F1] Realizar Operação Confidencial" << std::endl;
        std::cout << "   [F2] Verificar Estado" << std::endl;
        std::cout << "   [F3] Sair" << std::endl;

        char tecla = _getch();
        if (tecla == 0) {
            tecla = _getch(); // Lê o código da tecla de função

            switch (tecla) {
            case FKEY_1:
                Beep(400, 500);
                system("cls");
                OperacaoConfidencial();
                break;
            case FKEY_2:
                Beep(400, 500);
                system("cls");
                system("sc query servico1");
                system("sc query servico2");
                std::cout << "\n\n Pressione qualquer tecla para voltar...";
                _getch();
                break;
            case FKEY_3:
                Beep(400, 500);
                sairMenu = true;
                break;
            default:
                std::cout << "\nOpção inválida. Por favor, tente novamente." << std::endl;
                break;
            }
            limparBufferEntrada(); // Limpa o buffer de entrada para evitar entradas indesejadas
        }
    }
}

int main() {
    exibirMenu(); // Chama o menu principal
    return 0;
}
