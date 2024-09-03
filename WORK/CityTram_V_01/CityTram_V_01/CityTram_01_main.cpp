#include "CityTram.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int mainOperationCode = 0,
		operationCode = 0,
		modelNumNewTram = 0,
		numTram = 0,
		numRouteChange = 0,
		tramIndex = 0,
		routeIndex = 0,
		numTramBind = 0, 
		routeToBind = 0, 
		numTramDelete = 0, 
		numRouteDelete = 0,
		firstReportLimit = 0,
		secondReportLimit = 0;
	string timeStart, stationStart, stationEnd;

	tramInfo tram[maxNumberRecords];
	int tramCount = readTram(tram);

	routeInfo route[maxNumberRecords];
	int routeCount = readRoute(route);

	/*int tramCount = 0;
	tramInfo tram[maxNumberRecords] = {
		{1234, 3, "Tatra T3",120}
	};*/

	/*int routeCount = 1;
	routeInfo route[maxNumberRecords] = {
		{3, 6, 34, "Північна", 0, 0, "Південна", 21000}
	};*/

	enum { exit, watchTram, watchRoutes, reportGeneration };
	do
	{
		// Головне меню
		system("cls");
		cout << nameProject << endl << endl;
		printLine();
		cout << "[1] Переглянути інформацію про трамваї" << endl
			<< "[2] Переглянути інформацію про маршрути" << endl
			<< "[3] Сформувати звітну таблицю" << endl
			<< "[0] Вийти" << endl;
		printLine();
		cout << "Введіть код операції: ";
		cin >> mainOperationCode;
		checkOperationCode(mainOperationCode, 3); // перевірка на правильність коду операції (доробити)
		system("cls");
		switch (mainOperationCode)
		{
		case watchTram:
			// Переглянути інформацію про трамваї
			system("cls");
			cout << nameProject << endl << endl;
			cout << "-= Інформація про трамваї =-" << endl;
			printLine(lenLineMin, symb);
			cout << left;
			tramInfoBanner();
			printLine(lenLineMin, symb);
			printTramLine(tram, 0, tramCount);
			printLine(lenLineMin, symb);
			cout << "[1] Додати трамвай" << endl
				<< "[2] Прив'язати трамвай до маршруту" << endl
				<< "[3] Видалити трамвай" << endl
				<< "[0] Вийти" << endl;
			cout << endl << "Введіть код операції: ";
			cin >> operationCode;
			switch (operationCode)
			{
			case 1:
				// Додати новий трамвай
				system("cls");
				cout << "-= Закупівля нових трамваїв =-" << endl;
				printLine(lenLineMin, symb);
				printNewTram();
				printLine(lenLineMin, symb);
				addNewTram(tram, tramCount);
				tramCount++;
				break;
			case 2:
				// Змінити інформацію про трамвай 
				cout << "\nВведіть номер ТЗ: ";
				cin >> numTramBind;
				tramIndex = findTramIndex(tram, numTramBind, tramCount);
				system("cls");
				cout << nameProject << endl << endl;
				cout << "-= Прив'язка трамваю до маршруту =-" << endl;
				printLine(lenLineMax, symb);
				cout << left;
				routeInfoBanner();
				printLine(lenLineMax, symb);
				printRouteLine(route, 0, routeCount);
				printLine(lenLineMax, symb);
				cout << "\nВведіть номер маршруту: ";
				cin >> routeToBind;
				routeIndex = findRouteIndex(route, routeToBind, routeCount);
				system("cls");
				cout << nameProject << endl << endl;
				cout << "-= Прив'язка трамваю до маршруту =-" << endl;
				printLine(lenLineMax, symb);
				cout << left;
				routeInfoBanner();
				printLine(lenLineMax, symb);
				printRouteLine(route, routeIndex, routeIndex + 1);
				printLine(lenLineMax, symb);
				cout << "Прив'язати трамвай № " << numTramBind << " до маршруту № " << routeToBind << "?\n\n";
				cout << "[1] Продовжити" << endl
					<< "[0] Вийти" << endl;
				cout << endl << "Введіть код операції: ";
				cin >> operationCode;
				switch (operationCode)
				{
				case 1:
					bindTramToRoute(tram, route, tramIndex, routeIndex, routeCount);
					break;
				}
				break;
			case 3:
				// Видалити трамвай
				cout << "\nВведіть номер видаляємого ТЗ: ";
				cin >> numTramDelete;
				tramIndex = findTramIndex(tram, numTramDelete, tramCount);
				system("cls");
				cout << nameProject << endl << endl;
				cout << "-= Видалення трамваю =-" << endl;
				printLine(lenLineMin, symb);
				cout << left;
				tramInfoBanner();
				printLine(lenLineMin, symb);
				printTramLine(tram, tramIndex, tramIndex + 1);
				printLine(lenLineMin, symb);
				cout << "Видалити цей трамвай?\n\n";
				cout << "[1] Продовжити" << endl
					<< "[0] Вийти" << endl;
				cout << endl << "Введіть код операції: ";
				cin >> operationCode;
				switch (operationCode)
				{
				case 1:
					if (numTramDelete > 1000 && numTramDelete <= tram[tramCount - 1].tramNum)
					{
						int routeNum = findRouteIndex(route, tram[tramIndex].tramRouteNum, routeCount);
						deleteTram(tram, tramCount, tramIndex);
						tramCount--;
						route[routeNum].countTrams--;
					}
					else {
						cout << "Неправильний номер ТЗ!";
						break;
					}
					break;
				}
				break;
			}
			break;
		case watchRoutes:
			// Переглянути інформацію про маршрути
			system("cls");
			cout << nameProject << endl << endl;
			cout << "-= Інформація про маршрути =-" << endl;
			printLine(80, symb);
			cout << left;
			routeInfoBanner();
			printLine(lenLineMax, symb);
			printRouteLine(route, 0, routeCount);
			printLine(lenLineMax, symb);
			cout << "[1] Створити новий маршрут" << endl
				<< "[2] Змінити маршрут" << endl
				<< "[3] Видалити машрут" << endl
				<< "[0] Вийти" << endl;
			cout << endl << "Введіть код операції: ";
			cin >> operationCode;
			switch (operationCode)
			{
			case 1:
				// Створити новий маршрут
				if (addOrUpdRoute(route, routeCount))
					routeCount++;
				break;
			case 2:
				// Зміна маршруту
				cout << "\nВведіть номер змінюваного маршруту: ";
				cin >> numRouteChange;
				routeIndex = findRouteIndex(route, numRouteChange, routeCount);
				if (addOrUpdRoute(route, routeIndex, 0)) break;
			case 3:
				// Видалення маршруту
				cout << "\nВведіть номер видаляємого маршруту: ";
				cin >> numRouteDelete;
				routeIndex = findRouteIndex(route, numRouteDelete, routeCount);
				system("cls");
				cout << nameProject << endl << endl;
				cout << "-= Видалення маршруту =-" << endl;
				printLine(lenLineMax, symb);
				cout << left;
				routeInfoBanner();
				printLine(lenLineMax, symb);
				printRouteLine(route, routeIndex, routeIndex + 1);
				printLine(lenLineMax, symb);
				cout << "Видалити цей маршрут?\n\n";
				cout << "[1] Продовжити" << endl
					<< "[0] Вийти" << endl;
				cout << endl << "Введіть код операції: ";
				cin >> operationCode;
				switch (operationCode)
				{
				case 1: 
					if (numRouteDelete > 0 && numRouteDelete <= routeCount)
					{
						deleteRoute(route, routeCount, routeIndex);
						routeCount--;
						for (int i = 0; i < tramCount; i++)
						{
							if (tram[i].tramRouteNum == numRouteDelete) {
								tram[i].tramRouteNum = 0;
							}
						}
					}
					else {
						cout << "Неправильний номер маршруту!";
						break;
					}
					break;
				}
				break;
			}
			break;
		case reportGeneration:
			system("cls");
			cout << nameProject << endl << endl;
			cout << "-= Звітна таблиця =-" << endl;
			cout << left;
			printLine(lenLineMax, symb);
			printReportBanner();
			printLine(lenLineMax, symb);
			printReportLine(tram, route, 0, tramCount, routeCount);
			printLine(lenLineMax, symb);
			cout << "\n[0] Вийти";
			cout << "\n\nВведіть код операції: ";
			cin >> operationCode;
			break;
		case exit:
			// Вихід і оновлення файлу
			char updateFile;
			bool errUpdate = 0;
			cout << "\nОновити файл бази даних? [Т] чи [Н]: ";
			cin >> updateFile;
			switch (updateFile)
			{
			case 'т':
			case 'Т':
				errUpdate = writeTram(tram, tramCount);
				errUpdate = writeRoute(route, routeCount);
				break;
			default:
				errUpdate = 1;
				break;
			}
		}
	} while (mainOperationCode);
	system("pause");
}