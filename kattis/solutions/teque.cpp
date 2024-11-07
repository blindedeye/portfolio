#include <iostream>
#include <string>
#include <deque>

using namespace std;

class Teque {
private:
    deque<int> front, back;
    void balance(){
        if (front.size() > back.size() + 1){
            back.push_front(front.back());
            front.pop_back();
        } 
        else if (back.size() > front.size()){
            front.push_back(back.front());
            back.pop_front();
        }
    }
public:
    Teque(){}
    void push_back(int num){
        back.push_back(num);
        balance();
    }
    void push_front(int num){
        front.push_front(num);
        balance();
    }
    void push_middle(int num){
        front.push_back(num);
        balance();
    }
    int get_i(int index){
        if (index < front.size()){
            return front[index];
        } 
        else return back[index - front.size()];
    }
};

int main(){
Teque obj=Teque();
int ops, num;
string str;
cin >> ops;
for(int i=0; i<ops; i++){
    cin >> str >> num;
    if (str == "push_back") obj.push_back(num);
    else if (str == "push_middle") obj.push_middle(num);
    else if (str == "push_front") obj.push_front(num);
    else cout << obj.get_i(num) << endl;
}
}