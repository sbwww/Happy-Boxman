// TuiTuiLe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <opencv2/opencv.hpp>
#include "Game.h"
#include "Timer.h" 
#include "RankList.h"

#define CVUI_IMPLEMENTATION
#include "cvui.h"
#define WINDOW_NAME "Box Man"
#define QUIT -1
extern cv::Mat frame = cv::Mat(400, 530, CV_8UC3);
void Archieve(RankList& rklst, int& archieve, Timer& timer, int score);


int main() {
    int left = 100, top = 80;
    int spacing = 40;

    cv::namedWindow(WINDOW_NAME);
    cvui::init(WINDOW_NAME);
    RankList rklst;

    // press ESC to exit
    while (cv::waitKey(30) != 27) {

        frame = cv::Scalar(49, 52, 49); 
        cvui::text(frame, left, top, "Welcome to Happy Boxman v0.0.2", 0.6);

        if (cvui::button(frame, left + spacing, top + spacing, 200, 40, "Classical game")){
            Timer timer;
            int end = 0, archieve = 0;
            std::cout << "Classical Game" << std::endl;
            int i = 0;
            while (cv::waitKey(30) != 27) {   
                for (i; !end && i <= 5; i++) {
                    Normal_Game game(i);
                    if (game.Play(timer) == QUIT) {
                        end = 1;
                        break;
                    }
                }
                if (i > 5) {
                    frame = cv::Scalar(49, 52, 49);
                    timer.show();
                    if (cvui::button(frame, 155, 200, 200, 40, "You Win!")) {  
                        Archieve(rklst, archieve, timer, 5);
                        while (cv::waitKey(30) != 13) {
                            frame = cv::Scalar(49, 52, 49);
                            rklst.Show();
                            cvui::update();
                            cv::imshow(WINDOW_NAME, frame);
                        }
                        break;
                    }
                    cvui::update();
                    cv::imshow(WINDOW_NAME, frame);
                }
                else {
                    while (cv::waitKey(30) != 27) {
                        frame = cv::Scalar(49, 52, 49);
                        timer.show();
                        if (cvui::button(frame, 155, 200, 200, 40, "Continue")) {
                            break;
                        }
                        cvui::update();
                        cv::imshow(WINDOW_NAME, frame);
                    }
                    if(!archieve) Archieve(rklst, archieve, timer, i-1);
                    // 按ENTER结束
                    while (cv::waitKey(30) != 13) {
                        frame = cv::Scalar(49, 52, 49);
                        rklst.Show();
                        cvui::update();
                        cv::imshow(WINDOW_NAME, frame);
                    }
                    break;
                }
                std::cout << "内循环" << std::endl;
            }            
            std::cout << "button" << std::endl;        
        }
        else if(cvui::button(frame, left + spacing, top + 2 * spacing, 200, 40, "Random game")) {
            Timer timer;
            int signal = 0;
            while (cv::waitKey(30) != 27) {
                if (signal == 0) {
                    Random_Game game(10, 15);
                    if(game.Play(timer) == QUIT) break;
                    signal++;
                }
                else {
                    frame = cv::Scalar(49, 52, 49);
                    timer.show();
                    cvui::text(frame, 170, 50, "You Win!", 1.2, 0xff0000);
                    if (cvui::button(frame, 150, 190, 200, 40, "Continue")) {
                        signal = 0;
                        continue;
                    }
                    if (cvui::button(frame, 150, 230, 200, 40, "Quit")) {
                        break;
                    }
                    
                }
                cvui::update();
                cv::imshow(WINDOW_NAME, frame);
            }
        }
        else if (cvui::button(frame, left + spacing, top + 3 * spacing, 200, 40, "Dual game")) {
            int end = 0;
            Timer timer1, timer2;
            Time p1_t, p2_t;
            while (cv::waitKey(30) != 27) {
                if (!end) {
                    int i = rand() % 5 + 1;
                    Normal_Game game_1(i);
                    if (game_1.Play(timer1) == QUIT) break;
                    p1_t = timer1.getTotTime();
                    Normal_Game game_2(i);
                    if (game_2.Play(timer2) == QUIT) break;
                    p2_t = timer2.getTotTime();
                    end = 1;
                }
                else {
                    frame = cv::Scalar(49, 52, 49);
                    cvui::printf(frame, 150, top, 0.5, 0xf8f8ff, "Player 1 Time: %02d:%02d:%02d", p1_t.getH(), p1_t.getM(), p1_t.getS());
                    cvui::printf(frame, 150, top + spacing, 0.5, 0xf8f8ff, "Player 2 Time: %02d:%02d:%02d", p2_t.getH(), p2_t.getM(), p2_t.getS());
                    if (p1_t == p2_t) {
                        cvui::text(frame, 230, top + 2 * spacing, "Tie", 0.8, 0xff0000);
                    }
                    else if (p1_t < p2_t) {
                        cvui::text(frame, 170, top + 2 * spacing, "Player1 wins!", 0.8, 0xff0000);
                    }
                    else {
                        cvui::text(frame, 170, top + 2 * spacing, "Player2 wins!", 0.8,0xff0000);
                    }
                    if (cvui::button(frame, 150, top + 3 * spacing, 200, 40, "Quit")) {
                        break;
                    }
                }
                // refresh
                cvui::update();
                // show
                cv::imshow(WINDOW_NAME, frame);
            }
        }
        else if (cvui::button(frame, left + spacing, top + 4 * spacing, 200, 40, "Rank List")) {
            while (cv::waitKey(30) != 13) {
                frame = cv::Scalar(49, 52, 49);
                rklst.Show();
                cvui::update();
                // show
                cv::imshow(WINDOW_NAME, frame);
            }
        }
        else if (cvui::button(frame, left + spacing, top + 5 * spacing, 200, 40, "Quit")) {
            break;
        }
        // refresh
        cvui::update();
        // show
        cv::imshow(WINDOW_NAME, frame);
        std::cout << "循环" << std::endl;
    }
    return 0;
}

void Archieve(RankList& rklst, int &archieve, Timer& timer, int score) {
    archieve = 1;
    std::string s;
    while (true) {
        frame = cv::Scalar(49, 52, 49);
        int ch = cv::waitKey(10);
        // ENTER == 13
        if (ch == 13)	break;
        // Backspace == 8
        if (ch == 8) {
            if (!s.empty()) {
                s.pop_back();
            }
        }
        // space(空格) == 32
        else if (isprint(ch) && ch != 32) {
            std::cout << ch << std::endl;
            s += ch;
        }
        std::cout << ch << std::endl;
        cvui::printf(frame, 10, 10, 0.8, 0xf8f8ff, "Please enter your username:");
        cvui::printf(frame, 10, 50, 0.8, 0xff0000, (s+"|").c_str());   
        cvui::update();
        cv::imshow(WINDOW_NAME, frame);
    }
    Rec rec(s, score, timer.getTotTime());
    rklst.Save(rec);
    return;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
