#ifndef TESTLAYOUT_H
#define TESTLAYOUT_H

#include <QWidget>

namespace Ui {
    class TestLayout;
}

class TestLayout : public QWidget {
    Q_OBJECT
public:
    TestLayout(QWidget *parent = 0);
    ~TestLayout();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TestLayout *ui;
};

#endif // TESTLAYOUT_H
