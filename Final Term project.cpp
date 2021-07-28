#include <windows.h>//header file for console/windows graphics
#include<fstream>
#include<bits/stdc++.h>

using namespace std;

SetColor(int value)//Global Function for graphics and coloring
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),value);
}

ofstream fout; //Global output file handling object
ifstream fin;  //Global input file handling object

class Node {
  public:
   int marks;
  	Node * next;

  Node() {
    marks=0;
    next = NULL;
  }

};

class Queue 
{
  public:
  	Node *front;
  	Node *rear;
    Queue() 
	{
      front = NULL;
      rear = NULL;
    }
    
    bool isEmpty()
    {
    	if(front==NULL && rear==NULL)
    	{
    		return true;
		}
		else
		{
			return false;
		}
	 }
	void enqueue(Node *n) 
    {
	  if (isEmpty())
      {
        front = n;
        rear = n;
        //"Node  ENQUEUED successfully"
      }
      else
      {
        rear->next=n;
        rear=n;
        //"Node  ENQUEUED successfully"
      }
    
   }
	
	Node* dequeue() 
    {
        Node *temp=NULL;
      if (isEmpty()) 
      {
          // "Queue is Empty" 
          return NULL;
      } 
      else 
      {
        if(front==rear)
        {
          temp=front;
          front = NULL;
          rear = NULL;  
          return temp;
        }
        else
        {
          temp=front;
          front = front->next;  
          return temp;
        }
          
       }
    }
};

class NodeSA {
  public:
  string TypeSA;
  int point;
  string statementSA;
  string solutionSA;
  NodeSA * next;

  NodeSA() 
  {
    next = NULL;
  }
   
};
class NodeMC {
  public:
  string typeM;
  int point;
  string statementMC;
  string opt1;
  string opt2;
  string opt3;
  string rightopt;
  NodeMC * next;

  NodeMC() 
  {
    next = NULL;
  }
  
};

class NodeTF {
  public:
   string typeT;
   int points;
   string statementTF;
   string solutionT;
  
  NodeTF * next;

  NodeTF() 
  {
    next = NULL;
  }
  
};
int N;
string Guess;
NodeMC* tempM;
NodeSA* tempo;
NodeTF* tempT;
Queue Q;
class Question
{
	public:
    NodeSA* headSA;
    NodeMC* headMC;
    NodeTF* headTF;
	Question()
	{
		headSA= NULL;
		headMC=NULL;
		headTF=NULL;
	}
	
	void append_SA()
	
   {
   	    NodeSA* n1 = new NodeSA;
   	    if (headSA == NULL) 
		{
        headSA = n1;
        // "Node Appended" 
        
        } 
	    else 
	    {
        NodeSA * ptr = headSA;
        while (ptr -> next != NULL) 
		{
		  ptr = ptr -> next;
        }
        ptr -> next = n1;
        // "Node AppendedAfter"
        
	    }
      
   }
   void append_MC()
   {
   	   NodeMC* n1 = new NodeMC;
   	   if (headMC == NULL) 
	   {
           headMC = n1;
           // "MC Node Appended" 
       } 
	   else 
	   {
           NodeMC * ptr = headMC;
           while (ptr -> next != NULL) 
		   {
               ptr = ptr -> next;
           }
           ptr -> next = n1;
           // "MC Node AppendedAfter" 
      }
      
   }
   void append_TF()
   {
   	   NodeTF* n1 = new NodeTF;
   	   if (headTF == NULL) {
        headTF = n1;
        //"TF Node Appended" 
      } 
	  else 
	  {
        NodeTF * ptr = headTF;
        while (ptr -> next != NULL) 
		{
          ptr = ptr -> next;
        }
        ptr -> next = n1;
        //"TF Node AppendedAfter" 
      }
   }
   
   void readQuestion()
	{
		fin.open("file.txt",ios::in|ios::binary);
		if(!fin)
		{
			SetColor(12);cout<<"\a\nFile not found";SetColor(15);
		}
		else
		{
			NodeSA* temp;
			temp=headSA;
			NodeMC* tempMC;
			tempMC = headMC;
			NodeTF* tempTf; 
			tempTf= headTF;
			fin>>N;
			while(!fin.eof()&& temp!=NULL)
			{
				fin.read((char*) temp, (sizeof(*temp)-8));//storing question to short answers linkedlist 
				temp=temp->next;
				fin.read((char*) tempMC, (sizeof(*tempMC)-8));//storing questions to MCQ's linkedlist
				tempMC=tempMC->next;
				fin.read((char*) tempTf, (sizeof(*tempTf)-8));//storing questions to TF linkedlist
				tempTf=tempTf->next;
			}
			
		}
		fin.close();
		remove ("file.txt");
		tempo = headSA;		
		tempM = headMC;
		tempT=headTF;
	}
		
	void displayQuestionSA()//display function for SA Type questions
	{
		SetColor(11);cout<<"\nPoints: "<<tempo->point;SetColor(15);
		cout<<tempo->statementSA<<endl;
		SetColor(11);cout<<"\nEnter Your Answer\n";SetColor(15);
		cin>>Guess;
		if(Guess=="SKIP"|| Guess== "skip")
		{
			Node* queue = new Node();// runtime queue new node
			queue->marks = 0;
			cout<<"\nYou got 0 marks";
			Q.enqueue(queue);
		}
		else if(Guess==tempo->solutionSA)
		{
			SetColor(10);cout<<"\nCorrect Answer!\t ";SetColor(11);cout<<"You got" <<tempo->point<<" Points.\n"<<endl;SetColor(15);
			Node* queue = new Node();
			queue->marks =tempo->point;
			Q.enqueue(queue);
		}
		else
		{
			SetColor(12);cout<<"\nWrong Answer!\n"<<"\tYou lose "<<tempo->point<<" Points";SetColor(15);
			SetColor(10);cout<<"Correct answer is: "<<tempo->solutionSA;SetColor(15);
			Node* queue = new Node();
			queue->marks = -(tempo->point);
			Q.enqueue(queue);
		}
		tempo=tempo->next;	
				    
	}
		
	void displayQuestionMC()//display function for MC Type questions
	{
		SetColor(11);cout<<"\nPoints: "<<tempM->point;SetColor(15);
		cout<<tempM->statementMC<<endl;
		cout<<tempM->opt1<<endl;
		cout<<tempM->opt2<<endl;
		cout<<tempM->opt3<<endl;
		SetColor(11);cout<<"\nEnter Your Answer\n";SetColor(15);
		cin>>Guess;
		if(Guess=="SKIP" || Guess== "skip")
		{
			Node* queue = new Node();
			queue->marks = 0;
			cout<<"\nYou got 0 marks";
			Q.enqueue(queue);
		}
		else if(Guess==tempM->rightopt)
		{
			SetColor(10);cout<<"\nCorrect Answer!\t ";SetColor(11);cout<<"You got " <<tempM->point<<" Points.\n"<<endl;SetColor(15);
			Node* queue = new Node();
			queue->marks = tempM->point;
			Q.enqueue(queue);
		}
		else
		{
			SetColor(12);cout<<"\nWrong Answer!\n";
			SetColor(10);cout<<"Correct answer is: "<<tempM->rightopt;SetColor(12);cout<<"\tYou lose "<<tempM->point<<" Points";SetColor(15);
			Node* queue = new Node();
			queue->marks = -(tempM->point);
			Q.enqueue(queue);
		}
		tempM=tempM->next;			
	}
   
   void displayQuestionTF()//display function for TF Type questions
	{
		SetColor(11);cout<<"\nPoints: "<<tempT->points;SetColor(15);
		cout<<tempT->statementTF<<endl;
		SetColor(11);cout<<"\nEnter Your Answer\n";SetColor(15);
		cin>>Guess;
		if(Guess=="SKIP" || Guess== "skip")
		{
			Node* queue = new Node();
			queue->marks = 0;
			cout<<"\nYou got 0 marks";
			Q.enqueue(queue);
		}
		else if(Guess==tempT->solutionT)
		{
			SetColor(10);cout<<"\nCorrect Answer!\t";SetColor(11);cout<<" You got "<<tempT->points<<" Points.\n";SetColor(15);
			Node* queue = new Node();
			queue->marks = tempT->points;
			Q.enqueue(queue);
		}
		else
		{
			SetColor(12);cout<<"\a\nWrong Answer!\n";
			SetColor(10);cout<<"Correct answer is: "<<tempT->solutionT;SetColor(12);cout<<"\tYou lose "<<tempT->points<<" Points";SetColor(15);
			Node* queue = new Node();
			queue->marks = -(tempT->points);
			Q.enqueue(queue);
		}
		tempT=tempT->next;
					
	}
				
		
};

class Input_QuestionsSA
{
	public:
		string typeSA;
		int points;
		string Question_Text;
		string Correct_Answer;
		
		void setValuesSA(string t, int p, string q,string c)//writing SA type questions to the file
		{
			typeSA= t;
			points = p;
			Question_Text = q;
			Correct_Answer = c;
			fout.open("file.txt",ios::app|ios::binary);
			fout.write((char*) this,sizeof(*this));
			fout.close();
		
		}
		
};

class Input_QuestionsMC
{
	public:
		string typeMC;
		int points;
		string Question_Text;
		string Answer_1;
		string Answer_2;
		string Answer_3;
		string Correct_Answer;
		void setValuesMC(string t, int p, string q,string a1,string a2, string a3, string c)//writing MC type questions to the file
		{
			typeMC=t;
			points=p;
			Question_Text=q;
			Answer_1=a1;
			Answer_2=a2;
			Answer_3=a3;
			Correct_Answer=c;
			fout.open("file.txt",ios::app|ios::binary);
			fout.write((char*) this,sizeof(*this));
			fout.close();
		}
			
};

class Input_QuestionsTF
{
	public:
		string typeTF;
		int points;
		string Question_Text;
		string Correct_Answer;
		void setValuesTF(string t, int p, string q, string c)//writing TF type questions to the file
		{
			typeTF=t;
			points=p;
			Question_Text=q;
			Correct_Answer=c;
			fout.open("file.txt",ios::out|ios::app|ios::binary);
			fout.write((char*) this,sizeof(*this));
			fout.close();
		}
 	
};

int main()
{
	Question qs;
	Input_QuestionsSA QS1;
	Input_QuestionsSA QS2;
	Input_QuestionsSA QS3;
	Input_QuestionsSA QS4;
	Input_QuestionsSA QS5;
	Input_QuestionsMC QM1;
	Input_QuestionsMC QM2;
	Input_QuestionsMC QM3;
	Input_QuestionsMC QM4;
	Input_QuestionsMC QM5;
	Input_QuestionsTF QT1;
	Input_QuestionsTF QT2;
	Input_QuestionsTF QT3;
	Input_QuestionsTF QT4;
	Input_QuestionsTF QT5;
	int total=0,count=0,x;
	char num[2]; // input question number to attempt 
	string filename,fname,lname;
	bool flag=0;
	fout.open("file.txt",ios::out|ios::binary);
	fout<<15;
	fout.close();
	QS1.setValuesSA("\nSA\t",5,"\nQuestion: Which key is used in combination with another key to perform a specific task?", "control");
	QM1.setValuesMC("\nMC\t",5,"\nQuestion: Which of  the following is an Input Device?","A: Keyboard","B: LCD", "C: Printer ", "A");
	QT1.setValuesTF("\nTF\t",5,"\nQuestion: Is Computer an Electronic Device?. true/false ", "true");
	QS2.setValuesSA("\nSA\t",5,"\nQuestion: The term Computer is derived from which language?", "latin");
	QM2.setValuesMC("\nMC\t",5,"\nQuestion: A computer cannot boot if it does not have the?","A: compiler","B: Loader", "C: operating system ", "C");
	QT2.setValuesTF("\nTF\t",5,"\nQuestion: Formatting is the process of dividing the disk into tracks and sectors?. true/false ", "true");
	QS3.setValuesSA("\nSA\t",5,"\nQuestion: Junk e-mail is also called?", "spam");
	QM3.setValuesMC("\nMC\t",5,"\nQuestion: By default, your documents print in  mode?","A: Landscape","B: Potrait", "C: Print view ", "B");
	QT3.setValuesTF("\nTF\t",5,"\nQuestion: A Site is a software program used to view Web pages.?. true/false ", "false");
	QS4.setValuesSA("\nSA\t",5,"\nQuestion: The first computer was programmed using which Language?", "machine");
	QM4.setValuesMC("\nMC\t",5,"\nQuestion: Which of the following is a popular programming language for developing multimedia webpages?","A:Java","B: Basic", "C: COBOL ", "A");
	QT4.setValuesTF("\nTF\t",5,"\nQuestion: Several computers linked to a server to share programs and storage space by Network?. true/false ", "true");
	QS5.setValuesSA("\nSA\t",5,"\nQuestion: Where is RAM located??", "motherboard");
	QM5.setValuesMC("\nMC\t",5,"\nQuestion: The box that contains the central electronic components of the computer is the?","A: Motherboard","B: RAM", "C: System Unit", "C");
	QT5.setValuesTF("\nTF\t",5,"\nQuestion: In MICR, C stands for COLOR?. true/false ", "false");
	
	qs.append_SA();
	qs.append_SA();
	qs.append_SA();
	qs.append_SA();
	qs.append_SA();
	qs.append_MC();
	qs.append_MC();
	qs.append_MC();
	qs.append_MC();
	qs.append_MC();
	qs.append_TF();
	qs.append_TF();
	qs.append_TF();
	qs.append_TF();
	qs.append_TF();

	qs.readQuestion();
	system("cls");
	cout<<endl<<endl;
	SetColor(15);
	for(int i=0;i<66;i++){cout<<char(176);}cout<<char(201);for(int i=0;i<30;i++){cout<<char(205);}cout<<char(187);for(int i=0;i<69;i++){cout<<char(176);}cout<<"\n";
	for(int i=0;i<66;i++){cout<<char(176);}cout<<char(186);SetColor(9);cout<<"       Quizzer System   ";for(int i=0;i<6;i++){cout<<" ";}SetColor(7);cout<<char(186);for(int i=0;i<69;i++){cout<<char(176);}cout<<"\n";
	for(int i=0;i<66;i++){cout<<char(176);}cout<<char(200);for(int i=0;i<30;i++){cout<<char(205);}cout<<char(188);for(int i=0;i<69;i++){cout<<char(176);}cout<<"\n";
	cout<<endl;
	cout<<"\nWhat is Your First Name: ";
	cin>>fname;
	cout<<"What is Your Last Name: ";
	cin.ignore();
	getline(cin,lname);
	y:
	cout<<"\nWhat File stores your questions: ";
	cin>>filename;
	if(filename=="file.txt")
	{
		SetColor(10);cout<<"\nFile Loaded successfully \n";SetColor(15);
		do
	    { 
		   cin.ignore(numeric_limits<streamsize>::max(),'\n');
		   cout<<"\nHow many Questions would you (like out of 15)\n ";
	       cin>>num;
	       
	       if(isdigit(num[0]))
	       {
	       	    size_t pos = strlen(num);
	       	    x = atoi(&num[pos-2]);
	       	    if(x==0)
	       	    {
	       	    	x = atoi(&num[pos-1]);
				}
	       	    if(x==N||x<N)
	       	    { 
	       	   	    srand(time(NULL));
                    for(int i=0; i<x;)
                    {
              	        int ch= rand() % 100;
            	        if(ch%5==0&&tempo!=NULL)
            	        {
            	 	      qs.displayQuestionSA();
            	 	      i++;
				        }
				        else if(ch%2==0&&tempM!=NULL)
				        {
					      qs.displayQuestionMC();
					      i++;
				        }
				        else if(tempT!=NULL)
				        {
					       qs.displayQuestionTF();
					       i++;
				        }
			       }
                    flag= 1;
                }
	       	   	else if(x>N) 
	       	   	{
	       	   		SetColor(12);cout<<"Sorry, they are Too many!!\n";SetColor(15);
				}
				
		   }
	       else 
	       {
	       	  SetColor(12);cout<<"Wrong Input\n";SetColor(15);  
		   }
	    	   
	    }
    	while(flag== 0);
    	
    	for(int i = 1;i<=x;i++)
    	{
    		Node* new_node;
    		new_node= Q.dequeue();// returning address of the pointer from the Node Queue class.
    		cout<<endl;
    		SetColor(7);cout<<"Q"<<i<<"= "<<new_node->marks;SetColor(15);
    		total = total+new_node->marks;
    	}
    	//=========================================================RESULT===============================================================
    	cout<<endl;
		system("pause");
    	system("cls");
		cout<<endl<<endl;
		SetColor(7);for(int i=0;i<71;i++)cout<<"*";SetColor(9);cout << char(218);      for(int i=0; i<21; i++){cout << char(196);}cout << char(191);SetColor(7);for(int i=0;i<72;i++)cout<<"*";cout<<endl;
		SetColor(7);for(int i=0;i<71;i++)cout<<"*";SetColor(9);cout << char(179);SetColor(15);cout << "        RESULT       ";SetColor(9);cout << char(179);SetColor(7);for(int i=0;i<72;i++)cout<<"*";cout<<endl;
		SetColor(7);for(int i=0;i<71;i++)cout<<"*";SetColor(9);cout << char(192);      for(int i=0; i<21; i++){cout << char(196);}cout << char(217);SetColor(7);for(int i=0;i<72;i++)cout<<"*";cout<<endl;
	   	SetColor(14);
	  	cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------";
		SetColor(11);
		cout<<"\n\n\n\tFull Name :: "<<fname<<" "<<lname;
    	if(total>0)
    	{
    		SetColor(11);cout<<"\n\tTotal Marks\t: "<<total;SetColor(15);
		}
		else
		{
			SetColor(11);cout<<"\n\tTotal Marks\t: "<<0;SetColor(15);
		}
		SetColor(13);cout<<"\n\n\tTHANK YOU FOR USING THIS PROGRAM";SetColor(15);
    	
	}
	else
	{
		SetColor(12);cout<<"Wrong File\n";SetColor(15);
		goto y;
	}
	return 0;
}
