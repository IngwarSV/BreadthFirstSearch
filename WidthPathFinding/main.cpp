#include <iostream>
#include <iomanip> // std::setfill(' ') << std::setw(WIDTH)
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <array>


#include "Coord.h"


class Grid {
private:
    void mapBoundariesCreation() {
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                if (i == 0 || i == BOTTOM_EDGE || j == 0 || j == RIGHT_EDGE) {
                    map_borders.push_back(Coord{ j, i });
                }
            }
        }
    }

    void add_wall(int x1, int y1, int x2, int y2) {
        for (int x = x1; x < x2; ++x) {
            for (int y = y1; y < y2; ++y) {
                obstacles.push_back(Coord{ x, y });
            }
        }
    }

    void obstacleCreation() {
        //add_wall(3, 3, 5, 12);
        add_wall(13, 4, 15, 15);
        add_wall(21, 0, 23, 7);
        add_wall(23, 5, 26, 7);
    }

public:
    std::array<Coord, 4> DIRS;
    std::vector<Coord> map_borders;
    std::vector<Coord> obstacles;
    Coord finish;
    Coord start;

    Grid() {
        DIRS = { Coord{ 1, 0 }, Coord{ -1, 0 }, Coord{ 0, 1 }, Coord{ 0, -1 } };
        finish = { WIDTH - 6, 2};
        start = { 4, HEIGHT / 2 };
        mapBoundariesCreation();
        obstacleCreation();
    }

    bool inBoundaries(Coord next) {
        return next.x > 0 && next.x < RIGHT_EDGE && next.y > 0 && next.y < BOTTOM_EDGE;
    }

    bool notObstacle(Coord next) {
        return std::find(std::begin(obstacles), std::end(obstacles), next) == std::end(obstacles);
    }

    std::vector<Coord> giveNeighbors(Coord& current) {
        std::vector<Coord> neighbors;

        for (Coord i : DIRS) {
            Coord temp = current + i;

            if (inBoundaries(temp) && notObstacle(temp)) {
                neighbors.push_back(temp);
            }
        }
        if ((current.x + current.y) % 2 == 0) {
            std::reverse(neighbors.begin(), neighbors.end());
        }

        return neighbors;
    }
};

void drawMap(Grid& grid, std::map<Coord, Coord>* cameFrom = nullptr, std::vector<Coord>* path = nullptr) {
        system("cls");

        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                Coord id{ j, i };

                if (std::find(grid.map_borders.begin(), grid.map_borders.end(), id) != grid.map_borders.end()) {
                    std::cout << '#';
                }
                else if (std::find(grid.obstacles.begin(), grid.obstacles.end(), id) != grid.obstacles.end()) {
                    std::cout << '#';
                }
                else if (id == grid.start) {
                    std::cout << 'S';
                }
                else if (id == grid.finish) {
                    std::cout << 'F';
                }
                else if (path && std::find(path->begin(), path->end(), id) != path->end()) {
                    std::cout << 'o';
                }
                else if (cameFrom && cameFrom->find(id) != cameFrom->end()) {
                    Coord from = (*cameFrom)[id];
                    if (id.x == from.x - 1) {
                        std::cout << '>';
                    }
                    else if (id.x == from.x + 1) {
                        std::cout << '<';
                    }
                    else if (id.y == from.y + 1) {
                        std::cout << '^';
                    }
                    else if (id.y == from.y - 1) {
                        std::cout << 'v';
                    }
                }
                else {
                    std::cout << ' ';
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
};

int main() {
    Grid grid;
    
    drawMap(grid);

    /*while (true) {
        std::cout << "Please enter coordinates of finish: ";
        std::cin >> grid.finish.x >> grid.finish.y;
        if (grid.inBoundaries(grid.finish) && grid.notObstacle(grid.finish)) {
            break;
        }
    }*/
            
    std::queue<Coord> searchBoundary;
    std::map<Coord, Coord> cameFrom;
    std::vector<Coord> forDrawing;
    

    searchBoundary.push(grid.start);
    
    cameFrom.insert(std::pair<Coord, Coord>(grid.start, grid.start));

    while (!searchBoundary.empty()) {
        Coord current = searchBoundary.front();

        if (current == grid.finish) {
            break;
        }

        for (Coord next : grid.giveNeighbors(current))
        {
            if (cameFrom.find(next) == cameFrom.end()) {
                searchBoundary.push(next);
                cameFrom.insert(std::pair<Coord, Coord>(next, current));
            }
        }
        forDrawing.push_back(current);
        searchBoundary.pop();
        drawMap(grid, &cameFrom);
    }

    Coord current = grid.finish;
    std::vector<Coord> path;
    path.push_back(grid.finish);
    
    while (current != grid.start) {
        current = cameFrom.at(current);
        path.push_back(current);
    }

    path.push_back(current);
    std::reverse(std::begin(path),std::end(path));

    drawMap(grid, &cameFrom, &path);

	return 0;
}