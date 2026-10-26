package PomodoroTimerUI {
    doc /* SysML v2 prototype: главное окно WinAPI. */

    part def MainWindow {
        attribute title : String = "Pomodoro — Фокус";
        attribute size : String = "960 × 640";
    }

    part def TimerPanel {
        attribute phase : String = "Фокус";
        attribute remaining : String = "25:00";
        attribute session : String = "Сессия 2 из 4";
    }

    part def ControlPanel {
        attribute primaryAction : String = "Начать";
        attribute secondaryActions : String = "Пауза, Сброс";
    }

    part def TaskPanel {
        attribute selectedTask : String = "Подготовить SRS";
        attribute action : String = "Выбрать задачу";
    }

    part def NavigationPanel {
        attribute pages : String = "Таймер, Задачи, Аналитика, Настройки";
    }

    part mainWindow : MainWindow;
    part navigation : NavigationPanel;
    part timer : TimerPanel;
    part controls : ControlPanel;
    part task : TaskPanel;

    connection navigationToTimer connect navigation to timer;
    connection timerToControls connect timer to controls;
    connection taskToTimer connect task to timer;
}
