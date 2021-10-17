#define _CRT_SECURE_NO_WARNINGS
#include <bangtal>
#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace bangtal;
using namespace std;


ScenePtr scene0, scene, intro_scene, scene2;
ObjectPtr food_button[8], ok, next1, text1, text2, beforegame, title, forreset, kaonashi[2], black_back, think, start, black_bar;

ObjectPtr  q_ingredient[8];

SoundPtr BGM;




int food_x = 180, food_y = 20;

int questY[8] = { 340, 370, 400, 430, 460, 490, 520, 550 };
int answerY[8] = { 200, 250, 300, 350, 400, 450, 500, 550 };


enum
{
    F0 = 77, F1 = 78, F2 = 79, F3 = 80, F4 = 81, F5 = 82, F6 = 83, F7 = 84
};





void bgm_start()
{
    BGM = Sound::create("sounds/one_summer_day.mp3");
    BGM->play();
}





void show_clock()       //현재 게임 진행 시간 보여주는 타이머 clock. 시간이 지나면  Fail 메시지 출력
{
    
    auto clock = Timer::create(15.f);
    showTimer(clock);

    start->show();
    clock->start();

    clock->setOnTimerCallback([&](TimerPtr clock)->bool {
        showMessage("FAIL");
        
        start->show();      //게임이 fail되면 다시 시작하는 버튼

        return true;
    });
}







// 게임 배경 & 음식 버튼 생성
void making_image()
{
    kaonashi[1] = Object::create("images-3/kaonashi.png", scene2, 170, 0);

    black_bar = Object::create("images-3/black_bar.png", scene2, -10, -10);
    

    char path[20];
    int count = 0;
    int food_x_pos = 150;


    for (int i = 0; i < 8;i++)                              // 음식 버튼 생성
    {
        sprintf(path, "images-3/f%d.png", i + 1);
        food_button[i] = Object::create(path, scene2, food_x, food_y);
        food_x += 120;


    }

    food_x -= (120 * 8);



}






void ans_ingredientCase(int question[]) {           // 문제 내는 랜덤 음식

    forreset = Object::create("images-3/forreset.png", scene2, 800, 0);
    auto bar = Object::create("images-3/f0.png", scene2, 970, 130);
    auto clockback = Object::create("images-3/clockback.png", scene2, 600, 600);

    think = Object::create("images-3/think.png", scene2, -15, 280);
    think->setScale(0.9f);

    for (int i = 0; i < 8; i++)
    {
        int n = 80;
        int num;
        num = rand() % 8;

        switch (num) {
        case 0:
            question[i] = F0;
            q_ingredient[i] = Object::create("images-3/f1.png", scene2, n, questY[i]);
            q_ingredient[i]->setScale(0.6f);
            break;
        case 1:
            question[i] = F1;
            q_ingredient[i] = Object::create("images-3/f2.png", scene2, n, questY[i]);
            q_ingredient[i]->setScale(0.6f);
            break;
        case 2:
            question[i] = F2;
            q_ingredient[i] = Object::create("images-3/f3.png", scene2, n, questY[i]);
            q_ingredient[i]->setScale(0.6f);
            break;
        case 3:
            question[i] = F3;
            q_ingredient[i] = Object::create("images-3/f4.png", scene2, n, questY[i]);
            q_ingredient[i]->setScale(0.6f);
            break;
        case 4:
            question[i] = F4;
            q_ingredient[i] = Object::create("images-3/f5.png", scene2, n, questY[i]);
            q_ingredient[i]->setScale(0.6f);
            break;
        case 5:
            question[i] = F5;
            q_ingredient[i] = Object::create("images-3/f6.png", scene2, n, questY[i]);
            q_ingredient[i]->setScale(0.6f);
            break;
        case 6:
            question[i] = F6;
            q_ingredient[i] = Object::create("images-3/f7.png", scene2, n, questY[i]);
            q_ingredient[i]->setScale(0.6f);
            break;
        case 7:
            question[i] = F7;
            q_ingredient[i] = Object::create("images-3/f8.png", scene2, n, questY[i]);
            q_ingredient[i]->setScale(0.6f);
            break;
        }
    }

}





void  my_ingredientCase(int& q_index, int& key_flag, int question[], ObjectPtr my_ingredient[], ScenePtr& scene2) {            // 내가 선택한 음식 꼬치에 꽂기

    switch (question[q_index])
    {
    case F0:
        my_ingredient[q_index] = Object::create("images-3/f1.png", scene2, 930, answerY[q_index]);
        my_ingredient[q_index]->setScale(1.2f);
        break;
    case F1:
        my_ingredient[q_index] = Object::create("images-3/f2.png", scene2, 930, answerY[q_index]);
        my_ingredient[q_index]->setScale(1.2f);
        break;
    case F2:
        my_ingredient[q_index] = Object::create("images-3/f3.png", scene2, 930, answerY[q_index]);
        my_ingredient[q_index]->setScale(1.2f);
        break;
    case F3:
        my_ingredient[q_index] = Object::create("images-3/f4.png", scene2, 930, answerY[q_index]);
        my_ingredient[q_index]->setScale(1.2f);
        break;
    case F4:
        my_ingredient[q_index] = Object::create("images-3/f5.png", scene2, 930, answerY[q_index]);
        my_ingredient[q_index]->setScale(1.2f);
    case F5:
        my_ingredient[q_index] = Object::create("images-3/f6.png", scene2, 930, answerY[q_index]);
        my_ingredient[q_index]->setScale(1.2f);
    case F6:
        my_ingredient[q_index] = Object::create("images-3/f7.png", scene2, 930, answerY[q_index]);
        my_ingredient[q_index]->setScale(1.2f);
    case F7:
        my_ingredient[q_index] = Object::create("images-3/f8.png", scene2, 930, answerY[q_index]);
        my_ingredient[q_index]->setScale(1.2f);
    }

    key_flag++;
    q_index++;


}












void clearArray(int key_press[], ObjectPtr q_ingredient[], ObjectPtr my_ingredient[], int& q_index, int& key_index, int& key_flag)
{
    for (int i = 0; i < 100; i++)
    {
        key_press[i] = 0;
    }
    for (int i = 0; i < 8; i++)
    {
        my_ingredient[i]->hide();
        my_ingredient[i] = nullptr;
    }
    for (int i = 0; i < 8; i++)
    {
        q_ingredient[i]->hide();
        q_ingredient[i] = nullptr;
    }
    q_index = 0;
    key_index = 0;
    key_flag = 0;

}







void intro()
{
    intro_scene->enter();
    kaonashi[0] = Object::create("images-3/kaonashi.png", intro_scene, 170, 0);

    text1 = Object::create("images-3/text1.png", intro_scene, 100, 100);
    next1 = Object::create("images-3/next.png", intro_scene, 1050, 100);
    next1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        text1->hide();
        next1->hide();

        text2 = Object::create("images-3/text5.png", intro_scene, 100, 100);
        ok = Object::create("images-3/ok.png", intro_scene, 1100, 100);
        ok->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            text2->hide();
            ok->hide();
            scene2->enter();
            kaonashi[0]->hide();

            show_clock();

            return true;
        });
        return true;
    });
}






void start_button()             //처음 게임 시작 버튼
{



    black_back = Object::create("images-3/black_back.png", scene, 0, 0);
    start = Object::create("images-3/start.png", scene, 550, 200);
    title = Object::create("images-3/title.png", scene, 300, 400);

    start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        start->hide();
        title->hide();
        black_back->hide();

        intro();

        return true;
    });



}




void before_game_start()
{
    beforegame = Object::create("images-3/beforegame.png", scene0, 0, 0);
    beforegame->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        beforegame->hide();

        scene->enter();
        start_button();

        return true;
    });

}





int main()
{
    srand((unsigned int)time(NULL));

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

    scene0 = Scene::create("", "images-3/beforegame.png");
    scene = Scene::create("one summer day", "images-3/background.png");
    intro_scene = Scene::create("", "images-3/background.png");
    scene2 = Scene::create("one summer day", "images-3/background.png");

    before_game_start();


    start_button();
    bgm_start();



    int key_press[100] = { 0 };
    int question[8] = { 0 };
    int key_index = 0;
    int q_index = 0;
    int key_flag = 0;
    ObjectPtr q_ingradient[8] = { 0 }, my_ingredient[8] = { 0 };

    making_image();
    ans_ingredientCase(question);





    scene2->setOnKeyboardCallback([&](ScenePtr scene2, KeyCode code, bool pressed)->bool {
        int key = 0;
        switch (code) {
        case KeyCode::KEY_1: key = F0; break;
        case KeyCode::KEY_2: key = F1; break;
        case KeyCode::KEY_3: key = F2; break;
        case KeyCode::KEY_4: key = F3; break;
        case KeyCode::KEY_5: key = F4; break;
        case KeyCode::KEY_6: key = F5; break;
        case KeyCode::KEY_7: key = F6; break;
        case KeyCode::KEY_8: key = F7; break;
        }
        key_press[key_index] = key;

        if (key_index % 2 == 0)
        {

            if (question[q_index] == key_press[key_index])
            {
                my_ingredientCase(q_index, key_flag, question, my_ingredient, scene2);

            }
            else if (question[q_index] != key_press[key_index] && question[q_index] != 0)
            {

                q_index = 0;
                key_index = 0;
                key_flag = 0;
                showMessage("FAIL");

                scene->enter();
                start->show();

            }
        }

        if (key_flag == 8)
        {
            showMessage("Completed!");
            clearArray(key_press, q_ingredient, my_ingredient, q_index, key_index, key_flag);

            scene->enter();
            start->show();
        }


        key_index++;
        return true;
    });





    startGame(scene0);
    return 0;
}