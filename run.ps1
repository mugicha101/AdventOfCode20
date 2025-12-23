param([char]$part='A')
if (Test-Path -Path './a.exe') {
    Remove-Item ./a.exe
}
g++ -O3 -fpermissive ../main.cpp ../template.h ./code.cpp -o ./a.exe
if (Test-Path -Path './output.txt') {
    Remove-Item ./output.txt
}
if (Test-Path -Path './a.exe') {
    ./a.exe $part | Tee-Object ./output.txt
}