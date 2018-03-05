#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<cstdlib>
using namespace std;

class Player{
	public:
		int usermoney,money,count,win,lose,ran;
	public:
		Player(int i =0){
			usermoney=i;
			money=i;
			count=i;
			win=i;
			lose=i;
			ran=i;
		}// 建構子  ASAFGSRHS
		void show(){
			count=win+lose;
			if(usermoney-200>=0){
				printf("您共玩%d了回合，贏%d回合，輸%d回合，目前餘額%d元，共賺%d元\n",count,win,lose,usermoney,usermoney-200);
			}else if(usermoney<0){
				printf("您共玩%d了回合，贏%d回合，輸%d回合，目前餘額0元，共賠%d元\n",count,win,lose,usermoney*-1);
			}else{
				printf("您共玩%d了回合，贏%d回合，輸%d回合，目前餘額%d元，共賠%d元\n",count,win,lose,usermoney,200-usermoney);				
			}
			
		} // 顯示玩家成績
};

class Gamble{
	public:
		int comcards,comsum,comcount,usercards,usersum,usercount;
	public:
		Gamble(int i=0){
			comcards=i;
			comsum=i;
			comcount=i;
			usercards=i;
			usersum=i;
			usercount=i;
		} 
		void comserve(){
			srand(time(NULL));
			while(comcards<5&&comsum<21&&comsum<18){				
					int com=rand()%13+1;
					if(com>10){
						comsum+=10;
					}else{
						comsum+=com;
					}
					comcards+=1;				
			}
		}// 發牌給電腦
		void playerserve(char willing){
			srand(time(NULL));		
			int play=rand()%13+1;
			if(willing =='y'||willing=='Y'){
				if(play>10){
					usersum+=10;
				}else{
					usersum+=play;
				}
				usercards+=1;
				printf("\n你目前點數為：%d\n",usersum);
				if(usercards<5&&usersum<21){					
					printf("請問是否要增加牌數(y/n)：");
					cin>>willing;
					playerserve(willing);
				}				
			}
																
		} // 發牌給玩家
		Player check(Player player,int ran){
			printf("\n===========Result===========\n");
			printf("電腦共發%d張牌 點數：%d點\n您共發%d張牌 點數：%d點\n",comcards,comsum,usercards,usersum);
			if (usersum>=21){
				printf("您的點數超過21點，你輸了\n");
				comcount+=1;
				printf("您輸了%d元\n",player.money*ran);
			}else if(comsum>=21){
				printf("電腦點數超過21點，您贏了\n");
				usercount+=1;	
				player.usermoney+=player.money*ran;
				printf("您贏了%d元，含本金%d元共%d元\n",player.money*ran,player.money,player.usermoney);				
			}else if (usersum<=comsum){
				printf("您的點數比電腦點數小，你輸了\n");
				comcount+=1;
				printf("您輸了%d元\n",player.money*ran);
			}else if(usersum>comsum){
				printf("電腦點數比你的點數小，您贏了\n");
				usercount+=1;
				player.usermoney+=player.money*ran;
				printf("您贏了%d元，含本金%d元共%d元\n",player.money*ran,player.money,player.usermoney);
			}			
		} // 勝負判定
};

int main(void){
	char con;
	Gamble g;
	Player p;
	p.usermoney=200;
	do{
		g.comcards=0;
		g.comsum=0;
		g.usercards=0;
		g.usersum=0;
		p.ran=0;
		printf("\n===========遊戲開始===========\n");
		for(int i=1;i<=2;i++){
			int play=rand()%13+1;
			if(play>10){
				g.usersum+=10;
			}else{
				g.usersum+=play;
			}
				g.usercards+=1;
		}
		g.comserve();
		printf("目前餘額為：%d元\n",p.usermoney);
		srand(time(NULL));
		p.ran = rand()%6+1;
		printf("此回合遊戲賠率為%d倍\n",p.ran);
		printf("請輸入下注金額：");
		cin>>p.money;
		while(p.money>p.usermoney){
			printf("請重新輸入下注金額：");
			cin>>p.money;
		}		
		printf("\n你目前點數為：%d\n",g.usersum);
		printf("請問是否要增加牌數(y/n)：");
		cin>>con;
		g.playerserve(con);
		p.lose=g.comcount;
		p.win=g.usercount;
		g.check(p,p.ran);
		if(p.lose<g.comcount){
			p.lose=g.comcount;
			p.usermoney-=p.money*p.ran;
		}else{
			p.win=g.usercount;	
			p.usermoney+=p.money*p.ran;
		}
		
		if(p.usermoney>0){
			printf("請選擇是否繼續遊戲(y/n)：");
			cin>>con;
		}else{
			printf("您沒錢了，請離開\n");
			break;
		}				
	}while(con=='Y'||con=='y');
	p.show();
	system("pause");
	return 0;
}
