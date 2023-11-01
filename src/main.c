#include "lcd/lcd.h"
#include <string.h>
#include "systick.h"
#include "utils.h"
#include <img.h>
#include <stdio.h>
//#include <stdlib.h.>
#include <time.h>

int px[160];
int py[160];
int head = 0;
int tail = 0;
int pointernum=0;

void Inp_init(void)
{
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}

void Adc_init(void) 
{
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_1);
    RCU_CFG0|=(0b10<<14)|(1<<28);
    rcu_periph_clock_enable(RCU_ADC0);
    ADC_CTL1(ADC0)|=ADC_CTL1_ADCON;
}

void IO_init(void)
{
    Inp_init(); // inport init
    Adc_init(); // A/D init
    Lcd_Init(); // LCD init
}


typedef struct Bat
{
    int status;
    int height_u;
    int height_d;
    int index_l;
    int index_r;
}bat;

typedef struct Cactus
{
    int height_u;
    int height_d;
    int index_l;
    int index_r;
}cactus;

typedef struct Dinosaur
{
    int run_status;
    int height_u;
    int height_d;
}dina;

void bat_move(bat** a,int *num)
{
    if((*num) == 0){return;}
    
    else if((*num) == 1)
    {
        int index;
        for(int i = 0;i<2;++i)
            {if(a[i] != NULL){index = i;break;}}
        if(a[index]->index_l == 0)
        {
            --(*num);
            LCD_Fill(a[index]->index_l , a[index]->height_u , a[index]->index_r - 1, a[index]->height_d - 1, 0x0000);
            free(a[index]);a[index] = NULL;
            return;
        }
        if (a[index]->status == 1)
        {
            LCD_Fill(a[index]->index_l , a[index]->height_u , a[index]->index_r - 1, a[index]->height_d - 1, 0x0000);
            a[index]->index_l -= 2;a[index]->index_r -= 2;
            LCD_ShowPic(a[index]->index_l , a[index]->height_u , a[index]->index_r - 1, a[index]->height_d - 1, pter2);
            a[index]->status = 0;
        }
        else
        {
            LCD_Fill(a[index]->index_l , a[index]->height_u , a[index]->index_r - 1, a[index]->height_d - 1, 0x0000);
            a[index]->index_l -= 2;a[index]->index_r -= 2;
            LCD_ShowPic(a[index]->index_l , a[index]->height_u , a[index]->index_r - 1, a[index]->height_d - 1, pter1);
            a[index]->status = 1;
        }
    }
    else
    {
        if(a[0]->index_l == 0)
        {
            --(*num);
            LCD_Fill(a[0]->index_l , a[0]->height_u , a[0]->index_r - 1, a[0]->height_d - 1, 0x0000);
            free(a[0]);a[0] = NULL;
            return;
        }
        if(a[1]->index_l == 0)
        {
            --(*num);
            LCD_Fill(a[1]->index_l , a[1]->height_u , a[1]->index_r - 1, a[1]->height_d - 1, 0x0000);
            free(a[1]);a[1] = NULL;
            return;
        }

        if (a[0]->status == 1)
        {
            LCD_Fill(a[0]->index_l , a[0]->height_u , a[0]->index_r - 1, a[0]->height_d - 1, 0x0000);
            a[0]->index_l -= 2;a[0]->index_r -= 2;
            LCD_ShowPic(a[0]->index_l , a[0]->height_u , a[0]->index_r - 1, a[0]->height_d - 1, pter2);
            a[0]->status = 0;
        }
        else
        {
            LCD_Fill(a[0]->index_l , a[0]->height_u , a[0]->index_r - 1, a[0]->height_d - 1, 0x0000);
            a[0]->index_l -= 2;a[0]->index_r -= 2;
            LCD_ShowPic(a[0]->index_l , a[0]->height_u , a[0]->index_r - 1, a[0]->height_d - 1, pter1);
            a[0]->status = 1;
        }
        if (a[1]->status == 1)
        {
            LCD_Fill(a[1]->index_l , a[1]->height_u , a[1]->index_r - 1, a[1]->height_d - 1, 0x0000);
            a[1]->index_l -= 2;a[1]->index_r -= 2;
            LCD_ShowPic(a[1]->index_l , a[1]->height_u , a[1]->index_r - 1, a[1]->height_d - 1, pter2);
            a[1]->status = 0;
        }
        else
        {
            LCD_Fill(a[1]->index_l , a[1]->height_u , a[1]->index_r - 1, a[1]->height_d - 1, 0x0000);
            a[1]->index_l -= 2;a[1]->index_r -= 2;
            LCD_ShowPic(a[1]->index_l , a[1]->height_u , a[1]->index_r - 1, a[1]->height_d - 1, pter1);
            a[1]->status = 1;
        }

    }
}

void cac_move(cactus** a,int *num)
{
    if((*num) == 0){return;}
    
    else if((*num) == 1)
    {
        int index;
        for(int i = 0;i<2;++i)
            {if(a[i] != NULL){index = i;break;}}
        if(a[index]->index_l == 0)
        {
            --(*num);
            LCD_Fill(a[index]->index_l , a[index]->height_u , a[index]->index_r - 1, a[index]->height_d - 1, 0x0000);
            free(a[index]);a[index] = NULL;
            return;
        }
        LCD_Fill(a[index]->index_l , a[index]->height_u , a[index]->index_r - 3, a[index]->height_d - 1, 0x0000);
        a[index]->index_l -= 2;a[index]->index_r -= 2;
        LCD_ShowPic(a[index]->index_l , a[index]->height_u , a[index]->index_r - 1, a[index]->height_d - 1, cactus2);
    }
    else
    {
        if(a[0]->index_l == 0)
        {
            --(*num);
            LCD_Fill(a[0]->index_l , a[0]->height_u , a[0]->index_r - 3, a[0]->height_d - 1, 0x0000);
            free(a[0]);a[0] = NULL;
            return;
        }
        if(a[1]->index_l == 0)
        {
            --(*num);
            LCD_Fill(a[1]->index_l , a[1]->height_u , a[1]->index_r - 3, a[1]->height_d - 1, 0x0000);
            free(a[1]);a[1] = NULL;
            return;
        }

        LCD_Fill(a[0]->index_l , a[0]->height_u , a[0]->index_r - 3, a[0]->height_d - 1, 0x0000);
        a[0]->index_l -= 2;a[0]->index_r -= 2;
        LCD_ShowPic(a[0]->index_l , a[0]->height_u , a[0]->index_r - 1, a[0]->height_d - 1, cactus2);

        LCD_Fill(a[1]->index_l , a[1]->height_u , a[1]->index_r - 3, a[1]->height_d - 1, 0x0000);
        a[1]->index_l -= 2;a[1]->index_r -= 2;
        LCD_ShowPic(a[1]->index_l , a[1]->height_u , a[1]->index_r - 1, a[1]->height_d - 1, cactus2);

    }
}

bat* creat_bat(bat** arr,int* num,const cactus** data,const int cac_num)
{
    int index;
    if(cac_num == 1)
    {
        for(int i = 0;i<2;++i)
            {if(data[i] != NULL){index = i;break;}}
        if(data[index]->index_r > 100){return NULL;} 
    }
    if(cac_num == 2)
    {
        if(data[0]->index_r > 100 || data[1]->index_r > 100){return NULL;} 
    }
    if((*num) == 1)
    {
        for(int i = 0;i<2;++i)
            {if(arr[i] != NULL){index = i;break;}}
        if(arr[index]->index_r > 134){return NULL;} 
    }
    ++(*num);
    bat* target = (bat*)malloc(sizeof(int) * 5);
    if((rand() % 10 + 1) < 4)
    {
        target->height_u = 25;
        target->height_d = 45;
    }
    else
    {
        target->height_u = 15;
        target->height_d = 35;
    }
    target->index_l = 140;
    target->index_r = 160;
    return target;
}

cactus* creat_cac(cactus** arr,int* num,const bat** data,const int bat_num)
{
    int index;
    if(bat_num == 1)
    {
        for(int i = 0;i<2;++i)
            {if(data[i] != NULL){index = i;break;}}
        if(data[index]->index_r > 100){return NULL;} 
    }
    if(bat_num == 2)
    {
        if(data[0]->index_r > 100 || data[1]->index_r > 100){return NULL;} 
    }
    if((*num) == 1)
    {
        for(int i = 0;i<2;++i)
            {if(arr[i] != NULL){index = i;break;}}
        if(arr[index]->index_r > 109){return NULL;} 
    }
    ++(*num);
    cactus* target = (cactus*)malloc(sizeof(int) * 4);
    target->height_u = 39;
    target->height_d = 59;
    target->index_l = 148;
    target->index_r = 160;
    return target;
}

void pop(){
    if (head != 159)
    {
        head = head + 1;
    }else{
        head = 0;
    }
    pointernum--;
}


void push(int x,int y){
    if (tail != 159)
    {
        px[tail]=x;
        py[tail]=y;
        tail = tail + 1;       
    }else{
        px[tail]=x;
        py[tail]=y;
        tail = 0;
    }
    pointernum++;
}

void pointer_create(void)
{
    int num1;
    int num2;
	num1= rand() % 100 + 1; 
    num2= rand() % 10 + 1;
    
    if (num1 <= 9){
        int tempx = 159;
        int tempy = 63 + num2;
        push(tempx,tempy);
        //LCD_DrawPoint(tempx,tempy,WHITE);
    }
}


void pointer_move(void)
{
    int index;
    if(pointernum != 0){
        if (px[head] < 1)
        {
            LCD_DrawPoint(px[head],py[head],BLACK);
            pop();
        }
    }
    for (int i = 0; i < pointernum; i++)
    {
        index = head + i;
        if (index > 159)
        {
            index = index - 160;
        }
        LCD_DrawPoint(px[index],py[index],BLACK);
        px[index] = px[index] - 1;
        LCD_DrawPoint(px[index],py[index],WHITE);
        //LCD_ShowNum(20,20,pointernum,5,GREEN);
    }
}
void dinosaur_run_changepic(int x0,char* x1,char* x2);

void dinosaur_run(dina* a,int* state,int* lock,int* whed,int* down_first,int* jump_down_first,int *hedown)
{
    if((*hedown) == 1){(*hedown) = 0;}
    if((*lock) == 0)
    {
        if(Get_Button(1)){(*state) = 1;(*lock) = 1;}
        if(Get_Button(3)){(*state) = 3;(*lock) = 1;}
    }
    if(*state == 0)
    {
        *down_first = 1;
        LCD_Fill(40 , 45 , 47 - 1, 60 - 1, 0x0000);
        if (a->run_status == 1)
        {
            // LCD_Fill(35 , 55 , 37 - 1, 60 - 1, 0x0000);
            // LCD_ShowPic(20 , 40 , 40 - 1, 60 - 1, trex2);
            dinosaur_run_changepic(a->run_status,trex1,trex2);
            a->run_status = 0;
        }
        else if(a->run_status == 0)
        {
            // LCD_Fill(35 , 55 , 37 - 1, 60 - 1, 0x0000);
            // LCD_ShowPic(20 , 40 , 40 - 1, 60 - 1, trex1);
            dinosaur_run_changepic(a->run_status,trex1,trex2);
            a->run_status = 1;
        }
        return;
    }
    if(*state == 1) //jump
    {
        *down_first = 1;
        if((*whed) == 0)
        {
            LCD_Fill(20 , a->height_u , 40 - 1, a->height_d - 1, 0x0000);
            a->height_u--;a->height_u--;a->height_u--;
            a->height_d--;a->height_d--;a->height_d--;
            LCD_ShowPic(20 , a->height_u , 40 - 1, a->height_d - 1, trex3);
            if(a->height_u < 9)
            {
                (*whed) = 1;
                *jump_down_first = 5;
            }
        }
        if((*whed) == 1)
        {
            (*jump_down_first)--;
            if((*jump_down_first) > 0){return;}
            LCD_Fill(20 , a->height_u , 40 - 1, a->height_d - 1, 0x0000);
            a->height_u++;a->height_u++;a->height_u++;
            a->height_d++;a->height_d++;a->height_d++;
            LCD_ShowPic(20 , a->height_u , 40 - 1, a->height_d - 1, trex3);
            if(a->height_u == 40){*state = 0;*whed = 0;*lock = 0;return;}
        }
    }
    if(*state == 3) //head_down
    {
        (*hedown) = 1;
        if(*down_first == 1){*down_first = 0;LCD_Fill(20 , 40 , 40 - 1, 60 - 1, 0x0000);}
        if (a->run_status == 1)
        {
            LCD_ShowPic(20 , 40 , 47 - 1, 60 - 1, trex4);
            a->run_status = 0;
        }
        else if(a->run_status == 0)
        {
            LCD_ShowPic(20 , 40 , 47 - 1, 60 - 1, trex5);
            a->run_status = 1;
        }
        *state = 0;*lock = 0;
        return;
    }
}

void end_game(char* x);


void draw_line_dino(unsigned char* temp);

void draw_title(char* x0,char* x1);

void draw_ready(char* x0,char* x1,char* x2);

void draw_difficulty(char* x0,char* x1,char* x2);

int main(void)
{
    IO_init();         // init OLED
    // YOUR CODE HERE
    LCD_Clear(BLACK);

    int speed;
    int invincible = 0;
    int energy = 0;
    int chart = 2;

    char menu[] = {"Dinosaur"};
    char menu1[] = {"Runnnnnnnn!"};
    draw_title(menu,menu1); //draw the title
    // LCD_ShowString(40,10,menu,BLUE);
    // LCD_ShowString(35,40,menu1,BLUE);
    // delay_1ms(2000);
    // LCD_Clear(BLACK);

    char menu2[] = {"Ready Go?"};
    char menu3[] = {"Yes"},menu4[] = {"No"};
    draw_ready(menu2,menu3,menu4);  //draw the ready
    // LCD_ShowString(45,12,menu2,GREEN);
    // LCD_ShowString(26,42,menu3,GREEN);
    // LCD_ShowString(125,42,menu4,GREEN);


    for(;;)
    {
        if(Get_Button(1)){break;}
        else if(Get_Button(3)){LCD_Clear(BLACK);return 0;}
    }
    LCD_Clear(BLACK);
    delay_1ms(1000);
    char menu5[] = {"Select difficulty"};
    char menu6[] = {"easy"},menu7[] = {"hard"};
    char meme[] = {"!invincible!"};
    // draw_difficulty(menu5,menu6,menu7);
    // LCD_Clear(BLACK);
    LCD_ShowString(14,12,menu5,GREEN);
    LCD_ShowString(25,42,menu6,GREEN);
    LCD_ShowString(110,42,menu7,GREEN);
    for(;;)
    {
        if(Get_Button(1)){speed = 65;break;}
        else if(Get_Button(3)){speed = 25;break;}
    }
    LCD_Clear(BLACK);

    delay_1ms(999);

    draw_line_dino(trex3);

    int end_flag = 0;
    int if_head_down = 0;
    dina game_boy = {1,40,60};
    int lock = 0,rstate = 0,down_first = 1,jump_down_first = 0;
    int bat_num = 0,cac_num = 0,whether_down = 0;
    bat** bat_array = (bat**)malloc(sizeof(bat*) * 2);
    cactus** cac_array = (cactus**)malloc(sizeof(cactus*) * 2);
    bat_array[0] = NULL;bat_array[1] = NULL;
    cac_array[0] = NULL;cac_array[1] = NULL;


    int mark = 0;
    for (;;)
    {
        delay_1ms(speed);
        LCD_ShowNum(120,2,mark,4,WHITE);
        LCD_DrawRectangle(2,2,60,5,YELLOW);
        ++mark;
        dinosaur_run(&game_boy,&rstate,&lock,&whether_down,&down_first,&jump_down_first,&if_head_down);          ///////
        pointer_create();
        pointer_move();
        pointer_move();
        if(bat_num < 2 && (rand() % 299 + 1) < 3)
        {
            for(int i = 0;i<2;++i)
            {
                if(bat_array[0] == NULL){bat_array[0] = creat_bat(bat_array,&bat_num,cac_array,cac_num);break;}
                else if(bat_array[1] == NULL){bat_array[1] = creat_bat(bat_array,&bat_num,cac_array,cac_num);}
            }
        }
        if(cac_num < 2 && (rand() % 299 + 1) < 3)
        {
            for(int i = 0;i<2;++i)
            {
                if(cac_array[0] == NULL){cac_array[0] = creat_cac(cac_array,&cac_num,bat_array,bat_num);break;}
                else if(cac_array[1] == NULL){cac_array[1] = creat_cac(cac_array,&cac_num,bat_array,bat_num);}
            }
        }
        bat_move(bat_array,&bat_num);
        cac_move(cac_array,&cac_num);

        for(int i = 0;i<2;++i)
        {
            if(invincible == 1){break;}
            if(bat_array[i] != NULL)
            {
                if(bat_array[i]->height_d == 45)
                {
                    if(bat_array[i]->index_l < 38 && bat_array[i]->index_r > 24 && if_head_down == 0){end_flag = 1;break;}
                }
                else
                {
                    if(bat_array[i]->index_l < 38 && bat_array[i]->index_r > 24 && game_boy.height_u < 32){end_flag = 1;break;}
                }
            }
            if(cac_array[i] != NULL)
            {
                if(cac_array[i]->index_l < 38 && cac_array[i]->index_r > 32 && game_boy.height_d > 45){end_flag = 1;break;}
            }
        }
        if(end_flag == 1){break;}
        if(invincible == 0){++energy;}
        if(invincible == 1){--energy;}
        if(energy == 349)
        {
            invincible = 1;
            LCD_ShowString(20,9,meme,LIGHTBLUE);
            delay_1ms(250);
            LCD_Fill(20,9,120,22,BLACK);
        }
        if(energy == 0){invincible = 0;}
        if(invincible == 0 && energy % 6 == 1){++chart;LCD_Fill(2,2,chart,5,YELLOW);}
        if(invincible == 1 && energy % 6 == 1){--chart;LCD_Fill(chart,2,60,5,BLACK);}
    }
    char over[] = {"Game Over :("};
    end_game(over);
    free(bat_array);
    free(cac_array);
    return 0;
}