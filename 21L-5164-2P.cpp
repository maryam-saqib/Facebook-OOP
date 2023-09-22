#include<iostream>
#include<fstream>
#include<string>
using namespace std;

template<class T>
void Deallocate2DArray(T** array)
{
	for (int i = 0; array[i] != 0; i++)
	{
		delete array[i];
	}
	delete[] array;
}
class Helper
{
public:
	/// <summary>
	/// Takes a string and returns its length
	/// </summary>
	/// <param name="str">Character Array</param>
	/// <returns>Length of String</returns>
	static int StringLength(const char* str)
	{
		int strLen = 0;
		for (int i = 0; str[i] != '\0'; i++)
			strLen++;

		return strLen;
	}
	/// <summary>
	/// Takes two strings and copies the second one into first
	/// </summary>
	/// <param name="dest">Destination string</param>
	/// <param name="src">Source string</param>
	static void StringCopy(char*& dest, const char*& src) {
		const char* ptr = src;
		int i = 0;
		while (*ptr != 0)
		{
			dest[i] = *ptr;
			i = i + 1;
			ptr++;
		}
		dest[i] = 0;
	}
	/// <summary>
	/// Gets string from buffer and stores it on destination
	/// </summary>
	/// <param name="str">Original string on stack</param>
	/// <returns>String on heap</returns>
	static char* GetStringFromBuffer(const char* str)
	{

		int strLen = StringLength(str);
		char* string = 0;
		strLen = strLen + 1;
		if (strLen > 0) //checking if size is greater than zero
		{
			string = new char[strLen]; //dynamically allocates an array
			char* tempDest = string;
			StringCopy(tempDest, str);
		}
		else
		{
			string = new char[strLen];
			string[0] = '\0';
		}
		return string;
	}
	/// <summary>
	/// Takes two strings and compares them
	/// </summary>
	/// <param name="cstring1">First string</param>
	/// <param name="cstring2">Second string</param>
	/// <returns>1 or -1 or 0</returns>
	static int CompareString(const char* cstring1, const char* cstring2)
	{
		int i = 0;
		for (i = 0; cstring1[i] != '\0' && cstring2[i] != '\0'; i++) //iterates till the end of strings
		{

			if (cstring1[i] < cstring2[i])
			{
				return -1;
			}
			else if (cstring1[i] > cstring2[i])
			{
				return 1;
			}
		}
		if ((cstring1[i] == '\0') && (cstring2[i] != '\0'))
		{
			return 2;
		}
		return 0;
	}
	/// <summary>
	/// Takes two strings and appends second string at the end of first one
	/// </summary>
	/// <param name="cstring1">First String</param>
	/// <param name="cstring2">Second String</param>
	static void StringConcatenate(char*& cstring1, const char* cstring2)
	{
		char* newStr = new char[StringLength(cstring1) + StringLength(cstring2) + 1]; //dynamically creates an array
		char* ptr = cstring1;
		char* temp = newStr;
		while (*ptr != '\0') //iterates through first string and stores value in temporary string
		{
			*temp = *ptr;
			ptr++;
			temp++;
		}
		while (*cstring2 != '\0') //iterates through second string and stores value in temporary string
		{
			*temp = *cstring2;
			cstring2++;
			temp++;
		}
		*temp = '\0';
		delete[] cstring1;
		cstring1 = NULL;
		cstring1 = newStr; //storing value in first string
	}
};

class Post;

class Object
{
	char* id;
public:
	Object(char* i = 0)
	{
		id = i;
	}
	/// <summary>
	/// Assigns values of an object to a previously created object
	/// </summary>
	/// <param name="rhs">Object whose values have to be assigned</param>
	/// <returns>Object with modified values</returns>
	const Object& operator=(const Object& rhs)
	{
		if (&rhs != this)
		{
			if (id)
				delete[]id;
			id = Helper::GetStringFromBuffer(rhs.id);
		}
		return *this;
	}
	char* GetObjectId()
	{
		return id;
	}
	void SetObjectId(char* i)
	{
		id = i;
	}
	virtual void AddPostToTimeline(Post*)
	{
	}
	virtual void PrintName()
	{
	}
	~Object()
	{
		delete[]id;
	}
};
class Date
{
	int day;
	int month;
	int year;
	static Date currDate;
public:
	Date()
	{
		day = 0;
		month = 0;
		year = 0;
	}
	int GetDay()
	{
		return day;
	}
	int GetMonth()
	{
		return month;
	}
	int GetYear()
	{
		return year;
	}
	static void SetCurrDate(int d = 0, int m = 0, int y = 0)
	{
		currDate.day = d;
		currDate.month = m;
		currDate.year = y;
	}
	static Date GetCurrDate()
	{
		return currDate;
	}
	/// <summary>
	/// Takes input file stream and reads values of date from file
	/// </summary>
	/// <param name="fin">Input File Stream</param>
	void ReadDataFromFile(ifstream& fin)
	{
		fin >> day;
		fin >> month;
		fin >> year;
	}
	void PrintDate()
	{
		cout << day << "/" << month << "/" << year;
	}
	~Date()
	{
	}
};
Date Date::currDate;
class Comment
{
	const char* id;
	char* text;
	Object* commentBy;
	static int totalComments;
public:
	Comment()
	{
		id = text = 0;
		commentBy = 0;
	}
	static void SetTotalComments(int c)
	{
		totalComments = c;
	}
	static int GetTotalComments()
	{
		return totalComments;
	}
	void IncrementTotalComments()
	{
		totalComments++;
	}
	void SetCommentId(const char* i)
	{
		id = i;
	}
	void SetCommentText(char* t)
	{
		text = t;
	}
	void SetCommentBy(Object* oPtr)
	{
		commentBy = oPtr;
	}
	/// <summary>
	/// Prints the comment acc to format
	/// </summary>
	void PrintComment()
	{
		commentBy->PrintName();
		cout << " wrote:" << "\"" << text << "\"" << endl;
	}
	~Comment()
	{
		delete[]id;
		delete[]text;
	}
};
int Comment::totalComments = 0;

class Activity
{
	int type;
	char* value;
public:
	Activity()
	{
		type = 0;
		value = 0;
	}
	/// <summary>
	/// Sets the type and value of activity equal to passed values
	/// </summary>
	/// <param name="t">Type of Activity</param>
	/// <param name="v">Value of Activity</param>
	void SetActivity(int t, char* v)
	{
		type = t;
		value = v;
	}
	void ReadDataFromFile(ifstream& fin)
	{
		char temp[50] = "\0";
		fin >> type;
		fin.getline(temp, 50);
		value = Helper::GetStringFromBuffer(temp);
	}
	char* GetType()
	{
		char* temp = 0;
		if (type == 1)
		{
			temp = Helper::GetStringFromBuffer("feeling");
		}
		else if (type == 2)
		{
			temp = Helper::GetStringFromBuffer("thinking about");
		}
		else if (type == 3)
		{
			temp = Helper::GetStringFromBuffer("making");
		}
		else if (type == 4)
		{
			temp = Helper::GetStringFromBuffer("celebrating");
		}
		return temp;

	}
	char* GetValue()
	{
		return value;
	}
	~Activity()
	{
	}
};

class Post
{
	const char* id;
	char* text;
	Comment** comments;
	Date sharedDate;
	Object* sharedBy;
	Activity* activity;
	Object** likedBy;
	static int totalPosts;
	int cIdx;
	int oIdx;
public:
	Post(Object* s = 0, const char* i = 0, char* t = 0, Comment** c = 0, Date d = Date::GetCurrDate(), Activity* a = 0, Object** l = 0, int idx = 0, int odx = 0)
	{
		id = i;
		text = t;
		comments = c;
		comments = new Comment * [11];
		comments[0] = 0;
		sharedDate = d;
		sharedBy = s;
		activity = a;
		likedBy = l;
		cIdx = idx;
		oIdx = odx;
	}
	/// <summary>
	/// Sets the number of posts equal to the posts passed
	/// </summary>
	/// <param name="p">Number of posts passed</param>
	static void SetTotalPosts(int p)
	{
		totalPosts = p;
	}
	void IncrementTotalPosts()
	{
		totalPosts++;
	}
	void SetSharedBy(Object* oPtr)
	{
		sharedBy = oPtr;
	}
	void SetLikedBy(Object* oPtr)
	{
		if (!likedBy)
			likedBy = new Object * [11];
		likedBy[oIdx] = oPtr;
		oIdx++;
		likedBy[oIdx] = nullptr;
	}
	void SetComments(Comment* cPtr)
	{
		comments[cIdx] = cPtr;
		cIdx++;
		comments[cIdx] = nullptr;
	}
	void PrintLikedBy()
	{
		for (int i = 0; likedBy[i] != 0; i++)
		{
			cout << likedBy[i]->GetObjectId() << " - ";
			likedBy[i]->PrintName();
			cout << endl;
		}
	}
	/// <summary>
	/// Returns the number of posts
	/// </summary>
	/// <returns>total number of posts</returns>
	static int GetTotalPosts()
	{
		return totalPosts;
	}
	/// <summary>
	/// Returns the ID of page
	/// </summary>
	/// <returns>Page ID</returns>
	const char* GetPostId()
	{
		return id;
	}
	/// <summary>
	/// Returns the text of page
	/// </summary>
	/// <returns>Text of Page</returns>
	char* GetText()
	{
		return text;
	}
	/// <summary>
	/// Returns the array of objects that liked the post
	/// </summary>
	/// <returns>Array of Objects</returns>
	Object** GetLikedBy()
	{
		return likedBy;
	}
	Object* GetSharedBy()
	{
		return sharedBy;
	}
	Comment** GetComments()
	{
		return comments;
	}
	Date GetSharedDate()
	{
		return sharedDate;
	}
	Activity* GetActivity()
	{
		return activity;
	}
	void ReadPostFromFile(ifstream& fin)
	{
		int isActivity = 0;
		fin >> isActivity;
		char temp[80] = "\0";
		fin >> temp;
		id = Helper::GetStringFromBuffer(temp);
		sharedDate.ReadDataFromFile(fin);
		fin.getline(temp, 80);
		fin.getline(temp, 80);
		text = Helper::GetStringFromBuffer(temp);
		if (isActivity == 2)
		{
			activity = new Activity;
			activity->ReadDataFromFile(fin);
		}
	}
	virtual void PrintPost(bool showDate, bool showComm)
	{
		cout << "---";
		sharedBy->PrintName();
		if (activity != 0)
		{
			cout << " is " << activity->GetType() << activity->GetValue() << endl;
			cout << "   " << "\"" << text << "\"...";
		}
		else
		{
			cout << " shared " << "\"" << text << "\"...";
		}
		if (showDate == 1)
		{
			cout << "(";
			sharedDate.PrintDate();
			cout << ")";
		}
		cout << endl;
		if (showComm == 1)
		{
			for (int i = 0; comments[i] != nullptr; i++)
			{
				cout << "\t\t";
				comments[i]->PrintComment();
			}
		}
		cout << endl;
	}
	~Post()
	{
		delete[]id;
		delete[]text;
		Deallocate2DArray(comments);
		if (activity)
			delete[]activity;
		if (likedBy)
			delete[]likedBy;
	}
};
int Post::totalPosts = 0;

class Memory :public Post
{
	Post* shareAsMemory;
public:
	Memory(Object* currUser, Post* postPtr, char* text) :Post(currUser, "post13", text)
	{
		shareAsMemory = postPtr;
	}
	void PrintPost(bool showDate, bool showComm)
	{
		Activity* activity = shareAsMemory->GetActivity();
		char* postText = shareAsMemory->GetText();
		char* memoryText = GetText();
		Object* sharedBy = shareAsMemory->GetSharedBy();
		Date currDate = GetSharedDate();
		cout << "~~~";
		sharedBy->PrintName();
		cout << " shared a memory~~~";
		cout << "...(";
		currDate.PrintDate();
		cout << ")";
		cout << endl;
		cout << "\"" << memoryText << "\"" << endl;
		cout << "                     (2 Years Ago)                    " << endl;
		shareAsMemory->PrintPost(1, 0);

	}
	~Memory()
	{
	}
};
class Page :public Object
{
	char* title;
	static int totalPages;
	Post** timeline;
	int tlIdx;
public:
	/// <summary>
	/// Returns the number of pages
	/// </summary>
	/// <returns>total number of pages</returns>
	static int GetTotalPages()
	{
		return totalPages;
	}
	/// <summary>
	/// Sets the number of pages equal to the pages passed
	/// </summary>
	/// <param name="p">Number of pages passed</param>
	static void SetTotalPages(int p)
	{
		totalPages = p;
	}
	/// <summary>
	/// Creates an object with default values
	/// </summary>
	Page(char* i = 0) :Object(i)
	{
		title = 0;
		timeline = new Post * [11];
		timeline[0] = nullptr;
		tlIdx = 0;
	}
	/// <summary>
	/// Deallocates memory in object
	/// </summary>
	~Page()
	{
		if (title)
			delete[]title;
		Deallocate2DArray(timeline);
		totalPages--;
	}
	/// <summary>
	/// Returns the ID of page
	/// </summary>
	/// <returns>Page ID</returns>
	char* GetPageId()
	{
		char* id = GetObjectId();
		return id;
	}
	/// <summary>
	/// Returns the title of pages
	/// </summary>
	/// <returns>Page Title</returns>
	char* GetPageTitle()
	{
		return title;
	}
	void PrintName()
	{
		cout << title;
	}
	/// <summary>
	/// Takes a file and inputs data from it
	/// </summary>
	/// <param name="fin">Input file stream</param>
	void ReadDataFromFile(ifstream& fin)
	{
		char temp[50];
		fin >> temp;
		char* id = Helper::GetStringFromBuffer(temp);
		SetObjectId(id);
		fin.ignore();
		fin.getline(temp, 50);
		title = Helper::GetStringFromBuffer(temp);
	}
	/// <summary>
	/// Assigns values of an object to a previously created object
	/// </summary>
	/// <param name="rhs">Object whose values have to be assigned</param>
	/// <returns>Object with modified values</returns>
	const Page& operator=(const Page& rhs)
	{
		if (&rhs != this)
		{
			if (title)
				delete[]title;
			title = Helper::GetStringFromBuffer(rhs.title);
		}
		return *this;
	}
	void AddPostToTimeline(Post* pPtr)
	{
		timeline[tlIdx] = pPtr;
		tlIdx++;
		timeline[tlIdx] = nullptr;
	}
	void ViewTimeLine(bool check)
	{
		if (check == 0)
		{
			for (int i = 0; timeline[i] != 0; i++)
			{
				Date sharedDate = timeline[i]->GetSharedDate();
				Date currDate = Date::GetCurrDate();
				if ((sharedDate.GetDay() == currDate.GetDay() || sharedDate.GetDay() == currDate.GetDay() - 1) && (sharedDate.GetMonth() == currDate.GetMonth()) && (sharedDate.GetYear() == currDate.GetYear()))
				{
					timeline[i]->PrintPost(check, 1);
				}
			}
		}
		else
		{
			PrintName();
			cout << endl;
			for (int i = 0; timeline[i] != 0; i++)
			{
				timeline[i]->PrintPost(check, 1);
			}
		}
	}
};
int Page::totalPages = 0;

class User :public Object
{
	char* fName;
	char* lName;
	static int totalUsers;
	User** friendList;
	Page** likedPages;
	Post** timeline;
	int tlIdx;
	Memory* memories;
public:
	/// <summary>
	/// Creates an object with default values
	/// </summary>
	User(char* i = 0) :Object(i)
	{
		fName = lName = 0;
		friendList = new User * [11];
		likedPages = new Page * [11];
		timeline = new Post * [11];
		timeline[0] = 0;
		tlIdx = 0;
		memories = 0;
	}
	/// <summary>
	/// Deallocates memory in object
	/// </summary>
	~User()
	{
		if (fName)
			delete[]fName;
		if (lName)
			delete[]lName;
		delete[]friendList;
		delete[]likedPages;
		Deallocate2DArray(timeline);
	}
	/// <summary>
	/// Returns the first name of user
	/// </summary>
	/// <returns>First Name</returns>
	char* GetFName()
	{
		return fName;
	}
	/// <summary>
	/// Returns the last name of user
	/// </summary>
	/// <returns>Last Name</returns>
	char* GetLName()
	{
		return lName;
	}
	/// <summary>
	/// Displays the details of the pages liked by the user as output
	/// </summary>
	void ViewLikedPages()
	{
		cout << *this << " - " << "Liked Pages" << endl << endl;
		for (int i = 0; likedPages[i] != 0; i++)
		{
			cout << likedPages[i]->GetPageId() << " - " << likedPages[i]->GetPageTitle() << endl;
		}
	}
	/// <summary>
	/// Returns the ID of user
	/// </summary>
	/// <returns>User ID</returns>
	char* GetUserId()
	{
		char* id = GetObjectId();
		return id;
	}
	/// <summary>
	/// takes the index of array of liked pages and gives it a sets it to equal to passed value
	/// </summary>
	/// <param name="temp">Passed pointer to page</param>
	/// <param name="idx">Index of array of liked pages</param>
	void SetLikedPages(Page* temp, int idx)
	{
		likedPages[idx] = temp;
	}
	/// <summary>
	/// takes the index of friend list and gives it a sets it to equal to passed value
	/// </summary>
	/// <param name="temp">Passed pointer to user</param>
	/// <param name="idx">Index of friend list</param>
	void SetFriendList(User* temp, int idx)
	{
		friendList[idx] = temp;
	}
	/// <summary>
	/// Sets total users equal to passed number of users
	/// </summary>
	/// <param name="u">Passed Users</param>
	static void SetTotalUsers(int u)
	{
		totalUsers = u;
	}
	/// <summary>
	/// Returns the total number of users
	/// </summary>
	/// <returns>total number of users</returns>
	static int GetTotalUsers()
	{
		return totalUsers;
	}
	void PrintName()
	{
		cout << fName << " " << lName;
	}
	/// <summary>
	/// Assigns values of an object to a previously created object
	/// </summary>
	/// <param name="rhs">Object whose values have to be assigned</param>
	/// <returns>Object with modified values</returns>
	const User& operator=(const User& rhs)
	{
		if (&rhs != this)
		{
			if (fName)
				delete[]fName;
			fName = Helper::GetStringFromBuffer(rhs.fName);
			if (lName)
				delete[]lName;
			lName = Helper::GetStringFromBuffer(rhs.lName);
			friendList = rhs.friendList;
			likedPages = rhs.likedPages;
		}
		return *this;
	}
	/// <summary>
	/// Takes a file and inputs data from it
	/// </summary>
	/// <param name="fin">Input file stream</param>
	void ReadDataFromFile(ifstream& fin)
	{
		int total = totalUsers;
		char temp[50];
		fin >> temp;
		char* id = Helper::GetStringFromBuffer(temp);
		SetObjectId(id);
		fin >> temp;
		fName = Helper::GetStringFromBuffer(temp);
		fin >> temp;
		lName = Helper::GetStringFromBuffer(temp);
	}
	/// <summary>
	/// Displays the details of the friends of the user as output
	/// </summary>
	void ViewFriendList()
	{
		cout << *this << " - " << "Friend List" << endl << endl;
		for (int i = 0; friendList[i] != 0; i++)
		{
			cout << friendList[i]->GetObjectId() << " - " << *friendList[i] << endl;
		}
	}
	void AddPostToTimeline(Post* pPtr)
	{
		timeline[tlIdx] = pPtr;
		tlIdx++;
		timeline[tlIdx] = nullptr;
	}
	void ViewTimeLine(bool check)
	{
		if (check == 0)
		{
			for (int i = 0; timeline[i] != 0; i++)
			{
				Date sharedDate = timeline[i]->GetSharedDate();
				Date currDate = Date::GetCurrDate();
				if ((sharedDate.GetDay() == currDate.GetDay() || sharedDate.GetDay() == currDate.GetDay() - 1) && (sharedDate.GetMonth() == currDate.GetMonth()) && (sharedDate.GetYear() == currDate.GetYear()))
				{
					timeline[i]->PrintPost(check, 1);
				}
			}
		}
		else
		{
			cout << *this << " - " << "Time Line" << endl << endl;
			for (int i = 0; timeline[i] != 0; i++)
			{
				timeline[i]->PrintPost(check, 1);
			}
		}
	}
	void ViewHomePage()
	{
		cout << *this << " - " << "Home Page" << endl << endl;
		for (int i = 0; friendList[i] != nullptr; i++)
		{
			friendList[i]->ViewTimeLine(0);
		}
		for (int i = 0; likedPages[i] != nullptr; i++)
		{
			likedPages[i]->ViewTimeLine(0);
		}
	}
	void SeeYourMemories()
	{
		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago." << endl << endl;
		cout << "On this Day" << endl;
		int prevYears = 2;
		cout << prevYears << " Years Ago" << endl;
		Date currDate = Date::GetCurrDate();
		for (int i = 0; timeline[i] != 0; i++)
		{
			Date sharedDate = timeline[i]->GetSharedDate();
			if ((sharedDate.GetDay() == currDate.GetDay()) && (sharedDate.GetMonth() == currDate.GetMonth()) && (sharedDate.GetYear() == currDate.GetYear() - prevYears))
			{
				timeline[i]->PrintPost(1, 1);
			}
		}

	}
	void ShareMemory(Post* postPtr, char* text)
	{
		postPtr->IncrementTotalPosts();
		memories = new Memory(this, postPtr, text);
		AddPostToTimeline(memories);
	}
	friend ostream& operator<<(ostream&, const User&);
};
int User::totalUsers = 0;

/// <summary>
/// Gives output of the values in an object
/// </summary>
/// <param name="out">ostream variable</param>
/// <param name="obj">Object passed</param>
/// <returns>Output stream</returns>
ostream& operator<<(ostream& out, const User& obj)
{
	out << obj.fName << " " << obj.lName;
	return out;
}

class Facebook
{
	Page** pages;
	User** users;
	Post** posts;
	Comment** comments;
	char*** friendIds;

public:
	/// <summary>
	/// Creates an object with default values
	/// </summary>
	Facebook()
	{
		pages = NULL;
		users = NULL;
		friendIds = 0;
		posts = NULL;
		comments = NULL;
	}
	/// <summary>
	/// Deallocates memory in object
	/// </summary>
	~Facebook()
	{
		Deallocate2DArray(users);
		Deallocate2DArray(pages);
		delete[]posts;
		delete[]comments;
	}
	/// <summary>
	/// Takes the names of files and opens them to read data
	/// </summary>
	/// <param name="fileName1">Name of page file</param>
	/// <param name="fileName2">Name of user file</param>
	void LoadData(const char* fileName1, const char* fileName2, const char* fileName3, const char* fileName4)
	{
		ifstream pageFile;
		pageFile.open(fileName1);
		if (pageFile.is_open())
		{
			this->LoadPages(pageFile);
			pageFile.close();
		}
		ifstream userFile;
		userFile.open(fileName2);
		if (userFile.is_open())
		{
			this->LoadUsers(userFile);
			userFile.close();
		}
		int total = User::GetTotalUsers();
		User* uPtr = 0;
		for (int i = 0; i < total; i++)
		{
			int j = 0;
			{
				for (j = 0; friendIds[i][j] != nullptr; j++)
				{
					uPtr = SearchUserByID(friendIds[i][j]);
					users[i]->SetFriendList(uPtr, j);
				}
			}
		}
		delete[]uPtr; //deallocating pointer to user
		for (int i = 0; i < total; i++) //deallocating temporary array of user IDs
		{
			for (int j = 0; friendIds[i][j] != nullptr; j++)
			{
				delete[]friendIds[i][j];
			}
			delete[]friendIds[i];
		}
		delete[]friendIds;
		ifstream postFile;
		postFile.open(fileName3);
		if (postFile.is_open())
		{
			this->LoadPosts(postFile);
			postFile.close();
		}
		ifstream commFile;
		commFile.open(fileName4);
		if (commFile.is_open())
		{
			this->LoadComments(commFile);
			commFile.close();
		}

	}
	/// <summary>
	/// Takes a file and inputs data from it into the array of pages
	/// </summary>
	/// <param name="fin">Input file stream</param>
	void LoadPages(ifstream& fin)
	{
		int total;
		fin >> total;
		int size = total + 1;
		Page::SetTotalPages(total);
		pages = new Page * [size];
		for (int i = 0; i < size - 1; i++)
		{
			pages[i] = new Page;
			pages[i]->ReadDataFromFile(fin);
		}
		pages[size - 1] = 0;
	}
	/// <summary>
	/// Takes a file and inputs data from it into the array of users
	/// </summary>
	/// <param name="fin">Input file stream</param>
	void LoadUsers(ifstream& fin)
	{
		int total;
		fin >> total;
		int size = total + 1;
		User::SetTotalUsers(total);
		users = new User * [size];
		friendIds = new char** [total];
		for (int i = 0; i < total; i++)
		{
			users[i] = new User;
			users[i]->ReadDataFromFile(fin);
			int j = 0;
			int k = 0;
			Page* pPtr = 0;
			int pCount = 0;
			char** pageIds = 0;
			char temp[50] = "\0";
			friendIds[i] = new char* [11];
			pageIds = new char* [11];
			while (temp != "-1")
			{
				fin >> temp;
				friendIds[i][j] = Helper::GetStringFromBuffer(temp);
				if ((friendIds[i][j][0] == '-') && (friendIds[i][j][1] == '1'))
				{
					j++;
					break;
				}
				j++;
			}
			friendIds[i][j] = nullptr;
			temp[0] = '\0';
			while (temp != "-1")
			{
				fin >> temp;
				pageIds[k] = Helper::GetStringFromBuffer(temp);
				if ((pageIds[k][0] == '-') && (pageIds[k][1] == '1'))
				{
					pPtr = SearchPageByID(pageIds[k]);
					users[i]->SetLikedPages(pPtr, pCount);
					k++;
					break;
				}
				pPtr = SearchPageByID(pageIds[k]);
				users[i]->SetLikedPages(pPtr, pCount);

				pCount++;
				k++;
			}
			delete[]pPtr; //deallocating pointer to page
			pageIds[k] = nullptr;
			for (int i = 0; pageIds[i] != nullptr; i++)
			{
				delete[]pageIds[i];
			}
			delete[]pageIds;
		}
		users[size - 1] = 0;
	}
	/// <summary>
	/// Takes a file and inputs data from it into the array of posts
	/// </summary>
	/// <param name="fin">Input file stream</param>
	void LoadPosts(ifstream& fin)
	{
		int total = 0;
		char temp[50] = "\0";
		Object* oPtr = 0;
		Object** oArray = 0;
		char* likedBy = 0;
		char* sharedBy = 0;
		fin >> total;
		int size = total + 1;
		posts = new Post * [size];
		Post::SetTotalPosts(total);
		for (int i = 0; i < size - 1; i++)
		{
			posts[i] = new Post;
			posts[i]->ReadPostFromFile(fin);
			fin >> temp;
			sharedBy = Helper::GetStringFromBuffer(temp);
			oPtr = SearchObjectByID(sharedBy);
			posts[i]->SetSharedBy(oPtr);
			int j = 0;
			oArray = new Object * [11];
			while (temp != "-1")
			{
				fin >> temp;
				likedBy = Helper::GetStringFromBuffer(temp);
				if ((likedBy[0] == '-') && (likedBy[1] == '1'))
				{
					break;
				}
				oArray[j] = SearchObjectByID(likedBy);
				posts[i]->SetLikedBy(oArray[j]);
				j++;
			}
			oPtr->AddPostToTimeline(posts[i]);
		}
		posts[size - 1] = 0;
	}
	/// <summary>
	/// Takes a file and inputs data from it into the array of comments
	/// </summary>
	/// <param name="fin">Input file stream</param>
	void LoadComments(ifstream& fin)
	{
		int total = 0;
		char temp[80] = "\0";
		char* commentOn = 0;
		char* commentBy = 0;
		char* text = 0;
		char* id = 0;
		Post* postPtr = 0;
		Object* oPtr = 0;
		fin >> total;
		Comment::SetTotalComments(total);
		int size = total + 1;
		comments = new Comment * [size];
		for (int i = 0; i < size - 1; i++)
		{
			comments[i] = new Comment;
			fin >> temp;
			id = Helper::GetStringFromBuffer(temp);
			comments[i]->SetCommentId(id);
			fin >> temp;
			commentOn = Helper::GetStringFromBuffer(temp);
			postPtr = SearchPostByID(commentOn);
			fin >> temp;
			commentBy = Helper::GetStringFromBuffer(temp);
			oPtr = SearchObjectByID(commentBy);
			comments[i]->SetCommentBy(oPtr);
			fin.ignore();
			fin.getline(temp, 80);
			text = Helper::GetStringFromBuffer(temp);
			comments[i]->SetCommentText(text);
			postPtr->SetComments(comments[i]);
		}
	}
	/// <summary>
	/// Takes a user ID and serches through the array of users
	/// </summary>
	/// <param name="uId">ID of user passed</param>
	/// <returns>Pointer to user or null</returns>
	User* SearchUserByID(const char* uId)
	{
		int total = User::GetTotalUsers();
		for (int i = 0; i < total; i++)
		{
			if (Helper::CompareString(users[i]->GetUserId(), uId) == 0)
				return users[i];
		}
		return 0;
	}
	/// <summary>
	/// Takes a page ID and serches through the array of pages
	/// </summary>
	/// <param name="pId">ID of page passed</param>
	/// <returns>Pointer to page or null</returns>
	Page* SearchPageByID(char* pageId)
	{
		int total = Page::GetTotalPages();
		for (int i = 0; i < total; i++)
		{
			if (Helper::CompareString(pages[i]->GetPageId(), pageId) == 0)
				return pages[i];
		}
		return 0;
	}
	/// <summary>
	/// Takes a post ID and serches through the array of posts
	/// </summary>
	/// <param name="poId">ID of post passed</param>
	/// <returns>Pointer to post or null</returns>
	Post* SearchPostByID(char* postId)
	{
		int total = Post::GetTotalPosts();
		for (int i = 0; i < total; i++)
		{
			if (Helper::CompareString(posts[i]->GetPostId(), postId) == 0)
				return posts[i];
		}
		return 0;
	}
	/// <summary>
	/// Takes an object ID and serches through the array of objects
	/// </summary>
	/// <param name="objId">ID of post passed</param>
	/// <returns>Pointer to object or null</returns>
	Object* SearchObjectByID(char* objId)
	{
		Object* oPtr = 0;
		if (objId[0] == 'u')
		{
			oPtr = SearchUserByID(objId);
		}
		else
		{
			oPtr = SearchPageByID(objId);
		}
		return oPtr;

	}
	void ViewLikedList(const char* postId)
	{
		for (int i = 0; posts[i] != 0; i++)
		{
			if (Helper::CompareString(posts[i]->GetPostId(), postId) == 0)
			{
				posts[i]->PrintLikedBy();
			}
		}
	}
	void LikePost(const char* postId, User* currUser)
	{
		for (int i = 0; posts[i] != 0; i++)
		{
			int j = 0;
			if (Helper::CompareString(posts[i]->GetPostId(), postId) == 0)
			{
				Object* oPtr = currUser;
				posts[i]->SetLikedBy(oPtr);
			}
		}
	}
	void PostComment(const char* postId, User* currUser, char* text)
	{
		for (int i = 0; posts[i] != 0; i++)
		{
			int j = 0;
			if (Helper::CompareString(posts[i]->GetPostId(), postId) == 0)
			{
				Comment** comments = posts[i]->GetComments();
				while (comments[j] != 0)
				{
					j++;
				}
				comments[j] = new Comment;
				int commNumber = Comment::GetTotalComments();
				char letter[] = "c";
				char* id = Helper::GetStringFromBuffer(letter);
				string temp = std::to_string(commNumber);
				char const* num = temp.c_str();
				Helper::StringConcatenate(id, num);
				comments[j]->SetCommentId(id);
				comments[j]->SetCommentBy(currUser);
				comments[j]->SetCommentText(text);
				comments[j]->IncrementTotalComments();
				comments[j + 1] = 0;
				posts[i]->SetComments(comments[j]);
			}
		}
	}
	void ViewPost(const char* postId)
	{
		for (int i = 0; posts[i] != 0; i++)
		{
			if (Helper::CompareString(posts[i]->GetPostId(), postId) == 0)
			{
				posts[i]->PrintPost(1, 1);
			}
		}
	}
	/// <summary>
	/// Takes post ID and displays page
	/// </summary>
	/// <param name="pageId">Temporary Page Id</param>
	void ViewPage(char* pageId)
	{
		for (int i = 0; pages[i]; i++)
		{
			if (Helper::CompareString(pageId, pages[i]->GetPageId()) == 0)
			{
				pages[i]->ViewTimeLine(1);
			}
		}
	}
	/// <summary>
	/// Runs the functions to display output
	/// </summary>
	void Run()
	{
		int day = 15, month = 11, year = 2017;
		cout << "Command:\tSet current System Date " << day << " " << month << " " << year << endl;
		Date::SetCurrDate(day, month, year);
		Date currDate = Date::GetCurrDate();
		cout << "System Date:\t";
		currDate.PrintDate();
		cout << endl << endl;
		char userId[50] = "u7";
		cout << "Command:\tSet current user \"" << userId << "\"" << endl;
		User* currUser = SearchUserByID(userId);
		cout << *currUser << " successfully set as current user" << endl << endl;
		cout << "Command:\tView Friend List" << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		currUser->ViewFriendList();
		cout << "-----------------------------------------------------------------------" << endl << endl;
		cout << "Command:\tView Liked Pages" << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		currUser->ViewLikedPages();
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Command:\tView Home" << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		currUser->ViewHomePage();
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Command:\tView TimeLine" << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		currUser->ViewTimeLine(1);
		cout << "-----------------------------------------------------------------------" << endl;
		char postToLike[50] = "post5";
		cout << "Command:\tViewLikedList(" << postToLike << ")" << endl << endl;
		ViewLikedList(postToLike);
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Command:\tLikePost(" << postToLike << ")" << endl << endl;
		LikePost(postToLike, currUser);
		cout << "Command:\tViewLikedList(" << postToLike << ")" << endl << endl;
		ViewLikedList(postToLike);
		cout << "-----------------------------------------------------------------------" << endl;
		char commOnPost[50] = "post4";
		char commText[50] = "Good luck for your result";
		cout << "Command:\tPostComment(" << commOnPost << "," << commText << ")" << endl << endl;
		PostComment(commOnPost, currUser, commText);
		cout << "Command:\tViewPost(" << commOnPost << ")" << endl << endl;
		ViewPost(commOnPost);
		cout << "-----------------------------------------------------------------------" << endl;
		char commOnPost1[50] = "post8";
		char commText1[50] = "Thanks for the wishes";
		cout << "Command:\tPostComment(" << commOnPost1 << "," << commText1 << ")" << endl << endl;
		PostComment(commOnPost1, currUser, commText1);
		cout << "Command:\tViewPost(" << commOnPost1 << ")" << endl << endl;
		ViewPost(commOnPost1);
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Command:\tSeeYourMemories()" << endl << endl;
		currUser->SeeYourMemories();
		cout << "-----------------------------------------------------------------------" << endl;
		char postMemory[50] = "post10";
		char memoryText[80] = "Never thought I will be specialist in this field...";
		cout << "Command:\tShareMemory(" << postMemory << "," << memoryText << ")" << endl << endl;
		Post* postPtr = SearchPostByID(postMemory);
		currUser->ShareMemory(postPtr, memoryText);
		currUser->ViewTimeLine(1);
		cout << endl << "-----------------------------------------------------------------------" << endl;
		char pageId[50] = "p1";
		cout << "Command:\tViewPage(" << pageId << ")" << endl << endl;
		ViewPage(pageId);
		cout << "-----------------------------------------------------------------------" << endl;
	}
};
int main()
{
	{
		Facebook fb; //creates an object of Facebook class called fb
		fb.LoadData("Pages.txt", "Users.txt", "Posts.txt", "Comments.txt");
		fb.Run();
	}

	return 0;
}