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
mkdir platforms
cp C:\Qt/5.7/msvc2013/plugins/platforms/qwindows.dll ./platforms/
cd ..
7z a cenniki.7z cenniki
