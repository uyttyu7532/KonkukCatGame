//gage�� ��� �ǽð����� ���� ��Ű�� ����
//****************������ �� �߰��ϰ� �ʹ�************


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#define INTERVAL_LEVEL  20

pthread_mutex_t mutex_lock;
static int level = 1;
static int cleangage = 50;
static int foodgage = 50;
static int sleepgage = 50;
static int joygage = 50;
static int menunum;


void time_level(int signo)
{
        level = level + 1;

        printf("\n\n*************************************\n");
        printf("**************����%d*****************\n", level);
        printf("*************************************\n");
        sleep(1);
        alarm(INTERVAL_LEVEL);
}


void* t_function(void* data)
{
        static struct sigaction act;
        act.sa_handler = time_level;
        sigfillset(&act.sa_mask);
        if (sigaction(SIGALRM, &act, 0) == -1)

 {
                perror("sigaction");
                exit(0);
        }
        alarm(INTERVAL_LEVEL);
}



// ������ ���� ����
void* rand_minus(void* data)
{
        int rand_num;

        while (1)
        {
                srand((unsigned)time(NULL));
                rand_num = rand() % 4 + 1;

                pthread_mutex_lock(&mutex_lock);

                switch (rand_num)
                {
                case 1:
                        foodgage = foodgage - 5;
                        break;
                case 2:
                        sleepgage = sleepgage - 5;
                        break;
                case 3:
                        joygage = joygage - 5;
                        break;
                case 4:
                        cleangage = cleangage - 5;
                        break;
                }
                if (foodgage <= 0 | sleepgage <= 0 | joygage <= 0 | cleangage <= 0) break;


                pthread_mutex_unlock(&mutex_lock);

                sleep(10 - level);
        }  // while�� ��

        exit(0);
}

void menu(void) {
        while (1) { // level�� 10�� �Ǹ� ����
                menunum = 6;
                if (level >= 10) exit(0);
                if (menunum != 5) {
                        showgage();
                }
                scanf("%d", &menunum);
                switch (menunum) {
                case 0:
                        select_food();
                        menunum = 5;
                        break;

                case 1:
                        select_sleep();
                        menunum = 5;
                        break;

                case 2:
                        select_minigame();
                        menunum = 5;
                        break;

                case 3:
                        select_clean();
                        menunum = 5;
                        break;

                case 4:
                        exit(0);
                }
        }
}

// ���� ������ �ְ� �׿� ���� ������ ����
void select_food(void)
{
        int num;
        if (foodgage > 90) {
                showgage();
                printf("�ǳ� is already full ^-^* \n");    // �ִ������ 100 ��>�� ���� ����
                sleep(2);
                return;
        }

        while (1) {

                showgage();

                printf("**** Select the food's number ****\n ex)1 \n\n1. ���� Ȳ
��    2. ����    3. �����\n\n");
                scanf("%d", &num);

                if (num == 1) {
                        foodgage = foodgage + 5;
                        break;
                }
                if (num == 2) {
                        foodgage = foodgage + 8;
                        break;
                }
                if (num == 3) {
                        foodgage = foodgage + 10;
                        break;
                }
        }

        printf("food_gage: %d\n", foodgage);
        if (50 <= foodgage && foodgage < 70)
                showcat_food(50);

        else if (70 <= foodgage && foodgage <= 100)
                showcat_food(70);

}


void showcat_food(int n)
        {

        showgage();

            FILE *fp;
            int c;

            if (n == 50)
            fp = fopen("food50.txt", "r");

            else
            fp = fopen("food70.txt", "r");

            while((c = fgetc(fp)) != EOF)
        {
            putchar(c);
        }

        fclose(fp);

        sleep(2);
        }



void select_sleep(void) {

        showgage();

        if (sleepgage > 90){
                printf("�ǳ� is already deep sleep\n\n");
                sleep(2);
        }//�ִ� ������ 100�Ѵ� �� ����
        else {
                sleepgage = sleepgage + 10;
                showcat_sleep();
        }
        return;
}

void showcat_sleep(void) {

        showgage();

        FILE* fp;
        int c;

        fp = fopen("sleep.txt", "r");

        while ((c = fgetc(fp)) != EOF) {
                putchar(c);
        }
        fclose(fp);

        sleep(1);
        return;
}



void select_clean(void) {

        showgage();

        if (cleangage > 90){
                printf("�ǳ� is already clean\n\n"); //�ִ� ������ 100�Ѵ� �� ��
��
                sleep(2);}
        else { //clean�̹��� ��� & ������ 10����
                cleangage = cleangage + 10;
                printf("clean: %d\n", cleangage);
                showcat_clean();
        }
        return;
}

void showcat_clean(void) { //����� ����� �̹��� ���

        showgage();

        FILE* fp;
        int c;

        fp = fopen("clean.txt", "r");

        while ((c = fgetc(fp)) != EOF) {
                putchar(c);
        }

        fclose(fp);

        sleep(1);
        return;
}

void gameover_atexit(void) { //��������Ǹ� ���� ���� ����ϸ� ����

        showgage();

        printf("\n*****************game finish***************\n");
        printf("*******************���� %d******************\n", level);
        printf("*******************************************\n");
}

void savecatimage(void) { //����� �̹��� ����
        FILE* fp1 = fopen("food50.txt", "wt");
        fputs("\n     ��:.    ��  ,, ��\n       *. (= ' �� ' =)  *:.\n           {          }/  .��:.\n Meow~ \n(mean: Thank u!)\n", fp1);
        fclose(fp1);

        FILE* fp2 = fopen("food70.txt", "wt");
        fputs("      *��.\n    ��:.    ��  ,, ��  ��:.\n     *.  (= > �� < =)  .:*\n          {          }/  ��:.\n Meow~ Meow~\n(mean: Thank u so much! Now I'm full)\n", fp2);
        fclose(fp2);
        FILE* fp3 = fopen("sleep.txt", "wt");
        fputs(" ��,,�� Good night\n(-��-)Z Z Z Z Z\n/��|\n�գ�  ��\n��", fp3);
        fclose(fp3);

        FILE* fp4 = fopen("clean.txt", "wt");
        fputs(" ��,,�� clean~\n(o��<)\n/����----:��:��\n�գա����� ..��\n���������� .��:.\n���������������� .:��:��\n������������  ����:�٣�\n", fp4);
        fclose(fp4);

        FILE* fp10 = fopen("minigame1.txt", "wt");
        fputs("\n[ M I N I G A M E ! ]\n\n       ^ ,,^\n Mya! (='��'=)  oO{?}\n       ��   ��\n(mean: Guess the number I think!(1~100))\n\n", fp10);
        fclose(fp10);

        FILE* fp20 = fopen("same.txt", "wt");
        fputs("\n[ C O R R E C T ! ]\n\n       ^ ,,^\n Mya~ (=^��^=)  <{��}\n       ��   ��\n\n", fp20);
        fclose(fp20);

        FILE* fp30 = fopen("greaterthan.txt", "wt");
        fputs("\n        ^ ,, ^\n Meow (=������=)  <{��}\n       ��    ��\n(mean: greater than that number)\n\n", fp30);

  fclose(fp30);

        FILE* fp40 = fopen("lessthan.txt", "wt");
        fputs("\n        ^ ,, ^\n Meow (=������=)  <{��}\n       ��    ��\n(mean: less than that number)\n\n", fp40);
        fclose(fp40);

        FILE* fp50 = fopen("best.txt", "wt");
        fputs("\n[ Joyful + 10 ]\n\n  ^ ,,^\n (=>��<=) Myamya!\n  ��   ��\n(mean: It was so fun!)\n\n", fp50);
        fclose(fp50);

        FILE* fp60 = fopen("good.txt", "wt");
        fputs("\n[ Joyful + 7 ]\n\n  ^ ,,^\n (='��'=) Mya\n  ��   ��\n(mean: It was fun)\n\n", fp60);
        fclose(fp60);

        FILE* fp70 = fopen("soso.txt", "wt");
        fputs("\n[ Joyful + 3 ]\n\n  ^ ,, ^\n (='��'=) Hmm..\n  ��    ��\n(mean: I'm still boring..)\n\n", fp70);
        fclose(fp70);

        FILE* fp80 = fopen("draw.txt", "wt");
        fputs("\n  [Joyful +3]\n      /\\_/\\\n      ( ._. ) {ONE MORE TIME!!}\n     (mean: It was boring)\n\n", fp80);
        fclose(fp80);

        FILE* fp90 = fopen("win.txt", "wt");
        fputs("\n  [Joyful +7]\n          /\\_/\\\n         (= >_< )// \n  (mean: I W~I~N~ It's funny)\n\n", fp90);
        fclose(fp90);

        FILE* fp100 = fopen("lose.txt", "wt");
        fputs("\n  [joyful +1]\n    (=^-w-^=)../\n    u___u\n  (meam: I L O S E.. I am so sad)\n\n", fp100);
        fclose(fp100);

}

void showcat_minigame(int n) //�̹��� ���

{
        showgage();
        FILE* fp;
        int c;
        switch (n)
        {
        case 10:
                fp = fopen("minigame1.txt", "r");
                break;
        case 20:
                fp = fopen("same.txt", "r");
                break;
        case 30:
                fp = fopen("greaterthan.txt", "r");
                break;
        case 40:
                fp = fopen("lessthan.txt", "r");
                break;
        case 50:
                fp = fopen("best.txt", "r");
                break;
        case 60:
                fp = fopen("good.txt", "r");
                break;
        case 70:
                fp = fopen("soso.txt", "r");
                break;
        case 80:
                fp = fopen("draw.txt", "r");
                break;
        case 90:
                fp = fopen("win.txt", "r");
                break;
        case 100:
                fp = fopen("lose.txt", "r");
                break;

        }


        while ((c = fgetc(fp)) != EOF) {
                putchar(c);
        }
        fclose(fp);

}



void play_minigame1(void) //���� ���� ���߱� ����
{
        int rand_num = 0;
        int count = 0;
        int guess = 0;
        char q = NULL;
        char buf[200];

        srand((unsigned)time(0));

        rand_num = rand() % 100;
        showcat_minigame(10);
        sleep(1);

        while (1) {
                printf("���ڸ� �Է��ϼ���\t");
                scanf("%d", &guess);

                if (1 <= guess && guess <= 100)
                {
                        if (guess == rand_num)
                        {
                                showcat_minigame(20);
                                sleep(2);
                                break;
                        }

                        else if (guess < rand_num){
                                showcat_minigame(30);
                                printf("���� �Է��� ����:%d\n\n ",guess);
                        }
                        else if (guess > rand_num){
                                showcat_minigame(40);
 printf("���� �Է��� ����:%d\n\n ",guess);
                        }
                        count++;
                }

                else
                {
                        showgage();
                        printf("\n* only 1~100 number *\n");
                        break;
                }
        }

        if (count <= 5)
        {
                showcat_minigame(50);
                joygage += 10;
        }
        else if (5 < count && count <= 15)
        {
                showcat_minigame(60);
                joygage += 7;
        }
        else if (count > 15)
        {
                showcat_minigame(70);
                joygage += 3;
        }
        sleep(2);
        buf[0] = '\0';
}

void play_minigame2(void) //���������� ����
{
        int a;
        int t;
        char q = NULL;
        char buf[200];

        srand(time(NULL)); //time(NULL):1�� ������ �ð� ����
        a = rand() % 3 + 1; //1~3���� �����ϰ� ���� �߻�

        do
        {
                showgage();
                printf("\n���������������� �����մϴ� \n1.���� 2.���� 3.�� 0.��>�ӳ�����\n");
                scanf("%d", &t);

                if (t == 0)
                {
                        printf("\n���ӳ�����\n");
                        return 0;
                }

                else if (t < 0 || t>3)
                {
                        printf("\n�߸��� �Է��߽��ϴ�.\n");
                        return 0;
                }
                else if (t == a)
                {
                        printf("\n�����ϴ�\n");
                        showcat_minigame(80);
                        joygage += 3;
                        sleep(1);
                }

                else if ((t == 1 && a == 3) || (t == 2 && a == 1) || (t == 3 && a == 2))
                {
                        printf("\n�̰���ϴ�\n");
                        showcat_minigame(90);
                        joygage += 7;
                        sleep(1);
                }

                else if ((t == 1 && a == 2) || (t == 2 && a == 3) || (t == 3 && a == 1))
                {
                        printf("\n�����ϴ�\n");
                        showcat_minigame(100);
                        joygage += 1;
                        sleep(1);
                }

                buf[0] = '\0';
                showgage();
                printf("\n������ ����Ͻðڽ��ϱ�?(y/n)\n"); //����ڰ� ���� ��>�࿩�θ� ������ �� �ִ�.

                scanf("%s", &q);
        } while (q == 'y');
}
void select_minigame(void)
{
        int mg;

        if (joygage > 90) printf("�ǳ� is already fun\n\n"); //�ִ� ������ 100��
�� �� ����

        else {
                while (1) {
                        showgage();
                        printf("\n������ ������ �ּ���!\n1. ���� ���� ���߱�   2. ����������   0. ���� ȭ������ ���ư���\n");
                        scanf("%d", &mg);

                        if (mg == 1) {
                                play_minigame1();
                                break;
                        }

                        else if (mg == 2) {
                                play_minigame2();
                                break;
                        }

                        else if (mg == 0) {
                                return;
                                break;
                        }
                }
        }
}

void showgage(void){
        system("clear");
        printf("���� ����: %d\n",level);
        printf("\n\n\n ��θ�\t%d\n ��\t%d\n ��ſ�\t%d\n �����\t%d\n", foodgage, sleepgage, joygage, cleangage);
        printf("0: eat/ 1: sleep/ 2: play/ 3:clean/ 4:exit\n");
}

int main(void) {

        pthread_t p_thread1, p_thread2;
        int thr_id1, thr_id2;
        int status;
        int a = 1;

        pthread_mutex_init(&mutex_lock, NULL);

        pthread_create(&p_thread1, NULL, t_function, (void*)& a);
        pthread_create(&p_thread2, NULL, rand_minus, (void*)& a);

        if (thr_id1 < 0 | thr_id2 < 0)
        {
                perror("thread create error!");
                exit(0);
        }
        savecatimage();
        atexit(gameover_atexit);

        printf("~!~!�ǳ��� Ű���~!~!\n�ǳ����� �������� �ϳ��� 0�� �Ǹ� �ǳ�>�� Ű��� ����!\nlevel 10�� �Ǹ� �ǳ��� Ű��� ����!\n�������� �������� �ǳ��̸�
 ������ Ű���ּ���(=o��o=)");
        printf("\n  |������������������������������|\n��|!!!!������  ���۵Ǿ���>�ϴ�!!!!|            ��  \n��|�ߣߣߣߣߣߣߣߣߣߣߣߣߣߣ�|\n������ ����  ||\n��
�� ( ��?��)||\n������/���ĥ�\n");
        printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");

        menu();
        exit(0);
}
                          








