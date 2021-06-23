Приложение работает только на архитектуре x64 и oc windows, и компиляторе C++ не ниже 14
Проверялось на ос windows 10 и visual studio 2019, на более поздних версиях windows работа не гарантируется 
____
## Сброка спомошью cmake:

1. Клонируй репозиторий и создаем любую папку в нем
```powershell
    git clone https://github.com/europka0o/LittleWorld.git
    cd LittleWorld
    mkdir любое название папки
    cd Путь до только что созданной тобой папки
    cmake ..
    cmake -DCMAKE_GENERATOR_PLATFORM=x64 .
    cmake --build . --config release
```  
2. После этих команд в папке должен создаться и забилдиться проект
3. Открой папку, где был построен exe'шник, и закинь туда папки Sounds и Img, а так же 
следующие dll из папки SFML-2.5.1\bin :
    openal32.dll 
    sfml-audio-2.dll
    sfml-graphics-2.dll
    sfml-system-2.dll
    sfml-window-2.dll

____
Вуаля! Приложение собрано и готово к работе