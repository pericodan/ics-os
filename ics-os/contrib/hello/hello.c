
#include "../../sdk/dexsdk.h"

int main() 
{
	char a[60];
   printf("Hello World from ICS-OS!\n");
   printf("Doing division by zero!");
   fgets(a, 60, NULL);
   printf("%s", a);
   printf("%f",100.0/0);
   return 0;
}
