#include <iostream>

#include <Eigen/Dense>
#include <Eigen/SVD>

#include <map>
#include <vector>
#include <string>

#include "pch.h"
#include "reader.h"
#include "bullseye.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

int main()
{
	
	MatrixXd theta_0 = readMatrix("C:/Users/Whenti/Documents/Travail/EPFL/PDM/code/c++/bullseye/bullseye/data/theta_0");

	MatrixXd x_array = readMatrix("C:/Users/Whenti/Documents/Travail/EPFL/PDM/code/c++/bullseye/bullseye/data/x_array");
	MatrixXd y_array = readMatrix("C:/Users/Whenti/Documents/Travail/EPFL/PDM/code/c++/bullseye/bullseye/data/y_array");
	
	size_t n(y_array.rows());
	size_t d(x_array.cols());
	size_t k(y_array.cols());
	size_t p(d*k);

	MatrixXd mu = 0 * MatrixXd::Ones(p, 1);
	MatrixXd sigma = MatrixXd::Identity(p, p);

	VectorXd prior_std = 1 *MatrixXd::Ones(p, 1);

	//bullseye initialization
	vector<MatrixXd> As(0);
	for (size_t i(0); i < n; ++i)
		As.push_back(A(x_array, i, p, k));
	
	double ELBO = -10000000; //-∞
	//end initialization

	cout << "bullseye begin!" << endl;
	for (size_t i(0); i < 1000; ++i)
	{
		bullseye_iteration(x_array, y_array, mu, sigma, As, prior_std, ELBO);
		cout << "norm : " << (mu - theta_0).norm() << endl;
	}
	cout << "bullseye done!" << endl;

	return 0;
}