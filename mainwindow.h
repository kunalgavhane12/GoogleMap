#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWebEngineView>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onNavigate();

private:
    QLineEdit *sourceLineEdit;
    QLineEdit *destinationLineEdit;
    QPushButton *navigateButton;
    QWebEngineView *webView;
};

#endif // MAINWINDOW_H
