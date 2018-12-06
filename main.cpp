/*
 =========================================================
 * Pong++ Ball Physics Game With C & Borland Graphics Interface (Graphics.h) - v1.0
 =========================================================
 
 * Product Page:  http://umitaksoylu.space/pongplusplus/
 * Copyright 2018 Ümit AKSOYLU (http://www.umitaksoylu.space)
 * Licensed under CC BY-SA (https://github.com/Aksoylu/pong-/upload/master/licence.md)
 * More information about CC BY-SA Licence : https://creativecommons.org/licenses/
 =========================================================
 * Developer credits cannot be removed from "About" page of software
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 */

#include <iostream>
#include <graphics.h>
#include <math.h>
#include <time.h>


void brickssaga(),pvpsaga(),multisaga(),about(), gamemenu();
void bs_init_game(), bs_gameover(),bs_game();
void pv_game(),pv_init_game();
void about_controls(), gamemenu_controls();



int section = 0; 	//0: gamemenu, 1: bricks saga, 2:pvp, 3:pvpm, 4:about


//Game Menu

int gm_index =  1;

void gamemenu()
{
	settextstyle(0, HORIZ_DIR, 5);
	outtextxy(185, 100, "PONG++");
	settextstyle(0, HORIZ_DIR, 3);
	outtextxy(175, 200, "Bricks Saga");
	outtextxy(75, 250,  "Player versus Player");
	outtextxy(125, 300, "Play On Network");
	outtextxy(245, 350, "About");
	outtextxy(258, 400, "Exit");
	gamemenu_controls();
}

void gamemenu_controls()
{
		while(1)
       { 
       
	       	 	if(kbhit())
				{
				
					if(section == 0)
					{
						char ch;
					    ch = getch();
					    if(ch == KEY_UP)
					    {
					    	if(gm_index != 1)
					    	{
					    		gm_index = gm_index-1;
							}
					    	
						}
						else if(ch == KEY_DOWN)
						{
							if(gm_index != 5)
					    	{
					    		gm_index = gm_index+1;
							}
							
						}
						else if(ch == '\r')
						{
							if(gm_index == 5)
							{
								closegraph();
								exit(0);
							}
							else if(gm_index == 4)
							{
								about();
								break;
							}
							else if(gm_index == 3)
							{
								multisaga();
							}
							else if(gm_index == 1)
							{
								brickssaga();
								break;
							}
							else if(gm_index == 2)
							{
								pvpsaga();
								break;
							}
							
						}
					
					}
					else
					{
						break;
					}
			    
	  
				}
       
    
    	if(gm_index == 1)
    	{
    		
			
				settextstyle(0, HORIZ_DIR, 3);
				setcolor(4);
				outtextxy(175, 200, "Bricks Saga");
				setcolor(15);
				outtextxy(75, 250,  "Player versus Player");
				outtextxy(125, 300, "Play On Network");
				outtextxy(245, 350, "About");
				outtextxy(258, 400, "Exit");
    		
		}
		else if(gm_index == 2)
		{
			
		
				settextstyle(0, HORIZ_DIR, 3);
				outtextxy(175, 200, "Bricks Saga");
				setcolor(4);
				outtextxy(75, 250,  "Player versus Player");
				setcolor(15);
				outtextxy(125, 300, "Play On Network");
				outtextxy(245, 350, "About");
				outtextxy(258, 400, "Exit");
		}
		else if(gm_index == 3)
		{
			
	
				settextstyle(0, HORIZ_DIR, 3);
				outtextxy(175, 200, "Bricks Saga");				
				outtextxy(75, 250,  "Player versus Player");
				setcolor(4);
				outtextxy(125, 300, "Play On Network");
				setcolor(15);
				outtextxy(245, 350, "About");
				outtextxy(258, 400, "Exit");
		}
		else if(gm_index == 4)
		{
			
			
				settextstyle(0, HORIZ_DIR, 3);
				outtextxy(175, 200, "Bricks Saga");				
				outtextxy(75, 250,  "Player versus Player");
				outtextxy(125, 300, "Play On Network");
				setcolor(4);
				outtextxy(245, 350, "About");
				setcolor(15);
				outtextxy(258, 400, "Exit");
		}
		else if (gm_index ==5)
		{
				settextstyle(0, HORIZ_DIR, 5);
				outtextxy(185, 100, "PONG++");
				settextstyle(0, HORIZ_DIR, 3);
				outtextxy(175, 200, "Bricks Saga");				
				outtextxy(75, 250,  "Player versus Player");
				outtextxy(125, 300, "Play On Network");
				outtextxy(245, 350, "About");
				setcolor(4);
				outtextxy(258, 400, "Exit");
				setcolor(15);
			
		}
		        	
	
      
       
    }
}

	//Bricks Saga	[bs]

struct bs_brick_struct{

int start_x;
int end_x;
int start_y;
int end_y;
bool is_alive;	//0:dead 1:alive

};

bs_brick_struct bs_bricks[90];
	
int bs_ball_x = 300;			//ball's position as circle center (x)
int bs_ball_y = 425;			//ball's position as circle center (y)
int bs_ball_r = 10;				//ball's radius value
int bs_ball_speed_x = 3;		//ball's movement speed on x axis
int bs_ball_speed_y = 3;		//ball's movement speed on y axis

int bs_racket_s_x = 265;		//racket start x
int bs_racket_e_x = 335; 		//racket end x
int bs_racket_s_y = 435;		//racket start y
int bs_racket_e_y = 455;		//racket end y
int bs_racket_speed = 15;		//racket movement speed (controlled by user)

bool bs_time = false;			//time indicator of brick saga game mode

bool bs_flag_firsttime = true;	//if we start game from main menu, this value always true for first time
int bs_scoreboard_score = 0 ;	//integer value of play score

int bs_buffer_page = 0;			//Required for double buffering "anti-flickering" algorithm. (for mor knowledge : ÖYT computer graphics by umit aksoylu Lesson 5)


//this function must called from exit function. It returns all of variables to default values at starting.

void bs_flush()	
{
 bs_ball_x = 300;			//ball's position as circle center (x)
 bs_ball_y = 425;			//ball's position as circle center (y)
 bs_ball_r = 10;			//ball's radius value
 bs_ball_speed_x = 3;		//ball's movement speed on x axis
 bs_ball_speed_y = 3;		//ball's movement speed on y axis

 bs_racket_s_x = 265;		//racket start x
 bs_racket_e_x = 335; 		//racket end x
 bs_racket_s_y = 435;		//racket start y
 bs_racket_e_y = 455;		//racket end y
 bs_racket_speed = 10;		//racket movement speed (controlled by user)
 bs_scoreboard_score = 0 ;	//integer value of play score
 
 bs_flag_firsttime = true;	//if we start game from main menu, this value always true for first time
 
}

void bs_drawbricks()
{
	
	int i;
  	for(i = 0;i< 90;i++)
  	{
  		if(bs_bricks[i].is_alive == 1)
  		{
		  
  			bar(bs_bricks[i].start_x,bs_bricks[i].start_y,bs_bricks[i].end_x,bs_bricks[i].end_y);
	  	}
	}
  	
	


}

void bs_scoreboard()
{
	settextstyle(0, HORIZ_DIR, 2);
	char buffer [50];
	sprintf (buffer, "SCORE : %d", bs_scoreboard_score);
	
	outtextxy(10, 10, buffer );
	

	
	
}

//Easy collusion, no radius vectors

void bs_collusion()
{
	
	line(3,30,3,460);
	line(3,30,627,30);
	line(627,30,627,460);
	line(3,460,627,460);
	
	//if ball hit one of bricks
	int i;
	int flag_is_hit = 0;
	for(i = 0 ;i< 90;i++)
	{
		if(bs_bricks[i].is_alive == 1)
		{
			
			if( bs_ball_x >= bs_bricks[i].start_x && bs_ball_x <= bs_bricks[i].end_x &&
				bs_ball_y + bs_ball_r >= bs_bricks[i].start_y && bs_ball_y <= bs_bricks[i].end_y + bs_ball_r )
			{
				bs_bricks[i].is_alive = 0 ;
				bs_scoreboard_score++;
				flag_is_hit = 1;
				break;
			
			}
		}
		
	}
	
	if(flag_is_hit != 1)
	{

		//left wall : padding space from left = 3
		if(bs_ball_x <= 3 + bs_ball_r && (bs_ball_y >= 30 + bs_ball_r && bs_ball_y <= 460 + bs_ball_r))
		{
				bs_ball_speed_x *= -1;
	
		}
		//right wall : padding space from right = 3
		if(bs_ball_x + bs_ball_r >= 627  && (bs_ball_y >= 30 + bs_ball_r && bs_ball_y <= 460 + bs_ball_r))
		{
			bs_ball_speed_x *= -1;
		}
		//upper wall : padding space from top = 30
		if(bs_ball_y <= 30 + bs_ball_r && (bs_ball_x >= 3 + bs_ball_r && bs_ball_x <= 627 + bs_ball_r))
		{
			bs_ball_speed_y *= -1;
		}
		//downing area : if ball dont touch racket, we lose game
		if(bs_ball_y + bs_ball_r >= bs_racket_s_y && bs_ball_y <= bs_racket_e_y + bs_ball_r )
		{
			if(bs_ball_x + bs_ball_r >= bs_racket_s_x && bs_ball_x <= bs_racket_e_x + bs_ball_r)
			{
				bs_ball_speed_x =   bs_ball_speed_x;
				bs_ball_speed_y =  - bs_ball_speed_y;
			}
			else 
			{
				
				bs_gameover();
				
			
			}
		
		}
  	
	}
	else
	{
		bs_ball_speed_y *= -1;
	}

	
}

void bs_draw_ball()
{
	
	
	
		bs_ball_x -= bs_ball_speed_x;
		bs_ball_y-= bs_ball_speed_y;
		circle(bs_ball_x,bs_ball_y,bs_ball_r);
   		
		bs_collusion();
		
}

void bs_draw_racket()
{
	setfillstyle(SOLID_FILL, YELLOW);
   	bar(bs_racket_s_x,bs_racket_s_y,bs_racket_e_x,bs_racket_e_y);
	setfillstyle(SOLID_FILL, WHITE);	
}

void bs_gameover()
{
		setactivepage(bs_buffer_page);
	    setvisualpage(bs_buffer_page);
	while(1)
	{
		
	
		settextstyle(0, HORIZ_DIR, 5);
		setcolor(RED);
		outtextxy(140, 180, "GAME OVER");
		bs_ball_speed_x = 0 ;
		bs_ball_speed_y = 0 ;
		bs_racket_speed = 0 ;
		setcolor(WHITE);
		settextstyle(0, HORIZ_DIR, 3);
		outtextxy(60, 320, "Press [enter] to Exit");
		if(kbhit())
		{
			char ch;
			ch = getch();
		
			if(ch == '\r')
			{
				cleardevice();
				
				section = 0;	
				break;
			}
		}
	}
	
	if(section == 0)
	{
		setactivepage(bs_buffer_page);
		bs_flush();
		gamemenu();	
	}
	
		
}

void bs_finish()
{
		setactivepage(bs_buffer_page);
	    setvisualpage(bs_buffer_page);
	    
	    	while(1)
	{
	
		setcolor(WHITE);
		settextstyle(0, HORIZ_DIR, 5);
		outtextxy(10,200, "Congratulations");
		setcolor(GREEN);
		settextstyle(0, HORIZ_DIR, 3);
		outtextxy(220, 270, "You Win");
		setcolor(WHITE);
		outtextxy(60, 320, "Press [enter] to Exit");
	
		if(kbhit())
		{
			char ch;
			ch = getch();
		
			if(ch == '\r')
			{
				cleardevice();
				
				section = 0;	
				break;
			}
		}
		
				
		
	}
	
	if(section == 0)
	{
		setactivepage(bs_buffer_page);
		bs_flush();
		gamemenu();	
	}

}

void bs_pause()
{

		setactivepage(bs_buffer_page);
	    setvisualpage(bs_buffer_page);
	    
	    
	while(1)
	{
	
		setcolor(RED);
		settextstyle(0, HORIZ_DIR, 5);
		outtextxy(100, 200, "Game Paused");
		setcolor(WHITE);
		settextstyle(0, HORIZ_DIR, 3);
		outtextxy(20, 270, "Press [space] to Continue");
		outtextxy(60, 320, "Press [enter] to Exit");
	
		if(kbhit())
		{
			char ch;
			ch = getch();
			if(ch == ' ')
			{
				bs_time = true;
				break;
				
			}
			else if(ch == '\r')
			{
				cleardevice();
				
				section = 0;	
				break;
			}
		}
		
				
		
	}
	
	if(section == 0)
	{
		setactivepage(bs_buffer_page);
		bs_flush();
		gamemenu();	
	}
	else if(section == 1)
	{
		bs_game();
	}
	
}

void bs_game()
{	



		while(1)
       { 
           
           
	
	       	if(bs_time== true)
	      	 {
       			
       			if(bs_scoreboard_score == 90)
       			{
       				
       				bs_time = false;
       				break;
				}
       			
       			
	   
	       		setactivepage(bs_buffer_page);
	       		setvisualpage(1-bs_buffer_page);
	       		cleardevice();
	       	 	if(kbhit())
				{
						char ch;
					    ch = getch();
					
							if(ch == KEY_RIGHT) 
							{
								if(bs_racket_e_x >= 620)
								{
									
								}
								else
								{
								
								bs_racket_s_x+=bs_racket_speed;
							    bs_racket_e_x+=bs_racket_speed;
							    }
							}
							else if (ch == KEY_LEFT)
							{
								
								if(bs_racket_s_x <= 10)
								{
									
								}
								else
								{
								bs_racket_s_x=bs_racket_s_x-bs_racket_speed;
							    bs_racket_e_x=bs_racket_e_x-bs_racket_speed;  
								}
							
							}
							
							else if(ch == ' ')
							{
								
								bs_time = false;
								break;
							}
									
						
				}
				bs_scoreboard();
				bs_drawbricks();
       			bs_draw_ball();
       			bs_init_game();
				bs_draw_racket();	
				delay(3);	
				bs_buffer_page = 1- bs_buffer_page;		

				
			 }
		
		}
		
		if(bs_time == false)
		{
			if(bs_scoreboard_score == 90)
       		{
       			bs_finish();	
       			
			}
			else
			{
				bs_pause();
			}
			
		}
		

}

void bs_init_game()
{
	line(3,30,3,460);
	line(3,30,627,30);
	line(627,30,627,460);
	line(3,460,627,460);
}

void bs_init_bricks()
{
	int x_1 = 10;
	int x_2 = 70;
	int y_1 = 35;
	int y_2 = 45;  

  	int count = 0;
	for(int k=0;k<10;k++)
	{
		
		for(int i=0;i<9;i++)
		{
			x_1 = 25 + (i*5) + (i* 60);
			x_2 = 85 + (i*5) + (i* 60);
			
			y_1 = 35 + (k*5) + (k* 10);
			y_2 = 45 + (k*5) + (k* 10);
			
			bs_bricks[count].start_x  = x_1;
			bs_bricks[count].end_x  = x_2;
			bs_bricks[count].start_y  = y_1;
			bs_bricks[count].end_y  = y_2;
			bs_bricks[count].is_alive  = 1;
			count++;
		}	
	}
}

void brickssaga()
{
	cleardevice();
	
	if(bs_flag_firsttime)
	{
	
		srand(time(NULL));	
		int vector_code = (rand() % 2) + 1;	
		
		switch(vector_code)
		{
			case 1:
				bs_ball_speed_x = 3;
				bs_ball_speed_y = 3;				
				
			break;
				
			case 2:
				bs_ball_speed_x = -3;
				bs_ball_speed_y = 3;	
						
			break;
		}
		
		srand(time(NULL));
		
		int racket_random_start_pos_x = (rand() % 525) + 10;
		
		bs_racket_s_x = racket_random_start_pos_x;
		bs_racket_e_x = racket_random_start_pos_x + 70;
		
		bs_ball_x =  (bs_racket_s_x + bs_racket_e_x) / 2;
		
		srand(time(NULL));
		bs_flag_firsttime = false;
	}	
	//set racket position and ball vector with random variable
	
	bs_init_bricks();
	
	bs_drawbricks();
	bs_draw_racket();
	bs_draw_ball();
	bs_init_game();
	settextstyle(0, HORIZ_DIR, 3);
	outtextxy(50, 300, "Press [space] to Start");
	outtextxy(60, 350, "Press [enter] to Exit");
	
	
	while(1)
	{
		if(kbhit())
				{
						char ch;
					    ch = getch();
						if (ch == ' ')
						{
								bs_time = true;
								section = 1 ;
							    break;	
						}
						else if(ch == '\r')
						{
								section = 0 ;
								
								break;
								
							
						}
						
						
				}
				
	}
	cleardevice();
	if(section == 0 )
	{
		gamemenu();
	}
	else if(section == 1 && bs_time == true)
	{
		bs_game();
	}
	

	
}


	//PVP		[pvp]

	
int pv_ball_x = 310;				//ball's position as circle center (x)
int pv_ball_y = 235;				//ball's position as circle center (y)
int pv_ball_r = 10;					//ball's radius value
int pv_ball_speed_x = 0;			//ball's movement speed on x axis
int pv_ball_speed_y = 0;			//ball's movement speed on y axis

int pv_p1_racket_s_x = 5;			//racket start x for player 1 
int pv_p1_racket_e_x = 25; 			//racket end x for player 1
int pv_p1_racket_s_y = 200;			//racket start y for player 1
int pv_p1_racket_e_y = 270;			//racket end y for player 1
int pv_p1_racket_speed = 18;		//racket movement speed (controlled by user) for player 1

int pv_p2_racket_s_x = 605;			//racket start x
int pv_p2_racket_e_x = 625; 		//racket end x
int pv_p2_racket_s_y = 200;			//racket start y
int pv_p2_racket_e_y = 270;			//racket end y
int pv_p2_racket_speed = 18;		//racket movement speed (controlled by user)

bool pv_time = false;				//time variable for pvp game mode

int pv_p1_scoreboard_score = 0 ;	//Player1's score
int pv_p2_scoreboard_score = 0 ;	//Player2's score

bool flag_isfirst = true;

int score_winner_flag = 0 ; 		//1 for player 1 , 2 for player 2 , //0 for none

void pv_flush()	
{
 pv_ball_x = 310;					//ball's position as circle center (x)
 pv_ball_y = 235;					//ball's position as circle center (y)
 pv_ball_r = 10;					//ball's radius value
 pv_ball_speed_x = 0;				//ball's movement speed on x axis
 pv_ball_speed_y = 0;				//ball's movement speed on y axis
 
 // X1-x2 : 20, y1-y2 : 70	
 
 pv_p1_racket_s_x = 5;				//racket start x for player 1 
 pv_p1_racket_e_x = 25; 			//racket end x for player 1
 pv_p1_racket_s_y = 200;			//racket start y for player 1
 pv_p1_racket_e_y = 270;			//racket end y for player 1
 pv_p1_racket_speed = 17;			//racket movement speed (controlled by user) for player 1
 
 pv_p2_racket_s_x = 605;			//racket start x for player 2
 pv_p2_racket_e_x = 625; 			//racket end x for player 2
 pv_p2_racket_s_y = 200;			//racket start y for player 2
 pv_p2_racket_e_y = 270;			//racket end y for player 2
 pv_p2_racket_speed = 17;			//racket movement speed (controlled by user) for player 2
 
 pv_p1_scoreboard_score = 0 ;		//Player1's score
 pv_p2_scoreboard_score = 0 ;		//Player2's score
 
 flag_isfirst = true;
	
}

void pv_scoreboard()
{
	settextstyle(0, HORIZ_DIR, 2);
	char buffer_p1 [50];
	char buffer_p2 [50];
	sprintf (buffer_p1, "Player 1: %d", pv_p1_scoreboard_score);
	sprintf (buffer_p2, "Player 2: %d", pv_p2_scoreboard_score);
	outtextxy(10, 10, buffer_p1);
	outtextxy(440, 10, buffer_p2);
}

//Show announcement of score
void pv_score()
{
	int player = score_winner_flag;
	
	setactivepage(bs_buffer_page);
	setvisualpage(bs_buffer_page);
	
	int busy_waiting = 0 ; 	
	
	if(pv_p1_scoreboard_score == 5 || pv_p2_scoreboard_score == 5)
	{
		if(player == 1)
		{
			pv_p1_scoreboard_score++;
		}
		else
		{
			pv_p2_scoreboard_score++;
		}
		pv_time = true;
		pv_game();
	}
	else
	{
	
	
		if(player == 1)
		{
			setcolor(RED);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(75, 200, "Player 1 Scores!");
			pv_p1_scoreboard_score++;
		}
		else
		{
			setcolor(BLUE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(75, 200, "Player 2 Scores!");
			pv_p2_scoreboard_score++;
		}
		
		setcolor(WHITE);	
		
		outtextxy(300, 250, "3");
		delay(1000);
		outtextxy(300, 250, "2");
		delay(1000);		
		outtextxy(300, 250, "1");
		delay(1000);
			
		pv_ball_x = 310;
		pv_ball_y = 225;
		score_winner_flag = 0;
		pv_time = true;
		pv_game();
	}
	
}

//Mid collusion, 2 radius and vectors
void pv_collusion()
{
	
 
		//left wall : padding space from left = 3, p1 lose - p2 scores 
		if(pv_ball_x  + pv_ball_r <= 20 && (pv_ball_y >= 30 + pv_ball_r && pv_ball_y <= 460 + pv_ball_r))
		{		
			score_winner_flag = 2;
			pv_time = false;
	
		}
		//right wall : padding space from right = 3 p2 lose, p1 scores
		if(pv_ball_x + pv_ball_r >= 635  && (pv_ball_y >= 30 + pv_ball_r && pv_ball_y <= 460 + pv_ball_r))
		{
			score_winner_flag = 1;
			pv_time = false;
		}
		//upper wall : padding space from top = 30
		if(pv_ball_y <= 30 + pv_ball_r && (pv_ball_x >= 3 + pv_ball_r && pv_ball_x <= 627 + pv_ball_r))
		{
			pv_ball_speed_y *= -1;
		}
		//bottom wall: padding y at 500
		if(pv_ball_y + pv_ball_r >= 450  && (pv_ball_x >= 3 + pv_ball_r && pv_ball_x <= 627 + pv_ball_r))
		{
			pv_ball_speed_y *= -1;
		}		
	
		
		//Collusion detection for player 1's racket
		if(pv_ball_x - pv_ball_r - 3<= pv_p1_racket_e_x && pv_ball_y + pv_ball_r >= pv_p1_racket_s_y - 3 )
		{
			if (pv_ball_y >= pv_p1_racket_s_y && pv_ball_y <= pv_p1_racket_s_y + 35 )
			{
				if(pv_ball_speed_x == 5)
				{
					pv_ball_speed_x = -4;
					pv_ball_speed_y = 4;	
				}
				else
				{
					pv_ball_speed_x *= -1;
				}
					
			}
			else if(pv_ball_y > pv_p1_racket_s_y + 35 && pv_ball_y <= pv_p1_racket_s_y + 70 + 3 )
			{
				if(pv_ball_speed_x == 5)
				{
					pv_ball_speed_x = -4;
					pv_ball_speed_y = -4;	
				}
				else
				{
					pv_ball_speed_x *= -1;
				}
				
			}
				
		}
		
		//Collusion detection for player 2's racket
		if(pv_ball_x + pv_ball_r + 3 >= pv_p2_racket_s_x && pv_ball_y + pv_ball_r >= pv_p2_racket_s_y - 3)
		{
				
			if(pv_ball_y >= pv_p2_racket_s_y && pv_ball_y <= pv_p2_racket_s_y + 35 )
			{
				if(pv_ball_speed_x == -5)
				{
					pv_ball_speed_x = 4;
					pv_ball_speed_y = 4;
				}
				else
				{
					pv_ball_speed_x *= -1;
					
				}
			
			}
			else if(pv_ball_y > pv_p2_racket_s_y + 35 && pv_ball_y <= pv_p2_racket_s_y + 70 + 3 )
			{
				if(pv_ball_speed_x == -5)
				{
					pv_ball_speed_x = 4;
					pv_ball_speed_y = -4;	
				}
				else
				{
					pv_ball_speed_x *= -1;
				}
	
			}	
	
		}
		
		
	
		
		
		
	
}

void pv_draw_ball()
{
	
	
	
		pv_ball_x -= pv_ball_speed_x;
		pv_ball_y-= pv_ball_speed_y;
		circle(pv_ball_x,pv_ball_y,pv_ball_r);
   		
		pv_collusion();
		
}

void pv_draw_rackets()
{
	setfillstyle(SOLID_FILL, RED);
   	bar(pv_p1_racket_s_x,pv_p1_racket_s_y,pv_p1_racket_e_x,pv_p1_racket_e_y);
   	
   	setfillstyle(SOLID_FILL, BLUE);
   	bar(pv_p2_racket_s_x,pv_p2_racket_s_y,pv_p2_racket_e_x,pv_p2_racket_e_y);
   	
	setfillstyle(SOLID_FILL, WHITE);	
	
	
	
	
}

pv_finish()
{
		cleardevice();
		setactivepage(bs_buffer_page);
	    setvisualpage(bs_buffer_page);
	    
	    while(1)
		{
		
		
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 5);
			if(pv_p1_scoreboard_score > pv_p2_scoreboard_score)
			{
				outtextxy(150,200, "Player 1");
				setcolor(GREEN);
				settextstyle(0, HORIZ_DIR, 3);
				outtextxy(260, 270, "Wins");
			}
			else if (pv_p2_scoreboard_score > pv_p1_scoreboard_score)
			{
				outtextxy(150,200, "Player 2");
				setcolor(GREEN);
				settextstyle(0, HORIZ_DIR, 3);
				outtextxy(260, 270, "Wins");
			}
			else
			{
				setcolor(RED);
				outtextxy(10,200, "DRAW");
				
			}
			
		
			setcolor(WHITE);
			outtextxy(60, 320, "Press [enter] to Exit");
		
			if(kbhit())
			{
				char ch;
				ch = getch();
			
				if(ch == '\r')
				{
					cleardevice();
					
					section = 0;	
					break;
				}
			}
			
					
		
	}
	
	if(section == 0)
	{
		setactivepage(bs_buffer_page);
		pv_flush();
		gamemenu();	
	}
	else if(section == 2)
	{
		pv_game();
	}
}
	
void pv_pause()
{
		setactivepage(bs_buffer_page);
	    setvisualpage(bs_buffer_page);
	    
	    
	while(1)
	{
	
		setcolor(RED);
		settextstyle(0, HORIZ_DIR, 5);
		outtextxy(100, 200, "Game Paused");
		setcolor(WHITE);
		settextstyle(0, HORIZ_DIR, 3);
		outtextxy(20, 270, "Press [space] to Continue");
		outtextxy(60, 320, "Press [enter] to Exit");
	
		if(kbhit())
		{
			char ch;
			ch = getch();
			if(ch == ' ')
			{
				pv_time = true;
				break;
				
			}
			else if(ch == '\r')
			{
				cleardevice();
				
				section = 0;	
				break;
			}
		}
		
				
		
	}
	
	if(section == 0)
	{
		setactivepage(bs_buffer_page);
		pv_flush();
		gamemenu();	
	}
	else if(section == 2)
	{
		pv_game();
	}
}
		
void pv_game()
{
	//create random vector for first throwing
	// Left-Up : 0 		Left-Down : 1		Left : 2		Right-Up : 3		Right-Down : 4		Right : 5	
	if(flag_isfirst)
	{
		srand(time(NULL));	
		int vector_code = (rand() % 5) + 0;	
		
		srand(time(NULL));
		
		switch(vector_code)
		{
			case 0:
				pv_ball_speed_x = 4;
				pv_ball_speed_y = 4;
			break;
			
			case 1:
				pv_ball_speed_x =  4;
				pv_ball_speed_y = -4;	
			break;	
			
			case 2:
				pv_ball_speed_x =  5;
				pv_ball_speed_y =  0;
			break;
			
			case 3:
				pv_ball_speed_x =  -4;
				pv_ball_speed_y =  4;	
			break;
			
			case 4:
				pv_ball_speed_x =  -4;
				pv_ball_speed_y =  -4;	
			break;
			
			case 5:
				pv_ball_speed_x =  -5;
				pv_ball_speed_y =  0;		
			break;
			
			
		}
		
		flag_isfirst = false;
	}

	
		while(1)
       { 
         
	
	       	if(pv_time== true)
	      	 {
       			
       			if(pv_p1_scoreboard_score == 5 || pv_p2_scoreboard_score == 5)
       			{
       				
       				pv_time = false;
       				break;
				}
       			
       			if(score_winner_flag != 0)
       			{
       				pv_time = false;
       				break;	
				}
       			
	   
	       		setactivepage(bs_buffer_page);
	       		setvisualpage(1-bs_buffer_page);
	       		cleardevice();
	       	 	
	       	 	if(kbhit())
				{
		       	 	if(GetAsyncKeyState(VK_UP))
					{				
						
						if(pv_p2_racket_s_y <= 40)
						{
									
						}
						else
						{
							pv_p2_racket_s_y-=pv_p2_racket_speed;
							pv_p2_racket_e_y-=pv_p2_racket_speed;	
						}
					
					
					}	
					if(GetAsyncKeyState(VK_DOWN))
					{
						if(pv_p2_racket_e_y >= 450)
						{
									
						}
						else
						{
						pv_p2_racket_s_y+=pv_p2_racket_speed;
						pv_p2_racket_e_y+=pv_p2_racket_speed;
						}
					
					}
					if(GetAsyncKeyState('W'))
					{
						if(pv_p1_racket_s_y <= 40)
						{
									
						}
						else
						{
							pv_p1_racket_s_y-=pv_p1_racket_speed;
							pv_p1_racket_e_y-=pv_p1_racket_speed;
						}
						
					}
					if(GetAsyncKeyState('S'))
					{

						if(pv_p1_racket_e_y >= 450)
						{
									
						}
						else
						{
							pv_p1_racket_s_y+=pv_p1_racket_speed;
							pv_p1_racket_e_y+=pv_p1_racket_speed;
						}
						
					}
					
					char ch;
					ch = getch();
					if(ch == ' ')
					{
						pv_time = false;
						break;
						
					}
				}
				
	       	 	
	       	 	
	       	 	pv_scoreboard();
				pv_draw_ball();
       			pv_init_game();
				pv_draw_rackets();
				delay(3);	
				bs_buffer_page = 1- bs_buffer_page;	
				
			 }
			 else
			 {
			 	break;
			 }
		
		}
		
		if(pv_time == false)
		{
			if(pv_p1_scoreboard_score == 5 || pv_p2_scoreboard_score == 5)
       		{			
       			pv_finish();
       				
			}
			else
			{
				if(score_winner_flag != 0)
				{
					pv_score();
				}
				else
				{
					pv_pause();
				}					
				
			}
			
		}
}	

void pv_init_game()
{
	line(3,30,3,460);
	line(3,30,627,30);
	line(627,30,627,460);
	line(3,460,627,460);
}

void pvpsaga()
{
	cleardevice();
	settextstyle(0, HORIZ_DIR, 3);
	setcolor(RED);
	outtextxy(210, 100, "Player 1");
	outtextxy(247, 150, "[W-S]");
	setcolor(BLUE);
	outtextxy(210, 200, "Player 2");
	outtextxy(200, 250, "[UP-DOWN]");
	setcolor(WHITE);
	outtextxy(50, 300, "Press [space] to Start");
	outtextxy(60, 350, "Press [enter] to Exit");
	
	
	while(1)
	{
		if(kbhit())
				{
						char ch;
					    ch = getch();
						if (ch == ' ')
						{
								pv_time = true;
								section = 2 ;
							    break;	
						}
						else if(ch == '\r')
						{
								section = 0 ;
								
								break;
								
							
						}
						
						
				}
				
	}
	cleardevice();
	if(section == 0 )
	{
		gamemenu();
	}
	else if(section == 2 && pv_time == true)
	{
		pv_game();
	}	
		
}

	//PVP MULTI		[pvpm]
	

void multisaga()
{
	cleardevice();
	setactivepage(bs_buffer_page);
	setvisualpage(bs_buffer_page);
	    
	    
	    settextstyle(0, HORIZ_DIR, 1);
		outtextxy(3, 3, "[enter] for back to main menu"); 
	    setcolor(RED);
		settextstyle(0, HORIZ_DIR, 3);
		outtextxy(70, 100, "Play On Network Mode");
		outtextxy(70, 130, "Is Not Completed Yet");
		setcolor(WHITE);
		outtextxy(50, 190, "Wait for ASMES Library");
		outtextxy(20, 270, "Details On :");
		settextstyle(0, HORIZ_DIR, 2);
		outtextxy(20, 300, "http://aksoylu.space/A-S-M-E-S");
	
	while(1)
	{
	
	
	
		if(kbhit())
		{
			char ch;
			ch = getch();
		
			 if(ch == '\r')
			{
				cleardevice();
				
				section = 0;	
				break;
			}
		}
		
				
		
	}
	
	if(section == 0)
	{
		setactivepage(bs_buffer_page);
		pv_flush();
		gamemenu();	
	}
	else if(section == 2)
	{
		pv_game();
	}
}	
	
	//About
	
void about()
{
	section = 4;
	cleardevice();
	
	settextstyle(0, HORIZ_DIR, 1);
	outtextxy(3, 3, "[enter] for back to main menu"); 
	settextstyle(4, HORIZ_DIR, 3);
	outtextxy(125, 100, "Game By Ümit Aksoylu");
	settextstyle(4, HORIZ_DIR, 1);
	outtextxy(35, 200, "Pong++ is a Open Source game project");
	outtextxy(35, 230, "and made with c++ & BGI Graphics");
	outtextxy(35, 260, "library. Developers can get source");
	outtextxy(35, 290, "codes from this github repository:"); 
	setcolor(4);
	outtextxy(35, 330, "https://github.com/Aksoylu/pong-"); 
	setcolor(15);
	outtextxy(35, 360, "you can also visit my website for tutorials"); 
	setcolor(4);
	outtextxy(35, 390, "http://umitaksoylu.space"); 
	setcolor(15);
	about_controls();
	 
}

void about_controls()
{
		while(1)
       { 
       
	       	 	if(kbhit())
				{
				
					if(section == 4)
					{
						char ch;
					    ch = getch();
					    
						if(ch == '\r')
						{
							
							section = 0 ;
							cleardevice();
							gamemenu();
							
						}

					
					}
					else
					{
						break;
					}
			    
	  
				}
       
       
       }
}	
	
int main()
{

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

	 //This command line hides console on startup of project
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    gamemenu();
    cleardevice(); 
    getch();
    
    closegraph();
}




