package PomodoroTimer {
    doc /*
      Pomodoro-таймер с аналитикой
      Модель требований и трассируемости для ЛР №3.
      Целевой GUI: настольное приложение C++/WinAPI.
    */

    requirement def BusinessGoal {
        doc /* Повысить концентрацию пользователя и дать ему измеримые данные о продуктивности. */
    }

    requirement def FunctionalRequirement {
        doc /* Наблюдаемая функция приложения. */
    }

    requirement def QualityRequirement {
        doc /* Ограничение качества или реализации. */
    }

    requirement goalFocus : BusinessGoal {
        doc /* Пользователь должен планировать и выполнять фокус-сессии по технике Pomodoro. */
    }

    requirement goalInsights : BusinessGoal {
        doc /* Пользователь должен видеть статистику своей продуктивности по дням и задачам. */
    }

    requirement timerControl : FunctionalRequirement {
        doc /* Запуск, пауза, возобновление и сброс рабочего/перерывного таймера. */
    }

    requirement cycleManagement : FunctionalRequirement {
        doc /* Автоматическое чередование работы, короткого и длинного перерыва. */
    }

    requirement taskIntegration : FunctionalRequirement {
        doc /* Создание задач, выбор активной задачи и учёт помодоро в её прогрессе. */
    }

    requirement analytics : FunctionalRequirement {
        doc /* Отображение дневной, недельной и задачной статистики завершённых сессий. */
    }

    requirement notifications : FunctionalRequirement {
        doc /* Вывод системного уведомления и звукового сигнала при смене фазы. */
    }

    requirement localStorage : QualityRequirement {
        doc /* Все данные сохраняются локально в JSON без передачи третьим лицам. */
    }

    requirement winApiGui : QualityRequirement {
        doc /* Интерфейс реализуется как нативное desktop-приложение на C++ и WinAPI. */
    }

    satisfy goalFocus by timerControl;
    satisfy goalFocus by cycleManagement;
    satisfy goalFocus by taskIntegration;
    satisfy goalInsights by analytics;
    satisfy analytics by localStorage;
    satisfy timerControl by winApiGui;
}
