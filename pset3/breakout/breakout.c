
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
// dimnesions of paddle
 
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
   
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);
    
    
    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
     // istansiate a cheering board
    GLabel label2 = newGLabel("BRAVO !!");
    add(window,label2);
    double z = ((getWidth(window) - getWidth(label2)) / 2) - 2;
  
    double u = ((getHeight(window) - getHeight(label2)) / 2) + 60;
    setLocation(label2,z,u); 
    setColor(label2,"RED");
    setFont(label2,"SansSerif-36"); 
    add(window,label2);
    setVisible(label2,0);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 50;

    // keep playing until game over
    double x;
    double velocityy = drand48(); 
    double velocityx = 2;
    waitForClick();
    while (lives > 0 && bricks > 0)
    { 
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        { 
            if (getEventType(event) == MOUSE_MOVED )
            {
                x = getX(event);
                setLocation(paddle,x,520);
            }
        }
        move(ball,velocityx,velocityy * 6);
        
        if (getY(ball) <= 0  )
        {
            velocityy = -velocityy;
        }
        else if( getX(ball) <= 0 || ( getX(ball) + (RADIUS * 2) >= getWidth(window)))
        {
            velocityx = -velocityx;
        }
      
      else if( getY(ball) + (RADIUS * 2) >= getHeight(window) )
        { 
            pause(10);
            lives--;
            if (lives != 0)
            {
                setLocation(label2,z - 140,u);
                setLabel(label2,"click to start again");
                setVisible(label2,1);
                waitForClick();
            }
            else
            { 
                setLocation(label2,z - 70,u); 
                setLabel(label2,"GAME OVER");    
            }
       
            setLocation(ball,198,300);
      }
        GObject object = detectCollision(window, ball);
        if (object != NULL )
        {
            if (strcmp(getType(object),"GRect") == 0)
            {
                if ( object == paddle )
                {
                    velocityy = -velocityy;
                    setVisible(label2,0);
                }
                else
                {
                    setLocation(label2,z,u);  
                    setLabel(label2,"BRAVO !!");
                    setVisible(label2,1);
                    removeGWindow(window,object);
                    bricks--;
                    points--;
                    updateScoreboard(window,label,points);
                    velocityy = -velocityy;  
                }
                 
                   
           }
        
        }
        
       
        pause(6);
        
        
    }
  
  
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{  
    GRect rec[ROWS][COLS];
    int brick_width=37;
    int brick_height=20;
    int xcord=0, ycord=0;
    for( int i = 0; i < ROWS;i++)
    { 
        xcord = 0;
        for(int c = 0;c < COLS;c++)
        { 
            rec[i][c] = newGRect(xcord,ycord,brick_width,brick_height);
            setColor(rec[i][c],"GRAY");
            setFilled(rec[i][c], true);
            add(window, rec[i][c]);
            xcord = xcord + brick_width + 3;
        }
          
        ycord = ycord + brick_height + 5;
         }
          
}
/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(198, 300, 20, 20);
    setColor(ball, "PINK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(150,520,PADDLE_WIDTH,PADDLE_HEIGHT);
    setColor(paddle, "PINK");
    setFilled(paddle, true);
    
    
    add(window,paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{   
    GLabel label = newGLabel("50");
    add(window,label);
    double x = (getWidth(window) - getWidth(label)) / 2;
  
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label,x,y); 
    setColor(label,"RED");
    setFont(label,"SansSerif-36");
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
