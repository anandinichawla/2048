#include<iostream.h>
#include<conio.h>
#include<iomanip.h>
#include<stdlib.h>
#include<process.h>
#include "board.h"
#include<fstream.h>
#include<stdio.h>

int calc_digit(int n)    //to calculate number of digits
{
   int ndigits ;

   if(n<10)
     ndigits=1 ;
   else if(n<100)
     ndigits=2 ;
   else if(n<1000)
     ndigits=3 ;
   else if(n<10000)
     ndigits=4 ;

   return ndigits ;

} //end of function calc_digits

void generate(twenty48 *g)
{
     int i,j,m,r,f=0 ;

     while(f<1)
     {
       r=random(4) +1 ;
       if(r==2 || r==4)
	 f++ ;
     }
	       m=0 ;
	       while(m==0)
	       {
		 i=random(4) ;      //generate the random cells to put the 2 or 4
		 j=random(4) ;
	       //	 cout<<endl<<"i= "<<i<<" j= "<<j  ;  getch() ;
		 if((*g).board[i][j]==0)      //to check random numbers are in the same cell .
		 {	 (*g).board[i][j]=r ; m++ ; (*g).oc++ ;  }
	       }
	      // cout<<" "<<i<<","<<j ;
   //  cout << endl << "generate(): " << r;
   //  getch() ;

} //end of generate

twenty48::twenty48()
{
      int i,j ;

      oc=0 ;
      score=0 ;
      best_score=0 ;
      randomize() ;

      for(i=0;i<4;i++)
      {
	   for(j=0;j<4;j++)
	   {
	     board[i][j]=0 ;      //to initialize matrix
	   }
      }

      //read best score from bestscore.dat
      ifstream fin ;
      fin.open("bestscore.dat",ios::in|ios::binary) ;
      if(fin) ;
	fin>>best_score ;
      fin.close() ;
}  //end of constructor

int twenty48::new_game()
{
   int f=0 ;
   int i,j ;              //initalizing data to start a new game


	oc=0 ;
      /* if(score>0 && score>=best_score )
	 save_bestScore() ; //to save score if user does not exit and wants to start a new game
      */
      score=0 ;
      randomize() ;
      for(i=0;i<4;i++)
      {
	   for(j=0;j<4;j++)
	   {
	     board[i][j]=0 ;      //to initialize matrix
	   }
      }

      //	randomize() ;

	while(f<2)
	{
		generate(this) ;  //generating 2 or 4 to start game .
		f++ ;
	}

     drawboard() ;
     play() ;

return SUCCESS ;

} //end of new_game()

int twenty48::endgame(int n)
{
    int check=0,i,j ;

    if(n==2048)
    {
	 drawboard();
	 cout<<"YOU GOT TO THE 2048 TILE !! " ;
	 cout<<endl<<"YOU WIN!!!!" ;
    }
    else if(oc==16)
    {
	for(i=0;i<NO_OF_ROWS;i++)
	{
		for(j=0;j<NO_OF_COLS;j++)
		{
		  if(j<3)
		  {
		     if(board[i][j]==board[i][j+1])
		       check++ ;
		  }
		}
	}

	    for(j=0;j<NO_OF_COLS;j++)
	    {
		for(i=0;i<NO_OF_ROWS;i++)
		{
		   if(i<3)
		   {
		     if(board[i][j]==board[i+1][j])
		       check++ ;
		   }
		}
	    }

	    if(check==0) //if no moves, end of game; hence, cout
	    {
	      cout<<endl<<"BOARD IS FILLED UP!!" ;
	      cout<<endl<<"END OF GAME" ;
	    }
     } //end of else
     return SUCCESS ;
}  //end of function endgame

int twenty48::swipe_right()
{
      int i,j,k,n ;

      shift_flag=FALSE ;

      for(i=0;i<NO_OF_ROWS;i++)         //for each  row
      {
	//first add up neighbouring cells that have same value
	//then shift right
	for (j=NO_OF_COLS-1; j>0; j--)
	{

	  if (board[i][j] == 0)   //empty cell
		continue;

	  k = j-1;
	  while ( (k >= 0) && (board[i][k] == 0) )  //find the next non-empty cell
		k--;

	  if(k<0)
		break ;  //all cells empty hence go to shift logic for loop

	  if(board[i][j]==board[i][k])
	  {
	     board[i][j]*=2 ;
	     oc-- ;
	     n=board[i][j] ;    //newly added value
	     board[i][k]=0 ;
	     shift_flag=TRUE ;
	     j = k;
	     update_score(n) ;
	  }
	}


	for(j=NO_OF_COLS-1;j>0;j--)      //for each rightmost non-empty
	{                                //column in that row, move it right

	    if(board[i][j]==0)  //empty
	    {  int k = j-1;

	       while ((k >= 0) && (board [i][k] == 0)) //find next non-empty
			k--;                           //cell

	       if(k<0)
		 break ; //all cells empty ; nothing to swipe ;hencego to rows for loop


	       board[i][j]=board[i][k] ;  //move into rightmost empty slot
	       board[i][k]=0  ;	   //blank out the moved cell
	       shift_flag=TRUE ;         //cout<<"flag="<<flag ;getch() ;

	    } //end of if
	} //end of SHIFT RIGHT logic
      }//end of for loop for rows

      if(shift_flag==TRUE)
	  generate(this) ; //generate the random 2 or 4, and add it to the board

      drawboard() ;

      endgame(n) ;

   return SUCCESS ;
}   //end of function swipe_right()

int twenty48::swipe_left()
{
   int i,j,k,n  ;

   shift_flag=FALSE ;

  // cout<<endl<<"1. "<<shift_flag ; getch() ;

   for(i=0;i<NO_OF_ROWS;i++)
   {
       for(j=0;j<NO_OF_COLS;j++) // add all neighbouring cells with equal value
       {
	 if (board[i][j] == 0)
	     continue;

	  k=j+1 ;

	  while( k<NO_OF_COLS && board[i][k]==0 )    //find next empty cells
	     k++ ;

	  if(k>=NO_OF_COLS)
	    break ;   //all cells empty, nothing to add; hence go to next column

	  if(board[i][j]==board[i][k])
	  {
	      board[i][j]*=2 ;
	      n=board[i][j] ;
	      board[i][k]=0 ;
	      if(board[i][j]!=0)
	      {
		shift_flag=TRUE ;
		oc-- ;
		update_score(n) ;
	      }
	      j = k;
	  }
	  //cout<<endl<<"k= "<<k<<" j= "<<j ;
       }  //end of add number for loop
   //    cout<<endl<<"exited for loop" ;
     //  cout<<endl<<"2. "<<shift_flag<<" j= "<<j<<" i= "<<i ; getch() ;

       for(j=0;j<NO_OF_COLS;j++)
       {
	  // cout<<endl<<"entering second loop " ; getch() ;

	   if(board[i][j]==0)
	   {
	      k=j+1 ;

	      while(k<4 && board[i][k]==0)
		  k++ ;

	      if(k>=4)
		break ;

		 board[i][j]=board[i][k] ;
		 board[i][k]=0 ;
		 shift_flag=TRUE ;

	    } // end of if
       } //end of shift logic
   }//end of for loop of rows




  /* for(i=0;i<4;i++)
     {
       for(j=0;j<4;j++)
       {
	  cout<<" "<<board[i][j] ;
       }
       cout<<endl;
     }
     getch() ;   */

    // cout<<"3. "<<shift_flag ;getch() ;

     if(shift_flag==TRUE)
	generate(this) ;	      //generating random number on shift or addition


	 drawboard() ;   //calling drawboard to redraw after swipe

	 endgame(n) ;

     return SUCCESS ;
} //end of swipe left

int twenty48::swipe_up()
{
   int i,j,k,n  ;

   shift_flag=FALSE ;

   for(j=0;j<NO_OF_COLS;j++)
   {
      for(i=0;i<NO_OF_ROWS;i++)
      {
	   if(board[i][j]==0)
	      continue ;

	   k=i+1 ;
	   while(k<NO_OF_ROWS && board[k][j]==0)
	      k++ ;

	   if(k>=4)
	     break ;

	   if(board[i][j]==board[k][j])
	   {
	     board[i][j]*=2 ;
	     oc-- ;
	     n=board[i][j] ;
	     board[k][j]=0 ;
	     shift_flag=TRUE ;
	     update_score(n) ;
	   }
      }

      for(i=0;i<NO_OF_ROWS;i++)
      {
	  if(board[i][j]==0)
	  {
	     k=i+1 ;

	     while(k<NO_OF_ROWS && board[k][j]==0)
		k++ ;

	     if(k>=4)
	       break ;

	     board[i][j]=board[k][j] ;
	     board[k][j]=0 ;
	     shift_flag=TRUE ;

	  }//end of if
      }//end of shift up logic
   }//end of for loop for cols

   if(shift_flag==TRUE)
     generate(this) ;


      drawboard() ;

      endgame(n) ;

   return SUCCESS ;

} //end of swipe up

int twenty48::swipe_down()
{
   int i,j,k,n  ;

   shift_flag=FALSE ;

   for(j=0;j<NO_OF_COLS;j++)
   {
      for(i=NO_OF_ROWS-1;i>=0;i--)
      {
	   if(board[i][j]==0)
	      continue ;


	     k=i-1 ;
	     while(k<NO_OF_ROWS && board[k][j]==0)
	     k-- ;

	    if(k<0)
	      break ;


	   if(board[i][j]==board[k][j])
	   {
	     board[i][j]*=2 ;
	     oc-- ;
	     n=board[i][j] ;
	     board[k][j]=0 ;
	     shift_flag=TRUE ;
	     update_score(n) ;
	   }
      }

      for(i=NO_OF_ROWS-1;i>0;i--)
      {
	  if(board[i][j]==0)
	  {
	     k=i-1 ;

	     while(k<NO_OF_ROWS && board[k][j]==0)
		k-- ;

	     if(k<0)
	       break ;

	     board[i][j]=board[k][j] ;
	     board[k][j]=0 ;
	     shift_flag=TRUE ;

	  }//end of if
      }//end of shift down logic
   }//end of for loop for cols

   if(shift_flag==TRUE)
     generate(this) ;


    drawboard() ;

    endgame(n) ;

   return SUCCESS ;

} //end of swipe down


void twenty48::drawboard()
{

    clrscr() ;
    int i,n,j ;
    /*   randomize() ;

       for(i=0;i<4;i++)
	{
	   for(j=0;j<4;j++)
	   {
	     board[i][j]=random(2000) ;      //to initialize matrice
	   }
	}  */
    cout<<endl<<endl<<endl<<endl<<endl ;
    cout<<setw(32) ;


     // if(score>=best_score)
       //	  best_score=score ;



       cout<<endl<<"SCORE: "<<score ;
       cout<<"           "<<"BEST: "<<best_score<<endl<<endl ;

    for(i=0;i<4;i++)
    {
      cout<<endl<<"                       "<<"-------------------------------------" ;

      cout<<endl<<"                       " ;
      cout << "|";
      for(j=0;j<4;j++)
      {
	 if(board[i][j]!=0)
	 {
	   n=calc_digit(board[i][j]) ;
	   if(n==1 || n==2)
	   {
	     cout<<setw(5)<< board[i][j]<< setw(4)<<"|" ;    //total spaces used: 9
	   }
	   else if(n==3)
	   {
	     cout<<setw(6)<< board[i][j]<< setw(3)<<"|" ;
	   }
	   else if(n==4)
	   {
	     cout<<setw(6)<< board[i][j]<< setw(3)<<"|" ;
	   }
	 }
	 else

	   cout<<setw(9)<<"|" ;
	}//end of for loop for loop
      } //end of for loop for rows

    cout<<endl<<"                       " <<"-------------------------------------" <<endl;

    //cout<<endl<<"occupied cells: "<<oc ;
    cout<<endl<<endl<<endl<<endl ;
    cout<<"                      ESC:MENU" ;
    cout<<"  G:LEFT" ;
    cout<<"  J:RIGHT" ;
    cout<<"  Y:UP" ;
    cout<<"  H:DOWN" ;


} //end of drawboard

int twenty48::show_menu()     //first function called from main to start game
{
   int opt=0;

   do {

   clrscr() ;

   ifstream fin;
   fin.open("menu.txt",ios::in)  ;
   if (!fin)
   {
      cerr << "Error in opening file Menu.txt" << endl;
      return FAILURE ;
   }

   char line[200] ;

   //read menu from file
   while(!fin.eof())
   {
       fin.getline(line,20) ;
       cout<<line<<endl ;

   }
   fin.close();

   cout<<endl<<"Enter Option: " ;
   cin>>opt ;

   if(opt==1)
   {
      new_game() ;            //starting new game /generating 2 or 4
   }

   if(opt==2)
   {
       continue_game() ;        //board saved from previous game /continue
   } //end of option 2 if for continue_game()


   if(opt==3)
   {
      how_to_play() ;          //instructions to play game
   }
   if(opt==4)

      ;        // exit from the game
   } while (opt != 4);

   return SUCCESS ;
}

int twenty48::continue_game()
{
   int i,j ;
   ifstream fin ;
   fin.open("board.dat",ios::in|ios::nocreate|ios::binary);
   if(!fin)
   {
     cout<<endl<<"------------FILE NOT FOUND !!!!----------- ";
     cout<<endl<<"PRESS ENTER AND THEN CHOOSE ANOTHER OPTION: " ;
     getch() ;
     return FAILURE;
  }


      fin.read((char*)&bdata,sizeof(board_data)) ;
      fin.close() ;
      for(i=0;i<NO_OF_ROWS;i++)
	 for(j=0;j<NO_OF_COLS;j++)
	     board[i][j]=bdata.board[i][j] ;
      score=bdata.score ;
      oc=bdata.oc ;
      drawboard() ;

  play() ;  //to start playing game after drawing already saved board
  return SUCCESS ;

}

int twenty48::how_to_play()
{


    ifstream fin ;
    char line[200] ;

    fin.open("option3.txt",ios::in) ;

      if (!fin)
      {
	cerr << "Error in opening file option3.txt! Press ESC to return to menu." << endl;
	while ((getch()) != ESC)
		;
	return FAILURE ;
      }

      while(!fin.eof())
      {
	 fin.getline(line,150) ;
	 cout<<line<<endl ;
      }
      fin.close();
      cout<<endl<<"PRESS ESC TO GO BACK TO MENU" ;

      while ((getch()) != ESC)
	 ; //quit instructions on ESC

      return SUCCESS ;
}

int twenty48::play()
{
    char c ;

    c = getch();
    while( c != ESC )
    {
	switch(c)
	{
	case 'g':
	case 'G': { swipe_left()  ; /*cout<<endl<<"left"*/ ; break ;}

	case 'h':
	case 'H': { swipe_down()  ; /*cout<<endl<<"down"*/ ; break ;}

	case 'j':
	case 'J': { swipe_right()  ; /*cout<<endl<<"right"*/ ; break ;}

	case 'y':
	case 'Y': { swipe_up()  ;  /*cout<<endl<<"up"*/  ; break ;}
	}    //end of switch

	c = getch() ; //wait for next key press

    } // end of while

    write_to_file() ;//save board for current play session
    return SUCCESS ;

} //end of function play();

int twenty48::write_to_file()
{
    int i=0, j=0;

    bdata.oc = oc;
    bdata.score = score;
    for (i=0; i < NO_OF_ROWS; ++i)
	for (j=0; j< NO_OF_COLS; ++j)
	   bdata.board[i][j] = board[i][j];

    ofstream fout ;

    if (!fout)
    {
      return FAILURE;
    }

    fout.open("board.dat",ios::out|ios::binary);
    fout.write((char*)&bdata, sizeof(board_data)) ;

    fout.close () ;

    return SUCCESS;
}

int twenty48::save_bestScore()
{

    // cout<<endl<<"best_score: "<<best_score ;
    // getch() ;
     if(best_score)
     {
	ofstream fout ;
	if(!fout)
	  return FAILURE ;

	fout.open("bestscore.dat",ios::out|ios::binary)  ;
	fout << best_score ;
	fout.close() ;
     }

     return SUCCESS ;
}


void main()
{

    clrscr() ;

    twenty48 game ;

    game.show_menu() ;     // display menu

    game.save_bestScore() ;     //save best score


}  //end of main