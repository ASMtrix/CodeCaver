#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "winvars.h"
#include "objects.h"


labelbox* lb1;
editbox* tb1;
button* b1;

labelbox* lb2;
editbox* tb2;
button* b2;

labelbox* lb3;

labelbox* lb4;
labelbox* lb5;


int setnewflesze();
int headeroffset=0;
int bytesize=0;
int PE_pos=0;
int num_of_sec=0;
DWORD filerawoffset=0;
DWORD filesizedec=0;
DWORD newfilesizedec=0;
DWORD newvsize;
int newrsize;
int entrypoint=0;


char* sec_nme;
WORD tmp[5];
BYTE filesize[8];
WORD entrypoinywrd[9];

FILE* thefile;
FILE* wfile;

WORD y=0;

int getheadersections();
bool opendb();
void Error(char* errormsg);
bool chkifnum();
int openfile();
int chkifexe();
int findPE();
int get_num_of_sec();
int binlin(int num1,int num2);
unsigned int binlin(WORD num1,WORD num2,WORD num3,WORD num4);
WORD rbinlin(int number,int pos);
int crtememspce();
int addnewsizes();
int setnewflesze();
int setnewhp();
int setnewrawsze();
int fillextra();
unsigned int getfleize();
int getentrypoint();

class Sections
{
	public:
		char* name;
		DWORD virutalsize;
		DWORD virutaloffset;
		int rawsize;
		DWORD rawoffset;
		DWORD unknown1;
		DWORD unknown2;
		DWORD unknown3;
		DWORD flags;
		int headeroffset;
		Sections();
		~Sections();
};

Sections::Sections()
{
	name = new char[10];
	virutalsize=0;
	virutaloffset=0;
	rawsize=0;
	rawoffset=0;
	unknown1=0;
	unknown2=0;
	unknown3=0;
	flags=0;
	headeroffset=0;
}

Sections::~Sections()
{
	if (name != NULL)
	{
		delete name;
		name = NULL;
		
	}
}
Sections* sections=NULL;

int WindowsMain()
{

	//}
	
    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon = LoadIcon(NULL, 0);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = ClassName;
    wc.hIconSm       = LoadIcon(NULL, 0);

   if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        NULL,
        ClassName,
        WindowTitle,
        DS_MODALFRAME+WS_POPUP+WS_SYSMENU+WS_CAPTION,
        window_x ,window_y,Width, Height,
        NULL, NULL, hInstance, NULL);

	form1hwnd = hwnd;

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, 1);
    UpdateWindow(hwnd);




    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

	return Msg.wParam;

    return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char filesizetxt[255];
	char sectionstxt[255];
	char entrypointtxt[255];

    switch(msg)
    {
		case WM_COMMAND:
		{
			if (LOWORD(wParam)==3) 
			{
				opendb();
				if (openfile() == 0) return 0;
				if (chkifexe() == 0) return 0;

				PE_pos = findPE();
				getentrypoint();
				get_num_of_sec();
				crtememspce();
				getheadersections();

				sprintf(filesizetxt,"File Size: %i",filesizedec);
				lb3->caption = filesizetxt;

				sprintf(sectionstxt,"Sections: %i",num_of_sec);
				lb4->caption = sectionstxt;

				sprintf(entrypointtxt,"Entry Point: %x%x%x%x",entrypoinywrd[3],entrypoinywrd[2],entrypoinywrd[1],entrypoinywrd[0]);
				lb5->caption = entrypointtxt;

				//sprintf(entrypointtxt,"Sections: %i",num_of_sec);
				//lb5->caption = entrypointtxt;
				
				fclose(thefile);
				break;
			}

			if (LOWORD(wParam) == 6)
			{
				if (strcmp("",tb1->caption) == 0) return 0;

				if (chkifnum() == false) return 0;

				//if (strcmp(sections[num_of_sec-1].name,".rsrc") == 0)
			//	{
					addnewsizes();

					wfile = fopen(tb1->caption, "r+b");
	
					setnewflesze();
					setnewhp();
					setnewrawsze();
					fillextra();


					fclose(wfile);



					MessageBox(NULL,"Process finshed!","blah",MB_OK);

			//	}

				if (sec_nme != NULL)
				{
					delete sec_nme;
					sec_nme=NULL;
				}
			}
			break;
		}
		case WM_CREATE:
		{
			lb1= new labelbox(hwnd);
			lb1->caption = "Filename:";
			lb1->width=50;

			tb1 = new editbox(hwnd);
			tb1->x = 60;
			tb1->width = 100;
			tb1->caption = "";

			b1 = new button(hwnd);
			b1->caption ="Broswe";
			b1->x =170;
			b1->width = 50;

			lb2 = new labelbox(hwnd);
			lb2->y = 40;
			lb2->width = 85;
			lb2->caption = "Bytes to allocate: ";


			tb2 = new editbox(hwnd);
			tb2->y = 40;
			tb2->x = 100;
			tb2->width = 30;
			tb2->caption = "";

			b2 = new button(hwnd);
			b2->caption ="Go!";
			b2->x =170;
			b2->y = 160;
			b2->width = 50;

			lb3 = new labelbox(hwnd);
			lb3->y = 80;
			lb3->width = 85;
			lb3->caption = "File size: ";

			lb4 = new labelbox(hwnd);
			lb4->y = 100;
			lb4->width = 85;
			lb4->caption = "Sections: ";

			lb5 = new labelbox(hwnd);
			lb5->y = 120;
			lb5->width = 110;
			lb5->caption = "Entry Point: ";

			break;
		}
		case WM_PAINT:
		{
			//BITMAP bm;
			PAINTSTRUCT ps;
		    HDC hdc;
		    hdc = BeginPaint(hwnd,&ps);
			EndPaint(hwnd, &ps);
		}
		break;
		case WM_CLOSE:
			

	
			DestroyWindow(hwnd);
        break;
        case WM_DESTROY:

			
			delete lb1;
			lb1 = NULL;

			delete tb1;
			tb1 = NULL;

			delete b1;
			b1 = NULL;

			delete lb2;
			lb2 = NULL;

			delete lb3;
			lb3 = NULL;

			delete lb4;
			lb4 = NULL;

		//	delete tb2;
		//	tb2 = NULL;
			if (sections != NULL)
			{
				if (sections[0].name!=NULL)
				{
					delete sections[0].name;
					sections[0].name = NULL;
				}
			}

			if (sections != NULL)
			{
				delete[] sections;
				sections = NULL;
			}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

bool opendb()
{
	OPENFILENAME ofn;

	//char* filename;

	char filename2[256];
	
	filename2[0] = '\0';

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = (HWND)NULL;
    ofn.lpstrFilter = "EXE file (*.exe)\0*.exe\0"; //modify your files extension here
    ofn.lpstrFile = filename2;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // for open file common dialog use OFN_FILEMUSTEXIST and/or OFN_HIDEREADONLY
    ofn.lpstrDefExt = "exe";
    ofn.lpstrTitle = "opening File..";

	

	if(GetOpenFileName(&ofn)) 
	{ 
		tb1->caption = filename2;
		return TRUE;
	}


	
	return false;
}

void Error(char* errormsg)
{
	MessageBox(hwnd,errormsg,"Error!",MB_OK); 
}

bool chkifnum()
{
	bytesize = atoi(tb2->caption);	
				
	if (bytesize == 0) 
	{
		Error("Please enter something larger than 0");
		return false;
	}
	return true;
}

int openfile()
{

	thefile = fopen(tb1->caption,"rb");

	if (thefile == NULL)
	{
		Error("Can't open file!"); 
		return 0;
	}
	return 1;
}

int chkifexe()
{
	fseek(thefile,0,SEEK_SET);

	char m = getc(thefile);

	fseek(thefile,1,SEEK_SET);

	char z = getc(thefile);

	if (m != 'M' && z != 'Z')
	{
		Error("Not an EXE File");
		return 0;
	}
/*
	get_num_of_sec();

	char test[255];

	sprintf(test,"%i",num_of_sec);

	MessageBox(NULL,"testing",test,MB_OK);
*/
	return 1;
}

int findPE()
{
	int filecount=0;
	char m; 

	while (!feof(thefile))
	{
		fseek(thefile,filecount,SEEK_SET);
		m = getc(thefile);
		if (m == 'P')
		{
			fseek(thefile,filecount+1,SEEK_SET);
			m = getc(thefile);
			if (m == 'E')
			{

				//MessageBox(NULL,"PE FOUND","PE FOUND!!",MB_OK);
				return filecount;
			}
		}
		filecount++;
	}

	return 0;
}

int get_num_of_sec()
{
	char s1;
	char s2;

	fseek(thefile,PE_pos+6,SEEK_SET);

	s1 = getc(thefile);

	fseek(thefile,PE_pos+7,SEEK_SET);
	
	s2 = getc(thefile);


	num_of_sec = binlin(s2,s1);

	return 0;
}

int binlin(int num1,int num2)
{
	int totalnum=0;

	totalnum = num1;
	totalnum  = totalnum << 8;
	totalnum = totalnum | num2;
	return totalnum;
}

unsigned int binlin(WORD num1,WORD num2,WORD num3,WORD num4)
{
	int totalnum=0;
	totalnum |= num4;
	totalnum <<= 8;

	totalnum &= 0xFFFF;

	totalnum |= num3;
	totalnum <<= 8;

	totalnum &= 0xFFFFFF;

	totalnum |=num2;
	totalnum <<= 8;

	totalnum &= 0xFFFFFFFF;
	totalnum |=num1;

	

	return totalnum;

}

WORD rbinlin(int number,int pos)
{
	//char rev[5];
	DWORD temp=0;
	

	switch(pos)
	{
		case 0:
		{
			return (WORD) number & 0xFF;

			break;
		}
		case 1:
		{
			temp = number & 0xFF00;
			temp >>= 8;
			temp  &=  0xFF;
			return (WORD) temp;
			break;
		}
		case 2:
		{
			temp = 0;
			temp =number & 0xFF0000;
			temp >>= 16;
			temp &=  0xFF;
			return  (WORD) temp;
			break;
		}
		case 3:
		{
			temp = 0;
			temp =  number & 0xFF000000;
			temp >>=24;
			temp &=  0xFF;
			return   (WORD) temp;
			break;
		}
	
	}




	return 0;
}

int crtememspce()
{
	if (sections != NULL)
	{
			delete[] sections;
			sections=NULL;
	}
	sections  = new Sections[num_of_sec+1];
				
	if (sec_nme != NULL)
	{
			delete sec_nme;
			sec_nme=NULL;
	}

	sec_nme = new char[10];
	return 0;
}


unsigned int getfleize()
{
	for (int byteclear=0;byteclear < 8;byteclear++)
	{
		filesize[byteclear] = '\0';
	}

	filerawoffset = PE_pos+80;

	fseek(thefile,PE_pos+80,SEEK_SET);
	filesize[0] = fgetc(thefile);

	fseek(thefile,PE_pos+81,SEEK_SET);
	filesize[1] = fgetc(thefile);

	fseek(thefile,PE_pos+82,SEEK_SET);
	filesize[2] = fgetc(thefile);

	fseek(thefile,PE_pos+83,SEEK_SET);
	filesize[3] = fgetc(thefile);

	return binlin(filesize[0],filesize[1],filesize[2],filesize[3]);
}

int getheadersections()
{
	filesizedec = getfleize();
	PE_pos+=248;

	headeroffset = PE_pos;

	fseek(thefile,PE_pos,SEEK_SET);

	for (int l=0; l < num_of_sec;l++)
	{
		sections[l].headeroffset = PE_pos;
		for (int i=0;i<8;i++)
		{
			fseek(thefile,PE_pos,SEEK_SET);
			sec_nme[i] = fgetc(thefile);
			PE_pos++;
		}
		sec_nme[7] = '\0';

		strcpy(sections[l].name,sec_nme);
		for (int tmpclear=0;tmpclear < 5;tmpclear++)
		{
			tmp[tmpclear] = '\0';
		}


		for (int k=0;k < 8; k++)
		{
			for (int j=0;j<4;j++)
			{
				fseek(thefile,PE_pos,SEEK_SET);
				tmp[j] = (WORD) fgetc(thefile);
				PE_pos++;
			}
			switch(k)
			{
				case 0:
				{
					sections[l].virutalsize = binlin(tmp[0],tmp[1],tmp[2],tmp[3]);
					break;
				}
				case 1:
				{
					sections[l].virutaloffset = binlin(tmp[0],tmp[1],tmp[2],tmp[3]);
					break;
				}
				case 2:
				{
					sections[l].rawsize = binlin(tmp[0],tmp[1],tmp[2],tmp[3]);
					break;
				}
				case 3:
				{
					sections[l].rawoffset = binlin(tmp[0],tmp[1],tmp[2],tmp[3]);
					break;
				}
				case 4:
				{
					sections[l].unknown1 = binlin(tmp[0],tmp[1],tmp[2],tmp[3]);
					break;
				}
				case 5:
				{
					sections[l].unknown2 = binlin(tmp[0],tmp[1],tmp[2],tmp[3]);
					break;
				}
				case 6:
				{
					sections[l].unknown3 = binlin(tmp[0],tmp[1],tmp[2],tmp[3]);
					break;
				}
				case 7:
				{
					sections[l].flags = binlin(tmp[0],tmp[1],tmp[2],tmp[3]);
					break;
				}
				break;
			}
						
			for (int c=0;c<4;c++)
			{
				tmp[c] = '\0';
			}
		}
	}
	return 0;
}

int addnewsizes()
{
	newfilesizedec = sections[num_of_sec-1].virutaloffset + sections[num_of_sec-1].virutalsize + atoi(tb2->caption);
	newrsize = sections[num_of_sec-1].rawsize +  atoi(tb2->caption);

	return 0;
}


int setnewflesze()
{
	//set new filesize
	fseek(wfile,filerawoffset,SEEK_SET);
	fputc(rbinlin(newfilesizedec,0),wfile);
		
	fseek(wfile,filerawoffset+1,SEEK_SET);
	fputc(rbinlin(newfilesizedec,1),thefile);
	fseek(wfile,filerawoffset+2,SEEK_SET);
	fputc(rbinlin(newfilesizedec,2),thefile);

	fseek(wfile,filerawoffset+3,SEEK_SET);
	fputc(rbinlin(newfilesizedec,3),thefile);

	return 0;
}

int setnewhp()
{
	//set the headers permissions
	fseek(wfile,sections[num_of_sec-1].headeroffset+36,SEEK_SET);
	fputc(0x60,wfile);
	fseek(wfile,sections[num_of_sec-1].headeroffset+37,SEEK_SET);
	fputc(0x00,wfile);
	fseek(wfile,sections[num_of_sec-1].headeroffset+38,SEEK_SET);
	fputc(0x00,wfile);
	fseek(wfile,sections[num_of_sec-1].headeroffset+39,SEEK_SET);
	fputc(0xE0,wfile);
	return 0;
}

int setnewrawsze()
{
					//new raw size title size + virual raw size +virual offset size
	fseek(wfile,sections[num_of_sec-1].headeroffset+8+4+4,SEEK_SET);
	y=0;
	y = (WORD) rbinlin(newrsize,0);
	y &= 0xFF;
	fputc((WORD) y & 0xFF, wfile);

	fseek(wfile,sections[num_of_sec-1].headeroffset+8+4+4+1,SEEK_SET);
	y=0;
	y = rbinlin(newrsize,1);
	y &= 0xFF;
	fputc((WORD) y, wfile);


	fseek(wfile,sections[num_of_sec-1].headeroffset+8+4+4+2,SEEK_SET);
	y=0;
	y = (WORD) rbinlin(newrsize,2);

	y &= 0xFF;
	fputc((WORD) y & 0xFF, wfile);

	fseek(wfile,sections[num_of_sec-1].headeroffset+8+4+4+3,SEEK_SET);
	y=0;
	y = (WORD) rbinlin(newrsize,3);
	y &= 0xFF;
	fputc((WORD) y & 0xFF, wfile);
	return 0;
}

int fillextra()
{
	fseek(wfile,0,SEEK_END);

	for (int m=0; m < atoi(tb2->caption);m++)
	{
			fputc(0x90,wfile);
	}
	return 0;
}

int getentrypoint()
{
	
	entrypoint = PE_pos + 40;

	for (int i=0; i < 4;i++)
	{
		fseek(thefile,entrypoint+i,SEEK_SET);
		entrypoinywrd[i] = fgetc(thefile);
	}

	return 0;
}