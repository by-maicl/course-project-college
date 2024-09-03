#include "CityTram.h"

bool addNewTram(tramInfo tram[], int i)
{
	int modelNum;
	cout << left;
	cout << setw(lenAddTram) << "Номер моделі" << ": ";
	cin >> modelNum;

	if (i == 0)
		tram[0].tramNum = 1001;
	else
		tram[i].tramNum = tram[i - 1].tramNum + 1;
	
	tram[i].tramRouteNum = 0;

	switch (modelNum)
	{
	case 1: 
		tram[i].model = "Tatra T3";
		tram[i].capacity = 115;
		break;
	case 2:
		tram[i].model = "К1";
		tram[i].capacity = 170;
		break;
	case 3:
		tram[i].model = "K-1M6";
		tram[i].capacity = 267;
		break;
	case 4:
		tram[i].model = "K-1T";
		tram[i].capacity = 350;
		break;
	default: cout << "Невірний номер моделі!";
		return 0;
	}

	return 1;
}

bool writeTram(tramInfo tram[], int n)
{
	ofstream TramsOut(TramsFileName);
	if (TramsOut.fail())
	{
		cout << "Помилка створення файлу!\n";
		system("pause");
		return 1;
	}
	cout << setiosflags(ios::fixed);
	cout << setprecision(0);
	for (int i = 0; i < n; i++)
	{
		TramsOut << left;
		TramsOut << setw(lenTramNum) << tram[i].tramNum;
		TramsOut << setw(lenTramRouteNum) << tram[i].tramRouteNum;
		TramsOut << setw(lenTramModel) << tram[i].model;
		TramsOut << setw(lenTramCapacity) << tram[i].capacity;
		
		if (i != n - 1) TramsOut << '\n';
	}
	TramsOut.close();
	cout << "\nФайл " << TramsFileName << " - оновленo" << endl;
	cout << "\n\tДодано записів: " << n << endl << endl;
	return 0;
	system("pause");
}

int readTram(tramInfo tram[])
{
	int num = 0, i;
	string buf;
	ifstream TramsInp(TramsFileName);
	if (TramsInp.fail())
	{
		cout << "Файл не існує!\n";
		system("pause");
		return 1;
	}
	else {
		for (i = 0; !TramsInp.eof(); i++)
		{
			int position = 0;
			getline(TramsInp, buf);

			tram[i].tramNum = stoi(&buf[position]);
			position += lenTramNum;
			tram[i].tramRouteNum = stoi(&buf[position]);
			position += lenTramRouteNum;
			tram[i].model.append(buf, position, lenTramModel);
			position += lenTramModel;
			tram[i].capacity = stoi(&buf[position]);

			/*cout << buf << endl;
			cout << tram[i].tramNum << endl
				<< tram[i].tramRouteNum << endl
				<< tram[i].model << endl
				<< tram[i].capacity << endl;
			system("pause");*/
		}
		num = i;
	}
	TramsInp.close();
	return num;
}

bool bindTramToRoute(tramInfo tram[], routeInfo route[], int tramIndex, int routeIndex, int routeCount)
{
	if (tram[tramIndex].tramRouteNum != 0)
	{
		int oldRouteIndex = findRouteIndex(route, tram[tramIndex].tramRouteNum, routeCount);
		route[oldRouteIndex].countTrams--;
	}
	tram[tramIndex].tramRouteNum = route[routeIndex].routeNum;
	route[routeIndex].countTrams++;
	return 1;
}

bool deleteTram(tramInfo tram[], int tramCount, int numTram)
{
	for (int i = numTram; i < tramCount - 1; i++)
	{
		tram[i] = tram[i + 1];
	}
	return 1;
}

bool addOrUpdRoute(routeInfo route[], int i, int newRoute)
{
	int operationCode = 0;
	enum {exit, save, repeat};
	do
	{
		system("cls");
		cout << nameProject << endl << endl;
		if (newRoute) cout << "-= Створення нового маршруту =-" << endl;
		else cout << "-= Зміна маршруту =-" << endl;
		printLine(lenLineMin, symb);
		cout << left;
		cout << setw(lenAddRoute) << "Час виїзду на маршрут (00 00)" << ": ";
		cin >> route[i].timeStartHours;
		cin >> route[i].timeStartMinutes;
		cout << setw(lenAddRoute) << "Початкову зупинку" << ": ";
		cin.ignore();
		getline(cin, route[i].stationStart);
		cout << setw(lenAddRoute) << "Кінцеву зупинку" << ": ";
		getline(cin, route[i].stationEnd);
		cout << setw(lenAddRoute) << "Довжину маршруту (у метрах)" << ": ";
		cin >> route[i].lengthRoute;

		if (newRoute) route[i].countTrams = 0;

		if (i == 0)
			route[0].routeNum = 1;
		else
			route[i].routeNum = route[i - 1].routeNum + 1;

		int TimeEnd[countTimeElement];
		calcRouteTimeEnd(route[i].lengthRoute, route[i].timeStartHours, route[i].timeStartMinutes, TimeEnd);
		route[i].timeEndHours = TimeEnd[0];
		route[i].timeEndMinutes = TimeEnd[1];

		system("cls");
		cout << nameProject << endl << endl;
		if (newRoute) cout << "-= Створення нового маршруту =-" << endl;
		else cout << "-= Зміна маршруту =-" << endl;
		printLine(lenLineMax, symb);
		routeInfoBanner();
		printLine(lenLineMax, symb);
		printRouteLine(route, i, i + 1);
		printLine(lenLineMax, symb);
		cout << "Зберегти дані?\n\n"
			<< "[1] Зберегти" << endl
			<< "[2] Повторити введення" << endl
			<< "[0] Вийти без збереження";
		cout << "\n\nВведіть код операції: ";
		cin >> operationCode;
		switch (operationCode)
		{
		case save: 
			return true;
			break;
		case repeat: break;
		case exit: 
			return false;
			break;
		default: 
			return false;
			break;
		}
	} while (operationCode == 2);
}

int* calcRouteTimeEnd(int lengthRoute, int timeStartHours, int timeStartMinutes, int TimeEnd[])
{
	int hours = timeStartHours;
	int numStops = lengthRoute / 300;
	int minutes = timeStartMinutes + (lengthRoute / 6 + numStops * 20) / 60;
	
	while (minutes > 60)
	{
		minutes -= 60;
		hours++;
	}

	TimeEnd[0] = hours;
	TimeEnd[1] = minutes;
	return TimeEnd;
}

bool writeRoute(routeInfo route[], int n)
{
	ofstream RoutesOut(RoutesFileName);
	if (RoutesOut.fail())
	{
		cout << "Помилка створення файлу!\n";
		system("pause");
		return 1;
	}
	cout << setiosflags(ios::fixed);
	cout << setprecision(0);
	for (int i = 0; i < n; i++)
	{
		RoutesOut << left;
		RoutesOut << setw(lenNumRoute) << route[i].routeNum;
		RoutesOut << setw(lenCountTrams) << route[i].countTrams;
		RoutesOut << setw(lenTimeStart) << to_string(route[i].timeStartHours) + ":" + to_string(route[i].timeStartMinutes);
		RoutesOut << setw(lenStation) << route[i].stationStart;
		RoutesOut << setw(lenTimeStart) << to_string(route[i].timeEndHours) + ":" + to_string(route[i].timeEndMinutes);
		RoutesOut << setw(lenStation) << route[i].stationEnd;
		if (i != n - 1) RoutesOut << '\n';
	}
	RoutesOut.close();
	cout << "\nФайл " << RoutesFileName << " - оновленo" << endl;
	cout << "\n\tДодано записів: " << n << endl << endl;
	return 0;
	system("pause");
}

int* breakRouteTime(string timeString, int Time[])
{
	int pos = timeString.find(':');
	Time[0] = stoi(timeString.substr(0, pos));
	Time[1] = stoi(timeString.substr(pos + 1));
	return Time;
}

int readRoute(routeInfo route[])
{
	int num = 0, i;
	string buf, timeStart, timeEnd;
	int Time[countTimeElement];
	ifstream RoutesInp(RoutesFileName);
	if (RoutesInp.fail())
	{
		cout << "Файл не існує!\n";
		system("pause");
		return 1;
	}
	else {
		for (i = 0; !RoutesInp.eof(); i++)
		{
			int position = 0;
			string timeStart, timeEnd;
			getline(RoutesInp, buf);
			route[i].routeNum = stoi(&buf[position]);
			position += lenNumRoute;
			route[i].countTrams = stoi(&buf[position]);
			position += lenCountTrams;
			timeStart.append(buf, position, lenTimeStart);
			position += lenTimeStart;
			route[i].stationStart.append(buf, position, lenStation);
			position += lenStation;
			timeEnd.append(buf, position, lenTimeEnd);
			position += lenTimeEnd;
			route[i].stationEnd.append(buf, position, lenStation);

			Time[0] = { 0 };
			Time[1] = { 0 };
			breakRouteTime(timeStart, Time);
			route[i].timeStartHours = Time[0];
			route[i].timeStartMinutes = Time[1];
			breakRouteTime(timeEnd, Time);
			route[i].timeEndHours = Time[0];
			route[i].timeEndMinutes = Time[1];

			/*cout << buf << endl;
			cout << route[i].routeNum << endl
				<< route[i].countTrams << endl
				<< route[i].timeStartHours << ":" << route[i].timeStartMinutes << endl
				<< route[i].stationStart << endl
				<< route[i].timeEndHours << ":" << route[i].timeEndMinutes << endl
				<< route[i].stationEnd << endl;
			system("pause");*/
		}
		num = i;
	}
	RoutesInp.close();
	return num;
}

bool deleteRoute(routeInfo route[], int routeCount, int numRoute)
{
	for (int i = numRoute; i < routeCount - 1; i++)
	{
		route[i] = route[i + 1];
	}
	return 1;
}

int findTramIndex(tramInfo tram[], int searchTramNum, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (tram[i].tramNum == searchTramNum)
		{
			return i;
		}
	}
	return 0;
}

int findRouteIndex(routeInfo route[], int searchRouteNum, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (route[i].routeNum == searchRouteNum)
		{
			return i;
		}
	}
	return 0;
}