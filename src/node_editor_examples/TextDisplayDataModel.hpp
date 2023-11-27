#pragma once

#include "TextData.hpp"

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

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class TextDisplayDataModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    TextDisplayDataModel();

    virtual ~TextDisplayDataModel() {}

public:
    QString caption() const override { return QString(name_.c_str()); }

    bool captionVisible() const override { return true; }

    bool resizable() const override { return true; }

    static QString Name() { return QString("TextDisplayDataModel"); }

    QString name() const override { return TextDisplayDataModel::Name(); }

public:
    unsigned int nPorts(PortType portType) const override;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex const port) override;

    void setInData(std::shared_ptr<NodeData> data, PortIndex const portIndex) override;

    QWidget *embeddedWidget() override { return _label; }

public:
    void inputConnectionCreated(QtNodes::ConnectionId const &ci) override;

    void inputConnectionDeleted(QtNodes::ConnectionId const &ci) override;

private:
    QLabel *_label;
    QString _inputText;
    std::string name_;

    std::map<PortIndex, std::string> input_connections_;
};
