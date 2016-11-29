mkdir cenniki 
cd cenniki
cp ../release/cenniki.exe ./
REM cp ../build/Logger/Release/logger.dll ./bin/
REM cp ../build/MainWindow/*.qm ./bin/
cp ../LICENSE ./
cp ../README.md ./
cp "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\msvcp120.dll" ./
cp "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\msvcr120.dll" ./
cp C:\Qt/5.7/msvc2013/bin/Qt5Core.dll ./
cp C:\Qt/5.7/msvc2013/bin/Qt5Gui.dll ./
cp C:\Qt/5.7/msvc2013/bin/Qt5Widgets.dll ./
cp C:\Qt/5.7/msvc2013/bin/Qt5Quick.dll ./
cp C:\Qt/5.7/msvc2013/bin/Qt5Qml.dll ./
cp C:\Qt/5.7/msvc2013/bin/Qt5Network.dll ./
cp C:\Qt/5.7/msvc2013/bin/Qt5QuickTemplates2.dll ./
cp C:\Qt/5.7/msvc2013/bin/Qt5QuickControls2.dll ./
mkdir platforms
cp C:\Qt/5.7/msvc2013/plugins/platforms/qwindows.dll ./platforms/
mkdir QtQuick
robocopy C:\Qt/5.7/msvc2013/qml/QtQuick ./QtQuick /s /e 
mkdir QtQuick.2
robocopy C:\Qt/5.7/msvc2013/qml/QtQuick.2 ./QtQuick.2 /s /e 
cd ..
7z a cenniki.7z cenniki
