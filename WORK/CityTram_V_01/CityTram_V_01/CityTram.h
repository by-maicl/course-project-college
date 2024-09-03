//======================================================
// Заголовний файл CityTram.h
//======================================================
#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <fstream>
using namespace std;

struct tramInfo {
	int tramNum;
	int tramRouteNum;
	string model;
	int capacity;
};

struct routeInfo {
	int routeNum;
	int countTrams;
	int timeStartHours;
	int timeStartMinutes;
	string stationStart;
	int timeEndHours;
	int timeEndMinutes;
	string stationEnd;
	int lengthRoute;
};

const unsigned int lenLineMax = 80, lenLineMin = 50;
const unsigned int lenNumRoute = 3, lenCountTrams = 10, lenTimeStart = 13, lenStation = 20, lenTimeEnd = 13;
const unsigned int lenAddRoute = 30;
const unsigned int lenTramNum = 7, lenTramRouteNum = 13, lenTramModel = 12, lenTramCapacity = 10;
const unsigned int lenAddTram = 15;
const unsigned int countTimeElement = 2;
const char symb = '-';
const string nameProject = "| Автоматизована інформаційно-пошукова система \"Міський трамвай\" |";
const string RoutesFileName = "Routes.txt", TramsFileName = "Trams.txt";
const int maxNumberRecords = 100;

//======================================================
// Прототипи функцій
//======================================================
bool checkOperationCode(int operationCode, int maxCode, int minCode = 0);
void printLine(int width = lenLineMax, char symb = '=');
void printNewTram();
void tramInfoBanner();
void routeInfoBanner();
void printRouteLine(routeInfo route[], int start, int finish);
void printTramLine(tramInfo tram[], int start, int finish);
void printReportBanner();
void printReportLine(tramInfo tram[], routeInfo route[], int start, int finish, int routeCount);

bool addNewTram(tramInfo tram[], int i);
bool writeTram(tramInfo tram[], int n);
int readTram(tramInfo tram[]);
bool deleteTram(tramInfo tram[], int tramCount, int numTram);
int findTramIndex(tramInfo tram[], int searchTramNum, int count);
int findRouteIndex(routeInfo route[], int searchRouteNum, int count);
bool bindTramToRoute(tramInfo tram[], routeInfo route[], int tramIndex, int routeIndex, int routeCount);
bool addOrUpdRoute(routeInfo route[], int i, int newRoute = 1);
bool writeRoute(routeInfo route[], int n);
int readRoute(routeInfo route[]);
int* calcRouteTimeEnd(int lengthRoute, int timeStartHours, int timeStartMinutes, int TimeEnd[]);
int* breakRouteTime(string timeString, int Time[]);
bool deleteRoute(routeInfo route[], int routeCount, int numRoute);