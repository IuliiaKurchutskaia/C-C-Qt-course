//Морской бой
//Киселев И.

#include "board.h"
#include "utils.h"

#include <iostream>
//#include <iomanip>
//#include <map>

using namespace std;

/*==============Расстановка кораблей игроком============*/
void create_board(Board &my_board)
{
    my_board.draw();

        while (true)
        {
            cout<< "Введите клетку куда ставить корабль" << endl;

            auto start_pos  = utils::ask_pos();
            auto end_pos    = utils::ask_pos();

            if ( !my_board.chk_cnt(start_pos.first,start_pos.second,end_pos.first,end_pos.second) )
            {
                cout << "Этот тип кораблей уже расставлен!" << endl;
                continue;
            }

            if ( !my_board.add_ship(start_pos.first,start_pos.second,end_pos.first,end_pos.second) )
                cout << "Невозможно поставить корабль!" << endl;
                    my_board.draw();
                    if (my_board.chk_ships_placed())

                    {
                        cout << "Корабли расставлены!" << endl;
                        break;
                    }
        }
}
/*===============Стрельба игрока==============*/
bool my_shot(Board &PC)
{
    cout << endl << "Ход игрока" << endl;

    auto pos = utils::ask_pos();

    if(PC.shot(pos.first,pos.second))
    {
        cout << "Попадание!" << endl;
        return true;
    }
    return false;
}
/*================Стрельба ИИ=================*/
bool PC_shot(Board &player)
{
    cout << "Ход ИИ" << endl;
    int i = rand()%10;
    int j = rand()%10;

    if(player.shot(i,j))
    {
        cout << "Попадание!" << endl;
        return true;
    }
    return false;
}
/*===================Ход игры=================*/
void game_begun(Board &player, Board &PC)
{
    bool chk_end = false;
    while (!chk_end)
    {
        bool chk_shot = true;
        system("clear");
        cout << endl << "Поле игрока";
        player.draw();
        cout << endl << "Поле противника";
        while (chk_shot)
        {
            PC.draw_visible();
            if(PC.chk_finish())
                break;
            if(!my_shot(PC))
            {
                chk_shot = false;
            }
        }
        if (PC.chk_finish())
        {
            chk_end = true;
            PC.draw_visible();
            cout << "Выиграл игрок" << endl;
            break;
        }
        chk_shot = true;
        while (chk_shot)
        {
            player.draw();
            if (player.chk_finish())
                break;
            if(!PC_shot(player))
                chk_shot = false;
        }
        if (PC.chk_finish())
        {
            chk_end = true;
            player.draw();
            cout << "Выиграл ИИ" << endl;
            break;
        }
    }
}
/*==========Главное меню==============*/
bool main_menu(Board &board)
{
    int choice;
    while (choice != 0)
    {
        cout << "1. Расставить корабли вручную" << endl;
        cout << "2. Расставить корабли автоматически и начать игру" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите цифру (0-2): ";
        cin >> choice;
        switch(choice)
        {
            case 1:
                    create_board(board);
                    return true;
                    break;
            case 2:
                    board.add_ship_auto();
                    return true;
                    break;
        case 0: return false;
            default: cout << "Введен неверный вариант" << endl;
                    break;
        }
    }
    return true;
}

int main()
{
    srand(time(NULL));
    Board board;
    Board board_pc;
    cout << "Игра - Морской бой" << endl;
//    main_menu(board);
    int choice = main_menu(board);

    if ( !choice )
    {
        cout << "Выход из игры.." << endl;
        return 0;
    }

    board_pc.add_ship_auto();
    game_begun(board,board_pc);

    return 0;
}
