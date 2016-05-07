#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

#define up_key 'w'
#define down_key 's'
#define right_key 'd'
#define left_key 'a'
#define enter '\n'
#define quit 27


#define YELLOW 54
#define GRAY 56
#define WHITE 63
#define BROWN 20
#define VIOLET 40
#define RED 36
#define GREEN 18
#define BLUE 9
#define ORANGE 38
#define MAROON 4
#define FLESH 55
#define BLACK 70
#define DARK_GREEN 16
#define DARK_BROWN 32

char player1[50];
char player2[50];

int items[16] = {0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0};

/*
    "Erases" the screen given the starting point and the width & height
    (from the blacjack application in the ics-os)
*/
void drawRectangle(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,color);
}

void drawMenu(){
    drawRectangle(0,0,320,220, BLACK);
    write_text("SUNGKA",41,41,WHITE,1);

    write_text("[Enter]Start",40,120,WHITE,0);
	write_text("[Esc]Quit",40,140,WHITE,0);
	write_text("[i]Instructions", 40, 160, WHITE, 0);
}

void getNames(){
/*    int i;
    char temp[50];

    drawRectangle(0,0,320,220, BLACK);
    write_text("Enter name of player 1",41,41,WHITE,1);
    write_text("Press Enter to proceed",41,100,WHITE,1);

    scanf("%s", temp);
    for(i=41;;i+=10){
        //fgets() how to fgets po
        write_text(temp+"",i,61,WHITE,0);
    }

    drawRectangle(0,0,320,220, BLACK);
    write_text("Enter name of player 2",41,41,WHITE,1);
*/

}

void drawBoard(){
    int x, z;
    char temp[1];
    drawRectangle(0,0,320,220, BLACK);

    drawRectangle(4,70,30,20, BROWN);
    sprintf(temp, "%d", items[0]);
    write_text(temp,12,75,WHITE,0);

    z=1;
    for(x=39; x<270; x+=35){
        drawRectangle(x,40,30,20, BROWN);
        sprintf(temp, "%d", items[(x-4)/35]);
        write_text(temp,x+8,45,WHITE,0);

    }

    z=8;
    for(x=39; x<270; x+=35){
        drawRectangle(x,100,30,20, DARK_BROWN);
        sprintf(temp, "%d", items[((x-4)/35)+7]);
        write_text(temp,x+8,105,WHITE,0);

    }

    drawRectangle(285,70,30,20, DARK_BROWN);
    sprintf(temp, "%d", items[15]);
    write_text(temp,293,75,WHITE,0);

}

void drawInvertedTriangle(int x, int y, int w, int h, int color){
    int i,j;
    for (i=y;i<=(y+h);i++)
       for (j=x+i-y;j<=(x+w)-i+y;j++)
          write_pixel(j,i,color);
}

void startGame(){
    int currentx = 49;
    char pressed;
    //getNames();
    drawBoard();

    //player1 turns
    drawInvertedTriangle(49, 30, 10, 20, WHITE);
    while(1){
        pressed = getchar();
        if(pressed==left_key && currentx!=49){
            drawRectangle(currentx, 30, 10, 8, BLACK);
            currentx-=35;
            drawInvertedTriangle(currentx, 30, 10, 20, WHITE);
        }
        else if(pressed==right_key && currentx!=259){
            drawRectangle(currentx, 30, 10, 8, BLACK);
            currentx+=35;
            drawInvertedTriangle(currentx, 30, 10, 20, WHITE);
        }
    }

}

main(){
    char pressed;
    set_graphics(VGA_320X200X256);
    drawMenu();

    pressed = (char)getch();
    //do{
        if(pressed==enter){
            startGame();
        }
        else if(pressed=='i'){
            //instruction();
        }
    //}while(pressed!=quit);

}
