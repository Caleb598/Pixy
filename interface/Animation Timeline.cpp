g++ your_program.cpp -o your_program -lncurses
#include <iostream>
#include <ncurses.h>

const int ROWS = 10;
const int COLS = 1000000;

int main() {
    // Initialize ncurses
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    // Declare and initialize the 2D array
    std::string chart[ROWS][COLS];

    // Assigning labels to the first row of the first column
    chart[0][0] = "Frame";
    chart[1][0] = "Move X";
    chart[2][0] = "Move Y";
    chart[3][0] = "Move Z";
    chart[4][0] = "Rotate X";
    chart[5][0] = "Rotate Y";
    chart[6][0] = "Rotate Z";
    chart[7][0] = "Size X";
    chart[8][0] = "Size Y";
    chart[9][0] = "Size Z";

    // Assigning numbers to the other columns in the first row
    for (int j = 1; j < COLS; ++j) {
        chart[0][j] = std::to_string(j);
    }

    // Assigning colors to the first row
    attron(COLOR_PAIR(1));
    for (int j = 0; j < COLS; ++j) {
        mvprintw(0, j, chart[0][j].c_str());
    }
    attroff(COLOR_PAIR(1));

    // Assigning colors to specific columns in the first column
    attron(COLOR_PAIR(2));
    for (int i = 1; i < 4; ++i) {
        mvprintw(i, 0, chart[i][0].c_str());
    }
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    for (int i = 4; i < 7; ++i) {
        mvprintw(i, 0, chart[i][0].c_str());
    }
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(4));
    for (int i = 7; i < 10; ++i) {
        mvprintw(i, 0, chart[i][0].c_str());
    }
    attroff(COLOR_PAIR(4));

    // Refresh the window
    refresh();

    // Wait for user input
    getch();

    // Clean up ncurses
    endwin();

    return 0;
}
