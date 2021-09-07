#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QList>
#include<QPointF>
#include <QDebug>
#include <QTouchEvent>
#include <QQuickItem>
#include<QEvent>

class TouchItem : public QQuickItem
{

public:
    TouchItem() {}//constructor


    struct GetPoints//structure
    {
        QPointF pos;
        qreal x() const { return pos.x(); }
        qreal y() const { return pos.y(); }
    };
    GetPoints startPoint;
    GetPoints endPoint;


    bool flag=false;
    float right=0;
    float left=0;


    void touchEvent(QTouchEvent *event) override {

        switch (event->type()) {

        case QEvent::TouchBegin:
        {
            // Dynamic cast to QTouchEvent*
            const QTouchEvent *touch = dynamic_cast<QTouchEvent*>(event);
            //list for storing points
            const QList<QTouchEvent::TouchPoint> points = touch->touchPoints();
            //get the points frm structure object
            startPoint.pos = points.at(0).pos();
            right=startPoint.x();
            flag=false;
            break;
        }

        case QEvent::TouchEnd:
        {
            const QTouchEvent *tuch = dynamic_cast<QTouchEvent*>(event);
            const QList<QTouchEvent::TouchPoint> point = tuch->touchPoints();
            endPoint.pos = point.at(0).pos();
            left=endPoint.x();
            flag=true;
            break;
        }

        default:
            break;
        }

        if(flag)
        {
            if(right < left){
                qDebug()<<"Swiped Right...";
            }
            else if(right > left){
                qDebug()<<"Swiped Left...";
            }
            else if(right == left){
                qDebug()<<"Clicked...";
            }
         }
    }
};

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<TouchItem>("App", 1, 0, "TouchItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}


