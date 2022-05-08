#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <math.h> 

class perceptron
{
public:
	perceptron(float eta, int epochs);
	float netInput(std::vector<float> X);
	int predict(std::vector<float> X);
	void fit(std::vector< std::vector<float> > X, std::vector<float> y);
	void printErrors();
	void exportWeights(std::string filename);
	void importWeights(std::string filename);
	void printWeights();
private:
	float m_eta;
	int m_epochs;
	std::vector < float > m_w;
	std::vector < float > m_errors;
};

perceptron::perceptron(float eta, int epochs)
{
	m_epochs = epochs;
	m_eta = eta;
}

void perceptron::fit(std::vector< std::vector<float> > X, std::vector<float> y)
{
	for (int i = 0; i < X[0].size() + 1; i++) // X[0].size() + 1 -> I am using +1 to add the bias term
	{
		m_w.push_back(0);
	}
	for (int i = 0; i < m_epochs; i++)
	{
		int errors = 0;
		for (int j = 0; j < X.size(); j++)
		{
			float update = m_eta * (y[j] - predict(X[j]));
			for (int w = 1; w < m_w.size(); w++) { m_w[w] += update * X[j][w - 1]; }
			m_w[0] = update;
			errors += update != 0 ? 1 : 0;
		}
		m_errors.push_back(errors);
	}
}

float perceptron::netInput(std::vector<float> X)
{
	// Sum(Vector of weights * Input vector) + bias
	float probabilities = m_w[0];
	for (int i = 0; i < X.size(); i++)
	{
		probabilities += X[i] * m_w[i + 1];
	}
	return probabilities;
}

int perceptron::predict(std::vector<float> X)
{
	return netInput(X) > 0 ? 1 : -1; //Step Function
}


void perceptron::exportWeights(std::string filename)
{
	std::ofstream outFile;
	outFile.open(filename);

	for (int i = 0; i < m_w.size(); i++)
	{
		outFile << m_w[i] << std::endl;
	}

	outFile.close();
}

void perceptron::importWeights(std::string filename)
{
	std::ifstream inFile;
	inFile.open(filename);

	for (int i = 0; i < m_w.size(); i++)
	{
		inFile >> m_w[i];
	}
}

void perceptron::printWeights()
{
	std::cout << "weights: ";
	for (int i = 0; i < m_w.size(); i++)
	{
		std::cout << m_w[i] << " ";
	}
	std::cout << std::endl;
}