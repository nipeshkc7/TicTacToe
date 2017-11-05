#include <gtk/gtk.h>

int turn=0; 
int board[24]={
	2,2,2,2,2,
	2,3,3,3,2,
	2,3,3,3,2,
	2,3,3,3,2,
	2,2,2,2,2
	};
enum{ALU,CROSSES,BORDER,EMPTY};

const int Directions[4] = { 1, 5, 4, 6 };

const int ConvertTo25[9] = {
	6, 7, 8,
	11,12,13,
	16,17,18
};

GtkWidget *turn_info;

int HasEmpty(const int *board) {
	int index = 0;
	
	for(index = 0; index < 9; ++index) {
		if( board[ConvertTo25[index]] == EMPTY) return 1;
	}
	return 0;
}

void reset(GtkWidget *reset,GtkWidget *window)
{
int index = 0;
	
	for(index = 0; index < 25; ++index) {
		board[index] = BORDER;
	}
	
	for(index = 0; index < 9; ++index) {
		board[ConvertTo25[index]] = EMPTY;
	}	
	gtk_widget_destroy(window);
	gtk_main_quit();
	main();
	
}

void out1(GtkWidget *quit,GtkWidget *window)
{
	gtk_widget_destroy(window);
	gtk_main_quit();
}


int GetNumForDir(int startSq, const int dir, const int *board, const int us) {
	int found = 0;
	while(board[startSq] != BORDER) {		
		if(board[startSq] != us) {	
			break;
		}
		found++;	
		startSq += dir;
	}	
	return found;
}

//threeinArowFunction
int threeInARow(const int *board,const int ourindex,const int us)
{
	int DirIndex = 0;
	int Dir = 0;
	int threeCount = 1;
	
	for(DirIndex = 0; DirIndex < 4; ++DirIndex) {
		Dir = Directions[DirIndex];
		threeCount += GetNumForDir(ourindex + Dir, Dir, board, us);
		threeCount += GetNumForDir(ourindex + Dir * -1, Dir * -1, board, us);
		if(threeCount == 3) {
			break;
		}
		threeCount = 1;
	}
	return threeCount;
}

void enter_button(GtkButton *button,gpointer data)
{
	
	int r=(int)data;
	while(board[ConvertTo25[r]]==EMPTY)
	{
	if(turn==0)
	{
	
  GtkWidget *label1;
  GtkWidget *vboxm;
  vboxm=gtk_vbox_new(0,0);
 
  gchar *str1 = "<b>X</b>";
  label1 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label1), str1);
  gtk_widget_modify_font (label1,pango_font_description_from_string ("Purisa 60"));
  gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);

  gtk_container_add(GTK_CONTAINER(button), vboxm);
  gtk_container_add(GTK_CONTAINER(vboxm),label1);	
    
  gtk_widget_show_all(vboxm);
  board[ConvertTo25[r]]=CROSSES;
	g_print("%d",board[r]);
	turn=1;
	
	//change turn info
		char turns[25];
		sprintf(turns,"Player %d's turn",turn+1);
		gtk_label_set(GTK_LABEL(turn_info),turns);

	//
		if (threeInARow(board,ConvertTo25[r],CROSSES)==3) 
            {
            g_print("Crosses wins");
   
		GtkWidget *message;
		GtkWidget *replay,*quit;
		GtkWidget *label;
		GtkWidget *vbox,*hbox;
		GtkWidget *frame;
		message=gtk_window_new(GTK_WINDOW_POPUP);
		gtk_window_set_position(GTK_WINDOW(message),GTK_WIN_POS_CENTER);
		gtk_window_resize(GTK_WINDOW(message),100,50);
		gtk_window_set_modal(GTK_WINDOW(message),TRUE);
		frame=gtk_frame_new(NULL);
		replay=gtk_button_new_with_label("Play Again");
		quit=gtk_button_new_with_label("Exit");
		label=gtk_label_new("CROSSES WINS");
		vbox=gtk_vbox_new(0,0);
		hbox=gtk_hbox_new(1,0);
		gtk_container_add(GTK_CONTAINER(message),frame);
		gtk_container_add(GTK_CONTAINER(frame),vbox);
		gtk_box_pack_start(GTK_BOX(vbox),label,0,0,0);
		gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
		gtk_box_pack_start(GTK_BOX(hbox),replay,1,1,0);
		gtk_box_pack_start(GTK_BOX(hbox),quit,1,1,0);
		g_signal_connect(GTK_OBJECT(replay),"clicked",GTK_SIGNAL_FUNC(reset),message);
		g_signal_connect(GTK_OBJECT(quit),"clicked",GTK_SIGNAL_FUNC(out1),message);
		gtk_widget_show_all(message);         
        }

	//if find threeinarow==3
		//say p1 wins
}
	else
	{
	
 GtkWidget *label2;
 GtkWidget *vboxm2;
 vboxm2=gtk_vbox_new(0,0);
 
  gchar *str2 = "<b>O</b>";
  label2 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label2), str2);
gtk_widget_modify_font (label2,pango_font_description_from_string ("Purisa 60"));
  gtk_label_set_line_wrap(GTK_LABEL(label2), TRUE);

gtk_container_add(GTK_CONTAINER(button), vboxm2);
gtk_container_add(GTK_CONTAINER(vboxm2),label2);	
    
gtk_widget_show_all(vboxm2);

	board[ConvertTo25[r]]=ALU;
	g_print("%d",board[r]);
	turn=0;
		
		// display turn change
		char turns[25];
		sprintf(turns,"Player %d's turn",turn+1);
		gtk_label_set(GTK_LABEL(turn_info),turns);

	if (threeInARow(board,ConvertTo25[r],ALU)==3) 
            {
            g_print("ALU wins");
            
        GtkWidget *message;
		GtkWidget *replay,*quit;
		GtkWidget *label;
		GtkWidget *vbox,*hbox;
		GtkWidget *frame;
		message=gtk_window_new(GTK_WINDOW_POPUP);
		gtk_window_set_position(GTK_WINDOW(message),GTK_WIN_POS_CENTER);
		gtk_window_resize(GTK_WINDOW(message),100,50);
		gtk_window_set_modal(GTK_WINDOW(message),TRUE);
		frame=gtk_frame_new(NULL);
		replay=gtk_button_new_with_label("Play Again");
		quit=gtk_button_new_with_label("Exit");
		label=gtk_label_new("NAUGHTS WINS");
		vbox=gtk_vbox_new(0,0);
		hbox=gtk_hbox_new(1,0);
		gtk_container_add(GTK_CONTAINER(message),frame);
		gtk_container_add(GTK_CONTAINER(frame),vbox);
		gtk_box_pack_start(GTK_BOX(vbox),label,0,0,0);
		gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
		gtk_box_pack_start(GTK_BOX(hbox),replay,1,1,0);
		gtk_box_pack_start(GTK_BOX(hbox),quit,1,1,0);
		g_signal_connect(GTK_OBJECT(replay),"clicked",GTK_SIGNAL_FUNC(reset),message);
		g_signal_connect(GTK_OBJECT(quit),"clicked",GTK_SIGNAL_FUNC(out1),message);
		gtk_widget_show_all(message);
        
            
            
            
            }

	}
	}

	//Write a function to check for draw//
	if(!HasEmpty(board)) {
			printf("Game over!\n");
			printf("It's a draw\n");
		
		GtkWidget *message;
		GtkWidget *replay,*quit;
		GtkWidget *label;
		GtkWidget *vbox,*hbox;
		GtkWidget *frame;
		message=gtk_window_new(GTK_WINDOW_POPUP);
		gtk_window_set_position(GTK_WINDOW(message),GTK_WIN_POS_CENTER);
		gtk_window_resize(GTK_WINDOW(message),100,50);
		gtk_window_set_modal(GTK_WINDOW(message),TRUE);
		frame=gtk_frame_new(NULL);
		replay=gtk_button_new_with_label("Play Again");
		quit=gtk_button_new_with_label("Exit");
		label=gtk_label_new("GAME DRAW");
		vbox=gtk_vbox_new(0,0);
		hbox=gtk_hbox_new(1,0);
		gtk_container_add(GTK_CONTAINER(message),frame);
		gtk_container_add(GTK_CONTAINER(frame),vbox);
		gtk_box_pack_start(GTK_BOX(vbox),label,0,0,0);
		gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
		gtk_box_pack_start(GTK_BOX(hbox),replay,1,1,0);
		gtk_box_pack_start(GTK_BOX(hbox),quit,1,1,0);
		g_signal_connect(GTK_OBJECT(replay),"clicked",GTK_SIGNAL_FUNC(reset),message);
		g_signal_connect(GTK_OBJECT(quit),"clicked",GTK_SIGNAL_FUNC(out1),message);
		gtk_widget_show_all(message);
        	
			
		}
}

void hover_button(GtkWidget *widget,gpointer data)
{
  if(turn==0)
{
  GdkColor col = {400000 ,20000,100000,95000};  
  
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &col);
}
 else
{
  GdkColor col = {28000 ,22000,13250,15000};  
  
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &col);
}
}



void out(GtkWidget *button2,GtkWidget *window)
{
	gtk_widget_destroy(window);
	gtk_main_quit();
}


void start(GtkWidget *widget, gpointer window1) {

GtkWidget *window;
GtkWidget *vbox;
GtkWidget *table;
GtkWidget *button[9];
GtkWidget *label;
GtkWidget *vboxa;
char turns[15];

window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
 gtk_window_resize(GTK_WINDOW(window),500,520);
gtk_window_set_title(GTK_WINDOW(window),"TIC TAC TOE BOARD DEMO");
gtk_container_set_border_width(GTK_CONTAINER(window),5);

vbox=gtk_vbox_new(0,0);
vboxa=gtk_vbox_new(0,0);

sprintf(turns,"Player %d's turn",turn+1);
turn_info=gtk_label_new(turns);
table=gtk_table_new(3,3,TRUE);
gtk_table_set_row_spacings(GTK_TABLE(table),2);
gtk_table_set_col_spacings(GTK_TABLE(table),2);

int i=0;
int j=0;
int pos=0;

for(i=0;i<3;i++)
{
for(j=0;j<3;j++){
	button[pos]=gtk_button_new();
	gtk_table_attach_defaults(GTK_TABLE(table),button[pos],j,j+1,i,i+1);
	pos++;
}
}

gtk_container_add(GTK_CONTAINER(window),vbox);
gtk_box_pack_start(GTK_OBJECT(vbox),vboxa,0,0,0);
gtk_box_pack_start(GTK_OBJECT(vbox),table,1,1,0);
gtk_box_pack_start(GTK_OBJECT(vboxa),turn_info,0,0,0);

g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

//INITIALISING THE BOARD
//InitialiseBoard();

int x=0;

	
for(x=0;x<9;x++)
gtk_widget_set_tooltip_text(button[x],"Click on your choice");

for(x=0;x<9;x++)
{
g_signal_connect(G_OBJECT(button[x]),"clicked",G_CALLBACK(enter_button),(gpointer)x);

}

for(x=0;x<9;x++)
{
g_signal_connect(G_OBJECT(button[x]),"enter",G_CALLBACK(hover_button),NULL);
}
 


gtk_widget_show_all(window);



}

int main(int argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget *table;
  GtkWidget *button;
  GtkWidget *label1;
  GtkWidget *label2;
  GtkWidget *label3;
  GtkWidget *label4;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *vbox;
  GtkWidget *hseparator;
 
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "TIC TAC TOE");
  gtk_window_resize(GTK_WINDOW(window),500,520);

  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gchar *str1 = "<b><u>TIC-TAC-TOE</u></b>";
  label1 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label1), str1);
gtk_widget_modify_font (label1,pango_font_description_from_string ("Purisa 30"));
  gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);


 label3 = gtk_label_new("__|__|__\n\__|__|__\n\  |  |  ");
gtk_widget_modify_font (label3,pango_font_description_from_string (" Monospace 30"));
  gtk_label_set_line_wrap(GTK_LABEL(label3), TRUE);

label2 = gtk_label_new(" RONIK KARKI \n\  ARPAN KC \n\RUBINA PHUYAL \n\SAUGAT POUDEL");
  gtk_widget_modify_font (label2,pango_font_description_from_string ("Monospace 10"));
  gtk_label_set_line_wrap(GTK_LABEL(label2), TRUE);

gchar *str2 = "<b><u>DEVELOPED BY:</u></b>";
  label4 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label4), str2);
gtk_widget_modify_font (label4,pango_font_description_from_string ("TIMES NEW ROMAN 15"));
  gtk_label_set_line_wrap(GTK_LABEL(label4), TRUE);

 
  vbox = gtk_vbox_new(FALSE, 10);
  gtk_container_add(GTK_CONTAINER(window), vbox);
 
  hseparator = gtk_hseparator_new();

  button1 = gtk_button_new_with_label("START GAME");
  gtk_widget_set_size_request(button1, 30, 30 );
  button2 = gtk_button_new_with_label("EXIT");
  gtk_widget_set_size_request(button2, 30, 30 );


gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, FALSE, 5);
 gtk_box_pack_start(GTK_BOX(vbox), hseparator, FALSE, FALSE, 5); 
  gtk_box_pack_start(GTK_BOX(vbox), label3, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), label4, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), button1, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), button2, FALSE, FALSE, 0);
  
  g_signal_connect(G_OBJECT(button1),"enter",G_CALLBACK(hover_button),NULL);
  
  g_signal_connect(G_OBJECT(button2),"enter",G_CALLBACK(hover_button),NULL);
  
  g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(start), (gpointer) window); 
		g_signal_connect(GTK_OBJECT(button2),"clicked",GTK_SIGNAL_FUNC(out),window);


  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

gtk_widget_show_all(window);
  gtk_main();

  return 0;
}#include <gtk/gtk.h>

int turn=0; 
int board[9];
enum{EMPTY,ALU,CROSSES};

int directions[4]={1,2,3,4};

GtkWidget *turn_info;

void reset(GtkWidget *reset,GtkWidget *window)
{
	int i,j;
	for(i=0;i<9;i++)
	{
		board[i]=EMPTY;
	}
	gtk_widget_destroy(window);
	gtk_main_quit();
	main();
}

void out1(GtkWidget *quit,GtkWidget *window)
{
	gtk_widget_destroy(window);
	gtk_main_quit();
}

//getdirNum
int getDirNum(int startSq,const int dir,const int us,const int *board)
{
    int found=0;

    while(board[startSq]==0 || board[startSq]==1 || board[startSq]==2)
    {
        if(board[startSq]!=us){
            break;
        }
        found++;
        startSq+=dir;
    }
    return found;
}

//threeinArowFunction
int threeInARow(const int *board,const int ourIndex,const int side)
{
    int index=0;
    int dir=0;
    int threeCount=1;

    for(index=0;index<4;index++)
    {
        dir=directions[index];
        threeCount+=getDirNum(ourIndex+dir,dir,side,board);
        threeCount+=getDirNum(ourIndex+dir*-1,dir*-1,side,board);
        if(threeCount==3){
            break;
        }
        threeCount=1;
    }
    return threeCount;
}

void enter_button(GtkButton *button,gpointer data)
{
		
	int r=(int)data;
	while(board[r]==EMPTY)
	{
	if(turn==0)
	{
	
	
	

  GtkWidget *label1;
  GtkWidget *vboxm;
  vboxm=gtk_vbox_new(0,0);
 
  gchar *str1 = "<b>X</b>";
  label1 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label1), str1);
  gtk_widget_modify_font (label1,pango_font_description_from_string ("Purisa 60"));
  gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);

gtk_container_add(GTK_CONTAINER(button), vboxm);
gtk_container_add(GTK_CONTAINER(vboxm),label1);	
    
gtk_widget_show_all(vboxm);
  board[r]=CROSSES;
	g_print("%d",board[r]);
	turn=1;
	
	//change turn info
		char turns[25];
		sprintf(turns,"Player %d's turn",turn+1);
		gtk_label_set(GTK_LABEL(turn_info),turns);

	//
		if (threeInARow(board,r,CROSSES)==3) 
            {
            g_print("Crosses wins");
   
		GtkWidget *message;
		GtkWidget *replay,*quit;
		GtkWidget *label;
		GtkWidget *vbox,*hbox;
		GtkWidget *frame;
		message=gtk_window_new(GTK_WINDOW_POPUP);
		gtk_window_set_position(GTK_WINDOW(message),GTK_WIN_POS_CENTER);
		gtk_window_resize(GTK_WINDOW(message),100,50);
		gtk_window_set_modal(GTK_WINDOW(message),TRUE);
		frame=gtk_frame_new(NULL);
		replay=gtk_button_new_with_label("Play Again");
		quit=gtk_button_new_with_label("Exit");
		label=gtk_label_new("CROSSES WINS");
		vbox=gtk_vbox_new(0,0);
		hbox=gtk_hbox_new(1,0);
		gtk_container_add(GTK_CONTAINER(message),frame);
		gtk_container_add(GTK_CONTAINER(frame),vbox);
		gtk_box_pack_start(GTK_BOX(vbox),label,0,0,0);
		gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
		gtk_box_pack_start(GTK_BOX(hbox),replay,1,1,0);
		gtk_box_pack_start(GTK_BOX(hbox),quit,1,1,0);
		g_signal_connect(GTK_OBJECT(replay),"clicked",GTK_SIGNAL_FUNC(reset),message);
		g_signal_connect(GTK_OBJECT(quit),"clicked",GTK_SIGNAL_FUNC(out1),message);
		gtk_widget_show_all(message);         
        }

	//if find threeinarow==3
		//say p1 wins
}
	else
	{
	
 GtkWidget *label2;
 GtkWidget *vboxm2;
 vboxm2=gtk_vbox_new(0,0);
 
  gchar *str2 = "<b>O</b>";
  label2 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label2), str2);
gtk_widget_modify_font (label2,pango_font_description_from_string ("Purisa 60"));
  gtk_label_set_line_wrap(GTK_LABEL(label2), TRUE);

gtk_container_add(GTK_CONTAINER(button), vboxm2);
gtk_container_add(GTK_CONTAINER(vboxm2),label2);	
    
gtk_widget_show_all(vboxm2);

	board[r]=ALU;
	g_print("%d",board[r]);
	turn=0;
		
		// display turn change
		char turns[25];
		sprintf(turns,"Player %d's turn",turn+1);
		gtk_label_set(GTK_LABEL(turn_info),turns);

	if (threeInARow(board,r,ALU)==3) 
            {
            g_print("ALU wins");
            
        GtkWidget *message;
		GtkWidget *replay,*quit;
		GtkWidget *label;
		GtkWidget *vbox,*hbox;
		GtkWidget *frame;
		message=gtk_window_new(GTK_WINDOW_POPUP);
		gtk_window_set_position(GTK_WINDOW(message),GTK_WIN_POS_CENTER);
		gtk_window_resize(GTK_WINDOW(message),100,50);
		gtk_window_set_modal(GTK_WINDOW(message),TRUE);
		frame=gtk_frame_new(NULL);
		replay=gtk_button_new_with_label("Play Again");
		quit=gtk_button_new_with_label("Exit");
		label=gtk_label_new("NAUGHTS WINS");
		vbox=gtk_vbox_new(0,0);
		hbox=gtk_hbox_new(1,0);
		gtk_container_add(GTK_CONTAINER(message),frame);
		gtk_container_add(GTK_CONTAINER(frame),vbox);
		gtk_box_pack_start(GTK_BOX(vbox),label,0,0,0);
		gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
		gtk_box_pack_start(GTK_BOX(hbox),replay,1,1,0);
		gtk_box_pack_start(GTK_BOX(hbox),quit,1,1,0);
		g_signal_connect(GTK_OBJECT(replay),"clicked",GTK_SIGNAL_FUNC(reset),message);
		g_signal_connect(GTK_OBJECT(quit),"clicked",GTK_SIGNAL_FUNC(out1),message);
		gtk_widget_show_all(message);
        
            
            
            
            }

	}
	}

	//Write a function to check for draw//
}

void hover_button(GtkWidget *widget,gpointer data)
{
  if(turn==0)
{
  GdkColor col = {400000 ,20000,100000,95000};  
  
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &col);
}
 else
{
  GdkColor col = {28000 ,22000,13250,15000};  
  
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &col);
}
}



void out(GtkWidget *button2,GtkWidget *window)
{
	gtk_widget_destroy(window);
	gtk_main_quit();
}


void start(GtkWidget *widget, gpointer window1) {
GtkWidget *window;
GtkWidget *vbox;
GtkWidget *table;
GtkWidget *button[9];
GtkWidget *label;
GtkWidget *vboxa;
char turns[15];

window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
 gtk_window_resize(GTK_WINDOW(window),500,520);
gtk_window_set_title(GTK_WINDOW(window),"TIC TAC TOE BOARD DEMO");
gtk_container_set_border_width(GTK_CONTAINER(window),5);

vbox=gtk_vbox_new(0,0);
vboxa=gtk_vbox_new(0,0);

sprintf(turns,"Player %d's turn",turn+1);
turn_info=gtk_label_new(turns);
table=gtk_table_new(3,3,TRUE);
gtk_table_set_row_spacings(GTK_TABLE(table),2);
gtk_table_set_col_spacings(GTK_TABLE(table),2);

int i=0;
int j=0;
int pos=0;

for(i=0;i<3;i++)
{
for(j=0;j<3;j++){
	button[pos]=gtk_button_new();
	gtk_table_attach_defaults(GTK_TABLE(table),button[pos],j,j+1,i,i+1);
	pos++;
}
}

gtk_container_add(GTK_CONTAINER(window),vbox);
gtk_box_pack_start(GTK_OBJECT(vbox),vboxa,0,0,0);
gtk_box_pack_start(GTK_OBJECT(vbox),table,1,1,0);
gtk_box_pack_start(GTK_OBJECT(vboxa),turn_info,0,0,0);

g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);


int x=0;

for(x=0;x<9;x++)
gtk_widget_set_tooltip_text(button[x],"Click on your choice");

for(x=0;x<9;x++)
{
g_signal_connect(G_OBJECT(button[x]),"clicked",G_CALLBACK(enter_button),(gpointer)x);

}

for(x=0;x<9;x++)
{
g_signal_connect(G_OBJECT(button[x]),"enter",G_CALLBACK(hover_button),NULL);
}
 


gtk_widget_show_all(window);



}

int main(int argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget *table;
  GtkWidget *button;
  GtkWidget *label1;
  GtkWidget *label2;
  GtkWidget *label3;
  GtkWidget *label4;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *vbox;
  GtkWidget *hseparator;
 
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "TIC TAC TOE");
  gtk_window_resize(GTK_WINDOW(window),500,520);

  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gchar *str1 = "<b><u>TIC-TAC-TOE</u></b>";
  label1 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label1), str1);
gtk_widget_modify_font (label1,pango_font_description_from_string ("Purisa 30"));
  gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);


 label3 = gtk_label_new("__|__|__\n\__|__|__\n\  |  |  ");
gtk_widget_modify_font (label3,pango_font_description_from_string (" Monospace 30"));
  gtk_label_set_line_wrap(GTK_LABEL(label3), TRUE);

label2 = gtk_label_new(" RONIK KARKI \n\  ARPAN KC \n\RUBINA PHUYAL \n\SAUGAT POUDEL");
  gtk_widget_modify_font (label2,pango_font_description_from_string ("Monospace 10"));
  gtk_label_set_line_wrap(GTK_LABEL(label2), TRUE);

gchar *str2 = "<b><u>DEVELOPED BY:</u></b>";
  label4 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label4), str2);
gtk_widget_modify_font (label4,pango_font_description_from_string ("TIMES NEW ROMAN 15"));
  gtk_label_set_line_wrap(GTK_LABEL(label4), TRUE);

 
  vbox = gtk_vbox_new(FALSE, 10);
  gtk_container_add(GTK_CONTAINER(window), vbox);
 
  hseparator = gtk_hseparator_new();

  button1 = gtk_button_new_with_label("START GAME");
  gtk_widget_set_size_request(button1, 30, 30 );
  button2 = gtk_button_new_with_label("EXIT");
  gtk_widget_set_size_request(button2, 30, 30 );


gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, FALSE, 5);
 gtk_box_pack_start(GTK_BOX(vbox), hseparator, FALSE, FALSE, 5); 
  gtk_box_pack_start(GTK_BOX(vbox), label3, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), label4, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), button1, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), button2, FALSE, FALSE, 0);
  
  g_signal_connect(G_OBJECT(button1),"enter",G_CALLBACK(hover_button),NULL);
  
  g_signal_connect(G_OBJECT(button2),"enter",G_CALLBACK(hover_button),NULL);
  
  g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(start), (gpointer) window); 
		g_signal_connect(GTK_OBJECT(button2),"clicked",GTK_SIGNAL_FUNC(out),window);


  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
