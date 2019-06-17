#ifndef BOARD_H
#define BOARD_H
#include <vector>
using namespace std;

enum values {empty, squad, shot, lose};

struct position {
    int row;
    int col;
};

class Board
{
    int row_cnt = 10; //Количество строк
    int col_cnt = 10; //Количество столбцов
    int one_cnt = 0;
    int two_cnt = 0;
    int three_cnt = 0;
    int quad_cnt = 0;
    values board_[100] = {values::empty};
    vector<int> ships_place;
    vector<int> free_pos;
    values visible_board[100] = {values::empty};

    int                     calc_index(int row, int col);                              //Получение индекса по строке и столбцу
    position                calc_pos_by_index(int index);                              //Получение строрки и столбца по индексу
    vector <position>       calc_area(int i_start, int j_start, int i_end, int j_end); //Определение зоны, куда собираются поставить корабль
    pair<position,position> calc_auto_pos(int value);                                  //Автовыбор позиции корабля для ИИ

    bool chk_area(int i_start, int j_start, int i_end, int j_end);                     //Проверка зоны, в которую собираются установить корабль
    bool chk_pos(const pair<position,position> &pos);                                  //Проверка возможности поставить корабль в конкретное место

    void add_ships(int deck);                                                          //Установка кораблей

public:
    Board();

    values  get_value(int row, int col) const;                               //Получение значения
    int     get_one_cnt();                                                   //Количество однопалубников на поле
    int     get_two_cnt();                                                   //Количество двупалубников на поле
    int     get_three_cnt();                                                 //Количество трехпалубников на поле
    int     get_quad_cnt();                                                  //Количество четырехпалубников на поле

    void set_value(int row, int col, values val);                            //Установка значения

    bool add_ship(int i_start, int j_start, int i_end = -1, int j_end = -1); //Добавление корабля на поле
    void add_ship_auto();                                                    //Установка кораблей для ИИ

    bool chk_ships_placed();                                                 //Проверка - установлены ли все корабли
    bool chk_cnt(int i_start, int j_start, int i_end, int j_end);            //Проверка - можно ли еще поставить корабль такого размера
    bool chk_finish();                                                       //Проверка на конец игры

    void draw();                                                             //Рисование доски
    void draw_visible();                                                     //Рисование результатов выстрелов
    bool shot(int i, int j);                                                 //Выстрелы по полям

};

#endif // BOARD_H
