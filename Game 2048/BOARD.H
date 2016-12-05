#ifndef board_h_included
#define board_h_included

#define NO_OF_ROWS 4
#define NO_OF_COLS 4
#define ESC 27
#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0


class boardGame
{
protected:

	int board[NO_OF_ROWS][NO_OF_COLS] ;

public:

	void drawboard() ;

friend	void generate(boardGame *) ;

	int write_to_file() ;

};

// game data to be stored into board.dat
struct board_data
{
    int board[NO_OF_ROWS][NO_OF_COLS] ;
    int oc ; //occupied cells
    int score ;

} ;



class twenty48 : public boardGame
{
     int shift_flag ;

     int score;   //score of the game
     int oc;      //occupied cells
     int best_score ;  //best score of the game
     struct board_data bdata;  //data of board

public:

	twenty48() ;

	void drawboard() ;

friend	void generate(twenty48 *) ;

	int  show_menu() ;

	int  new_game() ;

	int  continue_game() ;

	int  how_to_play() ;

	int  play() ;

	int swipe_right() ;

	int swipe_left() ;

	int swipe_up() ;

	int swipe_down() ;

	void update_score(int n)
	{
	  score+=n ; //adding score
	}


	int write_to_file();

	int save_bestScore() ;

	int endgame(int) ;

};   //end of class twenty48

#endif