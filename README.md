# Lab 2 — шаблон для лабораторной работы

## Назначение

Этот шаблон предназначен для начала второй лабораторной работы по дисциплине «Жизненный цикл разработки программного обеспечения».

Каталог `lab2/` содержит базовую структуру C++-проекта и CMake presets. В него добавляются исходный код, заголовочные файлы, тесты и основной `CMakeLists.txt` разрабатываемого приложения.

## Структура шаблона

```text
lab2/
├── CMakePresets.json
├── src/       # исходные файлы
├── include/   # заголовочные файлы
└── tests/     # автоматические тесты
```

Пустые каталоги сохранены в Git с помощью файлов `.gitkeep`.

## CMake presets

`lab2/CMakePresets.json` содержит общий скрытый preset `Common` и presets для двух платформ:

- Linux: `build` и `debug` с генератором Unix Makefiles;
- Windows: `windows-build` и `windows-debug` с генератором Ninja.

Во всех presets включены создание `compile_commands.json` и тесты через `BUILD_TESTING=ON`.

После добавления `CMakeLists.txt` проект можно будет собрать в Linux командами:

```bash
cd lab2
cmake --preset build
cmake --build --preset build
ctest --test-dir build/build --output-on-failure
```
