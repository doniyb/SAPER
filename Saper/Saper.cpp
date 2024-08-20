// Saper.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <stack>
#include <Windows.h>
#include <ctime>
#include <conio.h>

// постановка курсора в определённой части экрана консоли 
void gotoxy(int x, int y)
{
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

class Game;

// класс игрового поля
class Map
{
private:

    // граница
    const int BORDER = -100;
    // мина
    const int MINA = 9;
    // пустое поле
    const int FILD = 0;

    // кликтнутая ячейка
    const int CLICKED_CELL = -1;

    // размер поля включая границы
    int size;

    // создания вектора для поля
    std::vector <std::vector<int>> vmap;

    // маска(точки в выводе)
    std::vector <std::vector<int>> mask;

    //черновой вектор, который копирует vmap
    std::vector <std::vector<int>> cop;
public:

    Map()
    {
        size = 10;
    }

    // базовое создание поля
    void initmap()
    {
        std::vector <int> temp;
        for (int i = 0; i < size; ++i) {
            for (int k = 0; k < size; ++k) {
                // определенее границ поля
                if (i == 0 || k == 0 || i == size - 1 || k == size - 1)
                    temp.push_back(BORDER);
                else
                    temp.push_back(FILD);
            }
            vmap.push_back(temp); // значение ячеек поля
            mask.push_back(temp); // маска ячеек поля
            temp.erase(temp.begin(), temp.end());
        }
    }


    // вывод объектов на игровое поле
    void show()
    {
        gotoxy(0, 0);
        for (int i = 0; i < size; ++i) {
            for (int k = 0; k < size; ++k) {
                whitecolor();

                if (cop[k][i] == CLICKED_CELL) {
                    if (vmap[k][i] != BORDER) {
                        coloroutp(k, i);
                        std::cout << vmap[k][i];
                        whitecolor();
                        continue;
                    }
                }

                if (mask[k][i] == FILD) {
                    std::cout << '.';
                    continue;
                }
                std::cout << '#';

            }
            std::cout << std::endl;
        }
    }

    //ввывод разработчика
    /*void output_developer()
    {
        gotoxy(0, 0);
        for (int i = 0; i < size; ++i) {
            for (int k = 0; k < size; ++k) {

                if (vmap[k][i] == MINA) {
                    std::cout << '*';
                    continue;
                }

                if (vmap[k][i] == BORDER) {
                    std::cout << '#';
                    continue;
                }

                std::cout << vmap[k][i];

            }
            std::cout << std::endl;
        }
    }*/

    // случайная расстоновка мин
    void setRandMin(int n )
    {
        // проверка на количество мин
        int numMines = n;
        if (n == 0){}
        else {
            numMines = n % ((size - 2) * (size - 2));
            if (numMines == 0)
                ++numMines;
        }


        for(int i=0; i<numMines; ++i) {


            int x = 0;
            int y = 0;

            // поиск пустой ячейки для мины
            do {
                x = rand() % (size - 2) + 1;
                y = rand() % (size - 2) + 1;

            } while (vmap[x][y] == MINA);

            vmap[x][y] = MINA;
        }
    }

    // расстоновка чисел
    void numFild()
    {
        for (int i = 1; i < size-1; ++i) {
            for (int k = 1; k < size-1; ++k) {

                if (vmap[k][i] == MINA)
                    // проходимся по ячекам вокруг мины
                    for (int K = k - 1; K < k + 2; ++K) {
                        for (int I = i - 1; I < i + 2; ++I) {
                            // увеличиваем на 1 если это не мина и не граница
                            if (vmap[K][I] != MINA && vmap[K][I] != BORDER)
                                ++vmap[K][I];
                        }
                    }
            }
        }
    }
    
    // размер катры 
    int SizeMap() {
        return size;
    }

    // вывод содержимого клекти при нажатии на неё
    bool outp(int x, int y) {
        gotoxy(x, y);
        if (vmap[x][y] == MINA) {
            coloroutp(x, y);
            std::cout << "*";
            whitecolor();
            return false;
        }
        else {
            coloroutp(x, y);
            std::cout << vmap[x][y];
            open_empty(x, y);
            cop[x][y] = CLICKED_CELL;//метка на то что на клетку кликали
            whitecolor();
        }
        return true;
    }

    //изменение цвета вывода на белый
    void whitecolor()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);
    }

    //цвет цифры
    void coloroutp(int x, int y) 
    {
        if (vmap[x][y] == 0) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 0);//чёрный
        }

        if (vmap[x][y] == 1) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 11);//светло-голубой
        }

        if (vmap[x][y] == 2) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);//зеленый
        }

        if (vmap[x][y] == 3) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);//красный
        }

        if (vmap[x][y] ==4) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 1);//синий
        }

        if (vmap[x][y] == 5) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 13);//розовый
        }

        if (vmap[x][y] == 6) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 14);//желтый
        }

        if (vmap[x][y] == 7) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 6);//коричнивый
        }

        if (vmap[x][y] == 8) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 10);//светло-зеленый
        }

        if (vmap[x][y] == MINA) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);//алый
        }
    }

    void open_empty(int px, int py) 
    {
        if (vmap[px][py] == 0) {
            std::stack <int> stk;

            stk.push(px);
            stk.push(py);

            int x = px;
            int y = py;

            while (true) {
                y = stk.top();
                stk.pop();
                x = stk.top();
                stk.pop();


                if (vmap[x][y + 1] == FILD && cop[x][y + 1] != CLICKED_CELL ) {
                    stk.push(x);
                    stk.push(y + 1);
                }
                cop[x][y + 1] = CLICKED_CELL;

                if (vmap[x][y - 1] == FILD && cop[x][y - 1] != CLICKED_CELL) {
                    stk.push(x);
                    stk.push(y - 1);
                }
                cop[x][y - 1] = CLICKED_CELL;

                if (vmap[x + 1][y] == FILD && cop[x + 1][y] != CLICKED_CELL) {
                    stk.push(x + 1);
                    stk.push(y);
                }
                cop[x + 1][y] = CLICKED_CELL;

                if (vmap[x - 1][y] == FILD && cop[x - 1][y] != CLICKED_CELL) {
                    stk.push(x - 1);
                    stk.push(y);
                }
                cop[x - 1][y] = CLICKED_CELL;

                if (vmap[x + 1][y + 1] == FILD && cop[x + 1][y + 1] != CLICKED_CELL) {
                    stk.push(x + 1);
                    stk.push(y + 1);
                }
                cop[x + 1][y + 1] = CLICKED_CELL;

                if (vmap[x + 1][y - 1] == FILD && cop[x + 1][y - 1] != CLICKED_CELL) {
                    stk.push(x + 1);
                    stk.push(y - 1);
                }
                cop[x + 1][y - 1] = CLICKED_CELL;

                if (vmap[x - 1][y + 1] == FILD && cop[x - 1][y + 1] != CLICKED_CELL) {
                    stk.push(x - 1);
                    stk.push(y + 1);
                }
                cop[x - 1][y + 1] = CLICKED_CELL;

                if (vmap[x - 1][y - 1] == FILD && cop[x - 1][y - 1] != CLICKED_CELL) {
                    stk.push(x - 1);
                    stk.push(y - 1);
                }
                cop[x - 1][y - 1] = CLICKED_CELL;



                if (stk.empty())
                    break;


            }

            show();
        }
    }

    // вектор нужный для метота proverka
    void ccoopp() {
        cop = vmap;
    }

    //проверка на открытие всех обычные игровых клеток
    bool proverka()
    {
        for (int i = 1; i < size - 1; ++i) {
            for (int k = 1; k < size - 1; ++k) {

                if (cop[k][i] != MINA && cop[k][i] != CLICKED_CELL) {
                    return false;
                }
                if (k == size-2 && i == size-2) {
                    return true;
                }

                   
            }
        }

    }

};


class Keyboard
{
private:
    int ch = 0;

public:
    Keyboard()
    {
        ch = 0;
    }

    //переменная берет значение нажатой клавиши
    void waitKey() {
        ch = _getch();
    }

    int getKey() {
        return ch;
    }
};


class Cursor {
private:
    int x = 1;
    int y = 1;

public:

    void checkBorder() {
        Map timeobj;

        // ограничения курсора для выхода за правый край поля
        if (x > timeobj.SizeMap() - 2)
            x--;

        // ограничения курсора для выхода за левый край поля
        if (x < 1)
            x++;

        // ограничения курсора для выхода за нижний край поля
        if (y > timeobj.SizeMap() - 2)
            y--;

        // ограничения курсора для выхода за верхний край поля
        if (y < 1)
            y++;
    }
    //инкремент х
    void incX() {
        x++;
    }
    //декремент х
    void decX() {
        x--;
    }

    //инкремент у
    void incY() {
        y++;
    }
    //декремент у
    void decY() {
        y--;
    }

    int getX() {
        return x;
    }
    int getY() {
        return y;
    }

    //передвежение курсора
    void move() {
        gotoxy(x, y);
    }

};


class Game
{
private:

    // вывод логотипа игры
    void Logotip()
    {
        gotoxy(60, 10);
        std::cout << "Saper" << std::endl;
        Sleep(1000);
        system("cls");
    }

    void game_over()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);
        gotoxy(60, 10);
        std::cout << "Game over" << std::endl;
        Sleep(2000);
    }

    void victory()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);
        gotoxy(60, 10);
        std::cout << "victory" << std::endl;
        Sleep(2000);
    }

public:

    void run()
    {
        Logotip();


        //std::cout << "start" << std::endl;
        Map karta;
        karta.initmap();// базовое создание поля
        karta.setRandMin(10);//количество мин
        karta.numFild();//нумерация клето от количества мин вокруг
        karta.ccoopp();//копирование поля для чернового вектора
        karta.show();//вывод поля в начале игры
        //karta.output_developer();//вывод для разработчика

        Keyboard kb;

        Cursor cs;

        cs.move();//передвежение курсора

        bool exite = true;

        while (exite) {
            kb.waitKey();

            switch (kb.getKey()) {
            case 77: cs.incX(); break; //вправо
            case 80: cs.incY(); break; //вниз
            case 75: cs.decX(); break; //влево
            case 72: cs.decY(); break; //вверх
            case 13://нажатие на клетку
                if (!karta.outp(cs.getX(), cs.getY()))//если наткнулись на мину
                {
                    game_over();
                    exite = false;
                }
                if (karta.proverka())//всели безопасные клектки кликнуты
                {
                    victory();
                    exite = false;
                }

                break;
            }

            cs.checkBorder();//проверка на выход за границы

            cs.move();//передвижение курсора 
        }
    }

};

int main()
{
    srand(time(0));//для рандомного расположения мин
    Game game;
    game.run();//запукс 
}
