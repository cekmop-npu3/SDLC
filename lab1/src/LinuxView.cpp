#include "LinuxView.hpp"

#include <codecvt>
#include <locale>

LinuxView::LinuxView(LifeModel& model)
    : model_(model), controller_(model, *this) {
    model_.setObserver(this);
}

LinuxView::~LinuxView() {
    model_.setObserver(nullptr);
}

int LinuxView::run(int argc, char* argv[]) {
    application_ = gtk_application_new("by.bsuire.lifevolume", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(application_, "activate", G_CALLBACK(activate), this);
    const int status = g_application_run(G_APPLICATION(application_), argc, argv);
    g_object_unref(application_);
    application_ = nullptr;
    return status;
}

void LinuxView::activate(GtkApplication* app, gpointer userData) {
    static_cast<LinuxView*>(userData)->createWindow(app);
}

void LinuxView::createWindow(GtkApplication* app) {
    window_ = GTK_WINDOW(gtk_application_window_new(app));
    gtk_window_set_title(window_, "Калькулятор громкости жизни");
    gtk_window_set_default_size(window_, 560, 340);

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 18);
    gtk_widget_set_margin_start(box, 24);
    gtk_widget_set_margin_end(box, 24);
    gtk_widget_set_margin_top(box, 24);
    gtk_widget_set_margin_bottom(box, 24);
    gtk_window_set_child(window_, box);

    result_ = GTK_LABEL(gtk_label_new("Данные не введены"));
    gtk_label_set_xalign(result_, 0.0F);
    gtk_label_set_wrap(result_, TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(result_), TRUE);
    gtk_box_append(GTK_BOX(box), GTK_WIDGET(result_));

    GtkWidget* button = gtk_button_new_with_label("Ввести данные");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    g_signal_connect(button, "clicked", G_CALLBACK(enterData), this);
    gtk_box_append(GTK_BOX(box), button);

    gtk_window_present(window_);
}

void LinuxView::enterData(GtkButton*, gpointer userData) {
    static_cast<LinuxView*>(userData)->controller_.enterData();
}

void LinuxView::openInput(const LifeData& saved) {
    auto* dialog = GTK_DIALOG(gtk_dialog_new());
    gtk_window_set_title(GTK_WINDOW(dialog), "Ввод данных");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), window_);
    gtk_dialog_add_button(dialog, "Отмена", GTK_RESPONSE_CANCEL);
    gtk_dialog_add_button(dialog, "Рассчитать", GTK_RESPONSE_OK);

    GtkWidget* content = gtk_dialog_get_content_area(dialog);
    GtkWidget* grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 12);
    gtk_widget_set_margin_start(grid, 18);
    gtk_widget_set_margin_end(grid, 18);
    gtk_widget_set_margin_top(grid, 18);
    gtk_widget_set_margin_bottom(grid, 18);
    gtk_box_append(GTK_BOX(content), grid);

    const char* labels[] = {"Разговоры:", "Прослушивания музыки:", "Ругань:"};
    const int values[] = {saved.talks, saved.music, saved.swearing};
    GtkWidget* entries[3];
    for (int i = 0; i < 3; ++i) {
        GtkWidget* label = gtk_label_new(labels[i]);
        gtk_label_set_xalign(GTK_LABEL(label), 0.0F);
        entries[i] = gtk_entry_new();
        gtk_entry_set_input_purpose(GTK_ENTRY(entries[i]), GTK_INPUT_PURPOSE_DIGITS);
        gtk_editable_set_text(GTK_EDITABLE(entries[i]), std::to_string(values[i]).c_str());
        gtk_grid_attach(GTK_GRID(grid), label, 0, i, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), entries[i], 1, i, 1, 1);
        g_object_set_data(G_OBJECT(dialog), (std::string("entry") + std::to_string(i)).c_str(), entries[i]);
    }

    g_signal_connect(dialog, "response", G_CALLBACK(inputResponse), this);
    gtk_window_present(GTK_WINDOW(dialog));
}

void LinuxView::inputResponse(GtkDialog* dialog, int response, gpointer userData) {
    auto* self = static_cast<LinuxView*>(userData);
    if (response == GTK_RESPONSE_OK) {
        std::array<std::wstring, 3> text;
        for (int i = 0; i < 3; ++i) {
            auto* entry = GTK_ENTRY(g_object_get_data(
                G_OBJECT(dialog), (std::string("entry") + std::to_string(i)).c_str()));
            const char* value = gtk_editable_get_text(GTK_EDITABLE(entry));
            text[i] = std::wstring(value, value + std::char_traits<char>::length(value));
        }
        if (!self->controller_.submit(text))
            return;
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}

std::string LinuxView::toUtf8(const std::wstring& text) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(text);
}

void LinuxView::showError(const std::wstring& message) {
    auto* dialog = GTK_MESSAGE_DIALOG(gtk_message_dialog_new(window_, GTK_DIALOG_MODAL,
        GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", toUtf8(message).c_str()));
    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_window_destroy), dialog);
    gtk_window_present(GTK_WINDOW(dialog));
}

void LinuxView::onModelChanged(const LifeState& state) {
    displayed_ = state;
    const auto& data = displayed_.data;
    const std::wstring text = L"Разговоры: " + std::to_wstring(data.talks)
        + L" раз/день\nМузыка: " + std::to_wstring(data.music)
        + L" раз/день\nРугань: " + std::to_wstring(data.swearing)
        + L" раз/день\n\nУровень шума жизни: " + std::to_wstring(displayed_.score)
        + L" усл. ед.\nРекомендация: "
        + (displayed_.earplugs ? L"беруши" : L"караоке");
    gtk_label_set_text(result_, toUtf8(text).c_str());
}
