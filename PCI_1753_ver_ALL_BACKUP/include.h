#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <thread>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <dos.h>
#include <chrono>
#include "windows.h"
#include "BDaqCtrl.h"

//������� ����������
#include "compatibility.h"
#include "bdaqctrl.h"

//
# define KolPort 2 //���������� ����������� ������
# define deviceDescription  L"PCI-1751,BID#0"
# define k 7 //��������� ��� ������� ����� � ����
#define  clc 32

//
using namespace std;
using namespace Automation::BDaq;
