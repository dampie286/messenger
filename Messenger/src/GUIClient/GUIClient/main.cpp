#include "guiclient.h"
#include <QtWidgets/QApplication>
#include<vld.h>
int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);

		GUIClient w;
		w.show();
		//w.client

	return a.exec();
}
