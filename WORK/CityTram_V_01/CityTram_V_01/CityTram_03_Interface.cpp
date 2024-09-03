#include "CityTram.h"

bool checkOperationCode(int operationCode, int maxCode, int minCode)
{
	if (operationCode < minCode && operationCode > maxCode)
	{
		cout << "������� ��� ��������!" << endl;
		cin >> operationCode;
	}
	return 1;
}

void printLine(int width, char symb)
{
	cout << setw(width) << setfill(symb) << symb << endl << setfill(' ');
}

void printNewTram()
{
	cout << left;
	cout << setw(lenNumRoute) << "�" << setw(lenTramModel) << "������" << setw(lenTramCapacity) << "̳������, ���." << endl;
	printLine(lenLineMin, symb);
	cout << setw(lenNumRoute) << "1" << setw(lenTramModel) << "Tatra T3" << setw(lenTramCapacity) << 115 << endl;
	cout << setw(lenNumRoute) << "2" << setw(lenTramModel) << "K1" << setw(lenTramCapacity) << 170 << endl;
	cout << setw(lenNumRoute) << "3" << setw(lenTramModel) << "K-1M6" << setw(lenTramCapacity) << 267 << endl;
	cout << setw(lenNumRoute) << "4" << setw(lenTramModel) << "K-1T" << setw(lenTramCapacity) << 350 << endl;
}

void tramInfoBanner()
{
	cout << setw(lenTramNum) << "� ��"
		<< setw(lenTramRouteNum) << "� ��������"
		<< setw(lenTramModel) << "������"
		<< setw(lenTramCapacity) << "̳������, ���" << endl;
}

void printTramLine(tramInfo tram[], int start, int finish)
{
	for (int i = start; i < finish; i++)
	{
		cout << setw(lenTramNum) << tram[i].tramNum
			<< setw(lenTramRouteNum) << tram[i].tramRouteNum
			<< setw(lenTramModel) << tram[i].model
			<< setw(lenTramCapacity) << tram[i].capacity << endl;
	}
}

void routeInfoBanner()
{
	cout << setw(lenNumRoute) << "�"
		<< setw(lenCountTrams) << "ʳ���. ��"
		<< setw(lenTimeStart) << "��� �����"
		<< setw(lenStation) << "��������� �������"
		<< setw(lenTimeEnd) << "��� ��������"
		<< setw(lenStation) << "ʳ����� �������" << endl;
}

void printRouteLine(routeInfo route[], int start, int finish)
{
	for (int i = start; i < finish; i++)
	{
		cout << setw(lenNumRoute) << route[i].routeNum
			<< setw(lenCountTrams) << route[i].countTrams
			<< setw(lenTimeStart) << to_string(route[i].timeStartHours) + ":" + to_string(route[i].timeStartMinutes)
			<< setw(lenStation) << route[i].stationStart
			<< setw(lenTimeEnd) << to_string(route[i].timeEndHours) + ":" + to_string(route[i].timeEndMinutes)
			<< setw(lenStation) << route[i].stationEnd << endl;
	}
}

void printReportBanner()
{
	cout << setw(7) << "� ��"
		<< setw(12) << "� ��������"
		<< setw(20) << "��� �����������"
		<< setw(20) << "��� ��������" << endl;
}

void printReportLine(tramInfo tram[], routeInfo route[], int start, int finish, int routeCount)
{
	int routeNum = 0;
	for (int i = start; i < finish; i++)
	{
		if (tram[i].tramRouteNum)
		{
			routeNum = findRouteIndex(route, tram[i].tramRouteNum, routeCount);
			cout << setw(7) << tram[i].tramNum
				<< setw(12) << tram[i].tramRouteNum
				<< setw(20) << to_string(route[routeNum].timeStartHours) + ":" + to_string(route[routeNum].timeStartMinutes)
				<< setw(20) << to_string(route[routeNum].timeEndHours) + ":" + to_string(route[routeNum].timeEndMinutes) << endl;
		}
	}
}