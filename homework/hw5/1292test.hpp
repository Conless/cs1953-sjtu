#include<bits/stdc++.h>
using namespace std;
class Calendar{
	private:
		int sum;
	public:
		static const int sumonth[2][13];
		inline int is_good(const int&x)const{return (x%4==0&&x%100)||(x%400==0);}
		inline int cntyear(const int&x)const{return x*365+x/4-x/100+x/400;}
		inline int cntmonth(const int&fl,const int&x)const{return sumonth[fl][x];}
		Calendar(){sum=0;}
		Calendar(const int&x){sum=x;}
		Calendar(const int&year,const int&month,const int&day){
			sum=cntyear(year-1)+cntmonth(is_good(year),month-1)+day;
		}
		Calendar(const string&s){
			int year=(s[0]-'0')*1000+(s[1]-'0')*100+(s[2]-'0')*10+(s[3]-'0');
			int month=(s[5]-'0')*10+(s[6]-'0');
			int day=(s[8]-'0')*10+(s[9]-'0');
			*this=Calendar(year,month,day);
		}
		friend bool operator ==(const Calendar&A,const Calendar&B){return A.sum==B.sum;}
		friend bool operator !=(const Calendar&A,const Calendar&B){return A.sum!=B.sum;}
		friend bool operator >=(const Calendar&A,const Calendar&B){return A.sum>=B.sum;}
		friend bool operator <=(const Calendar&A,const Calendar&B){return A.sum<=B.sum;}
		friend bool operator >(const Calendar&A,const Calendar&B){return A.sum>B.sum;}
		friend bool operator <(const Calendar&A,const Calendar&B){return A.sum<B.sum;}
		friend Calendar operator +(const Calendar&A,const int&B){return Calendar(A.sum+B);}
		friend Calendar operator -(const Calendar&A,const int&B){return Calendar(A.sum-B);}
		friend Calendar &operator +=(Calendar&A,const int&B){return A=A+B;}
		Calendar &operator -=(const int&B){return *this=*this-B;}
		Calendar &operator ++(){return *this+=1;}
		Calendar &operator --(){return *this-=1;}
		Calendar operator ++(int){
			Calendar tmp=*this;
			*this=*this+1;
			return tmp;
		}
		Calendar operator --(int){
			Calendar tmp=*this;
			*this=*this-1;
			return tmp;
		}
		friend int operator -(const Calendar&A,const Calendar&B){return A.sum-B.sum;}
		operator string()const{
			char A[11];
			int year=0,tmp1=0,month=1;
			for(int i=15;~i;i--) if(cntyear(year|(1<<i))<sum) year|=(1<<i);tmp1=cntyear(year);year++;
			for(int tmp2=sum-tmp1;month<13&&sumonth[is_good(year)][month]<tmp2;month++);//month--;
			sprintf(A,"%04d-%02d-%02d",year,month,sum-tmp1-sumonth[is_good(year)][month-1]);
			return (string)A;
		}
		friend istream &operator >>(istream&A,Calendar&B){
			string s;
			A>>s;
			B=Calendar(s);
			return A;
		}
		friend ostream &operator <<(ostream&A,const Calendar&B){
			A<<string(B);
			return A;
		}
		int getday()const{return sum%7;}
};
const int Calendar::sumonth[2][13]={{0,31,59,90,120,151,181,212,243,273,304,334,365},{0,31,60,91,121,152,182,213,244,274,305,335,366}};

const Calendar operator "" _C(const char*col,size_t n){return Calendar(string(col));}