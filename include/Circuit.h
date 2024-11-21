#ifndef _CIRCUIT_H_
#define _CIRCUIT_H_

#include <vector>
#include <map>
#include <string>
#include <Eigen>
class Circuit
{
public:
    // 添加元件：电源、电阻、电容、电感，MOSFET，MOSFET模型
    // 对于电源，我们在这里只进行DC分析，因此传入参数只有节点和数值大小
    void addVoltageSource(const string& name, const string& node1, const string& node2, double voltage);
    void addResistor(const string& name, const string& node1, const string& node2, double resistance);
    void addCapacity(const string& name, const string& node1, const string& node2, double capacitance);
    void addInductor(const string& name, const string& node1, const string& node2, double inductance);
    void addMOSFET(const string& name, const string& ND, const string& NG, const string& NS, const string& modelID, double width, double length);
    void addMOSFETModel(const string& mosID, double VT, double MU, double COX, double LAMBDA, double CJ0);

    // 建立导纳矩阵
    void buildYMatrix();
    // 建立电流向量
    void buildCurrentVector();
    // 电路求解器
    void solve();
    // 计算元件的电流和功耗
    void computeCurrentsAndPowers();

    // 结果输出
    void printNodeVoltages();
    void printCurrentsAndPowers();

private:
    /*我们在这里定义电路的元件结构
    关于结构参数：
    Node：矩阵索引，名称
    VoltageSource：名称，节点，数值
    Resistor: 名称，节点，数值
    Capacity：名称，节点，数值
    Inductor：名称，节点，数值
    MOSFET：名称，端口，ID，尺寸
    model：ID，参数
    */
    struct Node
    {
        int index;
        string name;
    };

    struct VoltageSource
    {
        string name;
        int node1, node2;
        double voltage;
    };

    struct Resistor
    {
        string name;
        int node1, node2;
        double resistance;
    };

    struct Capacity
    {
        string name;
        int node1, node2;
        double capacitance;
    };

    struct Inductor
    {
        string name;
        int node1, node2;
        double inductance;
    };

    struct MOSFET
    {
        string name;
        int ND, NG, NS;
        string modelID;
        double width,length;
    };

    struct MOSFETModel
    {
        string mosID;
        double VT, MU, COX, LAMBDA, CJ0; 
    };

    // 存储方式，构建map和vector
    map<string, Node> nodes;
    vector<VoltageSource> voltagesources;
    vector<Resistor> resistors;
    vector<Capacity> capacities;
    vector<Inductor> inductors;
    vector<MOSFET> mosfets;
    map<string, MOSFETModel> mosfetmodels;

    // 定义元件添加方法
    void addVoltageSource(const string& name, const string& node1, const string& node2, double voltage)
    {
        voltagesources.push_back({name, nodes[node1].index, nodes[node2].index,voltage});
    }
    void addResistor(const string& name, const string& node1, const string& node2, double resistance)
    {
        resistors.push_back({name, nodes[node1].index, nodes[node2].index, resistance});
    }
    void addCapacity(const string& name, const string& node1, const string& node2, double capacitance)
    {
        capacities.push_back({name, nodes[node1].index, nodes[node2].index, capacitance});
    }
    void addInductor(const string& name, const string& node1, const string& node2, double inductance)
    {
        inductors.push_back({name, nodes[node1].index, nodes[node2].index, inductance});
    }
    void addMOSFET(const string& name, const string& ND, const string& NG, const string& NS, const string& modelID, double width, double length)
    {
        mosfets.push_back({name, nodes[ND].index, nodes[NG].index, nodes[NS].index, modelID, width, length});
    }
    void addMOSFETModel(const string& mosID, double VT, double MU, double COX, double LAMBDA, double CJ0)
    {
        mosfetmodels[mosID] = {VT, MU, COX, LAMBDA,CJ0};
    }



    







};
#endif