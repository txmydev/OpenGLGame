Write-Output "Going to directory /src/"
Set-Location ..
Set-Location ..
Set-Location src/
Write-Output "Compiling the program..."

$include_options='-I../include/'
$linker_paths='-L../lib/'
$output='../bin/app'
$files = 'main.c keyboard.c'

gcc -g -o $output $include_options $linker_paths $files -lglfw3 -lopengl32 -luser32 -lkernel32 -lgdi32

$prompt=Read-Host 'Run the program (Y/N)'
Clear-Host

if ($prompt -ne "Y" -or $prompt -ne "y") {
    exit
}

Write-Output "Running the program.."
Set-Location ../bin/
./app.exe