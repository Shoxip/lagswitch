#include <windows.h> 
#include <string>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h>


int main()
{
    std::string rule_name = "LagSwitch";
    std::string executable_path = "";
    std::cout << "Enter game path folder: ";
    std::cin >> executable_path;
    int lag_key = VK_F2;
    int exit_key = VK_END;


    int lag_time = 3500;





    std::string cmd = "netsh advfirewall firewall delete rule name=\"" + rule_name + "\"";
    WinExec(cmd.c_str(), 0);

    while (!(GetAsyncKeyState(exit_key) & 0x8000)) { // loop until exit key is pressed
        if (GetAsyncKeyState(lag_key) & 0x8000) {
            Beep(800, 200);


            cmd = "netsh advfirewall firewall add rule name =\"" + rule_name + "\" dir=out action=block program=\"" + executable_path + "\"";
            WinExec(cmd.c_str(), 0);


            cmd = "netsh advfirewall firewall add rule name =\"" + rule_name + "\" dir=in action=block program=\"" + executable_path + "\"";
            WinExec(cmd.c_str(), 0);


            Sleep(lag_time);

            cmd = "netsh advfirewall firewall delete rule name=\"" + rule_name + "\"";
            WinExec(cmd.c_str(), 0);

            Beep(500, 200);
        }
        Sleep(5);
    }
    Beep(200, 200);

    return 0;
}
