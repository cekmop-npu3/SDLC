#include "MainView.hpp"

#include "InputDialog.hpp"
#include "resource.h"

#include <stdexcept>

MainView::MainView(LifeModel& model)
    : model_(model), controller_(model, *this) {
    model_.setObserver(this);
}

MainView::~MainView() {
    model_.setObserver(nullptr);
}

bool MainView::create(HINSTANCE instance, int showCommand) {
    WNDCLASSW wc{};
    wc.lpfnWndProc = windowProc;
    wc.hInstance = instance;
    wc.lpszClassName = L"LifeVolumeMain";
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    if (!RegisterClassW(&wc))
        return false;

    window_ = CreateWindowExW(0, wc.lpszClassName,
        L"Калькулятор громкости жизни", WS_OVERLAPPED | WS_CAPTION |
        WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
        560, 340, nullptr, nullptr, instance, this);
    if (!window_)
        return false;
    ShowWindow(window_, showCommand);
    return true;
}

void MainView::createControls() {
    auto instance = GetModuleHandleW(nullptr);
    result_ = CreateWindowExW(0, L"STATIC", L"Данные не введены",
        WS_CHILD | WS_VISIBLE, 24, 24, 500, 200,
        window_, nullptr, instance, nullptr);
    HWND button = CreateWindowExW(0, L"BUTTON", L"Ввести данные",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
        175, 245, 190, 32, window_,
        reinterpret_cast<HMENU>(IDC_ENTER), instance, nullptr);
    for (HWND control : {result_, button})
        SendMessageW(control, WM_SETFONT,
            reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), TRUE);
    SetFocus(button);
}

void MainView::onModelChanged(const LifeState& state) {
    displayed_ = state;
    const auto& d = displayed_.data;
    std::wstring text = L"Разговоры: " + std::to_wstring(d.talks)
        + L" раз/день\r\nМузыка: " + std::to_wstring(d.music)
        + L" раз/день\r\nРугань: " + std::to_wstring(d.swearing)
        + L" раз/день\r\n\r\nУровень шума жизни: "
        + std::to_wstring(displayed_.score) + L" усл. ед.\r\nРекомендация: "
        + (displayed_.earplugs ? L"беруши" : L"караоке");
    SetWindowTextW(result_, text.c_str());
}

void MainView::openInput(const LifeData& saved) {
    InputDialog dialog(controller_, saved);
    dialog_ = &dialog;
    try {
        dialog.show(window_);
    } catch (const std::runtime_error&) {
        dialog_ = nullptr;
        showError(L"Не удалось открыть окно ввода.");
    }
    dialog_ = nullptr;
}

void MainView::showError(const std::wstring& message) {
    HWND owner = dialog_ ? dialog_->handle() : window_;
    MessageBoxW(owner, message.c_str(), L"Ошибка", MB_OK | MB_ICONERROR);
}

LRESULT CALLBACK MainView::windowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    auto* self = reinterpret_cast<MainView*>(
        GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    if (msg == WM_NCCREATE) {
        auto* cs = reinterpret_cast<CREATESTRUCTW*>(lp);
        self = static_cast<MainView*>(cs->lpCreateParams);
        self->window_ = hwnd;
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    }
    if (self) {
        if (msg == WM_CREATE) {
            self->createControls();
            return 0;
        }
        if (msg == WM_COMMAND && LOWORD(wp) == IDC_ENTER) {
            self->controller_.enterData();
            return 0;
        }
        if (msg == WM_DESTROY) {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}
