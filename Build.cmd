@echo off
color 0a
mkdir Build
%MSBUILD% "Mafia Bar Engine.sln" /p:Configuration="Debug" /p:Platform="x64" /p:BuildProjectReferences=true
cd Build/Debug
"Mafia Bar Engine.exe"
pause