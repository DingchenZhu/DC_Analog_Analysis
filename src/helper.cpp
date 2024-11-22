#include "Circuit.h"
#include <Eigen>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using namespace Eigen;

    
    // 定义元件添加方法
void Circuit::addNode(const string& name)
    {
        if(nodes.find(name) == nodes.end())
        {
            // 将添加到节点放在nodes的末尾：注意添加节点的顺序
            int index = nodes.size();
            nodes[name] = {index, name};
        }
    }
void Circuit::addVoltageSource(const string& name, const string& node1, const string& node2, double voltage)
    {
        voltagesources.push_back({name, nodes[node1].index, nodes[node2].index,voltage});
    }
void Circuit::addResistor(const string& name, const string& node1, const string& node2, double resistance)
    {
        resistors.push_back({name, nodes[node1].index, nodes[node2].index, resistance});
    }
void Circuit::addCapacity(const string& name, const string& node1, const string& node2, double capacitance)
    {
        capacities.push_back({name, nodes[node1].index, nodes[node2].index, capacitance});
    }
void Circuit::addInductor(const string& name, const string& node1, const string& node2, double inductance)
    {
        inductors.push_back({name, nodes[node1].index, nodes[node2].index, inductance});
    }
void Circuit::addMOSFET(const string& name, const string& ND, const string& NG, const string& NS, const string& modelID, double width, double length)
    {
        mosfets.push_back({name, nodes[ND].index, nodes[NG].index, nodes[NS].index, modelID, width, length});
    }
void Circuit::addMOSFETModel(const string& mosID, double VT, double MU, double COX, double LAMBDA, double CJ0)
    {
        mosfetmodels[mosID] = {VT, MU, COX, LAMBDA,CJ0};
    }


// 构建导纳矩阵
void Circuit::buildYMatrix()
{
    int size = nodes.size;
    YMatrix = MatrixXd::Zero(size, size);

    // 关于电阻对电路矩阵的贡献
    for(const auto& resistor : resistors)
    {
        int n1 = resistor.node1;
        int n2 = resistor.node2;
        double g = 1.0 / resistor.resistance;

        if(n1 >= 0) YMatrix(n1, n1) += g;
        if(n2 >= 0) YMatrix(n2, n2) += g;

        if (n1 >= 0 && n2 >= 0)
        {
            YMatrix(n1, n2) -= g;
            YMatrix(n2, n1) -= g;
        }
    }

}

void Circuit::buildCurrentVector()
{
    int size = nodes.size();
    CurrentVector = Vector::Zero(size);

    for(const auto& currentsource : currentsources)
    {
        int n1 = currentsource.
    }
}

