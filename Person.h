extern char buffer[80]; 

extern class CPerson
{
public:
	CPerson();
////
	~CPerson();
	void Read_a_file(char*filename);
	void Person_Lpdds_Init();
    void ImHere();
	void Move_to_other_side();
    void Move();//移动人物
	void If_I_Win();//判断是否获得胜利
	void Throwabrick();//判断是否可以放置BRICK，如果可以就放置
	void DDrawChessBoard();//画出棋盘上所有的BRICK
	void GetMouseState();//非常重要的一个函数，决定了能否放置BRICK，能否向另外一边移动
	int SeachAround(int index_x,int index_y);//辅助GetMouseState的一个函数，去搜找周围的格子
	int SeachFarafield(int index_x,int index_y);//搜寻更远的距离，并且设置where_will_be_I
	bool If_GetBrickBack(int index_x,int index_y);
private:
	LPDIRECTDRAWSURFACE7 justmove[4];
	LPDIRECTDRAWSURFACE7 justthrow[4][2];
	LPDIRECTDRAWSURFACE7 personshadow;
	LPDIRECTDRAWSURFACE7 aimcursorblue;
	LPDIRECTDRAWSURFACE7 aimcursorred;
	LPDIRECTDRAWSURFACE7 levels_nil;
	LPDIRECTDRAWSURFACE7 tileblue[5];
	LPDIRECTDRAWSURFACE7 tiledarkblue[5];
	LPDIRECTDRAWSURFACE7 tilered[5];
	LPDIRECTDRAWSURFACE7 tiletrail_up;
	LPDIRECTDRAWSURFACE7 tiletrail_down;
	LPDIRECTDRAWSURFACE7 tiletrail_left;
	LPDIRECTDRAWSURFACE7 tiletrail_right;
	LPDIRECTDRAWSURFACE7 tile_want_tile;
	LPDIRECTDRAWSURFACE7 aim_arrow_to_up;
	LPDIRECTDRAWSURFACE7 aim_arrow_to_right;
	LPDIRECTDRAWSURFACE7 aim_arrow_to_down;
	LPDIRECTDRAWSURFACE7 aim_arrow_to_left;

	int cursorstation[16][16];//用于表示鼠标的状态
    
	struct location
	{
		int row_location;
		int col_location;
	}chess_location[16][16];//用于表示各个小块的在背景上实际的位置

	int where_am_I;//标识人物所处的方向，如果在上方就是UP，下方是DOWN...

	int where_am_I_location[4];////标识人物所处的真正位置

	int chess_board[16][16]; //用于存放各个小砖块

	int where_will_be_I;//用于存储人物将来移动方向

	int counts_of_tile;

	int current_counts_of_tile;

    
};


