#pragma once

#include "TextData.hpp"
#include "condition_edit_widget.hpp"

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <iostream>
#include <vector>

using QtNodes::ConnectionPolicy;
using QtNodes::NodeData;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class UmrfNodeModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    UmrfNodeModel();

    virtual ~UmrfNodeModel() {}

public:
    QString caption() const override { return QString(name_.c_str()); }

    bool captionVisible() const override { return true; }

    bool resizable() const override { return true; }

    static QString Name() { return QString("UmrfNodeModel"); }

    QString name() const override { return UmrfNodeModel::Name(); }

public:
    unsigned int nPorts(PortType portType) const override;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex const port) override;

    void setInData(std::shared_ptr<NodeData> data, PortIndex const portIndex) override;

    QWidget *embeddedWidget() override { return condition_edit_widget_; }

public:
    void inputConnectionCreated(QtNodes::ConnectionId const &ci) override;

    void inputConnectionDeleted(QtNodes::ConnectionId const &ci) override;

private:
    ConditionEditWidget* condition_edit_widget_;
    QString _inputText;
    std::string name_;

    std::map<PortIndex, std::string> input_connections_;
};
