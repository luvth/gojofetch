# Gjfetch

gojofetch.cpp is a simple system fetch tool written in C++ that displays system information in the terminal with a Gojo Satoru ASCII art. It is inspired by `neofetch` but provides a lightweight alternative with a unique style.

## Features
- Displays system information such as:
  - Username and hostname
  - Operating system
  - Kernel version
  - System uptime
  - Installed packages count (Pacman & Flatpak)
  - Shell version
  - Window manager or desktop environment
  - Memory usage
- Minimal dependencies
- Colorful and formatted output

## Installation
### Manual Installation
```bash
# Clone the repository
git clone https://github.com/luvth/gojofetch.git
cd gojofetch.cpp

# Compile the program
g++ -o gjfetch gojofetch.cpp -std=c++17

# Move the binary to /bin for system-wide use
sudo mv gjfetch /bin/
```

## Usage
Simply run:
```bash
gjfetch
```
This will output system information with a Gojo Satoru ASCII art.

## Dependencies
- `g++` (for compilation)
- `glibc`
- `popen` for shell commands
- `sysinfo.h` for memory and uptime information

## License
This project is licensed under the MIT License.

## Author
Created by [luvth](https://github.com/luvth).

## Screenshots
Example output:
```
⠀⠀⠀⠀⠀⠀⠀⢀⠀⠔⡀⠀⢀⠞⢰⠂⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢸⠘⢰⡃⠔⠩⠤⠦⠤⢀⡀⠀⠀⠀⠀⠀
⠀⠀⠀⢀⠄⢒⠒⠺⠆⠈⠀⠀⢐⣂⠤⠄⡀⠯⠕⣒⣒⡀⠀
⠀⠀⢐⡡⠔⠁⠆⠀⠀⠀⠀⠀⢀⠠⠙⢆⠀⠈⢁⠋⠥⣀⣀            USER: raph@eos
⠈⠉⠀⣰⠀⠀⠀⠀⡀⠀⢰⣆⢠⠠⢡⡀⢂⣗⣖⢝⡎⠉⠀   ┌───────────────────────────────┐
⢠⡴⠛⡇⠀⠐⠀⡄⣡⢇⠸⢸⢸⡇⠂⡝⠌⢷⢫⢮⡜⡀⠀     OS: EndeavourOS Linux x86_64
⠀⠀⢰⣜⠘⡀⢡⠰⠳⣎⢂⣟⡎⠘⣬⡕⣈⣼⠢⠹⡟⠇⠀    ​ Host: Nitro AN515-58 V2.16
⠀⠠⢋⢿⢳⢼⣄⣆⣦⣱⣿⣿⣿⣷⠬⣿⣿⣿⣿⠑⠵⠀⠀    ​ Kernel: 6.13.4-arch1-1
⠀⠀⠀⡜⢩⣯⢝⡀⠁⠀⠙⠛⠛⠃⠀⠈⠛⠛⡿⠀⠀⠀⠀    ​ Uptime: 2 mins
⠀⠀⠀⠀⠀⣿⠢⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀    ​ Packages: 1450 (pacman), 7 (flatpak)
⠀⠀⠀⠀⢀⣀⡇⠀⠑⠀⠀⠀⠀⠐⢄⠄⢀⡼⠃⠀⠀⠀⠀    ​ Shell: zsh 5.9
⠀⠀⠀⠀⢸⣿⣷⣤⣀⠈⠲⡤⣀⣀⠀⡰⠋⠀⠀⠀⠀⠀⠀    ​ WM: bspwm
⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣶⣤⣙⣷⣅⡀⠀⠀⠀⠀⠀⠀⠀    ​ Memory: 1282MiB / 15678MiB
⠀⠀⢀⣾⣿⣿⣿⣿⣻⢿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀   └───────────────────────────────┘
⠀⡠⠟⠁⠙⠟⠛⠛⢿⣿⣾⣿⣿⣿⣿⣧⡀⠀⠀
```
