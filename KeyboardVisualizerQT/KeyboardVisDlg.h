#ifndef KEYBOARDVISDLG_H
#define KEYBOARDVISDLG_H

#include "KeyboardVisualizerCommon/Visualizer.h"
#include "ui_keyboardvisualizer.h"
#include <QMainWindow>
#include <QTimer>

namespace Ui
{
    class KeyboardVisDlg;
}

class Ui::KeyboardVisDlg : public QMainWindow
{
    Q_OBJECT

public:
    explicit KeyboardVisDlg(QWidget *parent = 0);
    ~KeyboardVisDlg();

    void show();

    void SetVisualizer(Visualizer* v);
    void StartMinimized(boolean startmin);

private slots:
    void update();

    void on_lineEdit_Background_Brightness_textChanged(const QString &arg1);

    void on_lineEdit_Amplitude_textChanged(const QString &arg1);

    void on_lineEdit_Average_Size_textChanged(const QString &arg1);

    void on_lineEdit_Decay_textChanged(const QString &arg1);

    void on_lineEdit_Delay_textChanged(const QString &arg1);

    void on_lineEdit_Normalization_Offset_textChanged(const QString &arg1);

    void on_lineEdit_Normalization_Scale_textChanged(const QString &arg1);

    void on_lineEdit_Animation_Speed_textChanged(const QString &arg1);

    void on_comboBox_FFT_Window_Mode_currentIndexChanged(int index);

    void on_comboBox_Background_Mode_currentIndexChanged(int index);

    void on_comboBox_Foreground_Mode_currentIndexChanged(int index);

    void on_comboBox_Single_Color_Mode_currentIndexChanged(int index);

    void on_comboBox_Average_Mode_currentIndexChanged(int index);

    void on_pushButton_Save_Settings_clicked();

private:
    Ui::KeyboardVisualizerDlg *ui;
    QTimer* timer;
    QGraphicsScene* scene;
    QImage* image;
    QPixmap pixmap;
};
#endif // KEYBOARDVISDLG_H
