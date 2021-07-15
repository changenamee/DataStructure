#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
#define MAXCAR 5
#define PRICE 10	//一小时10块
//停车时间
struct Time{
	int hour;
	int min;
};
//汽车
struct Car{
	string num;	//车牌号
	Time reach;
	Time leave;
};
//停车场结构
struct CarStack{
	Car *data[MAXCAR];
	int top;
};
//便道链队列
struct Road{
	Car *data;
	Road *next;
};
struct RoadLink{
	Road *front,*rear;
};
//初始化栈
int initStack(CarStack *s){
	s->top = -1;
	return 0;
}
//初始化队列
int initQueue(RoadLink *q){
	q->front = q->rear = (Road*)malloc(sizeof(Road));
	if(!q->front) return -1;
	q->front->next = NULL;
	return 0;
}

//车入栈
void Push(Car *c,CarStack *s){
	s->top++;
	cout<<"汽车停在"<<s->top+1<<"处"<<endl;
	cout<<"输入停车时间：(小时:分钟)"<<endl;
	scanf("%d:%d",&c->reach.hour,&c->reach.min);
	while((c->reach.hour<0||c->reach.hour>24)||(c->reach.min<0||c->reach.min>60)){
		cout<<"输入时间错误，重新输入：";
		scanf("%d:%d",&c->reach.hour,&c->reach.min);
	}
	s->data[s->top] = c;
	cout<<"停车成功"<<endl;
}
//汽车出停车场时临时存放其之后的汽车
void PushStack(Car *c,CarStack *s){
	s->top++;
	s->data[s->top] = c;
}
//再放入停车场
void PopStack(Car *(&c),CarStack *s){
	c = s->data[s->top];
	s->top--;
}
//停车位不够 放入便道
void PushQueue(RoadLink *q,Car *c){
	cout<<"停车位不足，汽车停入便道"<<endl;
	Road *t;
	t = (Road*)malloc(sizeof(Road));
	if(!t) return;
	t->data = c;
	t->next = NULL;
	q->rear->next = t;
	q->rear = t;
	cout<<"停车成功"<<endl;
}
//从便道处移出车辆
void PopQueue(Car *(&c),RoadLink *q){
	Road *t;
	t = (Road*)malloc(sizeof(Road));
	t = q->front->next;
	c = t->data;
	q->front->next = t->next;	//删除停进停车场车的队列中的数据
	if(q->rear == t){	//队列变空
		q->rear = q->front;
	}
	free(t);
}
//停入停车场
void InPark(RoadLink *r ,CarStack *s){
	Car *c = (Car*)malloc(sizeof(Car));
	cout<<"s->top:"<<s->top<<endl;
	cout<<"输入车牌号："<<endl;
	cin>>c->num;
	
	if(s->top+1 < MAXCAR){	//停在停车场
		Push(c,s);
	}else{	//停车场满，放入便道
		PushQueue(r,c);
	}
}
//计算停车价格
double GetPrice(Car *p){
	double price=0;
	cout<<"汽车离开的时间："<<endl;
	scanf("%d:%d",&p->leave.hour,&p->leave.min);
	while((p->leave.hour<0||p->leave.hour>24)||(p->leave.min<0||p->leave.min>60)){
		cout<<"输入时间错误，重新输入：";
		scanf("%d:%d",&p->leave.hour,&p->leave.min);
	}
	if((p->leave.hour>=p->reach.hour)&&(p->leave.min>=p->reach.min)){
		price = (p->leave.hour - p->reach.hour)*PRICE+(p->leave.min-p->reach.min)/60*10;
	}else if((p->leave.hour>=p->reach.hour)&&(p->leave.min<p->reach.min)){
		//6:08 5:12
		price = (p->leave.hour - p->reach.hour - 1)*PRICE+(60+p->leave.min-p->reach.min)/60*10;
	}else if((p->leave.hour<p->reach.hour)&&(p->leave.min>=p->reach.min)){
		price = (p->leave.hour + 24 - p->reach.hour)*PRICE+(p->leave.min-p->reach.min)/60*10;
	}else
		price = (p->leave.hour + 24 - p->reach.hour - 1)*PRICE+(60 + p->leave.min-p->reach.min)/60*10;
	return price;
}
//出停车场
void OutPark(RoadLink *r,CarStack *s,CarStack *t){
	int location;
	double price;
	Car *p,*q;
	if(s->top>=0){	//栈非空
		cout<<" 输入车的位置："<<endl;
		scanf("%d",&location);
		while(location<1||location>s->top+1){	//取车位置错误
			cout<<"此处没有车，重新输入:"<<endl;
			scanf("%d",&location);
		}
		while(s->top > location-1){	//将取车位置之后的车放入临时栈中
			PopStack(p,s);
			PushStack(p,t);
		}
		printf("t->top:%d\n",t->top);
		PopStack(p,s);
		//计算价格
		price = GetPrice(p);
		cout<<"出车成功,价钱："<<price<<endl;
		while(t->top >= 0){	//把临时栈中的数据再放入原栈中
			PopStack(p,t);
			PushStack(p,s);
		}
		if((r->front!=r->rear) && s->top<MAXCAR){	//链队列（便道）中有数据，且停车场中有位置，将便道中的第一辆车放入停车场
			PopQueue(q,r);
			PushStack(q,s);
			cout<<"便道第一辆车进入停车场"<<endl;
		}else{
			cout<<"便道没有车，无需进入停车场"<<endl;
		}
		cout<<"top:"<<s->top<<endl;
	}else{
		cout<<"停车场为空"<<endl;
	}
}
//显示停车场信息
void ShowPark(CarStack *c){
	int i;
	if(c->top>=0){	//不能对s->top进行减法，会改变栈中数据，用i代替s->top计数....
		for(i=0;i<=c->top;i++){
			cout<<"位置："<<i+1<<endl;
			cout<<"车牌号:"<<c->data[i]->num<<endl;
			cout<<"停车时间："<<c->data[i]->reach.hour<<":"<<c->data[i]->reach.min<<endl;
		}
	}else{
		cout<<"停车场为空"<<endl;
	}
}
//显示便道信息
void ShowRoad(RoadLink *r){
	Road *t;
	t = r->front->next;
	int i=0;
	if(r->front == r->rear){	//队列队头队尾相等，对空
		cout<<"便道为空\n\n\n"<<endl;
		return;
	}
	while(t!=NULL){
		i++;
		cout<<"位置："<<i<<endl;
		cout<<"车牌号:"<<t->data->num<<endl;
		t = t->next;
	}
}
//菜单选项
void Menu(){
	cout<<"输入功能："<<endl;
	cout<<"1--> 停车"<<endl;
	cout<<"2--> 出车"<<endl;
	cout<<"3--> 显示停车场信息"<<endl;
	cout<<"4--> 显示便道信息"<<endl;
	cout<<"0--> 退出"<<endl;
}

int main(void){
	char fun;
	CarStack c,t;
	RoadLink r;
	initStack(&c);
	initStack(&t);
	initQueue(&r);
	while(1){
		Menu();
		cin>>fun;
		getchar();
		switch(fun){
			case '1':
				InPark(&r,&c);
				break;
			case '2':
				OutPark(&r,&c,&t);
				break;
			case '3':
				ShowPark(&c);
				break;
			case '4':
				ShowRoad(&r);
				break;
			case '0':
				return 0;
			default:
				cout<<"输入指令错误..\n"<<endl;
				break;
		}
	}
}