#include <windows.h>
#include <computenetwork.h>
#include <iostream>
using namespace std;

#pragma comment(lib, "computenetwork")

//reference：https://github.com/microsoft/WSL/discussions/7395
int main()
{
    cout << "Creating WSL Switch ..."<<endl;
    HRESULT hRes;
    HCN_NETWORK hcnNetwork;
    PWSTR errRecord;
    const GUID netId = {
        0xB95D0C5E,
        0x57D4,
        0x412B,
        {0xB5, 0x71, 0x18, 0xA8, 0x1A, 0x16, 0xE0, 0x05} };

    // Flags = EnableDnsProxy + IsolateVSwitch
    // Type = Static

    PCWSTR netSettings = LR"(
    {
        "Name" : "WSL",
        "Type" : "ICS",
        "IsolateSwitch" : true,
        "Flags" : 9,
        "Subnets": [
            {
                "AddressPrefix":"192.168.114.0/30"
            }
        ]
    })";
    hRes = HcnCreateNetwork(netId, netSettings, &hcnNetwork, &errRecord);
   
    cout << "========================================" << endl;
    cout <<"0x"<<hex<< hRes << endl;
    if (hRes == 0x00000000) {
        cout << "WSL switch successfully created .\n\n" << endl;
        system("wsl ip r");
    }
    if (hRes == 0x803b0010)
        cout << "Failed.WSL switch may have been created. Please reboot and try again.\n\n" << endl;
    if (hRes == 0x800706d9)
        cout << "Unsupported platform.\nRequired:Windows 10, version 1809+,or Windows Server 2019 with WSL2\n\n" << endl;
    if (hRes == 0x80070490|| hRes==0x8007273f||hRes== 0x803b001b)
        cout << "Bad SubNet.\n\n" << endl;
    HcnCloseNetwork(hcnNetwork);
    cout << "Help: https://github.com/kkkgo/WSL_Switch_Mod" << endl;
    system("timeout 10");

    return hRes;
}