#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 9
#define ESC "\x1b"
#define CURSORMOVENUP    ESC"[%dA"
#define CURSORMOVENDOWN  ESC"[%dB"
#define CURSORMOVENRIGHT ESC"[%dC"
#define CURSORMOVENLEFT  ESC"[%dD"
#define DELETELINEECURSOR      ESC"[2K"
#define CLEARDISPLAY  ESC"[H"ESC"[2J"
//#define RANDOM1 rand()%9+1
//#define RANDOM2 rand()%9+1



void Printmap0(int c[][10]){
int x,y;

    printf(" \x1b[31mx\x1b[0m");
        for (x = 1; x <= NUM; x++){
        printf( "%2d|", x);
}        
        printf( "\n");

        printf("\x1b[31my\x1b[0m+----------------------------+\n");
        for (y = 1; y <= NUM; y++) {
            printf("%d|", y);

            for (x = 1; x <= NUM; x++) {
                if (c[y][x] >= 0) {
                    switch(c[y][x]){
                        case 0:
                        printf(" \x1b[34m%d\x1b[0m|",c[y][x]);
                        break;
                        case 1:
                        printf(" \x1b[32m%d\x1b[0m|",c[y][x]);
                        break;
                        case 2:
                        printf(" \x1b[31m%d\x1b[0m|",c[y][x]);
                        break;
                        case 3:
                        printf(" \x1b[33m%d\x1b[0m|",c[y][x]);
                        break;
                        case 4:
                        printf(" \x1b[35m%d\x1b[0m|",c[y][x]);
                        break;
                        case 5:
                        printf(" \x1b[36m%d\x1b[0m|",c[y][x]);
                        break;
                        default:
                        printf(" %d|",c[y][x]);

                    }
                    
                } else {
                    printf("  |");
                }
            }
            printf("\n");
        }
        printf(" +----------------------------+\n");
        printf("\033[s");
        printf(CURSORMOVENUP, 11);
        printf(CURSORMOVENRIGHT, 40);
        printf("\x1b[31m[ルール]\x1b[0m");
        printf("\033[u");
        printf(CURSORMOVENUP, 10);
        printf(CURSORMOVENRIGHT, 40);
        printf("・開けたマスの数字は周囲8マスの爆弾の数を表しています\n\n");
        printf("\033[u");
        printf(CURSORMOVENUP, 8);
        printf(CURSORMOVENRIGHT, 100);
        printf("| | | |");
        printf("\033[u");
        printf(CURSORMOVENUP, 7);
        printf(CURSORMOVENRIGHT, 100);
        printf("| |\x1b[31m2\x1b[0m| |");
        printf("\033[u");
        printf(CURSORMOVENUP, 6);
        printf(CURSORMOVENRIGHT, 100);
        printf("| | | |");
        printf("\033[u");
        printf(CURSORMOVENUP, 7);
        printf(CURSORMOVENRIGHT, 40);
        printf("右の場合周囲８マスのどこかに爆弾が\x1b[31m2つ\x1b[0mあります");
        printf("\033[u");
        printf(CURSORMOVENUP, 5);
        printf(CURSORMOVENRIGHT, 40);
        printf("・爆弾は合計\x1b[31m10個\x1b[0mあります");
        printf("\033[u");
        printf(CURSORMOVENUP, 4);
        printf(CURSORMOVENRIGHT, 40);
        printf("・\x1b[31m爆弾以外のすべてのマス\x1b[0mを先に開けたplayerの勝ちです\n\n");
        printf("\033[u");
        

}


void Init_map0(int c[][10]){
    int x,y;
    /* 配列を初期化する部分 */
    for (x = 0; x <= 9; x++) {
        for (y = 0; y <= 9; y++) {
            c[y][x] = -1;
        }
    }
    for (int i = 0; i<=9; i++){
        x = rand()%9+1;
        y = rand()%9+1;
        c[y][x] = -2;}

    //Printmap0(c);
}









int main(void){
	    int  i, j;
    char c;
    int counter = 0;
    int bomb;
    int xp,yp=0;
    int map0[10][10];

Init_map0(map0);
printf( CLEARDISPLAY);

/* ゲーム開始 */
while (1) {
    
    while (1){
        /*現在の盤面を表示する関数*/
        Printmap0(map0);
        /* プレーヤーが場所を入力 */
        counter ++;
        printf("場所を入力してください (x y) [%d 回目]:\n", counter);
        printf( "x=");
        scanf("%d", &xp );
        //printf( "%d\n", xp);
        printf( "y=");
        scanf("%d", &yp );
        //printf( "%d\n", yp);
        

        /*bomb発見 */
        if (map0[yp][xp] == -2)
            break;
        /* 指定場所の周囲の爆弾の数を確認 */
        bomb = 0;
        if (map0[yp - 1][xp] == -2)
            bomb ++;
        if (map0[yp + 1][xp] == -2)
            bomb ++;
        if (map0[yp][xp - 1] == -2)
            bomb ++;
        if (map0[yp][xp + 1] == -2)
            bomb ++;
        if (map0[yp - 1][xp - 1] == -2)
            bomb ++;
        if (map0[yp + 1][xp + 1] == -2)
            bomb ++;
        if (map0[yp + 1][xp - 1] == -2)
            bomb ++;
        if (map0[yp - 1][xp + 1] == -2)
            bomb ++;

        map0[yp][xp] = bomb;
        /* 画面更新　*/
        printf( CURSORMOVENUP, 2);
        printf(DELETELINEECURSOR );
        printf( CURSORMOVENDOWN, 1);
        printf(DELETELINEECURSOR );
        printf(CURSORMOVENUP, 14);
    }
    /* 爆弾を踏んだときの処理　*/
    printf( "bomb ! ゲームオーバーです\n");
    for (j = 0; j < 500000; j++); //出力を１秒ほど残す
    /* 画面更新　*/
    printf(CURSORMOVENUP, 3);
    printf(DELETELINEECURSOR );
    printf(CURSORMOVENDOWN, 1);
    printf(DELETELINEECURSOR );
    printf(CURSORMOVENDOWN, 1);
    printf(DELETELINEECURSOR );
    printf(CURSORMOVENUP, 15);
    counter = 0;
    Init_map0(map0);
    

}
return 0;
}    
    


