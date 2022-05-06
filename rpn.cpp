#include <list> 
#include <stack>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

int main(){
    string s;
    double num;
    stack<double> stac;

    while(cin.good()){
        cin >> s;
        stringstream ss;
        ss << s;

        ss >> num;
       

        if(ss.fail()){

            if(s == "+"){
                if(stac.size() < 2)
                    break;
                
                int num2 = stac.top();
                stac.pop();
                int num1 = stac.top();
                stac.pop();

                int sol = num1 + num2;

                stac.push(sol);
            }
            if(s == "-"){
                if(stac.size() < 2)
                    break;
                
                int num2 = stac.top();
                stac.pop();
                int num1 = stac.top();
                stac.pop();

                int sol = num1 - num2;

                stac.push(sol);
            }
            if(s == "/"){
                if(stac.size() < 2)
                    break;

                int num2 = stac.top();
                stac.pop();
                int num1 = stac.top();
                stac.pop();

                int sol = num1 / num2;

                stac.push(sol);

            }
            if(s == "*"){
                if(stac.size() < 2)
                    break;

                int num2 = stac.top();
                stac.pop();
                int num1 = stac.top();
                stac.pop();

                int sol = num1 * num2;

                stac.push(sol);
            }

            ss.clear();
        }

        else{
            stac.push(num);
        }

    }

    while (!stac.empty()) {
        cout << ' ' << stac.top();
        stac.pop();
    }

    return 0;


}