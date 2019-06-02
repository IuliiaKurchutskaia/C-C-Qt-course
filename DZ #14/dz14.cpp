//Крестики-Нолики
//Киселев И.

#include <iostream>
#include <map>
#include <time.h>
#include <iomanip>
#include <vector>

using namespace std;

enum values {empty,zero,cross};

map <values,char> quad = {{empty, ' '},
                          {zero, '0'},
                          {cross, 'x'}};
struct position {
    int row;
    int col;
};
class Board{
    int row_cnt=3;
    int col_cnt=3;
    values board_ [9] = {values::empty};
    //получение номера клетки
    int get_index(int row, int col)
    {
        return (row*col_cnt+col);
    }
    //проверка строки на выигрыш
    bool chk_row(int row)
    {
        values first = board_[get_index(row,0)];
        if (first == empty)
                return false;

        for (int i=1; i<col_cnt; i++)
        {
            if (board_[get_index(row,i)]!=first)
                return false;
        }

        return true;
    }
    //проверка колонки на выигрыш
    bool chk_col(int col)
    {
        values first = board_[get_index(0,col)];
        if (first == empty)
                return false;

        for (int i=1; i<col_cnt; i++)
        {
            if (board_[get_index(i,col)]!=first)
                return false;
        }

        return true;
    }
    //проверка диагонали на выигрыш
    bool chk_crosses()
    {
        values first = board_[get_index(0,0)];
        if (first == empty)
            return false;
        if (board_[get_index(1,1)]==first && board_[get_index(2,2)]==first)
            return true;
        first = board_[get_index(0,2)];
        if (first == empty)
            return false;
        if (board_[get_index(1,1)]==first && board_[get_index(2,0)]==first)
            return true;
        return false;
    }
    //Тут проверки на нахождение 2-х нулей в строке/столбце/диагонали, чтобы сделать правильный ход ПК.
    position chk_two_row(int row)
    {
        int cnt=0;
        int empty_pos=-1;
        for (int i=0; i<col_cnt; i++)
        {
            if (board_[get_index(row,i)]==cross)
                return {-1,-1};
            else if(board_[get_index(row,i)]==zero)
                cnt++;
            else if (board_[get_index(row,i)]==empty)
                empty_pos = i;
        }

        if (cnt!=2)
            return {-1,-1};

        return {row,empty_pos};
    }
    position chk_two_col(int col)
    {
        int cnt=0;
        int empty_pos=-1;
        for (int i=0; i<row_cnt; i++)
        {
            if (board_[get_index(i,col)]==cross)
                return {-1,-1};
            else if(board_[get_index(i,col)]==zero)
                cnt++;
            else if (board_[get_index(i,col)]==empty)
                empty_pos = i;
        }

        if (cnt!=2)
            return {-1,-1};

        return {empty_pos,col};
    }

    position chk_two_cross()
    {
        vector <position> diag1 = {{0,0},{1,1},{2,2}};
        vector <position> diag2 = {{2,0},{1,1},{0,2}};
        int cnt=0;
        position empty_pos= {-1,-1};
        for (auto d:diag1)
        {
            if (board_[get_index(d.row,d.col)]==cross)
                return {-1,-1};
            else if(board_[get_index(d.row,d.col)]==zero)
                cnt++;
            else if (board_[get_index(d.row,d.col)]==empty)
                empty_pos = {d.row,d.col};
        }
        if (cnt!=2)
        {
            cnt = 0;
            for (auto d:diag2)
            {
                if (board_[get_index(d.row,d.col)]==cross)
                    return {-1,-1};
                else if(board_[get_index(d.row,d.col)]==zero)
                    cnt++;
                else if (board_[get_index(d.row,d.col)]==empty)
                    empty_pos = {d.row,d.col};
            }
        }
        if (cnt!=2)
            return {-1,-1};

        return empty_pos;
    }
    //============================================================================//

public:
    //установка крестика или нолика
    void set_value(int row, int col, values val)
    {
        board_[row*col_cnt+col] = val;
    }
    values get_value(int row, int col) const
    {
        return board_[row*col_cnt+col];
    }
    //проверка на выигрыш по строкам и столбцам
    bool is_finish()
    {
        for (int i=0; i<col_cnt; i++)
            if (chk_col(i))
                return true;
        for(int i=0; i<row_cnt; i++)
            if (chk_row(i))
                return true;
        if(chk_crosses())
            return true;
        return false;
    }
    //рисование игровой доски
    void draw()
    {
        cout << "\n";
        cout << setw(3) <<  "0" << setw(3) << " 1" << setw(3) << " 2" << endl;
        for (int j=0; j<row_cnt; j++)
        {
            cout << j;
            for (int i=0; i < col_cnt; i++)
                cout << " " << quad[board_[get_index(j,i)]] << "|";
            cout << "\n";
        }
        cout << "\n";
    }
    //проверка на НЕ пустую клетку
    bool is_busy(int row, int col)
    {
        return board_[get_index(row,col)] != empty;
    }
    //проверка на корректные числовые значения введенных строк и столбцов
    bool chk_adekvat(int row,int col)
    {
        if ((row<row_cnt) && (col < col_cnt) && (row>=0) && (col >= 0))
                return true;
        else
            return false;
    }
    //Генерация рандомной позиции хода ПК
    void next_step_random()
    {
        position random_empty_pos = get_random_empty_position();
        set_value(random_empty_pos.row,random_empty_pos.col,zero);
    }
    position get_random_empty_position()
    {
        int row = -1;
        int col = -1;
        bool flag = true;
        while(flag==true)
        {
            row = 0 + rand()%3;
            col = 0 + rand()%3;
            if (!is_busy(row,col))
                return {row,col};
        }
    }
    //Генерация выигрышного хода, в зависимости от ситуации. Для сложного режима.
    position get_next_position()
    {
        position next_pos = {-1, -1};

        for (int i = 0; i < col_cnt; i++)
        {
            next_pos = chk_two_row(i);
            if ( next_pos.col != -1 )
                return next_pos;
        }

        next_pos = {-1, -1};
        for (int i = 0; i < row_cnt; i++)
        {
            next_pos = chk_two_col(i);
            if ( next_pos.row != -1 )
                return next_pos;
        }

        next_pos = {-1, -1};

        for (int i = 0; i < row_cnt; i++)
        {
            next_pos = chk_two_cross();
            if ( next_pos.row != -1 )
                return next_pos;
        }

        return get_random_empty_position();
    }
};

//проверка на корректный ввод
bool is_correct(char val)
{
    return (val == '0') || (val == '1') || (val == '2');
}
//Режим игрок - игрок================================================================
 void player_player()
 {
     system("clear");
     cout << "Режим игры - Игрок против Игрока\n";
     Board board;
     int col=-1,row=-1;
     char col_char,row_char;
     board.draw();
     for (int i=0; i<9; i++)
     {
         bool flag = true;
         char cur_player;
         if ((i&1)==0)
         {
             cur_player = 'X';
         }
         else
         {
             cur_player = '0';
         }
         while (flag==true)
         {
             cout << "Ходит " << cur_player << endl;
             cout << "Введите строку: ";
             cin >> row_char;
             cout << "Введите стобец: ";
             cin >> col_char;
             if (is_correct(row_char) && is_correct(col_char))
             {
                 row = (row_char-'0');
                 col = (col_char-'0');
                 flag = false;
             }
             else {
                 cout << "Некорректно введены значения!\n";
                 cout << "Выберите другую клетку.\n";
                 continue;
             }
         }
         system("clear");
         if ((i&1)==0)
         {
             if ((board.get_value(row,col)==empty) && (board.chk_adekvat(row,col)))
                 board.set_value(row,col,cross);
             else {
                 cout<< "Выберите другую клетку." << endl;
                 i--;
             }
         }
         else
         {
             if ((board.get_value(row,col)==empty) && (board.chk_adekvat(row,col)))
                 board.set_value(row,col,zero);
             else {
                 cout<< "Выберите другую клетку." << endl;
                 i--;
             }
         }

         board.draw();
         if(board.is_finish())
         {
             cout << "Игра окончена! Поздравляем с победой " << cur_player << endl;
             return;
         }
     }
     cout << "Ничья!" << endl;
 }

//Режим игрок - компьютер(Легко)=====================================================
 void player_pc()

 {
     system("clear");
     cout << "Режим игры - Игрок против Компьютера(Легко)\n";
     Board board;
     int row=-1,col=-1;
     char col_char,row_char;
     board.draw();
     srand(time(NULL));

     for (int i=0; i<9; i++)
     {
         char cur_player;
         if ((i&1)==0)
         {
             cur_player = 'X';
         }
         else
         {
             cur_player = '0';
         }

         if (cur_player == 'X')
         {
             bool flag = true;
             while(flag==true){
                 cout << "Ходит игрок - " << cur_player << endl;
                 bool chk=true;
                 while(chk==true)
                 {
                     cout << "Введите строку: ";
                     cin >> row_char;
                     cout << "Введите стобец: ";
                     cin >> col_char;
                     if (is_correct(row_char) && is_correct(col_char))
                     {
                         row = (row_char-'0');
                         col = (col_char-'0');
                         chk = false;
                     }
                     else {
                         cout << "Некорректно введены значения!\n";
                         cout << "Выберите другую клетку.\n";
                         continue;
                     }
                 }
                 if (!board.is_busy(row,col))
                 {
                     board.set_value(row,col,cross);
                     flag = false;
                 }
                 else
                 {
                     cout<< "Клетка уже занята!, выберите другую." << endl;
                 }
             }
         }
         else
         {
             cout << "Ход компьютера - " << cur_player << endl;
             bool flag = true;
             while(flag==true)
             {
                 row = 0 + rand()%3;
                 col = 0 + rand()%3;
                 if (!board.is_busy(row,col))
                 {
                     board.set_value(row,col,zero);
                     flag = false;
                 }
             }
         }
         system("clear");
         board.draw();
         if(board.is_finish())
         {
             cout << "Игра окончена! Поздравляем с победой " << cur_player << endl;
             return;
         }
     }
     cout << "Ничья!" << endl;

 }

 //Режим игрок - компьютер(Сложно)=====================================================
 void player_pc_hard()
 {
     system("clear");
     cout << "Режим игры - Игрок против Компьютера(Сложно)\n";
     Board board;
     int row=-1,col=-1;
     char col_char,row_char;
     board.draw();
     srand(time(NULL));

     for (int i=0; i<9; i++)
     {
         char cur_player;
         if ((i&1)==0)
             cur_player = 'X';
         else
             cur_player = '0';

         if (cur_player == 'X')
         {
             bool flag = true;
             while(flag==true){
                 cout << "Ходит игрок - " << cur_player << endl;
                 bool chk=true;
                 while(chk==true)
                 {
                     cout << "Введите строку: ";
                     cin >> row_char;
                     cout << "Введите стобец: ";
                     cin >> col_char;
                     if (is_correct(row_char) && is_correct(col_char))
                     {
                         row = (row_char-'0');
                         col = (col_char-'0');
                         chk = false;
                     }
                     else {
                         cout << "Некорректно введены значения!\n";
                         cout << "Выберите другую клетку.\n";
                         continue;
                     }
                 }
                 if (!board.is_busy(row,col))
                 {
                     board.set_value(row,col,cross);
                     flag = false;
                 }
                 else
                 {
                     cout<< "Клетка уже занята!, выберите другую." << endl;
                 }
             }
         }
         else
         {
             cout << "Ход компьютера - " << cur_player << endl;
             position next_pos = board.get_next_position();
             board.set_value(next_pos.row,next_pos.col,zero);
         }
         system("clear");
         board.draw();
         if(board.is_finish())
         {
             cout << "Игра окончена! Поздравляем с победой " << cur_player << endl;
             return;
         }
     }
     cout << "Ничья!" << endl;
 }

 int main()
{
     int mod;
     cout << "Добро пожаловать в игру Крестики-Нолики." << endl;
     cout << "Выберите режим игры" << endl;
     cout << "1. Режим Игрок против Игрока\n";
     cout << "2. Игрок против Компьютера. Сложность - легко.\n";
     cout << "3. Игрок против Компьютера. Сложность - сложно.\n";
     cout << "0. Выход"
             "\n";
     cout << "Ваш выбор: ";
     cin >> mod;
     switch(mod){
     case 1:
         player_player();
         break;
     case 2:
         player_pc();
         break;
     case 3:
         player_pc_hard();
         break;
     case 0:
         cout << "Всего доброго!\n";
         return 0;
     }
    cout << "Игра завершена\n";

    return 0;
}
