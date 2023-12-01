#pragma once

#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtNodes/Definitions>


class ConditionEditWidget : public QWidget
{
    Q_OBJECT
public:
    ConditionEditWidget(const std::string parent_name, QWidget* parent = nullptr);

    ~ConditionEditWidget();

    void setName(const std::string& name);

private Q_SLOTS:
    // void onPlusClicked();

    // void onMinusClicked();

private:

    QLabel* name_label_;
private:

};
