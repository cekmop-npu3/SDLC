#include "LifeController.hpp"

#include <stdexcept>

LifeController::LifeController(LifeModel& model, LifeView& view)
    : model_(model), view_(view) {}

void LifeController::enterData() {
    view_.openInput(model_.state().data);
}

int LifeController::parseCount(const std::wstring& text) {
    if (text.empty())
        throw std::invalid_argument("Empty input");

    int value = 0;
    for (wchar_t c : text) {
        if (c < L'0' || c > L'9')
            throw std::invalid_argument("Expected digits");
        const int digit = c - L'0';
        if (value > (LifeModel::MaxCount - digit) / 10)
            throw std::invalid_argument("Count too large");
        value = value * 10 + digit;
    }
    return value;
}

bool LifeController::submit(const std::array<std::wstring, 3>& text) {
    LifeData data;
    try {
        data = {parseCount(text[0]), parseCount(text[1]), parseCount(text[2])};
    } catch (const std::invalid_argument&) {
        view_.showError(L"Введите в каждое поле целое число от 0 до 10000. "
                        L"Пробелы, знаки и дроби недопустимы.");
        return false;
    }
    model_.setData(data);
    return true;
}
