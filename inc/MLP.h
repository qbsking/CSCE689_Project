#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <functional>
#include <numeric>
#include <fstream>
#define epsilon 0.003
class MLP{
    public:
    std::vector<double> weightij;
    std::vector<double> weightjk;
    std::vector<double> h;
    int s1;
    int s2;
    MLP(int size1, int size2){
        s1=size1;
        s2=size2;
    }
    
    ~MLP(){};
    
    void load(std::string file){
        std::ifstream myfile;
        int n=s1*s2;
        
        myfile.open(file,std::ios::in);
        double value;
            
        while(myfile >> value){
            if(weightij.size()<n)
                weightij.push_back(value);
            else
                weightjk.push_back(value);
            }
        
        myfile.close();
        
        //std::cout << weightij.size() + weightjk.size() << std::endl;
        // print(weightij);
        // print(weightjk);
        
    };
    
    void save(std::string file){
        std::ofstream myfile;
        myfile.open(file);//,std::ios::out);
        
        for(auto i : weightij){
            myfile << i <<" ";
        }
        for(auto j : weightjk){
            myfile << j <<" ";
        }
        myfile.close();
    };
    
    double predict(std::vector<double> &input){
        h.clear();
        double yhat=0;
        double hj=0;
        double y=0;
        for(int i=0;i<s2;i++){
            std::vector<double> weight(weightij.begin() + i*s2,weightij.begin() + (i+1)*s2);
            //std::cout<<std::endl;
            // print(weight);

            // print(input);
            hj=sigmoid(input,weight);
            h.push_back(hj);
            // std::cout<<hj<<" ";
        }
        
        yhat=sigmoid(h,weightjk);
        
        return yhat;
        
    };
    
    void update(std::vector<double> &input, double output){
        std::vector<double> mid;
        double a=predict(input);
        double ydiff=output-a;
        double sigmoid_derivative_jk=sigmoid_derivative(h,weightjk);
        double sigmoid_derivative_ij=sigmoid_derivative(input, weightij);
        //std::cout<<"grad "<<a<<" "<<sigmoid_derivative_jk<<" "<<sigmoid_derivative_ij<<std::endl;
        
        for(int i=0;i<s2;i++){
            mid.push_back(ydiff*sigmoid_derivative_jk*weightjk[i]*sigmoid_derivative_ij);
        }

        double sum1 = 0.0;

        for (int i=0;i<s1;i++){
            for(int j=0;j<s2;j++){
                sum1+=std::abs(input[i]*mid[j]);
            }
        }
        
        for (int i=0;i<s1;i++){
            for(int j=0;j<s2;j++){
                if (sum1 > 5)
                {
                    weightij[i*s2+j]+=epsilon*input[i]*mid[j]*5/sum1;
                } else
                {
                    weightij[i*s2+j]+=epsilon*input[i]*mid[j];
                }
                // std::cout<<"weightij"<<" "<<weightij[i*s2+j]<<std::endl;
            }
        }

        double sum2 = 0.0;

        for(int i=0;i<s2;i++){
            sum2+=std::abs(h[i]*sigmoid_derivative_jk*ydiff);
        }
        
        for(int i=0;i<s2;i++){
            if (sum1 > 1)
            {
                weightjk[i]+=epsilon*h[i]*sigmoid_derivative_jk*ydiff/sum2;
            } else
            {
                weightjk[i]+=epsilon*h[i]*sigmoid_derivative_jk*ydiff;
            }
            // std::cout<<"weightjk"<<" "<<weightjk[i]<<std::endl;
        }
        
    }
    
    
    double sigmoid(std::vector<double> x,std::vector<double> w){
        double t=std::inner_product(x.begin(), x.end(), w.begin(), 0.0);
        //std::cout<<"t"<<t<<std::endl;
        if(t>0){
            return t;
        }
        else
            return 0;
    }
    
    double sigmoid_derivative(std::vector<double> x,std::vector<double> w){
        double t=std::inner_product(x.begin(), x.end(), w.begin(), 0.0);
        if(t>0)
            return 1;
        else
            return 0;
    }
    
    void print(std::vector<double> &input)
    {
        for (int i = 0; i < input.size(); i++) {
            std::cout << input.at(i) << ' ';
        }
    }
    
    
    
};