package PomodoroAnalyticsUI {
    doc /* SysML v2 prototype: окно аналитики WinAPI. */

    part def AnalyticsWindow {
        attribute title : String = "Pomodoro — Аналитика";
        attribute period : String = "Неделя: 19–25 октября";
    }

    part def SummaryCards {
        attribute completed : String = "18 помодоро";
        attribute focusTime : String = "7 ч 30 мин";
        attribute goalProgress : String = "90 % от цели";
    }

    part def ProductivityChart {
        attribute kind : String = "Столбчатый график по дням";
        attribute values : String = "Пн 3, Вт 4, Ср 2, Чт 5, Пт 4";
    }

    part def TaskStatistics {
        attribute columns : String = "Задача, Помодоро, Время";
        attribute topTask : String = "Подготовить SRS — 5 — 2 ч 05 мин";
    }

    part analyticsWindow : AnalyticsWindow;
    part summary : SummaryCards;
    part chart : ProductivityChart;
    part taskTable : TaskStatistics;

    connection summaryToChart connect summary to chart;
    connection chartToTaskTable connect chart to taskTable;
}
