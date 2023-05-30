#include <qapplication.h>
#include <qresource.h>
#include <QtGui/QtGui>
#include <QWebEngineView>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QTabWidget>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	auto* window = new QWidget;
	auto* htmlEdit = new QPlainTextEdit;
	auto* webView = new QWebEngineView;
	auto* hbox = new QHBoxLayout(window);

	hbox->addWidget(htmlEdit);
	hbox->addWidget(webView);
	htmlEdit->setMinimumSize(500,500);
	webView->setMinimumSize(500,500);

	QObject::connect(htmlEdit, &QPlainTextEdit::textChanged, [webView, htmlEdit]() {
		auto htmlCode = htmlEdit->toPlainText();
		webView->setHtml(htmlCode);
	});
	window->show();
	window->setFixedSize(1000, 500);

	return app.exec();
}