#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

int main()
{
    Matrix<float, 2, 3> m_23;
    m_23<<1,2,3,4,5,6;
    cout<<m_23<<endl;
    return 0;
}


