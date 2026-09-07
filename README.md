# Арканоид

## Управление

- Стрелки влево/вправо — двигать каретку
- Пробел — запустить мяч / отлепить мяч от каретки
- Escape — выйти

## Как собрать и запустить

### Windows

1. Установить [MSYS2](https://www.msys2.org/)

2. Открыть **MSYS2 UCRT64** из меню Пуск и выполнить:
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-sfml

3. Открыть папку проекта в VS Code и нажать `Ctrl+Shift+B`

4. Запустить в терминале:
./arkanoid.exe

## Использованные библиотеки

- [SFML 2.6](https://www.sfml-dev.org/download.php) — графика, окно, ввод
- [MSYS2](https://www.msys2.org/) — компилятор и пакетный менеджер для Windows
