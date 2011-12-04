

#include <QtGui/QApplication>
#include <QErrorMessage>
#include "MainWindow/MainWindow.h"

int main( int argc, char * argv[] ) {
	QApplication application( argc, argv );

	// set up a message handler
	QErrorMessage::qtHandler();

	MainWindow window;

	window.resize( 900, 600 );
	window.show();

	return application.exec();
}

