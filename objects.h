#ifndef objects_H
#define objects_H


int object_count=1;



class wwidth 
{
	public:
	
		void operator=(int);
	
		int* height2;
		int* x;
		int* y;
		int width2;
	    int init(HWND hwnd,int* fake_height,int* x,int* y);
		operator int();
		HWND hwnd;
		
	
};


class hheight 
{
	public:
	
		void operator=(int);
	
		int* width2;
		int* x;
		int* y;
		int height2;
	    int init(HWND hwnd,int* fake_width,int* x,int* y);
		operator int();
		HWND hwnd;
		
	
};

class xx 
{
	public:
	
		void operator=(int);
	
		int* y2;
		int x2;

		int* width;
		int* height;

	    int init(HWND hwnd,int* fake_y,int* width, int* height);
		operator int();
		HWND hwnd;
		
	
};


class yy 
{
	public:
	
		void operator=(int);
	
		int* x2;
		int y2;
	    int init(HWND hwnd,int* fake_x,int* width, int* height);
		operator int();
		HWND hwnd;
		int* width;
		int* height;
	
};

class ccaption
{
	public:
		char* text_ref;
		int init(HWND hwnd,char* gettext,int ID);
		void operator=(char* text);
		operator char*();
		HWND hwnd;
		int id;
		~ccaption();
};


//button class
class button {
    public:
		~button();
		button(HWND hwnd);
		
		int setfont(char* fontname);
		HWND hwnd;
		HWND formhwnd;


		DWORD styles;
		char* objecttypes;
		
		int* refID;
		int id;
		char* gettext;
		xx x;
		yy y;
		ccaption caption;
		wwidth width;
		hheight height;

		void operator=(int);
	private:
		int x2;
		int y2;
		

};


class editbox
{
	public:
		~editbox();
		editbox(HWND hwnd);
		
		int setfont(char* fontname);
		HWND hwnd;
		HWND formhwnd;


		DWORD styles;
		char* objecttypes;
		
		int* refID;
		int id;
		char* gettext;
		xx x;
		yy y;
		ccaption caption;
		wwidth width;
		hheight height;

		void operator=(int);
	private:
		int x2;
		int y2;
		
};



/* Label Box */
class labelbox
{
	public:
		~labelbox();
		labelbox(HWND hwnd);
		
		int setfont(char* fontname);
		HWND hwnd;
		HWND formhwnd;


		DWORD styles;
		char* objecttypes;
		
		int* refID;
		int id;
		char* gettext;
		xx x;
		yy y;
		ccaption caption;
		wwidth width;
		hheight height;

		void operator=(int);
	private:
		int x2;
		int y2;
		
};

#include "objects.cpp"


#endif