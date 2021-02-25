#include "widgetmain.h"
#include "ui_widgetmain.h"

WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMain)
{
    ui->setupUi(this);
}

WidgetMain::~WidgetMain()
{
    delete ui;
}

void WidgetMain::showEvent(QShowEvent *event)
{
    event->setAccepted(true);
}

void WidgetMain::resizeEvent(QResizeEvent *event)
{
    int genislik, yukseklik;
    QPixmap resimPixmap;

    resimPixmap.load(":/img/IMG_20191030_173910.jpg");
    genislik = ui->labelResim1->width();
    yukseklik = ui->labelResim1->height();
    ui->labelResim1->setPixmap(resimPixmap.scaled(genislik,yukseklik));

    genislik = ui->labelResim2->width();
    yukseklik = ui->labelResim2->height();
    ui->labelResim2->setPixmap(resimPixmap.scaled(genislik,yukseklik));

    event->setAccepted(true);
}

void WidgetMain::closeEvent(QCloseEvent *event)
{
    event->setAccepted(true);
}

QImage WidgetMain::doKontrast(QImage &resim, int faktor)
{
    double kontrast;
    double kirmizi, yesil, mavi;
    int pixels;
    unsigned int *data;

    kontrast = (100.0+faktor)/100.0;
    pixels = resim.width()*resim.height();
    data = (unsigned int *)resim.bits();

    //kontrast -> newColor = 128 + Kontrast *(oldColor - 128)
    for (int i = 0; i < pixels; ++i)
    {
        kirmizi= 128+ kontrast*(qRed(data[i])-128);
        kirmizi = (kirmizi < 0x00) ? 0x00 : (kirmizi > 0xff) ? 0xff : kirmizi;
        yesil= 128+ kontrast*(qGreen(data[i])-128);
        yesil = (yesil < 0x00) ? 0x00 : (yesil > 0xff) ? 0xff : yesil;
        mavi= 128+ kontrast*(qBlue(data[i])-128);
        mavi =  (mavi  < 0x00) ? 0x00 : (mavi  > 0xff) ? 0xff : mavi ;
        data[i] = qRgba(kirmizi, yesil, mavi, qAlpha(data[i]));
    }

    return resim;
}

void WidgetMain::on_btnSifirla_clicked()
{
    QImage resim;
    QPixmap resimPixmap;

    resim=ui->labelResim1->pixmap()->toImage();
    resimPixmap=QPixmap::fromImage(resim);
    ui->labelResim2->setPixmap(resimPixmap);
    ui->verticalSliderKontrast->setValue(0);
}

void WidgetMain::on_verticalSliderKontrast_valueChanged(int value)
{
    QImage resim;
    QPixmap resimPixmap;

    resim=ui->labelResim1->pixmap()->toImage();
    resim=doKontrast(resim, value);
    resimPixmap=QPixmap::fromImage(resim);
    ui->labelResim2->setPixmap(resimPixmap);
}

void WidgetMain::on_btnKaydet_clicked()
{
    QString fullName;

    fullName = QFileDialog::getSaveFileName(this, "Kaydet", "modifiedResim.jpg", "*.*");
    if (fullName=="")
    {
        return;
    }

    ui->labelResim2->pixmap()->save(fullName);
}
