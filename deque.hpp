template<typename T>
struct Deque{
      std::deque<T> d;
      Deque(size_t len):
            d(len)
      {}
      Deque():
            d()
      {}
      Deque(size_t len,const T&val):
            d(len,val)
      {}
      decltype(auto) operator[](size_t n){
            return d[n];
      }
      decltype(auto) operator[](size_t n)const{
            return d[n];
      }
      decltype(auto) at(size_t n){
            return d.at(n);
      }
      decltype(auto) at(size_t n)const{
            return d.at(n);
      }
      decltype(auto) size()const{
            return d.size();
      }
      decltype(auto) push_back(const T&val){
            return d.push_back(val);
      }
      decltype(auto) push_front(const T&val){
            return d.push_front(val);
      }
      decltype(auto) pop_front(){
            return d.pop_front();
      }
      decltype(auto) pop_back(){
            return d.pop_back();
      }
      using iterator=typename std::deque<T>::iterator;
      decltype(auto) begin(){
            return d.begin();
      }
      decltype(auto) begin()const{
            return d.begin();
      }
      decltype(auto) rbegin(){
            return d.rbegin();
      }
      decltype(auto) rbegin()const{
            return d.rbegin();
      }
      decltype(auto) cbegin()const{
            return d.cbegin();
      }
      decltype(auto) end(){
            return d.end();
      }
      decltype(auto) end()const{
            return d.end();
      }
      decltype(auto) rend(){
            return d.rend();
      }
      decltype(auto) rend()const{
            return d.rend();
      }
      decltype(auto) cend()const{
            return d.cend();
      }
      decltype(auto) erase(const iterator&i){
            return d.erase(i);
      }
      decltype(auto) insert(const iterator&i,const T&val){
            return d.insert(i,val);
      }
};
