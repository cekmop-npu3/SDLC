#include "LifeController.hpp"

#include <iostream>
#include <stdexcept>

void check(bool condition) {
    if (!condition)
        throw std::runtime_error("Test failed");
}

struct Observer : ModelObserver {
    int notifications = 0;
    LifeState last;

    void onModelChanged(const LifeState& state) override {
        ++notifications;
        last = state;
    }
};

struct View : LifeView {
    int errors = 0;
    LifeData restored;

    void openInput(const LifeData& data) override {
        restored = data;
    }
    void showError(const std::wstring&) override {
        ++errors;
    }
};

int main() {
    LifeModel model;
    Observer observer;
    View view;
    LifeController controller(model, view);
    model.setObserver(&observer);

    check(!model.state().hasData);
    check(controller.submit({L"0", L"0", L"0"}));
    check(model.state().score == 0 && !model.state().earplugs);
    check(controller.submit({L"10", L"5", L"2"}));
    check(model.state().score == 26 && !model.state().earplugs);
    check(controller.submit({L"49", L"0", L"0"}));
    check(!model.state().earplugs);
    check(controller.submit({L"20", L"9", L"4"}));
    check(model.state().score == 50 && model.state().earplugs);

    controller.enterData();
    check(view.restored.talks == 20 && view.restored.music == 9
          && view.restored.swearing == 4);
    const int events = observer.notifications;
    for (const auto* bad : {L"", L"-1", L"1.5", L"abc", L" 2", L"2 ",
                            L"+2", L"10001", L"999999999999999999999"}) {
        for (int field = 0; field < 3; ++field) {
            std::array<std::wstring, 3> input{L"1", L"2", L"3"};
            input[field] = bad;
            check(!controller.submit(input));
            check(model.state().score == 50);
            check(observer.notifications == events);
        }
    }
    check(view.errors == 27);

    controller.enterData();
    check(view.restored.talks == 20 && view.restored.music == 9);
    for (LifeData bad : {LifeData{-1, 0, 0}, LifeData{0, 10001, 0},
                         LifeData{0, 0, -1}}) {
        bool rejected = false;
        try {
            model.setData(bad);
        } catch (const std::invalid_argument&) {
            rejected = true;
        }
        check(rejected && model.state().score == 50);
    }

    check(controller.submit({L"10000", L"10000", L"10000"}));
    check(model.state().score == 60000 && model.state().earplugs);
    check(observer.last.score == 60000);
    model.setObserver(nullptr);
    model.setData({1, 1, 1});
    check(observer.notifications == events + 1);
    std::cout << "All model/controller checks passed\n";
}
