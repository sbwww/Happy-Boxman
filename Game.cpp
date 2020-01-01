#include "Game.h"
#define QUIT -1
Status Game::Push(int ch) {
    const int dx[] = {0, -1, 0, 1};
    const int dy[] = {-1, 0, 1, 0};
    if (ch == '0') {
        while (cv::waitKey(30) != 27) {
            frame = cv::Scalar(49, 52, 49);
            if (cvui::button(frame, 100, 100, 200, 40, "Quit?")) {
                return SURRENDER;
            }
            if (cvui::button(frame, 100, 150, 200, 40, "Continue?")) {
                return 0;
            }
            // refresh
            cvui::update();
            // show
            cv::imshow(WINDOW_NAME, frame);
        }
       
    }
    int px = this->player_pos.first, py = this->player_pos.second;
    int pxx, pyy, bxx, byy;
    int twist = -1;
    switch (ch) {
        // left OpenCV waitKeyEx方向键返回值
    case 'a':
    case 2424832: {
        twist = 0;
        pxx = px + dx[0], pyy = py + dy[0];
        break;
    }
        // up
    case 'w':
    case 2490368: {
        twist = 1;
        pxx = px + dx[1], pyy = py + dy[1];
        break;
    }
        // right
    case 'd':
    case 2555904: {
        twist = 2;
        pxx = px + dx[2], pyy = py + dy[2];
        break;
    }
        // down
    case 's':
    case 2621440: {
        twist = 3;
        pxx = px + dx[3], pyy = py + dy[3];
        break;
    }
        // recall
    case 'z': {
        if (stk.empty())
            return ERROR;
        state save_state = stk.top();
        stk.pop();
        char **save_map = save_state.save_map;
        for (int i = 0; i < map_height; ++i) {
            for (int j = 0; j < map_length; ++j) {
                map[i][j] = save_map[i][j];
            }
        }
        player_pos = save_state.player_pos;
        box_pos = save_state.box_pos;
        return ERROR;
    }
    default: {
        return 0;
    }
    }
    // unable to move
    if (map[pxx][pyy] == BLOCK) {
        return 0;
    }
    // pushed a box
    auto result =
        find(box_pos.begin(), box_pos.end(), std::pair<int, int>{pxx, pyy});
    int index = result - box_pos.begin();
    if (result != box_pos.end()) {
        int bx = box_pos[index].first;
        int by = box_pos[index].second;
        bxx = bx + dx[twist], byy = by + dy[twist];
        // box cannot move
        if (map[bxx][byy] == BLOCK || map[bxx][byy] == BOX ||
            map[bxx][byy] == TARGET_BOX) {
            return 0;
        }
        map[bx][by] = EMPTY;
        box_pos[index] = std::pair<int, int>{bxx, byy};
        map[bxx][byy] = (find(target_pos.begin(), target_pos.end(),
                              box_pos[index]) != target_pos.end())
                            ? TARGET_BOX
                            : BOX;
    }
    this->player_pos.first = pxx, this->player_pos.second = pyy;
    map[px][py] = EMPTY;
    auto find_player = find(target_pos.begin(), target_pos.end(), player_pos);
    for (auto a : target_pos) {
        if (map[a.first][a.second] == TARGET_BOX)
            continue;
        if (map[a.first][a.second] == EMPTY)
            map[a.first][a.second] = TARGET;
    }
    map[pxx][pyy] = PLAYER;
    return OK;
}

Status Game::Play(Timer& timer) {
    
    state current_state;
    Save_State(current_state);
    std::cout << "In Game::Play()" << std::endl;
    std::cout << "Print_Map() Finished!" << std::endl;
    this->is_game_finished = false;
    int ch;

    timer.start();

    while ((ch = cv::waitKeyEx(30))!=27) {
        if (Print_Map(timer) == QUIT) {
            timer.end();
            return QUIT;
        }
        std::cout << "In Play()循环" << std::endl;
        is_game_finished = Judge();
        if (is_game_finished) {
            timer.end();
            return OK;
        } 
        int value = Push(ch);
        if (value == 0)
            continue;
        if (value == SURRENDER) {
            timer.end();
            return QUIT;
        }
        if (value == OK) {
            stk.push(current_state);
        }
        Save_State(current_state);
    }
    return 0;
}

Status Random_Game::Play(Timer& timer) {
    this->Create_Map();
    return Game::Play(timer); 
}

bool Game::Judge() {
    for (auto a : box_pos) {
        if (find(target_pos.begin(), target_pos.end(), a) == target_pos.end()) {
            return false;
        }
    }
    return true;
}
