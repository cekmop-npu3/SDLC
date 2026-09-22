#pragma once

#include <windows.h>

#include "LifeController.hpp"

class InputDialog;

class MainView final : public LifeView, public ModelObserver {
public:
    explicit MainView(LifeModel& model);
    ~MainView() override;
    bool create(HINSTANCE instance, int showCommand);
    void openInput(const LifeData& saved) override;
    void showError(const std::wstring& message) override;
    void onModelChanged(const LifeState& state) override;

private:
    static LRESULT CALLBACK windowProc(HWND, UINT, WPARAM, LPARAM);
    void createControls();
    LifeModel& model_;
    LifeController controller_;
    LifeState displayed_;
    HWND window_ = nullptr;
    HWND result_ = nullptr;
    InputDialog* dialog_ = nullptr;
};
