#include <QWebFrame>
#include "widget.h"

Widget::Widget(QWidget *parent):
    QWidget(parent){
    width = 590;
    height = 450;
    w_quit = 25;
    h_quit = 25;
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(width,height);
    show();
    web = new QWebView(this);
    web->installEventFilter(this);

    layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->addWidget(web,0,0,1,2);
    web->setUrl(QString("qrc:/html/index.html"));
    web->setFixedSize(width,height);
    layout->setAlignment(web,Qt::AlignCenter|Qt::AlignAbsolute);

    QPixmap image("://icons/quit.png");
    label = new QLabel();
    label->installEventFilter(this);
    label->setFixedSize(w_quit,h_quit);
    label->setPixmap(image);
    label->setScaledContents(true);
    layout->addWidget(label,0,1);
    layout->setAlignment(label,Qt::AlignTop|Qt::AlignRight);

    mousepressed = false;
}

Widget::~Widget(){
    delete web;
    delete label;
    delete layout;
}

bool Widget::eventFilter(QObject *obj, QEvent *e){
    if(obj==web){
        if(e->type()==QEvent::MouseButtonDblClick){
            mouseDoubleClickEvent((QMouseEvent*)e);
        }else if(e->type()==QEvent::MouseButtonPress){
            mousePressEvent((QMouseEvent*)e);
        }else if(e->type()==QEvent::MouseButtonRelease){
            mouseReleaseEvent((QMouseEvent*)e);
        }else if(e->type()==QEvent::MouseMove){
            mouseMoveEvent((QMouseEvent*)e);
        }
    }
    else if(obj==label){
        if(e->type()==QEvent::MouseButtonPress){
            closeEvent((QCloseEvent *)e);
        }
    }
    return QWidget::eventFilter(obj,e);
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event){
    event->accept();
    web->page()->mainFrame()->evaluateJavaScript("clicked()");
}


void Widget::mousePressEvent(QMouseEvent *event) {
    mousepressed = true;
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void Widget::mouseReleaseEvent(QMouseEvent *event){
    event->accept();
    mousepressed = false;
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
    if(mousepressed)
        move(event->globalX()-m_nMouseClick_X_Coordinate,
             event->globalY()-m_nMouseClick_Y_Coordinate);
    else{
        int x = event->globalX()-this->pos().x();
        int y = event->globalY()-this->pos().y();
        if(x>width-w_quit&&y<h_quit)
            label->show();
        else if(!label->isHidden())
            label->hide();
    }
}

void Widget::closeEvent(QCloseEvent *event){
    event->accept();
    this->close();
}
