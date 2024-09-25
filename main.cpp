#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/graphics.hpp>
#include <vector>
#include <string>
#include "Board.h"
#include <map>
#include <chrono>

using namespace std;

vector<int> readFile(const string& fileName) {
    ifstream file(fileName);
    string buffer;
    vector<int> values;
    while (getline(file, buffer)) {
        values.push_back(stoi(buffer));
    }
    return values;
}

void readLeaderboardFile(string fileName, vector<vector<string>> &playerList) {
    ifstream test(fileName);
    if (!test) {
        test.close();
        ofstream fout;
        fout.open(fileName, ios::out);
        fout.close();
    }
    test.close();
    ifstream leaderBoard(fileName);
    if (!leaderBoard) {
        cout << "file failed to open\n";
        return;
    }
    string line;
    while (getline(leaderBoard, line)) {
        vector<string> row;
        istringstream wholeLine(line);
        string value;
        while (getline(wholeLine, value, ',')) {
            row.push_back(value);
        }
        if (!row.empty()) {
            playerList.push_back(row);
        }
    }
    leaderBoard.close();
}

int addEntry(string fileName, vector<vector<string>> &playerList, string &userName, int time) {
    int placement = 6;
    int minutes = 0;
    cout << "Time: " << time << endl;
    int temp = time;
    while (temp >= 60) {
        temp -= 60;
        minutes++;
    }
    vector<int> formatTime{0, 0, 0, 0};
    if (minutes >= 10) {
        formatTime[0] = minutes / 10;
        formatTime[1] = minutes % 10;
    } else {
        formatTime[1] = minutes;
    }
    if (temp >= 10) {
        formatTime[2] = temp / 10;
        formatTime[3] = temp % 10;
    } else {
        formatTime[3] = temp;
    }
    cout << formatTime[0] << endl;
    cout << formatTime[1] << endl;
    cout << formatTime[2] << endl;
    cout << formatTime[3] << endl;

    string bestTime;
    bestTime += to_string(formatTime[0]) + to_string(formatTime[1]);
    bestTime += ':';
    bestTime += to_string(formatTime[2]) + to_string(formatTime[3]);
    cout << bestTime << endl;
    vector<string> newPlayer{bestTime, userName};
    for (int i = 0; i < playerList.size(); i++) {
        int min;
        int sec;
        char delimiter;
        istringstream iss(playerList[i][0]);
        iss >> min >> delimiter >> sec;
        int totalSeconds = min * 60 + sec;
        if (time < totalSeconds) {
            for (int j = playerList.size() - 1; j != i; j--) {
                playerList[j] = playerList[j-1];
            }
            playerList.at(i) = newPlayer;
            placement = i+1;
            break;
        }
    }

    ofstream fout;
    fout.open(fileName);
    if (!fout) {
        cout << "can't open file\n";
        return placement;
    }
    for (int i = 0; i < playerList.size(); i++) {
        string s;
        s += playerList[i][0];
        s += ',';
        s += playerList[i][1];
        s += '\n';
        fout << s;
    }
    fout.close();
    return placement;
}

void createTexture(vector<string> imageList, map<string, sf::Texture> &textureMap) {
    sf::Texture revealedTileTexture;
    if (!revealedTileTexture.loadFromFile(imageList[0], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Revealed"] = revealedTileTexture;
    sf::Texture num1;
    if (!num1.loadFromFile(imageList[1], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Number1"] = num1;
    sf::Texture num2;
    if (!num2.loadFromFile(imageList[2], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Number2"] = num2;
    sf::Texture num3;
    if (!num3.loadFromFile(imageList[3], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Number3"] = num3;
    sf::Texture num4;
    if (!num4.loadFromFile(imageList[4], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Number4"] = num4;
    sf::Texture num5;
    if (!num5.loadFromFile(imageList[5], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Number5"] = num5;
    sf::Texture num6;
    if (!num6.loadFromFile(imageList[6], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Number6"] = num6;
    sf::Texture num7;
    if (!num7.loadFromFile(imageList[7], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Number7"] = num7;
    sf::Texture num8;
    if (!num8.loadFromFile(imageList[8], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Number8"] = num8;
    sf::Texture mineTexture;
    if (!mineTexture.loadFromFile(imageList[9], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Mine"] = mineTexture;
    sf::Texture hiddenTileTexture;
    if (!hiddenTileTexture.loadFromFile(imageList[10], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Hidden"] = hiddenTileTexture;
    sf::Texture flagTexture;
    if (!flagTexture.loadFromFile(imageList[11], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Flag"] = flagTexture;
    sf::Texture playTexture;
    if (!playTexture.loadFromFile(imageList[12], sf::IntRect(0, 0, 64, 64))) {
        cout << "didn't work\n";
    }
    textureMap["Play"] = playTexture;
    sf::Texture pauseTexture;
    if (!pauseTexture.loadFromFile(imageList[13], sf::IntRect(0, 0, 64, 64))) {
        cout << "didn't work\n";
    }
    textureMap["Pause"] = pauseTexture;
    sf::Texture debugTexture;
    if (!debugTexture.loadFromFile(imageList[14], sf::IntRect(0, 0, 64, 64))) {
        cout << "didn't work\n";
    }
    textureMap["Debug"] = debugTexture;
    sf::Texture digitsTexture;
    if (!digitsTexture.loadFromFile(imageList[15], sf::IntRect(0, 0, 32, 32))) {
        cout << "didn't work\n";
    }
    textureMap["Digits"] = digitsTexture;
    sf::Texture happyTexture;
    if (!happyTexture.loadFromFile(imageList[16], sf::IntRect(0, 0, 64, 64))) {
        cout << "didn't work\n";
    }
    textureMap["HappyFace"] = happyTexture;
    sf::Texture loseTexture;
    if (!loseTexture.loadFromFile(imageList[17], sf::IntRect(0, 0, 64, 64))) {
        cout << "didn't work\n";
    }
    textureMap["LoseFace"] = loseTexture;
    sf::Texture winTexture;
    if (!winTexture.loadFromFile(imageList[18], sf::IntRect(0, 0, 64, 64))) {
        cout << "didn't work\n";
    }
    textureMap["WinFace"] = winTexture;
    sf::Texture leaderboardTexture;
    if (!leaderboardTexture.loadFromFile(imageList[19], sf::IntRect(0, 0, 64, 64))) {
        cout << "didn't work\n";
    }
    textureMap["Leaderboard"] = leaderboardTexture;
    sf::Texture digits;
    if (!digits.loadFromFile(imageList[15], sf::IntRect(0, 0, 231, 32))) {
        cout << "digits didn't work\n";
    }
    textureMap["Digits"] = digits;

}

void UISprites(int col, int row, map<string, sf::Texture> &textureMap, map<string, sf::Sprite> &spriteMap, sf::RenderWindow &window) {
    tuple<float, float> currentPosition(0, (row + 0.5) * 32);
    get<0>(currentPosition) = (col * 32) - 240;
    sf::Sprite play;
    play.setTexture(textureMap["Play"]);
    play.setPosition(get<0>(currentPosition),get<1>(currentPosition));
    spriteMap["Play"] = play;
    sf::Sprite pause;
    pause.setTexture(textureMap["Pause"]);
    pause.setPosition(get<0>(currentPosition),get<1>(currentPosition));
    spriteMap["Pause"] = pause;
    sf::Sprite debug;
    debug.setTexture(textureMap["Debug"]);
    get<0>(currentPosition) = (col * 32) - 304;
    debug.setPosition(get<0>(currentPosition), get<1>(currentPosition));
    spriteMap["Debug"] = debug;
    get<0>(currentPosition) = ((col / 2.0) * 32) - 32;
    sf::Sprite happyFace;
    happyFace.setTexture(textureMap["HappyFace"]);
    happyFace.setPosition(get<0>(currentPosition), get<1>(currentPosition));
    spriteMap["HappyFace"] = happyFace;
    sf::Sprite lostFace;
    lostFace.setTexture(textureMap["LoseFace"]);
    lostFace.setPosition(get<0>(currentPosition), get<1>(currentPosition));
    spriteMap["LoseFace"] = lostFace;
    sf::Sprite winFace;
    winFace.setTexture(textureMap["WinFace"]);
    winFace.setPosition(get<0>(currentPosition), get<1>(currentPosition));
    spriteMap["WinFace"] = winFace;
    sf::Sprite leaderboard;
    get<0>(currentPosition) = (col * 32) - 176;
    leaderboard.setTexture(textureMap["Leaderboard"]);
    leaderboard.setPosition(get<0>(currentPosition), get<1>(currentPosition));
    spriteMap["Leaderboard"] = leaderboard;

    sf::IntRect textureRect(0, 0, 21, 32);
    sf::Sprite zero;
    zero.setTexture(textureMap["Digits"]);
    zero.setTextureRect(textureRect);
    spriteMap["0"] = zero;

    sf::Sprite one;
    one.setTexture(textureMap["Digits"]);
    textureRect.left += 21;
    one.setTextureRect(textureRect);
    spriteMap["1"] = one;

    sf::Sprite two;
    two.setTexture(textureMap["Digits"]);
    textureRect.left += 21;
    two.setTextureRect(textureRect);
    spriteMap["2"] = two;

    sf::Sprite three;
    three.setTexture(textureMap["Digits"]);
    textureRect.left += 21;
    three.setTextureRect(textureRect);
    spriteMap["3"] = three;

    sf::Sprite four;
    four.setTexture(textureMap["Digits"]);
    textureRect.left += 21;
    four.setTextureRect(textureRect);
    spriteMap["4"] = four;

    sf::Sprite five;
    five.setTexture(textureMap["Digits"]);
    textureRect.left += 21;
    five.setTextureRect(textureRect);
    spriteMap["5"] = five;

    sf::Sprite six;
    six.setTexture(textureMap["Digits"]);
    textureRect.left += 21;
    six.setTextureRect(textureRect);
    spriteMap["6"] = six;

    sf::Sprite seven;
    seven.setTexture(textureMap["Digits"]);
    textureRect.left += 21;
    seven.setTextureRect(textureRect);
    spriteMap["7"] = seven;

    sf::Sprite eight;
    eight.setTexture(textureMap["Digits"]);
    textureRect.left += 21;
    eight.setTextureRect(textureRect);
    spriteMap["8"] = eight;

    sf::Sprite nine;
    nine.setTexture(textureMap["Digits"]);
    textureRect.left += 21;
    nine.setTextureRect(textureRect);
    spriteMap["9"] = nine;

    sf::Sprite negative;
    negative.setTexture(textureMap["Digits"]);
    textureRect.left += 21;
    negative.setTextureRect(textureRect);
    spriteMap["negative"] = negative;


}

void drawUIBar(int col,int row, int status, bool paused, int seconds, int &mineRemaining, map<string, sf::Sprite> &spriteMap, sf::RenderWindow &window) {
    window.draw(spriteMap["Debug"]);
    if (status == 0) {
        window.draw(spriteMap["HappyFace"]);
    } else if (status == 1) {
        window.draw(spriteMap["LoseFace"]);
    } else if (status == 2){
        window.draw(spriteMap["WinFace"]);
    }
    if (paused) {
        window.draw(spriteMap["Pause"]);
    } else {
        window.draw(spriteMap["Play"]);
    }
    window.draw(spriteMap["Leaderboard"]);
    tuple<float, float> position(33, (row + 0.5) * 32 + 16);
    int temp = mineRemaining;
    if (mineRemaining < 0) {
       // draws the negative
       spriteMap["negative"].setPosition(get<0>(position) - 21, get<1>(position));
       window.draw(spriteMap["negative"]);
    }
    // draws the mine counter
    vector<int> count{0, 0, 0};
    int i = 0;
    if (temp < 0) {
        temp *= -1;
    }
    while (temp > 0) {
        count.at(i) = temp % 10;
        temp /= 10;
        i++;
    }
    spriteMap[to_string(count[2])].setPosition(get<0>(position), get<1>(position));
    window.draw(spriteMap[to_string(count[2])]);
    spriteMap[to_string(count[1])].setPosition(get<0>(position) + 21, get<1>(position));
    window.draw(spriteMap[to_string(count[1])]);
    spriteMap[to_string(count[0])].setPosition(get<0>(position) + 42, get<1>(position));
    window.draw(spriteMap[to_string(count[0])]);

    // draws the timer counter
    vector<int> formatTime{0, 0, 0, 0};
    int minutes = 0;
    while (seconds >= 60) {
        seconds -= 60;
        minutes++;
    }
    if (minutes >= 10) {
        formatTime[1] = minutes % 10;
        formatTime[0] = minutes / 10;
    } else {
        formatTime[1] = minutes;
    }
    if (seconds >= 10) {
        formatTime[3] = seconds % 10;
        formatTime[2] = seconds / 10;
    } else {
        formatTime[3] = seconds;
    }
    get<0>(position) = (col * 32) - 97;
    get<1>(position) = (row + 0.5) * 32 + 16;
    spriteMap[to_string(formatTime[0])].setPosition(get<0>(position), get<1>(position));
    window.draw(spriteMap[to_string(formatTime[0])]);
    get<0>(position) = (col * 32) - 78;
    spriteMap[to_string(formatTime[1])].setPosition(get<0>(position), get<1>(position));
    window.draw(spriteMap[to_string(formatTime[1])]);
    get<0>(position) = (col * 32) - 54;
    spriteMap[to_string(formatTime[2])].setPosition(get<0>(position), get<1>(position));
    window.draw(spriteMap[to_string(formatTime[2])]);
    get<0>(position) = (col * 32) - 33;
    spriteMap[to_string(formatTime[3])].setPosition(get<0>(position), get<1>(position));
    window.draw(spriteMap[to_string(formatTime[3])]);
}

void debug(Board* board, sf::Texture &texture, sf::RenderWindow &window) {
    window.clear(sf::Color::White);
    for (int i = 0; i < board->getBoard().size(); i++) {
        for (int j = 0; j < board->getBoard()[i].size(); j++) {
            sf::Sprite hiddenTile;
            hiddenTile.setTexture(texture);
            hiddenTile.setPosition(j * 32, i * 32);
            window.draw(hiddenTile);
            Bomb* bombPtr = dynamic_cast<Bomb*>(board->getBoard()[i][j]);
            if (bombPtr) {
                window.draw(board->getBoard()[i][j]->getBombSprite());
            }
        }
    }
}

void pauseGame(Board* board, sf::Texture &texture, sf::RenderWindow &window) {
    window.clear(sf::Color::White);
    for (int i = 0; i < board->getBoard().size(); i++) {
        for (int j = 0; j < board->getBoard()[i].size(); j++) {
            sf::Sprite revealedTile;
            revealedTile.setTexture(texture);
            revealedTile.setPosition(j * 32, i * 32);
            window.draw(revealedTile);
        }
    }
}

int revealSurrounding(int row, int col, Board* board, map<string, sf::Texture> &textureMap) {
    int revealed_count = 0;
    // top 3 and bottom 3
    for (int i = -1; i < 2; i+=2) {
        if (row + i >= 0 and row + i < board->getBoard().size()) {
            for (int j = -1; j < 2; j++) {
                if (col + j >= 0 and col + j < board->getBoard()[0].size() and !board->getBoard()[row + i][col + j]->isItRevealed() and !board->getBoard()[row + i][col + j]->getFlagStatus()) {
                    tuple<float, float> currPos((col + j) * 32, (row + i) * 32);
                    board->getBoard()[row + i][col + j]->revealTile(textureMap["Revealed"], currPos);
                    revealed_count++;
                    Bomb* bombPtr = dynamic_cast<Bomb*>(board->getBoard()[row + i][col + j]);
                    if (bombPtr) {
                        continue;
                    } else if (board->getBoard()[row + i][col + j]->getSurroundingMines() == 0) {
                        revealed_count += revealSurrounding(row + i, col + j, board, textureMap);
                    }
                }
            }
        }
    }
    // left and right
    for (int k = -1; k < 2; k+=2) {
        if (col + k >= 0 and col + k < board->getBoard()[0].size() and !board->getBoard()[row][col + k]->isItRevealed() and !board->getBoard()[row][col + k]->getFlagStatus()) {
            tuple<float, float> currPos((col + k) * 32, row * 32);
            board->getBoard()[row][col + k]->revealTile(textureMap["Revealed"], currPos);
            revealed_count++;
            Bomb* bombPtr = dynamic_cast<Bomb*>(board->getBoard()[row][col + k]);
            if (bombPtr) {
                continue;
            } else if (board->getBoard()[row][col + k]->getSurroundingMines() == 0) {
                revealed_count+= revealSurrounding(row, col + k, board, textureMap);
            }
        }
    }
    return revealed_count;
}

string drawleaderBoardWindow(int colCount, int rowCount, vector<vector<string>> &playerVect, int newPlacement) {
    int width = colCount * 16;
    int height = (rowCount * 16) + 50;
    // loading font
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "font file doesn't work\n";
        return "closed";
    }
    // main text
    sf::Text title;
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    title.setPosition(width / 2, (height / 2) - 120);

    // player list
    string playerLists;
    for (int i = 0; i < playerVect.size(); i++) {
        playerLists += to_string(i+1) + ".\t";
        playerLists += playerVect[i][0];
        playerLists += '\t';
        playerLists += playerVect[i][1];
        if (i+1 == newPlacement) {
            playerLists += '*';
        }
        playerLists += "\n\n";
    }
    sf::Text players;
    players.setFont(font);
    players.setString(playerLists);
    players.setCharacterSize(18);
    players.setFillColor(sf::Color::White);
    players.setStyle(sf::Text::Bold);
    sf::FloatRect playersRect = players.getLocalBounds();
    players.setOrigin(playersRect.left + playersRect.width / 2.0f, playersRect.top + playersRect.height / 2.0f);
    players.setPosition(width / 2, (height / 2) + 20);



    sf::RenderWindow window(sf::VideoMode(width, height), "MineSweeper");
    window.clear(sf::Color::Blue);
    window.draw(title);
    window.draw(players);
    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return "closed";
            }
        }

    }
}

string drawWelcomeWindow(int colCount, int rowCount) {
    int width = colCount * 32;
    int height = (rowCount * 32) + 100;
    // loading font
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "font file doesn't work\n";
        return "closed";
    }
    // main text
    sf::Text title;
    title.setFont(font);
    title.setString("WELCOME TO MINESWEEPER!");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    title.setPosition(width / 2, (height / 2) - 150);

    // enter your name text
    sf::Text sub;
    sub.setFont(font);
    sub.setString("Enter your name:");
    sub.setCharacterSize(20);
    sub.setFillColor(sf::Color::White);
    sub.setStyle(sf::Text::Bold);
    sf::FloatRect subRect = sub.getLocalBounds();
    sub.setOrigin(subRect.left + subRect.width/2.0f, subRect.top + subRect.height/2.0f);
    sub.setPosition(width / 2, (height / 2) - 75);

    //initialize the spot for the user input
    sf::Text input;
    input.setFont(font);
    string userInput = "|";
    input.setString(userInput);
    input.setCharacterSize(18);
    input.setFillColor(sf::Color::Yellow);
    sub.setStyle(sf::Text::Bold);
    sf::FloatRect inputRect = input.getLocalBounds();
    input.setOrigin(inputRect.left + inputRect.width/2.0f, inputRect.top + inputRect.height/2.0f);
    input.setPosition(width / 2, (height / 2) - 45);


    sf::RenderWindow window(sf::VideoMode(width, height), "MineSweeper");
    window.clear(sf::Color::Blue);
    window.draw(title);
    window.draw(sub);
    window.draw(input);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return "closed";
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter and userInput.size() > 1) {
                    userInput.pop_back();
                    window.close();
                    return userInput;
                }
            }
            if (event.type == sf::Event::TextEntered) {
                if ((event.text.unicode > 64 and event.text.unicode < 91) or (event.text.unicode > 96 and event.text.unicode < 123)) {
                    if (userInput.size() == 11) {
                        continue;
                    } else if (userInput.size() == 1) {
                        userInput.pop_back();
                        auto c = static_cast<unsigned char>(event.text.unicode);
                        userInput += toupper(c);
                        userInput += '|';
                    } else {
                        userInput.pop_back();
                        auto c = static_cast<unsigned char>(event.text.unicode);
                        userInput += tolower(c);
                        userInput += '|';
                    }
                } else if (event.text.unicode == '\b') {
                    if (userInput.size() > 1) {
                        userInput.pop_back();
                        userInput.pop_back();
                        userInput += '|';
                    }
                }
                input.setString(userInput);
                window.clear(sf::Color::Blue);
                window.draw(title);
                window.draw(sub);
                window.draw(input);
                window.display();

            }
        }

    }
    return userInput;
}

string drawGameWindow(int colCount, int rowCount, int mineCount, string &userName) {
    vector<vector<string>> playerList;
    readLeaderboardFile("./files/leaderboard.txt", playerList);
    int height = (rowCount * 32) + 100;
    int width = colCount * 32;
    int bombFreeTiles = (rowCount * colCount) - mineCount;
    int mineRemaining = mineCount;
    int status = 0;
    bool debugOn = false;
    int placement = 6;
    bool paused = false;
    chrono::steady_clock clock;
    auto current_time = clock.now();
    int totalGameTime = 0;
    int totalTime;
    int totalPausedTime = 0;
    auto pauseStartTime = clock.now();
    vector<string> fileName = {"./files/images/tile_revealed.png", "./files/images/number_1.png", "./files/images/number_2.png", "./files/images/number_3.png",
                               "./files/images/number_4.png", "./files/images/number_5.png", "./files/images/number_6.png", "./files/images/number_7.png",
                               "./files/images/number_8.png", "./files/images/mine.png", "./files/images/tile_hidden.png", "./files/images/flag.png",
                               "./files/images/play.png", "./files/images/pause.png", "./files/images/debug.png", "./files/images/digits.png",
                               "./files/images/face_happy.png", "./files/images/face_lose.png", "./files/images/face_win.png", "./files/images/leaderboard.png"};
    map<string, sf::Texture> textureMap;
    createTexture(fileName, textureMap);
    map<string, sf::Sprite> spriteMap;

    sf::RenderWindow window(sf::VideoMode(width, height), "MineSweeper");
    UISprites(colCount, rowCount,textureMap, spriteMap, window);
    Board gameBoard = Board(colCount, rowCount, mineCount);
    window.clear(sf::Color::White);
    // draws the board here
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            tuple<float, float> currentPosition(j * 32, i * 32);
            gameBoard.getBoard()[i][j]->setBaseTile(textureMap["Hidden"], currentPosition);
            gameBoard.getBoard()[i][j]->setFlagSprite(textureMap["Flag"], currentPosition);
            Bomb *bombPtr = dynamic_cast<Bomb *>(gameBoard.getBoard()[i][j]);
            if (bombPtr) {
                gameBoard.getBoard()[i][j]->setBombSprite(textureMap["Mine"], currentPosition);
            } else {
                int number = gameBoard.getBoard()[i][j]->getSurroundingMines();
                if (number != 0) {
                    string numbers = "Number" + to_string(number);
                    gameBoard.getBoard()[i][j]->setNumber(textureMap[numbers], currentPosition);
                }
            }
            window.draw(gameBoard.getBoard()[i][j]->getBaseTile());
        }
    }
    drawUIBar(colCount, rowCount, status, paused, totalGameTime - totalPausedTime, mineRemaining, spriteMap, window);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return "closed";
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                //cout << mousePosition.x << endl;
                //cout << mousePosition.y << endl;
                // check if the user clicks outside of the board for UI buttons
                if (mousePosition.y > 32 * (rowCount + 0.5) and mousePosition.y < (32 * (rowCount + 0.5)) + 60) {
                    // face button
                    if (mousePosition.x > (colCount * 32) - 430 and mousePosition.x < (colCount * 32) - 370) {
                        gameBoard.resetBoard();
                        debugOn = false;
                        paused = false;
                        status = 0;
                        current_time = clock.now();
                        totalGameTime = 0;
                        totalPausedTime = 0;
                        bombFreeTiles = (rowCount * colCount) - mineCount;
                        mineRemaining = mineCount;
                        placement = 6;
                        window.clear(sf::Color::White);
                        // draws the new board
                        for (int i = 0; i < rowCount; i++) {
                            for (int j = 0; j < colCount; j++) {
                                tuple<float, float> currentPosition(j * 32, i * 32);
                                gameBoard.getBoard()[i][j]->setBaseTile(textureMap["Hidden"], currentPosition);
                                gameBoard.getBoard()[i][j]->setFlagSprite(textureMap["Flag"], currentPosition);
                                Bomb *bombPtr = dynamic_cast<Bomb *>(gameBoard.getBoard()[i][j]);
                                if (bombPtr) {
                                    gameBoard.getBoard()[i][j]->setBombSprite(textureMap["Mine"], currentPosition);
                                } else {
                                    int number = gameBoard.getBoard()[i][j]->getSurroundingMines();
                                    if (number != 0) {
                                        string numbers = "Number" + to_string(number);
                                        gameBoard.getBoard()[i][j]->setNumber(textureMap[numbers], currentPosition);
                                    }
                                }
                                window.draw(gameBoard.getBoard()[i][j]->getBaseTile());
                            }
                        }
                        window.display();
                    }
                    // debug button
                    if (mousePosition.x > (colCount * 32) - 304 and mousePosition.x < (colCount * 32) - 240 and status == 0 and !paused) {
                        debugOn = !debugOn;
                        if (debugOn) {
                            debug(&gameBoard, textureMap["Hidden"], window);
                            drawUIBar(colCount, rowCount, status, paused, totalGameTime - totalPausedTime, mineRemaining, spriteMap, window);
                            window.display();
                        }
                    }
                    // play/pause button
                    if (mousePosition.x > (colCount * 32) - 240 and mousePosition.x < (colCount * 32) - 176 and status == 0) {
                        paused = !paused;
                        if (paused) {
                            pauseStartTime = clock.now();
                            pauseGame(&gameBoard, textureMap["Revealed"], window);
                            drawUIBar(colCount, rowCount, status, paused, totalGameTime - totalPausedTime, mineRemaining, spriteMap, window);
                            window.display();
                            debugOn = false;
                        } else {
                            chrono::duration<double> elapsedSeconds = chrono::steady_clock::now() - pauseStartTime;
                            totalPausedTime += elapsedSeconds.count();
                        }
                    }
                    // leaderboard button
                    if (mousePosition.x > (colCount * 32) - 176 and mousePosition.x < (colCount * 32) - 112) {
                        debugOn = false;
                        if (paused) {
                            drawleaderBoardWindow(colCount, rowCount, playerList, placement);
                        } else {
                            if (status == 0) {
                                pauseStartTime = clock.now();
                                paused = true;
                                pauseGame(&gameBoard, textureMap["Revealed"], window);
                                drawUIBar(colCount, rowCount, status, paused, totalGameTime - totalPausedTime, mineRemaining, spriteMap, window);
                                window.display();
                                drawleaderBoardWindow(colCount, rowCount, playerList, placement);
                                paused = false;
                                chrono::duration<double> elapsedSeconds = chrono::steady_clock::now() - pauseStartTime;
                                totalPausedTime += elapsedSeconds.count();
                            } else {
                                drawUIBar(colCount, rowCount, status, paused, totalGameTime - totalPausedTime, mineRemaining, spriteMap, window);
                                window.display();
                                drawleaderBoardWindow(colCount, rowCount, playerList, placement);
                            }
                        }
                    }
                } else if (mousePosition.y < rowCount * 32 and !debugOn and status == 0 and !paused) {
                    int currentCol = mousePosition.x / 32;
                    int currentRow = mousePosition.y / 32;
                    tuple<float, float> currentPosition(currentCol * 32, currentRow * 32);
                    // check if the tile is revealed
                    if (!gameBoard.getBoard()[currentRow][currentCol]->isItRevealed()) {
                        // if the tile is not revealed, check if its flagged
                        if (!gameBoard.getBoard()[currentRow][currentCol]->getFlagStatus()) {
                            gameBoard.getBoard()[currentRow][currentCol]->revealTile(textureMap["Revealed"],currentPosition);
                            bombFreeTiles--;
                            // if player clicked on a bomb tile, game ends
                            Bomb* bombPtr = dynamic_cast<Bomb*>(gameBoard.getBoard()[currentRow][currentCol]);
                            if (bombPtr) {
                                cout << "clicked on a bomb\n";
                                for (int i = 0; i < rowCount; i++) {
                                    for (int j = 0; j < colCount; j++) {
                                        bombPtr = dynamic_cast<Bomb*>(gameBoard.getBoard()[i][j]);
                                        if (bombPtr and !gameBoard.getBoard()[i][j]->isItRevealed()) {
                                            get<0>(currentPosition) = j * 32;
                                            get<1>(currentPosition) = i * 32;
                                            gameBoard.getBoard()[i][j]->revealTile(textureMap["Revealed"],currentPosition);
                                        }
                                    }
                                }
                                status = 1;
                            } else if (gameBoard.getBoard()[currentRow][currentCol]->getSurroundingMines() == 0) {
                                // check if the current tile doesn't have any surrounding Mines
                                bombFreeTiles -= revealSurrounding(currentRow, currentCol, &gameBoard, textureMap);
                            }
                            cout << "BombFreeTile remaining:" << bombFreeTiles << endl;
                        }
                    }
                }

            }
            // only for flags
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) and !debugOn and status == 0 and !paused) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (mousePosition.y < rowCount * 32) {
                    int currentCol = mousePosition.x / 32;
                    int currentRow = mousePosition.y / 32;
                    //cout << "CurrentCol: " << currentCol << endl;
                    //cout << "CurrentRow: " << currentRow << endl;
                    // check if the tile has been revealed
                    if (!gameBoard.getBoard()[currentRow][currentCol]->isItRevealed()) {
                        // places a flag or removes the flag
                        mineRemaining -= gameBoard.getBoard()[currentRow][currentCol]->flag();

                    }
                }
            }
        }
        if (!debugOn and !paused) {
            Bomb *bombPtr;
            // game won
            if (bombFreeTiles == 0) {
                status = 2;
                for (int i = 0; i < rowCount; i++) {
                    for (int j = 0; j < colCount; j++) {
                        bombPtr = dynamic_cast<Bomb*>(gameBoard.getBoard()[i][j]);
                        if (bombPtr and !gameBoard.getBoard()[i][j]->getFlagStatus()) {
                            gameBoard.getBoard()[i][j]->flag();
                            mineRemaining = 0;
                        }
                    }
                }
            }
            // updates the board
            window.clear(sf::Color::White);
            for (int i = 0; i < rowCount; i++) {
                for (int j = 0; j < colCount; j++) {
                    window.draw(gameBoard.getBoard()[i][j]->getBaseTile());
                    // check if tile is revealed
                    if (gameBoard.getBoard()[i][j]->isItRevealed()) {
                        bombPtr = dynamic_cast<Bomb *>(gameBoard.getBoard()[i][j]);
                        if (bombPtr) {
                            window.draw(gameBoard.getBoard()[i][j]->getBombSprite());
                        } else {
                            window.draw(gameBoard.getBoard()[i][j]->getNumber());
                        }
                        // if tile not revealed, then check if its flagged
                    } else if (gameBoard.getBoard()[i][j]->getFlagStatus()) {
                        window.draw(gameBoard.getBoard()[i][j]->getFlagSprite());
                    }
                }
            }
            drawUIBar(colCount, rowCount, status, paused, totalGameTime - totalPausedTime, mineRemaining, spriteMap, window);
            window.display();
            if (bombFreeTiles == 0) {
                placement = addEntry("files/leaderboard.txt", playerList, userName, totalGameTime);
                drawleaderBoardWindow(colCount, rowCount, playerList, placement);
                bombFreeTiles++;
            }
        }
        // timer
        chrono::duration<double> elapsedSeconds = chrono::steady_clock::now() - current_time;
        totalTime = elapsedSeconds.count();
        if (totalGameTime < totalTime and status == 0) {
            totalGameTime++;
        }
    }
    return "gg\n";
}

int main() {
    vector<int> values = readFile("files/config.cfg");

    //drawing welcome window
    string userName = drawWelcomeWindow(values[0], values[1]);
    cout << userName << endl;
    if (userName == "closed") {
        return 1;
    }
    string gameFeedBack = drawGameWindow(values[0], values[1], values[2], userName);
    if (gameFeedBack == "won") {
        cout << "W\n";
    } else {
        cout << "obomba\n";
    }

    return 0;
}