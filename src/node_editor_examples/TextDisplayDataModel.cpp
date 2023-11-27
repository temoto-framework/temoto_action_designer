#include "TextDisplayDataModel.hpp"
#include "counter.hpp"

TextDisplayDataModel::TextDisplayDataModel()
: _label(new QLabel("Resulting Text"))
, name_{"Action_" + std::to_string(global::count++)}
{
    _label->setMargin(3);
    // _label->sizePolicy().verticalPolicy().
}

unsigned int TextDisplayDataModel::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:
        result = input_connections_.size() + 1;
        break;

    case PortType::Out:
        result = 1;
        break;

    default:
        break;
    }

    return result;
}

NodeDataType TextDisplayDataModel::dataType(PortType portType, PortIndex portIndex) const
{
    NodeDataType ndt;

    switch (portType) {
    case PortType::In:
        if (input_connections_.find(portIndex) == input_connections_.end())
        {
            ndt = NodeDataType{"text", "IN"};
            break;
        }
        else
        {
            ndt = NodeDataType{"text", input_connections_.at(portIndex).c_str()};
            break;
        }

    case PortType::Out:
        ndt = NodeDataType{"text", "OUT"};
        break;

    default:
        break;
    }

    return ndt;
}

std::shared_ptr<NodeData> TextDisplayDataModel::outData(PortIndex)
{
    return std::make_shared<TextData>(name_.c_str());
}

void TextDisplayDataModel::setInData(std::shared_ptr<NodeData> data, PortIndex const portIndex)
{
    auto textData = std::dynamic_pointer_cast<TextData>(data);

    if (!textData) 
    {
        _label->setText("");
    }
    else
    {
        _label->setText(textData->text());
        input_connections_[portIndex] = textData->text().toStdString();
    }

    _label->adjustSize();
}

void TextDisplayDataModel::inputConnectionCreated(QtNodes::ConnectionId const &ci)
{
}

void TextDisplayDataModel::inputConnectionDeleted(QtNodes::ConnectionId const &ci)
{
    input_connections_.erase(ci.inPortIndex);
}