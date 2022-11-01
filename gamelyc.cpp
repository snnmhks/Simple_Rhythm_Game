#include <iostream>
#include <vector>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

using namespace std;

void gotoxy(int x, int y) {
    COORD pos = { x,y }; // Windows 헤더에 내장된 구조체, 위치 변수만을 가진 구조체
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  // pos 방향으로 커서를 옮긴다.
}

void HideCursor() // 커서 숨기기, 정형화 되어 있으니 그냥 사용하면 됨
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void PushData(vector<string> *data, string object)
{
    for (int i = 0; i < data->size()-1; i++)
    {
        //data[i] = &data[i+1];
    }
    data->pop_back();
    data->push_back(object);
}

long WaitingTime = 0;
int length = 7;
long MaxWaitingTime = 50;
int level = 1;
int score = 0;
int life = 10;
int LevelUpSwitch = 0;

void TimePlus()
{
    while (1)
    {
        WaitingTime++;
        Sleep(33);
    }
}

void LevelUp()
{
    while(1)
    {
        if (score % 50 == 0 && LevelUpSwitch == 1)
        {
            level++;
            MaxWaitingTime = MaxWaitingTime * 9 / 10;
            LevelUpSwitch = 0;
        }
        if (score % 100 == 0 && LevelUpSwitch == 1)
        {
            length--;
            LevelUpSwitch = 0;
        }
        Sleep(33);
    }
}

int main()
{
    string object[4] = { "→","←","↑","↓" };
    vector<string> data;
 
    _beginthreadex(NULL, 0, (_beginthreadex_proc_type)TimePlus, NULL, 0, NULL);
    _beginthreadex(NULL, 0, (_beginthreadex_proc_type)LevelUp, NULL, 0, NULL);

    HideCursor();
    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        int RandomNum = rand() % 4;
        data.push_back(object[RandomNum]);
    }

    while (1)
    {
        system("cls");
        gotoxy(50, 18);
        cout << "LV " << level;
        gotoxy(50, 20);
        cout << "score : " << score;
        gotoxy(50, 22);
        cout << "life : ";
        for (int i = 0; i < life; i++)
        {
            cout << "♥";
        }
        
        gotoxy(50, 24);
        for (int i = 0; i < length; i++)
        {
            cout << data[i] << " ";
        }

        gotoxy(50, 26);
        cout << "Time : ";
        for (int i = 0; i < 10-(WaitingTime*10)/MaxWaitingTime; i++)
        {
            cout << "■";
        }

        if (GetAsyncKeyState(VK_UP) & 0x0001)
        {
            gotoxy(50, 28);
            if (data[0] == "↑")
            {
                cout << "Clear!";
                score++;
                LevelUpSwitch = 1;
            }
            else if (data[0] != "↑")
            {
                cout << "Fail!";
                life--;
            }
            int RandomNum = rand() % 4;
            for (int i = 0; i < data.size() - 1; i++)
            {
                data[i] = data[i + 1];
            }
            data.pop_back();
            data.push_back(object[RandomNum]);
            WaitingTime = 0;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x0001)
        {
            gotoxy(50, 28);
            if (data[0] == "↓")
            {
                cout << "Clear!";
                score++;
                LevelUpSwitch = 1;
            }
            else if (data[0] != "↓")
            {
                cout << "Fail!";
                life--;
            }
            int RandomNum = rand() % 4;
            for (int i = 0; i < data.size() - 1; i++)
            {
                data[i] = data[i + 1];
            }
            data.pop_back();
            data.push_back(object[RandomNum]);
            WaitingTime = 0;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x0001)
        {
            gotoxy(50, 28);
            if (data[0] == "←")
            {
                cout << "Clear!";
                score++;
                LevelUpSwitch = 1;
            }
            else if (data[0] != "←")
            {
                cout << "Fail!";
                life--;
            }
            int RandomNum = rand() % 4;
            for (int i = 0; i < data.size() - 1; i++)
            {
                data[i] = data[i + 1];
            }
            data.pop_back();
            data.push_back(object[RandomNum]);
            WaitingTime = 0;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
        {
            gotoxy(50, 28);
            if (data[0] == "→")
            {
                cout << "Clear!";
                score++;
                LevelUpSwitch = 1;
            }
            else if (data[0] != "→")
            {
                cout << "Fail!";
                life--;
            }
            int RandomNum = rand() % 4;
            for (int i = 0; i < data.size() - 1; i++)
            {
                data[i] = data[i + 1];
            }
            data.pop_back();
            data.push_back(object[RandomNum]);
            WaitingTime = 0;
        }
       
        if (WaitingTime >= MaxWaitingTime)
        {
            gotoxy(50, 28);
            cout << "Fail!";
            life--;
            WaitingTime = 0;
        }
        if (life <= 0)
        {
            system("cls");
            gotoxy(50, 25);
            cout << "GameOver...";
            gotoxy(50, 26);
            cout << "Your score is " << score;
            Sleep(3000);
            break;
        }
        Sleep(33);
    }      
}


