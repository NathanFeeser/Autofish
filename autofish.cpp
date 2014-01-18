#include "autofish.h"
#include "ui_autofish.h"

AutoFish::AutoFish(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AutoFish)
{
    ui->setupUi(this);
}

AutoFish::~AutoFish()
{
    delete ui;
}

void AutoFish::on_quitButton_clicked()
{
    qApp->quit();
}

//Function to set the text in the status bar.
void AutoFish::updatelabel(QString str)
{
    ui->statusLabel->setText(str);

    qApp->processEvents();
}

void AutoFish::on_startButton_clicked()
{
    //The handle for the window.
    HWND window = getWindow("FINAL FANTASY XIV: A Realm Reborn");
    if (window)
    {
        //Set label
        updatelabel("Fishing!!");

        //Setup the static pointer and offsets:
        address = 0x1EB25D4;
        offset1 = 0x54;
        offset2 = 0xFC;
        memValue = 0;

        //Set the initial state
        state = AutoFish::Casting;
        //Start fishing.
        goneFishing(window);
    }
}

//Returns the window handle of the given process.
HWND AutoFish::getWindow(LPCSTR processName) {
    HWND hwnd = FindWindowA(0, processName);
    if(!hwnd) {
        std::cout << "Error: Cannot find window!" << std::endl;
        updatelabel("Error: Cannot find window.");
    }
    else {
        //Store the pid in our pid variable address
        GetWindowThreadProcessId(hwnd,&pid);
        std::cout << "Success! Window found!" << std::endl;
        updatelabel("Success! Window Found!");
    }
    return hwnd;
}

//Function called when it is time to start fishing:
void AutoFish::goneFishing(HWND window) {

    //Get permission to read the process
    phandle = OpenProcess(PROCESS_VM_READ,0,pid);
    if (!phandle)
    {
        updatelabel("Error, unable to open process for reading.");
    }

    //Setup the input keys:
    INPUT ip;

    while (running && phandle)
    {
        switch (state)
        {
            case AutoFish::Casting:
            {
                // Bring specified window into focus
                SetForegroundWindow(window);
                // Set up a generic keyboard event.
                ip.type = INPUT_KEYBOARD;
                ip.ki.wScan = 0; // hardware scan code for key
                ip.ki.time = 0;
                ip.ki.dwExtraInfo = 0;
                //List of virtual key codes: http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx
                ip.ki.wVk = 0x32; // virtual-key code for the "2" key
                //Press the cast key
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));

                // Release the cast key
                ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
                SendInput(1, &ip, sizeof(INPUT));

                //if a fish has bitten...
                if (gotBite())
                {

                }

                //Make the state waiting for bite
                state = AutoFish::WaitingForBite;
                break;
            }
            case AutoFish::WaitingForBite:
            {

                //Make the state Hooked
                state = AutoFish::Hooked;
                break;
            }
            case AutoFish::Hooked:
            {

                //Make the state Casting again to recast our line
                state = AutoFish::Casting;
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

//Function to call to check if there is a bite
bool AutoFish::gotBite()
{
    ReadProcessMemory(phandle,(LPCVOID)address,&memValue,sizeof(memValue),NULL);
    memValue += offset1;
    ReadProcessMemory(phandle,(LPCVOID)memValue,&memValue,sizeof(memValue),NULL);
    memValue += offset2;
    ReadProcessMemory(phandle,(LPCVOID)memValue,&memValue,sizeof(memValue),NULL);
    std::cout << "Memory Value: " << memValue;
    Sleep(1000);
    return memValue == 5;
}
