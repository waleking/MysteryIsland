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
    void Move();//�ƶ�����
	void If_I_Win();//�ж��Ƿ���ʤ��
	void Throwabrick();//�ж��Ƿ���Է���BRICK��������Ծͷ���
	void DDrawChessBoard();//�������������е�BRICK
	void GetMouseState();//�ǳ���Ҫ��һ���������������ܷ����BRICK���ܷ�������һ���ƶ�
	int SeachAround(int index_x,int index_y);//����GetMouseState��һ��������ȥ������Χ�ĸ���
	int SeachFarafield(int index_x,int index_y);//��Ѱ��Զ�ľ��룬��������where_will_be_I
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

	int cursorstation[16][16];//���ڱ�ʾ����״̬
    
	struct location
	{
		int row_location;
		int col_location;
	}chess_location[16][16];//���ڱ�ʾ����С����ڱ�����ʵ�ʵ�λ��

	int where_am_I;//��ʶ���������ķ���������Ϸ�����UP���·���DOWN...

	int where_am_I_location[4];////��ʶ��������������λ��

	int chess_board[16][16]; //���ڴ�Ÿ���Сש��

	int where_will_be_I;//���ڴ洢���ｫ���ƶ�����

	int counts_of_tile;

	int current_counts_of_tile;

    
};


