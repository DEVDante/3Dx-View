#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include "Library.h"//

int main(int argc, char *argv[])
{
	/*QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();*/
	Library test();
	int tab[] = { 1,2,3,4,5 };
	vector<int>vektor(5);
	copy(&tab[0], &tab[4], vektor.begin());

	return 0;
}
