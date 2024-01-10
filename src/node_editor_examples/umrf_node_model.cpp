#include "umrf_node_model.hpp"
#include "counter.hpp"
#include <QtNodes/ConnectionIdUtils>

UmrfNodeModel::UmrfNodeModel()
: name_{"Action_" + std::to_string(global::count++)}
{
    condition_edit_widget_ = new ConditionEditWidget(name_);
}

unsigned int UmrfNodeModel::nPorts(PortType portType) const
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

NodeDataType UmrfNodeModel::dataType(PortType portType, PortIndex portIndex) const
{
    NodeDataType ndt;

    switch (portType) {
    case PortType::In:
        if (portIndex >= input_connections_.size())
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

std::shared_ptr<NodeData> UmrfNodeModel::outData(PortIndex)
{
    return std::make_shared<TextData>(name_.c_str());
}

void UmrfNodeModel::setInData(std::shared_ptr<NodeData> data, PortIndex const portIndex)
{
    auto textData = std::dynamic_pointer_cast<TextData>(data);

    if (!textData) 
    {
        condition_edit_widget_->setName("");
    }
    else
    {
        condition_edit_widget_->setName(textData->text().toStdString());
        if (portIndex > input_connections_.size())
        {
            return;
        }

        input_connections_.push_back(textData->text().toStdString());
    }
}

void UmrfNodeModel::inputConnectionCreated(QtNodes::ConnectionId const &ci)
{
}

void UmrfNodeModel::inputConnectionDeleted(QtNodes::ConnectionId const &ci)
{
    std::cout << ci.inPortIndex << std::endl;
    portsAboutToBeDeleted(PortType::In, ci.inPortIndex, ci.inPortIndex);
    input_connections_.erase(input_connections_.begin() + ci.inPortIndex);
    portsDeleted();
}