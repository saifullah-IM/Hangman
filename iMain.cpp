#include "iGraphics.h"

int sec,ck,mstk,rigt,mov,score,len,ltrs,ara[40],isInput,gamemode,idx,wrdinpt,lvl=1,cat=1,hscr[10];
char crntstr[40],level[3][10]={"Easy","Medium","Hard"},ctgry[6][15]={"Sports","Movie","History","Literature","Bangladesh","Science"};
double temp;

void newgame ()
{
    int i,cnt=0;
    len=strlen(crntstr);
    for (i=0;i<len;i++) if (crntstr[i]==' ') cnt++;
    ltrs=len-cnt;
    isInput=1;
    rigt=0;
    mstk=0;
    mov=0;
    ck=0;
    sec=0;
    memset(ara,0,sizeof(ara));
}

void getstr ()
{
    int i,n;

    rigt=0;
    ltrs=500;
    srand(time(NULL));
    n=rand();
    n%=15;

    if (lvl==1) {
        switch(cat) {
            case 1:
                freopen("texts\\sports1.txt","r",stdin);
                break;
            case 2:
                freopen("texts\\movie1.txt","r",stdin);
                break;
            case 3:
                freopen("texts\\history1.txt","r",stdin);
                break;
            case 4:
                freopen("texts\\literature1.txt","r",stdin);
                break;
            case 5:
                freopen("texts\\bangladesh1.txt","r",stdin);
                break;
            case 6:
                freopen("texts\\science1.txt","r",stdin);
                break;
        }
    }
    else if (lvl==2) {
        switch(cat) {
            case 1:
                freopen("texts\\sports2.txt","r",stdin);
                break;
            case 2:
                freopen("texts\\movie2.txt","r",stdin);
                break;
            case 3:
                freopen("texts\\history2.txt","r",stdin);
                break;
            case 4:
                freopen("texts\\literature2.txt","r",stdin);
                break;
            case 5:
                freopen("texts\\bangladesh2.txt","r",stdin);
                break;
            case 6:
                freopen("texts\\science2.txt","r",stdin);
                break;
        }
    }
    else if (lvl==3) {
        switch(cat) {
            case 1:
                freopen("texts\\sports3.txt","r",stdin);
                break;
            case 2:
                freopen("texts\\movie3.txt","r",stdin);
                break;
            case 3:
                freopen("texts\\history3.txt","r",stdin);
                break;
            case 4:
                freopen("texts\\literature3.txt","r",stdin);
                break;
            case 5:
                freopen("texts\\bangladesh3.txt","r",stdin);
                break;
            case 6:
                freopen("texts\\science3.txt","r",stdin);
                break;
        }
    }

    for (i=0;i<=n;i++) scanf (" %[^\n]",crntstr);
    fclose(stdin);

    wrdinpt=0;
    gamemode=2;
    newgame();
}

void takestr ()
{
    int x,y,i,dx,dy;
    rigt=0;
    mstk=0;
    ltrs=500;

    x=300,y=300;
    crntstr[idx]='\0';
    iShowBMP(0,0,"images\\Game_Window.bmp");

    iSetColor(240,240,240);
    iRectangle(x,y,500,50);
    iShowBMP(550,80,"images\\Keyboard_2.bmp");

    iSetColor(255,255,53);
    iText(x+20,y+10,crntstr,GLUT_BITMAP_TIMES_ROMAN_24);
}

void DrawHangman (int n)
{
    switch(n) {
        case 6:
            iShowBMP(200,332,"images\\6.bmp");
        case 5:
            iShowBMP(223,503,"images\\5.bmp");
        case 4:
            iShowBMP(69,501,"images\\4.bmp");
        case 3:
            iShowBMP(83,121,"images\\3.bmp");
        case 2:
            iShowBMP(57,101,"images\\2.bmp");
        case 1: {
            iShowBMP(206,101,"images\\1.bmp");
        }
    }
}

void DrawWordBox ()
{
    int x,y,i,dx,dy;

    x=300,y=300;
    dx=30,dy=30;

    iSetColor(240,240,240);
    for (i=0;i<len;i++) {
        if (crntstr[i]==' ') continue;
        iRectangle(x+i*dx,y,dx,dy);
    }
}

void DrawString ()
{
    int i,x,y,dx;
    char str[2];

    x=305,y=305,dx=30;

    iSetColor(255,255,53);
    for (i=0;i<len;i++) {
        if (ara[i]==1) {
            str[0]=crntstr[i];
            str[1]='\0';
            iText(x+i*dx,y,str,GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }
}

char* inttostr (int x)
{
    int i,ln,a;
    char *ptr,ch;
    ptr=(char *) malloc(10*sizeof(char));

    if (x==0) {
        *ptr='0';
        *(ptr+1)='\0';
    }
    else {
        ln=0;
        while (x!=0) {
            a=x%10;
            x/=10;
            *(ptr+ln)='0'+a;
            ln++;
        }
        *(ptr+ln)='\0';
        a=(ln-1)/2;

        for (i=0;i<=a;i++) {
            ch=*(ptr+i);
            *(ptr+i)=*(ptr+ln-1-i);
            *(ptr+ln-1-i)=ch;
        }
    }

    return ptr;
}

void ChkGame ()
{
    char *ptr;
    int i,x,y;

    ptr=(char *) malloc(25*sizeof(char));
    iSetColor(250,0,0);

    if (mstk>=6) {
        iShowBMP(445,360,"images\\Game_Over.bmp");
        iShowBMP(495,230,"images\\Sorry.bmp");
        iShowBMP(920,360,"images\\playagain.bmp");
        iShowBMP(920,230,"images\\Return.bmp");
        iText(550,180,"The word/phrase was",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,255,127);
        iText(780,180,crntstr,GLUT_BITMAP_TIMES_ROMAN_24);
        isInput=0;
    }
    else if (rigt>=ltrs) {
        iShowBMP(445,360,"images\\Game_Over.bmp");
        iShowBMP(495,230,"images\\Congrats.bmp");
        iShowBMP(920,360,"images\\playagain.bmp");
        iShowBMP(920,230,"images\\Return.bmp");
        isInput=0;
        if (gamemode==2) {
            if (ck==0) {
                temp=(1.0/sec)*(ltrs*1.0)*(ltrs*1000.0);
                if (mstk==0) temp*=2;
                else temp/=mstk;
            }
            score=round(temp);
            ptr=inttostr(score);
            iText(550,180,"Your score is",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(700,180,ptr,GLUT_BITMAP_TIMES_ROMAN_24);

            if (ck==0) {
                ck=1;
                switch (lvl) {
                    case 1: {
                        freopen("texts\\high_score1.txt","r",stdin);
                        break;
                    }
                    case 2: {
                        freopen("texts\\high_score2.txt","r",stdin);
                        break;
                    }
                    case 3: {
                        freopen("texts\\high_score3.txt","r",stdin);
                        break;
                    }
                }

                for (i=0;i<5;i++) {
                    scanf ("%d",&x);
                    if (x<score) {
                        hscr[i++]=score;
                        hscr[i++]=x;
                        break;
                    }
                    hscr[i]=x;
                }
                while (i<5) scanf ("%d",&hscr[i++]);
                fclose(stdin);

                switch (lvl) {
                    case 1: {
                        freopen("texts\\high_score1.txt","w",stdout);
                        break;
                    }
                    case 2: {
                        freopen("texts\\high_score2.txt","w",stdout);
                        break;
                    }
                    case 3: {
                        freopen("texts\\high_score3.txt","w",stdout);
                        break;
                    }
                }

                for (i=0;i<5;i++) printf ("%d\n",hscr[i]);
                fclose(stdout);
            }
        }
    }
}

void showHcr ()
{
    int i,j,k,dx,dy=330;
    char *ptr;

    iSetColor(255,178,102);
    for (j=1;j<=3;j++) {
        switch (j) {
            case 1: {
                freopen("texts\\high_score1.txt","r",stdin);
                dx=410;
                break;
            }
            case 2: {
                freopen("texts\\high_score2.txt","r",stdin);
                dx=737;
                break;
            }
            case 3: {
                freopen("texts\\high_score3.txt","r",stdin);
                dx=1062;
                break;
            }
        }

        for (i=0;i<5;i++) {
            scanf ("%d",&k);
            ptr=inttostr(k);
            iText(dx,dy-i*30,ptr,GLUT_BITMAP_TIMES_ROMAN_24);
        }

        fclose(stdin);
    }
}

void iDraw()
{
	iClear();
	if (gamemode==0) {
        iShowBMP(0,0,"images\\Home.bmp");
        return;
	}
	if (gamemode==3) {
        iShowBMP(0,0,"images\\Categories.bmp");
        iSetColor(250,128,114);
        iText(980,555,"Category: ",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(980,600,"Level: ",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,255,127);
        iText(1090,555,ctgry[cat-1],GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1050,600,level[lvl-1],GLUT_BITMAP_TIMES_ROMAN_24);
        return;
	}
	if (gamemode==1 || gamemode==2) {
        iShowBMP(0,0,"images\\Game_Window.bmp");
        if (wrdinpt==2) getstr();
        if (wrdinpt==1) takestr();
        DrawHangman (mstk);
        if (isInput==1) {
            DrawWordBox();
            DrawString();
            iShowBMP(550,80,"images\\Keyboard.bmp");
            if (gamemode==2) {
                iSetColor(250,128,114);
                iText(980,555,"Category: ",GLUT_BITMAP_TIMES_ROMAN_24);
                iText(980,600,"Level: ",GLUT_BITMAP_TIMES_ROMAN_24);
                iSetColor(0,255,127);
                iText(1090,555,ctgry[cat-1],GLUT_BITMAP_TIMES_ROMAN_24);
                iText(1050,600,level[lvl-1],GLUT_BITMAP_TIMES_ROMAN_24);
            }
        }
        ChkGame();
        return;
	}
	if (gamemode==4) {
        iShowBMP(0,0,"images\\About_Hangman.bmp");
        return;
	}
	if (gamemode==5) {
        iShowBMP(0,0,"images\\About_Us.bmp");
        return;
	}
	if (gamemode==6) {
        iShowBMP(0,0,"images\\High_Score.bmp");
        showHcr ();
        return;
	}
}

void iMouseMove(int mx, int my)
{
	///printf("x = %d, y= %d\n",mx,my);
}

void iMouse(int button, int state, int mx, int my)
{
    char ch;
    int i,p,isThere;

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (gamemode==1 || gamemode==2) {
            if(mx >= 605 && mx <= 1315 && my >= 80 && my <= 220)
            {
                ch='n';
                p=floor((mx*1.0-605.0)/54.62);
                ch+=p;
                if (my>150) ch-=13;

                if (wrdinpt==1) {
                    crntstr[idx]=ch;
                    idx++;
                }
                if (isInput==1) {
                    mov++;
                    isThere=0;
                    for (i=0;i<len;i++) {
                        if (crntstr[i]==ch) {
                            if (ara[i]==0) rigt++;
                            ara[i]=1;
                            isThere=1;
                        }
                    }

                    if (!isThere) mstk++;
                }
            }

            if (mx >= 920 && mx <= 1304 && my >= 360 && my <= 472){
                idx=0;
                wrdinpt=gamemode;
                return;
            }
            if (gamemode==2 && mx >= 920 && mx <= 1174 && my >= 230 && my <= 320) {
                gamemode=3;
                return;
            }
            if (gamemode==1 && mx >= 920 && mx <= 1174 && my >= 230 && my <= 320) {
                gamemode=0;
                return;
            }
        }
        if (gamemode==0) {
            if(mx >= 612 && mx <= 860 && my >= 406 && my <= 486) {
                gamemode=3;
                return;
            }
            if(mx >= 614 && mx <= 1320 && my >= 200 && my <= 282) {
                idx=0;
                mstk=0;
                rigt=0;
                len=-1;
                isInput=0;
                mov=0;
                gamemode=wrdinpt=1;
                return;
            }
            if(mx >= 874 && mx <= 1320 && my >= 406 && my <= 486) {
                gamemode=4;
                return;
            }
            if(mx >= 612 && mx <= 930 && my >= 304 && my <= 389) {
                gamemode=6;
                return;
            }
            if(mx >= 965 && mx <= 1320 && my >= 300 && my <= 386) {
                gamemode=5;
                return;
            }
        }

        if (gamemode==3) {
            if(mx >= 410 && mx <= 605 && my >= 113 && my <= 168) {
                idx=0;
                mstk=0;
                rigt=0;
                len=-1;
                isInput=0;
                mov=0;
                gamemode=wrdinpt=2;
                return;
            }
            if(mx >= 410 && mx <= 605 && my >= 56 && my <= 106) {
                gamemode=0;
                return;
            }
            if(mx >= 406 && mx <= 605 && my >= 189 && my <= 275) {
                lvl=3;
                return;
            }
            if(mx >= 406 && mx <= 605 && my >= 289 && my <= 363) {
                lvl=2;
                return;
            }
            if(mx >= 406 && mx <= 605 && my >= 386 && my <= 470) {
                lvl=1;
                return;
            }
            if(mx >= 619 && mx <= 861 && my >= 383 && my <= 471) {
                cat=1;
                return;
            }
            if(mx >= 619 && mx <= 861 && my >= 286 && my <= 366) {
                cat=2;
                return;
            }
            if(mx >= 619 && mx <= 861 && my >= 185 && my <= 274) {
                cat=3;
                return;
            }
            if(mx >= 899 && mx <= 1196 && my >= 383 && my <= 470) {
                cat=4;
                return;
            }
            if(mx >= 899 && mx <= 1196 && my >= 289 && my <= 368) {
                cat=5;
                return;
            }
            if(mx >= 899 && mx <= 1196 && my >= 185 && my <= 274) {
                cat=6;
                return;
            }
        }

        if (gamemode==4) {
            if(mx >= 1008 && mx <= 1261 && my >= 542 && my <= 633) {
                gamemode=0;
                return;
            }
        }

        if (gamemode==5) {
            if(mx >= 1010 && mx <= 1266 && my >= 532 && my <= 623) {
                gamemode=0;
                return;
            }
        }

        if (gamemode==6) {
            if(mx >= 1014 && mx <= 1269 && my >= 540 && my <= 628) {
                gamemode=0;
                return;
            }
        }
	}
}

void iKeyboard(unsigned char key)
{
    int i,isThere=0;

    if (key>='A' && key<='Z') key+=32;
    if (wrdinpt==1) {
        if (key=='\r') {
            wrdinpt=0;
            gamemode=1;
            newgame();
            return;
        }
        else if (key=='\b' && idx>0) idx--;
        else if ((key>='a' && key<='z') || key==' ') {
            crntstr[idx]=key;
            idx++;
        }
    }

    if (isInput==1) {
        mov++;
        for (i=0;i<len;i++) {
            if (crntstr[i]==key) {
                if (ara[i]==0) rigt++;
                ara[i]=1;
                isThere=1;
            }
        }

        if (!isThere) mstk++;
    }
}

void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END) {
		exit(0);
	}
}

void update ()
{
    sec++;
}

int main()
{
    iSetTimer(1000,update);
	iInitialize(1320, 670, "HANGMAN");
	return 0;
}
