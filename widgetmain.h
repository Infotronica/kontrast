#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include <QWidget>
#include <QShowEvent>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QFileDialog>

namespace Ui {
class WidgetMain;
}

class WidgetMain : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetMain(QWidget *parent = 0);
    ~WidgetMain();

    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *ev);
    void closeEvent(QCloseEvent *event);
    QImage doKontrast(QImage &resim, int faktor);

private slots:
    void on_btnSifirla_clicked();

    void on_verticalSliderKontrast_valueChanged(int value);

    void on_btnKaydet_clicked();

private:
    Ui::WidgetMain *ui;
};

#endif // WIDGETMAIN_H
