//�������� �������. ��������� ������������ ����� � ������. 
#include "include.h"

//������� f(x)
char READ_WRITE_INI(char INI[KolPort * 8][20], char MASKA[KolPort][9], byte MaskaHex[KolPort]);
int  PrintDisplay(char INI[KolPort * 8][20], char MASKA[KolPort][9], byte SostPort[KolPort],int sost_i[KolPort * 8]);
int  PiecewiseLinearFunction(int PortPin[2], int key);
int  IMPULS_RE(int lcnt, int key, char MASKA[KolPort][9], byte MaskaHex[KolPort]);


//���������� ����������
int		sost_i[KolPort * 8]  = { 0 };//��������� ���� �� ������
int		PortPin[2];
int		key  = 0;//������� ������
bool     lcnt = false; //���������� ���� ��� ������ ������ �� main ("������� �������� f(IMPULS_RE)").
char	INI[KolPort * 8][20] = { " " };
char	MASKA[KolPort][9]    = { " " };
byte	SostPort[KolPort]    = { 0x00 };//��������� �����
byte    MaskaHex[KolPort];//������ ����� � hex


//using
using namespace std;
using namespace Automation::BDaq;
InstantDoCtrl * instantDoCtrl = InstantDoCtrl::Create();
//
int main(int argc, char *argv[])
{
	//��������� ����������
	int			   i;//�������
	int			   sost = 0;//���������� ��� PCI
	unsigned char  bit;
	
	//
	setlocale(LC_ALL, "Rus");
	ErrorCode ret = Success;
	InstantDoCtrl * instantDoCtrl = AdxInstantDoCtrlCreate();
	DeviceInformation devInfo(deviceDescription);
	ret = instantDoCtrl->setSelectedDevice(devInfo);
	
	// ����������� ����� � ��������� ������ �� �����
	ICollection<PortDirection>* portDirection = instantDoCtrl->getPortDirection();
	if (portDirection != NULL)
	{
		//Set the first two port to output 
		DioPortDir dir = Output;
		for (i = 0; i < KolPort; i++)
		{
			portDirection->getItem(i).setDirection(dir);
		}
	}
	else
	{
		printf("����� �� ��������!\n");
	}

	//��������� ������ ��� ���������
	//for (i = 0; i < KolPort; i++)
	//{
	//	ret = instantDoCtrl->Write(i, byte(0));
	//}
	
	//while (true)
	//{
		//���������� ��������� ������
		for (i = 0; i < KolPort; i++)
		{
			ret = instantDoCtrl->Read(i, SostPort[i]);
		}

		//
		READ_WRITE_INI(INI, MASKA, MaskaHex);
		//PrintDisplay(INI, MASKA, SostPort, sost_i);

		//Switch
		//scanf("%i", &key);
		key = atoi(argv[1]);
		bit = atoi(argv[2]);
		PiecewiseLinearFunction(PortPin, key);
		if (key >= 0)
		{
			//sost = instantDoCtrl->ReadBit(PortPin[1], PortPin[0], &bit);
			if (bit == 0)
			{
				ret = instantDoCtrl->WriteBit(PortPin[1], PortPin[0], 0);
				//ret = instantDoCtrl->WriteBit(0, 0, 1);
				sost_i[key] = 1;
			}
			else if(bit == 1)
			{
				ret = instantDoCtrl->WriteBit(PortPin[1], PortPin[0], 1);
				//ret = instantDoCtrl->WriteBit(0, 0, 0);
				sost_i[key] = 0;
			}
			system("cls");
		}
		else if (key <= -10)
		{
			lcnt = !lcnt;
			thread func_thread(IMPULS_RE,lcnt, key, MASKA, MaskaHex);//����� ������� �������� ����� �����.
			func_thread.detach();// ������������� main ��� ������ ������.
			//IMPULS_RE(lcnt, key, MASKA, MaskaHex);
		}
		else return -1;
	//}

	//int a;
	//a = 0;
}