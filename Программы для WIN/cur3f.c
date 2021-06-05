
#include <stdio.h>
/*Подключение стандартной билотеки ввода/вывола*/
#include <stdlib.h>
/*Подключение сандартной математической билиотеки для вызова математических ф-ций*/
#include <math.h>
/*Поключение библотеки определения времени, она необходима для генертора случайных чисел, и расчета зтраченного времени*/
#include <time.h>

#define Mx 5
/*Определние фнкции в кторой будет проводится расчет*/
float Calc(float Arr[Mx],float buf[Mx],float itog,int Rn);

int main()
{/*создание файла для сохранения счет*/
  FILE *save;
  /*Определение пременных money-деньги, pointnum-зелья, key-набор клавиш, serial счетчик серии, ExSy-переменная для сохранения выборанной мат. операции при повышении сложности*/
  int money=30,poitnum=0,key,okr=0,Leng=1,ExSy,Rn,serial=0;
  /*Arr[Mx]массив сохранения знаков и чисел, buf[mx]- массив ждля записи скобок, itog-в нее сохраняется итог вычислений, expr[Mx]в этот массив сохраняется массив Arr для вывода*/
  float Arr[Mx]={},buf[Mx]={},itog,expr[Mx],itog1,itog2;
  /*Сохранение ответа пользавателя*/
  float answer;
  /*перменные для отсчета времени*/
  time_t start,end;
  int df;
  /*Очищаем экран*/
  system("cls");
  while(1)
    {/*Выводим меню*/
      system("cls");
      printf("---------------------------------------\n");
      printf("You have %d $ and %d potions \n",money,poitnum);
      printf("---------------------------------------\n");
      printf("1 - Launch \n");
      printf("2 - Lenght \n");
      printf("3 - Save/Load score \n");
      printf("4 - Shop \n");
      printf("0 - Exit \n");
      printf("---------------------------------------\n");
      scanf("%d",&key);
      if(key==0)break;
      switch(key)
	{

	case(1):
	  {/*Если выбрана кнопка расчета выводим правила*/
	    system("cls");
	    printf("You need to answer 3 questions correct \n");
	    printf("Enter the answer with 2 numbers after point (Example Answer = 2.56) \n");
	    printf("You  heave a 1 min to answer for every expression \n");
	    printf("With correct answer you can get 10 $ \n");
	    printf("With wrong answer you loose 10 $ \n");
	    printf(" To cntinue press - 1  Exit - 0\n");
	    scanf("%d",&key);
	    /*Если нажато подтверждение (1) исполняем ф-цию*/
	    while(key==1 & serial<3)
	      {/*Очищаем экран*/
		system("cls");
		/*Генерируем случайную последовательность*/
		srand(time(NULL));
		/*Начало отсчета времени*/
		time(&start);
		/*Если сложность больше 1 заключает 1 выражение в скобки*/
		if(Leng>1)printf("(");
		/*Использование ф-ции вычисления, она же и выводит первый модуль выражнения*/
		itog=Calc(Arr,buf,itog,Rn);
		/*Если сложность больше 1*/
		if(Leng>1){
		  /*Закрытие скобок превого выражения*/
		  printf(")");
		  /*Присваиваем ExSy случайное число(0 или 1)*/
		  ExSy=rand()%2;
		  /*Если сгенерировался 0 операция +*/
		  if(ExSy==0)printf(" + ");
		  /*Если сегенрировался 1 опреация - */
		  if(ExSy==1)printf(" - ");
		  /*Rn увеличивается что бы изменить резульат следующего вызова calc, это необходимо для того что-бы результат calc не получился тем же самым*/
		  Rn+=rand();
		  /*Закрываем скобки*/
		  printf("(");
		  /*Вызываем calc*/
		  itog1=Calc(Arr,buf,itog,Rn);
		  /*Cкладываем или вычитаем резултаты в зависимости от ExSy*/
		  if(ExSy==0)itog=itog+itog1;
		  if(ExSy==1)itog=itog-itog1;
		  /*Закрываем скобку*/
		  printf(")");
		  if(Leng>2){
		    /*Если сложность больше двух вышеописанные действия повторяются*/
		    ExSy=rand()%2;
		    if(ExSy==0)printf(" + ");
		    if(ExSy==1)printf(" - ");
		    printf("(");
		    Rn+=rand();
		    itog2=Calc(Arr,buf,itog,Rn);
		    if(ExSy==0)itog=itog+itog2;
		    if(ExSy==1)itog=itog-itog2;
		    printf(")");
		  }
		}
		printf("\n");\
		/*Округление результата, для корректного ввод пользвоателя*/
		if(itog!=0){
		itog*=100;
		if(itog<0)itog-=0.5;
		else itog+=0.5;
		okr=itog;
		itog=okr/100.0;
		}
		/*Считвыания ответа*/
		scanf("%f",&answer);
		/*Конец отсчета веремни*/
		time(&end);
		/*Рассчет разницы во времнеи*/
		df=difftime(end,start);
		/*Если разница больше 1 минуты вывод сообщение о неудае и снятие баллов*/
	       	if(df>=60){
		  printf("Sorry time is out you loose 10$ \n");
		  money-=10;}
		/*Если кол-во зелий больше 0 и введно кодове число покзывает ответ*/
		else if(answer==15551 & poitnum>0){printf("Potion tell that answer is %f \n",itog);poitnum--;}
		/*Если ответ правильный +10 очков*/
		else if(itog==answer){
		  printf("You answer is correct you get 10$ \n");
		  money+=10;
		  printf("Now you have %d $ \n\n",money);
		  /*Увелечение серии*/
		  serial++;
		}
		/*Если ответ не сходится сообщение о неудаче и снятие очков*/
		else if(itog!=answer){
		  printf("you answer is wrong correct answer is %.2f \n",itog);
		  printf("You lose 10$ \n\n");
		  money-=10;
		}
		/*Если денег меньше 0 выход из цикла*/
		if(money<0)break;
		/*Есл серия меньши 3 спрашивает пользавателя желает ли он продолжить*/
		if(serial<3){	  
		printf("Do you want continue? 1-Yes 0-No\n");
		scanf("%d",&key);
		}
		/*Если серия выполнена добавление бонуса, и выход в меню*/
		if(serial==3 || serial>3){
		  printf("You finish the serial, you have bonus 10$ \n");
		  printf("-------------Press 0 to Return in menu----------- \n");
		  money+=10;
		  scanf("%d",&key);
		  serial=0;	  
		}
	      }
	    break;
	  }
	case(2):
	  {
	    while(key==2)
	      {
		/*вывод меню*/
		system("cls");
		printf("Change lenght(level) of expression \n");
		printf("1-standart, 2- medium, 3- extendet \n");
		printf("------------- 0-Exit ------------- \n");
		/*Изменение длинны(сложности)*/
		scanf("%d",&Leng);
		if((Leng!=1) & (Leng!=2) & (Leng!=3)){
		  printf("Error chose only 1/2/3 \n");
		  Leng=1;
		}
		/*Хочет ли пользователь перевыбрать сложность*/
		printf("You choose %d lenght \n",Leng);
		printf("Rechoose lenght?\n 2-yes 0-back \n");
		scanf("%d",&key);

	      }
	    break;
	  }
	case(3):
	  {
	    while(key==3)
	      {/*Вывод меню*/
		system("cls");
		printf("Save youre score(money and potions)-1   Load score-2    Exit-0  \n");
		scanf("%d",&key);
		/*при нажатии 1 сохраняет счет в save.txt*/
		if(key==1){
		if((save=fopen("save.txt","w"))==NULL)printf("Error File cant be opent for write \n");
		else{
		  fprintf(save,"%d %d",money,poitnum);
		  fclose(save);
		  printf("\n You saved %d $ & %d poitions \n",money,poitnum);
		  }
		}
		/*При нажатии 2 загружает счет из save.txt*/
		if(key==2)
		  {
		   if((save=fopen("save.txt","r"))==NULL)printf("Error File cant be opent for write \n");
		else{
		  fscanf(save,"%d %d",&money,&poitnum);
		  fclose(save);
		  printf("you load %d $ & %d poitions \n",money,poitnum);
		  }
		  }
		if(key==0)break;
		scanf("%d",&key);

	      }
	  }
	case(4):
	  {
	    while(key==4)
	      {/*Вывод меню*/
		system("cls");
		printf("Here you can buy potion of answers \n");
		printf("You have %d $ and %d potions \n",money,poitnum);
		printf("1-buy potion of answers (30$)   0-Exit\n");
		scanf("%d",&key);
		/*Покупа зелья, если денег недостаточно покупка несостояится*/
		if(key==1){
		  if(money>=30){printf("your'e buy a 1 potion of answers to use them in expr print: 15551 \n");money-=30;poitnum+=1;}
		  else{printf("You dont have enough money");}
		}
		if(key==0)break;
	  	scanf("%d",&key);
	      }
	  }
	}
      if(money<0){printf("------------------game over------------------ \n");break;}
    }



  return 0;
}







/*Релизация ф-ции расчета на вход поступает массив для чиесл(Arr), массив для скобок(buf),iotg,rn-Перменная для изменения случаного генератора при измеении сложности*/
float Calc(float Arr[Mx],float buff[Mx], float itog,int Rn)
{
  /*shc-счетчик, ogr-ограничение прохождения массива,step-шаг*/
  int sch=0,ogr=0,step;
  /*Буферные переменные для хранения положения скобок*/
  float p1=0,p2=0;
  /*Генератор случйных чисел*/
  srand(time(NULL)+Rn);
  /*Заполнение каждого 2 с 0 элемента массива числами*/
  for(int i=0;i<Mx;i+=2)
    {
      Arr[i]=rand()%9+1;
    }
  /*Заполнение каждого второго с 1 эелмента массива служебными кодами*/
  for(int i=1;i<Mx;i+=2)
    {
      Arr[i]=rand()%5+1000;
      if(Arr[i]==1000 || Arr[i]==1001)Arr[i]--;
      /*Расщифровка служебных кодов*/
      /*999: - ,1000: + ,1002: * ,1003:/ ,1004: ^ */
    }
  /*Цикл расстановки скобок с1 и с2 перменные для ограничения ошибочной расстановки*/
  for(int i=0,c1=0,c2=0; i<Mx;i+=2)
    { /*Если генератор ставит 1, и огр с1=0 и массив не находится перед концом массив ствит открытую скобку(1)*/
       if((rand()%2==1) & c1==0 & i!=Mx-2 & sch==0) 
	 {
	   buff[i]=1;
	   c1=1;
	   p1=i;
	   sch++;
	 }
       /*Если генератор ставит 2, и огр. с1=1 и огр. c2=0 ставит закрывающую  скобку(2)*/
       if((rand()%2==1)&(c1==1)&(c2==0)&(i+2<=Mx))
	 {
	   buff[i+2]=2;
	   c2=1;
	   p2=i+2;
	   sch++;
	 }
       /*Если скобка 1 поставлена а 2 все еще нетЮ ставит скобку 2 перед концо массива*/
       if(i+2==Mx & c2==0){buff[i+1]=2;sch+=1;p2=i+1;}
     }
  /*Цикл ищет и препроверяет расстановку скобок*/
   for(int i=0;i<Mx;i++)
     {
       if(buff[i]==1)p1=i;
       if(buff[i]==2)p2=i;
     }
   /*Данный чикл оприруя массивом Arr выводит выражения в понятном для пользователя виде*/
for(int i=0; i<Mx;i++)
		  {
		    if(buff[i]==1 & sch==2 & ogr<1)printf("("),ogr++;
		    if(Arr[i]<999)printf("%.f",Arr[i]);
		    if(Arr[i]==1004){if(buff[i-1]>0 & Arr[i]<999)printf("^2) +");else printf("^2 + ");}
		    if(Arr[i]==1003)printf(" / ");
		    if(Arr[i]==1002)printf(" * ");
		    if(Arr[i]==1000)printf(" + ");
		    if(Arr[i]==999)printf(" - ");
		    if(buff[i]==2 & sch==2 & ogr<2){printf(")");step=0;ogr++;}
		  }
   /*-------------------------------------------------------------------*/
/*Если кол-во скобок 2*/
   if(sch==2)
     {/*Начало двоного цикла т.к. приротиетов операйи 3 цикл выполняется 3 раза*/
     for(int j=0,zn=2;j<3;j++)
       {/*Выполняется от одной скобки до ругой, т.е сначал выщитывается выражение в скобках*/
     for(int i=p1;i<p2;i++)
       {/*Операции вычисления, результат записывается в соседнии ячеейки от выполненого кода дейтсвия*/
	 if(2==zn & Arr[i]==1004){Arr[i-1]=pow(Arr[i-1],2);Arr[i]=1000;itog=Arr[i+1];}
    if(1==zn & (Arr[i]==1003 || Arr[i]==1002))
	 {
	 if(Arr[i]==1003){Arr[i-1]=Arr[i+1]=Arr[i-1]/Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 if(Arr[i]==1002){Arr[i-1]=Arr[i+1]=Arr[i-1]*Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 }
	 if(0==zn & (Arr[i]==1000 || Arr[i]==999))
	 {
	 if(Arr[i]==1000){Arr[i-1]=Arr[i+1]=Arr[i-1]+Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 if(Arr[i]==999){Arr[i-1]=Arr[i+1]=Arr[i-1]-Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 }
       }/*Уменьшение приоретита*/
     zn--;
       }
     /*-------------------------------------------------------------------*/
     /*Начало двоного цикла т.к. приротиетов операйи 3 цикл выполняется 3 раза*/
     for(int j=0,zn=2;j<3;j++)
       {
	 /*Выполняется рассчет выражения вне скобок*/
     for(int i=0;i<Mx;i++)
       {/*Операции вычисления, результат записывается в соседнии ячеейки от выполненого кода дейтсвия*/
	 if(i==p1){i=p2+1;}
	 if(2==zn & Arr[i]==1004){Arr[i-1]=pow(Arr[i-1],2);Arr[i]=1000;itog=Arr[i+1];}
	 if(1==zn & (Arr[i]==1003 || Arr[i]==1002))
	 {
	 if(Arr[i]==1003){Arr[i-1]=Arr[i+1]=Arr[i-1]/Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 if(Arr[i]==1002){Arr[i-1]=Arr[i+1]=Arr[i-1]*Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 }
	 if(0==zn & (Arr[i]==1000 || Arr[i]==999))
	 {
	 if(Arr[i]==1000){Arr[i-1]=Arr[i+1]=Arr[i-1]+Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 if(Arr[i]==999){Arr[i-1]=Arr[i+1]=Arr[i-1]-Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 }
       }/*Уменьшение приоретита*/
     zn--;
       }
   }
     /*-------------------------------------------------------------------------------*/
     else{
       /*Если скобок нет вовсе, просто вычисляет выражение согласно приоритетам*/
/*Начало двоного цикла т.к. приротиетов операйи 3 цикл выполняется 3 раза*/
for(int j=0,zn=2;j<3;j++)
       {
     for(int i=0;i<Mx;i++)
       {
    if(2==zn & Arr[i]==1004){Arr[i-1]=pow(Arr[i-1],2);Arr[i]=1000;itog=Arr[i+1];}
    if(1==zn & (Arr[i]==1003 || Arr[i]==1002))
	 {
	 if(Arr[i]==1003){Arr[i-1]=Arr[i+1]=Arr[i-1]/Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 if(Arr[i]==1002){Arr[i-1]=Arr[i+1]=Arr[i-1]*Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 }
	 if(0==zn & (Arr[i]==1000 || Arr[i]==999))
	 {
	 if(Arr[i]==1000){Arr[i-1]=Arr[i+1]=Arr[i-1]+Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 if(Arr[i]==999){Arr[i-1]=Arr[i+1]=Arr[i-1]-Arr[i+1];Arr[i]=0;itog=Arr[i+1];}
	 }
       }/*Уменьшение приоретита*/
     zn--;
       }
 }

   return(itog);

}

