#include <allegro.h>


volatile long fps = 0;
volatile long frames = 0;
int a = rand() % 600;
int c = rand() % 600;
int d = 0;
int k = rand() % 600;
int l = 0;
int fx= 0;
int fy = 380;
int x = 0;
int y = 330;
int f = 1;
int lives = 3;
int b = 0;
int score = 0;
int bx1 = rand() % 600;
int by1 = 0;
int bx2 = rand() % 600;
int by2 = 0;
int bx3 = rand() % 600;
int by3 = 0;
int difficulty = 0;
bool mute = false;

void initialize()
{
     allegro_init();
     install_keyboard();
     install_timer();
     install_sound (DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
     set_color_depth(32);   
     set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0);   
}
void loopframes()
{
     if (frames > 180) frames = 0;
}
void incfps()
{
     fps++;
}
void objects()
{
  b += 4;
  d += 4;
  l += 4;
  by1 += 4;
  by2 += 4;
  by3 += 4;
}
void resetgraphics()
{
     if ( b < fy+20 && b+20 > fy )
     {
          b = 0;
          a = rand() % 600;
     }
     if (d <fy+20 && d+20 > fy)
     {
           d =0;
           c = rand() % 600;
     }
     if (l <fy+20 && l+20 > fy)
     {
           l =0;
           k = rand() % 600;
     }
      if (by1 <fy+20 && by1+20 > fy)
     {
           by1 =0;
           bx1 = rand() % 600;
     }
     if (by2 <fy+20 && by2+20 > fy)
     {
           by2 =0;
           bx2 = rand() % 600;
     }
     if (by3 <fy+20 && by3+20 > fy)
     {
           by3 =0;
           bx3 = rand() % 600;
     }
}

void collision()
{
  if ( a <= x+20 && a+20 >= x && b <= y+20 && b+20 >= y)
     { ++ score;
     b =0;
     a = rand() % 600;
     } 
     if ( c <= x+25 && c+25 >= x && d <= y+25 && d+25 >= y)
     {  ++score;
     d =0;
     c = rand() % 600;
     }  
     if ( k <= x+25 && k+25 >= x && l <= y+25 && l+25 >= y)
     { ++ score;
     l =0;
     k = rand() % 600;
     }  
     if ( bx1 <= x+25 && bx1+25 >= x && by1 <= y+25 && by1+25 >= y)
     { -- lives;
     by1 =0;
     bx1 = rand() % 600;
     }   
     if ( bx2 <= x+25 && bx2+25 >= x && by2 <= y+25 && by2+25 >= y && difficulty == 1)
     { -- lives;
     by2 =0;
     bx2 = rand() % 600;
     } 
     if ( bx3 <= x+25 && bx3+25 >= x && by3 <= y+25 && by3+25 >= y && difficulty == 2)
     { -- lives;
     by3 =0;
     bx3 = rand() % 600;
     }
}
void dchange()
{if(key[KEY_1]) difficulty = 0;
else if(key[KEY_2]) difficulty = 1;
else if(key[KEY_3]) difficulty = 2;
}
void volume()
{
     if (mute == true) set_volume(0,0);
     else if (mute == false) set_volume(255,255);
     if (key[KEY_M] && mute == false)
     { mute = true;
     rest(100);}
     else if (key[KEY_M] && mute == true)
     { mute = false;
     rest(100);}
}
int main()
{
   initialize();
   LOCK_VARIABLE (fps);
   LOCK_FUNCTION (incfps);
   install_int_ex( incfps, BPS_TO_TIMER(90) );
   
   BITMAP *buffer = create_bitmap(640,480);
   BITMAP *josh = load_bitmap("joshsprite.bmp", NULL);
   BITMAP *joshf = load_bitmap("joshleft.bmp",NULL);
   BITMAP *background = load_bitmap("background.bmp", NULL); 
   BITMAP *floor = load_bitmap("floor.bmp", NULL);
   BITMAP *joshforward =load_bitmap("joshforward.bmp",NULL);
   BITMAP *card = load_bitmap("card.bmp", NULL);
   BITMAP *book = load_bitmap("book.bmp", NULL);
   BITMAP *sock = load_bitmap("sock.bmp", NULL);
   BITMAP *bomb = load_bitmap("bomb.bmp", NULL);
   BITMAP *titlebackground = load_bitmap("titlebackground.bmp",NULL);
   BITMAP *EGB = load_bitmap("endgamebackground.bmp", NULL);
   BITMAP *bomb2 = load_bitmap("bomb.bmp", NULL);
   BITMAP *bomb3 = load_bitmap("bomb.bmp",NULL);
   MIDI *lost = load_midi("gameover.mid");
   MIDI *music = load_midi("BM.mid");
   srand (time(NULL));
   
   while (!key[KEY_ESC])
   { play_midi(music,true);
         
        
           while (!key[KEY_ENTER] && !key[KEY_ESC])
    {
           volume();
              while (key[KEY_F3])
    {
          
          rectfill(buffer,0,0,640,480,makecol(0,0,0));
          textout_ex(buffer, font,"Instructions:", 40, 40, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"Use the Left and Right arrow keys to move", 70, 100, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"Collect the Socks, Books and Cards to gain points", 70, 140, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"You have 3 lives", 70, 180, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"Avoid the bombs, they kill you", 70, 220, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"Toggle difficulty with the 1,2,3 keys", 70, 260, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"Pause the game by clicking off the game (clicking outside the window)", 70, 300, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"Toggle sound by pressing M", 70, 340, makecol(255,255,255),makecol(0,0,0));
          
          blit(buffer, screen,0,0,0,0,640,480);
          clear_bitmap(buffer);
}
          blit(titlebackground, buffer, 0,0,0,0, 640, 480);
          textout_ex(buffer, font,"Version: 1.4", 530, 10, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"Press Enter to play!", 150, 240, makecol(255,255,255),makecol(0,0,0)); 
          textout_ex(buffer, font,"Press F3 to view instructions", 10, 10, makecol(255,255,255),makecol(0,0,0));  
          rectfill(buffer,380,260,600,440,makecol(0,0,0));        
          textout_ex(buffer, font,"Your name is Josh.", 390, 285, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"You are eighteen.", 390, 315, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"You are teething again.", 390, 345, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"Eat everything.", 390, 375, makecol(255,255,255),makecol(0,0,0));
          textout_ex(buffer, font,"Except bombs.", 390, 405, makecol(255,255,255),makecol(0,0,0));
          blit(buffer,screen,0,0,0,0, 640, 480);
          clear_bitmap(buffer);
      
    }
     while (lives != 0 && !key[KEY_ESC])
       {
         while ( fps > 0)
         {   
               if (key[KEY_RIGHT] && x !=590) x += 4;
               else if (key[KEY_LEFT] && x !=0) x -= 4;
               dchange();
               volume();
               collision();
               resetgraphics();
               objects();
               fps -= 1;
               ++frames;
               loopframes();
         }
         blit(background, buffer, 0,0,0,0, 640, 480);
         draw_sprite(buffer, card, a, b);
         draw_sprite(buffer, book, c, d);
         draw_sprite(buffer,sock,k,l);
         if (difficulty == 0)
         {draw_sprite(buffer, bomb,bx1,by1);}
         else if(difficulty == 1)
         {draw_sprite(buffer, bomb,bx1,by1);
         draw_sprite(buffer, bomb2,bx2,by2);}
         else if (difficulty == 2)
         {draw_sprite(buffer, bomb,bx1,by1);
         draw_sprite(buffer, bomb2,bx2,by2);
         draw_sprite(buffer, bomb3, bx3, by3);}
         draw_sprite(buffer, floor, fx, fy);
         if (!key[KEY_LEFT] && !key[KEY_RIGHT])draw_sprite(buffer,joshforward,x,y);
         if (key[KEY_RIGHT])draw_sprite(buffer,josh,x,y);
         else if (key[KEY_LEFT])draw_sprite(buffer,joshf,x,y);
         textout_ex(buffer, font,"Version: 1.4", 530, 10, makecol(255,255,255),makecol(0,0,0));
         textout_ex(buffer, font,"Press Esc to exit the game", 10, 10, makecol(255,255,255),makecol(0,0,0));
         textprintf(buffer, font, 10, 20, makecol(255,255,255), "Score: %i", score);
         textprintf(buffer, font, 10, 30, makecol(255,255,255), "Lives: %i", lives);
         if (score <=80)
         textout_ex(buffer, font, "Rank: Noob", 10, 40,makecol(255,255,255),makecol(0,0,0));
         else if (score >80 && score <=150)
         textout_ex(buffer, font, "Rank: Amatuer", 10, 40,makecol(255,255,255),makecol(0,0,0));
         else if (score >150 && score <=250)
         textout_ex(buffer, font, "Rank: Average", 10, 40,makecol(255,255,255),makecol(0,0,0));
         else if (score >250 && score  <=400)
         textout_ex(buffer, font,"Rank: Pro", 10, 40,makecol(255,255,255),makecol(0,0,0));
         else if(score > 400)
         textout_ex(buffer, font, "Rank: Star!", 10, 40,makecol(255,255,255),makecol(0,0,0));
         blit(buffer,screen,0,0,0,0, 640, 480);
         clear_bitmap(buffer);
         release_screen();
   }

   play_midi(lost,false);
     while (!key[KEY_ESC] && !key[KEY_ENTER])
     {
           
     blit(EGB,buffer,0,0,0,0, 640, 480);
     textout_ex(buffer, font,"Press Esc to exit the game", 10, 10, makecol(255,255,255),makecol(0,0,0));
     textout_ex(buffer, font,"Press Enter to play again", 10, 30, makecol(255,255,255),makecol(0,0,0));
     textout_ex(buffer, font,"GAME OVER!", 270, 240, makecol(255,255,255),makecol(0,0,0));
     textprintf(buffer, font, 255, 260, makecol(255,255,255), "Final Score: %i", score);
     if (score <=80)
     textout_ex(buffer, font, "Rank: Noob", 270, 280,makecol(255,255,255),makecol(0,0,0));
     
     else if (score >80 && score <=150)
     textout_ex(buffer, font, "Rank: Amatuer", 270, 280,makecol(255,255,255),makecol(0,0,0));
     
     else if (score >150 && score <=250)
     textout_ex(buffer, font, "Rank: Average", 270, 280,makecol(255,255,255),makecol(0,0,0));
     
     else if (score >250 && score  <=400)
     textout_ex(buffer, font,"Rank: Pro", 270, 280,makecol(255,255,255),makecol(0,0,0));
     
     else if(score > 400)
     textout_ex(buffer, font, "Rank: Star!", 270, 280,makecol(255,255,255),makecol(0,0,0));
     blit(buffer,screen,0,0,0,0, 640, 480);
     }
     score = 0;
     lives = 3;
     }

    destroy_bitmap(EGB);
    destroy_bitmap(titlebackground);
    destroy_bitmap(bomb);
    destroy_bitmap(sock);
    destroy_bitmap(book);
    destroy_bitmap(card);
    destroy_bitmap(buffer);
    destroy_bitmap(josh);
    destroy_bitmap(joshf);
    destroy_bitmap(floor);
    destroy_bitmap(background);
    destroy_bitmap(joshforward);
    destroy_midi(music);
    destroy_midi(lost);
    return 0;
}
END_OF_MAIN();
