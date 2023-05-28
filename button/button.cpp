#include <qapplication.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <QPaintEvent>
#include <qresource.h>
#include <qmediaplayer.h>
#include <qmediacontent.h>
#include <qpushbutton.h>
#include <qtimer.h>

class ImgButton : public QPushButton {
public:
	ImgButton() = default;
	ImgButton(QWidget* parent);
	void paintEvent(QPaintEvent* e) override;
	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;
	void keyPressEvent(QKeyEvent* e) override;
public slots:
	void setGreen();
	void setRed();
private:
	QPixmap mCurrentButtonPixmap;
	QPixmap mButtonGreenPixmap;
	QPixmap mButtonRedPixmap;
	bool isDown = false;
};

ImgButton::ImgButton(QWidget* parent) {
	setParent(parent);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	mButtonGreenPixmap = QPixmap(":/green.png");
	mButtonRedPixmap = QPixmap(":/red.png");
	mCurrentButtonPixmap = mButtonRedPixmap;
	setGeometry(mCurrentButtonPixmap.rect());
	connect(this, &QPushButton::clicked, this, &ImgButton::setGreen);
}

void ImgButton::paintEvent(QPaintEvent* e) {
	QPainter p(this);
	p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImgButton::sizeHint() const {
	return QSize(100, 100);
}

QSize ImgButton::minimumSizeHint() const {
	return sizeHint();
}

void ImgButton::keyPressEvent(QKeyEvent* e) {
	setGreen();
	update();
}

void ImgButton::setGreen() {
	mCurrentButtonPixmap = mButtonGreenPixmap;
	update();
	QTimer::singleShot(100, this, &ImgButton::setRed);
}

void ImgButton::setRed() {
	mCurrentButtonPixmap = mButtonRedPixmap;
	update();
}


int main(int argc, char** argv) {
	QResource::registerResource("/res.qrc");
	QApplication app(argc, argv);
	QWidget* window = new QWidget;
	window->setFixedSize(200, 200);
	ImgButton button(window);
	auto* player = new QMediaPlayer(window);
	bool isPlaying = false;

	QObject::connect(&button, &QPushButton::clicked, [&isPlaying, &player]() {
		if (!isPlaying) {
			player->setMedia(QUrl("qrc:/click.wav"));
			player->setVolume(75);
		}
		player->play();
	});
	button.setFixedSize(100, 100);
	button.move(50, 50);
	window->show();
	button.show();
	return app.exec();
}