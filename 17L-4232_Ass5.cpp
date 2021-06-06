#include<iostream>
#include<conio.h>
#include<fstream>
#include<vector>
#include<list>

using namespace std;
template<class T, class K>
class User
{
private:
	T key; //priority
	K ID;
	char operation;
public:
	User()  //constructor
	{
		key = -1;
		ID = -1;
		operation = 'n';
	}
	User(const User& rhs) //copy constructor 
	{
		key = rhs.key;
		ID = rhs.ID;
		operation = rhs.operation;
	}
	User(T k, K id, char o)	 //Over-Loaded Constructor
	{
		key = k;
		ID = id;
		operation = o;
	}
	void setData(T k, K id, char o)			//update values
	{
		key = k;
		ID = id;
		operation = 0;
	}
	T getPriority()				   //to access priority value
	{
		return key;
	}
	K getID()				   //to access ID of user
	{
		return ID;
	}
	char getOperation()		  //to access operation of user on file
	{
		return operation;
	}
	bool operator==(const User &rhs)
	{
		if (key == rhs.key)				 //if found then true
			return true;
		else
			return false;
	}
	bool operator!=(const User &rhs)
	{
		if (key != rhs.key)				  //if not found then true
			return true;
		else
			return false;
	}
	bool operator>(const User &rhs)
	{
		return (key > rhs.key);					//if greater then true
	}
	bool operator<(const User&rhs)
	{
		return(key < rhs.key);					   //if smaller then true
	}

	const User& operator=(const User &rhs)		  //assignment operator
	{
		if (&rhs != this) //check for self assignment
		{
			key = rhs.key;
			ID = rhs.ID;
			operation = rhs.operation;
		}
		return *this;
	}
	void PrintUser()							//Print function of user
	{
		cout << key << " " << ID << " " << operation;
	}
};

template<class T>
class MaxHeap
{
private:
	vector<T> data;		//array or vector to store data
	int csize; //current size of heap
	int range;	  //capacity of heap
	T min;
public:

	MaxHeap(int r = 10)
	{
		csize = 1;
		range = r;
	}
	MaxHeap(T d, int c, int r)
	{
		//data.resize(csize - 1);  //resizing vector
		//data.insert(d); //push_back(d);    //inserting value in vector
		csize = c;
		range = r;
	}
	void ReHeapUP(int curr, int size)
	{
		int parent;
		if (curr < size)	//if in range
		{
			parent = curr / 2;		 //parent=current/2 when start from index 1 
		}
		if (parent >= 1 && data[parent] < data[curr])
		{
			swapData(data[parent], data[curr]);		 //if destroying heap property then swap
			ReHeapUP(parent, range);
		}
	}

	void Heapify(int i)
	{
		//i is current element 
		int l = 2 * i;			   //left child index
		int r = 2 * i + 1;		 //right child index
		int largest = i;
		if (l <= csize && data[l] > data[i])
			largest = l;
		if (r <= csize && data[r] > data[largest])
			largest = r;
		if (largest != i)
		{
			swapData(data[i], data[largest]);		 //if destroying heap property then swap
			Heapify(largest);
		}
	}
	bool IsEmpty() //if no element in heap then true
	{
		if (csize == 1)
			return true;
		else
			return false;
	}
	int size()		 //return current size of heap
	{
		return csize;
	}
	void Insert(T element)
	{
		if (csize < range)
		{
			if (csize == 1)
				min = element;
			else if (element < min)
				min = element;
			data.resize(csize);		 //resize vector
			data.push_back(element);//[csize] = element;		 //add element to vector
			csize++;
			ReHeapUP(csize-1 , range);
			//csize = data.size();
		}
	}
	void swapData(T &a, T &b)  //exchange a with b
	{
		T temp = a;
		a = b;
		b = temp;
	}
	T ExtractMax()
	{
		if (!IsEmpty())
		{
			T temp = data[1];
			csize--;						 //decreasing current size of heap
			data[1] = data[csize ];			 //reassignming data
			Heapify(1);
			return temp;
		}
		else
			cout << "Empty Queue";
	}
	void BuildHeap(T* d, int size)		   	  //takes unsorted array and turn it into heap
	{
		for (int i = size / 2 - 1; i >= 1; i--)
			Heapify(i);
	}
	void print()
	{
		for (int i = 1; i < csize; i++)
			cout << data[i] << "," << endl;
	}
	T& findMax()			 //return data of root
	{
		return data[1];
	}
	T& findMin()
	{
		/*
		T min = data[csize / 2 + 1];
		for (int i = csize / 2 + 2; i <= csize - 1; i++)
		if (data[i] < min)
		min = data[i];*/
		return min;
	}
	void setRange(int c, int r)
	{
		csize = c;
		range = r;
	}

};
class file
{
private:
	int fileId;
	int TUsers;					   //Users Accessing the file
	char operation;				   //current operation on file
	vector<int> currentUsersID;	   //Users accessing the file presently
	MaxHeap< User <int, int> > Queue;	   //waiting queue of users
public:
	file()
	{
		fileId = -1;
		TUsers = 0;
		Queue.setRange(1, 100);

	}
	file(const file&rhs)			  //copy constructor
	{
		fileId = rhs.fileId;
		TUsers = rhs.TUsers;
		operation = rhs.operation;
		currentUsersID = rhs.currentUsersID;
		Queue = rhs.Queue;
	}
	void setID(int i)
	{
		fileId = i;
	}
	file(int f, User<int, int> user)   //constructor
	{
		fileId = f;
		TUsers = 0;
		Queue.setRange(1, 100);
		Queue.Insert(user);
	}
	void printfile()
	{

		if (currentUsersID.empty())
			cout << "-> File " << fileId << " ... Access granted to no-one";
		else
			cout << "-> File " << fileId << " ... Access granted to User " << currentUsersID[0] << " " << operation;
		if (!Queue.IsEmpty())
		{
			User<int, int > s = Queue.findMax();
			cout << endl << "\t \t \t \t" << "\t" << "Next User " << s.getID() << "  " << s.getOperation() << endl;
			cout << endl << "\t \t \t \t" << "\t" << "Wating " << Queue.size() - 1 << " Users" << endl;
		}
		else
		{
			cout << endl << "\t \t \t \t" << "\t" << "No Next User in Queue" << endl;
			cout << endl << "\t \t \t \t" << "\t" << "No one is Wating" << endl;
		}
	}
	void FileAccess(file &f, User<int, int> u)
	{
		int flag = 0;
		if (u.getOperation() == 'w')
		{
			f.TUsers++;
			f.currentUsersID.resize(f.TUsers);		//adding to vector of current user
			cout << "User " << u.getID() << " can access the file." << endl;
			f.currentUsersID[f.TUsers - 1] = u.getID();
			f.operation = 'W';
		}
		else if (u.getOperation() == 'r')
		{
			f.TUsers++;
			f.currentUsersID.resize(f.TUsers);	//adding to vector of current user
			cout << "User " << u.getID() << " can access the file." << endl;
			f.currentUsersID[f.TUsers - 1] = u.getID();
			f.operation = 'R';
		}
		u = Queue.ExtractMax();	 //remove from queue
	}
	void RA(file &f, User<int, int> &u)
	{

		int flag = 0;
		if (u.getOperation() == 'w')
		{
			f.TUsers++;
			f.currentUsersID.resize(f.TUsers);
			cout << "User " << u.getID() << " can access the file." << endl;
			f.currentUsersID[f.TUsers - 1] = u.getID();
			f.operation = 'W';
		}
		if (u.getOperation() == 'r' || u.getOperation() == 'R')
		{

			while (u.getOperation() == 'r' || u.getOperation() == 'R'&&flag == 0)
			{
				f.TUsers++;
				f.currentUsersID.resize(f.TUsers);
				cout << "User " << u.getID() << " can access the file." << endl;
				f.currentUsersID[f.TUsers - 1] = u.getID();
				u = Queue.ExtractMax();
				f.operation = 'R';
			}

			if (!f.Queue.IsEmpty())
				u = Queue.findMax();
			else
				flag = 1;
		}
	}
	void EndAccess(file &s, int userId)
	{
		if (s.currentUsersID.empty())
			cout << "No one is accessing a file. You entered wrong information." << endl;
		else
		{
			vector<int>::iterator i = s.currentUsersID.begin();
			vector<int>::iterator e = s.currentUsersID.end();
			while (i != e)
			{
				if (*i == userId)
				{
					s.currentUsersID.erase(i); //remove user from current users
					break;
				}

			}
			TUsers--;
		}
	}
	void AddUserQueue(file *f, User<int, int>& u)
	{
		f->Queue.Insert(u);
		if (f->Queue.findMax() == u)
			FileAccess(*f, u);
		else
			cout << "Sorry you have to wait to access this file." << endl;
	}
	int getQueueMax()
	{
			User<int, int> temp = Queue.findMax();
			return temp.getPriority();
		
	}
	User<int, int>& GetTopUser()
	{
		if (Queue.IsEmpty())
			cout << "No one is in waiting queue." << endl;
		else
			return Queue.findMax();
	}
	void RemoveFromQueue()
	{
		Queue.ExtractMax();
	}
	int getQueueMin()
	{
		if (!Queue.IsEmpty())
		{

			User<int, int> temp = Queue.findMin();
			return temp.getPriority();
		}
		else
			return 1;
	}

	int getTUsers()
	{
		return TUsers;
	}
	int getFileID()
	{
		return fileId;
	}
};

int GPN(int n)		 //Greatest Prime Number
{
	int num;
	int flag = 0;
	for (int k = n + 1; k <= n + 1000; k++)
	{
		num = k;
		flag = 0;
		for (int i = 2; flag == 0 && i < num - 1; i++)
		{
			if (num %i == 0)
				flag = 1;
		}
		if (flag == 0)
			break;

	}
	return num;
}


class HashTable{
private:
	std::vector<list<file>> H;
public:

	HashTable() : H(500) {

	}
	void RequestFileAccess()
	{
		file temp;
		User<int, int> user;
		int u, f, p, k;
		char o, P;
		cout << "Enter User ID" << '\t';
		cin >> u;
		cout << "Enter File ID" << '\t';
		cin >> f;
		cout << "Select Method for giving priority ;" << endl << endl << "Select 1 for integer value else press 2 for high/low priority";
		cin >> p;

		temp = GetFileIndex(temp,f);

		if (p == 1)
		{
			cout << "Enter Priority Value:\t";
			cin >> p;
			k = p;
		}
		else if (p == 2)
		{
			cout << "Press 'H'or'h' for high priority or 'L' or 'l' for low priority" << endl;
			cin >> P;
			k = p;
			if (P == 'H' || P == 'h')
				k = temp.getQueueMax();
			else if (P == 'L' || P == 'l')
				k = temp.getQueueMin();
			else
				cout << "You Entered Wrong value. Please Enter Valid Value" << endl;
		}
		else
			cout << "You Entered Wrong value." << endl;
		cout << "Enter Operation Type.Press 'w' for writing or press 'r' for reading." << endl;
		cin >> o;
		User<int, int> NewUser(k, u, o);
		if (Search(f) == true)
		{

			file s;
				GetFileIndex(s,f);
			s.AddUserQueue(&s, NewUser);
			update(s);
			Insert(s);
		}
		else
			cout << "No file exist with given key." << endl;
	}
	void ReleaseFile()
	{
		int u, f;
		cout << "Enter User ID:" << '\t';
		cin >> u;
		cout << "Enter File ID:" << '\t';
		cin >> f;
		file s;
			GetFileIndex(s,f);
		if (s.getFileID() == f)
		{

			s.EndAccess(s, u);
			s.RA(s, s.GetTopUser());//fileaccess
			update(s);
			Insert(s);
		}
		else
			cout << "No file exist with this ID." << endl;
	}
	void Readfile()
	{
		ifstream fin;
		int fileID, UserID, Priority;
		char Access;
		fin.open("file.txt");
		char buffer[100];
		if (fin.is_open())
		{
			fin.getline(buffer, 100, '\n');
			while (!fin.eof())
			{

				fin >> fileID;
				fin >> UserID;
				fin >> Priority;
				fin >> Access;
				User<int, int> u(Priority, UserID, Access);	    //creat user after reading from input file
				file f(fileID, u);							   //make file with user
				this->Insert(f);							   //insert file in table
			}
		}
		else
			cout << "Error: File Not Found." << endl;
	}
	void Insert(file x)
	{
		int id = x.getFileID();
		H[HashFun(id)].push_back(x); //insert at empty place of list 
	}
	file GetFileIndex(file &f ,int x)
	{
	//	file f;
		int hf = HashFun(x);
		if (!H[hf].empty())
		{
			list<file>::iterator i = H[hf].begin();
			list<file>::iterator e = H[hf].end();
			for (i; i != e; i++)
			{
				if (i->getFileID() == x)
				{
					f = *i;
					return *i;
				}
			}
		}
		//else
			//cout << "No file exist. " << endl;
			//return f;//empty file
	}

	bool Search(int x)
	{
		int hf = HashFun(x);
		list<file>::iterator i = H[hf].begin();
		list<file>::iterator e = H[hf].end();
		for (i; i != e; i++)
		{
			if (i->getFileID() == x)   //if found in list
				return true;
		}
		return false;
	}
	void Delete(file x)
	{
		if (x.getTUsers() == 0)
		{
			int flag = 0;
			int a = x.getFileID();
			int hf = HashFun(a);
			if (!H[hf].empty())
			{

				list<file>::iterator i = H[hf].begin();
				list<file>::iterator e = H[hf].end();
				for (i; i != e && flag == 0; i++)
				{
					if (i->getFileID() == x.getFileID())
					{
						flag = 1;
						break;
					}
				}
				if (flag == 1)
				{
					H[hf].erase(i);
				}
			}
			else
				cout << "No file with this ID exist in Table." << endl;
		}
		else
			cout << "Can't delete file as file is in use by a user." << endl;
	}
	void update(file x)
	{
		int flag = 0;
		int a = x.getFileID();
		int hf = HashFun(a);
		if (!H[hf].empty())
		{

			list<file>::iterator i = H[hf].begin();
			list<file>::iterator e = H[hf].end();
			for (i; i != e && flag == 0; i++)
			{
				if (i->getFileID() == x.getFileID())
				{
					flag = 1;
					break;
				}
			}
			if (flag == 1)
			{
				H[hf].erase(i);
			}
		}
	}

	int HashFun(int x, int tableSize = 500)
	{
		int p = GPN(tableSize);
		int a = 11;
		int b = 21;
		int H = ((a*x + b) % p) % tableSize;
		return H;
	}
	void PrintTable()
	{
		for (int i = 0; i < 500;)
		{
			if (H[i].empty())
				i++;
			else
			{
				cout << "H" << i;

				list<file>::iterator s = H[i].begin();
				list<file>::iterator e = H[i].end();
				for (s; s != e; s++)
				{
					s->printfile();
				}
				i++;
			}
		}
	}
	void Menu()
	{
		char k;
		cout << "****************************************MENU***********************************************************" << endl;
		cout << "-------------------------------------------------------------------------------------------------------" << endl;
		cout << "Press 'E' To Quit Menu." << endl;
		cout << "Press 'P' To Print Hash table with file information." << endl;
		cout << "Press 'L' To Load Data from file." << endl;
		cout << "Press 'I' To insert a file." << endl;
		cout << "Press 'D' To delete a file." << endl;
		cout << "Press 'A' To Request an Access to file." << endl;
		cout << "Press 'R' To Release the file by user." << endl;
		cout << "-------------------------------------------------------------------------------------------------------" << endl;
		cout << "*******************************************************************************************************" << endl;
		cin >> k; //which option to deal with

		while (k != 'E')
		{
			if (k == 'P') //Print Table
			{
				cout << "**************************************************************************************************" << endl;
				cout << " ***Hash Table with File Information.*** " << endl;
				PrintTable();
				cout << "**************************************************************************************************" << endl;
			}
			if (k == 'L') //Load Data from file
			{
				cout << "**************************************************************************************************" << endl;
				cout << " ***Data Loaded from File*** " << endl;
				Readfile();
				cout << "**************************************************************************************************" << endl;
			}
			if (k == 'I')	//Insert file in table
			{
				cout << "**************************************************************************************************" << endl;
				int id;
				cout << "Enter file ID:\t";
				cin >> id; //take input from user and then insert the file
				file f;
				f.setID(id);
				Insert(f);
				cout << " *** File Inserted*** " << endl;
				cout << "**************************************************************************************************" << endl;
			}
			if (k == 'D')
			{
				cout << "**************************************************************************************************" << endl;
				int id;
				cout << "Enter file ID:\t";
				cin >> id;  //take input from user then delete the file
				file f;
				f.setID(id);
				Delete(f);
				cout << " *** File Deleted*** " << endl;
				cout << "**************************************************************************************************" << endl;
			}
			if (k == 'A')
			{
				cout << "**************************************************************************************************" << endl;
				cout << " ***Access File*** " << endl;
				RequestFileAccess();
				cout << "**************************************************************************************************" << endl;
			}
			if (k == 'R')
			{
				cout << "**************************************************************************************************" << endl;
				cout << " ***Release File*** " << endl;
				ReleaseFile();
				cout << "**************************************************************************************************" << endl;
			}
			cin >> k; //which option to deal with
		}
	}
};
void main()
{

	HashTable H;
	H.Menu();
	//H.Readfile();
	//H.RequestFileAccess();
	//H.ReleaseFile();
	//H.PrintTable();

	_getch();
}