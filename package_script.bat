dir
dir build 
dir build/release
dir release
mkdir cenniki 
cd cenniki
cp ../build/Release/cenniki.exe ./
REM cp ../build/Logger/Release/logger.dll ./bin/
REM cp ../build/MainWindow/*.qm ./bin/
cp ../LICENSE ./
cp ../README.md ./
cp "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\redist\x86\Microsoft.VC140.CRT\concrt140.dll" ./
cp "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\redist\x86\Microsoft.VC140.CRT\msvcp140.dll" ./
cp "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\redist\x86\Microsoft.VC140.CRT\vccorlib140.dll" ./
cp "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\redist\x86\Microsoft.VC140.CRT\vcrunetime140.dll" ./
cp C:\Qt/5.7/msvc2015/bin/Qt5Core.dll ./
cp C:\Qt/5.7/msvc2015/bin/Qt5Gui.dll ./
cp C:\Qt/5.7/msvc2015/bin/Qt5Widgets.dll ./
cp C:\Qt/5.7/msvc2015/bin/Qt5Quick.dll ./
mkdir platforms
cp C:\Qt/5.7/msvc2015/plugins/platforms/qwindows.dll ./platforms/
cd ..
7z a cenniki.7z cenniki
