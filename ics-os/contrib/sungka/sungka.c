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

char player1_name[50] = "player1";
char player2_name[50] = "player2";
int player1_current = 1;
int player2_current = 15;
int game_number = 1;

int items[16] = {0, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7};
//int items[16] = {57, 1, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0};

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

    write_text("[Enter] Start",40,120,WHITE,0);
	write_text("[Esc] Quit",40,140,WHITE,0);
	write_text("[i] Instructions", 40, 160, WHITE, 0);
}
/*
void getNames(){ //with maximum dapat
    int index=41;
    char temp;
    char temp2[10];

    drawRectangle(0,0,320,220, BLACK);
    write_text("Enter name of player 1",41,41,WHITE,1);
    write_text("Press Enter to proceed",41,100,WHITE,0);


    for(index=41;index<320;index+=10){
        temp = getchar();
        sprintf(temp2, "%c", temp);
        write_text(temp2,index,61,WHITE,0);
    }

    drawRectangle(0,0,320,220, BLACK);
    write_text("Enter name of player 2",41,41,WHITE,1);


}
*/
void drawBoard(){
    int x, z;
    char temp[1];
    //drawRectangle(0,0,320,220, BLACK);

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
        sprintf(temp, "%d", items[(16-(x-4)/35)]);
        write_text(temp,x+8,105,WHITE,0);

    }

    drawRectangle(285,70,30,20, DARK_BROWN);
    sprintf(temp, "%d", items[8]);
    write_text(temp,293,75,WHITE,0);

}

void drawInvertedTriangle(int x, int y, int w, int h, int color){
    int i,j;
    for (i=y;i<=(y+h);i++)
       for (j=x+i-y;j<=(x+w)-i+y;j++)
          write_pixel(j,i,color);
}

void printTurn(int turn){
    char temp[100];
    drawRectangle(60, 70, 225, 20, BLACK);
    if(turn==1)
        strcpy(temp, player1_name);
    else
        strcpy(temp, player2_name);
    strcat(temp, "'s turn");
    write_text(temp,60,70,WHITE,0);
}

int moveItems(int player){
    int index;
    int item;
    if(player==1){
        item = items[player1_current];
        items[player1_current] = 0;
        drawBoard();
        highlight(player1_current);
        for(index=player1_current-1; item>0; index--){
            index = (index+16) % 16;
            if(items[index]==-1){}
            else if(index!=8){
                item--;
                items[index] = items[index] + 1;
                if(item!=0){
                    delay(10);
                    drawBoard();
                    highlight(index);
                }
                else if(item==0 && index==0){
                    delay(10);
                    drawBoard();
                    return 1; //the turn does not end
                }
                else if(item==0 && items[index]>1){
                    delay(10);
                    drawBoard();
                    item = items[index];
                    items[index] = 0;
                    delay(10);
                    drawBoard();
                    highlight(index);
                }
                else if(item==0 && index>=9 && index<16){
                    delay(10);
                    drawBoard();
                    return 0; //end of turn
                }
                else if(item==0){
                    delay(10);
                    drawBoard();
                    highlight(index);
                    items[index] = 0;
                    if(items[index+((8-index)*2)]!=-1){
                        item = items[index+((8-index)*2)] + 1;
                        items[index+((8-index)*2)] = 0;
                        delay(10);
                        drawBoard();
                        highlight(index+((8-index)*2));
                        items[0] = item + items[0];
                        delay(10);
                        drawBoard();
                        highlight(0);
                        delay(10);
                        drawBoard();
                    }
                    else{
                        items[0] = 1 + items[0];
                    }
                    delay(10);
                    drawBoard();
                    return 0; // end of turn
                }
            }
        }
    }

    if(player==2){
        item = items[player2_current];
        items[player2_current] = 0;
        drawBoard();
        highlight(player2_current);
        for(index=player2_current-1; item>0; index--){
            index = (index+16) % 16;
            if(items[index]==-1){}
            else if(index!=0){
                item--;
                items[index] = items[index] + 1;
                if(item!=0){
                    delay(10);
                    drawBoard();
                    highlight(index);
                }
                else if(item==0 && index==8){
                    delay(10);
                    drawBoard();
                    return 1; //the turn does not end
                }
                else if(item==0 && items[index]>1){
                    delay(10);
                    drawBoard();
                    item = items[index];
                    items[index] = 0;
                    delay(10);
                    drawBoard();
                    highlight(index);
                }
                else if(item==0 && index>0 && index<8){
                    delay(10);
                    drawBoard();
                    return 0; //end of turn
                }
                else if(item==0){
                    delay(10);
                    drawBoard();
                    highlight(index);
                    items[index] = 0;
                    if(items[index+((8-index)*2)]!=-1){
                        item = items[index+((8-index)*2)] + 1;
                        items[index+((8-index)*2)] = 0;
                        delay(10);
                        drawBoard();
                        highlight(index+((8-index)*2));
                        items[8] = item + items[8];
                        delay(10);
                        drawBoard();
                        highlight(8);
                        delay(10);
                        drawBoard();
                    }
                    else{
                        items[8] = 1 + items[8];
                    }
                    delay(10);
                    drawBoard();
                    return 0; // end of turn
                }
            }
        }
    }
}

int checkIfFinish(){
    int i=0;
    for(i=1; i<16; i++){
        if(i==8) continue;
        if(items[i]>0) return 1;
    }
    return -1;
}

int checkIfNotEmpty(int a){
    int b = a + 7;
    for(; a<b; a++){
        if(items[a]>0) return 1;
    }
    return 0;
}

void highlight(int a){
    char temp[1];
    if(a == 0){
        drawRectangle(4,70,30,20, FLESH);
        sprintf(temp, "%d", items[0]);
        write_text(temp,12,75,BLACK,0);
    }
    else if(a > 0 && a < 8){
        drawRectangle(a*35+4,40,30,20, FLESH);
        sprintf(temp, "%d", items[a]);
        write_text(temp,a*35+12,45,BLACK,0);
    }
    else if ( a == 8 ){
        drawRectangle(285,70,30,20, FLESH);
        sprintf(temp, "%d", items[8]);
        write_text(temp,293,75,BLACK,0);
    }
    else {
        drawRectangle(a*-35+564,100,30,20, FLESH);
        sprintf(temp, "%d", items[a]);
        write_text(temp,a*-35+572,105,BLACK,0);
    }
}

void startGame(){
    //int currentx = 49;
    int i=0;
    char pressed;
    //getNames();
    drawRectangle(0,0,320,220, BLACK);
    drawBoard();

    while(1){

        if(checkIfFinish()==-1){
            //prepare for the next round
            i=1;
            while(items[0]>=7 && i<8){
                items[i] = 7;
                items[0] = items[0] - 7;
                i++;
            }
            while(i<8){
                if(i==8) break;
                items[i]=-1;
                i++;
            }
            i=9;
            while(items[8]>=7 && i<16){
                items[i] = 7;
                items[8] = items[8] - 7;
                i++;
            }

            for(; i<16; i++){
                items[i]=-1;
            }

            drawBoard();
        }
        //player1 turns
        printTurn(1);
        drawInvertedTriangle((player1_current-1)*35+49, 30, 10, 20, WHITE);

        while(1){
            if (checkIfNotEmpty(1)==0) {
                drawRectangle((player1_current-1)*35+49, 30, 10, 8, BLACK);
                break;
            }
            pressed = getchar();
            if(pressed==left_key && player1_current!=1){
                drawRectangle((player1_current-1)*35+49, 30, 10, 8, BLACK);
                player1_current-=1;
                drawInvertedTriangle((player1_current-1)*35+49, 30, 10, 20, WHITE);
            }
            else if(pressed==right_key && player1_current!=7){
                drawRectangle((player1_current-1)*35+49, 30, 10, 8, BLACK);
                player1_current+=1;
                drawInvertedTriangle((player1_current-1)*35+49, 30, 10, 20, WHITE);
            }
            if(pressed==enter){
                if (moveItems(1)!=1){
                    drawRectangle(49, 30, 35*7, 8, BLACK);
                    break;
                }
            }
        }
        //player2 turns
        printTurn(2);
        drawInvertedTriangle((player2_current*-1+15)*35+49, 90, 10, 20, WHITE);
        while(1){
            if (checkIfNotEmpty(9)==0) {
                drawRectangle((player2_current*-1+15)*35+49, 90, 10, 8, BLACK);
                break;
            }
            pressed = getchar();
            if(pressed==left_key && player2_current!=15){
                drawRectangle((player2_current*-1+15)*35+49, 90, 10, 8, BLACK);
                player2_current+=1;
                drawInvertedTriangle((player2_current*-1+15)*35+49, 90, 10, 20, WHITE);
            }
            else if(pressed==right_key && player2_current!=9){
                drawRectangle((player2_current*-1+15)*35+49, 90, 10, 8, BLACK);
                player2_current-=1;
                drawInvertedTriangle((player2_current*-1+15)*35+49, 90, 10, 20, WHITE);
            }
            if(pressed==enter){
                if (moveItems(2)!=1){
                    drawRectangle(49, 90, 35*7, 8, BLACK);
                    break;
                }
            }
        }
    }
}

main(){
    char pressed;
    set_graphics(VGA_320X200X256);
    drawMenu();


    do{
        pressed = (char)getch();
        if(pressed==enter){
            startGame();
        }
        else if(pressed=='i'){
            //instruction();
        }
    }while(pressed!=quit);
    //Return ICS-OS graphics before exiting
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
	exit(0);
}
