#include <iostream>
#include <cmath>
#include <chrono> 
using std::cout;
using std::endl;
// �{���W��: NLight41 �����j��̨Τƾ� / NLight41 HoloLoop Optimizer 
// ��B�c�Q: 03.18.2025 �쪩: 30.20.2025 by NLight41 
// �w�p���u�ϥ� std �禡�w�A�G�����ŧi�R�W�Ŷ� 
// �����w��ŧi std �� cout, endl �H�Q�{���X���g 
 

// �w�q�t�ΰѼƵ��c (�����p�W�[�Ѽ�) 
struct Parameters {
	double param1;
	double param2;
	// �p�e��s�X�i���V�q�Φ��A�ΥH�B�̧�������Ѽ�  
	
};


// �����禡 : �����t�ιB�@�A�íp�� �������G �P �w���� �������~�t 
// �]�w �w���Ȭ� 100�A�Ӽ����ҫ��� param1 * sin(param2) + 10 
inline double simulationFunction(const Parameters &p) {
	double outcome = p.param1 * std::sin(p.param2) + 10;
	double expected = 100.0;
	return std::fabs(outcome - expected);
	
}


// �ϥΦ����t���k���p��� (�쪩) 
inline void computeGradient(const Parameters &p, Parameters &grad, double delta = 1e-5){
	Parameters p_temp = p;
	double f0 = simulationFunction(p);
	
	// �p�� param1 ��~�t����� 
	p_temp.param1 = p.param1 + delta;
	double f1 = simulationFunction(p_temp);
	grad.param1 = (f1 - f0) / delta;
	p_temp.param1 = p.param1;	// ���m 
	
	// �p�� param2 ��~�t����� 
	p_temp.param2 = p.param2 + delta;
	double f2 = simulationFunction(p_temp);
	grad.param2 = (f2 - f0) / delta;
	
}


// �۾A�������j��̨Τƺt��k : ���X�ʶq�k�h �P �����^�X�����z�� �i��ѼƧ�s 
// mometumFactor : �ʶq��� / HoloFactor : �����^�X�]�l 
Parameters  adaptiveHoloLoopOptimizer(Parameters initParams, double learningRate, double momentumFactor, double holoFactor, double threshold, int maxIterations) {
	Parameters p = initParams;
	Parameters grad{0.0, 0.0};
	Parameters momentum{0.0, 0.0};	// �O�s�W�@������װʶq��  
	
	double prevError = simulationFunction(p);
	double currError = prevError;
	int iteration = 0;
	
	
	while (currError > threshold && iteration < maxIterations) {
		
		// 1. �p���� (�쪩) 
		computeGradient(p, grad);
		
		// 2. �ʶq��s : �N��e����� �P �W�@�����ժ���� ����ҿĦX 
		momentum.param1 = momentumFactor * momentum.param1 + (1 - momentumFactor) * grad.param1;
		momentum.param2 = momentumFactor * momentum.param2 + (1 - momentumFactor) * grad.param2;
		
		// 3. �����^�X�վ� : �ھڱ���ܤƶq�վ��ק�s�t�� 
		double errorDiff = currError - prevError;
		// holoAdjustment : �����^�X�ܦ]�A�|�H�ۻ~�t �W�ɻP�U�� �i�� �ʺA�ץ� 
		double holoAdjustment = holoFactor * errorDiff;
		
		// 4. ��s�Ѽ� : �N �ʶq �P �����^�X�ܦ] ���X��A�i���פU����s 
		p.param1 -= learningRate * (momentum.param1 + holoAdjustment);
		p.param2 -= learningRate * (momentum.param2 + holoAdjustment);
		
		// 5. ��s�~�t�� �� ���N���� 
		prevError = currError;
		currError = simulationFunction(p);
		iteration++;
		
		// 6. ��X��e���N���p�A�Ω� �l�ܪ��� �� ��K�վ�  
		cout << "Iteration: " << iteration
			 << ", Error: " << currError 
			 << ", param1: " << p.param1
			 << ", param2: " << p.param2 << endl; 
				
	}
	
	return p;	
}


int main() {
	// ��l�ѼƳ]�w 
	Parameters initialParams {50.0, 1.0};
	double learningRate = 0.01;
	double momentumFactor = 0.9;	// �q�`�w�] momentum �ѼƬ� 0.9�A�g��k�h��� 0.9 �b�[�t���ĻP�O��í�w�ʤ������ۨ}�n�������I 
	double holoFactor = 0.05;		// �ھڻ~�t�ܤƽվ�B�� 
	double threshold = 1e-3;		// ���ħP�w�֭� 
	int maxIterations = 10000;
	
	// �p�� �[��ʯ� 
	auto start = std::chrono::high_resolution_clock::now();
	Parameters optimized = adaptiveHoloLoopOptimizer(initialParams, learningRate, momentumFactor, holoFactor, threshold, maxIterations);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	
	cout << "\nOptimized Parameters:" << endl;
	cout << "param1: " << optimized.param1 << endl;
	cout << "param2: " << optimized.param2 << endl;
	cout << "Time elapsed: " << elapsed.count() << " seconds." << endl;
	
	return 0;
		
}



 
