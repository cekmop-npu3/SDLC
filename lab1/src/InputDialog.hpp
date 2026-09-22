#pragma once

#include <windows.h>

#include "LifeController.hpp"

class InputDialog {
public:
    InputDialog(LifeController& controller, const LifeData& saved);
    void show(HWND owner);
    HWND handle() const;

private:
    static INT_PTR CALLBACK dialogProc(HWND, UINT, WPARAM, LPARAM);
    std::wstring readField(int id) const;
    LifeController& controller_;
    LifeData saved_;
    HWND window_ = nullptr;
};
