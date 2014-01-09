#include <cs50.h>
#include <stdio.h>

void drawPyramid(int pyramid_height);
void drawFloor(int floor_width, int pyramid_height);

int main(void)
{
    int pyramid_height;

    do {
        printf("Height: ");
        pyramid_height = GetInt();
    } while (pyramid_height < 0 || pyramid_height > 23);

    drawPyramid(pyramid_height);    
}

void drawPyramid(int pyramid_height)
{
    // Here we use the fact that the bottom floor width is equal to the pyramid height plus 1
    for(int floor_width = 2; floor_width <= pyramid_height+1; floor_width++)
        drawFloor(floor_width, pyramid_height);
}

void drawFloor(int floor_width, int pyramid_height)
{
    int i;

    // Draw empty space
    for (i = 0; i <= pyramid_height-floor_width; i++)
        printf(" ");

    // Draw floor
    for (i = 0; i < floor_width; i++)
        printf("#");

    printf("\n");
}
