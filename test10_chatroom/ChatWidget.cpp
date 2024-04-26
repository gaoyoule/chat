#include "ChatWidget.h"

ChatWidget::ChatWidget(QWidget *parent):
    QListWidget(parent)
{
    setSelectionMode(QAbstractItemView::NoSelection);//item不可选中，为了消除鼠标移动到item上的效果
    setMaximumWidth(ITEM_WIDTH);
    setMinimumWidth(ITEM_WIDTH);
}

ChatWidget::~ChatWidget()
{
    
}

void ChatWidget::addMsg(QString msg, int headId, ChatItem::ChatRole role)
{
    //创建自定义页面
    ChatItem* item = new ChatItem(msg, headId, role, this);
    
    //创建行对象
    QListWidgetItem* listItem = new QListWidgetItem(this);

    //修改行对象的大小
    listItem->setSizeHint(item->size());

    //三者绑定
    setItemWidget(listItem, item);
}

