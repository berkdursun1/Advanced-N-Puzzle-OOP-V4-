#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<vector>
#define empty 0
using namespace std;
class NPUZZLE {
	public :
	inline void print_goal()  { table[0].print_goal();}
	inline void setLine(int x){ BoardObj.setLine(x);}
	inline void setcoloun(int x){ BoardObj.setcoloun(x);}
	inline void print() { table[0].print(); }
	inline void printReport(){	BoardObj.printReport();}
	inline void writeToFile(string name){	BoardObj.writeToFile(name);}
	inline void initial_goal(){	table[0].initial_goal();}
	inline int get_count(){ return table[0].get_count();}
	inline int isSolved() const {	return table[0].isSolved();}
	inline int move_up(){ table[0].move_up();};
	inline int move_left(){ table[0].move_left();};
	inline int move_down(){ table[0].move_down();};
	inline int move_right(){ table[0].move_right();};
	inline void set_lastmove(int i,char son_hareket){table[i].set_lastmove(son_hareket);};
	inline char get_lastmove(int i){return table[i].get_lastmove();}
	inline int get_size(){ return table[0].getsize();}
	int move_clever();
	void reset(int size);
	void setSize();
	void move(char selection);
	void solvePuzzle();
	void shuffle(){
		int number_of_move;
		table[0].shuffle(number_of_move);
	}
	void readFromFile(string name)
	{
		BoardObj.readFromFile(name);
		table.push_back(BoardObj);
		temp=table[0];
	}
	 private :
		 class Board {
		 	public:
				 // Defining the public functions ...
				 inline  int get_count(){return count;}
				 inline  void set_count(int value){count=value;}
				 inline  int getsize(){return line;}
				 inline  char get_lastmove(){return last_move;}
				 inline  void set_lastmove(char last){last_move=last;}
				 inline	 void setLine(int x){ line=x;}
				 inline	 void setcoloun(int x){ coloun=x;}
				 inline void printReport(){		 cout << "Move number -> " << count << "\n" ;}
				 void readFromFile(string name);
				 void writeToFile(string name);
				 void reset(int size);
				 void setSize();
				 void moveRandom();
				 void shuffle(int number_of_move);
				 void print_goal();
				 void initial_goal();
				 void print() const;
				 int move_up();
				 int move_left();
				 int move_down();
				 int move_right();
				 int isSolved() const;
				 int find_blank_coordinat_x_new(vector<vector<int>> arr);
				 int find_blank_coordinat_y_new(vector<vector<int>> arr);
			 	 int copy_ptr(vector<vector<int>> &ptr2,vector<vector<int>> &copy);
				 int operator()(int satir,int sutun){
					 if(satir>line || sutun>coloun){
						 cout << "Wrong\n" ;
						 return 0;
					 }
					 else{
						 return ptr[satir][sutun];
					 }
				 }
				 inline bool operator ==(Board otherBoard){ return (ptr==otherBoard.ptr);}
			 private :
			 		vector<vector<int> > goal_ptr;
			 		vector<vector<int>> ptr;
					char last_move;
					int line=3;
					int coloun=3;
					int count = 0 ;
		 }BoardObj;
		 vector < Board > table;
		 Board temp;
	 public:
		 friend ostream & operator <<(ostream & os,NPUZZLE a){
	 		a.print();
	 	}
		friend istream & operator >>(istream &input,NPUZZLE &b){
			string name;
			cout << "please : ";
			input>> name;
			b.readFromFile(name);
		}
};
int main(int argc, char* argv[]){
	NPUZZLE puzzle ;
	int size;
	int i=0;
	char selection;
	string name;
	srand(time(NULL));
	if(argc==1){
		cout << "please enter size : ";
		cin >> size;
		puzzle.reset(size);
		puzzle.shuffle();
		cout << puzzle ;
		do{
			cout << "Please enter any selection : " ;
			cin >> selection ;
			if(selection=='u' || selection=='U' ||
				 selection=='l' || selection=='L' ||
			   selection=='d' || selection=='D' ||
			   selection=='r' || selection=='R')
			{
				puzzle.move(selection);
				cout << puzzle ;
			}
			else if(selection=='s' || selection=='S'){
				puzzle.shuffle();
				cout << "SHUFFLE BOARD : \n";
				cout << puzzle;
			}
			else if(selection=='v' || selection=='V'){
					puzzle.move_clever();
					puzzle.reset(size);

			}
		}while( selection!='q' && selection!='Q' &&  puzzle.isSolved()==0);
	}
	else{
		puzzle.readFromFile(argv[1]);
		puzzle.initial_goal();
		cout<<puzzle;

		do{
			cout << "Please select your move : " ;
			cin >> selection ;
			if(selection=='v' || selection=='V'){
				puzzle.move_clever();
			}
			else if(selection=='t' || selection=='T'){
				cout << "Soloution is founded by " << puzzle.get_count() << "moves\n";
			}
			else if(selection=='e' || selection=='E'){
				cout << "Please enter file name : " ;
				cin >>name;
				puzzle.writeToFile(name);
			}
			else if(selection=='s' || selection=='S'){
				puzzle.shuffle();
				cout << "SHUFFLE BOARD \n";
				cout << puzzle;
			}
			else if(selection=='o' || selection=='O'){
				cin >> puzzle ;
				cout << puzzle;
			}
			else if(selection=='u' || selection=='U'
			|| selection=='l' || selection=='L'
			|| selection=='d' || selection=='D'
			|| selection=='r' || selection=='R'){
				puzzle.move(selection);
				puzzle.print();
			}
	}while(  selection!='q' && selection!='Q' );
		cout << puzzle ;
		cout << "\n";
	}
}
void NPUZZLE::move(char selection){
	if(selection=='u' || selection=='U'){
		table[0].move_up();
	}
	else if(selection=='l' || selection=='L'){
		table[0].move_left();
	}
	else if(selection=='d' || selection=='D'){
		table[0].move_down();
	}
	else if(selection=='r' || selection=='R'){
		table[0].move_right();
	}
}

int NPUZZLE::move_clever(){
	int index=0;
	int step=0;
	int issolved=0;
	int start=0;
	int issame=-1;
	table[0].set_lastmove(-1);
	while(!issolved){
			if(table[step].get_lastmove()!='D'){ // moveup // controling lastmove
				if(table[step].move_up()!=99 && issolved==0){ // controling is move_up legal
					for(start=0;start<step;start++){
						if(table[step]==table[start]){ // controling is there the same board previus
							issame=1;
						}
					}
					if(issame==-1){
							table.push_back(table[step]); // adding new board to the vector
							index++;
							table[index].set_lastmove('U');

					}
					issame=-1;
					if(table[step].isSolved()==1){ // controling the solved
						temp=table[step];
						issolved=1;
					}
					table[step].move_down(); // return the privious mod
				}
			}
			if(table[step].get_lastmove()!='R' && issolved==0){ // control the last move ... same things
				if(table[step].move_left()!=99){
					for(start=0;start<step;start++){
						if(table[step]==table[start]){
							issame=1;
						}
					}
					if(issame==-1){
							table.push_back(table[step]);
							index++;
							table[index].set_lastmove('L');
					}
					issame=-1;

					if(table[step].isSolved()==1){
						temp=table[step];
						issolved=1;
					}
					table[step].move_right(); // eski haline döndürme
				}
			}
			if(table[step].get_lastmove()!='U' && issolved==0){
				if(table[step].move_down()!=99){
					for(start=0;start<step;start++){
						if(table[step]==table[start]){
							issame=1;
						}
					}
					if(issame==-1){
							table.push_back(table[step]);
							index++;
							table[index].set_lastmove('D');
					}
					issame=-1;

					if(table[step].isSolved()==1){
						temp=table[step];
						issolved=1;
					}
					table[step].move_up(); // eski haline döndürme
				}
			}
			if(table[step].get_lastmove()!='L' && issolved==0){
				if(table[step].move_right()!=99){
					for(start=0;start<step;start++){
						if(table[step]==table[start]){
							issame=1;
						}
					}
					if(issame==-1){
							table.push_back(table[step]);
							index++;
							table[index].set_lastmove('R');
					}
					issame=-1;

					if(table[step].isSolved()==1){
						temp=table[step];
						issolved=1;
					}
					table[step].move_left(); // eski haline döndürme
				}
			}
			step++;
			table[step].set_count(step-1);
		}
	cout << "The solution found in " << table[step].get_count() << " moves\n";
	temp.print();
	table[0]=temp;
	table[0].set_count(step-1);
}


int NPUZZLE::Board::find_blank_coordinat_y_new(vector<vector<int>> arr){ // find the blank coordinat => y
 int i=0;
 int k=0;
 for(i=0;i<=line;i++){
	 for(k=0;	k<=coloun;k++){
		 if(arr[i][k]==97){
			 return i ;
		 }
	 }
 }
}
int NPUZZLE::Board::find_blank_coordinat_x_new(vector<vector<int >> arr){ // find the blank coordinat => x
 int i=0;
 int k=0;
 for(i=0;i<=line;i++){
	 for(k=0;k<=coloun;k++){
		 if(arr[i][k]==97){
			 return k ;
		 }
	 }
 }
}
int NPUZZLE::Board::isSolved() const {
	int i,j;
	for(i=0;i<=line;i++){
		for(j=0;j<=coloun;j++){
			if(ptr[i][j]!=goal_ptr[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}

void ::NPUZZLE::Board::print_goal(){ // print the goal state
	int i;
 	int k;
 	for(i=0;i<=line;i++){
	 for(k=0;k<=coloun;k++){
		 if(goal_ptr[i][k]!=99 && goal_ptr[i][k]!=95){
			 if(goal_ptr[i][k]==97)
				 cout << "\t" ;
			 else{
				 if(goal_ptr[i][k]<10)
					 cout << "0" ;
				 cout << "" << goal_ptr[i][k] << "\t";
			 }
		 }
	 }
	 cout << "\n" ;
 }
}
void NPUZZLE::Board::print()const{ // print the current configuration
	int i;
 	int k;
 	for(i=0;i<=line;i++){
	 for(k=0;k<=coloun;k++){
		 if(ptr[i][k]!=99 && ptr[i][k]!=95){
			 if(ptr[i][k]==97)
				 cout << "\t" ;
			 else{
				 if(ptr[i][k]<10)
					 cout << "0" ;
				 cout << "" << ptr[i][k] << "\t";
			 }
		 }
	 }
	 cout << "\n" ;
 }
}
void NPUZZLE::Board::readFromFile(string name){
	int i=0;
  int k=0;
  int l=0;
  int m=0;
  int row=0;
	int max=0;
  char transformation[3];
  string satir[9] ;
  ifstream infile(name);
	while(getline(infile,satir[i])){
		i++;
	}
  satir[++i]='\0';
  i=0;
  k=0;
  l=0;
  do{
		ptr.push_back(vector<int>());

		while(satir[i][k]!='\n'  && satir[i][k]!='\0'){
			if(satir[i][k]=='b' && satir[i][k+1]=='b'){
					transformation[l++]='9';
					transformation[l++]='7';
			}
			else if(satir[i][k]=='b' && satir[i][k-1]=='b'){
					transformation[l++]='9';
					transformation[l++]='7';
			}
			else if(satir[i][k]==' ')
      {
				k++;
				if(satir[i][k]=='b' && satir[i][k+1]=='b'){
						transformation[l++]='9';
						transformation[l++]='7';
				}
			}

		  transformation[l]=satir[i][k];
      l++;
      k++;
      if(satir[i][k]==' '){
        transformation[l]='\0';
        l=0;
        k++;
      }
      else{
        transformation[l]=satir[i][k];
        k++;
        transformation[++l]='\0';
        l=0;
      }
      ptr[i].push_back(atoi(transformation));
		  m++;
			if(m>max && ptr[i][m]!=99){
				max=m;
			}
      transformation[0]='\0';
    }
		setcoloun(max-1);
		if(m<9){
			ptr[i].push_back(95);
			m++;
		}
 		while(m<9){
      ptr[i].push_back(99);
      m++;
    }
    i++;
    k=0;
    m=0;
    l=0;
  }while(satir[i]!="\0") ;
	row=i;
	while(i<9){
		ptr.push_back(vector<int>());

		m=0;
		while(m<9){
			ptr[i].push_back(99);
			m++;
		}
		i++;
	}
	setLine(row-1);
	copy_ptr(ptr,goal_ptr);
}
void NPUZZLE::Board::writeToFile(string name){
	int i=0;
  int j=0;

  ofstream dosyaYaz(name);
  while(i<=line){
    while(j<=coloun){
			if(ptr[i][j]==97){
				dosyaYaz << "bb ";
			}
			else if(ptr[i][j]!=99){

				if(ptr[i][j]<10){
            dosyaYaz << "0" ;
        }
        dosyaYaz << ptr[i][j] << " " ;
      }
      j++;
    }
      dosyaYaz  << "\n" ;
      i++;
      j=0;
  }
}
void NPUZZLE::Board::shuffle(int number_of_move){
	int blank_coordinat_x;
	int blank_coordinat_y;
	int random;
	int selection;
	int i;
	int last_move=-1;
	copy_ptr(goal_ptr,ptr); // from the goal state
	number_of_move=line*coloun;
	for(i=0;i<number_of_move || isSolved()==1;i++){
		random=rand()%4;
		while((random==0 && (move_up()==99))
			|| (random==1 && (move_left()==99))
			|| (random==2 && (move_down()==99))
			|| (random==3 && (move_right()==99))){
			random=rand()%4;
		}
	}
}
void NPUZZLE :: reset(int size){
		BoardObj.reset(size);
		table.push_back(BoardObj);
		temp=table[0];
}
void NPUZZLE::Board::reset(int size){
	int i=0;
	int k=0;
	for(i=0;i<size;i++){
		ptr.push_back(vector<int>());
		for(k=0;k<size;k++){
			ptr[i].push_back((i*size)+k+1);
		}
		for(k=k;k<9;k++){
			ptr[i].push_back(99);
		}
	}
	ptr[size-1][size-1]=97;
	for(i=i;i<9;i++){
		ptr.push_back(vector<int>());
		for(k=0;k<9;k++){
			ptr[i].push_back(99);
		}
	}
	setLine(size-1);
	setcoloun(size-1);
	copy_ptr(ptr,goal_ptr);
}
int NPUZZLE::Board::copy_ptr(vector <vector <int >> &ptr2,vector <vector<int >> &copy){
	int i=0;
	int k=0;
	for(i=0;i<9;i++){
		copy.push_back(vector<int>());
		for(k=0;k<9;k++){
			copy[i].push_back(ptr2[i][k]);
		}
	}
}
// THERE İS MOVE FUNCTİONS
int NPUZZLE::Board::move_left(){
	int blank_coordinat_x=find_blank_coordinat_x_new(ptr);
	int blank_coordinat_y=find_blank_coordinat_y_new(ptr);
	if(blank_coordinat_x==0 || ptr[blank_coordinat_y][blank_coordinat_x-1]==0 ){
		return 99 ;
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y][blank_coordinat_x-1];
		ptr[blank_coordinat_y][blank_coordinat_x-1]=97;
	}

}
int NPUZZLE::Board::move_right(){
	int blank_coordinat_x=find_blank_coordinat_x_new(ptr);
	int blank_coordinat_y=find_blank_coordinat_y_new(ptr);
	if(blank_coordinat_x==coloun || ptr[blank_coordinat_y][blank_coordinat_x+1]==0){
		return 99 ;
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y][blank_coordinat_x+1];
		ptr[blank_coordinat_y][blank_coordinat_x+1]=97;
	}
}
int NPUZZLE::Board::move_up(){
	int blank_coordinat_x=find_blank_coordinat_x_new(ptr);
	int blank_coordinat_y=find_blank_coordinat_y_new(ptr);
	if(blank_coordinat_y==0 || ptr[blank_coordinat_y-1][blank_coordinat_x]==0){
		return 99 ;
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y-1][blank_coordinat_x];
		ptr[blank_coordinat_y-1][blank_coordinat_x]=97;
	}
}
int NPUZZLE::Board::move_down(){
	int blank_coordinat_x=find_blank_coordinat_x_new(ptr);
	int blank_coordinat_y=find_blank_coordinat_y_new(ptr);
	if(blank_coordinat_y==line || ptr[blank_coordinat_y+1][blank_coordinat_x]==0){
		return 99;
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y+1][blank_coordinat_x];
		ptr[blank_coordinat_y+1][blank_coordinat_x]=97;
	}
}
// Inıtıal the goal state
void NPUZZLE::Board::initial_goal(){
	int m=1;
	int i=0;
	int j;
	int k;
	int l;
	for(i=0;i<=line;i++){
		//goal_ptr.push_back(vector<int>());
		for(j=0;j<=coloun;j++){
			if(goal_ptr[i][j]!=99 && goal_ptr[i][j]!=95){
				if(goal_ptr[i][j]==0){
					goal_ptr[i][j]=0;
					}
				else{
					goal_ptr[i][j]=m++;

					k=i;
					l=j;
				}
			}
		}
	}
	goal_ptr[line][coloun]=97;
		}
// 97 = blank 99 = nonusable
