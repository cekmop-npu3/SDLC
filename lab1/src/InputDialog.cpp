#include "InputDialog.hpp"

#include "resource.h"

#include <stdexcept>

InputDialog::InputDialog(LifeController& controller, const LifeData& saved)
    : controller_(controller), saved_(saved) {}

void InputDialog::show(HWND owner) {
    const auto result = DialogBoxParamW(GetModuleHandleW(nullptr),
        MAKEINTRESOURCEW(IDD_INPUT), owner, dialogProc,
        reinterpret_cast<LPARAM>(this));
    window_ = nullptr;
    if (result == -1)
        throw std::runtime_error("Cannot create input dialog");
}

HWND InputDialog::handle() const {
    return window_;
}

std::wstring InputDialog::readField(int id) const {
    HWND field = GetDlgItem(window_, id);
    int length = GetWindowTextLengthW(field);
    std::wstring text(length + 1, L'\0');
    int copied = GetWindowTextW(field, text.data(), length + 1);
    text.resize(copied);
    return text;
}

INT_PTR CALLBACK InputDialog::dialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    auto* self = reinterpret_cast<InputDialog*>(GetWindowLongPtrW(hwnd, DWLP_USER));
    if (msg == WM_INITDIALOG) {
        self = reinterpret_cast<InputDialog*>(lp);
        self->window_ = hwnd;
        SetWindowLongPtrW(hwnd, DWLP_USER, lp);
        SetDlgItemInt(hwnd, IDC_TALKS, self->saved_.talks, FALSE);
        SetDlgItemInt(hwnd, IDC_MUSIC, self->saved_.music, FALSE);
        SetDlgItemInt(hwnd, IDC_SWEARING, self->saved_.swearing, FALSE);
        return TRUE;
    }
    if (!self)
        return FALSE;
    if (msg == WM_COMMAND && LOWORD(wp) == IDOK) {
        if (self->controller_.submit({self->readField(IDC_TALKS),
            self->readField(IDC_MUSIC), self->readField(IDC_SWEARING)}))
            EndDialog(hwnd, IDOK);
        return TRUE;
    }
    if ((msg == WM_COMMAND && LOWORD(wp) == IDCANCEL) || msg == WM_CLOSE) {
        EndDialog(hwnd, IDCANCEL);
        return TRUE;
    }
    return FALSE;
}
