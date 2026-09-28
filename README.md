# Lab 1 — калькулятор громкости жизни

**Автор:** И.М. Серков

**Дисциплина:** «Жизненный цикл разработки программного обеспечения»

**Вариант:** 30

## О приложении

LifeVolume — приложение на C++17, которое рассчитывает условный уровень шума жизни. Пользователь вводит количество разговоров, прослушиваний музыки и случаев ругани за день. Результатом являются индекс шума и рекомендация.

Расчёт выполняется по формуле:

```text
S = R + 2M + 3F
```

где `R` — разговоры, `M` — прослушивания музыки, `F` — случаи ругани. При `S >= 50` рекомендация — «беруши», иначе — «караоке».

## Архитектура

Проект построен по MVC с активной моделью:

- `LifeModel` хранит состояние, проверяет данные и рассчитывает индекс;
- `LifeController` проверяет текстовый ввод и передаёт корректные данные модели;
- `MainView` и `InputDialog` реализуют интерфейс WinAPI;
- `LinuxView` реализует интерфейс Linux на GTK4;
- `ModelObserver` позволяет модели уведомлять представление об изменении состояния.

Модель и контроллер не зависят от операционной системы.

## Структура

```text
lab1/
├── Отчёт_ЛР1_В30.pdf
├── CMakeLists.txt
├── CMakePresets.json
├── src/
│   ├── LifeModel.*
│   ├── LifeController.*
│   ├── MainView.*          # WinAPI
│   ├── InputDialog.*       # WinAPI
│   ├── LinuxView.*         # GTK4
│   └── main.cpp
└── tests/core_tests.cpp
```

## Сборка и тестирование

Для Linux требуются CMake 3.20+, компилятор с поддержкой C++17, Make, `pkg-config` и пакет разработки GTK4.

```bash
cd lab1
cmake --preset build
cmake --build --preset build
ctest --preset build
```

Отладочная сборка:

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

Linux presets `build` и `debug` используют Unix Makefiles. Windows presets `windows-build` и `windows-debug` используют Ninja. Во всех presets включены тесты и создание `compile_commands.json`.
