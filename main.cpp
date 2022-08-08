#include <QApplication>
#include "Notepad.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	Notepad np;
	np.resize(800, 600);
	np.move(10, 5);
	np.show();
   	return app.exec();
}