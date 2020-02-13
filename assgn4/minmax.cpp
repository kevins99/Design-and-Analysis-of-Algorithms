#include <iostream> 
#include <math.h>
using namespace std;

//CREATE STRUCTURE TO STORE RESULTS
struct results{     
    int mi;
    int ma;
};

class minmax {
    int *arr;
    int n;

    public:
    minmax() {
        cout<<"Enter the number of elements"<<endl;
        cin>>n;
        arr = new int[n];
        for (int i=0; i<n; i++) {
            cout<<"Enter element "<<i+1<<endl;
            cin>>*(arr + i);
        }
    }
    
    int size() {
        return this->n;
    }
    
    
    results min_max(int low, int high) {
        results r;
        results r1;
        results r2;
        if ((high - low) <= 1) {
            r.ma = max(*(arr + high), *(arr + low));
            r.mi = min(*(arr + high), *(arr + low));
            cout<<"MAX: "<<r.ma<<endl;
            cout<<"MIN: "<<r.mi<<endl;
        }
        else {
            for(int i=low; i<high; i++) {
                cout<<*(arr+i);
            }
            cout<<endl;
            r1 = min_max(low, (low+high)>>1);
            r2 = min_max(((low+high)>>1)+1, high);

            for(int i=low; i<high; i++) {
                cout<<*(arr+i);
            }
            cout<<endl;

            r.ma = max(r1.ma, r2.ma);
            r.mi = min(r1.mi, r2.mi);

            for(int i=low; i<high; i++) {
                cout<<*(arr+i);
            }
            cout<<endl;
        }
        return r;
    }
};


int main() {
   int n;
   minmax m;
   results r;
   n = m.size();
   r = m.min_max(0, n-1);
   cout<<"Max: "<<r.ma<<endl;
   cout<<"Min: "<<r.mi<<endl;
}