#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

#define up_key 'w'
#define down_key 's'
#define right_key 'd'
#define left_key 'a'

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


/*
    "Erases" the screen given the starting point and the width & height
    (from the blacjack application in the ics-os)
*/
void erase(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,color);
}

void drawMenu(){
    write_text("SUNGKA",41,41,WHITE,1);

    write_text("[Enter]Start",40,120,WHITE,0); 
	write_text("[Esc]Quit",40,140,WHITE,0);
	write_text("[i]Instructions", 40, 160, WHITE, 0);
}

main(){

    set_graphics(VGA_320X200X256);
    erase(0,0,320,220, BLACK);
    drawMenu();
}
