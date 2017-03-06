//////////////////////////////////////////////////////////////////////////
#include "include.h"
using namespace std;

int sound_Puzzle_Completed=SOUND_NULL;
int sound_tile_throwing=SOUND_NULL;
int sound_tile_backing=SOUND_NULL;
int sound_tile_taget=SOUND_NULL;

char buffer[80];        // used to print strings
//////////////////////////////////////////////////////////////////////////

CPerson::CPerson()
{
	
    Person_Lpdds_Init();//先是位图的初始化
	//infile levels

	//下面到了chess_location的初始化	
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
		{
			chess_location[i][j].row_location=245+i*20;
			chess_location[i][j].col_location=75+j*20;
		}
	for(i=0;i<16;i++)
		for(int j=0;j<16;j++)
			cursorstation[i][j]=TRUE;
	//where_am_I的初始化
	where_am_I=Left;
	where_am_I_location[Left]=200;
	where_am_I_location[Right]=575;
	where_am_I_location[Up]=15;
	where_am_I_location[Down]=395;
	where_will_be_I=Left;
};  

void CPerson::Read_a_file(char* filename)
{
	ifstream infile(filename);
	//ifstream infile("levels\\apple.txt");
	if(!infile)cerr<<"cannot open the file\n";
	counts_of_tile=0;
	for(int j=0;j<16;j++)
		for(int i=0;i<16;i++)
		{
			char temp;
			infile>>temp;
			if(temp=='0')
				chess_board[i][j]=Empty;
			if(temp=='X')
				chess_board[i][j]=Wall;
			if(temp=='?')
			{
				chess_board[i][j]=Want_to_be_filled;
				counts_of_tile++;
			}
		}
		current_counts_of_tile=counts_of_tile;
	infile.close();
}

//////////////////////////////////////////////////////////////////////////
void CPerson::ImHere()
{
	if(justmove[Left])
		DDraw_Draw_Surface(justmove[Left],200,200,48,60,lpddsback,1);
}/**/

void CPerson::GetMouseState()
{
int index_x,index_y;
if(mouse_x>=245&&mouse_x<565&&mouse_y>75&&mouse_y<395)
{
	index_x=floor((mouse_x-245)/20);
	index_y=floor((mouse_y-75)/20);
	//搜寻，包括四周
	cursorstation[index_x][index_y]=SeachAround(index_x,index_y);
	//搜寻，本地的
	if(chess_board[index_x][index_y]>=2)
			cursorstation[index_x][index_y]=FALSE;
	if(cursorstation[index_x][index_y])
		cursorstation[index_x][index_y]=SeachFarafield(index_x,index_y);
	if(!cursorstation[index_x][index_y]) where_will_be_I=where_am_I;
}//end if
}

int CPerson::SeachAround(int index_x,int index_y)
{
	if(index_y-1>=0)//向上搜寻
	{
		if(chess_board[index_x][index_y-1]==Empty||chess_board[index_x][index_y-1]==Want_to_be_filled)
			cursorstation[index_x][index_y]=FALSE;
		else 
		{
			cursorstation[index_x][index_y]=TRUE;
			return (cursorstation[index_x][index_y]);
		}
	}
	if(index_x+1<=15)//向右搜寻
	{
		if(chess_board[index_x+1][index_y]==Empty||chess_board[index_x+1][index_y]==Want_to_be_filled)
			cursorstation[index_x][index_y]=FALSE;
		else 
		{
			cursorstation[index_x][index_y]=TRUE;
			return (cursorstation[index_x][index_y]);
		}
	}
	if(index_y+1<=15)//向上搜寻
	{
		if(chess_board[index_x][index_y+1]==Empty||chess_board[index_x][index_y+1]==Want_to_be_filled)
			cursorstation[index_x][index_y]=FALSE;
		else 
		{
			cursorstation[index_x][index_y]=TRUE;
			return (cursorstation[index_x][index_y]);
		}
	}
	if(index_x-1>=0)//向左搜寻
	{
		if(chess_board[index_x-1][index_y]==Empty||chess_board[index_x-1][index_y]==Want_to_be_filled)
			cursorstation[index_x][index_y]=FALSE;
		else 
		{
			cursorstation[index_x][index_y]=TRUE;
			return (cursorstation[index_x][index_y]);
		}
	}
	return (cursorstation[index_x][index_y]);
}

int CPerson:: SeachFarafield(int index_x,int index_y)
{
	//向上搜寻
	if(index_y!=15&&(chess_board[index_x][index_y+1] >=2))
	{
		if(index_y==0)
		{
			cursorstation[index_x][index_y]=TRUE;
			where_will_be_I=Up;
			return (cursorstation[index_x][index_y]);
		}/**/
		if(index_y!=0)
		{
			for(int i=index_y-1;i>=0;i--)
			{
				if(chess_board[index_x][i]>=2)
				{
					break;
				}
				if(i==0 && (chess_board[index_x][i]==Want_to_be_filled||chess_board[index_x][i]==Empty))//搜到最顶上了
				{
					cursorstation[index_x][index_y]=TRUE;
					where_will_be_I=Up;
					return (cursorstation[index_x][index_y]);
				}
			}
		}
	}
	//向右搜寻
	if(index_x!=0&&(chess_board[index_x-1][index_y]>=2 ))
	{
	
		if(index_x==15)
		{
			{
				cursorstation[index_x][index_y]=TRUE;
				where_will_be_I=Right;
				return (cursorstation[index_x][index_y]);
			}
		}/**/
		if(index_x!=15)
		{
			for(int i=index_x+1;i<=15;i++)
			{
				if(chess_board[i][index_y]>=2)
				{
					break;
				}
				if(i==15&& (chess_board[i][index_y]==Want_to_be_filled||chess_board[i][index_y]==Empty))
				{
					cursorstation[index_x][index_y]=TRUE;
					where_will_be_I=Right;
					return (cursorstation[index_x][index_y]);
				}
			}
		}
	}
	//向下搜寻
	if(index_y!=0&&(chess_board[index_x][index_y-1]>=2))
	{
		if(index_y==15)
			{
			cursorstation[index_x][index_y]=TRUE;
			where_will_be_I=Down;
			return (cursorstation[index_x][index_y]);
			}/**/
		if(index_y!=15)
		{
			for(int i=index_y+1;i<=15;i++)
			{
				if(chess_board[index_x][i]>=2)
				{
					break;
				}
				if(i==15 && (chess_board[index_x][i]==Want_to_be_filled||chess_board[index_x][i]==Empty))//搜到最顶上了
				{
					cursorstation[index_x][index_y]=TRUE;
					where_will_be_I=Down;
					return (cursorstation[index_x][index_y]);
				}
			}
		}
	}
	//向左搜寻
	if(index_x!=15&&(chess_board[index_x+1][index_y]>=2))
	{
		if(index_x==0)
			{
				cursorstation[index_x][index_y]=TRUE;
				where_will_be_I=Left;
				return (cursorstation[index_x][index_y]);
			}/**/
		if(index_x!=0)
		{
			for(int i=index_x-1;i>=0;i--)
			{
				if(chess_board[i][index_y]>=2)
				{
					cursorstation[index_x][index_y]=FALSE;
					where_will_be_I=where_am_I;
					return(cursorstation[index_x][index_y]);
				}
				if(i==0&& (chess_board[i][index_y]==Want_to_be_filled||chess_board[i][index_y]==Empty))
				{
					cursorstation[index_x][index_y]=TRUE;
					where_will_be_I=Left;
					return (cursorstation[index_x][index_y]);
				}
			}
		}
	}
	return FALSE;
}

void CPerson:: Move_to_other_side()
{
	if(where_am_I!=where_will_be_I)
	{
		if(where_will_be_I==Left)
		{
			DDraw_Draw_Surface(justmove[Left],where_am_I_location[Left],mouse_y-45,48,60,lpddsback,1);
			where_am_I=Left;
		}
		if(where_will_be_I==Right)
		{
			DDraw_Draw_Surface(justmove[Right],where_am_I_location[Right],mouse_y-45,48,60,lpddsback,1);
			where_am_I=Right;
		}
		if(where_will_be_I==Up)
		{
			DDraw_Draw_Surface(justmove[Up],mouse_x-20,where_am_I_location[Up],48,60,lpddsback,1);
			where_am_I=Up;
		}
		if(where_will_be_I==Down)
		{
			DDraw_Draw_Surface(justmove[Down],mouse_x-20,where_am_I_location[Down],48,60,lpddsback,1);
			where_am_I=Down;
		}
	}
	where_will_be_I=where_am_I;
	
}

void CPerson::Move()
{
	static int temp_x,temp_y;//用于记录人物当前所处的位置
	if(mouse_x>=245&&mouse_x<565&&mouse_y>75&&mouse_y<395)
	{
		int index_x=floor((mouse_x-245)/20);//得到在棋盘的行位置
		int index_y=floor((mouse_y-75)/20); //得到在棋盘列位置
		
        
		//DDraw_Draw_Surface(justmove[Left],where_am_I_location[Left],mouse_y-45,48,60,lpddsback,1);//画DAVINCI
		if(where_am_I==Left||where_am_I==Right)
		{
			DDraw_Draw_Surface(personshadow,where_am_I_location[where_am_I]-4,mouse_y-7,48,32,lpddsback,1);	//画人物影子
			DDraw_Draw_Surface(justmove[where_am_I],where_am_I_location[where_am_I],mouse_y-45,48,60,lpddsback,1);
		}/**/
		if(where_am_I==Up||where_am_I==Down)
		{
			DDraw_Draw_Surface(justmove[where_am_I],mouse_x-20,where_am_I_location[where_am_I],48,60,lpddsback,1);
		}
		if(cursorstation[index_x][index_y]||If_GetBrickBack(index_x,index_y))
			DDraw_Draw_Surface(aimcursorblue,index_x*20+240,index_y*20+71,32,32,lpddsback,1);//	在棋盘上画兰色的框
		else
			DDraw_Draw_Surface(aimcursorred,index_x*20+240,index_y*20+71,32,32,lpddsback,1);//在棋盘上画红色的框
		temp_x=mouse_x;//用于保存鼠标离开棋盘时最后的位置
		temp_y=mouse_y;
		//sprintf(buffer,"Mouse(%6d,%6d) index(%3d,%3d)",mouse_x,mouse_y,index_x,index_y);//显示一下关键数据
		//sprintf(buffer,"index(%3d,%3d) cursorstation(%d) wherewillbeI %d whereamI %d",index_x,index_y,cursorstation[index_x][index_y],where_will_be_I,where_am_I);
	}
	else
	{
		DDraw_Draw_Surface(personshadow,200-4,temp_y-7,48,32,lpddsback,1);
		DDraw_Draw_Surface(justmove[Left],200,temp_y-45,48,60,lpddsback,1);
	}	
}

void CPerson::Throwabrick()
{
	int temp_x;
	int temp_y;
	temp_x=floor((mouse_x-245)/20);
	temp_y=floor((mouse_y-75)/20);
	static bool switch_of_index_of_timer=FALSE;
	static int index_of_timer=0;
	if(cursorstation[temp_x][temp_y]==1&&current_counts_of_tile!=0)//放置一个判断，来确定是否可以放置BRICK，初步确定为用GetMouseState()来做
	{
		////draw arrows
		if(where_am_I==Left)
		{
			if(temp_x<2)
				DDraw_Draw_Surface(aim_arrow_to_right,
					chess_location[temp_x+2][temp_y].row_location-3*20,
					chess_location[temp_x+2][temp_y].col_location,32,16,lpddsback,1);//ok
			if(temp_x>=2)
				for(int i=temp_x-2;i>=0;i=i-2)
					DDraw_Draw_Surface(aim_arrow_to_right,
						chess_location[i][temp_y].row_location,
						chess_location[i][temp_y].col_location,32,16,lpddsback,1);//ok
		}

		if(where_am_I==Right)
		{
			if(temp_x>=14)
				DDraw_Draw_Surface(aim_arrow_to_left,
					chess_location[temp_x-1][temp_y].row_location+2*20,
					chess_location[temp_x-1][temp_y].col_location,32,16,lpddsback,1);
			if(temp_x<14)
				for(int i=temp_x+1;i<=14;i=i+2)
					DDraw_Draw_Surface(aim_arrow_to_left,
						chess_location[i][temp_y].row_location,
						chess_location[i][temp_y].col_location,32,16,lpddsback,1);//ok

		}

		if(where_am_I==Up)
		{
			if(temp_y<2)
				DDraw_Draw_Surface(aim_arrow_to_down,
				chess_location[temp_x][temp_y+2].row_location,
				chess_location[temp_x][temp_y+2].col_location-3*20,16,32,lpddsback,1);
			if(temp_y>=2)
				for(int i=temp_y-2;i>=0;i=i-2)
					DDraw_Draw_Surface(aim_arrow_to_down,
						chess_location[temp_x][i].row_location,
						chess_location[temp_x][i].col_location,16,32,lpddsback,1);//ok
		}
			
			
		if(where_am_I==Down)
		{
			if(temp_y>=14)
				DDraw_Draw_Surface(aim_arrow_to_up,
					chess_location[temp_x][temp_y-1].row_location,
					chess_location[temp_x][temp_y-1].col_location+20,16,32,lpddsback,1);
			if(temp_y<14)
				for(int i=temp_y+1;i<=14;i=i+2)
					DDraw_Draw_Surface(aim_arrow_to_up,
						chess_location[temp_x][i].row_location,
						chess_location[temp_x][i].col_location,16,32,lpddsback,1);//ok
		}
		/////					
		if(mouse_state.rgbButtons[0] & 0x80)
		{

			switch_of_index_of_timer=TRUE;
			if(sound_tile_backing==SOUND_NULL)
			{
				if((sound_tile_backing = DSound_Load_WAV("wave\\Tile Moving 02d.wav"))!=-1)
						sound_fx[sound_tile_backing].dsbuffer->Play(0,0,0);
				sound_tile_backing=SOUND_PLAYING;
			}
			
			
		}
		else sound_tile_backing=SOUND_NULL;
		
	}
	if(If_GetBrickBack(temp_x,temp_y))//这也可以作为一个触发条件,看是否能取掉
	{
		////draw arrows
		if(where_am_I==Left)
		{
			if(temp_x<2)
				DDraw_Draw_Surface(aim_arrow_to_left,
					chess_location[temp_x+2][temp_y].row_location-3*20,
					chess_location[temp_x+2][temp_y].col_location,32,16,lpddsback,1);//ok
			if(temp_x>=2)
				for(int i=temp_x-2;i>=0;i=i-2)
					DDraw_Draw_Surface(aim_arrow_to_left,
						chess_location[i][temp_y].row_location,
						chess_location[i][temp_y].col_location,32,16,lpddsback,1);//ok
		}

		if(where_am_I==Right)
		{
			if(temp_x>=14)
				DDraw_Draw_Surface(aim_arrow_to_right,
					chess_location[temp_x-1][temp_y].row_location+2*20,
					chess_location[temp_x-1][temp_y].col_location,32,16,lpddsback,1);
			if(temp_x<14)
				for(int i=temp_x+1;i<=14;i=i+2)
					DDraw_Draw_Surface(aim_arrow_to_right,
						chess_location[i][temp_y].row_location,
						chess_location[i][temp_y].col_location,32,16,lpddsback,1);//ok

		}

		if(where_am_I==Up)
		{
			if(temp_y<2)
				DDraw_Draw_Surface(aim_arrow_to_up,
				chess_location[temp_x][temp_y+2].row_location,
				chess_location[temp_x][temp_y+2].col_location-3*20,16,32,lpddsback,1);
			if(temp_y>=2)
				for(int i=temp_y-2;i>=0;i=i-2)
					DDraw_Draw_Surface(aim_arrow_to_up,
						chess_location[temp_x][i].row_location,
						chess_location[temp_x][i].col_location,16,32,lpddsback,1);//ok
		}
			
			
		if(where_am_I==Down)
		{
			if(temp_y>=14)
				DDraw_Draw_Surface(aim_arrow_to_down,
					chess_location[temp_x][temp_y-1].row_location,
					chess_location[temp_x][temp_y-1].col_location+40,16,32,lpddsback,1);
			if(temp_y<14)
				for(int i=temp_y+1;i<=14;i=i+2)
					DDraw_Draw_Surface(aim_arrow_to_down,
						chess_location[temp_x][i].row_location,
						chess_location[temp_x][i].col_location,16,32,lpddsback,1);//ok
		}
		/////				
		if(mouse_state.rgbButtons[0] & 0x80)
		{
			if(sound_tile_throwing==SOUND_NULL)
			{
				if((sound_tile_throwing = DSound_Load_WAV("wave\\Tile Moving 02.wav"))!=-1)
						sound_fx[sound_tile_throwing].dsbuffer->Play(0,0,0);
				sound_tile_throwing=SOUND_PLAYING;
			}		
			switch_of_index_of_timer=TRUE;
		}
		else
		{sound_tile_throwing=SOUND_NULL;/*sound_tile_taget=SOUND_NULL;*/}
	}
	
	if(switch_of_index_of_timer) index_of_timer++; 
		if(index_of_timer==5)
		{
			//很好，现在还需要判断一下是否可以放置小砖块
			if(chess_board[temp_x][temp_y]==Empty)
			{
				current_counts_of_tile--;
				chess_board[temp_x][temp_y]=Temp_occupied;
			}
			else if(chess_board[temp_x][temp_y]==Want_to_be_filled)
			{
				current_counts_of_tile--;
				chess_board[temp_x][temp_y]=Have_been_filled;
			}
			//很好，现在来把原来可取掉的取掉
			else if(chess_board[temp_x][temp_y]==Temp_occupied)
			{
				current_counts_of_tile++;
				chess_board[temp_x][temp_y]=Empty;
			}
			else if(chess_board[temp_x][temp_y]==Have_been_filled)
			{
				current_counts_of_tile++;
				chess_board[temp_x][temp_y]=Want_to_be_filled;
			}

			switch_of_index_of_timer=FALSE;
			index_of_timer=0;
		}
}

bool CPerson::If_GetBrickBack(int index_x,int index_y)
{
	//先向where_am_I的方向搜寻
	if(where_am_I==Up)
	{
		if(chess_board[index_x][index_y]==Have_been_filled||chess_board[index_x][index_y]==Temp_occupied)
		{
		
			if(index_y==0)//如果是在最上面，就直接是TRUE
			{
				where_will_be_I=Up;
				return TRUE;
			}
			else
			{
				for(int i=index_y-1;i>=0;i--)
				{
					if(chess_board[index_x][i]>=2) break;
					if(i==0 && chess_board[index_x][i]<=1)
					{
						where_will_be_I=Up;
						return TRUE;
					}
				}
			}
		}
	}
	if(where_am_I==Right)
	{
		if(chess_board[index_x][index_y]==Have_been_filled||chess_board[index_x][index_y]==Temp_occupied)
		{
			//向右搜寻
			if(index_x==15)
			{
				where_will_be_I=Right;
				return TRUE;
			}
			else
			{
				for(int i=index_x+1;i<=15;i++)
				{
					if(chess_board[i][index_y]>=2) break;
					if(i==15&& chess_board[i][index_y]<=1)
					{
						where_will_be_I=Right;
						return TRUE;
					}
				}
			}

		}
		
	}
	if(where_am_I==Down)
	{
		if(chess_board[index_x][index_y]==Have_been_filled||chess_board[index_x][index_y]==Temp_occupied)
			//向下搜寻
		{
			if(index_y==15)
			{
				where_will_be_I=Down;
				return TRUE;
			}
			else
			{
				for(int i=index_y+1;i<=15;i++)
				{
					if(chess_board[index_x][i]>=2) break;
					if(i==15&& chess_board[index_x][i]<=1)
					{
						where_will_be_I=Down;
						return TRUE;
					}
				}
			}
		}

	}
	if(where_am_I==Left)
	{
		if(chess_board[index_x][index_y]==Have_been_filled||chess_board[index_x][index_y]==Temp_occupied)
		{
			if(index_x==0)
			{
				where_will_be_I=Left;
				return TRUE;
			}
			else
			{
				for(int i=index_x-1;i>=0;i--)
				{
					if(chess_board[i][index_y]>=2) break;
					if(i==0&&chess_board[i][index_y]<=1)
					{
						where_will_be_I=Left;
						return TRUE;
					}
				}
			}
		}
	}
	//
	if(chess_board[index_x][index_y]==Have_been_filled||chess_board[index_x][index_y]==Temp_occupied)
	{
		//向上搜寻
		if(index_y==0)//如果是在最上面，就直接是TRUE
		{
			where_will_be_I=Up;
			return TRUE;
		}
		else
		{
			for(int i=index_y-1;i>=0;i--)
			{
				if(chess_board[index_x][i]>=2) break;
				if(i==0 && chess_board[index_x][i]<=1)
				{
					where_will_be_I=Up;
					return TRUE;
				}
			}
		}
		//向右搜寻
		if(index_x==15)
		{
			where_will_be_I=Right;
			return TRUE;
		}
		else
		{
			for(int i=index_x+1;i<=15;i++)
			{
				if(chess_board[i][index_y]>=2) break;
				if(i==15&& chess_board[i][index_y]<=1)
				{
					where_will_be_I=Right;
					return TRUE;
				}
			}
		}
		//向下搜寻
		if(index_y==15)
		{
			where_will_be_I=Down;
			return TRUE;
		}
		else
		{
			for(int i=index_y+1;i<=15;i++)
			{
				if(chess_board[index_x][i]>=2) break;
				if(i==15&& chess_board[index_x][i]<=1)
				{
					where_will_be_I=Down;
					return TRUE;
				}
			}
		}
		//向左搜寻
		if(index_x==0)
		{
			where_will_be_I=Left;
			return TRUE;
		}
		else
		{
			for(int i=index_x-1;i>=0;i--)
			{
				if(chess_board[i][index_y]>=2)
				{
					where_will_be_I=where_am_I;
					return FALSE;
				}
				if(i==0&&chess_board[i][index_y]<=1)
				{
					where_will_be_I=Left;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void CPerson::DDrawChessBoard()
{
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
		{
			if(chess_board[i][j]==Wall)
				DDraw_Draw_Surface(tiledarkblue[0],chess_location[i][j].row_location,chess_location[i][j].col_location,24,24,lpddsback,1);
			if(chess_board[i][j]==Have_been_filled)
				DDraw_Draw_Surface(tileblue[0],chess_location[i][j].row_location,chess_location[i][j].col_location,24,24,lpddsback,1);
			if(chess_board[i][j]==Temp_occupied)
				DDraw_Draw_Surface(tilered[0],chess_location[i][j].row_location,chess_location[i][j].col_location,24,24,lpddsback,1);
			if(chess_board[i][j]==Want_to_be_filled)
				DDraw_Draw_Surface(tile_want_tile,chess_location[i][j].row_location,chess_location[i][j].col_location,24,24,lpddsback,1);
		}
	if(current_counts_of_tile!=0)
		for(int i=0;i<current_counts_of_tile;i++)
			DDraw_Draw_Surface(tileblue[3],180+i*20,460,24,24,lpddsback,1);
}


void CPerson::If_I_Win()
{
	int if_i_win=1;
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
		{
			if(chess_board[i][j]==Want_to_be_filled)
			{
				if_i_win=0;
				break;
			}
		}
	static int index_of_win=0;
	//获得胜利时的情形
	if(if_i_win) 
	{
		if(sound_Puzzle_Completed==SOUND_NULL)
		{
			if((sound_Puzzle_Completed = DSound_Load_WAV("wave\\Pixelus Puzzle Completed Sting v01.wav"))!=-1)
			{
				sound_fx[sound_Puzzle_Completed].dsbuffer->SetVolume(-1000);
                sound_fx[sound_Puzzle_Completed].dsbuffer->Play(0,0,0);
			}
			sound_Puzzle_Completed=SOUND_PLAYING;
		}
		if(index_of_win<=30)
		{
			DDraw_Draw_Surface_Scaled_parts(gLevel_map_temp,247,76,16,(index_of_win/3),320,20*(index_of_win/3),lpddsback,0);
			index_of_win++;
		}
		else
		{
			DDraw_Draw_Surface_Scaled(gLevel_map_temp,247,76,16,16,320,320,lpddsback,0);
			index_of_win++;
		}
		if(index_of_win==100)
		{
			gGame_state=Temple_temp;
			index_of_win=0;
		}
	}
}


void CPerson:: Person_Lpdds_Init()
{
	justmove[Up]=DDraw_Create_Surface(48,60,0,1);
	justmove[Down]=DDraw_Create_Surface(48,60,0,1);
	justmove[Left]=DDraw_Create_Surface(48,60,0,1);
	justmove[Right]=DDraw_Create_Surface(48,60,0,1);
    justthrow[Up][0]=DDraw_Create_Surface(48,60,0,1);
	justthrow[Up][1]=DDraw_Create_Surface(48,60,0,1);
	justthrow[Down][0]=DDraw_Create_Surface(48,60,0,1);
	justthrow[Down][1]=DDraw_Create_Surface(48,60,0,1);
	justthrow[Left][0]=DDraw_Create_Surface(48,60,0,1);
	justthrow[Left][1]=DDraw_Create_Surface(48,60,0,1);
	justthrow[Right][0]=DDraw_Create_Surface(48,60,0,1);
	justthrow[Right][1]=DDraw_Create_Surface(48,60,0,1);
	personshadow=DDraw_Create_Surface_nowhite(48,32,0,1);
	aimcursorblue=DDraw_Create_Surface_nowhite(32,32,0,1);
	aimcursorred=DDraw_Create_Surface_nowhite(32,32,0,1);
	//levels_nil=DDraw_Create_Surface(16,16,0,1);
	Scan_Image_Bitmap(&map_justmove[Up],justmove[Up],48,60);
	Scan_Image_Bitmap(&map_justmove[Down],justmove[Down],48,60);
	Scan_Image_Bitmap(&map_justmove[Left],justmove[Left],48,60);
	Scan_Image_Bitmap(&map_justmove[Right],justmove[Right],48,60);
	Scan_Image_Bitmap(&map_justthrow[Up][0],justthrow[Up][0],48,60);
	Scan_Image_Bitmap(&map_justthrow[Up][1],justthrow[Up][1],48,60);
	Scan_Image_Bitmap(&map_justthrow[Down][0],justthrow[Down][0],48,60);
	Scan_Image_Bitmap(&map_justthrow[Down][1],justthrow[Down][1],48,60);
	Scan_Image_Bitmap(&map_justthrow[Right][0],justthrow[Right][0],48,60);	
	Scan_Image_Bitmap(&map_justthrow[Right][1],justthrow[Right][1],48,60);
	Scan_Image_Bitmap(&map_justthrow[Left][0],justthrow[Left][0],48,60);
	Scan_Image_Bitmap(&map_justthrow[Left][1],justthrow[Left][1],48,60);
	Scan_Image_Bitmap(&map_personshadow,personshadow,48,32);
	Scan_Image_Bitmap(&map_aimcursorred,aimcursorred,32,32);
	Scan_Image_Bitmap(&map_aimcursorblue,aimcursorblue,32,32);
	//Scan_Image_Bitmap(&map_levels_nil,levels_nil,16,16);
	if(!Unload_Bitmap_File(&map_justmove[Up]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justmove[Down]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justmove[Left]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justmove[Right]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justthrow[Up][0]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justthrow[Up][1]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justthrow[Down][0]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justthrow[Down][1]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justthrow[Left][0]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justthrow[Left][1]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justthrow[Right][0]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_justthrow[Right][1]))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_personshadow))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_aimcursorblue))cerr<<"it's wrong";
	if(!Unload_Bitmap_File(&map_aimcursorred))cerr<<"it's wrong";
	//if(!Unload_Bitmap_File(&map_levels_nil))cerr<<"it's wrong";

	
	for(int i=0;i<5;i++)
	{
		tileblue[i]=DDraw_Create_Surface_nowhite(24,24,0,0);
		Scan_Image_Bitmap(&map_tileblue[i],tileblue[i],24,24);
		if(!Unload_Bitmap_File(&map_tileblue[i]))cerr<<"it's wrong";
		
		tiledarkblue[i]=DDraw_Create_Surface_nowhite(24,24,0,0);
		Scan_Image_Bitmap(&map_tiledarkblue[i],tiledarkblue[i],24,24);
		if(!Unload_Bitmap_File(&map_tiledarkblue[i]))cerr<<"it's wrong";

		tilered[i]=DDraw_Create_Surface_nowhite(24,24,0,0);
		Scan_Image_Bitmap(&map_tilered[i],tilered[i],24,24);
		if(!Unload_Bitmap_File(&map_tilered[i]))cerr<<"it's wrong";
	}
	tile_want_tile=DDraw_Create_Surface_nowhite(24,24,0,0);
	Scan_Image_Bitmap(&map_tile_want_tile,tile_want_tile,24,24);
	if(!Unload_Bitmap_File(&map_tile_want_tile))cerr<<"it's wrong";

	tiletrail_down=DDraw_Create_Surface_nowhite(20,128,0,0);
	Scan_Image_Bitmap(&map_tiletrail_down,tiletrail_down,20,128);
	if(!Unload_Bitmap_File(&map_tiletrail_down))cerr<<"it's wrong";
	
	tiletrail_up=DDraw_Create_Surface_nowhite(20,128,0,0);
	Scan_Image_Bitmap(&map_tiletrail_up,tiletrail_up,20,128);
	if(!Unload_Bitmap_File(&map_tiletrail_up))cerr<<"it's wrong";

	tiletrail_left=DDraw_Create_Surface_nowhite(128,20,0,0);
	Scan_Image_Bitmap(&map_tiletrail_left,tiletrail_left,128,20);
	if(!Unload_Bitmap_File(&map_tiletrail_left))cerr<<"it's wrong";
	
	tiletrail_right=DDraw_Create_Surface_nowhite(128,20,0,0);
	Scan_Image_Bitmap(&map_tiletrail_right,tiletrail_right,128,20);
	if(!Unload_Bitmap_File(&map_tiletrail_right))cerr<<"it's wrong";
	
	aim_arrow_to_left=DDraw_Create_Surface_nowhite(32,16,0,1);
	Scan_Image_Bitmap(&map_aim_arrow[Left],aim_arrow_to_left,32,16);
	if(Unload_Bitmap_File(&map_aim_arrow[Left]))cerr<<"it's wrong";

	aim_arrow_to_right=DDraw_Create_Surface_nowhite(32,16,0,1);
	Scan_Image_Bitmap(&map_aim_arrow[Right],aim_arrow_to_right,32,16);
	if(Unload_Bitmap_File(&map_aim_arrow[Right]))cerr<<"it's wrong";

	aim_arrow_to_up=DDraw_Create_Surface_nowhite(16,32,0,1);
	Scan_Image_Bitmap(&map_aim_arrow[Up],aim_arrow_to_up,16,32);
	if(Unload_Bitmap_File(&map_aim_arrow[Up]))cerr<<"it's wrong";

	aim_arrow_to_down=DDraw_Create_Surface_nowhite(16,32,0,1);
	Scan_Image_Bitmap(&map_aim_arrow[Down],aim_arrow_to_down,16,32);
	if(Unload_Bitmap_File(&map_aim_arrow[Down]))cerr<<"it's wrong";/**/
}


//////////////////////////////////////////////////////////////////////////
CPerson::~CPerson()
{
	for(int i=0;i<4;i++)
	{
		if(justmove[i])
		{
			justmove[i]->Release();
			justmove[i]=NULL;
		}
	}
	for(i=0;i<4;i++)
		for(int j=0;j<2;j++)
		{
			if(justthrow[i][j])
			{
				justthrow[i][j]->Release();
				justthrow[i][j]=NULL;
			}
		}
	if(personshadow)
	{
		personshadow->Release();
		personshadow=NULL;
	}
	if(aimcursorblue)
	{
		aimcursorblue->Release();
		aimcursorblue=NULL;
	}
	if(aimcursorred)
	{
		aimcursorred->Release();
		aimcursorred=NULL;
	}
	/*if(levels_nil)
	{
		levels_nil->Release();
		levels_nil=NULL;
	}*/
	for(i=0;i<5;i++)
	{
		if(tileblue[i])
		{
			tileblue[i]->Release();
			tileblue[i]=NULL;
		}
		if(tiledarkblue[i])
		{
			tiledarkblue[i]->Release();
			tiledarkblue[i]=NULL;
		}
	}
	if(tile_want_tile)
	{
		tile_want_tile->Release();
		tile_want_tile=NULL;
	}
	if(tiletrail_left)
	{
		tiletrail_left->Release();
		tiletrail_left=NULL;
	}

	if(tiletrail_right)
	{
		tiletrail_right->Release();
		tiletrail_right=NULL;
	}

	if(tiletrail_up)
	{
		tiletrail_up->Release();
		tiletrail_up=NULL;
	}

	if(tiletrail_down)
	{
		tiletrail_down->Release();
		tiletrail_down=NULL;
	}
	if(aim_arrow_to_up)
	{
		aim_arrow_to_up->Release();
		aim_arrow_to_up=NULL;
	}
	if(aim_arrow_to_right)
	{
		aim_arrow_to_right->Release();
		aim_arrow_to_right=NULL;
	}
	if(aim_arrow_to_down)
	{
		aim_arrow_to_down->Release();
		aim_arrow_to_down=NULL;
	}
	if(aim_arrow_to_left)
	{
		aim_arrow_to_left->Release();
		aim_arrow_to_left=NULL;
	}
}