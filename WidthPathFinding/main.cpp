#include <iostream>
#include <iomanip> // std::setfill(' ') << std::setw(WIDTH)
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <array>

#include "Coord.h"


class Grid {
private:
    void obstacleCreation() {
        int obstacleAmount = WIDTH * HEIGHT / OBSTACLES_RATIO;
        Coord start1 = Coord();
        Coord start2 = Coord() + Coord(0,-1);
        
        for (int i = 0; i < obstacleAmount; ++i) {
            Coord obstacleCoord = Coord(rand() % (WIDTH - 3) + 1, rand() % (HEIGHT - 3) + 1);

            if (obstacleCoord != start1 && obstacleCoord != start2) {
                obstacles.insert(obstacleCoord);
            }
        }
    }
public:
    std::array<Coord, 4> DIRS;
    std::set<Coord> obstacles;
    Coord finish;
    Coord start;

    Grid() {
        DIRS = { Coord{1,0}, Coord{-1,0}, Coord{0,1}, Coord{0,-1} };
        finish = { WIDTH * 2, HEIGHT * 2 };
        start = { 1, HEIGHT / 2 };
        obstacleCreation();
    }

    bool inBoundaries(Coord next) {
        return next.x > 0 && next.x < RIGHT_EDGE && next.y > 0 && next.y < BOTTOM_EDGE;
    }

    bool notObstacle(Coord next) {
        return obstacles.find(next) == obstacles.end();
    }
    
    std::vector<Coord> giveNeighbors(Coord& current) {
        std::vector<Coord> neighbors;

        for (Coord i : DIRS) {
            Coord temp = current + i;

            if (inBoundaries(temp) && notObstacle(temp)) {
                neighbors.push_back(temp);
            }
        }
        return neighbors;
    }

    
};

void drawMap(Grid& grid, std::vector<Coord>* border = nullptr) {
        system("cls");

        std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::endl;

        for (int i = 1; i < BOTTOM_EDGE; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                if (j == 0 || j == RIGHT_EDGE) {
                    std::cout << '#';
                    continue;
                }
                if (i == grid.start.y && j == grid.start.x) {
                    std::cout << 'S';
                    continue;
                }
                if (i == grid.finish.y && j == grid.finish.x) {
                    std::cout << 'F';
                    continue;
                }
                else {
                    bool flag = false;
                    size_t k = 1;
                    if (border) {
                        for (; !(*border->end); ++k) {
                            if (j == (*border)[k].x && i == (*border)[k].y) {
                                std::cout << 'o';
                                flag = true;
                                break;
                            }
                        }
                    }
                    /*if (snake.getSnakeLength() > 1 && !flag) {
                        if (j == snake.getSnakeCoord(k).x && i == snake.getSnakeCoord(k).y) {
                            std::cout << snake.getTailEndForm();
                            continue;
                        }
                    }
                    if (!flag) {
                        for (k = 0; k < obstacles.size(); ++k) {
                            if (j == this->obstaclesList[k].x && i == this->obstaclesList[k].y) {
                                std::cout << this->obstacleForm;
                                flag = true;
                                break;
                            }
                        }
                    }*/
                    if (!flag) {
                        std::cout << ' ';
                    }
                }
            }
            std::cout << std::endl;
        }

        std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::endl;

        std::cout << std::endl;
          
};




int main() {
    Grid grid;
    
    drawMap(grid);

    while (true) {
        std::cout << "Please enter finish coordinates: ";
        std::cin >> grid.finish.x >> grid.finish.y;
        if (grid.inBoundaries(grid.finish) && grid.notObstacle(grid.finish)) {
            break;
        }
    }
            
    std::queue<Coord> border;
    std::map<Coord, Coord> cameFrom;
    std::vector<Coord> forDrawing;

    border.push(grid.start);
    cameFrom.insert(grid.start, grid.start);

    while (!border.empty()) {
        Coord current = border.front();

        if (current == grid.finish) {
            break;
        }

        for (Coord next : grid.giveNeighbors(current))
        {
            if (cameFrom.find(next) == cameFrom.end()) {
                border.push(next);
                cameFrom.insert(std::pair<Coord, Coord>(next, current));
            }
        }
        forDrawing.push_back(current);
        border.pop();
        drawMap(grid, &forDrawing);
    }

    Coord current = grid.finish;


        path = [current]
        while current != start:
    current = came_from[current]
        path.append(current)
        path.append(start) # optional
        path.reverse() # optional





   /* frontier = queue()
        frontier.put(start)
        came_from = {}
        came_from[start] = none

        while not frontier.empty() :
            current = frontier.get()

            if current == goal :
                break

                for next in graph.neighbors(current) :
                    if next not in came_from :
    frontier.put(next)
        came_from[next] = current*/






	return 0;
}