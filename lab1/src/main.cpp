#if defined(LIFEVOLUME_WINDOWS)

#include "MainView.hpp"

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int showCommand) {
    LifeModel model;
    MainView view(model);
    if (!view.create(instance, showCommand)) {
        MessageBoxW(nullptr, L"Не удалось создать главное окно.",
                     L"Ошибка", MB_OK | MB_ICONERROR);
        return 1;
    }

    MSG message{};
    int status;
    while ((status = GetMessageW(&message, nullptr, 0, 0)) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
    return status == -1 ? 1 : static_cast<int>(message.wParam);
}

#elif defined(LIFEVOLUME_LINUX)

#include "LinuxView.hpp"

int main(int argc, char* argv[]) {
    LifeModel model;
    LinuxView view(model);
    return view.run(argc, argv);
}

#else
#error "No supported LifeVolume platform was selected"
#endif
