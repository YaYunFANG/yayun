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
		}// �غc�l  ASAFGSRHS
		void show(){
			count=win+lose;
			if(usermoney-200>=0){
				printf("�z�@��%d�F�^�X�AĹ%d�^�X�A��%d�^�X�A�ثe�l�B%d���A�@��%d��\n",count,win,lose,usermoney,usermoney-200);
			}else if(usermoney<0){
				printf("�z�@��%d�F�^�X�AĹ%d�^�X�A��%d�^�X�A�ثe�l�B0���A�@��%d��\n",count,win,lose,usermoney*-1);
			}else{
				printf("�z�@��%d�F�^�X�AĹ%d�^�X�A��%d�^�X�A�ثe�l�B%d���A�@��%d��\n",count,win,lose,usermoney,200-usermoney);				
			}
			
		} // ��ܪ��a���Z
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
		}// �o�P���q��
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
				printf("\n�A�ثe�I�Ƭ��G%d\n",usersum);
				if(usercards<5&&usersum<21){					
					printf("�аݬO�_�n�W�[�P��(y/n)�G");
					cin>>willing;
					playerserve(willing);
				}				
			}
																
		} // �o�P�����a
		Player check(Player player,int ran){
			printf("\n===========Result===========\n");
			printf("�q���@�o%d�i�P �I�ơG%d�I\n�z�@�o%d�i�P �I�ơG%d�I\n",comcards,comsum,usercards,usersum);
			if (usersum>=21){
				printf("�z���I�ƶW�L21�I�A�A��F\n");
				comcount+=1;
				printf("�z��F%d��\n",player.money*ran);
			}else if(comsum>=21){
				printf("�q���I�ƶW�L21�I�A�zĹ�F\n");
				usercount+=1;	
				player.usermoney+=player.money*ran;
				printf("�zĹ�F%d���A�t����%d���@%d��\n",player.money*ran,player.money,player.usermoney);				
			}else if (usersum<=comsum){
				printf("�z���I�Ƥ�q���I�Ƥp�A�A��F\n");
				comcount+=1;
				printf("�z��F%d��\n",player.money*ran);
			}else if(usersum>comsum){
				printf("�q���I�Ƥ�A���I�Ƥp�A�zĹ�F\n");
				usercount+=1;
				player.usermoney+=player.money*ran;
				printf("�zĹ�F%d���A�t����%d���@%d��\n",player.money*ran,player.money,player.usermoney);
			}			
		} // �ӭt�P�w
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
		printf("\n===========�C���}�l===========\n");
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
		printf("�ثe�l�B���G%d��\n",p.usermoney);
		srand(time(NULL));
		p.ran = rand()%6+1;
		printf("���^�X�C���߲v��%d��\n",p.ran);
		printf("�п�J�U�`���B�G");
		cin>>p.money;
		while(p.money>p.usermoney){
			printf("�Э��s��J�U�`���B�G");
			cin>>p.money;
		}		
		printf("\n�A�ثe�I�Ƭ��G%d\n",g.usersum);
		printf("�аݬO�_�n�W�[�P��(y/n)�G");
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
			printf("�п�ܬO�_�~��C��(y/n)�G");
			cin>>con;
		}else{
			printf("�z�S���F�A�����}\n");
			break;
		}				
	}while(con=='Y'||con=='y');
	p.show();
	system("pause");
	return 0;
}
