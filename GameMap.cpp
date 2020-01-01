#include "GameMap.h"
#include <direct.h>
#define QUIT -1
extern cv::Mat frame;

Game_Map::Game_Map() : map(NULL), map_height(0), map_length(0){
    Box = cv::imread(".\\img\\BOX.jpg", cv::IMREAD_COLOR);
    if (Box.empty()) {
        std::cout << "Unable to open the image!" << std::endl;
        throw std::runtime_error("unable to open the image");
    }
    Player = cv::imread(".\\img\\PLAYER.png", cv::IMREAD_COLOR);
    if (Player.empty()) {
        std::cout << "Unable to open the image!" << std::endl;
        throw std::runtime_error("unable to open the image");
    }
    Block = cv::imread(".\\img\\BLOCK.png", cv::IMREAD_COLOR);
    if (Block.empty()) {
        std::cout << "Unable to open the image!" << std::endl;
        throw std::runtime_error("unable to open the image");
    }
    Target = cv::imread(".\\img\\TARGET.png", cv::IMREAD_COLOR);
    if (Target.empty()) {
        std::cout << "Unable to open the image!" << std::endl;
        throw std::runtime_error("unable to open the image");
    }
    Targ_box = cv::imread(".\\img\\TARGET_BOX.png", cv::IMREAD_COLOR);
    if (Targ_box.empty()) {
        std::cout << "Unable to open the image!" << std::endl;
        throw std::runtime_error("unable to open the image");
    }
};
Status Game_Map::Print_Instruction(){
    cv::Mat INS = cv::imread(".\\img\\INS.png", cv::IMREAD_COLOR);
    cvui::image(frame, 300, 245, INS);
   /* cvui::text(frame, 300, 245, "move:", 0.6);
    cvui::text(frame, 300, 265, "   w         ↑   :", 0.6);
    cvui::text(frame, 300, 285, "a  s  d   ← ↓ →", 0.6);
    cvui::text(frame, 300, 305, "recall: z", 0.6;
    cvui::text(frame, 300, 325, "quit: 0", 0.6);*/
	return OK; 
}

/* Game_Map:: */
Status Game_Map::Print_Map(Timer& timer) {
    frame = cv::Scalar(49, 52, 49);
    timer.getTime().show();

    if (cvui::button(frame, 70, 245, 150, 50, "Quit Game")) return QUIT;

    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < map_length; ++j) {
            int xpos =  j * 20, ypos = i * 20;
            switch (map[i][j]) {
                case '0': {
                    break;
                }
                case '1': {
                    cvui::image(frame, xpos, ypos, Block);
                    break;
                }
                case '2': {
                    cvui::image(frame, xpos, ypos, Box);
                    break;
                }
                case '3': {
                    cvui::image(frame, xpos, ypos, Target);
                    break;
                }
                case '4': {
                    cvui::image(frame, xpos, ypos, Targ_box);
                    break;
                }
                case '5': {
                    cvui::image(frame, xpos, ypos, Player);
                    break;
                }
            }
        }
    }
    Print_Instruction();
    cvui::update();
    cv::imshow(WINDOW_NAME, frame);
    std::cout << "Print_Map() cv::imshow() Finished!" << std::endl;
    return OK;
}

void Game_Map::Clear_Map() {
    for (int i = 0; i < map_height; ++i) {
        std::fill(map[i], map[i] + map_length, EMPTY);
    } //全部置空
    //周围一圈是BLOCK
    for (int i = 0; i < map_height; ++i) {
        map[i][0] = BLOCK;
        map[i][map_length - 1] = BLOCK;
    }
    for (int i = 0; i < map_length; ++i) {
        map[0][i] = BLOCK;
        map[map_height - 1][i] = BLOCK;
    }
	return ;
}

void Game_Map::Save_State(state &save_state) {
    /*td::cout << "In Save_Map()" << std::endl;*/
    char **&save_map = save_state.save_map;
    save_map = new char *[map_height];
    for (int i = 0; i < map_height; ++i) {
        save_map[i] = new char[map_length];
    }
    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < map_length; ++j) {
            save_map[i][j] = map[i][j];
        }
    }
    save_state.box_pos = this->box_pos;
    save_state.player_pos = this->player_pos;
	return ;
}

/*Random_Game_Map::*/
Random_Game_Map::Random_Game_Map(int height /* = 10 */, int length /* = 10 */) {
    // 外框为阻碍物，所以地图的长宽都加2
    map_height = height + 2;
    map_length = length + 2;
    // std::cout << "map_height = " << map_height << std::endl;
    // std::cout << "map_weight = " << map_length << std::endl;
    map = new char *[map_height];
    for (int i = 0; i < map_height; ++i) {
        if ((map[i] = new (std::nothrow) char[map_length]) == NULL) {
            std::cout << "memory limit exceeded" << std::endl;
            exit(OVERFLOW);
        }
        std::fill(map[i], map[i] + map_length, EMPTY);
    }
    /*std::cout << "test" << std::endl;*/
    for (int i = 0; i < map_height; ++i) {
        map[i][0] = BLOCK;
        map[i][map_length - 1] = BLOCK;
    }
    for (int i = 0; i < map_length; ++i) {
        map[0][i] = BLOCK;
        map[map_height - 1][i] = BLOCK;
    }
    // Print_Map();
    srand(time(0));
}

Random_Game_Map::~Random_Game_Map() {
    for (int i = 0; i < map_height; ++i) {
        delete[] map[i];
    }
    delete[] map;
}

//Create random map
Status Random_Game_Map::Create_Map() {
    std::cout << "Creating Map..." << std::endl;
    Random_Create_Map();
    while (!Check_Map()) {
        // std::cout << "Try: " << std::endl;
        Clear_Map();
        box_pos.clear();
        target_pos.clear();
        Random_Create_Map();
        // Print_Map();
    }
    return OK;
}
void Random_Game_Map::Random_Create_Map() {
    // std::cout << "In Random_Game_Map::Random_Create_Map(): " << std::endl;
    const int Num_Of_Blocks = 30;
    for (int i = 0; i < Num_Of_Blocks; ++i) {
        Create_Item(BLOCK);
    }
    player_pos = Create_Item(PLAYER);
    box_pos.push_back(Create_Item(BOX));
    target_pos.push_back(Create_Item(TARGET));
}
std::pair<int, int> Random_Game_Map::Create_Item(const char item) {
    int x_Block = rand() % map_height, y_Block = rand() % map_length;
    while (map[x_Block][y_Block] != EMPTY) {
        x_Block = rand() % map_height;
        y_Block = rand() % map_length;
    }
    map[x_Block][y_Block] = item;
    return {x_Block, y_Block};
}
bool Random_Game_Map::Check_Map() {
    const int INF = 0x4f4f4f4f;
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    struct Node {
        int px, py, bx, by, step;
    } s;
    std::queue<Node> que;
    // const int MAP_HEIGHT = static_cast<const int>(map_height);
    // const int MAP_LENGTH = static_cast<const int>(map_length);
    // int vis[MAP_HEIGHT][MAP_LENGTH][MAP_HEIGHT][MAP_LENGTH];
    std::vector<std::vector<std::vector<std::vector<int>>>> vis(
        map_height,
        std::vector<std::vector<std::vector<int>>>(
            map_length, std::vector<std::vector<int>>(
                            map_height, std::vector<int>(map_length, INF))));
    int ans = INF;
    s.px = player_pos.first;
    s.py = player_pos.second;
    s.bx = box_pos[0].first;
    s.by = box_pos[0].second;
    s.step = 0;
    vis[s.px][s.py][s.bx][s.by] = 0;
    que.push(s);

    while (!que.empty()) {
        Node now = que.front();
        que.pop();
        int px = now.px, py = now.py, bx = now.bx, by = now.by, step = now.step;
        if (map[bx][by] == TARGET) {
            ans = std::min(ans, step);
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            int pxx = px + dx[i], pyy = py + dy[i];
            if (map[pxx][pyy] == BLOCK) {
                continue;
            }
            int bxx = bx, byy = by;
            int flag = 0;
            //推到了箱子
            if (pxx == bx && pyy == by) {
                flag = 1;
                bxx = bx + dx[i];
                byy = by + dy[i];
                if (map[bxx][byy] == BLOCK) {
                    continue;
                }
            }
            if (vis[pxx][pyy][bxx][byy] <= step + flag) {
                continue;
            }
            Node to;
            to.px = pxx, to.py = pyy, to.bx = bxx, to.by = byy,
            to.step = step + flag;
            que.push(to);
            vis[pxx][pyy][bxx][byy] = step + flag;
        }
    }
    if (ans == INF)
        return false;
    return true;
}

Normal_Game_Map::Normal_Game_Map(int num_map /*= 1*/) {
    std::ifstream ifile;
    ifile.open((std::string) ".\\Data\\" + std::to_string(num_map) +
                   (std::string) ".in",
               std::ios::in);
    if (!ifile) {
        std::cout << "Error when open file！" << std::endl;
        exit(ERROR);
    }
    ifile >> map_height >> map_length;
    ifile.get();
    // std::cout << "map_height = " << map_height << " map_length = " <<
    // map_length << std::endl;
    map = new char *[(long long)map_height + 1];
    for (int i = 0; i < map_height + 1; ++i) {
        map[i] = new char[(long long)map_length + 1];
    }
    for (int i = 0; i < map_height; ++i) {
        ifile.getline(map[i], (long long)map_length + 1);
    }
    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < map_length; ++j) {
            Data_Transform(map[i][j]);
        }
    }
    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < map_length; ++j) {
            if (map[i][j] == PLAYER) {
                player_pos = std::pair<int, int>{i, j};
            }
            if (map[i][j] == BOX) {
                box_pos.push_back(std::pair<int, int>{i, j});
            }
            if (map[i][j] == TARGET) {
                target_pos.push_back(std::pair<int, int>{i, j});
            }
        }
    }
    ifile.close();
}

void Normal_Game_Map::Data_Transform(char &ch) {
    switch (ch) {
    case '_':
    case '#': {
        ch = BLOCK;
        break;
    }
    case '-': {
        ch = EMPTY;
        break;
    }
    case '$': {
        ch = BOX;
        break;
    }
    case '@': {
        ch = PLAYER;
        break;
    }
    case '.': {
        ch = TARGET;
        break;
    }
    }
	return ;
}

Normal_Game_Map::~Normal_Game_Map() {
    for (int i = 0; i < map_height; ++i) {
        delete[] map[i];
    }
    delete[] map;
}
