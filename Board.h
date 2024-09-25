#include <vector>
#include <cstdlib>
#include <tuple>

using namespace std;

class Tile {
    // baseTile sprite is for either hidden tiles or revealed tiles
    sf::Sprite baseTile;
    sf::Sprite flagSprite;
    bool flagged = false;
    bool is_revealed = false;
public:
    Tile() {}
    bool isItRevealed() {
        return is_revealed;
    }
    void revealTile(sf::Texture &texture, tuple<float, float> position) {
        is_revealed = true;
        baseTile.setTexture(texture);
        baseTile.setPosition(get<0>(position), get<1>(position));
    }
    int flag() {
        if (flagged) {
            flagged = false;
            return -1;
        } else {
            flagged = true;
            return 1;
        }
    }
    bool getFlagStatus() {
        return flagged;
    }
    sf::Sprite getFlagSprite() {
        return flagSprite;
    }
    void setFlagSprite(sf::Texture &texture, tuple<float, float> position) {
        flagSprite.setTexture(texture);
        flagSprite.setPosition(get<0>(position), get<1>(position));
    }
    void setBaseTile(sf::Texture &texture, tuple<float, float> position) {
        baseTile.setTexture(texture);
        baseTile.setPosition(get<0>(position), get<1>(position));
    }
    sf::Sprite getBaseTile() {
        return baseTile;
    }
    virtual void setBombSprite(sf::Texture &texture, tuple<float, float> position) {}
    virtual sf::Sprite getBombSprite() {}
    virtual void setSurroundingMines(int bombs) {}
    virtual int getSurroundingMines() {
     return 0;
    }
    virtual sf::Sprite getNumber() {}
    virtual void setNumber(sf::Texture &texture, tuple<float, float> position) {}
    virtual void tileIdentity() = 0;
};

class Bomb : public Tile {
    sf::Sprite bombSprite;
public:
    Bomb() : Tile() {}
    void setBombSprite(sf::Texture &texture, tuple<float, float> position) override {
        bombSprite.setTexture(texture);
        bombSprite.setPosition(get<0>(position), get<1>(position));
    }
    sf::Sprite getBombSprite() override {
        return bombSprite;
    }
    void tileIdentity() override {
        cout << "Bomb tile\n";
    }
};

class Regular : public Tile {
    int surroundingMines = 0;
    sf::Sprite numberSprite;
public:
    Regular() : Tile() {}
    int getSurroundingMines() override {
        return surroundingMines;
    }
    void setSurroundingMines(int bombs) override {
        surroundingMines = bombs;
    }
    sf::Sprite getNumber() override {
        return numberSprite;
    }
    void setNumber(sf::Texture &texture, tuple<float, float> position) override {
        numberSprite.setTexture(texture);
        numberSprite.setPosition(get<0>(position), get<1>(position));
    }
    void tileIdentity() override {
        cout << "Regular tile\n";
    }
};

class Board {
    int row;
    int col;
    int mineCount;
    vector<vector<Tile*>> board;
public:
    Board(int colCount, int rowCount, int mineCount) {
        // builds the 2d vector
        this->row = rowCount;
        this->col = colCount;
        for (int i = 0; i < row; i++) {
            vector<Tile*> tiles;
            for (int j = 0; j < col; j++) {
                Tile* newTile = new Regular;
                tiles.push_back(newTile);
            }
            board.push_back(tiles);
        }
        this->mineCount = mineCount;
        // randomly places mines
        int m = mineCount;
        while (m != 0) {
            int randNum = rand() % (row * col);
            int currentRow = 0;
            while (randNum >= col) {
                randNum -= col;
                currentRow++;
            }
            Regular* tilePtr = dynamic_cast<Regular*>(board[currentRow][randNum]);
            if (tilePtr) {
                delete board[currentRow][randNum];
                Tile* newBomb = new Bomb;
                board[currentRow][randNum] = newBomb;
                m--;
            }
        }
        // first two for loop selects the current tile
        Bomb* bombPtr;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                bombPtr = dynamic_cast<Bomb*>(board[i][j]);
                if (bombPtr) {
                    continue;
                }
                int bombs = 0;
                // this for loop checks the top 3 and bottom 3
                for (int k = -1; k < 2; k+=2) {
                    if (i + k >= 0 and i + k != row) {
                        for (int l = -1; l < 2; l++) {
                            if (j + l >= 0 and j + l != col) {
                                bombPtr = dynamic_cast<Bomb*>(board[i+k][j+l]);
                                if (bombPtr) {
                                    bombs++;
                                }
                            }
                        }
                    }
                }
                // checks left and right
                if (j != 0) {
                    bombPtr = dynamic_cast<Bomb*>(board[i][j-1]);
                    if (bombPtr) {
                        bombs++;
                    }
                }
                if (j < col - 1) {
                    bombPtr = dynamic_cast<Bomb*>(board[i][j+1]);
                    if (bombPtr) {
                        bombs++;
                    }
                }
                board[i][j]->setSurroundingMines(bombs);
            }
        }
    }
    vector<vector<Tile*>> getBoard() {
        return board;
    }
    void resetBoard() {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                delete board[i][j];
                Tile* newTile = new Regular;
                board[i][j] = newTile;
            }
        }
        // randomly places mines
        int m = mineCount;
        while (m != 0) {
            int randNum = rand() % (row * col);
            int currentRow = 0;
            while (randNum >= col) {
                randNum -= col;
                currentRow++;
            }
            Regular* tilePtr = dynamic_cast<Regular*>(board[currentRow][randNum]);
            if (tilePtr) {
                delete board[currentRow][randNum];
                Tile* newBomb = new Bomb;
                board[currentRow][randNum] = newBomb;
                m--;
            }
        }
        // first two for loop selects the current tile
        Bomb* bombPtr;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                bombPtr = dynamic_cast<Bomb*>(board[i][j]);
                if (bombPtr) {
                    continue;
                }
                int bombs = 0;
                // this for loop checks the top 3 and bottom 3
                for (int k = -1; k < 2; k+=2) {
                    if (i + k >= 0 and i + k != row) {
                        for (int l = -1; l < 2; l++) {
                            if (j + l >= 0 and j + l != col) {
                                bombPtr = dynamic_cast<Bomb*>(board[i+k][j+l]);
                                if (bombPtr) {
                                    bombs++;
                                }
                            }
                        }
                    }
                }
                // checks left and right
                if (j != 0) {
                    bombPtr = dynamic_cast<Bomb*>(board[i][j-1]);
                    if (bombPtr) {
                        bombs++;
                    }
                }
                if (j < col - 1) {
                    bombPtr = dynamic_cast<Bomb*>(board[i][j+1]);
                    if (bombPtr) {
                        bombs++;
                    }
                }
                board[i][j]->setSurroundingMines(bombs);
            }
        }

    }
    ~Board() {
        for (auto& row : board) {
            for (Tile* tile : row) {
                delete tile;
            }
        }
    }

};
