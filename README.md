# LifeVolume — калькулятор громкости жизни

**Автор:** И.М. Серков

**Дисциплина:** «Жизненный цикл разработки программного обеспечения»

**Вариант:** 30

## О проекте

LifeVolume — учебное приложение на C++17 для расчёта условного уровня шума жизни. Пользователь вводит количество разговоров, прослушиваний музыки и случаев ругани за день. Программа выводит рассчитанный индекс и рекомендацию: «беруши» при индексе от 50, иначе — «караоке».

Расчёт выполняется по формуле:

```text
S = R + 2M + 3F
```

где `R` — разговоры, `M` — прослушивания музыки, `F` — случаи ругани.

## Лабораторная работа № 1

Реализация первой лабораторной работы находится в ветке `lab1`, в каталоге `lab1/`.

Проект реализован с использованием MVC и активной модели:

- `LifeModel` хранит состояние, проверяет значения и рассчитывает индекс;
- `LifeController` разбирает и проверяет пользовательский ввод;
- `MainView` и `InputDialog` реализуют интерфейс WinAPI;
- `LinuxView` реализует графический интерфейс Linux на GTK4;
- модель и контроллер не зависят от операционной системы.

### Структура `lab1/`

```text
lab1/
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

### Сборка и тестирование в Linux

Требуются CMake 3.20+, компилятор C++17, Make, `pkg-config` и пакет разработки GTK4.

```bash
cd lab1
cmake --preset build
cmake --build --preset build
ctest --preset build
```

Для отладочной версии:

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

Linux presets `build` и `debug` используют Unix Makefiles и создают `compile_commands.json`. Для Windows предусмотрены Ninja-presets `windows-build` и `windows-debug`.
