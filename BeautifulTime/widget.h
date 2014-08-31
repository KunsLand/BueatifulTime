#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWebView>
#include <QMouseEvent>
#include <QGridLayout>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    bool eventFilter(QObject *, QEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    QGridLayout *layout;
    QWebView *web;
    QLabel *label;
    bool mousepressed;
    int width;
    int height;
    int w_quit;
    int h_quit;
};

#endif // WIDGET_H
