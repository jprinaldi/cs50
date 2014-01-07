#include <cs50.h>
#include <stdio.h>

void drawPyramids(int pyramid_height);
void drawFloors(int floor_width, int pyramid_height);

int main(void)
{
    int pyramid_height;
    
    do {
        printf("Height: ");
        pyramid_height = GetInt();
    } while (pyramid_height < 0 || pyramid_height > 23);
    
    drawPyramids(pyramid_height);    
}

void drawPyramids(int pyramid_height)
{
    for(int floor_width = 1; floor_width <= pyramid_height; floor_width++)
        drawFloors(floor_width, pyramid_height);
}

void drawFloors(int floor_width, int pyramid_height)
{
    int i;
    
    // Draw empty space
    for (i = 0; i < pyramid_height-floor_width; i++)
        printf(" ");
        
    // Draw first pyramid floor
    for (i = 0; i < floor_width; i++)
        printf("#");
        
    // Draw gap
    printf("  ");
    
    // Draw second pyramid floor
    for (i = 0; i < floor_width; i++)
        printf("#");
        
    printf("\n");
}
