#ifndef AUTOFISH_H
#define AUTOFISH_H

#pragma once

#include <QMainWindow>

#include <stdio.h>
#include <tchar.h>

#include <windows.h>
#include <iostream>

namespace Ui {
class AutoFish;
}

class AutoFish : public QMainWindow
{
    Q_OBJECT

public:
    explicit AutoFish(QWidget *parent = 0);
    ~AutoFish();
    void updatelabel(QString str);
    void delay();
    HWND getWindow(LPCSTR processName);
    HANDLE phandle;

    //Function to control the fishing states
    void AutoFish::goneFishing(HWND window);

    //The static pointer and offsets for fish bite detection:***********
    DWORD address;
    DWORD offset1;
    DWORD offset2;
    int memValue;
    DWORD pid;

    //Enum for the fishing states
    enum CurrentState {
        Casting,
        WaitingForBite,
        Hooked
    };
    AutoFish::CurrentState state;

    //Variable to start/stop the fishing
    bool running;

private slots:
    void on_quitButton_clicked();

    void on_startButton_clicked();

private:
    Ui::AutoFish *ui;
    bool gotBite();
};

#endif // AUTOFISH_H
