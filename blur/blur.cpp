#include <QtGui/QtGui>
#include <QApplication>
#include <QtConcurrent/QtConcurrent>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QSlider>
#include <QVBoxLayout>
#include <QResource>

QImage blurImage(QImage source, int radius) {
	if (source.isNull()) return QImage();
	QGraphicsScene scene;
	QGraphicsPixmapItem item;
	item.setPixmap(QPixmap::fromImage(source));
	auto* blur = new QGraphicsBlurEffect;
	blur->setBlurRadius(radius);
	item.setGraphicsEffect(blur);
	scene.addItem(&item);
	QImage result(source.size(), QImage::Format_ARGB32);
	result.fill(Qt::transparent);
	QPainter painter(&result);
	scene.render(&painter, QRectF(), QRectF(0, 0, source.width(), source.height()));
	return result;
}

int main(int argc, char **argv) {
	QResource::registerResource("/img.qrc");
	QApplication app(argc, argv);
	QWidget window;
	QVBoxLayout vbox(&window);
	auto* slider = new QSlider(&window);
	auto* openFile = new QPushButton("OPEN", &window);
	auto* image = new QLabel(&window);
	image->setMinimumSize(500, 500);
	image->move(250,250);
	slider->setOrientation(Qt::Horizontal);
	slider->setMinimum(0);
	slider->setMaximum(8);
	vbox.addWidget(image);
	vbox.addWidget(slider);
	vbox.addWidget(openFile);

	QString filePath = (":/blur_def.jpg");
	int radius;
	image->setPixmap(QPixmap::fromImage(blurImage(QImage(filePath), 0).scaled(image->width(), image->height(), Qt::KeepAspectRatio)));

	QObject::connect(openFile, &QPushButton::clicked, [&filePath, &image]() {
		filePath = QFileDialog::getOpenFileName(nullptr, "Open JPG image","*.jpg","*.jpg");
		image->setPixmap(QPixmap::fromImage(blurImage(QImage(filePath), 0).scaled(image->width(), image->height(), Qt::KeepAspectRatio)));
	});

	QObject::connect(slider, &QSlider::valueChanged, [&slider, &radius, &filePath, &image]() {
		radius = slider->value();
		image->setPixmap(QPixmap::fromImage(blurImage(QImage(filePath), radius).scaled(image->width(), image->height(), Qt::KeepAspectRatio)));
	});
		
	window.show();
		
	return app.exec();
}