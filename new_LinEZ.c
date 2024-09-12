#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<termios.h>
#include<unistd.h>
#define MAPSIZE 52
#define LEN 30
#define UP 65
#define DOWN 66
#define LEFT 68
#define RIGHT 67
struct rows{
    char row[MAPSIZE];
};
struct map{
    struct rows handle;
    char cols[MAPSIZE];
}map;

struct eqiup{

    int tier; // 장비 등급
    int abil; // 장비 능력치
    int inchant; // 장비 인챈트
    double plus; // 장비 인챈트시 스탯향상률
}eqiup;

struct potion{
    int redpotion;
    int orangepotion;
    int purepotion;
    int highpotion;
}potion;

struct userable{
    int teleport;
    int town_return;
    int enh_sheet; //강화 주문서
    int elixir;
    struct potion p_count;
}userable;

struct sdam
{
    int dam1;
    int dam2;
    int dam3;
    int dam4;
}sdam;

struct adef
{
    int adef1;
    int adef2;
    int adef3;
    int adef4;
}adef;

struct mdef
{
    int mdef1;
    int mdef2;
    int mdef3;
    int mdef4;
}mdef;

struct cdef
{
    int cdef1;
    int cdef2;
    int cdef3;
    int cdef4;
}cdef;

struct sdef
{
    int sdef1;
    int sdef2;
    int sdef3;
    int sdef4;
}sdef;

struct gdef
{
    int gdef1;
    int gdef2;
    int gdef3;
    int gdef4;
}gdef;

typedef struct to
{
    struct sdam sword_stance;
    struct adef ad;
    struct mdef md;
    struct cdef cd;
    struct sdef sd;
    struct gdef gd;
}to;
to total;

struct t1
{
    int sword1;
    int amor1;
    int mask1;
    int shoes1;
    int cape1;
    int glove1;

}t1;

struct t2
{
    int sword2;
    int amor2;
    int mask2;
    int shoes2;
    int cape2;
    int glove2;

}t2;

struct t3
{
    int sword3;
    int amor3;
    int mask3;
    int shoes3;
    int cape3;
    int glove3;

}t3;

struct t4
{
    int sword4;
    int amor4;
    int mask4;
    int shoes4;
    int cape4;
    int glove4;

}t4;

typedef struct inventory{
    struct t1 one;
    struct t2 two;
    struct t3 three;
    struct t4 four; 
    struct userable ur;
}inventory;
inventory inven;


typedef struct boki{
    int fullHP;
    int remainHP;
    int gold;
    int user_dam;
    int user_def;
}boki;
boki bk;


struct win{
    int gold_drop;
    int hp_up;
}win;

struct nomal{
    int dam;
    int HP;
}nomal;

struct named{
    int dam;
    int HP;

}named;

struct boss{
    int dam;
    int HP;
}boss;

struct monster{
    struct nomal n_monster;
    struct named named_monster;
    struct boss b_monster;
}monster;

void win_drop(double a, int b, int c,inventory* d);
void nomal_battle(int x,boki* a);
enum b_name {baphomet = 1, LEE = 2, RYU = 3};
void boss_battle(int x,boki* a);
void named_battle(boki* a);
void equip2_drop(inventory* a);
void equip3_20drop(inventory* a);
void equip3_30drop(inventory* a);
void equip4_5drop(inventory* a);
void equip4_10drop(inventory* a);
void equip4_20drop(inventory* a);
void tel_drop(inventory* a);
void town_drop(inventory* a);
void elixir_10drop(inventory* a);
void elixir_20drop(inventory* a);
void enh(boki*, to*);
void equip(boki*, to*);
void vill_map();
void pandora();
void forge();
void sanctuary();
void printmap(char (*map)[MAPSIZE]);
void vill_move(char (*map)[MAPSIZE],int* x, int* y);
void dungeon_map();
void dungeon_move(char (*map)[MAPSIZE],int* x, int* y,int* floor);
int getch();
void show_inven(inventory* inven);

int main(void)
{
    inventory* inv = &inven;
    bk = (struct boki) {
        .fullHP = 300,
        .remainHP = 100,
        .gold = 300,
        .user_dam = 0
    };
    // int eqnum;
    // scanf(" %d",&eqnum);
    // if (eqnum == 6)
    //     equip(&bk, &total);
    vill_map();
    

    return 0;
}
void win_drop(double a, int b, int c,inventory* d)
{
    bk.fullHP *= a;
    win.gold_drop = rand()%b + c;
    bk.gold += win.gold_drop;

    printf("%d G 획득 했습니다. 현재 소지 골드: %d G\n",win.gold_drop, bk.gold);
    printf("\n전투에서 승리하여 체력량이 증가합니다. : %d\n",bk.fullHP);
}

void nomal_battle(int x, boki* a) // x는 층수
{
    if (monster.n_monster.HP <= 0)
    {   
        printf("\n이겼다!\n");
        switch(x)
        {
            case 1:
                win_drop(1.01, 10, 5, &inven);
                town_drop(&inven);
                break;
            case 2:
                win_drop(1.02, 60, 5, &inven);
                town_drop(&inven);
                break;
            case 3:
                win_drop(1.03, 101, 5, &inven);
                town_drop(&inven);
                break;
            case 4:
                win_drop(1.05, 130, 5, &inven);
                town_drop(&inven);
                equip2_drop(&inven);
                break;
            case 5:
                win_drop(1.07, 201, 5, &inven);
                town_drop(&inven);
                equip2_drop(&inven);
                break;
            default:
                break;
        }
    }
    else
        switch(x)
        {
            case 1:
                monster.n_monster.dam = rand()%15 + 10;
                monster.n_monster.HP -= bk.user_dam;
                printf("복이의 %d의 데미지 \n몬스터의 남은 체력은 %d 입니다.\n", bk.user_dam, monster.n_monster.HP);
                bk.remainHP-=monster.n_monster.dam;
                break;
            case 2:
                monster.n_monster.dam = rand()%30 + 17;
                monster.n_monster.HP -= bk.user_dam;
                printf("복이의 %d의 데미지 \n몬스터의 남은 체력은 %d 입니다.\n", bk.user_dam, monster.n_monster.HP);
                bk.remainHP-=monster.n_monster.dam;
                break;
            case 3:
                monster.n_monster.dam = rand()%45 + 20;
                monster.n_monster.HP -= bk.user_dam;
                printf("복이의 %d의 데미지 \n몬스터의 남은 체력은 %d 입니다.\n", bk.user_dam, monster.n_monster.HP);
                bk.remainHP-=monster.n_monster.dam;
                break;
            case 4:
                monster.n_monster.dam = rand()%55 + 28;
                monster.n_monster.HP -= bk.user_dam;
                printf("복이의 %d의 데미지 \n몬스터의 남은 체력은 %d 입니다.\n", bk.user_dam, monster.n_monster.HP);
                bk.remainHP-=monster.n_monster.dam;
                break;
            case 5:
                monster.n_monster.dam = rand()%75 + 32;
                monster.n_monster.HP -= bk.user_dam;
                printf("복이의 %d의 데미지 \n몬스터의 남은 체력은 %d 입니다.\n", bk.user_dam, monster.n_monster.HP);
                bk.remainHP-=monster.n_monster.dam;
                break;
            default:
                break;
        }         
}

void named_battle(boki* a) 
{
    
    if (monster.named_monster.HP <= 0)
    { 
        printf("\n이겼다!\n");
        win_drop(1.2, 500, 5, &inven);
        town_drop(&inven);
        tel_drop(&inven);
        equip2_drop(&inven);
        equip3_20drop(&inven);
    }
    else
    {          
        monster.named_monster.dam = rand()%300 + 100;
        monster.named_monster.HP -= bk.user_dam;
        printf("복이의 %d의 데미지 \n몬스터의 남은 체력은 %d 입니다.\n", bk.user_dam, monster.named_monster.HP);
        bk.remainHP-=monster.named_monster.dam;
    }
}

void boss_battle(int x, boki* a) // x는 보스 이름
{
    if (monster.b_monster.HP <= 0)
    {  
        printf("\n이겼다!\n");
        switch(x)
        {
            case 1:
                win_drop(1.3, 700, 5, &inven);
                equip3_20drop(&inven);
                equip4_5drop(&inven);
                tel_drop(&inven);
                break;
            case 2:
                win_drop(1.6, 1000, 5, &inven);
                equip3_20drop(&inven);
                equip4_10drop(&inven);
                tel_drop(&inven);
                elixir_10drop(&inven);
                break;
            case 3:
                win_drop(2.0, 3000, 5, &inven);
                equip3_30drop(&inven);
                equip4_20drop(&inven);
                tel_drop(&inven);
                elixir_20drop(&inven);
                break;
            default:
                break;
        }
    
    }
     else
        switch(x)
        {
            case 1:
                monster.b_monster.dam = rand()%450 + 180;
                monster.b_monster.HP -= bk.user_dam;
                printf("복이의 %d의 데미지 \n몬스터의 남은 체력은 %d 입니다.\n", bk.user_dam, monster.b_monster.HP);
                bk.remainHP-=monster.b_monster.dam;
                break;
            case 2:
                monster.b_monster.dam = rand()%550 + 300;
                monster.b_monster.HP -= bk.user_dam;
                printf("복이의 %d의 데미지 \n몬스터의 남은 체력은 %d 입니다.\n", bk.user_dam, monster.b_monster.HP);
                bk.remainHP-=monster.b_monster.dam;
                break;
            case 3:
                monster.b_monster.dam = rand()%1300 + 500;
                monster.b_monster.HP -= bk.user_dam;
                printf("복이의 %d의 데미지 \n몬스터의 남은 체력은 %d 입니다.\n", bk.user_dam, monster.b_monster.HP);
                bk.remainHP-=monster.b_monster.dam;
                break;
            default:
                break;
        }                     
}

void equip2_drop(inventory* inven)
{

    srand(time(NULL));   
    int a = rand()%101 + 1;
    if (a <= 20)
    {
        int b = rand()%6 + 1;
        switch(b)
        {
            case 1: 
                inven->two.sword2 += 1;
                break;
            case 2:
                inven->two.amor2 += 1;
                break;
            case 3:
                inven->two.mask2 += 1;
                break;
            case 4:
                inven->two.shoes2 += 1;
                break;
            case 5:
                inven->two.cape2 += 1;
                break;
            case 6:
                inven->two.glove2 += 1;
                break;
            default:
                break;
        }
    }
    
}

void equip3_20drop(inventory* inven)
{
    srand(time(NULL));   
    int a = rand()%101 + 1;
    if (a <= 20)
    {
        int b = rand()%6 + 1;
        switch(b)
        {
            case 1: 
                inven->three.sword3 += 1;
                break;
            case 2:
                inven->three.amor3 += 1;
                break;
            case 3:
                inven->three.mask3 += 1;
                break;
            case 4:
                inven->three.shoes3 += 1;
                break;
            case 5:
                inven->three.cape3 += 1;
                break;
            case 6:
                inven->three.glove3 += 1;
                break;
            default:
                break;
        }
    }
    
}

void equip3_30drop(inventory* inven)
{
    srand(time(NULL));   
    int a = rand()%101 + 1;
    if (a <= 30)
    {
        int b = rand()%6 + 1;
        switch(b)
        {
            case 1: 
                inven->three.sword3 += 1;
                break;
            case 2:
                inven->three.amor3 += 1;
                break;
            case 3:
                inven->three.mask3 += 1;
                break;
            case 4:
                inven->three.shoes3 += 1;
                break;
            case 5:
                inven->three.cape3 += 1;
                break;
            case 6:
                inven->three.glove3 += 1;
                break;
            default:
                break;
        }
    }
    
}

void equip4_5drop(inventory* inven)
{
    srand(time(NULL));   
    int a = rand()%101 + 1;
    if (a <= 5)
    {
        int b = rand()%6 + 1;
        switch(b)
        {
            case 1: 
                inven->four.sword4 += 1;
                break;
            case 2:
                inven->four.amor4 += 1;
                break;
            case 3:
                inven->four.mask4 += 1;
                break;
            case 4:
                inven->four.shoes4 += 1;
                break;
            case 5:
                inven->four.cape4 += 1;
                break;
            case 6:
                inven->four.glove4 += 1;
                break;
            default:
                break;
        }
    }
    
}

void equip4_10drop(inventory* inven)
{
    srand(time(NULL));   
    int a = rand()%101 + 1;
    if (a <= 10)
    {
        int b = rand()%6 + 1;
        switch(b)
        {
            case 1: 
                inven->four.sword4 += 1;
                break;
            case 2:
                inven->four.amor4 += 1;
                break;
            case 3:
                inven->four.mask4 += 1;
                break;
            case 4:
                inven->four.shoes4 += 1;
                break;
            case 5:
                inven->four.cape4 += 1;
                break;
            case 6:
                inven->four.glove4 += 1;
                break;
            default:
                break;
        }
    }
    
}

void equip4_20drop(inventory* inven)
{
    srand(time(NULL));   
    int a = rand()%101 + 1;
    if (a <= 20)
    {
        int b = rand()%6 + 1;
        switch(b)
        {
            case 1: 
                inven->four.sword4 += 1;
                break;
            case 2:
                inven->four.amor4 += 1;
                break;
            case 3:
                inven->four.mask4 += 1;
                break;
            case 4:
                inven->four.shoes4 += 1;
                break;
            case 5:
                inven->four.cape4 += 1;
                break;
            case 6:
                inven->four.glove4 += 1;
                break;
            default:
                break;
        }
    }
    
}

void tel_drop(inventory* inven)
{
    srand(time(NULL));
    int a = rand()%100 + 1;
    if (a <= 30)
    {
        int b = rand()%3 + 1;
        inven->ur.teleport += b;
        printf("순간이동 주문서를 %d개 획득 하셨습니다.\n", b);
        printf("현재 순간이동 주문서는 %d개입니다.\n", userable.teleport);
    }
    else
        printf("순간이동 주문서를 획득하지 못했습니다.\n");

}

void town_drop(inventory* inven)
{
    srand(time(NULL));
    int a = rand()%100 + 1;
    if (a <= 20)
    {
        int b = rand()%3 + 1;
        inven->ur.town_return += b;
        printf("마을이동 주문서를 %d개 획득 하셨습니다.\n", b);
        printf("현재 마을이동 주문서는 %d개입니다.\n", userable.town_return);
    }
    else
        printf("마을이동 주문서를 획득하지 못했습니다.\n");
}

void elixir_10drop(inventory* inven)
{
     srand(time(NULL));
    int a = rand()%100 + 1;
    if (a <= 10)
    {
        int b = rand()%3 + 1;
        inven->ur.elixir += b;
        printf("엘릭서를 %d개 획득 하셨습니다.\n", b);
        printf("현재 엘릭서는 %d개입니다.\n", userable.elixir);
    }
    else
        printf("엘릭서를 획득하지 못했습니다.\n");
}

void elixir_20drop(inventory* inven)
{
     srand(time(NULL));
    int a = rand()%100 + 1;
    if (a <= 20)
    {
        int b = rand()%3 + 1;
        inven->ur.elixir += b;
        printf("엘릭서를 %d개 획득 하셨습니다.\n", b);
        printf("현재 엘릭서는 %d개입니다.\n", userable.elixir);
    }
    else
        printf("엘릭서를 획득하지 못했습니다.\n");
}

void equip(boki* bk, to* total)
{
    total->sword_stance.dam1 = 2;
    total->sword_stance.dam2 = 5;
    total-> sword_stance.dam3 = 10;
    total->sword_stance.dam4 = 20;

    total->ad.adef1 = 1;
    total->ad.adef2 = 4;
    total->ad.adef3 = 8;
    total->ad.adef4 = 13;

    total->md.mdef1 = 1;
    total->md.mdef2 = 4;
    total->md.mdef3 = 8;
    total->md.mdef4 = 13;

    total->cd.cdef1 = 1;
    total->cd.cdef2 = 4;
    total->cd.cdef3 = 8;
    total->cd.cdef4 = 13;

    total->gd.gdef1 = 1;
    total->gd.gdef2 = 4;
    total->gd.gdef3 = 8;
    total->gd.gdef4 = 13;

    total->sd.sdef1 = 1;
    total->sd.sdef2 = 4;
    total->sd.sdef3 = 8;
    total->sd.sdef4 = 13;
    
    printf("장착할 장비를 선택");
    printf("1.무기 2.갑빠, 3.마스크 4.망토 5,장갑 6.신발");
    int echoice;
    int tchoice;
    scanf("%d",&echoice);
    printf("%d번을 선택하셨습니다.\n 티어를 선택해주세요 \n", echoice);
    printf("1T    2T    3T    4T\n");
    scanf("%d",&tchoice);
    switch(echoice)
    {   
        case 1:
        
            switch(tchoice)
            {
                case 1:
                    bk->user_dam += total->sword_stance.dam1;
                break;
                case 2:
                    bk->user_dam += total->sword_stance.dam2;
                break;
                 case 3:
                    bk->user_dam += total->sword_stance.dam3;
                break;
                 case 4:
                    bk->user_dam += total->sword_stance.dam4;
                break;
            }
        break;
        case 2:
            switch(tchoice)
            {
                case 1:
                    bk->user_def += total->ad.adef1;
                break;
                case 2:
                    bk->user_def += total->ad.adef2;
                break;
                 case 3:
                    bk->user_def += total->ad.adef3;
                break;
                 case 4:
                    bk->user_def += total->ad.adef4;
                break;
            }
        break;
        case 3:
            switch(tchoice)
            {
                case 1:
                    bk->user_def += total->md.mdef1;
                break;
                case 2:
                    bk->user_def += total->md.mdef2;
                break;
                 case 3:
                    bk->user_def += total->md.mdef3;
                break;
                 case 4:
                    bk->user_def += total->md.mdef4;
                break;
            }
        break;
        case 4:
            switch(tchoice)
            {
                case 1:
                    bk->user_def += total->cd.cdef1;
                break;
                case 2:
                    bk->user_def += total->cd.cdef2;
                break;
                 case 3:
                    bk->user_def += total->cd.cdef3;
                break;
                 case 4:
                    bk->user_def += total->cd.cdef4;
                break;
            }
        break;
            case 5:
            switch(tchoice)
            {
                case 1:
                    bk->user_def += total->gd.gdef1;
                break;
                case 2:
                    bk->user_def += total->gd.gdef2;
                break;
                 case 3:
                    bk->user_def += total->gd.gdef3;
                break;
                 case 4:
                    bk->user_def += total->gd.gdef4;
                break;
            }
        break;
            case 6:
            switch(tchoice)
            {
                case 1:
                    bk->user_def += total->sd.sdef1;
                break;
                case 2:
                    bk->user_def += total->sd.sdef2;
                break;
                 case 3:
                    bk->user_def += total->sd.sdef3;
                break;
                 case 4:
                    bk->user_def += total->sd.sdef4;
                break;
            }
        break;
    } 


}
void enh(boki* bk, to* total)
{
    srand(time(NULL));
    int suc = rand()%100 + 1;
    printf("강화할 장비를 선택");
    printf("1.무기 2.갑빠, 3.마스크 4.망토 5,장갑 6.신발");
    int echoice;
    int tchoice;
    scanf("%d",&echoice);
    printf("%d번을 선택하셨습니다.\n 티어를 선택해주세요 \n", echoice);
    printf("1T    2T    3T    4T\n");
    scanf("%d",&tchoice);
    if (suc <= 20)
    {
    switch(echoice)
    {   
        case 1:
        
            switch(tchoice)
            {
                case 1:
                    total->sword_stance.dam1 *= 1.1;
                break;
                case 2:
                    total->sword_stance.dam2 *= 1.1;
                break;
                 case 3:
                    total->sword_stance.dam3 *= 1.1;
                break;
                 case 4:
                    total->sword_stance.dam4 *= 1.1;
                break;
            }
        break;
        case 2:
            switch(tchoice)
            {
                case 1:
                    total->ad.adef1 *= 1.1;
                break;
                case 2:
                    total->ad.adef2*= 1.1;
                break;
                 case 3:
                    total->ad.adef3*= 1.1;
                break;
                 case 4:
                    total->ad.adef4*= 1.1;
                break;
            }
        break;
        case 3:
            switch(tchoice)
            {
                case 1:
                    total->md.mdef1*= 1.1;
                break;
                case 2:
                    total->md.mdef2*= 1.1;
                break;
                 case 3:
                    total->md.mdef3*= 1.1;
                break;
                 case 4:
                    total->md.mdef4*= 1.1;
                break;
            }
        break;
        case 4:
            switch(tchoice)
            {
                case 1:
                    total->cd.cdef1*= 1.1;
                break;
                case 2:
                     total->cd.cdef2*= 1.1;
                break;
                 case 3:
                   total->cd.cdef3*= 1.1;
                break;
                 case 4:
                    total->cd.cdef4*= 1.1;
                break;
            }
        break;
            case 5:
            switch(tchoice)
            {
                case 1:
                   total->gd.gdef1*= 1.1;
                break;
                case 2:
                    total->gd.gdef2*= 1.1;
                break;
                 case 3:
                   total->gd.gdef3*= 1.1;
                break;
                 case 4:
                   total->gd.gdef4*= 1.1;
                break;
            }
        break;
            case 6:
            switch(tchoice)
            {
                case 1:
                    total->sd.sdef1*= 1.1;
                break;
                case 2:
                    total->sd.sdef2*= 1.1;
                break;
                 case 3:
                    total->sd.sdef3*= 1.1;
                break;
                 case 4:
                    total->sd.sdef4*= 1.1;
                break;
            }
        break;
        
        }
    printf("강화에 성공하셨습니다, \n");
    }
    else
        printf("강화 실패");
}   
void vill_map(){
    int x = 1;
    int y = 1;
    char map[MAPSIZE][MAPSIZE];
    for (int i = 0; i < MAPSIZE ; i++)
    {
        for (int j = 0; j < MAPSIZE  ; j++)
        {
            if (i == 0 || j == 51 || i == 51 || j == 0)
                map[i][j] = '#';
            else if ((i > 10 && i < 25) && (j > 5 && j < 15))
                map[i][j] = 'S'; // 상점
            else if ((i > 10 && i < 25) && (j > 20 && j < 30))
                map[i][j] = 'F'; // 대장간
            else if ((i > 10 && i < 25) && (j > 35 && j < 45))
                map[i][j] = 'T'; // 성소
            else if (i == 50 && j == 50)
                map[i][j] = '@'; // 포탈(던전입구)
            else 
                map[i][j] = ' ';
        }
    }
    printmap(map);

    map[x][y] = 'B';

    while(1){
    
    vill_move(map,&x,&y);
    printmap(map);
    }
}
void printmap(char (*map)[MAPSIZE])
{
    for (int i = 0; i < MAPSIZE; i++)
    {
        for (int j = 0; j < MAPSIZE; j++)
        {   
        printf("%3c", map[i][j]);
        }
        printf("\n");  
    }
}
void vill_move(char (*map)[MAPSIZE],int* x, int* y)
{  
    char choice;
     
    printf("방향키로 이동 가능합니다.\n");
    choice = getch();
    system("clear");   
    switch (choice)
    {
        case UP:
                map[*x][*y] = ' ';
                *x -= 1;
                if(*x < 1)
                    *x = 1;
                break;
        case DOWN:
                map[*x][*y] = ' ';
                *x += 1;
                if(*x > MAPSIZE)
                    *x = MAPSIZE;
                break;
        case LEFT:
                map[*x][*y] = ' ';
                *y -= 1;
                if(*y < 1)
                    *y = 1;
                break;
        case RIGHT:
                map[*x][*y] = ' ';
                *y += 1;
                if(*y > MAPSIZE)
                    *y = MAPSIZE;
                break;
        case 105: // i
                equip(&bk, &total);
                break;
        case 106: // j
            show_inven(&inven);
            break;            
                
        // default:
        //         printf("알맞은 키를 눌러주세요.\n");
        //         break;
        }
    map[*x][*y] = 'B';

    if ((*x > 10 && *x < 25) && (*y > 5 && *y < 15)){
        pandora();
        map[*x][*y] = 'S'; // 상점
        *x = 25;
        *y = 10;
    }    
    else if ((*x > 10 && *x < 25) && (*y > 20 && *y < 30)){
        forge();
        map[*x][*y] = 'F'; // 대장간
        *x = 25;
        *y = 25;
    }    
    else if ((*x > 10 && *x < 25) && (*y > 35 && *y < 45)){
        system("clear");
        sanctuary();
        map[*x][*y] = 'T'; // 성소
        *x = 25;
        *y = 40;
        system("clear");

    }    
    else if (*x == 50 && *y == 50){
        dungeon_map();
        system("clear");
        printf("던전에 입장합니다..\n");
    }
}
void pandora(){
            
    int shop_num;
    int shop_buy;
    printf("말하는 섬 -- 판도라상점\n");
    printf("--------------------------------\n");
    printf("어서오세요. 판도라상점입니다.\n");
    printf("1. 구매      2.취소\n");
    scanf(" %d", &shop_num);
    switch(shop_num)
    {
        case 1:
        {
            printf("무엇을 구매 하시겠습니까?\n");
            printf("-------------------------------------------------\n");
            printf("1. 1T기본검 50G      2. 1T기본갑빠 30G\n");
            printf("3. 1T기본장화 30G      4. 1T기본장갑 30G\n");
            printf("5. 1T기본망토 30G      6. 빨간물약 30G\n");
            printf("7. 마을이동주문서 100G\n");
            printf("-------------------------------------------------\n");
            printf("\n현재 소지 골드: %d G\n",bk.gold);
            
            scanf(" %d", &shop_buy);

            if (bk.gold < 30){
                sleep(1);
                printf("소지골드가 충분하지 않습니다.\n");
                printf("현재 소지 골드: %d G\n",bk.gold);
                break;
            }
            if (shop_buy == 1){
                sleep(1);
                printf("기본검을 구입합니다. 금액은 50G\n");
                sleep(1);
                printf("구입 완료. 현재 소지 골드: %d G\n",bk.gold-50);
                bk.gold -= 50;
                sleep(1);
                //기본검 변수 += 1;
                break;
            }
            else if(shop_buy == 2){
                sleep(1);
                printf("기본갑빠를 구입합니다. 금액은 30G\n");
                sleep(1);
                printf("구입 완료. 현재 소지 골드: %d G\n",bk.gold-30);
                bk.gold -= 30;
                //기본갑빠 변수 += 1;
            }
            else if(shop_buy == 3){
                sleep(1);
                printf("기본장화를 구입합니다. 금액은 30G\n");
                sleep(1);
                printf("구입 완료. 현재 소지 골드: %d G\n",bk.gold-30);
                bk.gold -= 30;
                //기본장화 변수 += 1;
            }
            else if(shop_buy == 4){
                sleep(1);
                printf("기본장갑을 구입합니다. 금액은 30G\n");
                sleep(1);
                printf("구입 완료. 현재 소지 골드: %d G\n",bk.gold-30);
                bk.gold -= 30;
                //기본장갑 변수 += 1;
            }
            else if(shop_buy == 5){
                sleep(1);
                printf("기본망토를 구입합니다. 금액은 30G\n");
                sleep(1);
                printf("구입 완료. 현재 소지 골드: %d G\n",bk.gold-30);
                bk.gold -= 30;
                //기본망토 변수 += 1;
            }
            else if(shop_buy == 6){
                sleep(1);
                printf("빨간물약을 구입합니다. 금액은 30G\n");
                sleep(1);
                printf("구입 완료. 현재 소지 골드: %d G\n",bk.gold-30);
                bk.gold -= 30;
                //빨간물약 변수 += 1;
            }
            else if(shop_buy == 7){
                sleep(1);
                printf("마을이동 주문서를 구입합니다. 금액은 100G\n");
                sleep(1);
                printf("구입 완료. 현재 소지 골드: %d G\n",bk.gold-100);
                bk.gold -= 100;
                //twon_return += 1;
            }
        }
            break;
        case 2:
            printf("안녕히 가십시오.\n");
            shop_num = 0;
            break;
    }
}
void forge(){
    int forge_num;
    int forge_cho;
    int enhance_cho;

    printf("말하는 섬 -- 대장간\n");
    printf("--------------------------------\n");
    printf("어서오세요. 대장간입니다.\n");
    printf("1. 강화 주문서(300G) 구매      2.취소\n");

    scanf(" %d", &forge_num);
    switch(forge_num)
    {
        case 1:
        {
            if (bk.gold < 300){
                printf("소지골드가 충분하지 않습니다.\n");
                sleep(1);
                break;
            }
            else {
                printf("강화주문서를 구입합니다. 금액은 300G\n");
                bk.gold -= 300;
                sleep(1);
                printf("구입 완료. 현재 소지 골드: %d G\n",bk.gold);
                sleep(1);
                //강화주문서 변수 += 1;
                break;
            }
            break;
        }
        case 2:
            printf("안녕히 가십시오.\n");
            sleep(1);
            break;
    }
}
void dungeon_map()
{   
    srand(time(NULL));
    int x = 2;
    int y = 2;
    int Mon = 0;
    int floor = 1;
    char map[MAPSIZE][MAPSIZE];
    for (int i = 0; i < MAPSIZE ; i++)
    {
        for (int j = 0; j < MAPSIZE  ; j++)
        {
            Mon = rand()%49;
            if (i == 0 || j == 51 || i == 51 || j == 0)
                map[i][j] = '#';
            else if (i == 50 && j == 50){
                map[i][j] = '@'; // 포탈(던전입구)
            }
            else if (i == 1 && j == 1){
                map[i][j] = '@'; // 포탈(마을입구)
            }
            else if (i == Mon || j == Mon)
                map[i][j] = 'M';
            else 
                map[i][j] = ' ';
        }
    }
    printmap(map);

    map[x][y] = 'B';
    while(1){
    
    dungeon_move(map,&x,&y,&floor);
    printmap(map);
    }
}
void dungeon_move(char (*map)[MAPSIZE],int* x, int* y,int* floor)
{  
    char choice;
    printf("방향키로 이동 가능합니다.\n");
    choice = getch();
    system("clear"); 
    switch (choice)
    {
        case UP:
                map[*x][*y] = ' ';
                *x -= 1;
                if(*x < 1)
                    *x = 1;
                break;
        case DOWN:
                map[*x][*y] = ' ';
                *x += 1;
                if(*x > MAPSIZE)
                    *x = MAPSIZE;
                break;
        case LEFT:
                map[*x][*y] = ' ';
                *y -= 1;
                if(*y < 1)
                    *y = 1;
                break;
        case RIGHT:
                map[*x][*y] = ' ';
                *y += 1;
                if(*y > MAPSIZE)
                    *y = MAPSIZE;
                break;
        }
    map[*x][*y] = 'B';
    if (*floor < 5 && *floor >= 1 ){ 
        if (*x == 50 && *y == 50){
            (*floor)++;
            system("clear");
            printf("윗층으로 올라갑니다...\n");
            sleep(1);
            *x = 2,*y = 2;
        }
    }
    if(*floor == 1 || bk.remainHP <= 0){
        if (*x == 1 && *y == 1){
            system("clear");
            printf("마을로 진입합니다...\n");
            sleep(1);
            vill_map();
            vill_move(map,x,y);
        }
    }    
    else if (*floor > 1){
        if (*x == 1 && *y == 1){
            (*floor)--;
            system("clear");
            printf("아래층으로 내려갑니다...\n");
            sleep(1);
            *x = 2, *y = 2;
        }  
    }
    
    printf("현재위치 : 던전 %d층\n",*floor);

    char monster_name[30],monster_T[30];
    char named_monster[][30] = {"유시온", "김승수", "권철민", "안광민", "강진영",
                    "김영곤", "박선후", "김건", "이준호", "이철", "이동준",
                "황은비", "조세빈", "김성근", "이은승", "박희정", "박장미",
                "김민아", "조대정", "김재신", "박민건", "임석현", "황운하",
                "노주영", "김혜빈", "서훈", "오은지"};

    
    srand(time(NULL));
        if (*floor == 1 && (map[*x][*y] == 'M'))
        {
            printf("오크전사가 출현하였습니다.\n");
            monster.n_monster.dam = rand() % 15 + 10;
            monster.n_monster.HP = rand() % 100 + 50;
            printf("\n 체력: %d\n 공격력: %d\n ", monster.n_monster.HP, monster.n_monster.dam);
            nomal_battle(*floor,&bk);
        }
        else if (*floor == 2 && (map[*x][*y] == 'M')){
            printf("좀비가 출현하였습니다.\n");
            monster.n_monster.dam = rand() % 30 + 17;
            monster.n_monster.HP = rand() % 180 + 50;
            printf("\n 체력: %d\n 공격력: %d\n ", monster.n_monster.HP, monster.n_monster.dam);
            nomal_battle(*floor,&bk);
        }
        else if (*floor == 3 && (map[*x][*y] == 'M')){
            printf("구울이 출현하였습니다.\n");
            monster.n_monster.dam = rand() % 40 + 25;
            monster.n_monster.HP = rand() % 280 + 120;
            printf("\n 체력: %d\n 공격력: %d\n ", monster.n_monster.HP, monster.n_monster.dam);
            nomal_battle(*floor,&bk);
        }
        else if (*floor == 4 && (map[*x][*y] == 'M')){
            printf("해골이 출현하였습니다.\n");
            monster.n_monster.dam = rand() % 55 + 28;
            monster.n_monster.HP = rand() % 260 + 200;
            printf("\n 체력: %d\n 공격력: %d\n ", monster.n_monster.HP, monster.n_monster.dam);
            nomal_battle(*floor,&bk);
        }
        else if (*floor == 5 && (map[*x][*y] == 'M')){
            printf("스파토이가 출현하였습니다.\n");
            monster.n_monster.dam = rand() % 75 + 32;
            monster.n_monster.HP = rand() % 360 + 260;
            printf("\n 체력: %d\n 공격력: %d\n ", monster.n_monster.HP, monster.n_monster.dam);
            nomal_battle(*floor,&bk);
        }

        int boss_rand = rand()%100 + 1;
        if (*floor == 5 && (map[*x][*y] == 'M')){
            if (boss_rand <= 20)
            {
                printf(" 보스 몬스터 바포매트가 출현하였습니다.\n");
                monster.b_monster.dam = rand()%300 + 100;
                monster.b_monster.HP = bk.remainHP*5;
                printf("\n 체력: %d\n 공격력: %d\n ", monster.b_monster.HP, monster.b_monster.dam);
                boss_battle(baphomet,&bk);
            }
            int real_boss_rand = rand()%100 + 1;
            if (real_boss_rand <= 10){
                printf("찐보스 몬스터 이동녘이 출현하였습니다.\n");
                monster.b_monster.dam = rand()%550 + 300;
                monster.b_monster.HP = bk.remainHP*7;
                printf("\n 체력: %d\n 공격력: %d\n ", monster.b_monster.HP, monster.b_monster.dam);
                boss_battle(LEE,&bk);

            }
            int final_real_boss_rand = rand()%100+1;
            if (final_real_boss_rand <= 5){
                printf("찐막보스 몬스터 류홍걸이 출현하였습니다.\n");
                monster.b_monster.dam = rand()%1300 + 500;
                monster.b_monster.HP = bk.remainHP*10;
                printf("\n 체력: %d\n 공격력: %d\n ", monster.b_monster.HP, monster.b_monster.dam);
                boss_battle(RYU,&bk);

            }
        }    
        int class_rand = rand()%100 + 1;
        if (class_rand <= 30){ //출몰 확률 수정 해야함
            class_rand = rand()%28;
            printf("우리반 학생용사 %s(이)가 출현하였습니다.\n",named_monster[class_rand]);
            monster.named_monster.dam = rand()%300 + 100;
            monster.named_monster.HP = bk.remainHP*2;
            printf("\n 체력: %d\n 공격력: %d\n ", monster.named_monster.HP, monster.named_monster.dam);
            named_battle(&bk);
        }
    


        int ichoice =0;
        
        printf("나의 체력 : %d\n",bk.remainHP);
        printf("나의 공격력 : %d\n",bk.user_dam);
        printf("\n1.공격  2.아이템  3.도망\n 원하는 번호를 선택하시오. : ");
        scanf("%d",&ichoice);
            
            switch(ichoice)
            {
                case 1:
                    printf("\n\n용사복이가 몬스터에게 공격을 가합니다.\n");
                    printf("%d의 데미지!\n", bk.user_dam);
                    monster.n_monster.HP -= bk.user_dam;
                    printf("몬스터 남은 체력 : %d\n",monster.n_monster.HP);
                    
                    break;
                case 2:
                        printf("사용할 아이템을 선택해 주세요.\n");
                        printf("1. 빨간물약(%d)   2. 주황물약(%d)   3. 맑은물약(%d)   4. 고농도물약(%d)\n",
                        userable.p_count.redpotion, userable.p_count.orangepotion,
                        userable.p_count.purepotion, userable.p_count.highpotion);
                        scanf("%d", &ichoice);
                
                        if (ichoice == 1){
                            
                            if (userable.p_count.redpotion <= 0){
                                printf("소지한 물약이 없습니다.\n");
                                break;
                            }
                            else{
                                userable.p_count.redpotion -= 1;
                                printf("현재 체력 : %d  \n",bk.remainHP);
                                bk.remainHP += 30;
                            
                                printf("체력이 30 회복되었습니다.\n");
                                if(bk.remainHP > bk.fullHP)
                                {   
                                printf("\n회복체력이 최대 체력 %d를 초과합니다.\n",bk.fullHP);
                                printf("체력이 최대 체력만큼 재조정 됩니다.\n");
                                bk.remainHP = bk.fullHP;
                                }
                                printf("회복 후 체력 : %d  \n",bk.remainHP);
                            
                                break;
                            }
                        }
                        else if (ichoice == 2){
                            
                            if (userable.p_count.orangepotion <= 0){
                                printf("소지한 물약이 없습니다.\n");
                                break;
                            }
                            else{
                                userable.p_count.orangepotion -= 1;
                                    printf("현재 체력 : %d  \n",bk.remainHP);
                                bk.remainHP += 50;
                            
                                printf("체력이 50 회복되었습니다.\n");
                                if(bk.remainHP > bk.fullHP)
                                { 
                                printf("\n회복체력이 최대 체력 %d를 초과합니다.\n",bk.fullHP);
                                printf("체력이 최대 체력만큼 재조정 됩니다.\n");
                                bk.remainHP = bk.fullHP;
                                }
                                printf("회복 후 체력 : %d  \n",bk.remainHP);
                                break;
                            }
                        }
                        else if (ichoice == 3){
                            
                            if (userable.p_count.purepotion <= 0){
                                printf("소지한 물약이 없습니다.\n");
                                break;
                            }
                            else{
                                userable.p_count.purepotion -= 1;
                                    printf("현재 체력 : %d  \n",bk.remainHP);
                                bk.remainHP += 70;
                            
                                printf("체력이 70 회복되었습니다.\n");
                                if(bk.remainHP > bk.fullHP)
                                {   
                                printf("\n회복체력이 최대 체력 %d를 초과합니다.\n",bk.fullHP);
                                printf("체력이 최대 체력만큼 재조정 됩니다.\n");
                                bk.remainHP = bk.fullHP;
                                }
                                printf("회복 후 체력 : %d  \n",bk.remainHP);
                                
                                break;
                            }
                        }
                        else if (ichoice == 4){
                            
                            if (userable.p_count.highpotion <= 0){
                                printf("소지한 물약이 없습니다.\n");
                                break;
                            }
                            else{
                                userable.p_count.highpotion -= 1;
                                    printf("현재 체력 : %d  \n",bk.remainHP);
                                bk.remainHP += 150;
                            
                                printf("체력이 150 회복되었습니다.\n");
                                if(bk.remainHP >bk.fullHP)
                                {  
                                printf("\n회복체력이 최대 체력 %d를 초과합니다.\n",bk.fullHP);
                                printf("체력이 최대 체력만큼 재조정 됩니다.\n");
                                bk.remainHP = bk.fullHP;
                                }
                                printf("회복 후 체력 : %d  \n",bk.remainHP);
                                break;
                            }
                        }
                        else {
                            printf("잘못 입력하여 이전 화면으로 돌아갑니다.\n");
                            break;
                        }
                        
                case 3:
                        int run = rand()%10+1;
                        if (run >= 8)
                        {   
                            printf("\n몬스터에게서 도망쳤습니다.\n");
        
                        }
                        else
                        {   
                            printf("\n도망에 실패했습니다.\n몬스터의 턴으로 전환됩니다.\n");
                        }
                        
                        break;
                        
                // default:
                        
                //         printf("번호를 다시 입력해주세요.\n");
                //         break;  
                }    


   
    /////////////////////////////////////////////////////////////몬스터 턴////////////////////////////////////////////////////////////////////////
            
            printf("\n몬스터가 용사복이를 공격합니다!\n");
            printf("%d의 데미지!\n", monster.n_monster.dam);
            
            bk.remainHP = bk.remainHP - monster.n_monster.dam;
            if(bk.remainHP < 0)
            {   
                printf("\n플레이어가 사망했습니다.\n");
                bk.remainHP = bk.fullHP*0.1;
                printf("마을에서 부활합니다. 체력이 10%% 회복됩니다.\n");
                printf("현재체력: %d\n",bk.remainHP);
            }
            
}
void sanctuary()
{
    printf("말하는 섬 -- 성소\n");
    printf("------------------\n");
    printf("체력이 모두 회복되었습니다...\n");
    sleep(1);
    bk.remainHP = bk.fullHP;
    printf("현재 체력 : %d\n",bk.remainHP);
    sleep(1);
}

void show_inven(inventory* inven)
{
    inven->four.sword4 = 0;
    inven->four.amor4 = 0;
    inven->four.mask4 = 0;
    inven->four.cape4 = 0;
    inven->four.glove4 = 0;
    inven->four.shoes4 = 0;
    inven->three.amor3 = 0;
    inven->three.cape3 = 0;
    inven->three.glove3 = 0;
    inven->three.mask3 = 0;
    inven->three.shoes3 = 0;
    inven->three.sword3 = 0;
    inven->two.amor2 = 0;
    inven->two.cape2 = 0;
    inven->two.glove2 = 0;
    inven->two.mask2 = 0;
    inven->two.shoes2 = 0;
    inven->two.sword2 = 0;
    inven->one.amor1 = 1;
    inven->one.cape1 = 1;
    inven->one.glove1 = 1;
    inven->one.mask1 = 1;
    inven->one.shoes1 = 1;
    inven->one.sword1 = 1;
    printf("t1무기 %d개, ",inven->one.sword1);
    printf("t2무기 %d개, ",inven->two.sword2);
    printf("t3무기 %d개,",inven->three.sword3);
    printf("t4무기 %d개.\n",inven->four.sword4);
    printf("t1갑빠 %d개, ",inven->one.amor1);
    printf("t2갑빠 %d개, ",inven->two.amor2);
    printf("t3갑빠 %d개, ",inven->three.amor3);
    printf("t4갑빠 %d개\n",inven->four.amor4);
    printf("t1마스크 %d개, ",inven->one.mask1);
    printf("t2마스크 %d개, ",inven->two.mask2);
    printf("t3마스크 %d개, ",inven->three.mask3);
    printf("t4마스크 %d개\n",inven->four.mask4);
    printf("t1망토 %d개, ", inven->one.cape1);
    printf("t2망토 %d개, ",inven->two.cape2);
    printf("t3망토 %d개, ",inven->three.cape3);
    printf("t4망토 %d개\n",inven->four.cape4);
    printf("t1장갑 %d개, ",inven->one.glove1);
    printf("t2장갑 %d개, ",inven->two.glove2);
    printf("t3장갑 %d개, ",inven->three.glove3);
    printf("t4장갑 %d개\n",inven->four.glove4);
    printf("t1신발 %d개, ",inven->one.shoes1);
    printf("t2신발 %d개, ",inven->two.shoes2);
    printf("t3신발 %d개, ",inven->three.shoes3);
    printf("t4신발 %d개\n",inven->four.shoes4);
 

}
int getch()
{
    int c;
    struct termios oldattr, newattr;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON|ECHO);
    newattr.c_cc[VMIN] = 1;
    newattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    
    return c;
}