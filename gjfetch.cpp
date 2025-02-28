#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <array>
#include <chrono>
#include <cstring>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        return "Erreur d'exécution de la commande";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    if (!result.empty() && result[result.length()-1] == '\n') {
        result.erase(result.length()-1);
    }
    return result;
}

string getHostname() {
    char hostname[1024];
    gethostname(hostname, 1024);
    return string(hostname);
}

string getUptime() {
    struct sysinfo s_info;
    if (sysinfo(&s_info) != 0) {
        return "Inconnu";
    }
    
    long uptime = s_info.uptime;
    int days = uptime / (60*60*24);
    int hours = (uptime % (60*60*24)) / (60*60);
    int mins = (uptime % (60*60)) / 60;
    
    string result;
    if (days > 0) {
        result += to_string(days) + " jours ";
    }
    if (hours > 0 || days > 0) {
        result += to_string(hours) + " heures ";
    }
    result += to_string(mins) + " mins";
    
    return result;
}

string getMemoryUsage() {
    struct sysinfo s_info;
    if (sysinfo(&s_info) != 0) {
        return "Inconnu";
    }
    
    long total_ram = s_info.totalram * s_info.mem_unit / (1024 * 1024);
    long free_ram = s_info.freeram * s_info.mem_unit / (1024 * 1024);
    long used_ram = total_ram - free_ram;
    
    return to_string(used_ram) + "MiB / " + to_string(total_ram) + "MiB";
}

int main() {
    struct utsname buffer;
    uname(&buffer);
    
    string username = getenv("USER") ? getenv("USER") : "unknown";
    string hostname = getHostname();
    string os = exec("grep PRETTY_NAME /etc/os-release | cut -d '=' -f 2 | tr -d '\"'");
    string kernel = string(buffer.release);
    string uptime = getUptime();
    string packages = exec("pacman -Q | wc -l") + " (pacman), " + 
                     exec("flatpak list | wc -l") + " (flatpak)";
    string shell = exec("echo $SHELL | xargs basename") + " " + exec("$SHELL --version | head -n 1 | awk '{print $2}'");
    string wm = exec("echo $XDG_CURRENT_DESKTOP 2>/dev/null || echo $DESKTOP_SESSION 2>/dev/null || echo unknown");
    string memory = getMemoryUsage();
    
    cout << WHITE;
    cout << "⠀⠀⠀⠀⠀⠀⠀⢀⠀⠔⡀⠀⢀⠞⢰⠂⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⠀⠀⠀⢸⠘⢰⡃⠔⠩⠤⠦⠤⢀⡀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⢀⠄⢒⠒⠺⠆⠈⠀⠀⢐⣂⠤⠄⡀⠯⠕⣒⣒⡀⠀" << endl;
    cout << "⠀⠀⢐⡡⠔⠁⠆⠀⠀⠀⠀⠀⢀⠠⠙⢆⠀⠈⢁⠋⠥⣀⣀            ";
    cout << YELLOW << BOLD << "USER: " << BLUE << username << RED << "@" << BLUE << hostname << RESET << endl;
    cout << WHITE;
    cout << "⠈⠉⠀⣰⠀⠀⠀⠀⡀⠀⢰⣆⢠⠠⢡⡀⢂⣗⣖⢝⡎⠉⠀   " << WHITE << "┌───────────────────────────────┐" << RESET << endl;
    cout << WHITE << "⢠⡴⠛⡇⠀⠐⠀⡄⣡⢇⠸⢸⢸⡇⠂⡝⠌⢷⢫⢮⡜⡀⠀     " << BLUE << BOLD << "OS: " << RESET << WHITE << os << " x86_64" << RESET << endl;
    cout << WHITE << "⠀⠀⢰⣜⠘⡀⢡⠰⠳⣎⢂⣟⡎⠘⣬⡕⣈⣼⠢⠹⡟⠇⠀    ​ " << BLUE << BOLD << "Host: " << RESET << WHITE << exec("cat /sys/devices/virtual/dmi/id/product_name 2>/dev/null || echo unknown") << " " << 
            exec("cat /sys/devices/virtual/dmi/id/product_version 2>/dev/null || echo unknown") << RESET << endl;
    cout << WHITE << "⠀⠠⢋⢿⢳⢼⣄⣆⣦⣱⣿⣿⣿⣷⠬⣿⣿⣿⣿⠑⠵⠀⠀    ​ " << BLUE << BOLD << "Kernel: " << RESET << WHITE << kernel << RESET << endl;
    cout << WHITE << "⠀⠀⠀⡜⢩⣯⢝⡀⠁⠀⠙⠛⠛⠃⠀⠈⠛⠛⡿⠀⠀⠀⠀    ​ " << BLUE << BOLD << "Uptime: " << RESET << WHITE << uptime << RESET << endl;
    cout << WHITE << "⠀⠀⠀⠀⠀⣿⠢⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀    ​ " << BLUE << BOLD << "Packages: " << RESET << WHITE << packages << RESET << endl;
    cout << WHITE << "⠀⠀⠀⠀⢀⣀⡇⠀⠑⠀⠀⠀⠀⠐⢄⠄⢀⡼⠃⠀⠀⠀⠀    ​ " << BLUE << BOLD << "Shell: " << RESET << WHITE << shell << RESET << endl;
    cout << WHITE << "⠀⠀⠀⠀⢸⣿⣷⣤⣀⠈⠲⡤⣀⣀⠀⡰⠋⠀⠀⠀⠀⠀⠀    ​ " << BLUE << BOLD << "WM: " << RESET << WHITE << wm << RESET << endl;
    cout << WHITE << "⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣶⣤⣙⣷⣅⡀⠀⠀⠀⠀⠀⠀⠀    ​ " << BLUE << BOLD << "Memory: " << RESET << WHITE << memory << RESET << endl;
    cout << WHITE << "⠀⠀⢀⣾⣿⣿⣿⣻⢿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀   " << WHITE << "└───────────────────────────────┘" << RESET << endl;
    cout << WHITE << "⠀⡠⠟⠁⠙⠟⠛⠛⢿⣿⣾⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀" << RESET << endl;
    cout << endl;
    
    return 0;
}
