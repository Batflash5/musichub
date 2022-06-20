#include<stdio.h>
#include<iostream>
#include<fstream>
#include<process.h>
#include<string.h>
#include<dos.h>
#include<sstream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
string changestring;
int changeno;
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void spacing()
{
	for(int i=0;i<10;i++)
		cout<<endl;
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<"\t";
}
void instructions_for_adding_songs()
{
	for(int i=0;i<4;i++)
		cout<<endl;
	cout<<"There are 5 essentials for adding a song.";
	cout<<endl<<endl<<endl;
	cout<<"\t"<<"1. The song name"<<endl;
	cout<<"\t"<<"2. The Genre of the song"<<endl;
	cout<<"\t"<<"3. The Artist of the song"<<endl;
	cout<<"\t"<<"4. The Song's Language"<<endl;
	cout<<"\t"<<"5. The song's link(most important)"<<endl;
	cout<<endl<<endl<<endl;
	cout<<"Note:";
	cout<<endl<<endl;
	cout<<"\t"<<"The link/URL of the song must be given correctly!!!!!!";
	cout<<endl<<endl;
	cout<<"\t"<<"This instruction will disappear in   ";
	for(int i=15;i>0;i--)
	{
		if(i<10)
		{
		cout<<"0";
		cout<< i ;
		}
		else
			cout<<i;
			cout<<"\b"<<"\b";
		delay(1000);
	}
}
class song
{
	public:
		string song_name;
		string genre_type;
		string artist_type;
		string language_type;
		string song_link;
		int no_of_votes;
		class song* genre;
		class song* artist;
		class song* language;
		class song* next;		
		void getsongdetails();
		string makejsonformat();
		
};
void song::getsongdetails()
{
			cout<<"\t"<<"Enter the name of the song:";
			getline(cin,this->song_name);
			cout<<endl;
			cout<<"\t"<<"Enter the genre of the song:";
			getline(cin,this->genre_type);
			cout<<endl;
			cout<<"\t"<<"Enter the artist of the song:";
			getline(cin,this->artist_type);
			cout<<endl;
			cout<<"\t"<<"Enter the language of the song:";
			getline(cin,this->language_type);
			cout<<endl;
			cout<<"\t"<<"Enter the song's link:";
			getline(cin,this->song_link);
			cout<<endl;
			this->no_of_votes=0;           	//function to obtain current day
			this->genre=NULL;
			this->artist=NULL;
			this->language=NULL;
}
string song::makejsonformat()
{
	string json;
	string stars_no;
	string vote_no;
	char ch='0';
	int n,x;
	json="{\"Songname\":\"";
	json=json + this->song_name;
	json=json + "\",\"Artist\":\"";
	json=json + this->artist_type;
	json=json + "\",\"Genre\":\""; 
	json=json + this->genre_type;
	json=json + "\",\"Language\":\""; 
	json=json + this->language_type;
	json=json + "\",\"Songlink\":\""; 
	json=json + this->song_link;
	json=json + "\",\"Upvotes\":\""; 
	n=this->no_of_votes;
	while(n!=0)
	{
		ch='0';
		x=n%10;
		ch=ch + x;
		vote_no.push_back(ch);
		n=n/10;
	 } 
	 reverse(vote_no.begin(),vote_no.end());
	 json=json + vote_no;
	 json=json + "\"}";
	 return json; 
}   
typedef class song* songptr;
songptr s;
songptr getnode()
{
	songptr p;
	p= new class song;
	return p;
}
class topic_type_element
{
	public:
		string element_name;
		int element_type;
		songptr first;
		void get_topic_type_element()
		{
			cout<<"Enter the name of the element:";
			getline(cin,this->element_name);
			cout<<"Enter the topic/element type:";
			cout<<endl;
			cout<<"\t"<<"1.By Genre"<<endl;
			cout<<"\t"<<"2.By Artist"<<endl;
			cout<<"\t"<<"3.By Language"<<endl;
		l3:	cout<<"Enter here:";
			cin>>element_type;
			if(!(element_type==1 || element_type==2 || element_type==3))
			{
				cout<<"Invalid input"<<endl;
				cout<<"Enter number 1 or 2 or 3 ....";
				goto l3;
			}
			this->first=NULL;
		}
};

class topics
{
	public:
		vector<topic_type_element> elements; 
		void addsong();
		void addelement();
		int checkgenreexcistence(songptr s1);
		int checkartistexcistence(songptr s1);
		int checklanguageexcistence(songptr s1);
		void createnewgenre(songptr s1);
		void createnewartist(songptr s1);
		void createnewlanguage(songptr s1);
		void mapping_the_topics();
		void showtopics();
		int showsong(string topicname,int elem_type);
		string songabouts(int song_no,string topicname,int elem_type);
		void linking();
		void topicfile();
		~topics()
		{
			int i;
			i=0;
		}
};
topics top;
int topics::checkgenreexcistence(songptr s1)
{
	int g=0;
	for(int i=0;i< elements.size();i++)
	{
		if((elements[i].element_name)==(s1->genre_type))
		{
			g=1;
			break;
		}			
	}
	return g;
}
int topics::checkartistexcistence(songptr s1)
{
	int g=0;
	for(int i=0;i<elements.size();i++)
	{
		if((elements[i].element_name)==(s1->artist_type))
		{
			g=1;
			break;
		}
	}
	return g;
}
int topics::checklanguageexcistence(songptr s1)
{
	int g=0;
	for(int i=0;i<elements.size();i++)
	{
		if((elements[i].element_name)==(s1->language_type))
		{
			g=1;
			break;
		}
		
	}
	return g;
}
void topics::createnewgenre(songptr s1)
{
	fstream f1;
	topic_type_element newgenre;
	newgenre.element_name = s1->genre_type;
	newgenre.element_type=1;
	newgenre.first=NULL;
	elements.push_back(newgenre);
	f1.open("Topics.txt",ios::app);
	f1<<newgenre.element_name;
	f1<<",";
	f1<<"1";
	f1<<"\n";
	f1.close();
}
void topics::createnewartist(songptr s1)
{
	fstream f1;
	topic_type_element newartist;
	newartist.element_name = s1->artist_type;
	newartist.element_type=2;
	newartist.first=NULL;
	elements.push_back(newartist);
	f1.open("Topics.txt",ios::app);
	f1<<newartist.element_name;
	f1<<",";
	f1<<"2";
	f1<<"\n";
	f1.close();
}
void topics::createnewlanguage(songptr s1)
{
	fstream f1;
	topic_type_element newlanguage;
	newlanguage.element_name = s1->genre_type;
	newlanguage.element_type=3;
	newlanguage.first=NULL;
	elements.push_back(newlanguage);
	f1.open("Topics.txt",ios::app);
	f1<<newlanguage.element_name;
	f1<<",";
	f1<<"3";
	f1<<"\n";
	f1.close();
}
void topics::addsong()
{
				fstream f1;
				int ge;
				int ae;
				int le;
				int element_no;
				songptr traverse;
				string jsonaddsong;
				system("CLS");
				instructions_for_adding_songs();
				system("CLS");
				cout<<"Adding a new song.......";
				cout<<endl<<endl<<endl;
				songptr s1;
				s1=getnode();
				s1->getsongdetails();
				ge=checkgenreexcistence(s1);
				ae=checkartistexcistence(s1);
				le=checklanguageexcistence(s1);
				if(ge==0)
				{
					createnewgenre(s1);
					for(int ij=0;ij < elements.size();ij++)
					{
							if((elements[ij].element_name)==(s1->genre_type))
							{
								element_no=ij;
								break;
							}
					}
					elements[element_no].first= s1;
				}
				if(ge==1)
				{
					for(int ik=0;ik<elements.size();ik++)
					{
							if((elements[ik].element_name)==(s1->genre_type))
							{
								element_no=ik;
								break;
							}
					}
					traverse=elements[element_no].first;
					if(traverse==NULL)
					{
						elements[element_no].first=s1;
					}
					else
					{
					
						while((traverse->genre)!=NULL)
						{
							traverse=traverse->genre;
						}
						traverse->genre=s1;
					}
				}
				if(ae==0)
				{
					createnewartist(s1);
						for(int il=0;il<elements.size();il++) 
					{
							if((elements[il].element_name)==(s1->artist_type))
							{
								element_no=il;
								break;
							}
					}
					elements[element_no].first=s1;
				}
				if(ae==1)
				{
						for(int ia=0;ia<elements.size();ia++)
					{
							if((elements[ia].element_name)==(s1->artist_type))
							{
								element_no=ia;
								break;
							}
					}
					traverse=elements[element_no].first;
					if(traverse==NULL)
					{
						elements[element_no].first=s1;
					}
					else
					{
						while((traverse->artist)!=NULL)
						{
							traverse=traverse->artist;
						}
						traverse->artist=s1;
					}
				}
				if(le==0)
				{
					createnewlanguage(s1);
						for(int is=0;is<elements.size();is++)
					{
							if((elements[is].element_name)==(s1->language_type))
							{
								element_no=is;
								break;
							}
					}
					elements[element_no].first=s1;
				}
				if(le==1)
				{
					for(int id=0;id<elements.size();id++)
					{
							if((elements[id].element_name)==(s1->language_type))
							{
								element_no=id;
								break;
							}
					}
					traverse=elements[element_no].first;
					if(traverse==NULL)
					{
						elements[element_no].first=s1;
					}
					else
					{
						while((traverse->language)!=NULL)
						{
							traverse=traverse->language;
						}
						traverse->language=s1;
					}	
				}
				jsonaddsong=s1->makejsonformat();
				f1.open("jsonformat.txt",ios::app);
				f1<<jsonaddsong;
				f1<<"\n";
				f1.close();
}
void topics::addelement()
{
	fstream f1;
	string element;
	int choice;
	system("CLS");
	cout<<"Adding an element to the topic:";
	cout<<endl<<endl;
	cout<<"\t"<<"\t"<<"\t"<<"\t";
	topic_type_element t1;
	t1.get_topic_type_element();
	elements.push_back(t1);
	f1.open("Topics.txt",ios::app);
	f1<<t1.element_name;
	f1<<",";
	if(t1.element_type==1)
		f1<<"1";
	if(t1.element_type==2)
		f1<<"2";
	if(t1.element_type==3)
		f1<<"3";
	f1<<"\n";
	f1.close();			
	system("CLS");
	spacing();
	cout<<"Adding ur new topic  ";
	for(int i=0;i<5;i++)
	{
		delay(1000);
		cout<<".      ";
	}
	system("CLS");
	spacing();
	cout<<"Your topic was successfully added";
	delay(3000);
	system("CLS");
l2:	cout<<"Do you want to add any song in this new topic  ?";
	cout<<endl<<endl;
	cout<<" 1 - For Yes"<<endl;
	cout<<" 2 - For No"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 1:	addsong();
				break;
		case 2:	
				break;
		default: system("CLS");
					spacing();
				cout<<"You have entered an invalid choice";
				cout<<endl;
				cout<<"Either enter 1 or 2"<<endl;
				cout<<"Please try again";
				delay(3000);
				goto l2;
				break;					
	}
}
string topics::songabouts(int song_no,string topicname,int elem_type)
{
	string songreturn;
	int elemen_no;
	songptr trav;
	int trav_no=0;
	song_no=song_no-1;
	for(int i=0;i<elements.size();i++)
	{
		if((elements[i].element_name)==(topicname))
		{
			elemen_no=i;
			break;
		}
	}
	trav=elements[elemen_no].first;
	cout<<trav->genre_type<<endl<<endl;
	while(trav_no!=song_no)
	{
		if(elem_type==1)
			trav=trav->genre;
		if(elem_type==2)
			trav=trav->artist;
		if(elem_type==3)
			trav=trav->language;
		trav_no++;
	}
	system("CLS");
	spacing();
	cout<<"\t"<<"Song name:"<<trav->song_name<<endl;
	cout<<"\t"<<"Artist:"<<trav->artist_type<<endl;
	cout<<"\t"<<"Genre:"<<trav->genre_type<<endl;
	cout<<"\t"<<"Language:"<<trav->language_type<<endl;
//	cout<<"\t"<<"Upvotes:"<<trav->no_of_votes<<endl;
//	
	fstream f;
	songptr p;
	char a;
	string ra;
	p=new song;
	int nov;
	f.open("jsonformat.txt",ios::in | ios::out);
	while(1)
	{
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			p->song_name=ra;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			p->artist_type=ra;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			p->genre_type=ra;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			p->language_type=ra;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			p->song_link=ra;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			stringstream temp(ra);
			temp>>nov;
			p->no_of_votes=nov;
			if(trav->artist_type==p->artist_type)
			{
				changestring=trav->song_name;
				nov=++(p->no_of_votes);
				a=nov-48;
				f.seekg(-3,ios::cur);
				f<<nov;
				changeno=nov;
				break;
			}
	}
	f.close();	
	songreturn=trav->song_link;
	return songreturn;
}
int topics::showsong(string topicname,int elem_type)
{
	l18:int elem_no;
		string songplay;
		int choice_song;
		int listen_choice;
		int f=0;
		int song_no;
		songptr traverse;
		for(int i=0;i<elements.size();i++)
		{
			if((elements[i].element_name)==(topicname))
			{
				f=1;
				elem_no=i;
				break;
			}
			//delay(5000);
		}
		if(f==0)
		{
			system("CLS");
			cout<<"You would have entered an invalid topic or the topic you have entered doesn't exist";
			for(int i=0;i<5;i++)
			{
				cout<<".";
				delay(1000);
			}
		}
		else
		{
			traverse=elements[elem_no].first;
			if(traverse==NULL)
			{
				system("CLS");
				spacing();
				cout<<"Sorry, there are currently no songs in this topic/element";
				delay(3000);
				f=0;
			}
			else
			{
				song_no=1;
				system("CLS");
				cout<<"Displaying songs by ";
				cout<<topicname;
				cout<<"  :";
				cout<<endl<<endl<<endl;
				while(traverse!=NULL)
				{
					cout<<"\t";
					cout<<song_no<<".";
					cout<<(traverse->song_name);
					if(traverse->song_name==changestring)
					cout<<"\t\t"<<changeno;
					else
					cout<<"\t\t"<<(traverse->no_of_votes);
					cout<<endl;
					if(elem_type==1)
						traverse=traverse->genre;
					else if(elem_type==2)
						traverse=traverse->artist;
					else
						traverse=traverse->language;	
					song_no++;
				}
				
				cout<<"Enter song no to view about the song";
				cout<<"If no - Enter 0";
				cout<<endl;
				cout<<"Enter here:";
				cin>>choice_song;
				if(choice_song==0)
					f=0;
				else
				{
					songplay=songabouts(choice_song,topicname,elem_type);
					string url1=songplay;
					char url2[100];
					/*cout<<"Do u want to listen to it ?    ";
					cout<<endl;
					cout<<"If yes,Press 1";
					cout<<endl;
					cout<<"If no,Press 2";
					cout<<endl;
					cout<<"Enter your choice:";
					cin>>listen_choice;
					switch(listen_choice)
					{
						case 1: url1=songplay;
								strcpy(url2,url1.c_str());
								ShellExecute(NULL,"open",url2,NULL,NULL,SW_SHOWNORMAL);//play fuction;
								break;
						case 2:	
								break;
						default:cout<<"You have Entered an invalid choice....";
								cout<<endl<<endl;
								cout<<"Please try again..";
								delay(2500);
								goto l18;
								break;			
					}*/
					cout<<"\n\tThe song will be played in 9 seconds....";
					delay(9000);
					url1=songplay;
					strcpy(url2,url1.c_str());
					ShellExecute(NULL,"open",url2,NULL,NULL,SW_SHOWNORMAL);
					}	
				
			}
		}
		return f;
}	
void topics::showtopics()
{
l5:	int choice;
	int total_no;
	int hk;
	string specific_name;
	system("CLS");
	spacing();
	cout<<"Retriving data";
	for(int i=0;i<5;i++)
	{
		cout<<".";
		delay(1000);
	}
	system("CLS");
	spacing();
	cout<<"\t"<<"How do u want to see your songs ?"<<endl;
	cout<<"\t"<<"1. By Genre"<<endl;
	cout<<"\t"<<"2. By Artist"<<endl;
	cout<<"\t"<<"3. By Language"<<endl;
	cout<<"\t"<<"4. Back to menu"<<endl;
	cout<<"Enter your choice here:";
	cin>>choice;
	switch(choice)
	{
	l4:	case 1: int choicy;
				int decision;
				 hk=0;
				total_no=0;
				system("CLS");
				cout<<endl<<endl;
				cout<<"Displaying all genre topics:";
				for(int i=0;i<5;i++)
				{
						cout<<".";
						delay(1000);
				}
				cout<<endl<<endl<<endl<<endl;
				for(int i=0;i< elements.size();i++)
				{
					if(elements[i].element_type==1)
					{
						cout<<"\t";
						cout<<hk+1<<".";
						cout<<elements[i].element_name;
						cout<<endl;
						total_no=total_no+1;
						hk++;
					}
				}
				cout<<"The number of topics by genre are:"<<total_no;
				cout<<endl<<endl;
				cout<<"Do you want to browse any songs in these specific topics:"<<endl;
				cout<<"If Yes - Press 1"<<endl;
				cout<<"If No  - Press 2"<<endl;
				cout<<"Enter your choice:";
				cin>>choicy;
				switch(choicy)
				{
					case 1:	
							 cout<<"Enter the genre to view the songs about:";
							 cin>>specific_name;
							decision=showsong(specific_name,1);
							if(decision==0)
								goto l5;	
							if(decision==1)
								;	
							break;
					case 2:		;
							break;
					default: system("CLS");
							spacing();
			   				cout<<"You have entered an invalid choice";
							cout<<endl;
							cout<<"Either enter 1 or 2"<<endl;
							cout<<"Please try again";
							delay(3000);
							goto l4;
							break;					
				}
				break;
		case 2: system("CLS");
				 hk=0;
				total_no=0;
				cout<<endl<<endl;
				cout<<"Displaying all artist topics:";
				for(int i=0;i<5;i++)
				{
						cout<<".";
						delay(1000);
				}
				cout<<endl<<endl<<endl<<endl;
				for(int i=0;i< elements.size();i++)
				{
					if(elements[i].element_type==2)
					{
						cout<<"\t";
						cout<<hk+1<<".";
						cout<<elements[i].element_name;
						cout<<endl;
						total_no=total_no+1;
						hk++;
					}
				}
				cout<<"The number of topics by artist are:"<<total_no;
				cout<<endl<<endl;
				cout<<"If Yes - Press 1"<<endl;
				cout<<"If No  - Press 2"<<endl;
				cout<<"Enter your choice:";
				cin>>choicy;
				switch(choicy)
				{
					case 1:	
							 cout<<"Enter the artist to view the songs about:";
							cin>>specific_name;
							decision=showsong(specific_name,2);
							if(decision==0)
								goto l5;	
							if(decision==1)
								//go to the mainest menu;	
							break;
					case 2:		//go to the mainest menu
							break;
					default: system("CLS");
							spacing();
			   				cout<<"You have entered an invalid choice";
							cout<<endl;
							cout<<"Either enter 1 or 2"<<endl;
							cout<<"Please try again";
							delay(3000);
							goto l4;
							break;					
				}
				break;
		case 3:	system("CLS");
				hk=0;
				total_no=0;
				cout<<endl<<endl;
				cout<<"Displaying all language topics:";
				for(int i=0;i<5;i++)
				{
						cout<<".";
						delay(1000);
				}
				cout<<endl<<endl<<endl<<endl;
				for(int i=0;i< elements.size();i++)
				{
					
					if(elements[i].element_type==3)
					{
						cout<<"\t";
						cout<<hk+1<<".";
						cout<<elements[i].element_name;
						cout<<endl;
						total_no=total_no+1;
						hk++;
					}
				}
				cout<<"The number of topics by language are:"<<total_no;
					cout<<endl<<endl;
				cout<<"If Yes - Press 1"<<endl;
				cout<<"If No  - Press 2"<<endl;
				cout<<"Enter your choice:";
				cin>>choicy;
				switch(choicy)
				{
					case 1:	
							 cout<<"Enter the language to view the songs about:";
							cin>>specific_name;
							decision=showsong(specific_name,3);
							if(decision==0)
								goto l5;	
							if(decision==1)
								//go to the mainest menu;	
							break;
					case 2:		//go to the mainest menu;
							break;
					default: system("CLS");
							spacing();
			   				cout<<"You have entered an invalid choice";
							cout<<endl; 
							cout<<"Either enter 1 or 2"<<endl;
							cout<<"Please try again";
							delay(3000);
							goto l4;
							break;					
				}
				break; 
		case 4: ;
				break;
		default:cout<<"\t\t"<<"Invalid input"<<endl;
				cout<<"Please try Again";
				delay(2000);
				goto l5;
				break;									
	}
}
void topics::linking()
	{
		int nov;
		int j=0;
		string ra;
		fstream f;
		f.open("jsonformat.txt",ios::in);
		while(!f.eof())
		{
			songptr p;
			p=new song;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			p->song_name=ra;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			p->artist_type=ra;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			p->genre_type=ra;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			p->language_type=ra;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			p->song_link=ra;
			getline(f,ra,':');
			getline(f,ra,'"');
			getline(f,ra,'"');
			stringstream temp(ra);
			temp>>nov;
			p->no_of_votes=nov;
			p->artist=NULL;
			p->genre=NULL;
			p->next=NULL;
			p->language=NULL;
			songptr f1;
			f1=s;
			if(f1!=NULL)
			{	
				while(f1->next!=NULL)
					f1=f1->next;
				f1->next=p;
			}
			j=0;
			while(j!=elements.size())
			{
				//cout<<j;
				if(p->genre_type==elements[j].element_name)
				{
					//cout<<"fs1";
					if(s==NULL)
					{
						elements[j].first=p;
						s=p;
					}
					else
					{
						if(elements[j].first!=NULL)
						{
							songptr q;
							q=s;
							while(q->next!=NULL)
							{
								if(q->genre_type==p->genre_type)
								{
									while(q->genre!=NULL)
										q=q->genre;
									q->genre=p;
									break;
								}
								else
									q=q->next;
							}
						}
						else
						{
							elements[j].first=p;
						}
					}
				}
				if(p->artist_type==elements[j].element_name)
				{
					//cout<<"fs2";
					if(s==NULL)
					{
						elements[j].first=p;
						s=p;
					}
					else
					{
						if(elements[j].first!=NULL)
						{
							songptr q;
							q=s;
							while(q->next!=NULL)
							{
								if(q->artist_type==p->artist_type)
								{
									while(q->artist!=NULL)
										q=q->artist;
									q->artist=p;
									break;
								}
								else
									q=q->next;
							}
						}	
						else
						{
							elements[j].first=p;
						}
					}
				}
				if(p->language_type==elements[j].element_name)
				{
					//cout<<"fs3";
					if(s==NULL)
					{
						elements[j].first=p;
						s=p;
					}
					else
					{
						if(elements[j].first!=NULL)
						{
							songptr q;
							q=s;
							while(q->next!=NULL)
							{
								if(q->language_type==p->language_type)
								{
									while(q->language!=NULL)
										q=q->language;
									q->language=p;
									break;
								}
								else
									q=q->next;
							}
						}
						else
						{
							elements[j].first=p;
						}
					}
				}
				j++;
			}
		}
		f.close();
	}
//	int n=0;
void topics::topicfile()
	{
		fstream f;
		topic_type_element forp;
		f.open("Topics.txt",ios::in);
		string ra;
		int nov;
		while(!f.eof())
		{
			cout<<"12345";
			getline(f,ra,',');
			forp.element_name=ra;
			getline(f,ra,'\n');
			stringstream t(ra);
			t>>nov;
			forp.element_type=nov;
			forp.first=NULL;
			elements.push_back(forp);
		}
		f.close();
	}
void music_symbol()
{
	for(int i=0;i<8;i++)
	{
		system("CLS");
		cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   ***********************************************"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   ***********************************************"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                   **                                           **"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                  ***                                          ***"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                 ****                                         ****"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"                *****                                        *****"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"               ******                                       ******"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"              *******                                      *******"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"             ********                                     ********"<<endl;
		cout<<"\t"<<"\t"<<"\t"<<"            *********                                    *********"<<endl;
		cout<<endl<<endl;
		cout<<"\t"<<"\t"<<"Create your own kind of music!!!!!!!!!";
		cout<<endl<<endl;
		cout<<"\t"<<"  Hear, add and enjoy,         The one stop for your music love!!!"<<endl<<endl;
			for(int j=0;j<=i;j++)
				cout<<"\t"<<"\t";
			cout<<"      ***********"<<endl;
			for(int j=0;j<=i;j++)
				cout<<"\t"<<"\t";
			cout<<"      *         *"<<endl;
			for(int j=0;j<=i;j++)
				cout<<"\t"<<"\t";
			cout<<"      *         *"<<endl;
			for(int j=0;j<=i;j++)
				cout<<"\t"<<"\t";
			cout<<"     **        **"<<endl;
			for(int j=0;j<=i;j++)
				cout<<"\t"<<"\t";
			cout<<"    ***       ***"<<endl;
			delay(1000);
	}
}
//static int i=0;
//void music_store()
//{
//	
//l16:		int store_choice;
//	cout<<"Welcome to the music store";
//	cout<<endl<<endl<<endl;
//	cout<<"\t\t\t\t"<<"What to wanna a do today?";
//	cout<<endl<<"\t\t\t";
//	cout<<"1.Hear/Display Songs......";
//	cout<<endl<<"\t\t\t";
//	cout<<"2.Add a new song...";
//	cout<<endl<<"\t\t\t";
//	cout<<"3.Add a new genre/artist/language to the hub";
//	cout<<endl<<"\t\t\t";
//	cout<<"4.Go back to Main Menu";
//	cout<<endl<<endl<<"\t\t\t\t"<<"Enter your Choice:";
//	cin>>store_choice;
//	switch(store_choice)
//	{
//		case 1:t1.showtopics();
//				system("CLS");
//				goto l16;
//				break;
//		case 2:	getchar();
//				t1.addsong();
//				t1.~topics();
//				break;
//		case 3:getchar();
//				t1.addelement();
//				t1.~topics();
//				break;
//		case 4: t1.~topics();
//				system("CLS");
//				break;
//		default:cout<<"Invalid option...";
//				cout<<endl;
//				cout<<"Please try Again";
//				delay(2000);
//				system("CLS");
//				goto l16;
//				break;								
//	}
//}
//void mainest_menu()
//{
//
//}


int main()
{
	topics t1;
	int store_choice;	
	music_symbol();
		t1.topicfile();
		t1.linking();
	system("CLS");
	spacing();
		int menu_choice;
l15:	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"*   *      *      *  *   *        *   *  *****  *   *  *   *         "<<endl;
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"** **     * *     *  **  *        ** **  *      **  *  *   *        "<<endl;
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"* * *    *****    *  * * *        * * *  ****   * * *  *   *         "<<endl;
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"*   *   *     *   *  *  **        *   *  *      *  **  *   *      "<<endl;
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"*   *  *       *  *  *   *        *   *  *****  *   *  *****           "<<endl;
	cout<<endl<<endl<<endl;
	cout<<"\t\t\t"<<"So wassup for today???";
	cout<<endl<<endl<<endl;
	cout<<"\t\t\t\t"<<"1. To the music store"<<endl;
	cout<<"\t\t\t\t"<<"2. Exit"<<endl<<endl;
	cout<<"\t\t"<<"Enter your Choice:";
	cin>>menu_choice;
	switch(menu_choice)
	{
		case 1: system("CLS");
				//music_store();
	l16:				cout<<"Welcome to the music store";
	cout<<endl<<endl<<endl;
	cout<<"\t\t\t\t"<<"What to wanna a do today?";
	cout<<endl<<"\t\t\t";
	cout<<"1.Hear/Display Songs......";
	cout<<endl<<"\t\t\t";
	cout<<"2.Add a new song...";
	cout<<endl<<"\t\t\t";
	cout<<"3.Add a new genre/artist/language to the hub";
	cout<<endl<<"\t\t\t";
	cout<<"4.Go back to Main Menu";
	cout<<endl<<endl<<"\t\t\t\t"<<"Enter your Choice:";
	cin>>store_choice;
	switch(store_choice)
	{
		case 1:t1.showtopics();
				system("CLS");
				goto l16;
				break;
		case 2:	getchar();
				t1.addsong();
				break;
		case 3:getchar();
				t1.addelement();
				break;
		case 4: t1.~topics();
				system("CLS");
				break;
		default:cout<<"Invalid option...";
				cout<<endl;
				cout<<"Please try Again";
				delay(2000);
				system("CLS");
				goto l16;
				break;								
	}
				goto l15;
				break;
		case 2:	system("CLS");
				//about();
				break;
		case 3: exit(0);
				break;
		default:cout<<endl<<endl;
				cout<<"You have entered an invalid option";
				cout<<endl;
				cout<<"Please try again";
				delay(2000);
				system("CLS");
				goto l15;
				break;						
	}	
	return 0;
}
