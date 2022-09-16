struct s{
    s(){
        ic()
    }
    ~s(){
        ic()
    }
};

struct d:s{
    d(){
        ic()
    }
    ~d(){
        ic()
    }
};


int main(){
    d a;    
}
