#include <windows.h>
#include "objects.h"



int wwidth::init(HWND hwnd,int* fake_height,int *x,int* y)
{
	this->hwnd = hwnd;
	height2 = fake_height;
	this->x = x;
	this->y = y;
	return 0;
}
wwidth::operator int()
{
	return width2;    
}


void wwidth::operator=(int width)
{
	width2 = width;
	RECT rcClient;
	GetClientRect(hwnd, &rcClient);
	SetWindowPos(hwnd, NULL ,  *x,*y, width2,*height2, SWP_NOZORDER);
    
}


int hheight::init(HWND hwnd,int* fake_width,int* x,int* y)
{
	this->hwnd = hwnd;
	width2 = fake_width;
	this->x = x;
	this->y = y;
	return 0;
}
hheight::operator int()
{
	return height2;    
}


void hheight::operator=(int height)
{
	height2 = height;
	SetWindowPos(hwnd, NULL, *x,*y,*width2,height2 ,SWP_NOZORDER);
    
}



yy::operator int()
{
	return y2;    
}


void yy::operator=(int y)
{
	y2 = y;
	SetWindowPos(hwnd, NULL, *x2,y2 , *width, *height, SWP_NOZORDER);
	
    
}



int yy::init(HWND hwnd,int* fake_x,int* width, int* height)
{
	this->hwnd = hwnd;
	x2 = fake_x;
	this->width = width;
	this->height = height;
	return 0;
}


int xx::init(HWND hwnd,int* fake_y,int* width, int* height)
{
	this->hwnd = hwnd;
	y2 = fake_y;
	this->width = width;
	this->height = height;
	return 0;
}
xx::operator int()
{
	return x2;    
}


void xx::operator=(int x)
{
	x2 = x;
	RECT rcClient;
	GetClientRect(hwnd, &rcClient);
	SetWindowPos(hwnd, NULL, x2,*y2 ,  *width, *height, NULL);
    
}

int ccaption::init(HWND hwnd,char* gettext,int ID)
{
	text_ref = gettext;
	this->hwnd = hwnd;
	this->id = ID;
	return 0;
}

ccaption::operator char*()
{
	int txtLen = SendMessage(this->hwnd, WM_GETTEXTLENGTH, NULL, NULL);

	char*  gtext = new char[txtLen+1];


	SendMessage(hwnd, WM_GETTEXT, txtLen+1, (long) gtext);


	return gtext;
}

void ccaption::operator=(char* chgedtxt)
{

	if (text_ref != NULL) 
	{
		delete text_ref;
		text_ref=NULL;
	}

	text_ref = new char[strlen(chgedtxt)+1];

	strcpy(text_ref,chgedtxt);
	//SetDlgItemText(hwnd,id,  "test");
	SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM) text_ref);
	
	
}

ccaption::~ccaption()
{

}

/*button class functions */
button::button(HWND fhwnd)
{
	
	gettext = NULL;
	
	refID = &object_count;


	HWND hEdit;
	HFONT hf;
	hf = CreateFont(15, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "MS Sans Serif");
	hEdit = CreateWindowEx(NULL, "BUTTON", NULL, 
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 
		10, 10, 25, 17, fhwnd, (HMENU)object_count, GetModuleHandle(NULL), NULL);
	SendDlgItemMessage(fhwnd, object_count, WM_SETFONT, (WPARAM)hf, TRUE);
    this->hwnd = hEdit;
	formhwnd = fhwnd;
	x.x2=10;
	y.y2=10;
	width.width2 = 10;
	height.height2=10;
	
	x.init(this->hwnd,&y.y2,&width.width2,&height.height2);
	y.init(this->hwnd,&x.x2,&width.width2,&height.height2);
	height.init(this->hwnd,&width.width2,&x.x2,&y.y2);
	width.init(this->hwnd,&height.height2,&x.x2,&y.y2);

	x=10;
	y=10;

	width=25;
	height=17;

	caption.init(this->hwnd,gettext,object_count);
	caption = "testing";
	
	id = object_count;
	object_count++;
	
}





button::~button()
{
	if (gettext != NULL)
	{
		delete gettext;
		gettext=NULL;
	}

}

/*editbox class functions */

editbox::editbox(HWND fhwnd)
{
	
	gettext = NULL;
	
	refID = &object_count;


	HWND hEdit;
	HFONT hf;
	hf = CreateFont(15, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "MS Sans Serif");
	hEdit = CreateWindowEx(WS_EX_TRANSPARENT, "EDIT", NULL, 
		SS_NOTIFY|WS_CHILD | WS_VISIBLE | EM_SETWORDBREAKPROC, 
		10, 10, 25, 17, fhwnd, (HMENU)object_count, GetModuleHandle(NULL), NULL);
	SendDlgItemMessage(fhwnd, object_count, WM_SETFONT, (WPARAM)hf, TRUE);
    this->hwnd = hEdit;
	formhwnd = fhwnd;
	x.x2=10;
	y.y2=10;
	width.width2 = 10;
	height.height2=10;
	
	x.init(this->hwnd,&y.y2,&width.width2,&height.height2);
	y.init(this->hwnd,&x.x2,&width.width2,&height.height2);
	height.init(this->hwnd,&width.width2,&x.x2,&y.y2);
	width.init(this->hwnd,&height.height2,&x.x2,&y.y2);

	x=10;
	y=10;

	width=25;
	height=17;

	caption.init(this->hwnd,gettext,object_count);
	caption = "testing";
	
	id = object_count;
	object_count++;
	
}


editbox::~editbox()
{
	if (gettext != NULL)
	{
		delete gettext;
		gettext=NULL;
	}

}

/* LabelBox */

labelbox::labelbox(HWND fhwnd)
{
	
	gettext = NULL;
	
	refID = &object_count;


	HWND hEdit;
	HFONT hf;
	hf = CreateFont(15, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "MS Sans Serif");
	hEdit = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", NULL, 
		SS_NOTIFY|WS_CHILD | WS_VISIBLE | WS_EX_TRANSPARENT, 
		10, 10, 25, 17, fhwnd, (HMENU)object_count, GetModuleHandle(NULL), NULL);
	SendDlgItemMessage(fhwnd, object_count, WM_SETFONT, (WPARAM)hf, TRUE);
    this->hwnd = hEdit;
	formhwnd = fhwnd;
	x.x2=10;
	y.y2=10;
	width.width2 = 10;
	height.height2=10;
	
	x.init(this->hwnd,&y.y2,&width.width2,&height.height2);
	y.init(this->hwnd,&x.x2,&width.width2,&height.height2);
	height.init(this->hwnd,&width.width2,&x.x2,&y.y2);
	width.init(this->hwnd,&height.height2,&x.x2,&y.y2);

	x=10;
	y=10;

	width=25;
	height=17;

	caption.init(this->hwnd,gettext,object_count);
	caption = "testing";
	
	id = object_count;
	object_count++;
	
}


labelbox::~labelbox()
{
	if (gettext != NULL)
	{
		delete gettext;
		gettext=NULL;
	}

}
