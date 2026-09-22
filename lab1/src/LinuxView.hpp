#pragma once

#include <gtk/gtk.h>

#include <string>

#include "LifeController.hpp"

class LinuxView final : public LifeView, public ModelObserver {
public:
    explicit LinuxView(LifeModel& model);
    ~LinuxView() override;

    int run(int argc, char* argv[]);
    void openInput(const LifeData& saved) override;
    void showError(const std::wstring& message) override;
    void onModelChanged(const LifeState& state) override;

private:
    static void activate(GtkApplication* app, gpointer userData);
    static void enterData(GtkButton*, gpointer userData);
    static void inputResponse(GtkDialog* dialog, int response, gpointer userData);
    void createWindow(GtkApplication* app);
    static std::string toUtf8(const std::wstring& text);

    LifeModel& model_;
    LifeController controller_;
    LifeState displayed_;
    GtkApplication* application_ = nullptr;
    GtkWindow* window_ = nullptr;
    GtkLabel* result_ = nullptr;
};
