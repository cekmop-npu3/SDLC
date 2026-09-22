#pragma once

#include "LifeModel.hpp"

#include <array>
#include <string>

class LifeView {
public:
    virtual ~LifeView() = default;
    virtual void openInput(const LifeData& saved) = 0;
    virtual void showError(const std::wstring& message) = 0;
};

class LifeController {
public:
    LifeController(LifeModel& model, LifeView& view);
    void enterData();
    bool submit(const std::array<std::wstring, 3>& text);

private:
    static int parseCount(const std::wstring& text);
    LifeModel& model_;
    LifeView& view_;
};
