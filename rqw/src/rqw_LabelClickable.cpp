#include "rqw_LabelClickable.h"

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked(); // 触发信号
    }
    QLabel::mousePressEvent(event);
}
