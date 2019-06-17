#include "board.h"
#include <map>
#include <iomanip>
#include <iostream>
#include <time.h>
#include <algorithm>

using namespace std;

#define VERTICAL_DIRECTION      false
#define HORIZONTAL_DIRECTION    true

const int max_one   = 4; //Максимальное количество однопалубных
const int max_two   = 3; //Максимальное количество двупалубных
const int max_three = 2; //Маскимальное количество трехпалубных
const int max_quad  = 1; //Маскимальное количество четырехпалубных

std::map <values,char> quad = {{empty, ' '},
                               {squad, '#'},
                               {shot, 'x'},
                               {lose, '*'}};

/*===========Формирование свободных клеток поля=============*/
Board::Board()
{
    free_pos.resize(100);
    for (int i=0; i < free_pos.size(); i++)
        free_pos[i] = i;
};

/*===============Получение индекса по строке и столбцу==========*/
int Board::calc_index(int row, int col)
{
    return (row*col_cnt+col);
}

/*=============Получение строрки и столбца по индексу============*/
position Board::calc_pos_by_index(int index)
{
    position pos;

    pos.col = index%col_cnt;
    pos.row = index/col_cnt;

    return pos;
}

/*===============================Установка значения==============================*/
void Board::set_value(int row, int col, values val)
{
    board_[row*col_cnt+col] = val;
}
    /*===============================Получение значения==============================*/
values Board::get_value(int row, int col) const
{
    return board_[row*col_cnt+col];
}

/*=========Определение зоны, куда собираются поставить корабль===========*/
vector<position> Board::calc_area(int i_start, int j_start, int i_end, int j_end)
{
    position start_pos{i_start,j_start}, end_pos{i_end,j_end};
    vector<position> area_multi;
    if (i_start > i_end)
    {
        start_pos = {i_end, j_end};
        end_pos = {i_start, j_start};
    }
    for (int row=i_start-1; row <=i_end+1; row++)
        for (int col=j_start-1; col <= j_end+1; col++)
        {
            if ((row >= 0) && (col >= 0) && (col <= 9) && (row <= 9))            
                area_multi.push_back({row,col});

        }

    return area_multi;
}

/*==============Проверка зоны, в которую собираются установить корабль=============*/
bool Board::chk_area(int i_start, int j_start, int i_end, int j_end)
{
    vector<position> pos_area = calc_area(i_start,j_start,i_end,j_end);

    for (auto pos : pos_area)
        if (board_[calc_index(pos.row,pos.col)] != empty)
            return false;

    for (auto pos : pos_area)
    {
        int index = calc_index(pos.row,pos.col);
        free_pos.erase(remove(free_pos.begin(), free_pos.end(), index), free_pos.end());
    }

    return true;
}

/*==================Проверка на НЕдиагональное расположение корабля=============*/
bool correct_rowcol(int i_start, int j_start, int i_end, int j_end)
{
    int row_dist = abs(i_end - i_start)+1;
    int col_dist = abs(j_end - j_start)+1;
    if ((row_dist > 4) || (col_dist > 4))
        return false;


    bool chk_row = i_start == i_end;
    bool chk_col = j_start == j_end;
    return chk_col || chk_row;
}

/*========================Расчет размеров корабля====================*/
int calc_size (int i_start, int j_start, int i_end, int j_end)
{
    int row_dist = abs(i_end - i_start)+1;
    int col_dist = abs(j_end - j_start)+1;

    if ((row_dist == 1) && (col_dist == 1))
        return 1;

    if ((row_dist == 2) || (col_dist == 2))
        return 2;

    if ((row_dist == 3) || (col_dist == 3))
        return 3;

    if ((row_dist == 4) || (col_dist == 4))
        return 4;
}

/*======Добавление корабля на поле======================*/
bool Board::add_ship(int i_start, int j_start, int i_end, int j_end)
{
    if ( !correct_rowcol(i_start,j_start,i_end,j_end) )
        return false;

    if ( !chk_area(i_start,j_start,i_end,j_end) )
        return false;

    for (int i = i_start; i<= i_end; i++)
        for (int j=j_start; j<=j_end; j++)
        {
            board_[calc_index(i,j)] = squad;
            ships_place.push_back(calc_index(i,j));
        }

    int size = calc_size(i_start,j_start,i_end,j_end);
    switch (size)
    {
        case 1: one_cnt++; break;
        case 2: two_cnt++; break;
        case 3: three_cnt++; break;
        case 4: quad_cnt++; break;
    }

    return true;
}

/*===========Автовыбор позиции корабля для ИИ=========================*/
pair<position,position> Board::calc_auto_pos(int value)
{

    pair<position,position> result;
    bool direction = 0+rand()%2;
    int free_pos_index = rand()%(free_pos.size() + 1);
    result.first = calc_pos_by_index(free_pos[free_pos_index]);

    if (value == 1)
    {
        result.second = result.first;
        return result;
    }

    if (direction == VERTICAL_DIRECTION)
    {
        while ( result.first.row > row_cnt-value )
        {
            free_pos_index = rand()%(free_pos.size() + 1);
            result.first = calc_pos_by_index(free_pos_index);
        }
        result.second.row = result.first.row + value - 1;
        result.second.col = result.first.col;

    }
    else
    {
        while ( result.first.col > col_cnt-value )
        {
            free_pos_index = rand()%(free_pos.size() + 1);
            result.first = calc_pos_by_index(free_pos_index);
        }

        result.second.row = result.first.row;
        result.second.col = result.first.col + value - 1;
    }

    return result;
}

/*=======================Установка кораблей===========================*/
void Board::add_ships(int deck)
{
    int max_cnt = 5-deck;
    int cnt = 0;
    while (cnt < max_cnt)
    {
        auto temp = calc_auto_pos(deck);

        if ( !chk_pos(temp) )
            continue;

        if( add_ship(temp.first.row,temp.first.col,temp.second.row,temp.second.col) )
            cnt++;
    }
}

/*===========Проверка возможности поставить корабль в конкретное место=============*/
bool Board::chk_pos(const pair<position,position> &pos)
{
    int first_index = calc_index(pos.first.row, pos.first.col);
    int second_index = calc_index(pos.second.row, pos.second.col);

    if ( find(free_pos.begin(), free_pos.end(), first_index) != free_pos.end() &&
         find(free_pos.begin(), free_pos.end(), second_index) != free_pos.end() ) //есть среди свободных клеток
        return true;

    return false;
}

/*=============Установка кораблей для ИИ==========*/
void Board::add_ship_auto()
{
    for (int i = 4; i > 0; i--)
        add_ships(i);
//    cout << "ИИ готов к бою!" << endl;
}

/*==================Количество кораблей каждого типа============*/
int Board::get_one_cnt()
{
    return one_cnt;
}

int Board::get_two_cnt()
{
    return two_cnt;
}

int Board::get_three_cnt()
{
    return three_cnt;
}

int Board::get_quad_cnt()
{
    return quad_cnt;
}

/*======Проверка - можно ли еще поставить корабль такого размера============*/
bool Board::chk_cnt(int i_start, int j_start, int i_end, int j_end)
{
    int size = calc_size(i_start,j_start,i_end,j_end);
    bool result = true;
    switch(size)
    {
        case 1:
            if (one_cnt >=max_one)
                result = false;
                break;
        case 2:
            if (two_cnt >=max_two)
                result = false;
                break;
        case 3:
            if (three_cnt >=max_three)
                result = false;
                break;
        case 4:
            if (quad_cnt >=max_quad)
                result = false;
                break;
        default: result = true;
    }
    return result;
}

/*============Проверка - установлены ли все корабли=================*/
bool Board::chk_ships_placed()
{
    bool once   = one_cnt   == max_one;
    bool two    = two_cnt   == max_two;
    bool three  = three_cnt == max_three;
    bool quad   = quad_cnt  == max_quad;

    return once && two && three && quad;
}

bool Board::shot(int i, int j)
{
    if (board_[calc_index(i,j)] == empty)
    {
        board_[calc_index(i,j)] = lose;
        visible_board[calc_index(i,j)] = lose;
        return false;
    }
    else if (board_[calc_index(i,j)] == squad)
    {
        board_[calc_index(i,j)] = values::shot;
        visible_board[calc_index(i,j)] = values::shot;
        return true;
    }

}

/*===============================Рисование доски=================================*/
void Board::draw()
{
    cout << "\n  ";
    for (int i=65; i<75; i++)
    {
        cout << " " << setw(1) <<  (char)i;
    }
    cout << endl;
    for (int j=0; j<row_cnt; j++)
    {
        cout << setw(2) << j << "|";
        for (int i=0; i < col_cnt; i++)
            cout << setw(1) << quad[board_[calc_index(j,i)]] << setw(1) << "|";
        cout << endl;
    }
}

void Board::draw_visible()
{
    cout << "\n  ";
    for (int i=65; i<75; i++)
    {
        cout << " " << setw(1) <<  (char)i;
    }
    cout << endl;
    for (int j=0; j<row_cnt; j++)
    {
        cout << setw(2) << j << "|";
        for (int i=0; i < col_cnt; i++)
            cout << setw(1) << quad[visible_board[calc_index(j,i)]] << setw(1) << "|";
        cout << endl;
    }
}
/*=================Проверка на конец игры===================*/
bool Board::chk_finish()
{
    for (auto tmp : ships_place)
        if (board_[tmp] != values::shot)
            return false;
    return true;
}
