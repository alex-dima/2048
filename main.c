#include "header.h"
void menu_create (WINDOW *menuwin, PANEL *menupan)
{

     char list[3][9] = { "Resume", "New Game", "Quit" };
     char item[10];
    int i = 0,ok=1;;
    if(access( "saves", F_OK ) == -1 )
    {
        strcpy(list[0],"      ");
        ok=0;
    }
    start_color();
    init_pair(1,COLOR_GREEN, COLOR_BLACK);
    wbkgd(menuwin, COLOR_PAIR(1));
    wrefresh(menuwin);

     for( i=0; i<3; i++ ) {
        if (ok==1) {
            if( i == 0 )
            wattron( menuwin, A_STANDOUT ); // highlights the first item.
            else
            wattroff( menuwin, A_STANDOUT );
            }
        else
            {
            if( i == 1 )
            wattron( menuwin, A_STANDOUT ); // highlights the first item.
            else
            wattroff( menuwin, A_STANDOUT );
            }
        sprintf(item, "%s",  list[i]);
        mvwprintw( menuwin, i+1, 2, "%s", item );
    }

    wrefresh( menuwin );

    noecho(); // disable echoing of characters on the screen
    keypad( menuwin, TRUE ); // enable keyboard input for the window.
    curs_set( 0 ); // hide the default screen cursor.

}


int menu_navig (WINDOW *menuwin, PANEL *menupan)
{
   char list[3][9] = { "Resume", "New Game", "Quit" };
    char item[10];
    int ch, i = 0, ok=1;
    if(access( "saves", F_OK ) == -1 )
    {
        strcpy(list[0],"      ");
        ok=0;
        i=1;
    }

    while(( ch = wgetch(menuwin)) != 10){

                // right pad with spaces to make the items appear with even width.
            sprintf(item, "%s",  list[i]);
            mvwprintw( menuwin, i+1, 2, "%s", item );
              // use a variable to increment or decrement the value based on the input.
            switch( ch ) {
                case KEY_UP:
                            i--;
                            if(ok==1)i = ( i<0 ) ? 2 : i;
                            else i = ( i<1 ) ? 2 : i;
                            break;
                case KEY_DOWN:
                            i++;
                            if (ok==1)i = ( i>2 ) ? 0 : i;
                            else i = ( i>2 ) ? 1 : i;
                            break;
            }

            // now highlight the next item in the list.
            wattron( menuwin, A_STANDOUT );

            sprintf(item, "%s",  list[i]);
            mvwprintw( menuwin, i+1, 2, "%s", item);
            wattroff( menuwin, A_STANDOUT );
    }

  return i;
}

void game_grid(WINDOW *gamewin, PANEL *gamepan)
{


    char horizontal[44] = "===========================================";
    int c, r;
    //Print horizontally
    for (r=0;r<4;r++)
     mvwprintw (gamewin,r*6,1,"%s", horizontal);
     mvwprintw (gamewin,r*6,1,"%s", horizontal);
    //Print vertically
    for (c=0;c<5;c++)
        for (r=1;r<24;r++)
            mvwprintw (gamewin,r,c*11,"|");
    wrefresh(gamewin);
}

void instructions(WINDOW *gamewin, PANEL *gamepan)
{
            mvwprintw (gamewin,7,50,"%s", " Folositi sagetile pentru a juca      ");
            mvwprintw (gamewin,8,50,"%s", "                                    ");
            mvwprintw (gamewin,9,50,"%s","             _____                ");
            mvwprintw (gamewin,10,50,"%s","            |     |               ");
            mvwprintw (gamewin,11,50,"%s","            |  ^  |               ");
            mvwprintw (gamewin,12,50,"%s","            |  |  |               ");
            mvwprintw (gamewin,13,50,"%s","      -------------------         ");
            mvwprintw (gamewin,14,50,"%s","      |     |     |     |         ");
            mvwprintw (gamewin,15,50,"%s","      |  <- |  |  | ->  |         ");
            mvwprintw (gamewin,16,50,"%s","      |     |  v  |     |         ");
            mvwprintw (gamewin,17,50,"%s","      -------------------         ");
            mvwprintw (gamewin,18,50,"%s","         Sau W, S, A, D       ");
            mvwprintw (gamewin,22,50,"%s","      Apasati 'R' pentru restart");
            mvwprintw (gamewin,23,50,"%s","              'Q' pentru revenire la meniu");
            mvwprintw (gamewin,25,50,"%s","Daca in 7 secunde nu faceti nicio mutare noua");
            mvwprintw (gamewin,26,50,"%s","       se va face o mutare automata");


            wrefresh(gamewin);
}

void data_si_ora(WINDOW *gamewin)
{
time_t t = time(NULL);
struct tm tm = *localtime(&t);

mvwprintw(gamewin,20,48,"Data si ora actuala: %02d.%02d.%02d %02d:%02d", tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
wrefresh(gamewin);
}

void umple_casuta(int vect[])
{
    int casuta,val;
    srand(time(NULL));
    while(1)
    {
        casuta=rand() % 16;
        if(vect[casuta]==0)
        {
            val=rand();
            if(val%2==0)vect[casuta]=4;
            else vect[casuta]=2;
            return;
        }
    }
}
void highscore_save(int highscore)
{
    FILE *f=fopen("highscore","w");
    fprintf(f,"%d",highscore);
    fclose(f);
}
void save (int vect[],int scor)
{
    FILE *f;
    int i;
        f=fopen("saves","w");
         for(i=0;i<=16;i++)
            {if(i<16)
                fprintf(f,"%d ",vect[i]);
            else fprintf(f,"%d ",scor);
            if(i==3 || i==7 || i==11 || i==15)fprintf(f,"\n");
            }
            fprintf(f,"\n");
         fclose(f);
}
void load (int vect[], int *scor)
{
    FILE *f;
    int i;
    f=fopen("saves","r");
    for(i=0;i<=16;i++)
        {
            if(i<16)fscanf(f,"%d",&vect[i]);
            else fscanf(f,"%d",scor);
        }
    fclose(f);

}


int liber (int vect[])
{
    int i;
    for(i=0;i<16;i++)
      {
          if(vect[i]==2048)return 2;
      }
      for(i=0;i<16;i++)
      {
          if(vect[i]==0)return 1;
      }

        return 0;

}


int mutare_sus(int vect[])
{
    int i, j;
    int scor = 0;
    for (j=0;j<=5;j++) {
                if (j!=4) {
                    for (i=0;i<12;i++) {
                        if (vect[i] == 0) {
                            vect[i] = vect[i+4];
                            vect[i+4] = 0;
                        }
                    }
                } else {
                    for (i=0;i<12;i++) {
                        if (vect[i] == vect[i+4]) {
                            vect[i] = 2 * vect[i];
                            vect[i+4] = 0;
                            scor += vect[i];
                        }
                    }
                }
            }
    return scor;
}


int mutare_jos(int vect[])
{
    int i, j;
    int scor = 0;
     for (j=0;j<=5;j++) {
                if (j!=4) {
                    for (i=11;i>=0;i--) {
                        if (vect[i+4] == 0) {
                            vect[i+4] = vect[i];
                            vect[i] = 0;
                        }
                    }
                } else {
                    for (i=11;i>=0;i--) {
                        if (vect[i] == vect[i+4]) {
                            vect[i+4] = 2 * vect[i+4];
                            vect[i] = 0;
                            scor += vect[i+4];
                        }
                    }
                }
            }
    return scor;
}


int mutare_dreapta(int vect[])
{
    int i, j;
    int scor = 0;
    for (j=0;j<=5;j++) {
                if (j!=4) {
                    for (i=14;i>=0;i--) {
                        if (i == 3 || i == 7 || i == 11) {
                            continue;
                        }
                        if (vect[i+1] == 0) {
                            vect[i+1] = vect[i];
                            vect[i] = 0;
                        }
                    }
                } else {
                    for (i=14;i>=0;i--) {
                        if (i == 3 || i == 7 || i == 11) {
                            continue;
                        }
                        if (vect[i] == vect[i+1]) {
                            vect[i+1] = 2 * vect[i+1];
                            vect[i] = 0;
                            scor += vect[i+1];
                        }
                    }
                }
            }
    return scor;
}


int mutare_stanga(int vect[])
{
    int i, j;
    int scor = 0;
    for (j=0;j<=5;j++) {
                if (j!=4) {
                    for (i=0;i<=14;i++) {
                        if (i == 3 || i == 7 || i == 11)
                            continue;
                        if (vect[i] == 0) {
                            vect[i] = vect[i+1];
                            vect[i+1] = 0;
                        }
                    }
                } else {
                    for (i=0;i<=14;i++) {
                        if (i == 3 || i == 7 || i == 11)
                            continue;
                        if (vect[i] == vect[i+1]) {
                            vect[i] = 2 * vect[i];
                            vect[i+1] = 0;
                            scor += vect[i];
                        }
                    }
                }
            }
            return scor;

}
void patratel (int numar, int celula, WINDOW *gamewin)
{
    char before[5];
    char after[6];
    int row, col;
    int p_y, p_x;
    int num;

    init_color (1, 523, 867, 515);
    init_color (2, 402, 796, 984);
    init_color (3, 597, 199, 996);
    init_color (4, 996, 601, 601);
    init_color (5, 996, 886, 597);
    init_color (6, 636, 800, 285);
    init_color (7, 50, 660, 683);
    init_color (8, 421, 218, 597);
    init_color (9, 929, 769, 863);
    init_color (10, 578, 93, 93);
    init_color (11, 0, 0, 0);
    init_color (12, 781, 781, 781);
    init_color (13, 862, 784, 235);
    init_color (14, 737, 560, 560);
    init_color (15, 772, 756, 666);
    init_color (16, 823, 705, 549);

    switch (numar) {
        case 2:
            strcpy (before, "    ");
            strcpy (after, "     ");
            break;
        case 4:
            strcpy (before, "    ");
            strcpy (after, "     ");
            break;
        case 8:
            strcpy (before, "    ");
            strcpy (after, "     ");
            break;
        case 16:
            strcpy (before, "    ");
            strcpy (after, "    ");
            break;
        case 32:
            strcpy (before, "    ");
            strcpy (after, "    ");
            break;
        case 64:
            strcpy (before, "    ");
            strcpy (after, "    ");
            break;
        case 128:
            strcpy (before, "   ");
            strcpy (after, "    ");
            break;
        case 256:
            strcpy (before, "   ");
            strcpy (after, "    ");
            break;
        case 512:
            strcpy (before, "   ");
            strcpy (after, "    ");
            break;
        case 1024:
            strcpy (before, "   ");
            strcpy (after, "   ");
            break;
        case 2048:
            strcpy (before, "   ");
            strcpy (after, "   ");
            break;
        case 4096:
            strcpy (before, "   ");
            strcpy (after, "   ");
            break;
        case 8192:
            strcpy (before, "   ");
            strcpy (after, "   ");
            break;
        case 16384:
            strcpy (before, "  ");
            strcpy (after, "   ");
            break;
        case 32768:
            strcpy (before, "  ");
            strcpy (after, "   ");
            break;
        case 65536:
            strcpy (before, "  ");
            strcpy (after, "   ");
            break;
        default:
            break;
    }

    int count = 0;
    if (numar != 0) {
           num = numar;
        while (num != 2) {
            num = num >> 1;
            count += 1;
        }
    }
    row = (int) (celula/4+1);
    col = celula % 4 + 1;
    p_y = (row - 1) * 6 + 1;
    p_x = (col - 1) * 11 + 1;
    use_default_colors ();
   assume_default_colors(-1,-1);



    init_pair (1, COLOR_BLACK, -1);
    init_pair (2, COLOR_BLACK, 1);
    init_pair (3, COLOR_BLACK, 2);
    init_pair (4, COLOR_BLACK, 3);
    init_pair (5, COLOR_BLACK, 4);
    init_pair (6, COLOR_BLACK, 5);
    init_pair (7, COLOR_BLACK, 6);
    init_pair (8, COLOR_BLACK, 7);
    init_pair (9, COLOR_BLACK, 8);
    init_pair (10, COLOR_BLACK, 9);
    init_pair (11, COLOR_BLACK, 10);
    init_pair (12, COLOR_BLACK, 11);
    init_pair (13, COLOR_BLACK, 12);
    init_pair (14, COLOR_BLACK, 13);
    init_pair (15, COLOR_BLACK, 14);
    init_pair (16, COLOR_BLACK, 15);
    init_pair (17, COLOR_BLACK, 15);

    if (numar == 0) {
        wattron (gamewin,COLOR_PAIR(1));
        mvwprintw (gamewin,p_y, p_x, "          ");
        mvwprintw (gamewin,p_y+1, p_x, "          ");
        mvwprintw (gamewin,p_y+2, p_x, "          ");
        mvwprintw (gamewin,p_y+3, p_x, "          ");
        mvwprintw (gamewin,p_y+4, p_x, "          ");
        wattroff (gamewin,COLOR_PAIR(1));
    } else {
        wattron (gamewin,COLOR_PAIR(count+2));
        mvwprintw (gamewin,p_y, p_x, "          ");
        mvwprintw (gamewin,p_y+1, p_x, "          ");
        mvwprintw (gamewin,p_y+2, p_x, "%s%d%s", before, numar, after);
        mvwprintw (gamewin,p_y+3, p_x, "          ");
        mvwprintw (gamewin,p_y+4, p_x, "          ");
        wattroff (gamewin,COLOR_PAIR(count+2));
    }
    wrefresh (gamewin);
}


int valid(int vect[], int backup[])
{
    int nr=0,i;
    for(i=0;i<16;i++)
        if(vect[i]!=backup[i])nr++;
    if(nr!=0)return 1;
    return 0;
}


int final(int vect[], int continua)
{
    int i;
    int backup[16];

    for(i=0;i<16;i++)
       {
        if(vect[i]==2048 && continua!=0)return 1;
       }

    for(i=0;i<16;i++)
       {
           if(vect[i]==0)return 2;
       }

    for(i=0;i<16;i++)
       {
           backup[i]=vect[i];
       }
        mutare_sus(backup);
        mutare_jos(backup);
        mutare_stanga(backup);
        mutare_dreapta(backup);

      for(i=0;i<16;i++)
       {
           if(vect[i]!=backup[i])return 2;
       }

    return 0;
}

void new_game(WINDOW *menuwin, PANEL *menupan, int opt)
{
    char ch;
    int vect[16]={0},backup[16]={0}, scor=0, mutare=0,j,i,rez,continua=1,infinity=1,ok=0;
    int alone[16]={0},alegere=0,spatiu,highscore=0;
    dec directie[4],aux;
    WINDOW *gamewin;
    PANEL *gamepan;

    gamewin = newwin( 30, 100, 1, 1 );
     wrefresh( gamewin ); // update the terminal screen
    noecho(); // disable echoing of characters on the screen
    keypad( gamewin, TRUE ); // enable keyboard input for the window.
    curs_set( 0 );
    gamepan = new_panel(gamewin);

    game_grid(gamewin,gamepan);
    instructions(gamewin,gamepan);


    init_pair(18,COLOR_GREEN, COLOR_BLACK);
    wbkgd(gamewin, COLOR_PAIR(18));
    mvwprintw (gamewin,27,29,"Scor: %d ",scor);
    wrefresh(gamewin);
     if(opt==1)
     {
        umple_casuta(vect);
        umple_casuta(vect);
        save(vect,scor);
        wrefresh(gamewin);
        for (i=0;i<16;i++)
            patratel(vect[i], i,gamewin);
        wrefresh(gamewin);
        scor=0;
     }
     if(opt==0)
     {
         load(vect,&scor);
         save(vect,scor);
         wrefresh(gamewin);
        for (i=0;i<16;i++)
            patratel(vect[i], i,gamewin);
        wrefresh(gamewin);
     }

     FILE *f=fopen("highscore","r");
        fscanf(f,"%d",&highscore);
        if(scor>highscore)highscore=scor;
        fclose(f);
        mvwprintw(gamewin,27,6,"Highscore: %d",highscore);

    ch='\0';
    rez=2;
    srand(time(NULL));
    while(infinity)
    {
        data_si_ora(gamewin);


        if(rez!=0)
        {
           timeout(7000);
           ch=getch();
           if(tolower(ch)=='r')
        {
        for(i=0;i<16;i++)vect[i]=0;
        umple_casuta(vect);
        umple_casuta(vect);
        save(vect,scor);
        scor=0;
        }
        if(tolower(ch)=='q')
        {
            infinity=0;
        }
        mutare=0;
    for (i=0;i<16;i++)backup[i]=vect[i];
         for (i=0;i<16;i++)
            patratel(vect[i], i,gamewin);
        wrefresh(gamewin);

         if(ch=='w' || ch=='W')
         {scor+=mutare_sus(vect);mutare=1;}

         if(ch=='s' || ch=='S')
         {scor+=mutare_jos(vect);mutare=1;}

         if(ch=='a' || ch=='A')
         {scor+=mutare_stanga(vect);mutare=1;}

         if(ch=='d' || ch=='D')
         {scor+=mutare_dreapta(vect);mutare=1;}

          if (ch == '\033') { // if the first value is esc
    getch(); // skip the [
    switch(getch()) { // the real value
        case 'A':
            {scor+=mutare_sus(vect);mutare=1;}
            break;
        case 'B':
            {scor+=mutare_jos(vect);mutare=1;}
            break;
        case 'C':
            {scor+=mutare_dreapta(vect);mutare=1;}
            break;
        case 'D':
            {scor+=mutare_stanga(vect);mutare=1;}
            break;
    }
}
        if(ch == ERR)
        {
            //unplerea stucturii pentru alegerea directiei
            spatiu=0;
        for(i=0;i<16;i++)
            {
            alone[i]=vect[i];
            if(vect[i]==0)
            spatiu++;
            }
            for(i=0;i<4;i++)
                directie[i].scor=directie[i].spatiu=0;

            directie[0].scor=mutare_sus(alone);
            for(i=0;i<16;i++)
            {
            if(alone[i]==0)
            directie[0].spatiu++;
            alone[i]=vect[i];
            }
            strcpy(directie[0].nume,"SUS");

            directie[1].scor=mutare_jos(alone);
            for(i=0;i<16;i++)
            {
            if(alone[i]==0)
            directie[1].spatiu++;
            alone[i]=vect[i];
            }
            strcpy(directie[1].nume,"JOS");
            directie[2].scor=mutare_stanga(alone);
            for(i=0;i<16;i++)
            {
            if(alone[i]==0)
            directie[2].spatiu++;
            alone[i]=vect[i];
            }
            strcpy(directie[2].nume,"STANGA");

            directie[3].scor=mutare_dreapta(alone);
            for(i=0;i<16;i++)
            {
            if(alone[i]==0)
            directie[3].spatiu++;
            alone[i]=vect[i];
            }
            strcpy(directie[3].nume,"DREAPTA");
            for(i=0;i<4;i++)
                directie[i].spatiu=directie[i].spatiu-spatiu;
            //sortare dupa spatii
            for(i=0;i<3;i++)
                for(j=i+1;j<4;j++)
                {
                if(directie[i].spatiu<directie[j].spatiu)
                    {
                    aux=directie[i];
                    directie[i]=directie[j];
                    directie[j]=aux;
                    }
                }
             //efectuarea miscarii
             if(directie[0].spatiu > directie[1].spatiu)ok=0;
             if(directie[0].spatiu == directie[1].spatiu && directie[1].spatiu > directie[2].spatiu)ok=1;
             if(directie[0].spatiu == directie[1].spatiu && directie[1].spatiu == directie[2].spatiu && directie[2].spatiu > directie[3].spatiu)ok=2;
             if(directie[0].spatiu == directie[1].spatiu && directie[1].spatiu == directie[2].spatiu && directie[2].spatiu == directie[3].spatiu)ok=3;
             switch (ok)
             {
             case 0:
                if(strcmp(directie[0].nume,"SUS")==0)
                    scor+=mutare_sus(vect);mutare=1;
                if(strcmp(directie[0].nume,"JOS")==0)
                    scor+=mutare_jos(vect);mutare=1;
                if(strcmp(directie[0].nume,"STANGA")==0)
                    scor+=mutare_stanga(vect);mutare=1;
                if(strcmp(directie[0].nume,"DREAPTA")==0)
                    scor+=mutare_dreapta(vect);mutare=1;
                break;
             case 1:
                 alegere=rand()%2;
                 if(alegere==0)
                 {
                     if(strcmp(directie[0].nume,"SUS")==0)
                    scor+=mutare_sus(vect);mutare=1;
                if(strcmp(directie[0].nume,"JOS")==0)
                    scor+=mutare_jos(vect);mutare=1;
                if(strcmp(directie[0].nume,"STANGA")==0)
                    scor+=mutare_stanga(vect);mutare=1;
                if(strcmp(directie[0].nume,"DREAPTA")==0)
                    scor+=mutare_dreapta(vect);mutare=1;
                 }
                 if(alegere==1)
                 {
                     if(strcmp(directie[0].nume,"SUS")==0)
                    scor+=mutare_sus(vect);mutare=1;
                if(strcmp(directie[0].nume,"JOS")==0)
                    scor+=mutare_jos(vect);mutare=1;
                if(strcmp(directie[0].nume,"STANGA")==0)
                    scor+=mutare_stanga(vect);mutare=1;
                if(strcmp(directie[0].nume,"DREAPTA")==0)
                    scor+=mutare_dreapta(vect);mutare=1;
                 }
                 break;
             case 2:
                alegere=rand()%3;
                 if(alegere==0)
                 {
                     if(strcmp(directie[0].nume,"SUS")==0)
                    scor+=mutare_sus(vect);mutare=1;
                if(strcmp(directie[0].nume,"JOS")==0)
                    scor+=mutare_jos(vect);mutare=1;
                if(strcmp(directie[0].nume,"STANGA")==0)
                    scor+=mutare_stanga(vect);mutare=1;
                if(strcmp(directie[0].nume,"DREAPTA")==0)
                    scor+=mutare_dreapta(vect);mutare=1;
                 }
                 if(alegere==1)
                 {
                     if(strcmp(directie[1].nume,"SUS")==0)
                    scor+=mutare_sus(vect);mutare=1;
                if(strcmp(directie[1].nume,"JOS")==0)
                    scor+=mutare_jos(vect);mutare=1;
                if(strcmp(directie[1].nume,"STANGA")==0)
                    scor+=mutare_stanga(vect);mutare=1;
                if(strcmp(directie[1].nume,"DREAPTA")==0)
                    scor+=mutare_dreapta(vect);mutare=1;
                 }
                 if(alegere==2)
                 {
                     if(strcmp(directie[2].nume,"SUS")==0)
                    scor+=mutare_sus(vect);mutare=1;
                if(strcmp(directie[2].nume,"JOS")==0)
                    scor+=mutare_jos(vect);mutare=1;
                if(strcmp(directie[2].nume,"STANGA")==0)
                    scor+=mutare_stanga(vect);mutare=1;
                if(strcmp(directie[2].nume,"DREAPTA")==0)
                    scor+=mutare_dreapta(vect);mutare=1;
                 }
                 break;
             case 3:
                alegere=rand()%4;
                 if(alegere==0)
                 {
                     if(strcmp(directie[0].nume,"SUS")==0)
                    scor+=mutare_sus(vect);mutare=1;
                if(strcmp(directie[0].nume,"JOS")==0)
                    scor+=mutare_jos(vect);mutare=1;
                if(strcmp(directie[0].nume,"STANGA")==0)
                    scor+=mutare_stanga(vect);mutare=1;
                if(strcmp(directie[0].nume,"DREAPTA")==0)
                    scor+=mutare_dreapta(vect);mutare=1;
                 }
                 if(alegere==1)
                 {
                     if(strcmp(directie[1].nume,"SUS")==0)
                    scor+=mutare_sus(vect);mutare=1;
                if(strcmp(directie[1].nume,"JOS")==0)
                    scor+=mutare_jos(vect);mutare=1;
                if(strcmp(directie[1].nume,"STANGA")==0)
                    scor+=mutare_stanga(vect);mutare=1;
                if(strcmp(directie[1].nume,"DREAPTA")==0)
                    scor+=mutare_dreapta(vect);mutare=1;
                 }
                 if(alegere==2)
                 {
                     if(strcmp(directie[2].nume,"SUS")==0)
                    scor+=mutare_sus(vect);mutare=1;
                if(strcmp(directie[2].nume,"JOS")==0)
                    scor+=mutare_jos(vect);mutare=1;
                if(strcmp(directie[2].nume,"STANGA")==0)
                    scor+=mutare_stanga(vect);mutare=1;
                if(strcmp(directie[2].nume,"DREAPTA")==0)
                    scor+=mutare_dreapta(vect);mutare=1;
                 }
                  if(alegere==3)
                 {
                     if(strcmp(directie[3].nume,"SUS")==0)
                    scor+=mutare_sus(vect);mutare=1;
                if(strcmp(directie[3].nume,"JOS")==0)
                    scor+=mutare_jos(vect);mutare=1;
                if(strcmp(directie[3].nume,"STANGA")==0)
                    scor+=mutare_stanga(vect);mutare=1;
                if(strcmp(directie[3].nume,"DREAPTA")==0)
                    scor+=mutare_dreapta(vect);mutare=1;
                 }
                 break;

             }

        }
         mvwprintw (gamewin,27,29,"Scor: %d ",scor);
        if(scor>highscore)highscore=scor;
        mvwprintw(gamewin,27,6,"Highscore: %d",highscore);
         if(liber(vect) && mutare==1 && valid(vect,backup))umple_casuta(vect);
         save(vect,scor);
         highscore_save(highscore);

         rez=final(vect,continua);
         if(rez==1 && continua==1)
         {
           mvwprintw (gamewin,0,50,"%s", "   VICTORIE !!!");
           mvwprintw (gamewin,1,50,"%s", "               ");
           mvwprintw (gamewin,2,50,"%s", "Ai ajuns la 2048!!");
           mvwprintw (gamewin,3,50,"%s", "               ");
           mvwprintw (gamewin,4,50,"%s", "Poti continua pentru a face highscore");
           continua=0;
         }
         if(rez==0)
         {
             if(continua==1)
                {
                mvwprintw (gamewin,0,50,"%s", "   OH NU !!        ");
                mvwprintw (gamewin,1,50,"%s", "               ");
                mvwprintw (gamewin,2,50,"%s", "Ai pierdut !!!        ");
                mvwprintw (gamewin,3,50,"%s", "               ");
                mvwprintw (gamewin,4,50,"%s", "Apasa tasta Q pentru a reveni la meniu  ");
                }
             else
                {
                mvwprintw (gamewin,0,50,"%s", "  JOCUL S-A TERMINAT !!      ");
                mvwprintw (gamewin,1,50,"%s", "               ");
                mvwprintw (gamewin,2,50,"%s", "Apasa tasta Q pentru a reveni la meniu  ");
                mvwprintw (gamewin,3,50,"%s", "               ");
                mvwprintw (gamewin,4,50,"%s", "                                        ");
                }


            remove("saves");

         }

         wrefresh(gamewin);
        for (i=0;i<16;i++)
           patratel(vect[i], i,gamewin);
        wrefresh(gamewin);
        }
        if(rez==0)
        {
            ch=getch();
            if(tolower(ch)=='q')
                infinity=0;
        }
    }
    if(rez==0)
    {
        for(i=0;i<16;i++)vect[i]=0;
            scor=0;
    }
    highscore_save(highscore);
    hide_panel(gamepan);
    show_panel(menupan);
    update_panels();


}


int main()
{


    WINDOW *menuwin;
    PANEL *menupan;

    int i;
    initscr();
    menuwin = newwin( 6, 12, 1, 1 ); //(10, 12, 1, 1)
    box( menuwin, 0, 0 );
    menupan = new_panel(menuwin);

    if(access( "highscore", F_OK ) == -1 )
    {
        FILE *f=fopen("highscore","w");
    fprintf(f,"0\n");
    fclose(f);
    }


    while(1)
    {
        wrefresh(menuwin);
        menu_create(menuwin,menupan);
        i=menu_navig(menuwin,menupan);

    switch ( i )
        {
    case 0:
        hide_panel(menupan);
        update_panels();

        new_game(menuwin,menupan,0);
        wrefresh(menuwin);
        break;
    case 1:
       hide_panel(menupan);
       update_panels();

        new_game(menuwin,menupan,1);
        wrefresh(menuwin);
        break;
    case 2:
        delwin( menuwin );
        endwin();
        return 0;
        }

    }

    return 0;
}
