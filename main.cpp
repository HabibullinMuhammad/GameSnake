#include "TXLib.h"

  struct Snake
{
   int x;
   int y;
   int vx;
   int vy;
   bool visible;
};

struct Apple
{
   int x;
   int y;
   HDC pic;
   bool visible;
};

void drawSnake(Snake snake)
{
    txSetFillColor(RGB(0,38,0));
    txCircle(snake.x,snake.y,15);
}

void drawApple(Apple apple)
{
    if(apple.visible)
    txTransparentBlt(txDC(), apple.x, apple.y, 50, 50, apple.pic, 0, 0, TX_WHITE);
}

int main()
{
    txCreateWindow (1500, 800);

    txDisableAutoPause();

    txSetColor (TX_WHITE,3);
    txSetFillColor (TX_RED);

    char score[100];
    HDC Fon = txLoadImage("Pictures/fon.bmp");
    HDC Background = txLoadImage("Pictures/background.bmp");

    int level=1;

    //переменные Змейки
    int speed=15;
    int kol=5;
    int oldSnakeX = 0, oldSnakeY = 0;
    bool reBack;
    Snake snake[10000];
    snake[0].x=500;
    snake[0].y=300;



    //змейка - массив
    for(int i=0; i<kol; i++)
    {
      snake[i] = {snake[0].x+(i*15), snake[0].y, -speed, 0};
    }
    //добыча
    Apple apple = {500, 100, txLoadImage("Pictures/apple.bmp"), true};

    string PAGE = "Меню";



while(true)
{
    txClear();

    if(PAGE=="Меню")
    {
        txSetColor(TX_WHITE);
        txSetFillColor(TX_BLACK);
        txSelectFont("Times", 40);

        txBitBlt(txDC(), 0, 0, 1500, 800, Fon);

        txRectangle (600, 300, 800, 350);
        txDrawText (600, 300, 800, 350 ,  "START");

         if( txMouseX() >= 600 &&
             txMouseY() >= 300 &&
             txMouseX() <= 800 &&
             txMouseY() <= 350 &&
             txMouseButtons() == 1)
             {
               PAGE="Игра";
             }




        txRectangle (600, 500, 800, 550);
        txDrawText (600, 500, 800, 550 ,  "HELP");

         if( txMouseX() >= 600 &&
             txMouseY() >= 500 &&
             txMouseX() <= 800 &&
             txMouseY() <= 550 &&
             txMouseButtons() == 1)
             {
               PAGE="info";
             }

        txRectangle (600, 400, 800, 450);
        txDrawText (600, 400, 800, 450 ,  "EXIT");

         if( txMouseX() >= 600 &&
             txMouseY() >= 400 &&
             txMouseX() <= 800 &&
             txMouseY() <= 450 &&
             txMouseButtons() == 1)
             {
               return 0;
             }


    }

   if(PAGE=="info")
   {
        txSelectFont("Times", 40);
        txBitBlt(txDC(), 0, 0, 1500, 800, Fon);
       txRectangle(50,50,250,100);
       txDrawText(50,50,250,100,"НАЗАД");
       if(txMouseX() >= 50 && txMouseY()>=50 &&
          txMouseX() <= 250 && txMouseY()<=100 &&
          txMouseButtons() == 1)
          {
              PAGE="Меню";
          }
          txSelectFont("Arial", 60);
          txDrawText(0,0,1500,800,"Игра\n"
          "\n"
          "Змейка"
          "\n"
          "\n"
          "Управление: \n"
          "Cтрелками\n"
          "\n"
          "ЦЕЛЬ ИГРЫ\n"
          "\n"
          "Пройти все уровни\n"


         );


  }

    if(PAGE=="Игра")
    {
        if(GetAsyncKeyState (VK_ESCAPE))
        {
             PAGE="Меню";
        }

        txBegin();
        txBitBlt(txDC(), 0, 0, 1500, 800, Background);
        //Рисование змейки
        for(int i=0; i<kol; i++)
        {
            drawSnake(snake[i]);
        }

        reBack = false;
        oldSnakeX = snake[0].x;
        oldSnakeY = snake[0].y;

        //Рисование добычи
        drawApple(apple);

        if( snake[0].x>apple.x &&
            snake[0].x<apple.x+50 &&
            snake[0].y>apple.y &&
            snake[0].y<apple.y+50)
        {
             apple.visible=false;
             kol++;
             apple.x=random(50,1150);
             apple.y=random(50,550);

        }
           apple.visible=true;

        //Движение змейки
        for(int i=kol;  i>0; i--)
            {
                snake[i].x=snake[i-1].x;
                snake[i].y=snake[i-1].y;
            }

            snake[0].x=snake[0].x+snake[0].vx;
            snake[0].y=snake[0].y+snake[0].vy;



        //Управление змейкой
        if(GetAsyncKeyState (VK_RIGHT))
        {
            snake[0].vx=speed;
            snake[0].vy=0;
        }
        else if(GetAsyncKeyState (VK_LEFT))
        {
            snake[0].vx=-speed;
            snake[0].vy=0;
        }
        else if(GetAsyncKeyState (VK_UP))
        {
            snake[0].vx=0;
            snake[0].vy=-speed;
        }
        else if(GetAsyncKeyState (VK_DOWN))
        {
            snake[0].vx=0;
            snake[0].vy=speed;
        }

        for(int x=snake[0].x; x<snake[0].x+20; x=x+5)
        {
            for(int y=snake[0].y; y<snake[0].y+20; y=y+5)
            {
                if (txGetPixel(x, y) == RGB(255,242,0))
                {
                    reBack = true;
                }
            }
        }

        if(reBack)
        {
            txSetFillColor(TX_RED);
            txRectangle(650, 350, 850, 450);
            txDrawText(650, 350, 850, 450, "GAME OVER");
            txSleep(2000);
            PAGE = "Меню";
        }


        if(kol>5+5 && speed==15)
        {
            level++;
        }

        if(level == 2)
        {
          speed=30;
        }

        txSelectFont("Times", 40);
        sprintf(score, "Счет игры - %d ", kol-5);
        txTextOut(1250, 5, score);
        sprintf(score, "Уровень - %d ", level);
        txTextOut(1050, 5, score);

        txEnd();

    }
    txSleep(50);
    }

    txDeleteDC(Background);
    txDeleteDC(apple.pic);
    txDeleteDC(Fon);



return 0;
}
